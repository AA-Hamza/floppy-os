#ifndef BIRD_IMG_H
#define  BIRD_IMG_H

#define BIRD_OUTER 0x11
#define BIRD_EYEEE 0x0F
#define BIRD_MOUTH 0x04
#define BIRD_WINGG 0x43
#define BIRD_BODYY 0x2C

unsigned char bird_img[16][16] = {
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, BIRD_OUTER, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_EYEEE, BIRD_EYEEE, BIRD_OUTER, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_EYEEE, BIRD_EYEEE, BIRD_EYEEE, BIRD_EYEEE, BIRD_OUTER, 0x00000000, 0x00000000, 0x00000000},
    {BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_EYEEE, BIRD_EYEEE, BIRD_EYEEE, BIRD_OUTER, BIRD_EYEEE, BIRD_OUTER, 0x00000000, 0x00000000},
    {BIRD_OUTER, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_EYEEE, BIRD_EYEEE, BIRD_EYEEE, BIRD_OUTER, BIRD_EYEEE, BIRD_OUTER, 0x00000000, 0x00000000},
    {BIRD_OUTER, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_EYEEE, BIRD_EYEEE, BIRD_EYEEE, BIRD_EYEEE, BIRD_OUTER, 0x00000000, 0x00000000},
    {BIRD_OUTER, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, 0x00000000},
    {BIRD_OUTER, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_OUTER},
    {BIRD_OUTER, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_WINGG, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_OUTER},
    {0x00000000, BIRD_OUTER, BIRD_WINGG, BIRD_WINGG, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_MOUTH, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, 0x00000000},
    {0x00000000, BIRD_OUTER, BIRD_WINGG, BIRD_WINGG, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_OUTER, 0x00000000},
    {0x00000000, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_MOUTH, BIRD_OUTER, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, BIRD_OUTER, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_BODYY, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, BIRD_OUTER, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

/*
unsigned char bird_img[16][16] = {
    {0xe4, 0xe4, 0xe4, 0xe7, 0x00, 0x84, 0xa4, 0xa5, 0xa6, 0xaf, 0xd8, 0xea, 0xe7, 0xe4, 0xe4, 0x2e},
    {0xe4, 0xe4, 0xe7, 0xd8, 0x78, 0xa9, 0x50, 0x4f, 0x4e, 0x09, 0xae, 0x78, 0xed, 0xe4, 0xe4, 0x2e},
    {0xe4, 0xe4, 0xf0, 0x74, 0x28, 0xc8, 0x28, 0x20, 0xfe, 0xb6, 0x22, 0xf0, 0xd8, 0xe7, 0xe4, 0x2e},
    {0xe4, 0xf9, 0xcf, 0xe2, 0xc7, 0xf4, 0x28, 0x2b, 0xdc, 0x29, 0xe8, 0xf3, 0x48, 0x00, 0xe4, 0x2e},
    {0x00, 0x92, 0xc8, 0x12, 0xfc, 0x34, 0x26, 0x2a, 0xa0, 0x7a, 0xae, 0x5d, 0x7e, 0xe7, 0xf6, 0x2e},
    {0x24, 0x11, 0xe1, 0xf4, 0xe9, 0x83, 0x30, 0x2a, 0x9d, 0x83, 0x78, 0xde, 0xc9, 0x4e, 0x00, 0x2e},
    {0xfd, 0x63, 0x3d, 0x39, 0xc4, 0xd0, 0xe9, 0x2d, 0xfa, 0x07, 0x91, 0x75, 0xc6, 0x60, 0x00, 0x2e},
    {0x12, 0x5f, 0x30, 0x25, 0x32, 0x54, 0xee, 0x34, 0x18, 0xaf, 0x81, 0xcf, 0x9c, 0x44, 0xed, 0x2e},
    {0x09, 0x61, 0x31, 0x25, 0x33, 0x57, 0xe9, 0x32, 0x2a, 0xe0, 0x69, 0x44, 0x22, 0x19, 0xfd, 0x2f},
    {0x76, 0xfa, 0xd0, 0x3f, 0xcb, 0xd5, 0xda, 0x29, 0x2b, 0xe5, 0x1a, 0x34, 0x35, 0x3b, 0xdb, 0x24},
    {0x00, 0xe9, 0x02, 0x04, 0x03, 0x6f, 0x30, 0x2a, 0x52, 0xcb, 0xca, 0xcb, 0xc9, 0xd3, 0x31, 0x27},
    {0xe4, 0xf9, 0x36, 0x96, 0x74, 0x34, 0x29, 0x2a, 0x02, 0xf6, 0x80, 0x6b, 0x6e, 0x26, 0xe2, 0x2f},
    {0xe4, 0xe4, 0x00, 0x90, 0xc7, 0xe7, 0x0a, 0x29, 0x24, 0xa6, 0x4f, 0x77, 0x7b, 0xa6, 0xc9, 0x2f},
    {0xe4, 0xe4, 0xe7, 0xf3, 0x23, 0x1f, 0x13, 0x33, 0x2b, 0xe7, 0x44, 0x19, 0x1a, 0x09, 0xd9, 0x2f},
    {0xe4, 0xe4, 0xe4, 0xea, 0xc4, 0x56, 0x61, 0x64, 0x63, 0x89, 0x18, 0x49, 0x42, 0x43, 0xab, 0x2e},
    {0xe4, 0xe4, 0xe4, 0xe4, 0xea, 0x00, 0x47, 0x79, 0x7a, 0x96, 0xd8, 0x00, 0xf9, 0xf9, 0xed, 0x2e},
};
*/

/*
unsigned char bird_img[16*16] = {
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,},
};
*/
#endif
