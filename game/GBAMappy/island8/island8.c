#include "gba.h"

#include "island8.TXT"

#define u16 unsigned short

void AgbMain(void)
{
int i, x, y;
u16 * palpt;
u16 * gfxpt, * gfxpt2;
u16 * mappt;

	DISPCNT = DISP_MODE (0);

	BG0CNT = BG_CHARBASE_0x06004000 | BG_COLOUR_256 | BG_TEXT_32x32 | BG_MAPBASE(0x0000);

/* Copy the tile graphics to vram 16bits at a time (8bit transfers don't work) */
	gfxpt = VRAM_BASE+0x2000;	/* This is actually +0x4000, but 0x2000 because of short ptr */
	gfxpt2 = (u16 *) island8_blockgfx;
	for (i=0;i<(sizeof(island8_blockgfx)/2);i++) {
		gfxpt[i] = gfxpt2[i];
	}

/* Copy the 256 colour palette */
	palpt = (u16 *) BG_PAL;
	for (i=0;i<256;i++) {
		palpt[i] = island8_cmap[i];
	}

/* Copy the data to the map memory */
	mappt = (u16 *) VRAM_BASE;
	for (y=0;y<32;y++) {
		for (x=0;x<32;x++) {
			mappt[(y*32)+x] = (u16) island8_map0[y][x];
		}
	}

/* enable BG0 */
	DISPCNT |= DISP_BG0;
/* set coords to 0,0 */
	BG0X = 0;
	BG0Y = 0;

	while (1) {
	}
}

