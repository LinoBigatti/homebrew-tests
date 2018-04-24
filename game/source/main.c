
#include "OpenEngine.h"
#include "OpenGraphics.h"
#include "OpenInput.h"

#include "my_tiles.h"
#include "my_map.h"

int main(void) {

	int tile_setCharBaseBlock = 1;
	int my_mapScreenBaseBlock = 28;
	int i;
	bool pause = false;
	vector2 bg_pos;

	setmode(DCNT_MODE0, DCNT_BG2);

	unsigned short *tilePalette = PALETTEBUFFER;
	for(i = 0; i < 256; i++) {
		tilePalette[i] = my_tilespal[i];
	}

	unsigned short *tileData = (unsigned short*)( SCREENBUFFER + (tile_setCharBaseBlock * 0x4000) ); 
	loadmem(tileData, my_tilesdata, (my_tiles_WIDTH * my_tiles_HEIGHT));

	unsigned short *tileMap = (unsigned short*) ( SCREENBUFFER + (my_mapScreenBaseBlock*0x800) ); 
	unsigned short *myMapData = (unsigned short*)my_map;
	loadmem(tileMap, myMapData, (64 * 64));

	REG_BG2CNT = (tile_setCharBaseBlock << 2) | (my_mapScreenBaseBlock << 8) | 0x80 | 0x8000;
	
    while(1)
    {
        vsync();
        key_poll();
		
		if (wasKeyPressed(KEY_START)) {
			if (pause) {
				pause = false;
			} else if (!(pause)) {
				pause = true;
			}
		}
		
		if (!(pause)) {
			bg_pos.x += key_tri_h();
			bg_pos.y += key_tri_v();
	
			REG_BG2HOFS = bg_pos.x;
			REG_BG2VOFS = bg_pos.y;
		} else {
			if (getKeyState(KEY_A)) {
				SaveMemory[0] = bg_pos.x;
				SaveMemory[2] = bg_pos.y;
			} else if (getKeyState(KEY_B)) {
				bg_pos.x = SaveMemory[0];
				bg_pos.y = SaveMemory[2];
				REG_BG2HOFS = bg_pos.x;
				REG_BG2VOFS = bg_pos.y;
			}
		}
	}
}