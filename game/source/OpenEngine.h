//incluyendo librerias propias de C

#include <stdint.h>
#include <stdbool.h>

//definimos regiones, modos y valores

#define GAMEPAK_RAM ((volatile uint8_t*)0x0E000000)

unsigned short *SaveMemory[0xFFFF] = GAMEPAK_RAM;

#define SCREENBUFFER ((volatile u8*)0x06000000)

#define IO 0x04000000

#define REG_VCOUNT (* (volatile u16*) 0x04000006

#define SCREEN_W 240

#define SCREEN_H 160

#define PALETTEBUFFER ((volatile u8*)0x05000000)


#define REG_KEYINPUT (* (volatile unsigned short*) 0x4000130)

#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_R 0x0100
#define KEY_L 0x0200

#define KEY_MASK     0xFC00

//gran trozo de codigo proveniente de las librerias de tonc



#define REG_BG0CNT			*(vu16*)(IO+0x0008)	// bg 0-3 control
#define REG_BG1CNT			*(vu16*)(IO+0x000A)
#define REG_BG2CNT			*(vu16*)(IO+0x000C)
#define REG_BG3CNT			*(vu16*)(IO+0x000E)

#define REG_BG0HOFS			*(vu16*)(IO+0x0010)		// bg 0-3 origins
#define REG_BG0VOFS			*(vu16*)(IO+0x0012)
#define REG_BG1HOFS			*(vu16*)(IO+0x0014)
#define REG_BG1VOFS			*(vu16*)(IO+0x0016)
#define REG_BG2HOFS			*(vu16*)(IO+0x0018)
#define REG_BG2VOFS			*(vu16*)(IO+0x001A)
#define REG_BG3HOFS			*(vu16*)(IO+0x001C)
#define REG_BG3VOFS			*(vu16*)(IO+0x001E)

#define BG_MOSAIC			0x0040	//!< Enable Mosaic
#define BG_4BPP					 0	//!< 4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP				0x0080	//!< 8bpp (256 color) bg (no effect on affine bg)
#define BG_WRAP				0x2000	//!< Wrap around edges of affine bgs
#define BG_SIZE0				 0
#define BG_SIZE1			0x4000
#define BG_SIZE2			0x8000
#define BG_SIZE3			0xC000
#define BG_REG_32x32			 0	//!< reg bg, 32x32 (256x256 px)
#define BG_REG_64x32		0x4000	//!< reg bg, 64x32 (512x256 px)
#define BG_REG_32x64		0x8000	//!< reg bg, 32x64 (256x512 px)
#define BG_REG_64x64		0xC000	//!< reg bg, 64x64 (512x512 px)
#define BG_AFF_16x16			 0	//!< affine bg, 16x16 (128x128 px)
#define BG_AFF_32x32		0x4000	//!< affine bg, 32x32 (256x256 px)
#define BG_AFF_64x64		0x8000	//!< affine bg, 64x64 (512x512 px)
#define BG_AFF_128x128		0xC000	//!< affine bg, 128x128 (1024x1024 px)

#define BG_PRIO_MASK	0x0003
#define BG_PRIO_SHIFT		0
#define BG_PRIO(n)		((n)<<BG_PRIO_SHIFT)

#define BG_CBB_MASK		0x000C
#define BG_CBB_SHIFT		 2
#define BG_CBB(n)		((n)<<BG_CBB_SHIFT)

#define BG_SBB_MASK		0x1F00
#define BG_SBB_SHIFT		 8
#define BG_SBB(n)		((n)<<BG_SBB_SHIFT)

#define BG_SIZE_MASK	0xC000
#define BG_SIZE_SHIFT		14
#define BG_SIZE(n)		((n)<<BG_SIZE_SHIFT)

#define DCNT_MODE0				 0	//!< Mode 0; bg 0-4: reg
#define DCNT_MODE1			0x0001	//!< Mode 1; bg 0-1: reg; bg 2: affine
#define DCNT_MODE2			0x0002	//!< Mode 2; bg 2-2: affine
#define DCNT_MODE3			0x0003	//!< Mode 3; bg2: 240x160\@16 bitmap
#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_MODE5			0x0005	//!< Mode 5; bg2: 160x128\@16 bitmap
#define DCNT_GB				0x0008	//!< (R) GBC indicator
#define DCNT_PAGE			0x0010	//!< Page indicator
#define DCNT_OAM_HBL		0x0020	//!< Allow OAM updates in HBlank
#define DCNT_OBJ_2D				 0	//!< OBJ-VRAM as matrix
#define DCNT_OBJ_1D			0x0040	//!< OBJ-VRAM as array
#define DCNT_BLANK			0x0080	//!< Force screen blank
#define DCNT_BG0			0x0100	//!< Enable bg 0
#define DCNT_BG1			0x0200	//!< Enable bg 1
#define DCNT_BG2			0x0400	//!< Enable bg 2
#define DCNT_BG3			0x0800	//!< Enable bg 3
#define DCNT_OBJ			0x1000	//!< Enable objects
#define DCNT_WIN0			0x2000	//!< Enable window 0
#define DCNT_WIN1			0x4000	//!< Enable window 1
#define DCNT_WINOBJ			0x8000	//!< Enable object window

//definimos las variables de GBA_types

typedef	uint8_t		u8;	/**< Unsigned 8 bit value	*/
typedef	uint16_t	u16;	/**< Unsigned 16 bit value	*/
typedef	uint32_t	u32;	/**< Unsigned 32 bit value	*/
typedef	int8_t		s8;	/**< Signed 8 bit value	*/
typedef	int16_t		s16;	/**< Signed 16 bit value	*/
typedef	int32_t		s32;	/**< Signed 32 bit value	*/
typedef	volatile u8	vu8;	/**< volatile Unsigned 8 bit value	*/
typedef	volatile u16	vu16;	/**< volatile Unigned 16 bit value	*/
typedef	volatile u32	vu32;	/**< volatile Unsigned 32 bit value	*/
typedef	volatile s8	vs8;	/**< volatile Signed 8 bit value	*/
typedef	volatile s16	vs16;	/**< volatile Signed 8 bit value	*/
typedef	volatile s32	vs32;	/**< volatile Signed 8 bit value	*/

//definicion de vectores espaciales

struct vector {
	int x;
};

struct vector2 {
	int x;
	int y;
};

struct vector3 {
	int x;
	int y;
	int z;
};

typedef struct vector vector;
typedef struct vector2 vector2;
typedef struct vector3 vector3;

struct box {
	vector2 A;
	vector2 B;
	vector2 C;
	vector2 D;
};

typedef struct box box;

//definicion de otras variables

int g = 5;

//definicion de funciones fisicas

int gravity(int position)
{
	position += g;
	if (position >= SCREEN_H + 10)
	{
		position -= g;
	}
	return position;
}

box boxcreator(vector2 box1, vector2 box1d) {
	box boxreturned;
	boxreturned.A.x = box1.x;
	boxreturned.A.y = box1.y;
	boxreturned.B.x = box1.x + box1d.x;
	boxreturned.B.y = box1.y;
	boxreturned.C.x = box1.x;
	boxreturned.C.y = box1.y + box1d.y;
	boxreturned.D.x = box1.x + box1d.x;
	boxreturned.D.y = box1.y + box1d.y;
	return boxreturned;
}

bool box2d_col(vector2 box1, vector2 box2, vector2 box1d, vector2 box2d) {
	box box1b = boxcreator(box1, box1d);
	box box2b = boxcreator(box2, box2d);
	if ((box2b.B.x < box1b.A.x) || (box2b.A.x > box1b.B.x)) {
		return true;
	} else if ((box2b.D.y < box1b.C.y) || (box2b.C.y > box1b.D.y)) {
		return true;
	} else {
		return false;
	}
}

void loadmem(volatile unsigned short* reg[], unsigned short* data[], int length) {
	for(int i = 0; i < (length) / 2; i++) {
		reg[i] = data[i];
	}
}

