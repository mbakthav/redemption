/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Product name: redemption, a FLOSS RDP proxy
   Copyright (C) Wallix 2012
   Author(s): Christophe Grosjean

   Unit test to conversion of RDP drawing orders to PNG images
*/

#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestNativeCapture
#include <boost/test/auto_unit_test.hpp>

#undef SHARE_PATH
#define SHARE_PATH FIXTURES_PATH

#define LOGNULL
//#define LOGPRINT

#include "out_filename_sequence_transport.hpp"
#include "nativecapture.hpp"
#include "RDP/caches/bmpcache.hpp"
#include "fileutils.hpp"


BOOST_AUTO_TEST_CASE(TestSimpleBreakpoint)
{
    Rect scr(0, 0, 800, 600);
    const int groupid = 0;
    OutFilenameSequenceTransport trans(FilenameGenerator::PATH_FILE_PID_COUNT_EXTENSION, "./", "test", ".wrm", groupid);

    struct timeval now;
    now.tv_sec = 1000;
    now.tv_usec = 0;

    BmpCache bmp_cache(BmpCache::Recorder, 24, 3, false,
                       BmpCache::CacheOption(600, 768, false),
                       BmpCache::CacheOption(300, 3072, false),
                       BmpCache::CacheOption(262, 12288, false));
    GlyphCache gly_cache;
    PointerCache ptr_cache;
    Inifile ini;
    RDPDrawable drawable(800, 600, 24);
    NativeCapture consumer(now, trans, 800, 600, 24, bmp_cache, gly_cache, ptr_cache, drawable, ini);

    drawable.show_mouse_cursor(false);

    ini.video.frame_interval = 100; // one snapshot by second
    ini.video.break_interval = 5;   // one WRM file every 5 seconds
    consumer.update_config(ini);

    bool ignore_frame_in_timeval = false;

    consumer.draw(RDPOpaqueRect(scr, RED), scr);
    consumer.snapshot(now, 10, 10, ignore_frame_in_timeval);
    now.tv_sec += 6;
    consumer.snapshot(now, 10, 10, ignore_frame_in_timeval);
    trans.disconnect();

    const char * filename;

    filename = trans.seqgen()->get(0);
    BOOST_CHECK_EQUAL(1560, ::filesize(filename));
    ::unlink(filename);
    filename = trans.seqgen()->get(1);
    BOOST_CHECK_EQUAL(3365, ::filesize(filename));
    ::unlink(filename);
}

