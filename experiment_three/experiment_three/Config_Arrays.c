
#include <avr/io.h>
#include <avr/pgmspace.h>

// STA013 Configuration Register Addresses
#define PCM_DIV 0x54
#define PCMCONF 0x55
#define RES1 0x06
#define RES2 0x0B
#define PLLFRAC_441_H 0x52
#define PLLFRAC_441_L 0x51
#define PLLFRAC_H 0x65
#define PLLFRAC_L 0x64
#define MFSDF_441 0x50
#define MFSDF 0x61
#define PLLCTL 0x05

#define SCLK_POL 0x0D
#define DATA_REQ_ENABLE 0x18
#define REQ_POL 0x0C
#define DLA 0x46
#define DRA 0x48
#define RUN 0x72

const  uint8_t CONFIG[3998] PROGMEM = 
{  58, 1,
   42, 4,
   40, 0,
   41, 0,
   32, 0,
   33, 0,
   34, 0,
   35, 0,
   36, 0,
   37, 0,
   38, 0,
   39, 0,
   40, 1,
   40, 2,
   33, 143,
   40, 3,
   33, 0,
   40, 4,
   40, 5,
   40, 6,
   40, 7,
   40, 8,
   40, 9,
   40, 10,
   40, 11,
   40, 12,
   32, 128,
   33, 144,
   40, 13,
   32, 0,
   33, 0,
   40, 14,
   32, 129,
   33, 145,
   40, 15,
   32, 0,
   33, 146,
   40, 16,
   33, 0,
   40, 17,
   33, 147,
   40, 18,
   33, 0,
   40, 19,
   40, 20,
   40, 21,
   32, 130,
   40, 22,
   32, 0,
   40, 23,
   40, 24,
   40, 25,
   33, 148,
   40, 26,
   33, 149,
   40, 27,
   33, 150,
   40, 28,
   33, 0,
   40, 29,
   32, 131,
   40, 30,
   32, 0,
   40, 31,
   33, 151,
   40, 32,
   33, 0,
   40, 33,
   40, 34,
   40, 35,
   40, 36,
   40, 37,
   40, 38,
   40, 39,
   40, 40,
   40, 41,
   40, 42,
   32, 132,
   40, 43,
   32, 0,
   40, 44,
   40, 45,
   40, 46,
   40, 47,
   40, 48,
   40, 49,
   40, 50,
   32, 133,
   40, 51,
   32, 0,
   40, 52,
   40, 53,
   40, 54,
   40, 55,
   33, 152,
   40, 56,
   33, 0,
   40, 57,
   40, 58,
   40, 59,
   40, 60,
   40, 61,
   40, 62,
   40, 63,
   40, 64,
   40, 65,
   40, 66,
   40, 67,
   40, 68,
   40, 69,
   40, 70,
   40, 71,
   40, 72,
   40, 73,
   40, 74,
   40, 75,
   40, 76,
   40, 77,
   40, 78,
   40, 79,
   40, 80,
   40, 81,
   40, 82,
   40, 83,
   40, 84,
   40, 85,
   40, 86,
   40, 87,
   40, 88,
   40, 89,
   40, 90,
   40, 91,
   40, 92,
   40, 93,
   40, 94,
   40, 95,
   40, 96,
   40, 97,
   40, 98,
   33, 153,
   40, 99,
   33, 0,
   40, 100,
   40, 101,
   40, 102,
   40, 103,
   40, 104,
   40, 105,
   40, 106,
   40, 107,
   40, 108,
   40, 109,
   40, 110,
   40, 111,
   40, 112,
   40, 113,
   40, 114,
   40, 115,
   40, 116,
   40, 117,
   40, 118,
   40, 119,
   40, 120,
   40, 121,
   40, 122,
   40, 123,
   40, 124,
   40, 125,
   40, 126,
   40, 127,
   40, 128,
   40, 129,
   40, 130,
   40, 131,
   40, 132,
   40, 133,
   40, 134,
   40, 135,
   40, 136,
   40, 137,
   40, 138,
   40, 139,
   40, 140,
   40, 141,
   40, 142,
   40, 143,
   40, 144,
   40, 145,
   32, 134,
   40, 146,
   32, 135,
   40, 147,
   32, 0,
   40, 148,
   40, 149,
   40, 150,
   40, 151,
   40, 152,
   40, 153,
   40, 154,
   40, 155,
   40, 156,
   40, 157,
   40, 158,
   40, 159,
   33, 154,
   40, 160,
   33, 0,
   40, 161,
   40, 162,
   40, 163,
   40, 164,
   40, 165,
   40, 166,
   40, 167,
   40, 168,
   40, 169,
   40, 170,
   40, 171,
   40, 172,
   40, 173,
   40, 174,
   40, 175,
   40, 176,
   40, 177,
   40, 178,
   40, 179,
   40, 180,
   40, 181,
   40, 182,
   40, 183,
   40, 184,
   40, 185,
   32, 136,
   40, 186,
   32, 0,
   40, 187,
   32, 137,
   40, 188,
   32, 0,
   40, 189,
   40, 190,
   40, 191,
   40, 192,
   40, 193,
   40, 194,
   40, 195,
   33, 155,
   40, 196,
   33, 0,
   40, 197,
   40, 198,
   40, 199,
   40, 200,
   40, 201,
   40, 202,
   40, 203,
   40, 204,
   40, 205,
   40, 206,
   40, 207,
   40, 208,
   40, 209,
   40, 210,
   40, 211,
   40, 212,
   40, 213,
   40, 214,
   40, 215,
   40, 216,
   40, 217,
   40, 218,
   40, 219,
   40, 220,
   40, 221,
   40, 222,
   40, 223,
   40, 224,
   40, 225,
   32, 138,
   40, 226,
   32, 139,
   40, 227,
   32, 0,
   40, 228,
   40, 229,
   40, 230,
   40, 231,
   40, 232,
   40, 233,
   40, 234,
   40, 235,
   40, 236,
   40, 237,
   40, 238,
   40, 239,
   40, 240,
   40, 241,
   40, 242,
   40, 243,
   40, 244,
   40, 245,
   40, 246,
   40, 247,
   40, 248,
   32, 140,
   40, 249,
   32, 0,
   33, 156,
   40, 250,
   33, 157,
   40, 251,
   32, 141,
   33, 158,
   40, 252,
   32, 142,
   33, 159,
   40, 253,
   32, 0,
   33, 0,
   40, 254,
   40, 255,
   42, 1,
   40, 0,
   34, 1,
   35, 149,
   36, 137,
   37, 7,
   38, 164,
   39, 7,
   40, 1,
   33, 199,
   34, 0,
   35, 128,
   38, 196,
   39, 12,
   40, 2,
   32, 9,
   33, 28,
   34, 4,
   38, 170,
   39, 10,
   40, 3,
   32, 0,
   33, 0,
   34, 0,
   35, 166,
   38, 160,
   39, 7,
   40, 4,
   40, 5,
   32, 5,
   35, 132,
   38, 180,
   39, 9,
   40, 6,
   32, 0,
   34, 3,
   35, 0,
   36, 129,
   37, 192,
   38, 171,
   39, 10,
   40, 7,
   33, 174,
   34, 0,
   35, 149,
   36, 137,
   37, 7,
   38, 164,
   39, 0,
   40, 8,
   33, 72,
   34, 1,
   35, 128,
   38, 196,
   39, 12,
   40, 9,
   32, 9,
   33, 4,
   34, 4,
   38, 170,
   39, 10,
   40, 10,
   32, 0,
   33, 0,
   34, 0,
   35, 168,
   38, 164,
   39, 7,
   40, 11,
   40, 12,
   33, 64,
   34, 32,
   35, 128,
   38, 196,
   39, 12,
   40, 13,
   34, 36,
   38, 198,
   40, 14,
   33, 158,
   34, 0,
   38, 200,
   40, 15,
   32, 9,
   33, 2,
   34, 20,
   38, 170,
   39, 10,
   40, 16,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 17,
   32, 0,
   33, 1,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   39, 10,
   40, 18,
   33, 195,
   35, 149,
   36, 137,
   37, 7,
   38, 32,
   39, 0,
   40, 19,
   32, 3,
   33, 194,
   35, 131,
   38, 38,
   39, 13,
   40, 20,
   33, 179,
   34, 8,
   40, 21,
   32, 0,
   33, 198,
   34, 0,
   35, 149,
   38, 0,
   39, 8,
   40, 22,
   33, 0,
   35, 0,
   36, 150,
   37, 3,
   38, 170,
   39, 10,
   40, 23,
   32, 66,
   33, 182,
   35, 128,
   36, 137,
   37, 7,
   40, 24,
   32, 0,
   33, 0,
   35, 148,
   38, 14,
   40, 25,
   32, 15,
   35, 132,
   38, 180,
   39, 9,
   40, 26,
   32, 0,
   35, 147,
   38, 168,
   39, 3,
   40, 27,
   38, 40,
   39, 0,
   40, 28,
   33, 1,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   39, 10,
   40, 29,
   33, 197,
   35, 149,
   36, 137,
   37, 7,
   38, 32,
   39, 0,
   40, 30,
   33, 0,
   35, 148,
   38, 0,
   39, 10,
   40, 31,
   38, 14,
   40, 32,
   32, 3,
   33, 121,
   34, 1,
   35, 131,
   38, 38,
   39, 13,
   40, 33,
   33, 50,
   40, 34,
   32, 0,
   33, 4,
   34, 0,
   35, 128,
   36, 0,
   37, 252,
   38, 170,
   39, 10,
   40, 35,
   33, 0,
   35, 0,
   37, 0,
   40, 36,
   33, 163,
   34, 13,
   35, 128,
   36, 158,
   37, 59,
   40, 37,
   32, 66,
   33, 87,
   34, 1,
   36, 137,
   37, 7,
   40, 38,
   32, 0,
   33, 67,
   34, 13,
   36, 0,
   37, 56,
   40, 39,
   33, 8,
   34, 152,
   35, 149,
   36, 137,
   37, 7,
   38, 36,
   39, 0,
   40, 40,
   32, 66,
   33, 147,
   34, 1,
   35, 128,
   38, 170,
   39, 10,
   40, 41,
   32, 3,
   33, 126,
   34, 4,
   35, 131,
   38, 38,
   39, 13,
   40, 42,
   32, 0,
   33, 176,
   34, 0,
   35, 149,
   38, 160,
   39, 7,
   40, 43,
   33, 0,
   35, 0,
   36, 12,
   37, 4,
   38, 170,
   39, 10,
   40, 44,
   33, 2,
   35, 128,
   36, 134,
   37, 195,
   38, 171,
   40, 45,
   32, 66,
   33, 151,
   34, 1,
   36, 137,
   37, 7,
   38, 170,
   40, 46,
   32, 0,
   33, 0,
   34, 0,
   36, 31,
   37, 4,
   40, 47,
   33, 178,
   35, 149,
   36, 137,
   37, 7,
   38, 32,
   39, 4,
   40, 48,
   32, 66,
   33, 139,
   34, 4,
   35, 128,
   38, 170,
   39, 10,
   40, 49,
   32, 0,
   33, 177,
   34, 0,
   35, 149,
   38, 160,
   39, 7,
   40, 50,
   32, 3,
   33, 117,
   34, 4,
   35, 131,
   38, 38,
   39, 13,
   40, 51,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 52,
   32, 0,
   33, 96,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   39, 10,
   40, 53,
   33, 8,
   34, 152,
   35, 149,
   36, 137,
   37, 7,
   38, 36,
   39, 0,
   40, 54,
   33, 188,
   34, 0,
   40, 55,
   33, 163,
   34, 13,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   39, 10,
   40, 56,
   33, 96,
   34, 0,
   35, 128,
   36, 0,
   37, 56,
   38, 170,
   40, 57,
   33, 6,
   34, 152,
   35, 149,
   36, 137,
   37, 7,
   38, 36,
   39, 0,
   40, 58,
   33, 190,
   34, 0,
   40, 59,
   32, 5,
   33, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 60,
   32, 0,
   33, 96,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   39, 10,
   40, 61,
   33, 66,
   34, 1,
   35, 149,
   36, 137,
   37, 7,
   38, 36,
   39, 0,
   40, 62,
   33, 12,
   34, 152,
   38, 164,
   39, 7,
   40, 63,
   33, 8,
   40, 64,
   33, 96,
   34, 0,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   39, 10,
   40, 65,
   33, 12,
   34, 152,
   35, 149,
   36, 137,
   37, 7,
   38, 36,
   39, 0,
   40, 66,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 67,
   32, 0,
   35, 128,
   36, 0,
   37, 16,
   38, 171,
   39, 10,
   40, 68,
   33, 34,
   34, 1,
   35, 149,
   36, 137,
   37, 7,
   38, 36,
   39, 0,
   40, 69,
   33, 0,
   34, 0,
   35, 0,
   36, 4,
   37, 18,
   38, 170,
   39, 10,
   40, 70,
   32, 3,
   33, 212,
   34, 5,
   35, 131,
   36, 137,
   37, 7,
   38, 38,
   39, 13,
   40, 71,
   32, 0,
   33, 96,
   34, 0,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   39, 10,
   40, 72,
   33, 179,
   35, 149,
   36, 137,
   37, 7,
   38, 0,
   39, 8,
   40, 73,
   33, 0,
   35, 0,
   36, 9,
   37, 0,
   38, 170,
   39, 10,
   40, 74,
   33, 2,
   35, 128,
   36, 134,
   37, 59,
   40, 75,
   32, 66,
   33, 221,
   34, 5,
   36, 137,
   37, 7,
   40, 76,
   32, 0,
   33, 0,
   34, 0,
   36, 31,
   37, 0,
   40, 77,
   33, 179,
   35, 149,
   36, 137,
   37, 7,
   38, 32,
   39, 0,
   40, 78,
   33, 0,
   35, 0,
   36, 151,
   37, 3,
   38, 170,
   39, 10,
   40, 79,
   32, 66,
   33, 226,
   34, 5,
   35, 128,
   36, 137,
   37, 7,
   40, 80,
   32, 0,
   33, 16,
   34, 0,
   35, 0,
   36, 128,
   37, 204,
   38, 171,
   40, 81,
   33, 0,
   34, 64,
   35, 180,
   36, 137,
   37, 7,
   38, 170,
   39, 4,
   40, 82,
   34, 0,
   35, 176,
   38, 146,
   39, 9,
   40, 83,
   33, 20,
   34, 1,
   35, 149,
   38, 0,
   39, 8,
   40, 84,
   33, 72,
   35, 164,
   38, 42,
   39, 0,
   40, 85,
   33, 0,
   34, 0,
   35, 0,
   36, 9,
   37, 0,
   38, 170,
   39, 10,
   40, 86,
   33, 8,
   35, 128,
   36, 134,
   37, 59,
   40, 87,
   32, 66,
   33, 17,
   34, 7,
   36, 137,
   37, 7,
   40, 88,
   32, 0,
   33, 0,
   34, 0,
   36, 31,
   37, 0,
   40, 89,
   33, 20,
   34, 1,
   35, 149,
   36, 137,
   37, 7,
   38, 32,
   39, 0,
   40, 90,
   33, 22,
   38, 2,
   39, 9,
   40, 91,
   33, 0,
   34, 0,
   35, 0,
   36, 128,
   37, 72,
   38, 170,
   39, 10,
   40, 92,
   35, 160,
   36, 137,
   37, 7,
   38, 20,
   39, 9,
   40, 93,
   36, 128,
   37, 80,
   38, 164,
   39, 4,
   40, 94,
   33, 22,
   34, 1,
   35, 149,
   36, 137,
   37, 7,
   39, 0,
   40, 95,
   33, 4,
   34, 0,
   35, 0,
   36, 156,
   37, 120,
   38, 170,
   39, 10,
   40, 96,
   33, 67,
   34, 13,
   36, 1,
   37, 196,
   38, 171,
   40, 97,
   33, 3,
   34, 0,
   36, 21,
   40, 98,
   33, 0,
   36, 0,
   37, 0,
   38, 170,
   40, 99,
   33, 94,
   35, 149,
   36, 137,
   37, 7,
   38, 16,
   39, 9,
   40, 100,
   33, 3,
   35, 0,
   36, 21,
   37, 196,
   38, 171,
   39, 10,
   40, 101,
   33, 0,
   35, 128,
   36, 0,
   37, 6,
   38, 170,
   40, 102,
   36, 143,
   37, 227,
   38, 171,
   40, 103,
   32, 66,
   33, 205,
   34, 7,
   36, 137,
   37, 7,
   38, 170,
   40, 104,
   32, 0,
   33, 96,
   34, 0,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   40, 105,
   33, 0,
   35, 128,
   36, 143,
   37, 3,
   38, 170,
   40, 106,
   32, 66,
   33, 221,
   34, 7,
   36, 137,
   37, 7,
   40, 107,
   32, 0,
   33, 67,
   34, 13,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   40, 108,
   33, 0,
   34, 0,
   36, 0,
   37, 4,
   38, 170,
   40, 109,
   32, 3,
   33, 127,
   34, 1,
   35, 131,
   36, 137,
   37, 7,
   38, 38,
   39, 13,
   40, 110,
   33, 98,
   40, 111,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 112,
   32, 0,
   33, 6,
   35, 149,
   38, 0,
   39, 8,
   40, 113,
   33, 1,
   35, 0,
   36, 151,
   37, 59,
   38, 170,
   39, 10,
   40, 114,
   32, 66,
   33, 14,
   34, 8,
   35, 128,
   36, 137,
   37, 7,
   40, 115,
   32, 3,
   33, 60,
   34, 11,
   35, 131,
   38, 38,
   39, 13,
   40, 116,
   32, 0,
   33, 3,
   34, 0,
   35, 149,
   38, 2,
   39, 8,
   40, 117,
   33, 39,
   35, 0,
   36, 129,
   37, 196,
   38, 171,
   39, 10,
   40, 118,
   33, 0,
   35, 128,
   36, 9,
   37, 72,
   38, 170,
   40, 119,
   33, 88,
   34, 52,
   35, 163,
   36, 137,
   37, 7,
   38, 42,
   39, 0,
   40, 120,
   33, 0,
   34, 0,
   35, 160,
   38, 0,
   39, 9,
   40, 121,
   33, 7,
   35, 128,
   36, 3,
   37, 57,
   38, 170,
   39, 10,
   40, 122,
   33, 4,
   35, 0,
   36, 28,
   37, 56,
   40, 123,
   33, 7,
   35, 128,
   36, 131,
   37, 57,
   40, 124,
   33, 3,
   35, 149,
   36, 137,
   37, 7,
   38, 2,
   39, 8,
   40, 125,
   33, 39,
   35, 0,
   36, 129,
   37, 196,
   38, 171,
   39, 10,
   40, 126,
   33, 0,
   35, 128,
   36, 9,
   37, 72,
   38, 170,
   40, 127,
   33, 88,
   34, 52,
   35, 163,
   36, 137,
   37, 7,
   38, 42,
   39, 0,
   40, 128,
   33, 6,
   34, 0,
   35, 0,
   36, 129,
   37, 192,
   38, 147,
   39, 1,
   40, 129,
   33, 0,
   35, 128,
   36, 137,
   37, 72,
   38, 170,
   39, 10,
   40, 130,
   32, 2,
   33, 102,
   34, 8,
   35, 0,
   36, 0,
   37, 102,
   40, 131,
   32, 0,
   33, 0,
   34, 0,
   35, 128,
   36, 31,
   37, 2,
   40, 132,
   33, 6,
   36, 137,
   37, 7,
   38, 220,
   39, 12,
   40, 133,
   33, 0,
   35, 170,
   38, 170,
   39, 10,
   40, 134,
   35, 182,
   38, 0,
   39, 8,
   40, 135,
   35, 128,
   36, 134,
   37, 59,
   38, 170,
   39, 10,
   40, 136,
   33, 5,
   36, 137,
   37, 7,
   38, 220,
   39, 12,
   40, 137,
   33, 0,
   35, 170,
   38, 170,
   39, 10,
   40, 138,
   35, 182,
   38, 0,
   39, 8,
   40, 139,
   35, 128,
   36, 134,
   37, 59,
   38, 170,
   39, 10,
   40, 140,
   32, 66,
   33, 123,
   34, 8,
   36, 137,
   37, 7,
   40, 141,
   32, 0,
   33, 0,
   34, 0,
   35, 0,
   36, 1,
   37, 130,
   40, 142,
   33, 5,
   36, 129,
   37, 194,
   38, 171,
   40, 143,
   32, 3,
   33, 147,
   34, 8,
   35, 131,
   36, 137,
   37, 7,
   38, 38,
   39, 13,
   40, 144,
   32, 0,
   33, 5,
   34, 0,
   35, 0,
   36, 129,
   37, 192,
   38, 19,
   39, 1,
   40, 145,
   33, 0,
   35, 128,
   36, 137,
   37, 72,
   38, 170,
   39, 10,
   40, 146,
   32, 2,
   33, 126,
   34, 8,
   35, 0,
   36, 0,
   37, 102,
   40, 147,
   32, 0,
   33, 0,
   34, 0,
   35, 128,
   36, 31,
   37, 2,
   40, 148,
   33, 5,
   36, 137,
   37, 7,
   38, 220,
   39, 12,
   40, 149,
   33, 0,
   35, 170,
   38, 170,
   39, 10,
   40, 150,
   35, 182,
   38, 0,
   39, 8,
   40, 151,
   35, 128,
   36, 134,
   37, 59,
   38, 170,
   39, 10,
   40, 152,
   33, 5,
   36, 137,
   37, 7,
   38, 220,
   39, 12,
   40, 153,
   33, 0,
   35, 170,
   38, 170,
   39, 10,
   40, 154,
   35, 128,
   36, 31,
   37, 2,
   40, 155,
   33, 1,
   35, 0,
   36, 129,
   37, 194,
   38, 171,
   40, 156,
   32, 3,
   33, 147,
   34, 8,
   35, 131,
   36, 137,
   37, 7,
   38, 38,
   39, 13,
   40, 157,
   32, 0,
   33, 4,
   34, 0,
   35, 149,
   38, 18,
   39, 8,
   40, 158,
   33, 96,
   35, 196,
   38, 170,
   39, 4,
   40, 159,
   33, 0,
   35, 192,
   38, 0,
   39, 9,
   40, 160,
   32, 66,
   33, 203,
   34, 8,
   35, 128,
   38, 170,
   39, 10,
   40, 161,
   32, 112,
   33, 84,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 162,
   32, 2,
   33, 204,
   34, 8,
   35, 128,
   38, 170,
   39, 10,
   40, 163,
   32, 3,
   33, 202,
   34, 15,
   35, 131,
   38, 38,
   39, 13,
   40, 164,
   32, 0,
   33, 0,
   34, 0,
   35, 0,
   36, 140,
   37, 12,
   38, 170,
   39, 10,
   40, 165,
   33, 4,
   36, 130,
   37, 120,
   40, 166,
   33, 0,
   35, 128,
   36, 137,
   37, 72,
   38, 18,
   39, 4,
   40, 167,
   32, 3,
   33, 222,
   34, 15,
   35, 131,
   37, 7,
   38, 38,
   39, 13,
   40, 168,
   32, 0,
   33, 1,
   34, 0,
   35, 0,
   36, 156,
   37, 120,
   38, 170,
   39, 10,
   40, 169,
   33, 0,
   35, 128,
   36, 129,
   37, 64,
   40, 170,
   32, 3,
   33, 207,
   34, 15,
   35, 131,
   36, 137,
   37, 7,
   38, 38,
   39, 13,
   40, 171,
   32, 112,
   33, 8,
   34, 184,
   35, 149,
   38, 160,
   39, 4,
   40, 172,
   32, 3,
   33, 212,
   34, 15,
   35, 131,
   38, 38,
   39, 13,
   40, 173,
   33, 39,
   34, 11,
   40, 174,
   32, 112,
   33, 99,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 175,
   32, 0,
   33, 1,
   34, 0,
   35, 128,
   36, 134,
   37, 203,
   38, 171,
   39, 10,
   40, 176,
   32, 66,
   33, 221,
   34, 8,
   36, 137,
   37, 7,
   38, 170,
   40, 177,
   32, 0,
   33, 24,
   34, 128,
   35, 149,
   38, 164,
   39, 0,
   40, 178,
   32, 3,
   33, 217,
   34, 15,
   35, 131,
   38, 38,
   39, 13,
   40, 179,
   32, 112,
   33, 10,
   34, 184,
   35, 149,
   38, 160,
   39, 0,
   40, 180,
   32, 2,
   33, 224,
   34, 8,
   35, 128,
   38, 170,
   39, 10,
   40, 181,
   32, 112,
   33, 10,
   34, 184,
   35, 149,
   38, 160,
   39, 0,
   40, 182,
   33, 84,
   38, 2,
   39, 8,
   40, 183,
   32, 0,
   33, 24,
   34, 128,
   38, 164,
   39, 0,
   40, 184,
   33, 0,
   34, 0,
   35, 128,
   36, 128,
   37, 72,
   38, 170,
   39, 10,
   40, 185,
   32, 112,
   33, 94,
   34, 184,
   35, 149,
   36, 137,
   37, 7,
   38, 18,
   39, 8,
   40, 186,
   32, 0,
   33, 0,
   34, 0,
   35, 128,
   36, 9,
   37, 75,
   38, 170,
   39, 10,
   40, 187,
   32, 112,
   33, 95,
   34, 184,
   35, 149,
   36, 137,
   37, 7,
   38, 16,
   39, 8,
   40, 188,
   32, 0,
   33, 0,
   34, 0,
   35, 0,
   36, 28,
   37, 131,
   38, 171,
   39, 10,
   40, 189,
   32, 3,
   33, 50,
   34, 9,
   35, 131,
   36, 137,
   37, 7,
   38, 38,
   39, 13,
   40, 190,
   32, 0,
   33, 0,
   34, 0,
   35, 0,
   36, 130,
   37, 140,
   38, 171,
   39, 10,
   40, 191,
   32, 3,
   33, 37,
   34, 9,
   35, 131,
   36, 137,
   37, 7,
   38, 38,
   39, 13,
   40, 192,
   32, 66,
   33, 188,
   35, 128,
   38, 170,
   39, 10,
   40, 193,
   32, 0,
   33, 1,
   34, 0,
   35, 0,
   36, 1,
   37, 192,
   38, 171,
   40, 194,
   32, 112,
   33, 15,
   34, 184,
   35, 149,
   36, 137,
   37, 7,
   38, 32,
   39, 0,
   40, 195,
   32, 3,
   33, 227,
   34, 15,
   35, 131,
   38, 38,
   39, 13,
   40, 196,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 197,
   32, 0,
   33, 3,
   35, 149,
   38, 20,
   39, 8,
   40, 198,
   33, 166,
   35, 164,
   38, 42,
   39, 5,
   40, 199,
   33, 0,
   35, 160,
   38, 68,
   39, 9,
   40, 200,
   33, 24,
   34, 109,
   35, 128,
   36, 158,
   37, 123,
   38, 170,
   39, 10,
   40, 201,
   32, 66,
   33, 19,
   34, 11,
   36, 137,
   37, 7,
   40, 202,
   32, 0,
   33, 174,
   34, 0,
   35, 149,
   38, 36,
   39, 0,
   40, 203,
   33, 0,
   34, 3,
   35, 128,
   36, 135,
   37, 123,
   38, 170,
   39, 10,
   40, 204,
   32, 66,
   33, 22,
   34, 11,
   36, 137,
   37, 7,
   40, 205,
   32, 0,
   33, 174,
   34, 0,
   35, 149,
   38, 36,
   39, 0,
   40, 206,
   32, 5,
   33, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 207,
   32, 3,
   33, 13,
   34, 11,
   35, 131,
   38, 38,
   39, 13,
   40, 208,
   32, 0,
   33, 0,
   34, 0,
   35, 0,
   36, 128,
   38, 2,
   39, 0,
   40, 209,
   35, 128,
   36, 9,
   37, 72,
   38, 30,
   40, 210,
   33, 88,
   34, 52,
   35, 51,
   36, 128,
   37, 7,
   38, 42,
   40, 211,
   33, 0,
   34, 0,
   35, 0,
   38, 128,
   39, 16,
   40, 212,
   33, 16,
   35, 99,
   38, 42,
   39, 0,
   40, 213,
   33, 0,
   35, 96,
   38, 168,
   39, 18,
   40, 214,
   33, 175,
   34, 76,
   35, 0,
   38, 200,
   39, 12,
   40, 215,
   33, 0,
   34, 0,
   38, 128,
   39, 5,
   40, 216,
   35, 128,
   36, 134,
   37, 59,
   38, 30,
   39, 0,
   40, 217,
   32, 66,
   33, 28,
   34, 14,
   35, 0,
   36, 128,
   37, 7,
   40, 218,
   32, 0,
   33, 53,
   34, 41,
   38, 196,
   39, 12,
   40, 219,
   32, 2,
   33, 29,
   34, 14,
   38, 30,
   39, 0,
   40, 220,
   32, 0,
   33, 127,
   34, 52,
   38, 196,
   39, 12,
   40, 221,
   33, 0,
   34, 0,
   35, 144,
   36, 159,
   37, 4,
   38, 16,
   39, 10,
   40, 222,
   35, 0,
   36, 132,
   37, 0,
   38, 128,
   39, 16,
   40, 223,
   33, 6,
   35, 99,
   36, 128,
   37, 7,
   38, 42,
   39, 0,
   40, 224,
   33, 0,
   35, 128,
   36, 137,
   38, 170,
   39, 10,
   40, 225,
   32, 5,
   35, 132,
   38, 180,
   39, 9,
   40, 226,
   32, 112,
   33, 97,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 227,
   32, 0,
   33, 1,
   34, 0,
   35, 128,
   36, 134,
   37, 195,
   38, 171,
   39, 10,
   40, 228,
   32, 66,
   33, 206,
   34, 15,
   36, 137,
   37, 7,
   38, 170,
   40, 229,
   32, 112,
   33, 80,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 230,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 231,
   32, 112,
   33, 100,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 232,
   32, 0,
   33, 1,
   34, 0,
   35, 128,
   36, 134,
   37, 195,
   38, 171,
   39, 10,
   40, 233,
   32, 66,
   33, 211,
   34, 15,
   36, 137,
   37, 7,
   38, 170,
   40, 234,
   32, 112,
   33, 81,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 235,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 236,
   32, 112,
   33, 101,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 237,
   32, 0,
   33, 1,
   34, 0,
   35, 128,
   36, 134,
   37, 195,
   38, 171,
   39, 10,
   40, 238,
   32, 66,
   33, 216,
   34, 15,
   36, 137,
   37, 7,
   38, 170,
   40, 239,
   32, 112,
   33, 82,
   34, 184,
   35, 149,
   38, 18,
   39, 8,
   40, 240,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 241,
   32, 112,
   33, 97,
   34, 184,
   35, 149,
   38, 2,
   39, 8,
   40, 242,
   32, 0,
   33, 1,
   34, 0,
   35, 128,
   36, 134,
   37, 195,
   38, 171,
   39, 10,
   40, 243,
   32, 66,
   33, 221,
   34, 15,
   36, 137,
   37, 7,
   38, 170,
   40, 244,
   32, 112,
   33, 80,
   34, 184,
   35, 149,
   38, 2,
   39, 8,
   40, 245,
   32, 5,
   33, 0,
   34, 0,
   35, 132,
   38, 180,
   39, 9,
   40, 246,
   32, 0,
   33, 1,
   35, 128,
   36, 134,
   37, 203,
   38, 171,
   39, 10,
   40, 247,
   32, 66,
   33, 225,
   34, 15,
   36, 137,
   37, 7,
   38, 170,
   40, 248,
   32, 0,
   33, 2,
   34, 0,
   35, 0,
   36, 129,
   37, 196,
   38, 171,
   40, 249,
   33, 0,
   35, 128,
   36, 137,
   37, 72,
   38, 170,
   40, 250,
   32, 5,
   35, 132,
   37, 7,
   38, 180,
   39, 9,
   40, 251,
   32, 112,
   33, 78,
   34, 184,
   35, 149,
   38, 16,
   39, 8,
   40, 252,
   32, 0,
   33, 0,
   34, 0,
   35, 128,
   36, 134,
   37, 195,
   38, 171,
   39, 10,
   40, 253,
   32, 66,
   33, 231,
   34, 15,
   36, 137,
   37, 7,
   38, 170,
   40, 254,
   32, 0,
   33, 187,
   34, 0,
   35, 149,
   38, 32,
   39, 0,
   40, 255,
   32, 5,
   33, 0,
   35, 132,
   38, 180,
   39, 9,
   42, 8,
   16, 1,
   0xff, 0xff,
   0xff, 0xff};



const  uint8_t CONFIG2[50] PROGMEM =
  {58, 0,
   100, 58,
   101, 187,
   8, 58,
   9, 187,
   80, 16,
   82, 103,
   81, 119,
   5, 161,
   24, 4,
   84, 1,
   85, 33,
   7, 0,
   6, 12,
   11, 3,
   80, 16,
   81, 0,
   82, 4,
   97, 15,
   100, 85,
   101, 85,
   5, 161,
   24, 4,
   0xff, 0xff,
   0xff, 0xff};

#define SCLK_POL 0x0D
#define DATA_REQ_ENABLE 0x18
#define REQ_POL 0x0C
#define DLA 0x46
#define DRA 0x48
#define RUN 0x72

// User Configuration
const  uint8_t CONFIG3[24] PROGMEM =
  {
	PCM_DIV, 0x07, // Oversampling rate of 512
	PCMCONF, 0x10, // 16 bit output value
	RES1, 9,
	RES2, 2,
	MFSDF, 5,
	MFSDF_441,6,
	PLLFRAC_H, 0,
	PLLFRAC_441_H, 184,
	PLLFRAC_L, 0,
	PLLFRAC_441_L, 0,
	PLLCTL, 161,
	SCLK_POL, 0,
	DATA_REQ_ENABLE, 1,
	REQ_POL, 1, // Active High?
	DLA, 0x07,
	DRA, 0x07,
	RUN, 1,
	0xff, 0xff,
	0xff, 0xff};


