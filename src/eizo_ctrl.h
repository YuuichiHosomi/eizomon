#ifndef EZMON_EIZO_CTRL
#define EZMON_EIZO_CTRL

#if defined(__cplusplus)
extern "C" {
#endif

/*
   Copyright (C) 2015 Xfennec, CQFD Corp.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "hidapi.h"

#define EM_EIZO_FG_2421_VENDORID        0x056d
#define EM_EIZO_FG_2421_PRODUCTID       0x0002

#define EM_EIZO_FG_2421_CMD_COLORTEMP         0x01
#define EM_EIZO_FG_2421_CMD_MODE              0x03
#define EM_EIZO_FG_2421_CMD_BLACKLEVEL        0x0c /* 00..64 */
#define EM_EIZO_FG_2421_CMD_GAMMA             0x0b
#define EM_EIZO_FG_2421_CMD_POWERON           0x14
#define EM_EIZO_FG_2421_CMD_ECOVIEW           0x15
#define EM_EIZO_FG_2421_CMD_LANGUAGE          0x16
#define EM_EIZO_FG_2421_CMD_BOOTLOGO          0x1A
#define EM_EIZO_FG_2421_CMD_POWERSAVE         0x20
#define EM_EIZO_FG_2421_CMD_CONTRASTENHANCE   0x26
#define EM_EIZO_FG_2421_CMD_240HZ             0x27
#define EM_EIZO_FG_2421_CMD_BACKLIGHT         0x28
#define EM_EIZO_FG_2421_CMD_VOLUME            0x36
#define EM_EIZO_FG_2421_CMD_BRIGHTNESS        0x38 /* 00..c8 */
#define EM_EIZO_FG_2421_CMD_CONTRAST          0x39 /* 00..8c */
#define EM_EIZO_FG_2421_CMD_COLORGAIN_R       0x3a /* 00..ff */
#define EM_EIZO_FG_2421_CMD_COLORGAIN_G       0x3b
#define EM_EIZO_FG_2421_CMD_COLORGAIN_B       0x3c

#define EM_EIZO_FG_2421_REQ_INPUT             0x18

#define EM_EIZO_FG_2421_MODE_USER1      0x16
#define EM_EIZO_FG_2421_MODE_USER2      0x17
#define EM_EIZO_FG_2421_MODE_USER3      0x18
#define EM_EIZO_FG_2421_MODE_FPS1       0x28
#define EM_EIZO_FG_2421_MODE_FPS2       0x29
#define EM_EIZO_FG_2421_MODE_RTS        0x2a
#define EM_EIZO_FG_2421_MODE_WEB        0x2b

#define EM_EIZO_FG_2421_GAMMA_2_0           0x03
#define EM_EIZO_FG_2421_GAMMA_2_2           0x04
#define EM_EIZO_FG_2421_GAMMA_2_4           0x05
#define EM_EIZO_FG_2421_GAMMA_FPS_HIGH      0xf4
#define EM_EIZO_FG_2421_GAMMA_FPS_MEDIUM    0xf5
#define EM_EIZO_FG_2421_GAMMA_FPS_LOW       0xf6
#define EM_EIZO_FG_2421_GAMMA_FPS_RTS       0xf7
#define EM_EIZO_FG_2421_GAMMA_FPS_POWER     0xfc

#define EM_EIZO_FG_2421_LANG_EN             0x00
#define EM_EIZO_FG_2421_LANG_DE             0x01
#define EM_EIZO_FG_2421_LANG_FR             0x02
//~ #define EM_EIZO_FG_2421_LANG_..             0x..

//~ #define EM_EIZO_FG_2421_INPUT_DVI           0x..
//~ #define EM_EIZO_FG_2421_INPUT_HDMI          0x..
//~ #define EM_EIZO_FG_2421_INPUT_DISPLAYPORT   0x..

#define EM_EIZO_FG_2421_COLORTEMP_OFF       0x00
#define EM_EIZO_FG_2421_COLORTEMP_5000K     0x03
#define EM_EIZO_FG_2421_COLORTEMP_6500K     0x06
#define EM_EIZO_FG_2421_COLORTEMP_8000K     0x09
#define EM_EIZO_FG_2421_COLORTEMP_9300K     0x0c

#define EM_EIZO_FG_2421_CMD_CONTRASTENHANCE_OFF         0x00
#define EM_EIZO_FG_2421_CMD_CONTRASTENHANCE_STANDARD    0x01
#define EM_EIZO_FG_2421_CMD_CONTRASTENHANCE_ENHANCED    0x02

/*
- Unknown / To Inspect things:
0x06: accepts 00 / 15 (def) / ff, no visisble change
0x09: returns 03 17 (RW?)
0x0a: seems related to poweron time
0x0d: accepts 00 / 01 (def), no visible change
0x0e: returns ff (RW?)
0x0f: (same)
0x10: (same)
0x12: screen size (RW?, values?)
0x13: returns 02 (RW?)
0x17: returns model
0x19: long string, non-text. S/N?
0x25: returns 24 01 / 18 01 / 14 00 (RW?) seems to change during some cmds
0x2a: accepts 00 / 10 (def), seems to disable all color correction
0x30: returns 2a 17 (RW?)
0x31: returns 03 17 .. (RW?) See 0x09?
0x34: returns 0f 00 31 39 35 35 41 32 ([1955A2] as text). Unknow.
0x35: accepts 01 / 08 (def) / 09, no visible change
*/

#define EM_MONITOR_BUFFER_SIZE  3

typedef struct eizo_ctrl_monitor {
    hid_device *handle;
    unsigned char buffer[EM_MONITOR_BUFFER_SIZE];
    unsigned char backlight_status;
} eizo_ctrl_monitor;

int eizo_ctrl_detect(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number);
eizo_ctrl_monitor *eizo_ctrl_open(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number);
int eizo_ctrl_command(eizo_ctrl_monitor *monitor, unsigned char command, unsigned char arg1, unsigned char arg2);

#if defined(__cplusplus)
}
#endif

#endif
