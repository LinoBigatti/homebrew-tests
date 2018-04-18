/* gba.h, taken from retro run by Mike Wynn
 *
 * the source will be available 5th Feb 2002 onwards on 
 * http://www/L8Night.co.uk/mwynn/gbadev/ 
 * as long as not used for profit, or the profits gained are used for, by or to 
 * promote www.gbadev.org, www.L8night.co.uk/mwynn/gbadev or otherwise promote 
 * the homebrew GBA Dev scene you may use this binary and the sources for any 
 * purpose you see fit, I accept no responibility for what you get up to, but 
 * if you do anything interesting send me a scan of the polaroids :) 
 */

#ifndef GBA_SYSTEM_HEADER
#define GBA_SYSTEM_HEADER

/*
 * Gameboy Advance header
 *
 * most stolen from online docs/tutorials and tidyed into my style.
 *
 */

#define NULL ((void*)0)

/* ARM like names */
typedef unsigned char           Byte;       /*  8 bit */
typedef unsigned short int      Halfword;   /* 16 bit */
typedef unsigned int            Word;       /* 32 bit */
typedef unsigned long long int  Doubleword; /* 64 bit */

typedef Byte        * BytePtr;       /* pointer to  8 bit value */
typedef Halfword    * HalfwordPtr;   /* pointer to 16 bit value */
typedef Word        * WordPtr;       /* pointer to 32 bit value */
typedef Doubleword  * DoublewordPtr; /* pointer to 64 bit value */

/* Object (sprite) struct */
typedef struct OAM_S
{
	Halfword y;
	Halfword x;
	Halfword tile;
	Halfword _ignore; /* rotate data (see OamRotateInfo)*/
} OamEntry, * OamEntryPtr;

typedef struct OAM_word_s
{
	Word xy;
	Word tile;
} OamWordEntry, * OamWordEntryPtr;

/* rotate params (overlaps the Object (sprite) area)*/
typedef struct OAM_ROTATE_S
{
	Halfword _ignore0[3]; /* OamEntry */
	Halfword rotParamA;
	Halfword _ignore1[3];
	Halfword rotParamB;
	Halfword _ignore2[3];
	Halfword rotParamC;
	Halfword _ignore3[3];
	Halfword rotParamD;
} OamRotateInfo, * OamRotateInfoPtr;

#define OBJ_DATA_HALF ((Halfword*)(0x07000000))
#define OBJ_DATA      ((OamEntryPtr)(0x07000000))
#define OBJ_ROT_DATA  ((OamRotateInfoPtr)(0x07000000))
#define OBJ_WORD_DATA ((OamWordEntryPtr)(0x07000000))

// First halfword
#define OBJ_Y_MASK			0x00FF	/* bits used for sprite y value */
#define OBJ_ROTATE			0x0100	/* enable rotate and scale operations */
#define OBJ_SDOUBLE			0x0200	/* Double Size Flag (doubles bounding box if rotate and scale is enabled) */
#define OBJ_ALPHABLEND      0x0400	/* enable alpha blending */
#define OBJ_WINDOW			0x0800	/* window? like GB/GBC who knows */
#define OBJ_MOSAIC			0x1000	/* enables mosaic mode */
#define OBJ_COLOUR_256		0x2000	/* Object has 256 colours from 1 palette */
#define OBJ_COLOUR_16		0x0000	/* Object has 16 colours palette selected in third half word */
#define OBJ_SQUARE			0x0000	/* Object is square (1x1 aspect) */
#define OBJ_WIDE			0x4000	/* Object is wider than tall. (2x1 or 4x1) */
#define OBJ_TALL			0x8000	/* Object is taller than wide (1x2 or 1x4) */
#define OBJ_MAKE_SHAPE(s)	((s&3)<<14)	/* sprite size as 0..3 */

// Second halfword
#define OBJ_X_MASK			0x01FF	/* bits used for sprite x value   */
#define OBJ_ROTSCALE_MASK	0x3E00	/* bits avaliable for rotate and scale index   */
/* N.B. ROT SCALE share these bits Hflip and Vflip are only vaild in non rotate mode */
#define OBJ_HFLIP			0x1000	/* flip the object horizontally   */
#define OBJ_VFLIP			0x2000	/* flip the object vertically     */
#define OBJ_SIZE_16			0x4000	/* sprite basic size is 16 pixels */
#define OBJ_SIZE_32			0x8000	/* sprite basic size is 32 pixels */
#define OBJ_SIZE_64			0xC000	/* sprite basic size is 64 pixels */
#define OBJ_ROTSCALE(rs)	((rs<<9)&OBJ_ROTSCALE_MASK)
#define OBJ_MAKE_SIZE(s)	((s&3)<<14)	/* sprite size as 0..3 */


// Third halfword
#define OBJ_TILE_MASK		0x03FF	/* bits used for tile number      */
#define OBJ_PRIORITY_MASK	0x0C00	/* bits used for sprite priority  */
#define OBJ_PALETTE_MASK	0xF000	/* bits used for sprite palette if in 16 colour mode */
#define OBJ_PRIORITY_SHIFT	10	/* shift right for sprite priority  */
#define OBJ_PALETTE_SHIFT	12	/* shift right for sprite palette if in 16 colour mode */
#define OBJ_PRIORITY_Q(r) (r<<OBJ_PRIORITY_SHIFT)
#define OBJ_PRIORITY_S(r) ((r<<OBJ_PRIORITY_SHIFT)&OBJ_PRIORITY_MASK)

#define OBJ_MAKE_Y( oldy, y ) (((oldy)&(~OBJ_Y_MASK))|((y)&OBJ_Y_MASK))
#define OBJ_MAKE_X( oldx, x ) (((oldx)&(~OBJ_X_MASK))|((x)&OBJ_X_MASK))
#define OBJ_MAKE_X_RS( oldx, x, rs ) (((oldx)&(~(OBJ_X_MASK|OBJ_ROTSCALE_MASK))|((x)&OBJ_X_MASK)|OBJ_ROTSCALE(rs))
#define OBJ_MAKE_TILE( oldtile, tile ) (((oldtile)&(~OBJ_TILE_MASK))|((tile)&OBJ_TILE_MASK))
#define OBJ_CREATE_TILE( tile, palette, priority ) (((tile)&OBJ_TILE_MASK) | (((priority)<<OBJ_PRIORITY_SHIFT)&OBJ_PRIORITY_MASK)|(((palette)<<OBJ_PALETTE_SHIFT)&OBJ_PALETTE_MASK))

#define OBJ_UPDATE_PALETTE(  oldtile, palette )  (((oldtile)&~OBJ_PALETTE_MASK)  | (((palette)<<OBJ_PALETTE_SHIFT)&OBJ_PALETTE_MASK))
#define OBJ_UPDATE_PRIORITY( oldtile, priority ) (((oldtile)&~OBJ_PRIORITY_MASK) | (((priority)<<OBJ_PRIORITY_SHIFT)&OBJ_PRIORITY_MASK))


#define BG_PAL		((Halfword*)(0x05000000)) /* Background palette 256 * 16bits */
#define OBJ_PAL		((Halfword*)(0x05000200)) /* Object (sprite) palette 256 * 16bits */

#define VRAM_BASE		((Halfword*)(0x06000000)) /* Vram base address ( can be accessed 16 bits at a time) */
#define VRAM_BASE_BYTE  ((Byte*)(0x06000000)) /* Vram base address as BytePtr */
#define VRAM_SIZE		0x00010000
#define VRAM_OBJ_BASE	((Halfword*)(0x06010000)) /* Vram address for object data (N.B. from what I can tell mode 4 infringes on this!) */
#define VRAM_OBJ_SIZE	0x00008000

#define VIDC_BASE		(0x04000000)			/* Video controller address as number            */
#define VIDC_BASE_WORD	((volatile Word*)VIDC_BASE)		/* Video controller address as word pointer      */
#define VIDC_BASE_HALF	((volatile Halfword*)VIDC_BASE)	/* Video controller address as half word pointer */
#define VIDC_BASE_BYTE	((volatile Byte*)VIDC_BASE)		/* Video controller address as byte pointer      */

#define DISPCNT		(*VIDC_BASE_HALF)		/* display control register */

/* register settings */
#define DISP_MODE(mode)	(mode&7)	/* Display mode */
#define DISP_OLD_GBC	0x0008		/* something to do with enableing gameboy colour mode !*/
#define DISP_BGPAGESEL	0x0010		/* mode 4/5 page select */
#define DISP_HBLPROC	0x0020		/* ???? */
#define DISP_OAM_1D		0x0040		/* Oam ordered in 1d mode */
#define DISP_OAM_2D		0x0000		/* Oam ordered in 2d mode */
#define DISP_DISABLE	0x0080		/* Display disabled */
#define DISP_BG0		0x0100		/* BG 0 enabled */
#define DISP_BG1		0x0200		/* BG 1 enabled */
#define DISP_BG2		0x0400		/* BG 2 enabled */
#define DISP_BG3		0x0800		/* BG 3 enabled */
#define DISP_OBJ		0x1000		/* Objects (sprites) enabled */
#define DISP_WINDOW(n)	((n&3)<<13)	/* Window select/enable (no docs YET)*/
#define DISP_OWNABLE	0x8000		/* ???? */


/**
 * The following should all be and compile to the same :)
 * one day I'll try and see which is the fastest.
 * #define DISPSTAT	(VIDC_BASE_HALF[2])
 * #define DISPSTAT	((Halfword*)(VIDC_BASE_HALF+4))
 * #define DISPSTAT	((Halfword*)(&(VIDC_BASE_BYTE[4]))
 * I've used the half word index 
 */
#define DISPSTAT	(VIDC_BASE_HALF[2])	/* current display status */
#define VCOUNT		(VIDC_BASE_HALF[3])	/* vertical row count     */

/* Background control registers */
#define BG0CNT		(VIDC_BASE_HALF[4])
#define BG1CNT     	(VIDC_BASE_HALF[5])
#define BG2CNT     	(VIDC_BASE_HALF[6])
#define BG3CNT     	(VIDC_BASE_HALF[7])

#define BG_PRIORITY(n)	(n&3)				/* Background priority */
#define BG_CHARBASE(n)	((n&0xC000)>>12)	/* Character Base 0x6000000 + n only setable in 0x4000 increments */
#define BG_CHARBASE_INDEX(index) ((index&3)<<2)		/* Character Base 0x6000000 + index*0x4000 */
#define BG_CHARBASE_0x06000000	0x0000
#define BG_CHARBASE_0x06004000	0x0004
#define BG_CHARBASE_0x06008000	0x0008
#define BG_CHARBASE_0x0600C000	0x000C

#define BG_MOSAIC		0x0040		/* Enable mosaic mode */
#define BG_COLOUR_256	0x0080		/* 256 Colours/Tile, 1 Palette */
#define BG_COLOUR_8bit	0x0080		/* 256 Colours/Tile, 1 Palette */
#define BG_COLOUR_16	0x0000		/* 16 Colours/Tile, 16 Palettes */
#define BG_COLOUR_4bit	0x0000		/* 16 Colours/Tile, 16 Palettes */

#define BG_MAPBASE(n)	((n&0xF800)>> 3 )			/* Map Base Address 0x6000000 + n only setable in 0x800 increments */
#define BG_MAPBASE_INDEX(index)	((index&0x1F)<<8)	/* Map Base Address 0x6000000 + index * 0x800 */

#define BG_WRAP			0x2000		/* Wrap Background at edges */
#define BG_NOWRAP		0x0000		/* Background is transparent at edges */

/* Map size */
/* Text (16 bit maps) */
/* as tiles */
#define BG_TEXT_32x32	0x0000
#define BG_TEXT_64x32	0x4000
#define BG_TEXT_32x64	0x8000
#define BG_TEXT_64x64	0xC000
/* as pixels */
#define BG_TEXT_256x256	0x0000
#define BG_TEXT_512x256	0x4000
#define BG_TEXT_256x512	0x8000
#define BG_TEXT_512x512	0xC000

/* N.B. the type of the map is dependant on the mode */
/* Rotatable (8 bit maps) */
/* as tiles */
#define BG_ROT_16x16		0x0000
#define BG_ROT_32x32		0x4000
#define BG_ROT_64x64		0x8000
#define BG_ROT_TILE_128x128	0xC000
/* as pixels */
#define BG_ROT_PIX_128x128	0x0000
#define BG_ROT_256x256		0x4000
#define BG_ROT_512x512		0x8000
#define BG_ROT_1024x1024	0xC000


/* Background scroll offset rigisters */
#define BG0X		(VIDC_BASE_HALF[8])
#define BG0Y		(VIDC_BASE_HALF[9])
#define BG1X		(VIDC_BASE_HALF[10])
#define BG1Y		(VIDC_BASE_HALF[11])
#define BG2X		(VIDC_BASE_HALF[12])
#define BG2Y		(VIDC_BASE_HALF[13])
#define BG3X		(VIDC_BASE_HALF[14])
#define BG3Y		(VIDC_BASE_HALF[15])


/**** 
 **** from here down is ripped from Matthew Tighe 
 **** Savage 3D point sprite demo. [http://www.matt-tighe.co.uk/gba]
 ****   Copyright (C)Savage Development 2001.
 **** 
 ****/
/* defined to is still compiles */
typedef Halfword    u16;
typedef Word        u32;


#define INPUT_BASE	0x4000130		// Control pad base register


#define MOSAIC		*(u16*)(VIDC_BASE + 0x4C)		// Mosaic Control
#define BLDMOD		*(u16*)(VIDC_BASE + 0x50)		// Blending ControlRegister
#define COLEV		*(u16*)(VIDC_BASE + 0x52)
#define COLY	    *(u16*)(VIDC_BASE + 0x54)

#define BLEND_ALPHA		(1 << 6)					// alpha blend between source and dest
#define BLEND_FADEIN	(2 << 6)					// Fade out
#define BLEND_FADEOUT	(3 << 6)					// Fade in

#define BLEND_SRC(n)	(n&0x3F)				// Blend source BOPPPP
#define BLEND_DEST(n)	((n&0x3F)<<8)			// Blend target

// DMA Registers
// --------------------------

#define DMAC_BASE	0x4000000

#define DMA3SAD		*(u32*)(DMAC_BASE + 0xD4)		// DMA3 Source Address
#define DMA3DAD		*(u32*)(DMAC_BASE + 0xD8)		// DMA3 Destination Address
#define DMA3CNT		*(u32*)(DMAC_BASE + 0xDC)		// DMA3 Length Counter

// Register Bits
// -------------------------------------------

#define STAT_VCOUNT_MASK	(0x000000FF)
#define STAT_VBL_MASK		(1 << 0)
#define STAT_HBL_MASK		(1 << 1)
#define STAT_VC_MASK		(0xFF << 8)
#define STAT_VC(n)			((n & 0x000000FF) << 8)
#define STAT_VBL_IRQ		(1 << 3)
#define STAT_HBL_IRQ		(1 << 4)
#define STAT_IRQ			(1 << 5)

// Control Pad Defines
// -------------------

#define PADREG		*(volatile u16 *)(INPUT_BASE)

#define PAD_BUTTONA	1
#define PAD_BUTTONB	2
#define PAD_SELECT	4
#define PAD_START	8
#define PAD_RIGHT	16
#define PAD_LEFT	32
#define PAD_UP		64
#define PAD_DOWN	128
#define PAD_BUTTONR	256
#define PAD_BUTTONL	512

// Helper Macros
// -------------------------------------------
#define RGB(r,g,b) ((((b)>>3)<<10)+(((g)>>3)<<5)+((r)>>3))

#endif /* GBA_SYSTEM_HEADER */


