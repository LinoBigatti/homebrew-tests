#include "gba.h"

#define u8 unsigned char
#define u16 unsigned short
#define HFLIP 0x40
#define VFLIP 0x80

/* Shortened BLKSTR, unused fields removed */
typedef struct {
u16 bg;
u8 flags;
} BLKSTR;

#include "island16.TXT"




/* SetTile copies a 16x16 pixel tile to mapmemory */
void SetTile (u16 * mappt, int x, int y, int blk)
{
int tile;

	tile = island16_blockstr[blk].bg;
	tile *= 4;
	switch (island16_blockstr[blk].flags&(HFLIP+VFLIP)) {
		case 0:
			mappt[(y*32)+x] = tile;
			mappt[(y*32)+x+1] = tile+1;
			mappt[((y+1)*32)+x] = tile+2;
			mappt[((y+1)*32)+x+1] = tile+3;
			break;
		case HFLIP:
			tile |= 0x400;
			mappt[(y*32)+x+1] = tile;
			mappt[(y*32)+x] = tile+1;
			mappt[((y+1)*32)+x+1] = tile+2;
			mappt[((y+1)*32)+x] = tile+3;
			break;
		case VFLIP:
			tile |= 0x800;
			mappt[((y+1)*32)+x] = tile;
			mappt[((y+1)*32)+x+1] = tile+1;
			mappt[(y*32)+x] = tile+2;
			mappt[(y*32)+x+1] = tile+3;
			break;
		case (HFLIP+VFLIP):
			tile |= 0xC00;
			mappt[((y+1)*32)+x+1] = tile;
			mappt[((y+1)*32)+x] = tile+1;
			mappt[(y*32)+x+1] = tile+2;
			mappt[(y*32)+x] = tile+3;
			break;
	}
}








void AgbMain(void)
{
int i, x, y;
u16 * palpt;
u16 * gfxpt, * gfxpt2;

	DISPCNT = DISP_MODE (0);

	BG0CNT = BG_CHARBASE_0x06004000 | BG_COLOUR_256 | BG_TEXT_64x64 | BG_MAPBASE(0x0000);

/* Copy the tile graphics to vram 16bits at a time (8bit transfers don't work) */
	gfxpt = VRAM_BASE+0x2000;	/* This is actually +0x4000, but 0x2000 because of short ptr */
	gfxpt2 = (u16 *) island16_blockgfx;
	for (i=0;i<(sizeof(island16_blockgfx)/2);i++) {
		gfxpt[i] = gfxpt2[i];
	}

/* Copy the 256 colour palette */
	palpt = (u16 *) BG_PAL;
	for (i=0;i<256;i++) {
		palpt[i] = island16_cmap[i];
	}

/* Copy the data to the map memory */
/* map vram is divided into 4 sections in GBA 64x64 mode */
/* copy top left quarter */
	for (y=0;y<32;y+=2) {
		for (x=0;x<32;x+=2) {
			SetTile ((u16 *) VRAM_BASE, x, y, island16_map0[((y/2)*32)+(x/2)]);
		}
	}
/* copy top right quarter */
	for (y=0;y<32;y+=2) {
		for (x=32;x<64;x+=2) {
			SetTile ((u16 *) (VRAM_BASE+0x400), x-32, y, island16_map0[((y/2)*32)+(x/2)]);
		}
	}
/* copy bottom left quarter */
	for (y=32;y<64;y+=2) {
		for (x=0;x<32;x+=2) {
			SetTile ((u16 *) (VRAM_BASE+0x800), x, y-32, island16_map0[((y/2)*32)+(x/2)]);
		}
	}
/* copy bottom right quarter */
	for (y=32;y<64;y+=2) {
		for (x=32;x<64;x+=2) {
			SetTile ((u16 *) (VRAM_BASE+0xC00), x-32, y-32, island16_map0[((y/2)*32)+(x/2)]);
		}
	}


/* enable BG0 */
	DISPCNT |= DISP_BG0;
/* set coords to 0,0 */
	x = 0; y = 0;

	while (1) {
/* wait for vertical blank */
		while (VCOUNT != 160);
		while (VCOUNT == 160);

/* check gamepad (active low) */
		if (!(PADREG & PAD_LEFT) && x > 0) x--;
		if (!(PADREG & PAD_RIGHT) && x < 272) x++;
		if (!(PADREG & PAD_UP) && y > 0) y--;
		if (!(PADREG & PAD_DOWN) && y < 352) y++;

/* update coords */
		BG0X = x;
		BG0Y = y;
	}
}

