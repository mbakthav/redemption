/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  Product name: redemption, a FLOSS RDP proxy
  Copyright (C) Wallix 2012-2013
  Author(s): Christophe Grosjean, Raphael Zhou, Meng Tan

  Unit test to config.cpp file
  Using lib boost functions, some tests need to be added
*/

#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestConfig
#include <boost/test/auto_unit_test.hpp>

#undef SHARE_PATH
#define SHARE_PATH FIXTURES_PATH

#define LOGNULL
//#define LOGPRINT

#include "config.hpp"
#include <sstream>

BOOST_AUTO_TEST_CASE(TestConfigFromFile)
{
    // test we can read from a file (and not only from a stream)
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini, "/rdpproxy.ini");
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(true,                             ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)), ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());
    BOOST_CHECK_EQUAL(0,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("0.0.0.0",                        ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("inquisition",                    ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL(PNG_PATH,                         ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL(WRM_PATH,                         ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key0,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key1,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(0x8,                              ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0x80,                             ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(true,                             ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL("*",                              ini.mod_rdp.allow_channels);
    BOOST_CHECK_EQUAL("",                               ini.mod_rdp.deny_channels);

    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.clipboard_up.get());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.clipboard_down.get());
    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());
    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL("",                               ini.context.movie.c_str());

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());

    BOOST_CHECK_EQUAL(false,                            ini.context.opt_bpp.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.opt_height.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.opt_width.is_asked());

    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());

    BOOST_CHECK_EQUAL("",                               ini.context.auth_error_message.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.context.selector.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.selector_current_page.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.selector_device_filter.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.selector_group_filter.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.selector_lines_per_page.is_asked());

    BOOST_CHECK_EQUAL(false,                            ini.context.selector.get());
    BOOST_CHECK_EQUAL(1,                                ini.context.selector_current_page.get());
    BOOST_CHECK_EQUAL("",                               ini.context.selector_device_filter.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.context.selector_group_filter.get_cstr());
    BOOST_CHECK_EQUAL(0,                                ini.context.selector_lines_per_page.get());
    BOOST_CHECK_EQUAL(1,                                ini.context.selector_number_of_pages.get());

    BOOST_CHECK_EQUAL(true,                             ini.globals.target_device.is_asked());
    //BOOST_CHECK_EQUAL(true,                             ini.globals.state_target_device.asked);
    BOOST_CHECK_EQUAL(true,                             ini.context.target_password.is_asked());
    BOOST_CHECK_EQUAL(true,                             ini.context.target_port.is_asked());
    BOOST_CHECK_EQUAL(true,                             ini.context.target_protocol.is_asked());
    BOOST_CHECK_EQUAL(true,                             ini.globals.target_user.is_asked());

    BOOST_CHECK_EQUAL("",                               ini.context.target_password.get_cstr());
    BOOST_CHECK_EQUAL(3389,                             ini.context.target_port.get());
    BOOST_CHECK_EQUAL("RDP",                            ini.context.target_protocol.get_cstr());

    BOOST_CHECK_EQUAL(false,                            ini.globals.host.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.globals.target.is_asked());

    BOOST_CHECK_EQUAL(true,                             ini.globals.auth_user.is_asked());
    BOOST_CHECK_EQUAL(true,                             ini.context.password.is_asked());


    BOOST_CHECK_EQUAL("",                               ini.context.password.get_cstr());

    BOOST_CHECK_EQUAL(false,                            ini.context.authchannel_target.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.authchannel_result.is_asked());

    BOOST_CHECK_EQUAL("",                               ini.context.authchannel_answer.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.context.authchannel_result.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.context.authchannel_target.get_cstr());

    BOOST_CHECK_EQUAL(false,                            ini.context.accept_message.is_asked());
    BOOST_CHECK_EQUAL(false,                            ini.context.display_message.is_asked());

    BOOST_CHECK_EQUAL("",                               ini.context.message.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.context.accept_message.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.context.display_message.get_cstr());

    // BOOST_CHECK_EQUAL("Connection refused by authentifier.",
    //                   ini.context.rejected.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.context.rejected.get_cstr());

    BOOST_CHECK_EQUAL(false,                            ini.context.authenticated.get());

    BOOST_CHECK_EQUAL(false,                            ini.context.keepalive.is_asked());

    BOOST_CHECK_EQUAL(false,                            ini.context.keepalive.get());

    BOOST_CHECK_EQUAL("",                               ini.context.session_id.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.context.end_date_cnx.get());
    BOOST_CHECK_EQUAL("",                               ini.context.end_time.get_cstr());

    BOOST_CHECK_EQUAL("allow",                          ini.context.mode_console.get_cstr());
    BOOST_CHECK_EQUAL(-3600,                            ini.context.timezone.get());

    BOOST_CHECK_EQUAL("",                               ini.context.real_target_device.get_cstr());

    BOOST_CHECK_EQUAL(false,                            ini.context.authentication_challenge.get());
}

BOOST_AUTO_TEST_CASE(TestConfigDefaultEmpty)
{
    // default config
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini);
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(true,                             ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(0,                                ini.video.disable_keyboard_log.get());

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("0.0.0.0",                        ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("inquisition",                    ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL(PNG_PATH,                         ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL(WRM_PATH,                         ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key0,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key1,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(0x8,                              ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0x80,                             ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(true,                             ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL("*",                              ini.mod_rdp.allow_channels);
    BOOST_CHECK_EQUAL("",                               ini.mod_rdp.deny_channels);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.clipboard_up.get());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.clipboard_down.get());

    BOOST_CHECK_EQUAL("OK",                             ini.context_get_value(AUTHID_TRANS_BUTTON_OK));
    BOOST_CHECK_EQUAL("Cancel",                         ini.context_get_value(AUTHID_TRANS_BUTTON_CANCEL));
    BOOST_CHECK_EQUAL("Help",                           ini.context_get_value(AUTHID_TRANS_BUTTON_HELP));
    BOOST_CHECK_EQUAL("Close",                          ini.context_get_value(AUTHID_TRANS_BUTTON_CLOSE));
    BOOST_CHECK_EQUAL("Refused",                        ini.context_get_value(AUTHID_TRANS_BUTTON_REFUSED));
    BOOST_CHECK_EQUAL("Login",                          ini.context_get_value(AUTHID_TRANS_LOGIN));
    BOOST_CHECK_EQUAL("Username",                       ini.context_get_value(AUTHID_TRANS_USERNAME));
    BOOST_CHECK_EQUAL("Password",                       ini.context_get_value(AUTHID_TRANS_PASSWORD));
    BOOST_CHECK_EQUAL("Target",                         ini.context_get_value(AUTHID_TRANS_TARGET));
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.context_get_value(AUTHID_TRANS_DIAGNOSTIC));
    BOOST_CHECK_EQUAL("Connection closed",              ini.context_get_value(AUTHID_TRANS_CONNECTION_CLOSED));

    BOOST_CHECK_EQUAL("",                               ini.context.movie.c_str());

    BOOST_CHECK_EQUAL("40000",                          ini.context_get_value(AUTHID_OPT_BITRATE));
    BOOST_CHECK_EQUAL("5",                              ini.context_get_value(AUTHID_OPT_FRAMERATE));
    BOOST_CHECK_EQUAL("15",                             ini.context_get_value(AUTHID_OPT_QSCALE));

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_OPT_BPP));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_OPT_HEIGHT));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_OPT_WIDTH));

    BOOST_CHECK_EQUAL("800",                            ini.context_get_value(AUTHID_OPT_WIDTH));
    BOOST_CHECK_EQUAL("600",                            ini.context_get_value(AUTHID_OPT_HEIGHT));
    BOOST_CHECK_EQUAL("24",                             ini.context_get_value(AUTHID_OPT_BPP));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_AUTH_ERROR_MESSAGE));

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_CURRENT_PAGE));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_DEVICE_FILTER));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_GROUP_FILTER));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_LINES_PER_PAGE));

    BOOST_CHECK_EQUAL("False",                          ini.context_get_value(AUTHID_SELECTOR));
    BOOST_CHECK_EQUAL("1",                              ini.context_get_value(AUTHID_SELECTOR_CURRENT_PAGE));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_SELECTOR_DEVICE_FILTER));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_SELECTOR_GROUP_FILTER));
    BOOST_CHECK_EQUAL("0",                              ini.context_get_value(AUTHID_SELECTOR_LINES_PER_PAGE));
    BOOST_CHECK_EQUAL("1",                              ini.context_get_value(AUTHID_SELECTOR_NUMBER_OF_PAGES));

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_TARGET_DEVICE));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_TARGET_PASSWORD));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_TARGET_PORT));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_TARGET_PROTOCOL));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_TARGET_USER));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_TARGET_DEVICE));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_TARGET_PASSWORD));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_TARGET_PORT));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_TARGET_PROTOCOL));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_TARGET_USER));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_TARGET_APPLICATION));

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_HOST));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_TARGET));

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_AUTH_USER));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_PASSWORD));


    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_AUTH_USER));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_PASSWORD));

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_AUTHCHANNEL_TARGET));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_AUTHCHANNEL_RESULT));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_AUTHCHANNEL_ANSWER));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_AUTHCHANNEL_RESULT));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_AUTHCHANNEL_TARGET));

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_ACCEPT_MESSAGE));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_DISPLAY_MESSAGE));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_PATTERN_KILL));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_PATTERN_NOTIFY));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_MESSAGE));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_ACCEPT_MESSAGE));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_DISPLAY_MESSAGE));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_REJECTED));

    BOOST_CHECK_EQUAL("False",                          ini.context_get_value(AUTHID_AUTHENTICATED));

    BOOST_CHECK_EQUAL(false,                            ini.context_get_bool(AUTHID_AUTHENTICATED));


    BOOST_CHECK_EQUAL(false,                             ini.context_is_asked(AUTHID_KEEPALIVE));

    BOOST_CHECK_EQUAL("False",                          ini.context_get_value(AUTHID_KEEPALIVE));


    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_SESSION_ID));


    BOOST_CHECK_EQUAL("0",                              ini.context_get_value(AUTHID_END_DATE_CNX));
    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_END_TIME));

    BOOST_CHECK_EQUAL("allow",                          ini.context_get_value(AUTHID_MODE_CONSOLE));
    BOOST_CHECK_EQUAL("-3600",                          ini.context_get_value(AUTHID_TIMEZONE));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_REAL_TARGET_DEVICE));

    BOOST_CHECK_EQUAL("",                               ini.context_get_value(AUTHID_AUTHENTICATION_CHALLENGE));
}

BOOST_AUTO_TEST_CASE(TestConfigDefault)
{
    // test we can read a config file with a global section
    std::stringstream   oss;
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini, oss);
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(true,                             ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(0,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("0.0.0.0",                        ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("inquisition",                    ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL(PNG_PATH,                         ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL(WRM_PATH,                         ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key0,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key1,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(0x8,                              ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0x80,                             ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(true,                             ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL("*",                              ini.mod_rdp.allow_channels);
    BOOST_CHECK_EQUAL("",                               ini.mod_rdp.deny_channels);

    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.clipboard_up.get());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.clipboard_down.get());
    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());
}

BOOST_AUTO_TEST_CASE(TestConfig1)
{
    // test we can read a config file with a global section
    std::stringstream oss(
                          "[globals]\n"
                          "movie=yes\n"
                          "bitmap_cache=yes\n"
                          "glyph_cache=yes\n"
                          "port=3390\n"
                          "encryptionLevel=low\n"
                          "enable_file_encryption=yes\n"
                          "listen_address=192.168.1.1\n"
                          "enable_ip_transparent=yes\n"
                          "certificate_password=redemption\n"
                          "png_path=/var/tmp/wab/recorded/rdp\n"
                          "wrm_path=/var/wab/recorded/rdp\n"
                          "alternate_shell=C:\\WINDOWS\\NOTEPAD.EXE\n"
                          "shell_working_directory=C:\\WINDOWS\\\n"
                          "enable_bitmap_update=true\n"
                          "persistent_path=/var/tmp/wab/persistent/rdp\n"
                          "enable_close_box=false\n"
                          "enable_osd=false\n"
                          "enable_osd_display_remote_target=false\n"
                          "\n"
                          "[client]\n"
                          "ignore_logon_password=yes\n"
                          "performance_flags_default=0x00000007\n"
                          "performance_flags_force_present=0x1\n"
                          "performance_flags_force_not_present=0x0\n"
                          "tls_fallback_legacy=yes\n"
                          "tls_support=no\n"
                          "rdp_compression=1\n"
                          "disable_tsk_switch_shortcuts=yes\n"
                          "max_color_depth=0\n"
                          "persistent_disk_bitmap_cache=yes\n"
                          "cache_waiting_list=no\n"
                          "persist_bitmap_cache_on_disk=yes\n"
                          "bitmap_compression=true\n"
                          "\n"
                          "[mod_rdp]\n"
                          "disconnect_on_logon_user_change=yes\n"
                          "enable_nla=yes\n"
                          "open_session_timeout=45\n"
                          "certificate_change_action=1\n"
                          "extra_orders=22\n"
                          "persistent_disk_bitmap_cache=false\n"
                          "cache_waiting_list=no\n"
                          "persist_bitmap_cache_on_disk=true\n"
                          "allow_channels=audin\n"
                          "deny_channels=*\n"
                          "\n"
                          "[mod_vnc]\n"
                          "clipboard_up=yes\n"
                          "encodings=16,2,0,1,-239\n"
                          "allow_authentification_retries=yes\n"
                          "\n"
                          "[video]\n"
                          "hash_path=/mnt/wab/hash\n"
                          "record_path=/mnt/wab/recorded/rdp\n"
                          "record_tmp_path=/mnt/tmp/wab/recorded/rdp\n"
                          "ocr_interval=50\n"
                          "ocr_on_title_bar_only=yes\n"
                          "ocr_max_unrecog_char_rate=50\n"
                          "disable_keyboard_log=1\n"
                          "\n"
                          "[crypto]\n"
                          "key0=00112233445566778899AABBCCDDEEFF00112233445566778899AABBCCDDEEFF\n"
                          "key1=FFEEDDCCBBAA99887766554433221100FFEEDDCCBBAA99887766554433221100\n"
                          "\n"
                          "[debug]\n"
                          "password=1\n"
                          "compression=256\n"
                          "cache=128\n"
                          "[translation]\n"
                          "button_cancel=Annuler\n"
                          "\n"
                          );

    Inifile             ini;
    ConfigurationLoader cfg_loader(ini, oss);

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(true,                             ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(true,                             ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3390,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL("/var/tmp/wab/persistent/rdp/",   ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(50,                               ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(true,                             ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(50,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL("/mnt/wab/hash/",                 ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL("/mnt/wab/recorded/rdp/",         ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL("/mnt/tmp/wab/recorded/rdp/",     ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(1,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(true,                             ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("192.168.1.1",                    ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("redemption",                     ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL("/var/tmp/wab/recorded/rdp",      ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL("/var/wab/recorded/rdp",          ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("C:\\WINDOWS\\NOTEPAD.EXE",       ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("C:\\WINDOWS\\",                  ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key0,
                                                               "\x00\x11\x22\x33\x44\x55\x66\x77"
                                                               "\x88\x99\xAA\xBB\xCC\xDD\xEE\xFF"
                                                               "\x00\x11\x22\x33\x44\x55\x66\x77"
                                                               "\x88\x99\xAA\xBB\xCC\xDD\xEE\xFF", 32));
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key1,
                                                               "\xFF\xEE\xDD\xCC\xBB\xAA\x99\x88"
                                                               "\x77\x66\x55\x44\x33\x22\x11\x00"
                                                               "\xFF\xEE\xDD\xCC\xBB\xAA\x99\x88"
                                                               "\x77\x66\x55\x44\x33\x22\x11\x00", 32));

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(1,                                ini.debug.password);
    BOOST_CHECK_EQUAL(256,                              ini.debug.compression);
    BOOST_CHECK_EQUAL(128,                              ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(true,                             ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(7,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(1,                                ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(false,                            ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(1,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(true,                             ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(true,                             ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(true,                             ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(true,                             ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(45,                               ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(1,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("22",                             ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL("audin",                          ini.mod_rdp.allow_channels);
    BOOST_CHECK_EQUAL("*",                              ini.mod_rdp.deny_channels);

    BOOST_CHECK_EQUAL(true,                             ini.mod_vnc.clipboard_up.get());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.clipboard_down.get());
    BOOST_CHECK_EQUAL("16,2,0,1,-239",                  ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Annuler",                        ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());
}

BOOST_AUTO_TEST_CASE(TestConfig1bis)
{
    // test we can read a config file with a global section
    // alternative ways to say yes in file, other values
    std::stringstream oss(
                          "[globals]\n"
                          "bitmap_cache=true\n"
                          "encryptionLevel=medium\n"
                          "enable_file_encryption=no\n"
                          "listen_address=0.0.0.0\n"
                          "enable_ip_transparent=no\n"
                          "certificate_password=\n"
                          "png_path=/var/tmp/wab/recorded/rdp\n"
                          "wrm_path=/var/wab/recorded/rdp\n"
                          "alternate_shell=\n"
                          "shell_working_directory=\n"
                          "enable_bitmap_update=no\n"
                          "[client]\n"
                          "performance_flags_default=7\n"
                          "performance_flags_force_present=1\n"
                          "performance_flags_force_not_present=0\n"
                          "tls_support=yes\n"
                          "rdp_compression=0\n"
                          "max_color_depth=8\n"
                          "persistent_disk_bitmap_cache=no\n"
                          "cache_waiting_list=yes\n"
                          "bitmap_compression=on\n"
                          "[translation]\n"
                          "connection_closed=Connexion fermée\n"
                          "[mod_rdp]\n"
                          "rdp_compression=2\n"
                          "disconnect_on_logon_user_change=no\n"
                          "enable_nla=no\n"
                          "open_session_timeout=30\n"
                          "certificate_change_action=0\n"
                          "persistent_disk_bitmap_cache=yes\n"
                          "cache_waiting_list=no\n"
                          "persist_bitmap_cache_on_disk=no\n"
                          "[mod_replay]\n"
                          "on_end_of_data=1\n"
                          "[video]\n"
                          "hash_path=/mnt/wab/hash/\n"
                          "record_path=/mnt/wab/recorded/rdp/\n"
                          "record_tmp_path=/mnt/tmp/wab/recorded/rdp/\n"
                          "disable_keyboard_log=2\n"
                          "\n"
                          "[crypto]\n"
                          "key0=00112233445566778899AABBCCDDEEFF\n"
                          "key1=FFEEDDCCBBAA99887766554433221100\n"
                          "\n"
                          );

    Inifile             ini;
    ConfigurationLoader cfg_loader(ini, oss);
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(true,                             ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(1,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);
    BOOST_CHECK_EQUAL("/mnt/wab/hash/",                 ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL("/mnt/wab/recorded/rdp/",         ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL("/mnt/tmp/wab/recorded/rdp/",     ini.video.record_tmp_path.c_str());
    BOOST_CHECK_EQUAL(2,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(true,                             ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("0.0.0.0",                        ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("",                               ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL("/var/tmp/wab/recorded/rdp",      ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL("/var/wab/recorded/rdp",          ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key0,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.crypto.key1,
                                                               "\x00\x01\x02\x03\x04\x05\x06\x07"
                                                               "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                                                               "\x10\x11\x12\x13\x14\x15\x16\x17"
                                                               "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32));

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(7,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(1,                                ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(0,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(8,                                ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(true,                             ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(2,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(30,                               ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connexion fermée",               ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(1,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());
}

BOOST_AUTO_TEST_CASE(TestConfig2)
{
    // test we can read a config file with a global section, other values
    std::stringstream oss(
                          "[globals]\n"
                          "bitmap_cache=no\n"
                          "glyph_cache=no\n"
                          "encryptionLevel=high\n"
                          "enable_file_encryption=true\n"
                          "listen_address=127.0.0.1\n"
                          "certificate_password=rdpproxy\n"
                          "enable_ip_transparent=true\n"
                          "png_path=/var/tmp/wab/recorded/rdp\n"
                          "wrm_path=/var/wab/recorded/rdp\n"
                          "alternate_shell=C:\\Program Files\\Microsoft Visual Studio\\Common\\MSDev98\\Bin\\MSDEV.EXE\n"
                          "shell_working_directory=\n"
                          "[client]\n"
                          "tls_support=yes\n"
                          "performance_flags_default=07\n"
                          "performance_flags_force_present=1\n"
                          "performance_flags_force_not_present=0x\n"
                          "max_color_depth=24\n"
                          "persistent_disk_bitmap_cache=yes\n"
                          "cache_waiting_list=no\n"
                          "persist_bitmap_cache_on_disk=no\n"
                          "bitmap_compression=false\n"
                          "[mod_rdp]\n"
                          "rdp_compression=0\n"
                          "[mod_replay]\n"
                          "on_end_of_data=0\n"
                          "[video]\n"
                          "disable_keyboard_log=4\n"
                          "wrm_color_depth_selection_strategy=1\n"
                          "wrm_compression_algorithm=1\n"
                          "\n"
                          );

    Inifile             ini;
    ConfigurationLoader cfg_loader(ini, oss);
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(false,                            ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(2,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(4,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(true,                             ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(1,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(1,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("rdpproxy",                       ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL("/var/tmp/wab/recorded/rdp",      ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL("/var/wab/recorded/rdp",          ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("C:\\Program Files\\Microsoft Visual Studio\\Common\\MSDev98\\Bin\\MSDEV.EXE",
                      ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(7,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(1,                                ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(true,                             ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(false,                            ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());
}

BOOST_AUTO_TEST_CASE(TestConfig3)
{
    // test we can read a config file with a global section, other values
    std::stringstream oss(
                          " [ globals ] \n"
                          " bitmap_cache\t= no \n"
                          " glyph_cache = no \n"
                          "encryptionLevel=high\n"
                          "enable_file_encryption=true\n"
                          "listen_address=127.0.0.1\n"
                          "certificate_password=rdpproxy RDP\n"
                          "enable_ip_transparent=true\n"
                          "png_path=/var/tmp/wab/recorded/rdp\n"
                          "wrm_path=/var/wab/recorded/rdp\n"
                          "alternate_shell=C:\\Program Files\\Microsoft Visual Studio\\Common\\MSDev98\\Bin\\MSDEV.EXE   \n"
                          "shell_working_directory=\n"
                          "[client]\t\n"
                          "tls_support=yes\n"
                          "performance_flags_default=07\n"
                          "performance_flags_force_present=1\n"
                          "performance_flags_force_not_present=0x\n"
                          "max_color_depth=24\n"
                          "persistent_disk_bitmap_cache=yes\n"
                          "cache_waiting_list=no\n"
                          "persist_bitmap_cache_on_disk=no\n"
                          "bitmap_compression=false\n"
                          "\t[mod_rdp]\n"
                          "rdp_compression=0\n"
                          "[mod_replay]\n"
                          "on_end_of_data=0\n"
                          "[video]\n"
                          "disable_keyboard_log=4\n"
                          "wrm_color_depth_selection_strategy=1\n"
                          "wrm_compression_algorithm=1\n"
                          "\n"
                          );

    Inifile             ini;

    ini.globals.shell_working_directory.set_from_cstr("C:\\");

    ConfigurationLoader cfg_loader(ini, oss);
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(false,                            ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(2,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(4,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(true,                             ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(1,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(1,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("rdpproxy RDP",                   ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL("/var/tmp/wab/recorded/rdp",      ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL("/var/wab/recorded/rdp",          ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("C:\\Program Files\\Microsoft Visual Studio\\Common\\MSDev98\\Bin\\MSDEV.EXE",
                      ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(7,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(1,                                ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(true,                             ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(false,                            ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());
}

BOOST_AUTO_TEST_CASE(TestMultiple)
{
    // test we can read a config file with a global section
    std::stringstream oss(
                          "[globals]\n"
                          "bitmap_cache=no\n"
                          "port=3390\n"
                          "encryptionLevel=low\n"
                          "enable_file_encryption=False\n"
                          "listen_address=0.0.0.0\n"
                          "certificate_password=redemption\n"
                          "enable_ip_transparent=False\n"
                          "shell_working_directory=%HOMEDRIVE%%HOMEPATH%\n"
                          "[client]\n"
                          "bitmap_compression=TRuE\n"
                          "\n"
                          "[mod_rdp]\n"
                          "persistent_disk_bitmap_cache=true\n"
                          "cache_waiting_list=no\n"
                          "\n"
                          );

    Inifile             ini;
    ConfigurationLoader cfg_loader(ini, oss);
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(false,                            ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3390,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(0,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("0.0.0.0",                        ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("redemption",                     ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL(PNG_PATH,                         ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL(WRM_PATH,                         ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("%HOMEDRIVE%%HOMEPATH%",          ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(0x8,                              ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0x80,                             ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(true,                             ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());


    // see we can change configuration using parse without default setting of existing ini
    std::stringstream oss2(
                           "[globals]\n"
                           "enable_file_encryption=yes\n"
                           "listen_address=192.168.1.1\n"
                           "certificate_password=\n"
                           "enable_ip_transparent=yes\n"
                           "glyph_cache=yes\n"
                           "[client]\n"
                           "bitmap_compression=no\n"
                           "persist_bitmap_cache_on_disk=yes\n"
                           "[mod_rdp]\n"
                           "persist_bitmap_cache_on_disk=yes\n"
                           "[debug]\n"
                           "password=3\n"
                           "compression=0x3\n"
                           "cache=0\n"
                           );
    cfg_loader.cparse(ini, oss2);

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(false,                            ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3390,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(0,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("192.168.1.1",                    ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("",                               ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL(PNG_PATH,                         ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL(WRM_PATH,                         ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("%HOMEDRIVE%%HOMEPATH%",          ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(3,                                ini.debug.password);
    BOOST_CHECK_EQUAL(3,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(0x8,                              ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0x80,                             ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(true,                             ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(false,                            ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.persist_bitmap_cache_on_disk);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());
}

BOOST_AUTO_TEST_CASE(TestNewConf)
{
    // new behavior:
    // init() load default values from main configuration file
    // - options with multiple occurences get the last value
    // - unrecognized lines are ignored
    // - every characters following # are ignored until end of line (comments)
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini);
    char                temp_path[1024];

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());


    TODO("video related values should go to [video] section")
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(true,                             ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(0,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("0.0.0.0",                        ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("inquisition",                    ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL(PNG_PATH,                         ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL(WRM_PATH,                         ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(0x8,                              ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0x80,                             ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(true,                             ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());


    std::stringstream ifs2(
                           "# Here we put global values\n"
                           "[globals]\n"
                           "# below we have lines with syntax errors, but they are just ignored\n"
                           "yyy\n"
                           "zzz\n"
                           "# unknwon keys are also ignored\n"
                           "yyy=1\n"
                           "[client]\n"
                           "bitmap_compression=no\n"
                           );

    cfg_loader.cparse(ini, ifs2);

    BOOST_CHECK_EQUAL(true,                             ini.video.capture_png);
    BOOST_CHECK_EQUAL(true,                             ini.video.capture_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_flv);
    BOOST_CHECK_EQUAL(false,                            ini.video.capture_ocr);
    BOOST_CHECK_EQUAL(false,                            ini.globals.capture_chunk.get());
    BOOST_CHECK_EQUAL(false,                            ini.globals.movie.get());
    BOOST_CHECK_EQUAL("",                               ini.globals.movie_path.get_cstr());
    BOOST_CHECK_EQUAL("flv",                            ini.globals.codec_id.get_cstr());
    BOOST_CHECK_EQUAL("medium",                         ini.globals.video_quality.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.auth_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.host.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.target_application.get_cstr());
    BOOST_CHECK_EQUAL(0,                                memcmp(ini.globals.auth_channel, "\0\0\0\0\0\0\0\0", 8));

    BOOST_CHECK_EQUAL(true,                             ini.globals.bitmap_cache);
    BOOST_CHECK_EQUAL(false,                            ini.globals.glyph_cache);
    BOOST_CHECK_EQUAL(3389,                             ini.globals.port);
    BOOST_CHECK_EQUAL(0,                                ini.globals.encryptionLevel);
    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.authip.c_str());
    BOOST_CHECK_EQUAL(3350,                             ini.globals.authport);
    BOOST_CHECK_EQUAL(false,                            ini.globals.nomouse);
    BOOST_CHECK_EQUAL(false,                            ini.globals.notimestamp);
    BOOST_CHECK_EQUAL(pathncpy(temp_path, PERSISTENT_PATH, sizeof(temp_path)),
                                                        ini.globals.persistent_path.c_str());

    BOOST_CHECK_EQUAL(3,                                ini.video.capture_flags);
    BOOST_CHECK_EQUAL(3000,                             ini.video.png_interval);
    BOOST_CHECK_EQUAL(40,                               ini.video.frame_interval);
    BOOST_CHECK_EQUAL(600,                              ini.video.break_interval);
    BOOST_CHECK_EQUAL(0,                                ini.video.flv_break_interval);
    BOOST_CHECK_EQUAL(100,                              ini.video.ocr_interval);
    BOOST_CHECK_EQUAL(false,                            ini.video.ocr_on_title_bar_only);
    BOOST_CHECK_EQUAL(40,                               ini.video.ocr_max_unrecog_char_rate);

    BOOST_CHECK_EQUAL(5,                                ini.video.png_limit);

    BOOST_CHECK_EQUAL(10000,                            ini.video.l_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.l_framerate);
    BOOST_CHECK_EQUAL(480,                              ini.video.l_height);
    BOOST_CHECK_EQUAL(640,                              ini.video.l_width);
    BOOST_CHECK_EQUAL(28,                               ini.video.l_qscale);

    BOOST_CHECK_EQUAL(20000,                            ini.video.m_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.m_framerate);
    BOOST_CHECK_EQUAL(768,                              ini.video.m_height);
    BOOST_CHECK_EQUAL(1024,                             ini.video.m_width);
    BOOST_CHECK_EQUAL(14,                               ini.video.m_qscale);

    BOOST_CHECK_EQUAL(30000,                            ini.video.h_bitrate);
    BOOST_CHECK_EQUAL(5,                                ini.video.h_framerate);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_height);
    BOOST_CHECK_EQUAL(2048,                             ini.video.h_width);
    BOOST_CHECK_EQUAL(7,                                ini.video.h_qscale);

    BOOST_CHECK_EQUAL(pathncpy(temp_path, HASH_PATH,  sizeof(temp_path)),
                                                        ini.video.hash_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_PATH, sizeof(temp_path)),
                                                        ini.video.record_path.c_str());
    BOOST_CHECK_EQUAL(pathncpy(temp_path, RECORD_TMP_PATH, sizeof(temp_path)),
                                                        ini.video.record_tmp_path.c_str());

    BOOST_CHECK_EQUAL(0,                                ini.video.disable_keyboard_log.get());
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_syslog);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_wrm);
    BOOST_CHECK_EQUAL(false,                            ini.video.disable_keyboard_log_ocr);

    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_color_depth_selection_strategy);
    BOOST_CHECK_EQUAL(0,                                ini.video.wrm_compression_algorithm);

    BOOST_CHECK_EQUAL(900,                              ini.globals.session_timeout);
    BOOST_CHECK_EQUAL(30,                               ini.globals.keepalive_grace_delay);

    BOOST_CHECK_EQUAL("/tmp/",                          ini.video.replay_path.c_str());

    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_file_encryption.get());
    BOOST_CHECK_EQUAL("0.0.0.0",                        ini.globals.listen_address.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.globals.enable_ip_transparent);
    BOOST_CHECK_EQUAL("inquisition",                    ini.globals.certificate_password.c_str());

    BOOST_CHECK_EQUAL(PNG_PATH,                         ini.globals.png_path.c_str());
    BOOST_CHECK_EQUAL(WRM_PATH,                         ini.globals.wrm_path.c_str());

    BOOST_CHECK_EQUAL("",                               ini.globals.alternate_shell.get_cstr());
    BOOST_CHECK_EQUAL("",                               ini.globals.shell_working_directory.get_cstr());

    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_bitmap_update);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_close_box);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd);
    BOOST_CHECK_EQUAL(true,                             ini.globals.enable_osd_display_remote_target);

    BOOST_CHECK_EQUAL(0,                                ini.debug.x224);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mcs);
    BOOST_CHECK_EQUAL(0,                                ini.debug.sec);
    BOOST_CHECK_EQUAL(0,                                ini.debug.rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.primary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.secondary_orders);
    BOOST_CHECK_EQUAL(0,                                ini.debug.bitmap);
    BOOST_CHECK_EQUAL(0,                                ini.debug.capture);
    BOOST_CHECK_EQUAL(0,                                ini.debug.auth);
    BOOST_CHECK_EQUAL(0,                                ini.debug.session);
    BOOST_CHECK_EQUAL(0,                                ini.debug.front);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_rdp);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_vnc);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_int);
    BOOST_CHECK_EQUAL(0,                                ini.debug.mod_xup);
    BOOST_CHECK_EQUAL(0,                                ini.debug.widget);
    BOOST_CHECK_EQUAL(0,                                ini.debug.input);
    BOOST_CHECK_EQUAL(0,                                ini.debug.password);
    BOOST_CHECK_EQUAL(0,                                ini.debug.compression);
    BOOST_CHECK_EQUAL(0,                                ini.debug.cache);

    BOOST_CHECK_EQUAL(0,                                ini.client.keyboard_layout.get());
    BOOST_CHECK_EQUAL(false,                            ini.client.ignore_logon_password);
    BOOST_CHECK_EQUAL(0,                                ini.client.performance_flags_default);
    BOOST_CHECK_EQUAL(0x8,                              ini.client.performance_flags_force_present);
    BOOST_CHECK_EQUAL(0x80,                             ini.client.performance_flags_force_not_present);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_support);
    BOOST_CHECK_EQUAL(true,                             ini.client.tls_fallback_legacy);
    BOOST_CHECK_EQUAL(4,                                ini.client.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.client.disable_tsk_switch_shortcuts.get());
    BOOST_CHECK_EQUAL(24,                               ini.client.max_color_depth);
    BOOST_CHECK_EQUAL(false,                            ini.client.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.client.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.client.persist_bitmap_cache_on_disk);
    BOOST_CHECK_EQUAL(false,                            ini.client.bitmap_compression);

    BOOST_CHECK_EQUAL(4,                                ini.mod_rdp.rdp_compression);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.disconnect_on_logon_user_change);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.enable_nla);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.open_session_timeout);
    BOOST_CHECK_EQUAL(0,                                ini.mod_rdp.certificate_change_action);
    BOOST_CHECK_EQUAL("15,16,17,18,22",                 ini.mod_rdp.extra_orders.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persistent_disk_bitmap_cache);
    BOOST_CHECK_EQUAL(true,                             ini.mod_rdp.cache_waiting_list);
    BOOST_CHECK_EQUAL(false,                            ini.mod_rdp.persist_bitmap_cache_on_disk);

    BOOST_CHECK_EQUAL("",                               ini.mod_vnc.encodings.c_str());
    BOOST_CHECK_EQUAL(false,                            ini.mod_vnc.allow_authentification_retries);

    BOOST_CHECK_EQUAL("OK",                             ini.translation.button_ok.get_cstr());
    BOOST_CHECK_EQUAL("Cancel",                         ini.translation.button_cancel.get_cstr());
    BOOST_CHECK_EQUAL("Help",                           ini.translation.button_help.get_cstr());
    BOOST_CHECK_EQUAL("Close",                          ini.translation.button_close.get_cstr());
    BOOST_CHECK_EQUAL("Refused",                        ini.translation.button_refused.get_cstr());
    BOOST_CHECK_EQUAL("Login",                          ini.translation.login.get_cstr());
    BOOST_CHECK_EQUAL("Username",                       ini.translation.username.get_cstr());
    BOOST_CHECK_EQUAL("Password",                       ini.translation.password.get_cstr());
    BOOST_CHECK_EQUAL("Target",                         ini.translation.target.get_cstr());
    BOOST_CHECK_EQUAL("Diagnostic",                     ini.translation.diagnostic.get_cstr());
    BOOST_CHECK_EQUAL("Connection closed",              ini.translation.connection_closed.get_cstr());

    BOOST_CHECK_EQUAL(0,                                ini.mod_replay.on_end_of_data);

    BOOST_CHECK_EQUAL(40000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(5,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(15,                               ini.context.opt_qscale.get());
    BOOST_CHECK_EQUAL(800,                              ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(600,                              ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(24,                               ini.context.opt_bpp.get());
}

BOOST_AUTO_TEST_CASE(TestConfigTools)
{
    BOOST_CHECK_EQUAL(0,        ulong_from_cstr("0"));
    BOOST_CHECK_EQUAL(0,        ulong_from_cstr("0x"));

    BOOST_CHECK_EQUAL(3,        ulong_from_cstr("3"));
    BOOST_CHECK_EQUAL(3,        ulong_from_cstr("0x3"));

    BOOST_CHECK_EQUAL(7,        ulong_from_cstr("0x00000007"));
    BOOST_CHECK_EQUAL(7,        ulong_from_cstr("0x0000000000000007"));
    BOOST_CHECK_EQUAL(7,        ulong_from_cstr("0x0007    "));

    BOOST_CHECK_EQUAL(1357,     ulong_from_cstr("1357"));
    BOOST_CHECK_EQUAL(4951,     ulong_from_cstr("0x1357"));

    BOOST_CHECK_EQUAL(10,       ulong_from_cstr("0x0A"));
    BOOST_CHECK_EQUAL(10,       ulong_from_cstr("0x0a"));

    BOOST_CHECK_EQUAL(0,        ulong_from_cstr("0x0000000I"));
    BOOST_CHECK_EQUAL(0,        ulong_from_cstr("I"));

    BOOST_CHECK_EQUAL(0,        level_from_cstr("LoW"));
    BOOST_CHECK_EQUAL(1,        level_from_cstr("mEdIuM"));
    BOOST_CHECK_EQUAL(2,        level_from_cstr("High"));

    BOOST_CHECK_EQUAL(3600,     _long_from_cstr("3600"));
    BOOST_CHECK_EQUAL(0,        _long_from_cstr("0"));
    BOOST_CHECK_EQUAL(0,        _long_from_cstr(""));
    BOOST_CHECK_EQUAL(-3600,    _long_from_cstr("-3600"));
}

BOOST_AUTO_TEST_CASE(TestContextSetValue)
{
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini);

    // Translation
    ini.context_set_value(AUTHID_TRANS_BUTTON_OK,       "Ok");
    ini.context_set_value(AUTHID_TRANS_BUTTON_CANCEL,   "Annuler");
    ini.context_set_value(AUTHID_TRANS_BUTTON_HELP,     "Aide");
    ini.context_set_value(AUTHID_TRANS_BUTTON_CLOSE,    "Fermer");
    ini.context_set_value(AUTHID_TRANS_BUTTON_REFUSED,  "Refusé");
    ini.context_set_value(AUTHID_TRANS_LOGIN,           "Compte");
    ini.context_set_value(AUTHID_TRANS_USERNAME,        "Nom de l'utilisateur");
    ini.context_set_value(AUTHID_TRANS_PASSWORD,        "Mot de passe");
    ini.context_set_value(AUTHID_TRANS_TARGET,          "Cible");
    ini.context_set_value(AUTHID_TRANS_DIAGNOSTIC,      "Diagnostic");
    ini.context_set_value(AUTHID_TRANS_CONNECTION_CLOSED, "Connexion fermée");
    ini.context_set_value(AUTHID_TRANS_HELP_MESSAGE,    "Message d'aide");

    BOOST_CHECK_EQUAL("Ok",                ini.context_get_value(AUTHID_TRANS_BUTTON_OK));
    BOOST_CHECK_EQUAL("Annuler",           ini.context_get_value(AUTHID_TRANS_BUTTON_CANCEL));
    BOOST_CHECK_EQUAL("Aide",              ini.context_get_value(AUTHID_TRANS_BUTTON_HELP));
    BOOST_CHECK_EQUAL("Fermer",            ini.context_get_value(AUTHID_TRANS_BUTTON_CLOSE));
    BOOST_CHECK_EQUAL("Refusé",            ini.context_get_value(AUTHID_TRANS_BUTTON_REFUSED));
    BOOST_CHECK_EQUAL("Compte",            ini.context_get_value(AUTHID_TRANS_LOGIN));
    BOOST_CHECK_EQUAL("Nom de l'utilisateur",
                      ini.context_get_value(AUTHID_TRANS_USERNAME));
    BOOST_CHECK_EQUAL("Mot de passe",      ini.context_get_value(AUTHID_TRANS_PASSWORD));
    BOOST_CHECK_EQUAL("Cible",             ini.context_get_value(AUTHID_TRANS_TARGET));
    BOOST_CHECK_EQUAL("Diagnostic",        ini.context_get_value(AUTHID_TRANS_DIAGNOSTIC));
    BOOST_CHECK_EQUAL("Connexion fermée",  ini.context_get_value(AUTHID_TRANS_CONNECTION_CLOSED));
    BOOST_CHECK_EQUAL("Message d'aide",    ini.context_get_value(AUTHID_TRANS_HELP_MESSAGE));


    // bitrate, framerate, qscale
    ini.context_set_value(AUTHID_OPT_BITRATE,           "80000");
    ini.context_set_value(AUTHID_OPT_FRAMERATE,         "6");
    ini.context_set_value(AUTHID_OPT_QSCALE,            "16");

    BOOST_CHECK_EQUAL(80000,                            ini.context.opt_bitrate.get());
    BOOST_CHECK_EQUAL(6,                                ini.context.opt_framerate.get());
    BOOST_CHECK_EQUAL(16,                               ini.context.opt_qscale.get());

    BOOST_CHECK_EQUAL("80000",                          ini.context_get_value(AUTHID_OPT_BITRATE));
    BOOST_CHECK_EQUAL("6",                              ini.context_get_value(AUTHID_OPT_FRAMERATE));
    BOOST_CHECK_EQUAL("16",                             ini.context_get_value(AUTHID_OPT_QSCALE));


    // bpp, height, width
    ini.context_ask(AUTHID_OPT_BPP);
    ini.context_ask(AUTHID_OPT_HEIGHT);
    ini.context_ask(AUTHID_OPT_WIDTH);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_OPT_BPP));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_OPT_HEIGHT));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_OPT_WIDTH));

    ini.context_set_value(AUTHID_OPT_BPP,               "16");
    ini.context_set_value(AUTHID_OPT_HEIGHT,            "1024");
    ini.context_set_value(AUTHID_OPT_WIDTH,             "1280");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_OPT_BPP));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_OPT_HEIGHT));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_OPT_WIDTH));

    BOOST_CHECK_EQUAL(1280,                             ini.context.opt_width.get());
    BOOST_CHECK_EQUAL(1024,                             ini.context.opt_height.get());
    BOOST_CHECK_EQUAL(16,                               ini.context.opt_bpp.get());

    BOOST_CHECK_EQUAL("1280",                           ini.context_get_value(AUTHID_OPT_WIDTH));
    BOOST_CHECK_EQUAL("1024",                           ini.context_get_value(AUTHID_OPT_HEIGHT));
    BOOST_CHECK_EQUAL("16",                             ini.context_get_value(AUTHID_OPT_BPP));


    ini.context_set_value(AUTHID_AUTH_ERROR_MESSAGE,    "Message d'erreur.");

    BOOST_CHECK_EQUAL("Message d'erreur.", ini.context.auth_error_message.c_str());

    BOOST_CHECK_EQUAL("Message d'erreur.", ini.context_get_value(AUTHID_AUTH_ERROR_MESSAGE));


    // selector, ...
    ini.context_ask(AUTHID_SELECTOR);
    ini.context_ask(AUTHID_SELECTOR_CURRENT_PAGE);
    ini.context_ask(AUTHID_SELECTOR_DEVICE_FILTER);
    ini.context_ask(AUTHID_SELECTOR_GROUP_FILTER);
    ini.context_ask(AUTHID_SELECTOR_LINES_PER_PAGE);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_SELECTOR));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_SELECTOR_CURRENT_PAGE));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_SELECTOR_DEVICE_FILTER));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_SELECTOR_GROUP_FILTER));
    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_SELECTOR_LINES_PER_PAGE));

    ini.context_set_value(AUTHID_SELECTOR,                  "True");
    ini.context_set_value(AUTHID_SELECTOR_CURRENT_PAGE,     "2");
    ini.context_set_value(AUTHID_SELECTOR_DEVICE_FILTER,    "Windows");
    ini.context_set_value(AUTHID_SELECTOR_GROUP_FILTER,     "RDP");
    ini.context_set_value(AUTHID_SELECTOR_LINES_PER_PAGE,   "25");
    ini.context_set_value(AUTHID_SELECTOR_NUMBER_OF_PAGES,  "2");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_CURRENT_PAGE));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_DEVICE_FILTER));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_GROUP_FILTER));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_SELECTOR_LINES_PER_PAGE));

    BOOST_CHECK_EQUAL(true,                             ini.context.selector.get());
    BOOST_CHECK_EQUAL(2,                                ini.context.selector_current_page.get());
    BOOST_CHECK_EQUAL("Windows",                        ini.context.selector_device_filter.get_cstr());
    BOOST_CHECK_EQUAL("RDP",                            ini.context.selector_group_filter.get_cstr());
    BOOST_CHECK_EQUAL(25,                               ini.context.selector_lines_per_page.get());
    BOOST_CHECK_EQUAL(2,                                ini.context.selector_number_of_pages.get());

    BOOST_CHECK_EQUAL("True",                           ini.context_get_value(AUTHID_SELECTOR));
    BOOST_CHECK_EQUAL("2",                              ini.context_get_value(AUTHID_SELECTOR_CURRENT_PAGE));
    BOOST_CHECK_EQUAL("Windows",                        ini.context_get_value(AUTHID_SELECTOR_DEVICE_FILTER));
    BOOST_CHECK_EQUAL("RDP",                            ini.context_get_value(AUTHID_SELECTOR_GROUP_FILTER));
    BOOST_CHECK_EQUAL("25",                             ini.context_get_value(AUTHID_SELECTOR_LINES_PER_PAGE));
    BOOST_CHECK_EQUAL("2",                              ini.context_get_value(AUTHID_SELECTOR_NUMBER_OF_PAGES));

    BOOST_CHECK_EQUAL(true,                             ini.context_get_bool(AUTHID_SELECTOR));


    // target_xxxx
    ini.context_set_value(AUTHID_TARGET_DEVICE,         "127.0.0.1");
    ini.context_set_value(AUTHID_TARGET_PASSWORD,       "12345678");
    ini.context_set_value(AUTHID_TARGET_PORT,           "3390");
    ini.context_set_value(AUTHID_TARGET_PROTOCOL,       "RDP");
    ini.context_set_value(AUTHID_TARGET_USER,           "admin");
    ini.context_set_value(AUTHID_TARGET_APPLICATION,    "wallix@putty");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_TARGET_DEVICE));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_TARGET_PASSWORD));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_TARGET_PORT));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_TARGET_PROTOCOL));
    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_TARGET_USER));

    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.target_device.get_cstr());
    BOOST_CHECK_EQUAL("12345678",                       ini.context.target_password.get_cstr());
    BOOST_CHECK_EQUAL(3390,                             ini.context.target_port.get());
    BOOST_CHECK_EQUAL("RDP",                            ini.context.target_protocol.get_cstr());
    BOOST_CHECK_EQUAL("admin",                          ini.globals.target_user.get_cstr());
    BOOST_CHECK_EQUAL("wallix@putty",                   ini.globals.target_application.get_cstr());

    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.context_get_value(AUTHID_TARGET_DEVICE));
    BOOST_CHECK_EQUAL("12345678",                       ini.context_get_value(AUTHID_TARGET_PASSWORD));
    BOOST_CHECK_EQUAL("3390",                           ini.context_get_value(AUTHID_TARGET_PORT));
    BOOST_CHECK_EQUAL("RDP",                            ini.context_get_value(AUTHID_TARGET_PROTOCOL));
    BOOST_CHECK_EQUAL("admin",                          ini.context_get_value(AUTHID_TARGET_USER));
    BOOST_CHECK_EQUAL("wallix@putty",                   ini.context_get_value(AUTHID_TARGET_APPLICATION));


    // host
    ini.context_ask(AUTHID_HOST);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_HOST));

    ini.context_set_value(AUTHID_HOST,                  "127.0.0.1");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_HOST));

    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.globals.host.get_cstr());

    BOOST_CHECK_EQUAL("127.0.0.1",                      ini.context_get_value(AUTHID_HOST));


    // target
    ini.context_ask(AUTHID_TARGET);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_TARGET));

    ini.context_set_value(AUTHID_TARGET,                "192.168.0.1");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_TARGET));

    BOOST_CHECK_EQUAL("192.168.0.1",                    ini.globals.target.get_cstr());

    BOOST_CHECK_EQUAL("192.168.0.1",                    ini.context_get_value(AUTHID_TARGET));


    // auth_user
    ini.context_set_value(AUTHID_AUTH_USER,             "admin");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_AUTH_USER));

    BOOST_CHECK_EQUAL("admin",                          ini.globals.auth_user.get_cstr());

    BOOST_CHECK_EQUAL("admin",                          ini.context_get_value(AUTHID_AUTH_USER));


    // password
    ini.context_ask(AUTHID_PASSWORD);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_PASSWORD));

    ini.context_set_value(AUTHID_PASSWORD,              "12345678");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_PASSWORD));

    BOOST_CHECK_EQUAL("12345678",                       ini.context.password.get_cstr());

    BOOST_CHECK_EQUAL("12345678",                       ini.context_get_value(AUTHID_PASSWORD));


    // answer
    ini.context_set_value(AUTHID_AUTHCHANNEL_ANSWER,    "answer");

    BOOST_CHECK_EQUAL("answer",                         ini.context.authchannel_answer.get_cstr());

    BOOST_CHECK_EQUAL("answer",                         ini.context_get_value(AUTHID_AUTHCHANNEL_ANSWER));


    // authchannel_target
    ini.context_ask(AUTHID_AUTHCHANNEL_TARGET);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_AUTHCHANNEL_TARGET));

    ini.context_set_value(AUTHID_AUTHCHANNEL_TARGET,    "target");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_AUTHCHANNEL_TARGET));

    BOOST_CHECK_EQUAL("target",                         ini.context.authchannel_target.get_cstr());

    BOOST_CHECK_EQUAL("target",                         ini.context_get_value(AUTHID_AUTHCHANNEL_TARGET));


    // authchannel_result
    ini.context_ask(AUTHID_AUTHCHANNEL_RESULT);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_AUTHCHANNEL_RESULT));

    ini.context_set_value(AUTHID_AUTHCHANNEL_RESULT,    "result");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_AUTHCHANNEL_RESULT));

    BOOST_CHECK_EQUAL("result",                         ini.context.authchannel_result.get_cstr());

    BOOST_CHECK_EQUAL("result",                         ini.context_get_value(AUTHID_AUTHCHANNEL_RESULT));

    // regex
    ini.context_set_value(AUTHID_PATTERN_KILL,         "Explorer");
    BOOST_CHECK_EQUAL("Explorer",                      ini.context.pattern_kill.get_cstr());
    BOOST_CHECK_EQUAL("Explorer",                      ini.context_get_value(AUTHID_PATTERN_KILL));

    ini.context_set_value(AUTHID_PATTERN_NOTIFY,       "Word");
    BOOST_CHECK_EQUAL("Word",                      ini.context.pattern_notify.get_cstr());
    BOOST_CHECK_EQUAL("Word",                      ini.context_get_value(AUTHID_PATTERN_NOTIFY));


    // message
    ini.context_set_value(AUTHID_MESSAGE,               "message");

    BOOST_CHECK_EQUAL("message",                        ini.context.message.get_cstr());

    BOOST_CHECK_EQUAL("message",                        ini.context_get_value(AUTHID_MESSAGE));


    // accept_message
    ini.context_ask(AUTHID_ACCEPT_MESSAGE);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_ACCEPT_MESSAGE));

    ini.context_set_value(AUTHID_ACCEPT_MESSAGE,        "accept_message");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_ACCEPT_MESSAGE));

    BOOST_CHECK_EQUAL("accept_message",                 ini.context.accept_message.get_cstr());

    BOOST_CHECK_EQUAL("accept_message",                 ini.context_get_value(AUTHID_ACCEPT_MESSAGE));


    // display_message
    ini.context_ask(AUTHID_DISPLAY_MESSAGE);

    BOOST_CHECK_EQUAL(true,                             ini.context_is_asked(AUTHID_DISPLAY_MESSAGE));

    ini.context_set_value(AUTHID_DISPLAY_MESSAGE,       "display_message");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_DISPLAY_MESSAGE));

    BOOST_CHECK_EQUAL("display_message",                ini.context.display_message.get_cstr());

    BOOST_CHECK_EQUAL("display_message",                ini.context_get_value(AUTHID_DISPLAY_MESSAGE));


    // rejected
    ini.context_set_value(AUTHID_REJECTED,              "rejected");

    BOOST_CHECK_EQUAL("rejected",                       ini.context.rejected.get_cstr());

    BOOST_CHECK_EQUAL("rejected",                       ini.context_get_value(AUTHID_REJECTED));


    // authenticated
    ini.context_set_value(AUTHID_AUTHENTICATED,         "True");

    BOOST_CHECK_EQUAL(true,                             ini.context.authenticated.get());

    BOOST_CHECK_EQUAL(true,                             ini.context_get_bool(AUTHID_AUTHENTICATED));

    BOOST_CHECK_EQUAL("True",                           ini.context_get_value(AUTHID_AUTHENTICATED));


    // keepalive
    ini.context_set_value(AUTHID_KEEPALIVE,             "True");

    BOOST_CHECK_EQUAL(false,                            ini.context_is_asked(AUTHID_KEEPALIVE));

    BOOST_CHECK_EQUAL(true,                             ini.context.keepalive.get());

    BOOST_CHECK_EQUAL(true,                             ini.context_get_bool(AUTHID_KEEPALIVE));

    BOOST_CHECK_EQUAL("True",                           ini.context_get_value(AUTHID_KEEPALIVE));


    // session_id
    ini.context_set_value(AUTHID_SESSION_ID,            "0123456789");

    BOOST_CHECK_EQUAL("0123456789",                     ini.context.session_id.get_cstr());

    BOOST_CHECK_EQUAL("0123456789",                     ini.context_get_value(AUTHID_SESSION_ID));


    // end_date_cnx
    ini.context_set_value(AUTHID_END_DATE_CNX,          "12345678");

    BOOST_CHECK_EQUAL(12345678,                         ini.context.end_date_cnx.get());

    BOOST_CHECK_EQUAL("12345678",                       ini.context_get_value(AUTHID_END_DATE_CNX));


    // end_time
    ini.context_set_value(AUTHID_END_TIME,              "end_time");

    BOOST_CHECK_EQUAL("end_time",                       ini.context.end_time.get_cstr());

    BOOST_CHECK_EQUAL("end_time",                       ini.context_get_value(AUTHID_END_TIME));


    // mode_console
    ini.context_set_value(AUTHID_MODE_CONSOLE,          "deny");

    BOOST_CHECK_EQUAL("deny",                           ini.context.mode_console.get_cstr());

    BOOST_CHECK_EQUAL("deny",                           ini.context_get_value(AUTHID_MODE_CONSOLE));


    // timezone
    ini.context_set_value(AUTHID_TIMEZONE,              "-7200");

    BOOST_CHECK_EQUAL(-7200,                            ini.context.timezone.get());

    BOOST_CHECK_EQUAL("-7200",                          ini.context_get_value(AUTHID_TIMEZONE));


    // real_target_device
    ini.context_set_value(AUTHID_REAL_TARGET_DEVICE,    "10.0.0.1");

    BOOST_CHECK_EQUAL("10.0.0.1",                       ini.context.real_target_device.get_cstr());

    BOOST_CHECK_EQUAL("10.0.0.1",                       ini.context_get_value(AUTHID_REAL_TARGET_DEVICE));


    // authentication_challenge
    ini.context_set_value(AUTHID_AUTHENTICATION_CHALLENGE,     "true");

    BOOST_CHECK_EQUAL(true,                             ini.context.authentication_challenge.get());

    BOOST_CHECK_EQUAL("True",                           ini.context_get_value(AUTHID_AUTHENTICATION_CHALLENGE));
}


//BOOST_AUTO_TEST_CASE(TestAuthentificationKeywordRecognition)
//{
//    BOOST_CHECK_EQUAL(AUTHID_UNKNOWN, authid_from_string("unknown"));
//    BOOST_CHECK_EQUAL(AUTHID_TARGET_USER, authid_from_string(STRAUTHID_TARGET_USER));
//    BOOST_CHECK_EQUAL(AUTHID_TARGET_PASSWORD, authid_from_string(STRAUTHID_TARGET_PASSWORD));
//    BOOST_CHECK_EQUAL(AUTHID_HOST, authid_from_string(STRAUTHID_HOST));
//    BOOST_CHECK_EQUAL(AUTHID_PASSWORD, authid_from_string(STRAUTHID_PASSWORD));
//    BOOST_CHECK_EQUAL(AUTHID_AUTH_USER, authid_from_string(STRAUTHID_AUTH_USER));
//    BOOST_CHECK_EQUAL(AUTHID_TARGET_DEVICE, authid_from_string(STRAUTHID_TARGET_DEVICE));
//    BOOST_CHECK_EQUAL(AUTHID_TARGET_PORT, authid_from_string(STRAUTHID_TARGET_PORT));
//    BOOST_CHECK_EQUAL(AUTHID_TARGET_PROTOCOL, authid_from_string(STRAUTHID_TARGET_PROTOCOL));
//    BOOST_CHECK_EQUAL(AUTHID_REJECTED, authid_from_string(STRAUTHID_REJECTED));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_MOVIE, authid_from_string(STRAUTHID_OPT_MOVIE));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_MOVIE_PATH, authid_from_string(STRAUTHID_OPT_MOVIE_PATH));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_CLIPBOARD, authid_from_string(STRAUTHID_OPT_CLIPBOARD));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_DEVICEREDIRECTION, authid_from_string(STRAUTHID_OPT_DEVICEREDIRECTION));
//    BOOST_CHECK_EQUAL(AUTHID_END_DATE_CNX, authid_from_string(STRAUTHID_END_DATE_CNX));
//    BOOST_CHECK_EQUAL(AUTHID_MESSAGE, authid_from_string(STRAUTHID_MESSAGE));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_BITRATE, authid_from_string(STRAUTHID_OPT_BITRATE));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_FRAMERATE, authid_from_string(STRAUTHID_OPT_FRAMERATE));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_QSCALE, authid_from_string(STRAUTHID_OPT_QSCALE));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_CODEC_ID, authid_from_string(STRAUTHID_OPT_CODEC_ID));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_WIDTH, authid_from_string(STRAUTHID_OPT_WIDTH));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_HEIGHT, authid_from_string(STRAUTHID_OPT_HEIGHT));
//    BOOST_CHECK_EQUAL(AUTHID_OPT_BPP, authid_from_string(STRAUTHID_OPT_BPP));
//    BOOST_CHECK_EQUAL(AUTHID_AUTHENTICATED, authid_from_string(STRAUTHID_AUTHENTICATED));
//    BOOST_CHECK_EQUAL(AUTHID_SELECTOR, authid_from_string(STRAUTHID_SELECTOR));
//    BOOST_CHECK_EQUAL(AUTHID_KEEPALIVE, authid_from_string(STRAUTHID_KEEPALIVE));
//    BOOST_CHECK_EQUAL(AUTHID_UNKNOWN, authid_from_string("8899676"));
//    BOOST_CHECK_EQUAL(AUTHID_DISPLAY_MESSAGE, authid_from_string(STRAUTHID_DISPLAY_MESSAGE));
//    BOOST_CHECK_EQUAL(AUTHID_ACCEPT_MESSAGE, authid_from_string(STRAUTHID_ACCEPT_MESSAGE));
//    BOOST_CHECK_EQUAL(AUTHID_AUTH_ERROR_MESSAGE, authid_from_string(STRAUTHID_AUTH_ERROR_MESSAGE));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_BUTTON_OK, authid_from_string(STRAUTHID_TRANS_BUTTON_OK));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_BUTTON_CANCEL, authid_from_string(STRAUTHID_TRANS_BUTTON_CANCEL));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_BUTTON_HELP, authid_from_string(STRAUTHID_TRANS_BUTTON_HELP));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_BUTTON_CLOSE, authid_from_string(STRAUTHID_TRANS_BUTTON_CLOSE));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_BUTTON_REFUSED, authid_from_string(STRAUTHID_TRANS_BUTTON_REFUSED));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_LOGIN, authid_from_string(STRAUTHID_TRANS_LOGIN));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_USERNAME, authid_from_string(STRAUTHID_TRANS_USERNAME));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_PASSWORD, authid_from_string(STRAUTHID_TRANS_PASSWORD));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_TARGET, authid_from_string(STRAUTHID_TRANS_TARGET));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_DIAGNOSTIC, authid_from_string(STRAUTHID_TRANS_DIAGNOSTIC));
//    BOOST_CHECK_EQUAL(AUTHID_TRANS_CONNECTION_CLOSED, authid_from_string(STRAUTHID_TRANS_CONNECTION_CLOSED));
//    BOOST_CHECK_EQUAL(AUTHID_MODE_CONSOLE, authid_from_string(STRAUTHID_MODE_CONSOLE));
//    BOOST_CHECK_EQUAL(AUTHID_VIDEO_QUALITY, authid_from_string(STRAUTHID_VIDEO_QUALITY));
//    BOOST_CHECK_EQUAL(AUTHID_TIMEZONE, authid_from_string(STRAUTHID_TIMEZONE));
//}



BOOST_AUTO_TEST_CASE(TestConfigNotifications)
{
//     Inifile             ini;
//     ConfigurationLoader cfg_loader(ini);
    /*
    // nothing has been changed initialy
    //    BOOST_CHECK(!ini.check());

    // auth_user has been changed, so check() method will notify that something changed
    ini.globals.auth_user.set_from_cstr("someoneelse");
    BOOST_CHECK(ini.check());
    BOOST_CHECK_EQUAL("someoneelse",       ini.get_changed_list().back()->get_value());


    ini.reset();
    BOOST_CHECK(!ini.check());

    // setting a field without changing it should not notify that something changed
    ini.globals.auth_user.set_from_cstr("someoneelse");
    BOOST_CHECK(!ini.check());


    // Using the list of changed fields:
    ini.globals.auth_user.set_from_cstr("someuser");
    ini.globals.host.set_from_cstr("35.53.0.1");
    ini.context.opt_height.set(602);
    ini.globals.target.set_from_cstr("35.53.0.2");
    ini.context.selector.set(true);
    BOOST_CHECK(ini.check());
    std::list< Inifile::BaseField * > list = ini.get_changed_list();
    BOOST_CHECK_EQUAL("True",      list.back()->get_value());
    list.pop_back();
    BOOST_CHECK_EQUAL("35.53.0.2", list.back()->get_value());
    list.pop_back();
    BOOST_CHECK_EQUAL("602",       list.back()->get_value());
    list.pop_back();
    BOOST_CHECK_EQUAL("35.53.0.1", list.back()->get_value());
    list.pop_back();
    BOOST_CHECK_EQUAL("someuser",  list.back()->get_value());
    ini.reset();
    BOOST_CHECK(!ini.check());
    */
}

BOOST_AUTO_TEST_CASE(TestConfigFieldAuthid)
{
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini);
    // Test get_serialized()
    char tmp[256];
    BOOST_CHECK_EQUAL(AUTHID_SELECTOR,          ini.get_field_list().at(AUTHID_SELECTOR)->get_authid());
    BOOST_CHECK_EQUAL("login\nASK\n",           ini.globals.auth_user.get_serialized(tmp, sizeof(tmp), ini.debug.password));
    ini.globals.auth_user.set_from_cstr("someuser");
    BOOST_CHECK_EQUAL("login\n!someuser\n",     ini.globals.auth_user.get_serialized(tmp, sizeof(tmp), ini.debug.password));

    ini.context.authchannel_target.set_from_cstr("TEST_TARGET");
    BOOST_CHECK_EQUAL("auth_channel_target\n!TEST_TARGET\n",
                      ini.context.authchannel_target.get_serialized(tmp, sizeof(tmp), ini.debug.password));
}

BOOST_AUTO_TEST_CASE(TestConfigFieldGetValue)
{
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini);
    // Test get_value()

    ini.globals.target_user.ask();
    BOOST_CHECK_EQUAL("ASK",       ini.globals.target_user.get_value());
    ini.globals.target_user.set_from_cstr("linuxuser");
    BOOST_CHECK_EQUAL("linuxuser", ini.globals.target_user.get_value());
    ini.globals.target_user.ask();
    BOOST_CHECK_EQUAL("ASK",       ini.globals.target_user.get_value());

    ini.globals.enable_file_encryption.set(true);
    BOOST_CHECK_EQUAL("True",      ini.globals.enable_file_encryption.get_value());
    ini.globals.enable_file_encryption.set(false);
    BOOST_CHECK_EQUAL("False",     ini.globals.enable_file_encryption.get_value());
    ini.globals.enable_file_encryption.ask();
    BOOST_CHECK_EQUAL("ASK",       ini.globals.enable_file_encryption.get_value());

    ini.context.opt_bpp.ask();
    BOOST_CHECK_EQUAL("ASK",       ini.context.opt_bpp.get_value());
    ini.context.opt_bpp.set(123);
    BOOST_CHECK_EQUAL("123",       ini.context.opt_bpp.get_value());
    ini.context.opt_bpp.set(741258);
    BOOST_CHECK_EQUAL("741258",    ini.context.opt_bpp.get_value());
    ini.context.opt_bpp.ask();
    BOOST_CHECK_EQUAL("ASK",       ini.context.opt_bpp.get_value());

    ini.context.selector_lines_per_page.set(1111155555);
    BOOST_CHECK_EQUAL("1111155555",ini.context.selector_lines_per_page.get_value());
    ini.context.selector_lines_per_page.ask();
    BOOST_CHECK_EQUAL("ASK",       ini.context.selector_lines_per_page.get_value());

}

BOOST_AUTO_TEST_CASE(TestConfigUnsignedField)
{

}

BOOST_AUTO_TEST_CASE(TestConfigStringField)
{

}

BOOST_AUTO_TEST_CASE(TestConfigSignedField)
{

}

BOOST_AUTO_TEST_CASE(TestConfigBoolField)
{
    BOOST_CHECK_EQUAL(true, bool_from_cstr("1"));
    BOOST_CHECK_EQUAL(true, bool_from_cstr("yes"));
    BOOST_CHECK_EQUAL(true, bool_from_cstr("true"));
    BOOST_CHECK_EQUAL(true, bool_from_cstr("True"));
    BOOST_CHECK_EQUAL(true, bool_from_cstr("TRUE"));
    BOOST_CHECK_EQUAL(false, bool_from_cstr("Tru"));
    BOOST_CHECK_EQUAL(false, bool_from_cstr("111"));
}

BOOST_AUTO_TEST_CASE(TestConfigIp)
{
    std::stringstream   oss(
        "[globals]\n"
        "authip=255.255.255.255\n"
    );
    Inifile             ini;
    ConfigurationLoader cfg_loader(ini, oss);

    BOOST_CHECK_EQUAL("255.255.255.255", ini.globals.authip.c_str());
}

BOOST_AUTO_TEST_CASE(TestConfigField)
{
    /*---------------------------------
    // Testing StringField
    -----------------------------------*/
    Inifile::StringField stringf;

    // those are initial values
    BOOST_CHECK_EQUAL(false, stringf.is_asked());
    BOOST_CHECK_EQUAL(true, stringf.has_changed());

    // setting a string from initial value
    std::string initialstring("astring");
    stringf.set("astring");
    BOOST_CHECK_EQUAL(false, stringf.is_asked());
    BOOST_CHECK_EQUAL(true, stringf.has_changed());

    // using the field set it as unchanged
    stringf.use();
    BOOST_CHECK_EQUAL(false, stringf.has_changed());

    // getting the string set it as read
    BOOST_CHECK_EQUAL("astring", stringf.get_cstr());

    // asking for the field set it as changed
    stringf.ask();
    BOOST_CHECK_EQUAL(true, stringf.is_asked());
    BOOST_CHECK_EQUAL(true, stringf.has_changed());

    // setting another string set it as unasked
    stringf.set_from_cstr("anotherstring");
    BOOST_CHECK_EQUAL(false, stringf.is_asked());
    BOOST_CHECK_EQUAL(true, stringf.has_changed());

    BOOST_CHECK_EQUAL("anotherstring", stringf.get_cstr());
    BOOST_CHECK_EQUAL(true, stringf.has_changed());

    stringf.use();
    BOOST_CHECK_EQUAL(false, stringf.has_changed());

    // setting the same string changes only the ask flag (as not asked)
    stringf.set_from_cstr("anotherstring");
    BOOST_CHECK_EQUAL(false, stringf.has_changed());


    /*---------------------------------
    // Testing UnsignedField Same scenario
    -----------------------------------*/
    Inifile::UnsignedField unsignedf;
    BOOST_CHECK_EQUAL(false, unsignedf.is_asked());
    BOOST_CHECK_EQUAL(true, unsignedf.has_changed());
    // setting a unsigned from initial value

    unsignedf.set(321);
    BOOST_CHECK_EQUAL(false, unsignedf.is_asked());
    BOOST_CHECK_EQUAL(true, unsignedf.has_changed());

    // using the field set it as unchanged
    unsignedf.use();
    BOOST_CHECK_EQUAL(false, unsignedf.has_changed());

    // getting the integer set it as read
    BOOST_CHECK_EQUAL(321, unsignedf.get());

    // asking for the field set it as changed
    unsignedf.ask();
    BOOST_CHECK_EQUAL(true, unsignedf.is_asked());
    BOOST_CHECK_EQUAL(true, unsignedf.has_changed());

    // setting another integer set it as unasked
    unsignedf.set(654321);
    BOOST_CHECK_EQUAL(false, unsignedf.is_asked());
    BOOST_CHECK_EQUAL(true, unsignedf.has_changed());

    BOOST_CHECK_EQUAL(654321, unsignedf.get());
    BOOST_CHECK_EQUAL(true, unsignedf.has_changed());

    unsignedf.use();
    BOOST_CHECK_EQUAL(false, unsignedf.has_changed());

    // setting the same integer changes only the ask flag (as not asked)
    unsignedf.set(654321);
    BOOST_CHECK_EQUAL(false, unsignedf.has_changed());


    /*---------------------------------
    // Testing BoolField Same Scenario
    -----------------------------------*/
    Inifile::BoolField boolf;
    BOOST_CHECK_EQUAL(false, boolf.is_asked());
    BOOST_CHECK_EQUAL(true, boolf.has_changed());

    boolf.set(true);
    BOOST_CHECK_EQUAL(false, boolf.is_asked());
    BOOST_CHECK_EQUAL(true, boolf.has_changed());

    // using the field set it as unchanged
    boolf.use();
    BOOST_CHECK_EQUAL(false, boolf.has_changed());

    // getting the integer set it as read
    BOOST_CHECK_EQUAL(true, boolf.get());

    // asking for the field set it as changed
    boolf.ask();
    BOOST_CHECK_EQUAL(true, boolf.is_asked());
    BOOST_CHECK_EQUAL(true, boolf.has_changed());

    // setting another integer set it as unasked
    boolf.set(false);
    BOOST_CHECK_EQUAL(false, boolf.is_asked());
    BOOST_CHECK_EQUAL(true, boolf.has_changed());

    BOOST_CHECK_EQUAL(false, boolf.get());
    BOOST_CHECK_EQUAL(true, boolf.has_changed());

    boolf.use();
    BOOST_CHECK_EQUAL(false, boolf.has_changed());

    // setting the same integer changes only the ask flag (as not asked)
    boolf.set(false);
    BOOST_CHECK_EQUAL(false, boolf.has_changed());
}
