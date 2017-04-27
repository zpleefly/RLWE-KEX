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
#include "rlwe_params_512_12289.h"

const RINGELT m = 512;

const RINGELT q = 12289;

const RINGELT muwords = 4; /* key (mu) is 256 bits */
const RINGELT recwords = 16; /* reconciliation vector is 2*m bits */

#ifdef BINOMIAL
const RINGELT BINOMK = 24; // Binomial sampling parameter
#endif

#ifdef NHRECONCILE
const RINGELT rdim = 2; // rdim is number of coeffs per keybit
const RINGELT rsize = 2; // rsize is number of encoding bits per coeff per keybit
#else
const RINGELT qmod4 = 1;
const RINGELT q_1_4 = 3072, q_2_4 = 6144, q_3_4 = 9217;
const RINGELT r0_l = 4608, r0_u = 10753, r1_l = 1535, r1_u = 7681;
#endif


/* Public Parameter a. Each a parameter rejection sampled from non-overlapping
 * segments of the digits of e.
 * Note that this is held in the FFT / CRT basis.*/
const RINGELT a[512] = {
	0x0343, 0x111D, 0x0D8C, 0x1190, 0x01D7, 0x1396, 0x036D, 0x2B76, 
	0x10D0, 0x0BE2, 0x1536, 0x0D49, 0x2723, 0x1E74, 0x08AE, 0x277D, 
	0x0AD4, 0x14DD, 0x042E, 0x111F, 0x20FF, 0x291B, 0x224F, 0x1A27, 
	0x0FC9, 0x0F65, 0x0919, 0x0850, 0x269B, 0x2457, 0x2D3A, 0x2F19, 
	0x0B1B, 0x1593, 0x1B4B, 0x1CED, 0x1C24, 0x218E, 0x1FCA, 0x14D9, 
	0x241D, 0x1C5E, 0x2223, 0x12EC, 0x0B0B, 0x0E55, 0x0BB3, 0x2832, 
	0x24F5, 0x282C, 0x25B4, 0x1FF5, 0x2F78, 0x03FE, 0x1416, 0x28E4, 
	0x1309, 0x180A, 0x0B04, 0x2694, 0x27F2, 0x2570, 0x2FF8, 0x1C66, 
	0x0B76, 0x2127, 0x2E1F, 0x15D2, 0x1C59, 0x1D64, 0x122A, 0x013D, 
	0x1C19, 0x246A, 0x12FC, 0x093B, 0x098E, 0x2EB8, 0x285B, 0x29F1, 
	0x0F70, 0x22A1, 0x0C40, 0x2EA7, 0x0EEC, 0x2876, 0x124E, 0x137A, 
	0x0A55, 0x270C, 0x1B05, 0x22F2, 0x221C, 0x02DA, 0x0E19, 0x08FC, 
	0x08DE, 0x23F9, 0x1800, 0x2432, 0x26BF, 0x005A, 0x2058, 0x2D55, 
	0x081B, 0x05D0, 0x074C, 0x24F9, 0x255E, 0x220A, 0x0AA7, 0x00C4, 
	0x02E3, 0x20B7, 0x29F4, 0x1D61, 0x050B, 0x1AB0, 0x2EB2, 0x22FD, 
	0x1CC5, 0x07DD, 0x06EC, 0x0480, 0x10BD, 0x1C7D, 0x0531, 0x177D, 
	0x1F19, 0x2989, 0x2211, 0x22EF, 0x1C80, 0x07EE, 0x1711, 0x24B9, 
	0x2D3D, 0x00B9, 0x0BDF, 0x196B, 0x1890, 0x17EE, 0x2BD3, 0x25AD, 
	0x2BC6, 0x2097, 0x13E6, 0x0FC2, 0x0DE0, 0x1A40, 0x255D, 0x0870, 
	0x0EC8, 0x26EF, 0x0D9E, 0x0E3B, 0x26F3, 0x060F, 0x05A2, 0x1405, 
	0x1D6F, 0x0AC0, 0x0DD7, 0x038F, 0x0ABC, 0x00F6, 0x16E3, 0x1804, 
	0x0517, 0x1113, 0x1AFF, 0x0502, 0x2455, 0x004E, 0x0265, 0x1B95, 
	0x15E5, 0x2A54, 0x2CB2, 0x28C3, 0x1A0A, 0x110A, 0x0F95, 0x2F31, 
	0x2E1D, 0x295B, 0x0803, 0x0D08, 0x0DE0, 0x14F5, 0x20F0, 0x243C, 
	0x1BA8, 0x260A, 0x1AF6, 0x1B97, 0x2F82, 0x21D9, 0x247A, 0x2C26, 
	0x26D9, 0x022D, 0x2EB3, 0x180B, 0x1B10, 0x261C, 0x139E, 0x20F5, 
	0x0BF0, 0x2D72, 0x2523, 0x0338, 0x0AF2, 0x20B2, 0x2D1F, 0x05B5, 
	0x29AA, 0x2E36, 0x0475, 0x0A82, 0x2902, 0x01EE, 0x121A, 0x034A, 
	0x07EF, 0x2D13, 0x0B89, 0x0C07, 0x2E31, 0x1679, 0x0C7E, 0x0478, 
	0x1162, 0x266A, 0x00B3, 0x2180, 0x26FD, 0x178C, 0x1FC8, 0x2C5D, 
	0x0506, 0x0051, 0x2465, 0x10BE, 0x1619, 0x081A, 0x2558, 0x2DE6, 
	0x1FA4, 0x2513, 0x1852, 0x0E97, 0x075F, 0x0E0D, 0x1728, 0x01F7, 
	0x0BE4, 0x00BA, 0x2EF0, 0x1C43, 0x2C5A, 0x08BA, 0x0A81, 0x109C, 
	0x27BF, 0x25EE, 0x0BD7, 0x2778, 0x1C34, 0x1C04, 0x0788, 0x2ADA, 
	0x1736, 0x2CAA, 0x2FB5, 0x0F2C, 0x2C18, 0x2F2F, 0x2847, 0x1FF8, 
	0x193B, 0x2B41, 0x2FA4, 0x19E0, 0x0573, 0x10BF, 0x1C9D, 0x2C6F, 
	0x2887, 0x2F13, 0x0B34, 0x2F3C, 0x22E6, 0x17C3, 0x029F, 0x20E4, 
	0x2F23, 0x0CA4, 0x059C, 0x2150, 0x0D72, 0x0608, 0x1F3E, 0x05B6, 
	0x0048, 0x244A, 0x0BA9, 0x103A, 0x239E, 0x240F, 0x1C00, 0x21A3, 
	0x05F5, 0x0128, 0x1D65, 0x10EA, 0x0FB4, 0x17A7, 0x2A9E, 0x2EF1, 
	0x0E77, 0x0E33, 0x0466, 0x1362, 0x0FC6, 0x0C20, 0x0B38, 0x0A01, 
	0x0D83, 0x0226, 0x25AE, 0x2207, 0x0678, 0x0B1F, 0x2891, 0x1E43, 
	0x101E, 0x155A, 0x0820, 0x1D08, 0x15F9, 0x01CD, 0x0A7A, 0x1CA7, 
	0x14E1, 0x1844, 0x19E9, 0x10CE, 0x175B, 0x17F8, 0x0500, 0x2D62, 
	0x116C, 0x1098, 0x110C, 0x0EC3, 0x0A32, 0x010D, 0x0D21, 0x2322, 
	0x1AE3, 0x1083, 0x10EA, 0x0C5A, 0x253C, 0x1DD8, 0x079E, 0x115A, 
	0x17F8, 0x1717, 0x247A, 0x091B, 0x21D0, 0x2B10, 0x08D6, 0x0C42, 
	0x1FBF, 0x0CDB, 0x2A0F, 0x1AE3, 0x064F, 0x2B75, 0x20E8, 0x1B20, 
	0x151C, 0x1678, 0x125F, 0x0A20, 0x0696, 0x1E53, 0x15CC, 0x0962, 
	0x2CE3, 0x0635, 0x2D12, 0x2B20, 0x284A, 0x2884, 0x0FED, 0x0099, 
	0x1B83, 0x09EB, 0x223A, 0x2B98, 0x2C92, 0x12E0, 0x1174, 0x2358, 
	0x0215, 0x2885, 0x0955, 0x0A0A, 0x0BA7, 0x1E3B, 0x1AB6, 0x05CC, 
	0x1104, 0x286A, 0x1809, 0x1620, 0x093A, 0x2E12, 0x126B, 0x2DFA, 
	0x15FC, 0x03AB, 0x15AD, 0x2AF6, 0x0F9B, 0x26F3, 0x25D9, 0x1781, 
	0x1653, 0x02FE, 0x0C0B, 0x0D1A, 0x0846, 0x02FE, 0x242F, 0x1B61, 
	0x2533, 0x2DFF, 0x17EA, 0x13E7, 0x1B1F, 0x15B7, 0x196D, 0x0742, 
	0x2EBE, 0x0119, 0x2BA8, 0x09C8, 0x2419, 0x0A4C, 0x2A94, 0x1E6D, 
	0x137B, 0x2A00, 0x1570, 0x2673, 0x0C43, 0x1EB1, 0x000F, 0x0D5F, 
	0x0EAC, 0x1088, 0x26BD, 0x00A2, 0x035E, 0x0765, 0x1A0F, 0x0C34, 
	0x0C88, 0x0A4A, 0x0368, 0x1B6C, 0x1F71, 0x02A0, 0x2CE2, 0x1F3C, 
	0x1D4C, 0x24AF, 0x13A5, 0x1BAB, 0x1BAB, 0x22A2, 0x17FA, 0x18CB, 
	0x24B7, 0x15AC, 0x18D3, 0x0978, 0x2385, 0x2ED8, 0x0548, 0x2EDC, 
	0x2CA9, 0x117E, 0x0638, 0x136D, 0x1DC1, 0x1FCE, 0x1A18, 0x0AE0, 
	0x2C3F, 0x2618, 0x0F6A, 0x1DAB, 0x2BF4, 0x091A, 0x2F07, 0x1EBC
        };

