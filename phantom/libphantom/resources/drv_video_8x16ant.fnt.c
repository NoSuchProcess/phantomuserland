/**
 *
 * Phantom OS
 *
 * Copyright (C) 2005-2009 Dmitry Zavalishin, dz@dz.ru
 *
 * Kernel ready: yes
 * Preliminary: yes
 *
 *
**/

#include "drv_video_screen.h"

char drv_video_8x16ant_fnt [] = { 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7e, 0x81, 0xa5, 0x81, 0x81, 0xbd, 0x99, 0x81, 0x81, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7e, 0xff, 0xdb, 0xff, 0xff, 0xc3, 0xe7, 0xff, 0xff, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x6c, 0xfe, 0xfe, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x18, 0x3c, 0x3c, 0xe7, 0xe7, 0xe7, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc3, 0xc3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x66, 0x42, 0x42, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x99, 0xbd, 0xbd, 0x99, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x00, 0x1e, 0x0e, 0x1a, 0x32, 0x78, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3f, 0x33, 0x3f, 0x30, 0x30, 0x30, 0x30, 0x70, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7f, 0x63, 0x7f, 0x63, 0x63, 0x63, 0x63, 0x67, 0xe7, 0xe6, 0xc0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x18, 0x18, 0xdb, 0x3c, 0xe7, 0x3c, 0xdb, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfe, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x02, 0x06, 0x0e, 0x1e, 0x3e, 0xfe, 0x3e, 0x1e, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7f, 0xdb, 0xdb, 0xdb, 0x7b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x00, 0x00, 0x00, 0x00,
0x00, 0x7c, 0xc6, 0x60, 0x38, 0x6c, 0xc6, 0xc6, 0x6c, 0x38, 0x0c, 0xc6, 0x7c, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0xfe, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60, 0xfe, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x6c, 0xfe, 0x6c, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x7c, 0x7c, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x7c, 0x7c, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x66, 0x42, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x6c, 0x6c, 0x6c, 0xfe, 0x6c, 0x6c, 0x6c, 0xfe, 0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x10, 0x7c, 0xd2, 0xd0, 0xf0, 0x7c, 0x3e, 0x1e, 0x16, 0x96, 0x7c, 0x10, 0x00, 0x00, 0x00,
0x00, 0x00, 0x62, 0x66, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xcc, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x30, 0x68, 0x58, 0x38, 0x70, 0xf2, 0xd4, 0xc8, 0xd4, 0x76, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x08, 0x10, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00,
0x00, 0x10, 0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xd6, 0xfe, 0x7c, 0xee, 0x7c, 0xfe, 0xd6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x10, 0x20, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x06, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1c, 0x26, 0x66, 0x66, 0x6e, 0x76, 0x66, 0x66, 0x64, 0x38, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x46, 0x66, 0x06, 0x0c, 0x18, 0x30, 0x62, 0x7e, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x66, 0x66, 0x06, 0x3c, 0x06, 0x06, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x06, 0x0e, 0x16, 0x26, 0x46, 0xff, 0x06, 0x06, 0x0f, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7e, 0x7e, 0x40, 0x5c, 0x66, 0x46, 0x06, 0x66, 0x46, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1c, 0x26, 0x66, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7e, 0x7e, 0x42, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x66, 0x62, 0x74, 0x3c, 0x2e, 0x46, 0x46, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x3e, 0x06, 0x66, 0x64, 0x38, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x38, 0x18, 0x10, 0x20, 0x00, 0x00,
0x00, 0x00, 0x00, 0x04, 0x0c, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x20, 0x30, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7c, 0xc6, 0x86, 0x06, 0x0c, 0x18, 0x30, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x46, 0x9a, 0xb6, 0xba, 0xb6, 0x9c, 0x80, 0xc2, 0x7c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x06, 0x0e, 0x0e, 0x16, 0x16, 0x26, 0x3e, 0x46, 0x46, 0xef, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfc, 0x66, 0x62, 0x66, 0x7c, 0x66, 0x62, 0x62, 0x66, 0xfc, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3e, 0x46, 0xc2, 0xc0, 0xc0, 0xc0, 0xc0, 0xc2, 0xe6, 0x7c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfc, 0x6e, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x64, 0xf8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfe, 0x62, 0x60, 0x64, 0x7c, 0x64, 0x60, 0x60, 0x62, 0xfe, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfe, 0x62, 0x60, 0x64, 0x7c, 0x64, 0x60, 0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x66, 0xc2, 0xc0, 0xce, 0xc6, 0xc6, 0xc6, 0xe4, 0x78, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe7, 0x66, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x66, 0xe7, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xd8, 0x70, 0x00, 0x00,
0x00, 0x00, 0xe7, 0x62, 0x62, 0x64, 0x68, 0x7c, 0x6e, 0x66, 0x66, 0xe7, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xf0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0xfe, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe7, 0x66, 0x76, 0x7e, 0x7e, 0x56, 0x46, 0x46, 0x46, 0xef, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe7, 0x62, 0x72, 0x72, 0x5a, 0x5a, 0x4e, 0x4e, 0x46, 0xe6, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x4e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xe4, 0x78, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfc, 0x66, 0x66, 0x66, 0x64, 0x78, 0x60, 0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x4e, 0xc6, 0xc6, 0xc6, 0xc6, 0xd6, 0xd6, 0xf4, 0x78, 0x0e, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfc, 0x66, 0x66, 0x66, 0x6c, 0x78, 0x64, 0x66, 0x66, 0xe7, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7a, 0xc6, 0xc2, 0xe0, 0x70, 0x1c, 0x0e, 0x86, 0xce, 0xbc, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xff, 0xdb, 0x99, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe3, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x72, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe3, 0x62, 0x64, 0x64, 0x68, 0x68, 0x70, 0x70, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe3, 0x62, 0x62, 0x6a, 0x6a, 0x7e, 0x7e, 0x7e, 0x6c, 0x68, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xf7, 0x62, 0x62, 0x74, 0x38, 0x1c, 0x2e, 0x46, 0x46, 0xef, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe3, 0x62, 0x74, 0x34, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfe, 0x86, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0xc2, 0xfe, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x10, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x8c, 0x1c, 0x6c, 0xce, 0xdc, 0x68, 0x00, 0x00, 0x00, 0x00,
0x00, 0x20, 0x60, 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0x66, 0x64, 0x58, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x26, 0x60, 0x60, 0x62, 0x64, 0x38, 0x00, 0x00, 0x00, 0x00,
0x00, 0x04, 0x0c, 0x1c, 0x0c, 0x3c, 0x4c, 0xcc, 0xcc, 0xcc, 0xdc, 0x6e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x22, 0x64, 0x78, 0x72, 0x64, 0x38, 0x00, 0x00, 0x00, 0x00,
0x00, 0x06, 0x0f, 0x16, 0x30, 0x7c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x06, 0x3a, 0x4c, 0x64, 0x38, 0x7c, 0x8e, 0x66, 0x62, 0x3c, 0x00, 0x00,
0x00, 0x20, 0x60, 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0x66, 0x66, 0xe7, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0c, 0x00, 0x00, 0x04, 0x0c, 0x1c, 0x0c, 0x0c, 0x0c, 0x1e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0c, 0x00, 0x00, 0x04, 0x0c, 0x1c, 0x0c, 0x0c, 0x0c, 0x0c, 0x68, 0x70, 0x00, 0x00,
0x00, 0x20, 0x60, 0xe0, 0x60, 0x6e, 0x64, 0x68, 0x70, 0x78, 0x6c, 0xee, 0x00, 0x00, 0x00, 0x00,
0x00, 0x08, 0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x7f, 0xeb, 0x6b, 0x6b, 0x6b, 0xeb, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x76, 0xe6, 0x66, 0x66, 0x66, 0xe7, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x26, 0x66, 0x66, 0x66, 0x64, 0x38, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x76, 0xe6, 0x66, 0x64, 0x78, 0x60, 0x60, 0xf0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x4c, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0x0c, 0x1e, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x06, 0x4f, 0xf6, 0x60, 0x60, 0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x32, 0x38, 0x1c, 0x0e, 0x26, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x10, 0x30, 0x7e, 0x30, 0x30, 0x30, 0x32, 0x34, 0x18, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x66, 0x66, 0x66, 0x67, 0x6e, 0x34, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 0x64, 0x68, 0x68, 0x70, 0x70, 0x60, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0x62, 0x6a, 0x6e, 0x7e, 0x6c, 0x48, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x64, 0x38, 0x38, 0x38, 0x4c, 0xee, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x62, 0x36, 0x3c, 0x1c, 0x08, 0x10, 0x70, 0x60, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x46, 0x0c, 0x18, 0x30, 0x62, 0x7e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0e, 0x18, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x00, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x70, 0x18, 0x18, 0x18, 0x18, 0x0e, 0x18, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x32, 0x7e, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0x82, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1e, 0x33, 0x61, 0x60, 0x60, 0x61, 0x33, 0x1e, 0x06, 0x03, 0x3e, 0x00, 0x00, 0x00,
0x00, 0x00, 0x66, 0x66, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x06, 0x0c, 0x18, 0x00, 0x3e, 0x63, 0x7f, 0x60, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x08, 0x1c, 0x36, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x66, 0x66, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x30, 0x18, 0x0c, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1c, 0x36, 0x1c, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3c, 0x66, 0x60, 0x66, 0x3c, 0x0c, 0x06, 0x3c, 0x00, 0x00, 0x00, 0x00,
0x00, 0x08, 0x1c, 0x36, 0x00, 0x3e, 0x63, 0x7f, 0x60, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x66, 0x66, 0x00, 0x3e, 0x63, 0x7f, 0x60, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x30, 0x18, 0x0c, 0x00, 0x3e, 0x63, 0x7f, 0x60, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x66, 0x66, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x3c, 0x66, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x60, 0x30, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x63, 0x63, 0x08, 0x1c, 0x36, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1c, 0x36, 0x1c, 0x00, 0x1c, 0x36, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0c, 0x18, 0x30, 0x00, 0x7f, 0x33, 0x30, 0x3e, 0x30, 0x33, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x6e, 0x3b, 0x1b, 0x7e, 0xd8, 0xdc, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1f, 0x36, 0x66, 0x66, 0x7f, 0x66, 0x66, 0x66, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x08, 0x1c, 0x36, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x63, 0x63, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x30, 0x18, 0x0c, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x3c, 0x66, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x30, 0x18, 0x0c, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x63, 0x63, 0x00, 0x63, 0x63, 0x63, 0x63, 0x3f, 0x03, 0x06, 0x3c, 0x00, 0x00, 0x00,
0x00, 0x63, 0x63, 0x1c, 0x36, 0x63, 0x63, 0x63, 0x63, 0x36, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x63, 0x63, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x18, 0x7e, 0xc3, 0xc0, 0xc0, 0xc3, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1c, 0x36, 0x32, 0x30, 0x78, 0x30, 0x30, 0x30, 0x73, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0xff, 0x18, 0xff, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xfc, 0x66, 0x66, 0x7c, 0x62, 0x66, 0x6f, 0x66, 0x66, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0e, 0x1b, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x18, 0xd8, 0x70, 0x00, 0x00, 0x00,
0x00, 0x0c, 0x18, 0x30, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0c, 0x18, 0x30, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0c, 0x18, 0x30, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0c, 0x18, 0x30, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3b, 0x6e, 0x00, 0x6e, 0x33, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
0x3b, 0x6e, 0x00, 0x63, 0x73, 0x7b, 0x7f, 0x6f, 0x67, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3c, 0x6c, 0x6c, 0x3e, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x60, 0xe0, 0x63, 0x66, 0x6c, 0x18, 0x30, 0x6e, 0xc3, 0x06, 0x0c, 0x1f, 0x00, 0x00, 0x00,
0x00, 0x60, 0xe0, 0x63, 0x66, 0x6c, 0x18, 0x33, 0x67, 0xcf, 0x1f, 0x03, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x3c, 0x3c, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1b, 0x36, 0x6c, 0x36, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x6c, 0x36, 0x1b, 0x36, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44,
0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa,
0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x06, 0xf6, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x06, 0xf6, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x06, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x30, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x30, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x36, 0x36, 0x36, 0x36, 0x36, 0xf7, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xf7, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x30, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x36, 0x36, 0x36, 0x36, 0x36, 0xf7, 0x00, 0xf7, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x18, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xff, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x6e, 0x6c, 0x6c, 0x6e, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x7e, 0x63, 0x63, 0x7e, 0x60, 0x60, 0x20, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7f, 0x63, 0x63, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x7f, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7f, 0x63, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x63, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x6c, 0x6c, 0x6c, 0x6c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x3e, 0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3b, 0x6e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7e, 0x18, 0x3c, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1c, 0x36, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x36, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1c, 0x36, 0x63, 0x63, 0x63, 0x36, 0x36, 0x36, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1e, 0x30, 0x18, 0x0c, 0x3e, 0x66, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xdb, 0xdb, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0x06, 0x7e, 0xdb, 0xdb, 0xf3, 0x7e, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1c, 0x30, 0x60, 0x60, 0x7c, 0x60, 0x60, 0x30, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x30, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0c, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0c, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0e, 0x1b, 0x1b, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00,
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xd8, 0xd8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0xff, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3b, 0x6e, 0x00, 0x3b, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xec, 0x6c, 0x3c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xd8, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x70, 0xd8, 0x30, 0x60, 0xc8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
}; 


struct drv_video_font_t         drv_video_8x16ant_font = {
  8, 16,
  drv_video_8x16ant_fnt,
  FONT_FLAG_NONE
 };

