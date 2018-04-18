#include "gba.h"

#define u16 unsigned short

#include "projabg.txt"
#include "projafg.txt"
#include "projagfx.txt"
#include "projalook.txt"


void DrawRowBG (int y)
{
u16 * palpt;
int i, rp;

	rp = ((y/2)-16)%(32*8);
	rp /= 8;
	palpt = VRAM_BASE;
	for (i=0;i<22;i++) {
		if (i==16) rp += 31;
		palpt[rp*32+(i*2)] = (short) tilelookup[(projabg_map[(y/32)*22+i]*4)];
		palpt[rp*32+(i*2)+1] = (short) tilelookup[(projabg_map[(y/32)*22+i]*4+1)];
		palpt[(rp+1)*32+(i*2)] = (short) tilelookup[(projabg_map[(y/32)*22+i]*4+2)];
		palpt[(rp+1)*32+(i*2)+1] = (short) tilelookup[(projabg_map[(y/32)*22+i]*4+3)];
	}
}

void DrawRowFG (int y)
{
u16 * palpt;
int i, rp, blk;

	rp = ((y)-16)%(32*8);
	rp /= 8;
	palpt = VRAM_BASE+0x800;
	for (i=0;i<22;i++) {
		if (i==16) rp += 31;
		blk = (int) projafg_map[(y/16)*22+i];
		if (blk) {
			palpt[rp*32+(i*2)] = (short) tilelookup[blk*4+560];
			palpt[rp*32+(i*2)+1] = (short) tilelookup[blk*4+561];
			palpt[(rp+1)*32+(i*2)] = (short) tilelookup[blk*4+562];
			palpt[(rp+1)*32+(i*2)+1] = (short) tilelookup[blk*4+563];
		} else {
			palpt[rp*32+(i*2)] = 0;
			palpt[rp*32+(i*2)+1] = 0;
			palpt[(rp+1)*32+(i*2)] = 0;
			palpt[(rp+1)*32+(i*2)+1] = 0;
		}
	}
}

void AgbMain(void)
{
int i;
int x, y;
u16 * palpt;
u16 * gfxpt, * gfxpt2;

	x = 40; y = 500*16;
	DISPCNT = DISP_MODE (0);

	BG1CNT = BG_COLOUR_16 | BG_CHARBASE_0x06004000 | BG_TEXT_64x32 | BG_WRAP;
	BG0CNT = BG_COLOUR_16 | BG_CHARBASE_0x06004000 | BG_TEXT_64x32 | BG_WRAP | BG_MAPBASE(0x1000);

	gfxpt = VRAM_BASE+0x2000;
	gfxpt2 = (u16 *) projagfx_blockgfx;
	for (i=0;i<(sizeof(projagfx_blockgfx)/2);i++) {
		gfxpt[i] = gfxpt2[i];
	}
	palpt = BG_PAL;
	for (i=0;i<16;i++) {
		palpt[i] = projagfx_cmap[i];
	}

	DISPCNT |= DISP_BG0 | DISP_BG1;
	while (1) {
/* wait for vertical blank */
		while (VCOUNT != 160);
		while (VCOUNT == 160);

/* check gamepad (active low) */
		if (!(PADREG & PAD_LEFT) && x > 0) x--;
		if (!(PADREG & PAD_RIGHT) && x < 112) x++;

		BG1X = x;
		BG1Y = (y/2)%(32*8);
		BG0X = x;
		BG0Y = (y)%(32*8);
		if (y>0) y--;
		if (!((y/2)&0xF)) DrawRowBG (y);
		if (!((y)&0xF)) DrawRowFG (y);
	}
}

