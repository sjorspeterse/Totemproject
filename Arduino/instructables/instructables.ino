#include <LCD5110_Graph.h>

#include <avr/pgmspace.h>

const unsigned char Celine [] PROGMEM= {
0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x02, 0x02,
0x02, 0x02, 0x82, 0x02, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x20, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0,
0xA0, 0x20, 0x10, 0x08, 0x87, 0x88, 0xB0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x3E, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE3, 0x3E, 0x00, 0xF8, 0x04, 0x02, 0x02, 0x0D, 0x13,
0x1E, 0x1A, 0x0C, 0xF9, 0x00, 0xF9, 0x0C, 0x12, 0x1E, 0x1A, 0x0C, 0x01, 0xE2, 0x1C, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x07, 0x18, 0x20,
0x40, 0x80, 0x80, 0x10, 0x31, 0xB2, 0xB2, 0xB2, 0x11, 0x08, 0x82, 0x46, 0x20, 0x10, 0x1D, 0x62,
0x80, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0x00, 0x00, 0x00, 0xF8, 0x04, 0x02, 0x03, 0x02, 0x02, 0xE2,
0x02, 0x02, 0x02, 0x01, 0x00, 0x01, 0x42, 0x84, 0x44, 0x04, 0x02, 0x01, 0x00, 0x01, 0x02, 0xE2,
0x02, 0x06, 0x19, 0xE0, 0x00, 0x00, 0x03, 0xFE, 0x00, 0x00, 0x00, 0x01, 0x00, 0x38, 0x44, 0x44,
0x28, 0x01, 0x7C, 0x54, 0x54, 0x44, 0x00, 0x7C, 0x40, 0x41, 0x40, 0x00, 0x44, 0x7C, 0x44, 0x00,
0x7C, 0x09, 0x10, 0x7C, 0x00, 0x7C, 0x55, 0x55, 0x45, 0x00, 0x00, 0x00, 
};

const unsigned char Iris [] PROGMEM= {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x80, 0xB8, 0xD4, 0xAC, 0x32, 0x4A, 0xB6, 0xAC, 0x54, 0x88, 0xB0, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x44, 0x82, 0x01, 0x08, 0x44, 0x22, 0x12, 0x02, 0x10,
0x8A, 0x94, 0x44, 0x54, 0x48, 0xC0, 0x89, 0x21, 0x2A, 0x02, 0x25, 0x45, 0x8E, 0x13, 0xA0, 0x40,
0x80, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x58, 0xE7, 0x00, 0x00, 0x00, 0x09, 0x65, 0x55, 0x95, 0xF5,
0xD5, 0x95, 0x64, 0xC8, 0x00, 0xC8, 0x64, 0x94, 0xF4, 0xD5, 0x95, 0x55, 0x65, 0x09, 0x02, 0x04,
0x08, 0xF1, 0xA0, 0xA7, 0x18, 0x00, 0x00, 0x0F, 0x10, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0x88, 0x94, 0xA3, 0x20, 0xA3, 0x94, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0x7F, 0x10, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x08, 0x08,
0x10, 0x20, 0x40, 0x83, 0x87, 0x8D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x8D, 0x87, 0x83, 0x40, 0x20,
0x10, 0x08, 0x08, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x44, 0x7C, 0x44, 0x00, 0x7C, 0x15, 0x35, 0x49, 0x01, 0x45, 0x7C, 0x44, 0x00,
0x48, 0x54, 0x54, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char Sjors [] PROGMEM= {
0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1F, 0xFF, 0x7F, 0xE7, 0x9F, 0x7F, 0xFF, 0x6F, 0xDF, 0xBF,
0x7F, 0xCF, 0xBF, 0x7F, 0x5F, 0x3F, 0x7F, 0x6F, 0x1F, 0x3F, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0xFF,
0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x31, 0x42, 0x3F, 0xE0, 0x00, 0x04, 0x12, 0x2A, 0x0A,
0x3A, 0x1A, 0x32, 0xE4, 0x00, 0x00, 0xE4, 0x32, 0x0A, 0x3A, 0x1A, 0x2A, 0x12, 0x04, 0x00, 0x00,
0xE0, 0x3F, 0x42, 0x31, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3E, 0xC0, 0x00,
0x30, 0x10, 0x40, 0x80, 0x84, 0x8B, 0x90, 0x90, 0x8B, 0x84, 0x80, 0x80, 0x40, 0x10, 0x30, 0x00,
0xC0, 0x3E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x22, 0x12, 0x12, 0x12, 0x22, 0x81, 0x40, 0x20, 0x10,
0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48,
0x54, 0x54, 0x24, 0x00, 0x20, 0x40, 0x40, 0x3C, 0x00, 0x39, 0x45, 0x45, 0x39, 0x01, 0x7C, 0x14,
0x34, 0x48, 0x00, 0x48, 0x54, 0x54, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char Thomas [] PROGMEM= {
0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x10, 0x98, 0x08, 0x04, 0xB4, 0x04, 0x24, 0x44, 0x46,
0x02, 0x12, 0x96, 0x24, 0x04, 0x44, 0x84, 0x04, 0x4C, 0x58, 0x90, 0x30, 0x60, 0x40, 0xC0, 0x00,
0x00, 0x00, 0x00, 0xF8, 0x8E, 0x03, 0xE4, 0x38, 0x21, 0x6E, 0x40, 0x7D, 0x42, 0x40, 0x7B, 0x20,
0x20, 0x65, 0x79, 0xC2, 0x98, 0xE1, 0x86, 0xC8, 0x42, 0x7D, 0xC1, 0xF0, 0x46, 0x79, 0x30, 0xF0,
0xC1, 0x7F, 0x00, 0x00, 0x00, 0x3E, 0x41, 0x22, 0xFF, 0xA8, 0x50, 0x00, 0x00, 0x32, 0x4A, 0x6A,
0x7A, 0x4A, 0x32, 0xE4, 0x00, 0x00, 0xE4, 0x32, 0x4A, 0x6A, 0x7A, 0x4A, 0x32, 0x00, 0x00, 0xA8,
0x50, 0xFF, 0x22, 0x41, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x32, 0xD5, 0x20, 0x80, 0x40,
0x00, 0x00, 0x80, 0x40, 0x0C, 0x4B, 0x10, 0x50, 0x0B, 0x4C, 0x80, 0x00, 0x80, 0x00, 0x80, 0x20,
0x50, 0xCA, 0x35, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
0x08, 0x12, 0x2D, 0x52, 0xA8, 0x52, 0xA7, 0x57, 0xB7, 0x57, 0xA7, 0x57, 0xAA, 0xB4, 0x6A, 0x25,
0x1A, 0x09, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x7C, 0x04, 0x04,
0x00, 0x7C, 0x10, 0x10, 0x7C, 0x00, 0x38, 0x45, 0x45, 0x39, 0x01, 0x7D, 0x09, 0x11, 0x09, 0x7C,
0x00, 0x78, 0x14, 0x14, 0x78, 0x00, 0x48, 0x54, 0x54, 0x24, 0x00, 0x00,
};

const unsigned char Wiebke [] PROGMEM= {
0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0x7C, 0x7C, 0x7E, 0x3E, 0x3E,
0x3E, 0x3C, 0x1E, 0x3E, 0x7C, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x3F, 0x0F, 0x03, 0x21, 0xA0, 0xA0, 0xA0, 0x20,
0x40, 0x00, 0x40, 0x20, 0xA0, 0xA0, 0xA0, 0x20, 0x03, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF8, 0xC0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x03, 0x06, 0x07,
0xC4, 0x33, 0x0E, 0x00, 0x80, 0x03, 0x06, 0x07, 0x04, 0x83, 0x80, 0x00, 0x00, 0xC0, 0xFF, 0xFF,
0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0,
0xC0, 0x80, 0x08, 0x19, 0x19, 0x19, 0x18, 0x18, 0x08, 0x04, 0x82, 0xC0, 0xE1, 0xF0, 0xFC, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x11, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xF7, 0xC3, 0x01, 0x02, 0x04, 0x44, 0x84, 0x44, 0x02, 0x01, 0x00, 0x03, 0x07, 0x0F,
0x4F, 0xCF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0xE0, 0x00, 0x00, 0x01, 0x7C, 0x21, 0x11, 0x21,
0x7D, 0x01, 0x45, 0x7D, 0x45, 0x01, 0x7C, 0x54, 0x54, 0x44, 0x01, 0x7C, 0x54, 0x54, 0x28, 0x00,
0x7C, 0x10, 0x28, 0x45, 0x00, 0x7C, 0x54, 0x54, 0x44, 0x00, 0x01, 0x00, 
};


const unsigned char mijnenveger [] PROGMEM= {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x28, 0xBC, 0x20, 0x00, 0xBC, 0xBC, 0xBC, 0xBC, 0x00, 0xBC, 0xBC, 0xBC, 0xBC, 0x00,
0xBC, 0xBC, 0xBC, 0xBC, 0x00, 0xBC, 0xBC, 0xBC, 0xBC, 0x00, 0xBC, 0xBC, 0xBC, 0xBC, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0x7C, 0x7C, 0x7E,
0x3E, 0x3E, 0x3E, 0x3C, 0x1E, 0x3E, 0x7C, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0xF7, 0x84, 0x00, 0x07, 0xD7, 0xD7, 0xB7, 0x00, 0xF7,
0xF7, 0xF7, 0xF7, 0x00, 0xF7, 0xF7, 0xF7, 0xF7, 0x00, 0xF7, 0xF7, 0xF7, 0xF7, 0x00, 0xF7, 0xF7,
0xF7, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x3F, 0x0F, 0x03, 0x21,
0xA0, 0xA0, 0xA0, 0x20, 0x40, 0x00, 0x40, 0x20, 0xA0, 0xA0, 0xA0, 0x20, 0x03, 0x1F, 0x7F, 0xFF,
0xFF, 0xFF, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xD4, 0xDE, 0xD0, 0x00, 0xC0,
0xD4, 0xDE, 0xD0, 0x00, 0x00, 0x94, 0xDE, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94,
0xDE, 0x10, 0x00, 0x1E, 0x9E, 0xDE, 0x1E, 0x00, 0x1E, 0x9E, 0xDE, 0x1E, 0x00, 0x1E, 0x9E, 0xDE,
0x1E, 0x00, 0xDE, 0xDE, 0xDE, 0xDE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF,
0xC0, 0x00, 0x00, 0x03, 0x06, 0x07, 0xC4, 0x33, 0x0E, 0x00, 0x80, 0x03, 0x06, 0x07, 0x04, 0x83,
0x80, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B, 0x7B,
0x7B, 0x7B, 0x00, 0x03, 0x53, 0x7B, 0x43, 0x00, 0x00, 0x52, 0x7B, 0x42, 0x84, 0x00, 0x00, 0x00,
0x00, 0x84, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 0x02, 0x03, 0x02,
0x00, 0x00, 0x52, 0x7B, 0x42, 0x00, 0x7B, 0x7B, 0x7B, 0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0, 0xC0, 0x80, 0x08, 0x19, 0x19, 0x19, 0x18, 0x18,
0x08, 0x04, 0x82, 0xC0, 0xE1, 0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0xEF, 0xEF, 0xEF, 0xEF, 0x00, 0x00, 0x4A, 0xEF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xAA, 0xAF, 0x68, 0x00, 0xE0, 0xEA, 0xEF, 0xE8, 0x00, 0x00, 0x2A, 0xAF, 0xE8, 0x00,
0x00, 0x40, 0xE0, 0x00, 0x00, 0x00, 0x4A, 0xEF, 0x08, 0x00, 0xEF, 0xEF, 0xEF, 0xEF, 0x00, 0x00,
0x00, 0x00, 0x00, 0xE0, 0x11, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xC3, 0x01, 0x02,
0x04, 0x44, 0x84, 0x44, 0x02, 0x01, 0x00, 0x03, 0x07, 0x0F, 0x4F, 0xCF, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x10, 0xE0, 0x00, 0x00, 0x00, 0x3D, 0x3D, 0x3D, 0x3D, 0x00, 0x00, 0x29, 0x3D, 0x21, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x35, 0x2D, 0x00, 0x3D, 0x3D, 0x3D, 0x3D, 0x00, 0x3C,
0x3D, 0x3D, 0x3D, 0x00, 0x3C, 0x3D, 0x3D, 0x3D, 0x00, 0x3C, 0x3D, 0x3D, 0x3D, 0x00, 0x3D, 0x3D,
0x3D, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7C, 0x21, 0x11, 0x21, 0x7D, 0x01, 0x45, 0x7D,
0x45, 0x01, 0x7C, 0x54, 0x54, 0x44, 0x01, 0x7C, 0x54, 0x54, 0x28, 0x00, 0x7C, 0x10, 0x28, 0x45,
0x00, 0x7C, 0x54, 0x54, 0x44, 0x00, 0x01, 0x00, 
};

const unsigned char sudoku [] PROGMEM= {
0x00, 0xFE, 0x02, 0x2E, 0xAE, 0x96, 0x02, 0x02, 0x26, 0x36, 0x3E, 0x02, 0x02, 0x02, 0x02, 0x02,
0xFE, 0x02, 0x02, 0x82, 0x02, 0x02, 0x02, 0x86, 0xB6, 0x8E, 0x02, 0x02, 0x82, 0x82, 0x82, 0xFE,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFE, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x10, 0x98, 0x08, 0x04, 0xB4, 0x04, 0x24, 0x44,
0x46, 0x02, 0x12, 0x96, 0x24, 0x04, 0x44, 0x84, 0x04, 0x4C, 0x58, 0x90, 0x30, 0x60, 0x40, 0xC0,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x07, 0x06, 0x06, 0x00, 0x00, 0xB0, 0xB0, 0x70, 0x00,
0x30, 0xD0, 0xA0, 0xE0, 0xFF, 0x00, 0x05, 0x07, 0x04, 0x00, 0x00, 0x05, 0x05, 0x03, 0x00, 0x00,
0x05, 0x05, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xD0, 0xD0, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xF8, 0x8E, 0x03, 0xE4, 0x38, 0x21, 0x6E, 0x40, 0x7D, 0x42,
0x40, 0x7B, 0x20, 0x20, 0x65, 0x79, 0xC2, 0x98, 0xE1, 0x86, 0xC8, 0x42, 0x7D, 0xC1, 0xF0, 0x46,
0x79, 0x30, 0xF0, 0xC1, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x07, 0x9B, 0xD5, 0x1D, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xC1, 0x41, 0x81, 0x81, 0x01, 0x01, 0x1D,
0x1B, 0x1B, 0x01, 0x01, 0x41, 0x41, 0xC1, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x93, 0xDB, 0x1F, 0xFF, 0x00, 0x00, 0x00, 0x3E, 0x41, 0x22, 0xFF, 0xA8, 0x50,
0x00, 0x00, 0x32, 0x4A, 0x6A, 0x7A, 0x4A, 0x32, 0xE4, 0x00, 0x00, 0xE4, 0x32, 0x4A, 0x6A, 0x7A,
0x4A, 0x32, 0x00, 0x00, 0xA8, 0x50, 0xFF, 0x22, 0x41, 0x3E, 0x00, 0x00, 0x00, 0xFF, 0x81, 0x89,
0xEB, 0x99, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x80, 0x83, 0x82,
0x83, 0x80, 0x80, 0xC8, 0xE8, 0xD8, 0x80, 0x80, 0x82, 0x83, 0x83, 0xFF, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF2, 0xEB, 0xEA, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0F, 0x32, 0xD5, 0x20, 0x80, 0x40, 0x00, 0x00, 0x80, 0x40, 0x0C, 0x4B, 0x10, 0x50, 0x0B,
0x4C, 0x80, 0x00, 0x80, 0x00, 0x80, 0x20, 0x50, 0xCA, 0x35, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x80, 0xC0, 0xE0, 0x80, 0x00, 0x00, 0x40, 0xE0, 0x00, 0x00, 0x00, 0x60, 0x60, 0xE0, 0xFF,
0x00, 0x09, 0x0D, 0x0B, 0x00, 0x03, 0x0D, 0x0A, 0x0E, 0x00, 0x00, 0x60, 0x60, 0xA0, 0xFF, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x12, 0x2D, 0x52, 0xA8, 0x52, 0xA7,
0x57, 0xB7, 0x57, 0xA7, 0x57, 0xAA, 0xB4, 0x6A, 0x25, 0x1A, 0x09, 0x07, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x7F, 0x40, 0x40, 0x41, 0x40, 0x40, 0x40, 0x4D, 0x75, 0x69, 0x78, 0x40,
0x41, 0x41, 0x40, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x44, 0x74, 0x4C, 0x40, 0x40, 0x6D,
0x6D, 0x5C, 0x7F, 0x00, 0x00, 0x00, 0x04, 0x04, 0x7C, 0x04, 0x04, 0x00, 0x7C, 0x10, 0x10, 0x7C,
0x00, 0x38, 0x45, 0x45, 0x39, 0x01, 0x7D, 0x09, 0x11, 0x09, 0x7C, 0x00, 0x78, 0x14, 0x14, 0x78,
0x00, 0x48, 0x54, 0x54, 0x24, 0x00, 0x00, 0x00, 
};

LCD5110 lcd(7,6,5,3,4); //Creating LCD object

void setup() {
  lcd.InitLCD(); //Intializing LCD
  Serial.begin(9600);
}

void loop() {
  int acceleratex[] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
  int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  int middlelocx = 42-17;
  
  for(int i = 0; i <11; i++){
    lcd.clrScr(); //Clearing screen
    lcd.drawBitmap(middlelocx - 36 , -yoffset[33 + i], Wiebke, 34, 48); //Left Thomas
    lcd.drawBitmap(middlelocx, -yoffset[22 + i], Celine, 34, 48); //Middle Thomas
    lcd.drawBitmap(middlelocx + 36, -yoffset[11 + i], Iris, 34, 48); //Right Thomas
    lcd.drawBitmap(middlelocx + 2*36, -yoffset[i], Sjors, 34, 48); //Rightmost Thomas
    lcd.update(); //Updating the LCD
    middlelocx -= acceleratex[i];
    delay(30);   
  }
  delay(1000);
 
   middlelocx = 42-17;
   for(int i = 0; i <11; i++){
    lcd.clrScr(); //Clearing screen
    lcd.drawBitmap(middlelocx - 36 , -yoffset[33 + i], Celine, 34, 48); //Left Thomas
    lcd.drawBitmap(middlelocx, -yoffset[22 + i], Iris, 34, 48); //Middle Thomas
    lcd.drawBitmap(middlelocx + 36, -yoffset[11 + i], Sjors, 34, 48); //Right Thomas
    lcd.drawBitmap(middlelocx + 2*36, -yoffset[i], Thomas, 34, 48); //Rightmost Thomas
    lcd.update(); //Updating the LCD
    middlelocx -= acceleratex[i];
    delay(30);   
  }
  delay(1000);

   middlelocx = 42-17;
   for(int i = 0; i <11; i++){
    lcd.clrScr(); //Clearing screen
    lcd.drawBitmap(middlelocx - 36 , -yoffset[33 + i], Iris, 34, 48); //Left Thomas
    lcd.drawBitmap(middlelocx, -yoffset[22 + i], Sjors, 34, 48); //Middle Thomas
    lcd.drawBitmap(middlelocx + 36, -yoffset[11 + i], Thomas, 34, 48); //Right Thomas
    lcd.drawBitmap(middlelocx + 2*36, -yoffset[i], Wiebke, 34, 48); //Rightmost Thomas
    lcd.update(); //Updating the LCD
    middlelocx -= acceleratex[i];
    delay(30);   
  }
  delay(1000);

   middlelocx = 42-17;
   for(int i = 0; i <11; i++){
    lcd.clrScr(); //Clearing screen
    lcd.drawBitmap(middlelocx - 36 , -yoffset[33 + i], Sjors, 34, 48); //Left Thomas
    lcd.drawBitmap(middlelocx, -yoffset[22 + i], Thomas, 34, 48); //Middle Thomas
    lcd.drawBitmap(middlelocx + 36, -yoffset[11 + i], Wiebke, 34, 48); //Right Thomas
    lcd.drawBitmap(middlelocx + 2*36, -yoffset[i], Celine, 34, 48); //Rightmost Thomas
    lcd.update(); //Updating the LCD
    middlelocx -= acceleratex[i];
    delay(30);   
  }
  delay(1000);
  
   middlelocx = 42-17;
   for(int i = 0; i <11; i++){
    lcd.clrScr(); //Clearing screen
    lcd.drawBitmap(middlelocx - 36 , -yoffset[33 + i], Thomas, 34, 48); //Left Thomas
    lcd.drawBitmap(middlelocx, -yoffset[22 + i], Wiebke, 34, 48); //Middle Thomas
    lcd.drawBitmap(middlelocx + 36, -yoffset[11 + i], Celine, 34, 48); //Right Thomas
    lcd.drawBitmap(middlelocx + 2*36, -yoffset[i], Iris, 34, 48); //Rightmost Thomas
    lcd.update(); //Updating the LCD
    middlelocx -= acceleratex[i];
    delay(30);   
  }
  delay(1000);
  
}