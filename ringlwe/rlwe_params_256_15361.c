/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * See LICENSE for complete information.
 */
#include <inttypes.h>
#include "rlwe_params_256_15361.h"

const RINGELT m = 256;

const RINGELT q = 15361;
	
const RINGELT muwords = 4; /* key (mu) is m bits */
const RINGELT recwords = 4; /* reconciliation vector is m bits */

#ifdef UNIFORM
const RINGELT B = 5, BB = 11, LOG2B = 4, BMASK = 0xf;

const RINGELT small_coeff_table[11] = {15356, 15357, 15358, 15359, 15360, 0, 1, 2, 3, 4, 5};
#endif

#ifdef NHRECONCILE
        #error "Compiling without NH reconcile parameters"
#else
const RINGELT qmod4 = 1;
const RINGELT q_1_4 = 3840, q_2_4 = 7680, q_3_4 = 11521;
const RINGELT r0_l = 5760, r0_u = 13441, r1_l = 1919, r1_u = 9601;
#endif


/* Public Parameter a. Each a parameter rejection sampled from non-overlapping
 * segments of the digits of e.
 * Note that this is held in the FFT / CRT basis.*/
const RINGELT a[256] = {
        0x3BCD, 0x10F1, 0x26ED, 0x1C03, 0x3436, 0x2CD7, 0x2BAB, 0x2EEB, 
        0x3214, 0x10F3, 0x25D8, 0x355D, 0x1E6F, 0x2C21, 0x1F14, 0x2AF6, 
        0x008C, 0x1908, 0x19A5, 0x1A58, 0x11D2, 0x2F29, 0x0D49, 0x133D, 
        0x15BD, 0x18AD, 0x04AA, 0x2C46, 0x1ED6, 0x3515, 0x0881, 0x27EB, 
        0x30B7, 0x2D82, 0x066B, 0x09E2, 0x14A8, 0x216F, 0x06ED, 0x136A, 
        0x22BC, 0x1741, 0x0B08, 0x0774, 0x2DD3, 0x1D93, 0x1009, 0x1EC4, 
        0x1AD6, 0x0595, 0x1A42, 0x2EE7, 0x31FF, 0x0785, 0x300B, 0x3317, 
        0x1026, 0x3AA4, 0x18F0, 0x3022, 0x2810, 0x01D5, 0x084D, 0x0997, 
        0x1B03, 0x24C8, 0x084C, 0x0EC5, 0x11A9, 0x2D17, 0x1581, 0x3736, 
        0x3709, 0x0EBF, 0x2269, 0x14BA, 0x0651, 0x313E, 0x107B, 0x1FCD, 
        0x013E, 0x1EFC, 0x197C, 0x398C, 0x1157, 0x16E0, 0x1311, 0x10D3, 
        0x111D, 0x382E, 0x3720, 0x1696, 0x0278, 0x0122, 0x1487, 0x134D, 
        0x0A31, 0x1735, 0x1F48, 0x06F3, 0x38EE, 0x0BDF, 0x2B55, 0x3338, 
        0x164E, 0x29CA, 0x3A78, 0x06F3, 0x2D6D, 0x1A15, 0x01E3, 0x1773, 
        0x0DD1, 0x2C8E, 0x3758, 0x06CB, 0x04DC, 0x3A04, 0x0351, 0x0D3A, 
        0x1544, 0x3A4A, 0x2DA6, 0x0A66, 0x0B02, 0x0934, 0x39E0, 0x341B, 
        0x01F7, 0x125E, 0x2459, 0x3A44, 0x1368, 0x0B69, 0x28B9, 0x0FAA, 
        0x0C94, 0x31F2, 0x2207, 0x0805, 0x0A8C, 0x3B5E, 0x256C, 0x0CD4, 
        0x2985, 0x2BE7, 0x22A3, 0x16BD, 0x065C, 0x23B8, 0x07F3, 0x1B70, 
        0x25DD, 0x1618, 0x0E04, 0x276A, 0x2C46, 0x1624, 0x3235, 0x074F, 
        0x2020, 0x1C29, 0x1237, 0x190F, 0x3BD1, 0x1B13, 0x3971, 0x313E, 
        0x151E, 0x1AAB, 0x226E, 0x24E9, 0x1270, 0x0F01, 0x3B9D, 0x0E96, 
        0x0ED0, 0x3499, 0x0C67, 0x20D9, 0x1464, 0x0809, 0x2811, 0x2298, 
        0x2C41, 0x29AE, 0x167B, 0x05C0, 0x2A3C, 0x1FDB, 0x1B15, 0x3773, 
        0x14D6, 0x0A16, 0x3025, 0x1A7E, 0x0D79, 0x1F69, 0x2D3F, 0x06DA, 
        0x17BD, 0x0045, 0x1160, 0x07AB, 0x165D, 0x3370, 0x32D2, 0x13A2, 
        0x2EB6, 0x0CCA, 0x38AB, 0x358F, 0x2838, 0x3745, 0x393D, 0x2F2F, 
        0x1A3B, 0x0A76, 0x1DC9, 0x3563, 0x1497, 0x2383, 0x300A, 0x0151, 
        0x3A27, 0x17E7, 0x1813, 0x0058, 0x0FDA, 0x0E3B, 0x0758, 0x2FD2, 
        0x37FC, 0x2DB4, 0x16FB, 0x007A, 0x28EB, 0x2F15, 0x0D45, 0x1281, 
        0x15B7, 0x0E37, 0x1B97, 0x36EA, 0x20A8, 0x0531, 0x2F91, 0x2674, 
        0x19D0, 0x2D46, 0x30BF, 0x1C53, 0x04F3, 0x0E06, 0x0D48, 0x03B0
        };

