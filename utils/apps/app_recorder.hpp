/*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*   Product name: redemption, a FLOSS RDP proxy
*   Copyright (C) Wallix 2010-2014
*   Author(s): Jonathan Poelen
*/

#ifndef REDEMPTION_UTILS_APPS_APP_RECORDER_HPP
#define REDEMPTION_UTILS_APPS_APP_RECORDER_HPP

#include "FileToChunk.hpp"
#include "ChunkToFile.hpp"
#include "out_meta_sequence_transport.hpp"
#include "crypto_out_meta_sequence_transport.hpp"
#include "in_meta_sequence_transport.hpp"
#include "recording_progress.hpp"
#include "iter.hpp"
#include "crypto_in_meta_sequence_transport.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

template<class CaptureMaker, class... ExtraArguments>
int recompress_or_record( std::string & output_filename, std::string & input_filename
                        , Inifile & ini, bool remove_input_file, bool infile_is_encrypted
                        , bool auto_output_file, uint32_t begin_cap, uint32_t end_cap
                        , uint32_t order_count, uint32_t clear, unsigned zoom
                        , bool show_file_metadata, bool show_statistics
                        , bool force_record, uint32_t verbose
                        , ExtraArguments&&... extra_argument);

template<typename InWrmTrans>
unsigned get_file_count( InWrmTrans & in_wrm_trans, uint32_t & begin_cap, uint32_t & end_cap, timeval & begin_record
                       , timeval & end_record);

template<typename InWrmTrans>
void remove_file(InWrmTrans & in_wrm_trans, const char * hash_path, const char * infile_path
                , const char * infile_basename, const char * infile_extension, bool is_encrypted);

template<class CaptureMaker, class... ExtraArguments>
static int do_record( Transport & in_wrm_trans, const timeval begin_record, const timeval end_record
                    , const timeval begin_capture, const timeval end_capture, std::string const & output_filename
                    , Inifile & ini, unsigned file_count, uint32_t order_count, uint32_t clear, unsigned zoom
                    , bool show_file_metadata, bool show_statistics, uint32_t verbose
                    , ExtraArguments && ... extra_argument);

static int do_recompress( CryptoContext & cctx, Transport & in_wrm_trans, const timeval begin_record
                        , std::string const & output_filename, Inifile & ini, uint32_t verbose);


static void show_statistics(FileToGraphic::Statistics const & statistics);

static void show_metadata(FileToGraphic const & player);

static void raise_error(std::string const & output_filename, int code, const char * message, uint32_t verbose);

int is_encrypted_file(const char * input_filename, bool & infile_is_encrypted);


static const unsigned USE_ORIGINAL_COMPRESSION_ALGORITHM = 0xFFFFFFFF;
static const unsigned USE_ORIGINAL_COLOR_DEPTH           = 0xFFFFFFFF;


template<
    class CaptureMaker, class AddProgramOtion, class ParseFormat
  , class InitCryptoIni, class HasExtraCapture, class... ExtraArguments>
int app_recorder( int argc, char ** argv, const char * copyright_notice
                , AddProgramOtion add_prog_option, ParseFormat parse_format
                , InitCryptoIni init_crypto, HasExtraCapture has_extra_capture
                , ExtraArguments&&... extra_argument)
{
    openlog("redrec", LOG_CONS | LOG_PERROR, LOG_USER);

    std::string input_filename;
    std::string output_filename;

    uint32_t    verbose            = 0;
    uint32_t    clear              = 1; // default on
    uint32_t    begin_cap          = 0;
    uint32_t    end_cap            = 0;
    uint32_t    png_limit          = 10;
    uint32_t    png_interval       = 60;
    uint32_t    wrm_frame_interval = 100;
    uint32_t    wrm_break_interval = 86400;
    uint32_t    order_count        = 0;
    unsigned    zoom               = 100;
    bool        show_file_metadata = false;
    bool        show_statistics    = false;
    bool        auto_output_file   = false;
    bool        remove_input_file  = false;
    std::string wrm_compression_algorithm;  // output compression algorithm.
    std::string wrm_color_depth;
    std::string wrm_encryption;

    boost::program_options::options_description desc("Options");
    desc.add_options()
    ("help,h", "produce help message")
    ("version,v", "show software version")
    ("output-file,o", boost::program_options::value(&output_filename), "output base filename")
    ("input-file,i", boost::program_options::value(&input_filename), "input base filename")

    ("begin,b", boost::program_options::value<uint32_t>(&begin_cap), "begin capture time (in seconds), default=none")
    ("end,e", boost::program_options::value<uint32_t>(&end_cap), "end capture time (in seconds), default=none")
    ("count", boost::program_options::value<uint32_t>(&order_count), "Number of orders to execute before stopping, default=0 execute all orders")

    ("png_limit,l", boost::program_options::value<uint32_t>(&png_limit), "maximum number of png files to create (remove older), default=10, 0 will disable png capture")
    ("png_interval,n", boost::program_options::value<uint32_t>(&png_interval), "time interval between png captures, default=60 seconds")

    ("frameinterval,r", boost::program_options::value<uint32_t>(&wrm_frame_interval), "time between consecutive capture frames (in 100/th of seconds), default=100 one frame per second")

    ("breakinterval,k", boost::program_options::value<uint32_t>(&wrm_break_interval), "number of seconds between splitting wrm files in seconds(default, one wrm every day)")

    ("png,p", "enable png capture")
    ("wrm,w", "enable wrm capture")
    ;

    add_prog_option(desc.add_options());

    desc.add_options()
    ("clear", boost::program_options::value<uint32_t>(&clear), "clear old capture files with same prefix (default on)")
    ("verbose", boost::program_options::value<uint32_t>(&verbose), "more logs")
    ("zoom", boost::program_options::value<uint32_t>(&zoom), "scaling factor for png capture (default 100%)")
    ("meta,m", "show file metadata")
    ("statistics,s", "show statistics")

    //("compression,z", boost::program_options::value(&wrm_compression_algorithm), "wrm compression algorithm (default=original, none, gzip, snappy, lzma)")
    ("compression,z", boost::program_options::value(&wrm_compression_algorithm), "wrm compression algorithm (default=original, none, gzip, snappy)")
    ("color-depth,d", boost::program_options::value(&wrm_color_depth),           "wrm color depth (default=original, 16, 24)"                      )
    ("encryption,y",  boost::program_options::value(&wrm_encryption),            "wrm encryption (default=original, enable, disable)"              )

    ("auto-output-file",  "append suffix to input base filename to generate output base filename automatically")
    ("remove-input-file", "remove input file"                                                                  )
    ;


    boost::program_options::variables_map options;
    boost::program_options::store(
        boost::program_options::command_line_parser(argc, argv).options(desc).run(),
        options
    );
    boost::program_options::notify(options);

    if (options.count("help") > 0) {
        cout << copyright_notice;
        cout << "\n\nUsage: redrec [options]\n\n";
        cout << desc << endl;
        return 0;
    }

    if (options.count("version") > 0) {
        cout << copyright_notice << std::endl;
        return 0;
    }

    if (input_filename.empty()) {
        cerr << "Missing input filename : use -i filename\n\n";
        return -1;
    }

    show_file_metadata = (options.count("meta"             ) > 0);
    show_statistics    = (options.count("statistics"       ) > 0);
    auto_output_file   = (options.count("auto-output-file" ) > 0);
    remove_input_file  = (options.count("remove-input-file") > 0);

    if (!show_file_metadata && !show_statistics && !auto_output_file && output_filename.empty()) {
        cerr << "Missing output filename : use -o filename\n\n";
        return -1;
    }

    if (!output_filename.empty() && auto_output_file) {
        cerr << "Conflicting options : --output-file and --auto-output-file\n\n";
        return -1;
    }

    Inifile ini;
    ConfigurationLoader cfg_loader_full(ini, CFG_PATH "/" RDPPROXY_INI);

    if (options.count("compression") > 0) {
             if (0 == strcmp(wrm_compression_algorithm.c_str(), "none"       )) {
            ini.video.wrm_compression_algorithm = 0;
        }
        else if (0 == strcmp(wrm_compression_algorithm.c_str(), "gzip"       )) {
            ini.video.wrm_compression_algorithm = 1;
        }
        else  if (0 == strcmp(wrm_compression_algorithm.c_str(), "snappy"    )) {
            ini.video.wrm_compression_algorithm = 2;
        }
        else  if (0 == strcmp(wrm_compression_algorithm.c_str(), "original"  )) {
            ini.video.wrm_compression_algorithm = USE_ORIGINAL_COMPRESSION_ALGORITHM;
        }
        else {
            std::cerr << "Unknown wrm compression algorithm\n\n";
            return -1;
        }
    }
    else {
        ini.video.wrm_compression_algorithm = USE_ORIGINAL_COMPRESSION_ALGORITHM;
    }

    if (options.count("color-depth") > 0) {
             if (0 == strcmp(wrm_color_depth.c_str(), "16"       )) {
            ini.video.wrm_color_depth_selection_strategy = 16;
        }
        else if (0 == strcmp(wrm_color_depth.c_str(), "24"       )) {
            ini.video.wrm_color_depth_selection_strategy = 24;
        }
        else  if (0 == strcmp(wrm_color_depth.c_str(), "original")) {
            ini.video.wrm_color_depth_selection_strategy = USE_ORIGINAL_COLOR_DEPTH;
        }
        else {
            std::cerr << "Unknown wrm color depth\n\n";
            return -1;
        }
    }
    else {
        ini.video.wrm_color_depth_selection_strategy = USE_ORIGINAL_COLOR_DEPTH;
    }

    ini.video.png_limit      = png_limit;
    ini.video.png_interval   = png_interval;
    ini.video.frame_interval = wrm_frame_interval;
    ini.video.break_interval = wrm_break_interval;
    ini.video.capture_wrm    = (options.count("wrm") > 0);
    ini.video.capture_png    = (options.count("png") > 0);

    if (int status = parse_format(ini, options, output_filename)) {
        return status;
    }

    ini.video.rt_display.set(ini.video.capture_png ? 1 : 0);

    bool infile_is_encrypted;
    if (is_encrypted_file(input_filename.c_str(), infile_is_encrypted) == -1) {
        std::cerr << "Input file is absent.\n";
        return -1;
    }

    if (options.count("encryption") > 0) {
                if (0 == strcmp(wrm_encryption.c_str(), "enable")) {
            ini.globals.enable_file_encryption.set(true);
        }
        else if (0 == strcmp(wrm_encryption.c_str(), "disable")) {
            ini.globals.enable_file_encryption.set(false);
        }
        else  if (0 == strcmp(wrm_encryption.c_str(), "original")) {
            ini.globals.enable_file_encryption.set(infile_is_encrypted);
        }
        else {
            std::cerr << "Unknown wrm encryption parameter" << endl << endl;
            return -1;
        }
    }
    else {
        ini.globals.enable_file_encryption.set(infile_is_encrypted);
    }

    if (infile_is_encrypted || ini.globals.enable_file_encryption.get()) {
        if (int status = init_crypto(ini.crypto)) {
            return status;
        }
        OpenSSL_add_all_digests();
    }

    return recompress_or_record<CaptureMaker>(
        output_filename, input_filename, ini
      , remove_input_file, infile_is_encrypted, auto_output_file
      , begin_cap, end_cap, order_count, clear, zoom
      , show_file_metadata, show_statistics
      , has_extra_capture(ini)
      , verbose
      , std::forward<ExtraArguments>(extra_argument)...);
}


inline
int is_encrypted_file(const char * input_filename, bool & infile_is_encrypted)
{
    infile_is_encrypted = false;
    const int fd_test = open(input_filename, O_RDONLY);
    if (fd_test != -1) {
        uint32_t magic_test;
        TODO("Not portable code endianess, use byte array instead")
        ssize_t res_test = read(fd_test, &magic_test, sizeof(magic_test));
        if ((res_test == sizeof(magic_test)) &&
            (magic_test == WABCRYPTOFILE_MAGIC)) {
            infile_is_encrypted = true;
            cout << "Input file is encrypted." << endl;
        }
        close(fd_test);

        return 0;
    }

    return -1;
}


template<class CaptureMaker, class... ExtraArguments>
int recompress_or_record( std::string & output_filename, std::string & input_filename
                        , Inifile & ini, bool remove_input_file, bool infile_is_encrypted
                        , bool auto_output_file, uint32_t begin_cap, uint32_t end_cap
                        , uint32_t order_count, uint32_t clear, unsigned zoom
                        , bool show_file_metadata, bool show_statistics
                        , bool force_record, uint32_t verbose
                        , ExtraArguments&&... extra_argument)
{
    char infile_path     [1024] = "./"          ;   // default value, actual one should come from output_filename
    char infile_basename [1024] = "redrec_input";   // default value, actual one should come from output_filename
    char infile_extension[ 128] = ".mwrm"       ;

    canonical_path( input_filename.c_str()
                  , infile_path
                  , sizeof(infile_path)
                  , infile_basename
                  , sizeof(infile_basename)
                  , infile_extension
                  , sizeof(infile_extension)
                  , verbose
                  );
    if (verbose) {
        std::cout << "\nInput file path: " << infile_path << infile_basename << infile_extension << std::endl;
    }

    char infile_prefix[4096];
    snprintf(infile_prefix, sizeof(infile_prefix), "%s%s", infile_path, infile_basename);

    if (auto_output_file) {
        output_filename =  infile_path;
        output_filename += infile_basename;
        output_filename += "-redrec";
        output_filename += infile_extension;

        std::cout << "\nOutput file path (autogenerated): " << output_filename << std::endl;
    }

    TODO("before continuing to work with input file, check if it's mwrm or wrm and use right object in both cases")

    TODO("also check if it contains any wrm at all and at wich one we should start depending on input time")
    TODO("if start and stop time are outside wrm, users should also be warned")

    CryptoContext cctx;
    memset(&cctx, 0, sizeof(cctx));
    memcpy(cctx.crypto_key, ini.crypto.key0, sizeof(cctx.crypto_key));
    memcpy(cctx.hmac_key,   ini.crypto.key1, sizeof(cctx.hmac_key  ));

    timeval  begin_record = { 0, 0 };
    timeval  end_record   = { 0, 0 };
    unsigned file_count   = 0;
    try {
        if (infile_is_encrypted == false) {
            InMetaSequenceTransport in_wrm_trans_tmp(infile_prefix, infile_extension);
            file_count = get_file_count(in_wrm_trans_tmp, begin_cap, end_cap, begin_record, end_record);
        }
        else {
            CryptoInMetaSequenceTransport in_wrm_trans_tmp(&cctx, infile_prefix, infile_extension);
            file_count = get_file_count(in_wrm_trans_tmp, begin_cap, end_cap, begin_record, end_record);
        }
    }
    catch (const Error & e) {
        if (e.id == static_cast<unsigned>(ERR_TRANSPORT_NO_MORE_DATA)) {
            std::cerr << "Asked time not found in mwrm file\n";
        }
        else {
            std::cerr << "Exception code: " << e.id << std::endl;
        }
        const bool msg_with_error_id = false;
        raise_error(output_filename, e.id, e.errmsg(msg_with_error_id), verbose);
        return -1;
    };

    auto run = [&](Transport && trans, ExtraArguments&&... extra_argument) {
        timeval begin_capture = {0, 0};
        timeval end_capture = {0, 0};

        int result = -1;
        try {
            result = (
                force_record
             || ini.video.capture_png
             || ini.video.wrm_color_depth_selection_strategy != USE_ORIGINAL_COLOR_DEPTH
             || show_file_metadata
             || show_statistics
             || file_count > 1
             || order_count)
                ? ((verbose ? void(std::cout << "[A]"<< std::endl) : void())
                  , do_record<CaptureMaker>(
                      trans, begin_record, end_record, begin_capture, end_capture
                    , output_filename, ini, file_count, order_count, clear, zoom
                    , show_file_metadata, show_statistics, verbose
                    , std::forward<ExtraArguments>(extra_argument)...
                    )
                )
                : ((verbose ? void(std::cout << "[B]"<< std::endl) : void())
                  , do_recompress(cctx, trans, begin_record, output_filename, ini, verbose)
                )
            ;
        }
        catch (const Error & e) {
            const bool msg_with_error_id = false;
            raise_error(output_filename, e.id, e.errmsg(msg_with_error_id), verbose);
        }

        if (!result && remove_input_file) {
            if (infile_is_encrypted == false) {
                InMetaSequenceTransport in_wrm_trans_tmp(infile_prefix, infile_extension);
                remove_file( in_wrm_trans_tmp, ini.video.hash_path, infile_path, infile_basename, infile_extension
                           , infile_is_encrypted);
            }
            else {
                CryptoInMetaSequenceTransport in_wrm_trans_tmp(&cctx, infile_prefix, infile_extension);
                remove_file( in_wrm_trans_tmp, ini.video.hash_path, infile_path, infile_basename, infile_extension
                           , infile_is_encrypted);
            }
        }

        std::cout << std::endl;

        return result;
    };

    return infile_is_encrypted
        ? run( CryptoInMetaSequenceTransport(&cctx, infile_prefix, infile_extension)
             , std::forward<ExtraArguments>(extra_argument)...)
        : run( InMetaSequenceTransport(infile_prefix, infile_extension)
             , std::forward<ExtraArguments>(extra_argument)...);
}

template<typename InWrmTrans>
unsigned get_file_count( InWrmTrans & in_wrm_trans, uint32_t & begin_cap, uint32_t & end_cap, timeval & begin_record
                       , timeval & end_record) {
    in_wrm_trans.next();
    begin_record.tv_sec = in_wrm_trans.begin_chunk_time();
    TODO("a negative time should be a time relative to end of movie")
    REDOC("less than 1 year means we are given a time relatve to beginning of movie")
    if (begin_cap && (begin_cap < 31536000)) {  // less than 1 year, it is relative not absolute timestamp
        // begin_capture.tv_usec is 0
        begin_cap += in_wrm_trans.begin_chunk_time();
    }
    if (end_cap && (end_cap < 31536000)) { // less than 1 year, it is relative not absolute timestamp
        // begin_capture.tv_usec is 0
        end_cap += in_wrm_trans.begin_chunk_time();
    }
    while (begin_cap >= in_wrm_trans.end_chunk_time()) {
        in_wrm_trans.next();
    }
    unsigned result = in_wrm_trans.get_seqno();
    try {
        do {
            end_record.tv_sec = in_wrm_trans.end_chunk_time();
            in_wrm_trans.next();
        }
        while (true);
    }
    catch (const Error & e) {
        if (e.id != static_cast<unsigned>(ERR_TRANSPORT_NO_MORE_DATA)) {
            throw;
        }
    };
    return result;
}


template<typename InWrmTrans>
void remove_file( InWrmTrans & in_wrm_trans, const char * hash_path, const char * infile_path
                , const char * infile_basename, const char * infile_extension, bool is_encrypted) {
    std::vector<std::string> files;

    char infile_fullpath[2048];
    if (is_encrypted) {
        snprintf(infile_fullpath, sizeof(infile_fullpath), "%s%s%s", hash_path, infile_basename, infile_extension);
        files.push_back(infile_fullpath);
    }
    snprintf(infile_fullpath, sizeof(infile_fullpath), "%s%s%s", infile_path, infile_basename, infile_extension);
    files.push_back(infile_fullpath);

    try {
        do {
            in_wrm_trans.next();
            files.push_back(in_wrm_trans.path());
        }
        while (true);
    }
    catch (const Error & e) {
        if (e.id != ERR_TRANSPORT_NO_MORE_DATA) {
            throw;
        }
    };

    std::cout << endl;
    for (auto & s : iter(files.rbegin(), files.rend())) {
        unlink(s.c_str());
        std::cout << "Removed : " << s << endl;
    }
}

inline
static int do_recompress( CryptoContext & cctx, Transport & in_wrm_trans, const timeval begin_record
                        , std::string const & output_filename, Inifile & ini, uint32_t verbose) {
    FileToChunk player(&in_wrm_trans, 0);

    char outfile_path     [1024] = PNG_PATH "/"   ; // default value, actual one should come from output_filename
    char outfile_basename [1024] = "redrec_output"; // default value, actual one should come from output_filename
    char outfile_extension[1024] = ""             ; // extension is ignored for targets anyway

    canonical_path( output_filename.c_str()
                  , outfile_path
                  , sizeof(outfile_path)
                  , outfile_basename
                  , sizeof(outfile_basename)
                  , outfile_extension
                  , sizeof(outfile_extension)
                  , verbose
                  );

    if (verbose) {
        std::cout << "Output file path: " << outfile_path << outfile_basename << outfile_extension << '\n' << std::endl;
    }

    if (recursive_create_directory(outfile_path, S_IRWXU|S_IRGRP|S_IXGRP, ini.video.capture_groupid) != 0) {
        std::cerr << "Failed to create directory: \"" << outfile_path << "\"" << std::endl;
    }

    if (ini.video.wrm_compression_algorithm == USE_ORIGINAL_COMPRESSION_ALGORITHM) {
        ini.video.wrm_compression_algorithm = player.info_compression_algorithm;
    }

    int return_code = 0;
    try {
        auto run = [&](Transport && trans) {
            ChunkToFile recorder( &trans

                                , player.info_width
                                , player.info_height
                                , player.info_bpp
                                , player.info_cache_0_entries
                                , player.info_cache_0_size
                                , player.info_cache_1_entries
                                , player.info_cache_1_size
                                , player.info_cache_2_entries
                                , player.info_cache_2_size

                                , player.info_number_of_cache
                                , player.info_use_waiting_list

                                , player.info_cache_0_persistent
                                , player.info_cache_1_persistent
                                , player.info_cache_2_persistent

                                , player.info_cache_3_entries
                                , player.info_cache_3_size
                                , player.info_cache_3_persistent
                                , player.info_cache_4_entries
                                , player.info_cache_4_size
                                , player.info_cache_4_persistent

                                , ini);

            player.add_consumer(&recorder);

            player.play();
        };

        if (ini.globals.enable_file_encryption.get()) {
            run(CryptoOutMetaSequenceTransport( &cctx, outfile_path, ini.video.hash_path, outfile_basename
                                              , begin_record, player.info_width, player.info_height
                                              , ini.video.capture_groupid));
        }
        else {
            run(OutMetaSequenceTransport( outfile_path, outfile_basename, begin_record
                                        , player.info_width, player.info_height, ini.video.capture_groupid));
        }
    }
    catch (...) {
        return_code = -1;
    }

    return return_code;
}   // do_recompress

inline
static void show_statistics(FileToGraphic::Statistics const & statistics) {
    std::cout
    << "\nDstBlt                : " << statistics.DstBlt
    << "\nMultiDstBlt           : " << statistics.MultiDstBlt
    << "\nPatBlt                : " << statistics.PatBlt
    << "\nMultiPatBlt           : " << statistics.MultiPatBlt
    << "\nOpaqueRect            : " << statistics.OpaqueRect
    << "\nMultiOpaqueRect       : " << statistics.MultiOpaqueRect
    << "\nScrBlt                : " << statistics.ScrBlt
    << "\nMultiScrBlt           : " << statistics.MultiScrBlt
    << "\nMemBlt                : " << statistics.MemBlt
    << "\nMem3Blt               : " << statistics.Mem3Blt
    << "\nLineTo                : " << statistics.LineTo
    << "\nGlyphIndex            : " << statistics.GlyphIndex
    << "\nPolyline              : " << statistics.Polyline

    << "\nCacheBitmap           : " << statistics.CacheBitmap
    << "\nCacheColorTable       : " << statistics.CacheColorTable
    << "\nCacheGlyph            : " << statistics.CacheGlyph

    << "\nFrameMarker           : " << statistics.FrameMarker

    << "\nBitmapUpdate          : " << statistics.BitmapUpdate

    << "\nCachePointer          : " << statistics.CachePointer
    << "\nPointerIndex          : " << statistics.PointerIndex

    << "\ngraphics_update_chunk : " << statistics.graphics_update_chunk
    << "\nbitmap_update_chunk   : " << statistics.bitmap_update_chunk
    << "\ntimestamp_chunk       : " << statistics.timestamp_chunk
    << std::endl;
}

inline
static void show_metadata(FileToGraphic const & player) {
    std::cout
    << "\nWRM file version      : " << player.info_version
    << "\nWidth                 : " << player.info_width
    << "\nHeight                : " << player.info_height
    << "\nBpp                   : " << player.info_bpp
    << "\nCache 0 entries       : " << player.info_cache_0_entries
    << "\nCache 0 size          : " << player.info_cache_0_size
    << "\nCache 1 entries       : " << player.info_cache_1_entries
    << "\nCache 1 size          : " << player.info_cache_1_size
    << "\nCache 2 entries       : " << player.info_cache_2_entries
    << "\nCache 2 size          : " << player.info_cache_2_size
    << '\n';

    if (player.info_version > 3) {
        //cout << "Cache 3 entries       : " << player.info_cache_3_entries                         << endl;
        //cout << "Cache 3 size          : " << player.info_cache_3_size                            << endl;
        //cout << "Cache 4 entries       : " << player.info_cache_4_entries                         << endl;
        //cout << "Cache 4 size          : " << player.info_cache_4_size                            << endl;
        std::cout << "Compression algorithm : " << static_cast<int>(player.info_compression_algorithm) << '\n';
    }
    std::cout.flush();
}

inline
static void raise_error(std::string const & output_filename, int code, const char * message, uint32_t verbose) {
    if (!output_filename.length()) {
        return;
    }

    char outfile_pid[32];
    snprintf(outfile_pid, sizeof(outfile_pid), "%06u", getpid());

    char outfile_path     [1024] = "./"           ; // default value, actual one should come from output_filename
    char outfile_basename [1024] = "redrec_output"; // default value actual one should come from output_filename
    char outfile_extension[1024] = ""             ; // extension is ignored for targets anyway

    canonical_path( output_filename.c_str()
                  , outfile_path
                  , sizeof(outfile_path)
                  , outfile_basename
                  , sizeof(outfile_basename)
                  , outfile_extension
                  , sizeof(outfile_extension)
                  , verbose
                  );

    char progress_filename[4096];
    snprintf( progress_filename, sizeof(progress_filename), "%s%s-%s.pgs"
            , outfile_path, outfile_basename, outfile_pid);

    UpdateProgressData update_progress_data(progress_filename, 0, 0, 0, 0);

    update_progress_data.raise_error(code, message);
}

template<class CaptureMaker, class... ExtraArguments>
static int do_record( Transport & in_wrm_trans, const timeval begin_record, const timeval end_record
                    , const timeval begin_capture, const timeval end_capture, std::string const & output_filename
                    , Inifile & ini, unsigned file_count, uint32_t order_count, uint32_t clear, unsigned zoom
                    , bool show_file_metadata, bool show_statistics, uint32_t verbose
                    , ExtraArguments && ... extra_argument) {
    for (unsigned i = 1; i < file_count ; i++) {
        in_wrm_trans.next();
    }

    FileToGraphic player(&in_wrm_trans, begin_capture, end_capture, false, verbose);

    if (show_file_metadata) {
        show_metadata(player);
        std::cout << "Duration (in seconds) : " << (end_record.tv_sec - begin_record.tv_sec + 1) << std::endl;
        if (!show_statistics && !output_filename.length()) {
            return 0;
        }
    }

    player.max_order_count = order_count;

    int return_code = 0;

    if (output_filename.length()) {
        char outfile_pid[32];
        snprintf(outfile_pid, sizeof(outfile_pid), "%06u", getpid());

        char outfile_path     [1024] = "./"           ; // default value, actual one should come from output_filename
        char outfile_basename [1024] = "redrec_output"; // default value actual one should come from output_filename
        char outfile_extension[1024] = ""             ; // extension is ignored for targets anyway

        canonical_path( output_filename.c_str()
                      , outfile_path
                      , sizeof(outfile_path)
                      , outfile_basename
                      , sizeof(outfile_basename)
                      , outfile_extension
                      , sizeof(outfile_extension)
                      , verbose
                      );

        if (verbose) {
            std::cout << "Output file path: " << outfile_path << outfile_basename << '-' << outfile_pid << outfile_extension <<
                '\n' << endl;
        }

        if (clear == 1) {
            clear_files_flv_meta_png(outfile_path, outfile_basename);
        }

        if (ini.video.wrm_compression_algorithm == USE_ORIGINAL_COMPRESSION_ALGORITHM) {
            ini.video.wrm_compression_algorithm = player.info_compression_algorithm;
        }

        if (ini.video.wrm_color_depth_selection_strategy == USE_ORIGINAL_COLOR_DEPTH) {
            ini.video.wrm_color_depth_selection_strategy = player.info_bpp;
        }

        CaptureMaker capmake( ((player.record_now.tv_sec > begin_capture.tv_sec) ? player.record_now : begin_capture)
                            , player.screen_rect.cx, player.screen_rect.cy
                            , player.info_bpp, outfile_path, outfile_basename, outfile_extension
                            , ini, clear, verbose, std::forward<ExtraArguments>(extra_argument)...);
        auto & capture = capmake.capture;

        if (capture.capture_png) {
            capture.psc->zoom(zoom);
        }
        player.add_consumer(&capture, &capture);

        char progress_filename[4096];
        snprintf( progress_filename, sizeof(progress_filename), "%s%s-%s.pgs"
                , outfile_path, outfile_basename, outfile_pid);

        UpdateProgressData update_progress_data(
            progress_filename, begin_record.tv_sec, end_record.tv_sec, begin_capture.tv_sec, end_capture.tv_sec
        );

        if (update_progress_data.is_valid()) {
            try {
                player.play(std::ref(update_progress_data));
            }
            catch (Error const & e) {
                const bool msg_with_error_id = false;
                update_progress_data.raise_error(e.id, e.errmsg(msg_with_error_id));

                return_code = -1;
            }
            catch (...) {
                update_progress_data.raise_error(65536, "Unknown error");

                return_code = -1;
            }
        }
        else {
            return_code = -1;
        }
    }
    else {
        try {
            player.play();
        }
        catch (Error const &) {
            return_code = -1;
        }
    }

    if (show_statistics && return_code == 0) {
      ::show_statistics(player.statistics);
    }

    return return_code;
}   // do_record

#endif
