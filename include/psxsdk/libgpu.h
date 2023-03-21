#ifndef LIBGPU_H
#define LIBGPU_H

typedef struct {
    short x, y; /* offset point on VRAM */
    short w, h; /* width and height */
} RECT;

typedef struct {
    unsigned long tag;
    unsigned long code[15];
} DR_ENV; /* Packed Drawing Environment */

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
    unsigned char r1, g1, b1, p1;
    short x1, y1;
    unsigned char u1, v1;
    unsigned short tpage;
    unsigned char r2, g2, b2, p2;
    short x2, y2;
    unsigned char u2, v2;
    unsigned short pad2;
} POLY_GT3; /* Gouraud Textured Triangle */

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char r1, g1, b1, pad1;
    short x1, y1;
    unsigned char r2, g2, b2, pad2;
    short x2, y2;
    unsigned char r3, g3, b3, pad3;
    short x3, y3;
} POLY_G4; /* Gouraud Quadrangle */

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
    unsigned char r1, g1, b1, p1;
    short x1, y1;
    unsigned char u1, v1;
    unsigned short tpage;
    unsigned char r2, g2, b2, p2;
    short x2, y2;
    unsigned char u2, v2;
    unsigned short pad2;
    unsigned char r3, g3, b3, p3;
    short x3, y3;
    unsigned char u3, v3;
    unsigned short pad3;
} POLY_GT4; /* Gouraud Textured Quadrangle */

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
    short w, h;
} SPRT; /* free size Sprite */

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
} SPRT_16; /* 16x16 Sprite */

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
} SPRT_8; /* 8x8 Sprite */

typedef struct {
    RECT clip;                /* clip area */
    short ofs[2];             /* drawing offset */
    RECT tw;                  /* texture window */
    unsigned short tpage;     /* texture page */
    unsigned char dtd;        /* dither flag (0:off, 1:on) */
    unsigned char dfe;        /* flag to draw on display area (0:off 1:on) */
    unsigned char isbg;       /* enable to auto-clear */
    unsigned char r0, g0, b0; /* initital background color */
    DR_ENV dr_env;            /* reserved */
} DRAWENV;

typedef struct {
    RECT disp;                /* display area */
    RECT screen;              /* display start point */
    unsigned char isinter;    /* interlace 0: off 1: on */
    unsigned char isrgb24;    /* RGB24 bit mode */
    unsigned char pad0, pad1; /* reserved */
} DISPENV;

extern void SetShadeTex(void* p, int tge);
extern void SetPolyGT3(POLY_GT3* p);
extern void SetPolyG4(POLY_G4* p);
extern void SetPolyGT4(POLY_GT4* p);
extern void SetSprt(SPRT* p);
extern void SetSprt16(SPRT_16* p);
extern void SetSprt8(SPRT_8* p);
extern int ResetGraph(int mode);
extern int SetGraphReverse(int mode);
extern int SetGraphQueue(int mode);
extern unsigned long DrawSyncCallback(void (*func)());
extern void SetDispMask(int mask);
extern int DrawSync(int mode);
extern int ClearImage(RECT* rect, unsigned char r, unsigned char g,
                      unsigned char b);
extern int LoadImage(RECT* rect, unsigned long* p);
extern int StoreImage(RECT* rect, unsigned long* p);
extern int MoveImage(RECT* rect, int x, int y);
extern unsigned long* ClearOTag(unsigned long* ot, int n);
extern unsigned long* ClearOTagR(unsigned long* ot, int n);
extern void DrawOTag(unsigned long* p);
extern DRAWENV* PutDrawEnv(DRAWENV* env);
extern DISPENV* PutDispEnv(DISPENV* env);

#endif