#define USHORT unsigned short
#define u8 unsigned short

#include "my_tiles.h" /* 64x32 pixel pcx, converted by pcx2gba */
#include "my_map.h" /* 512x512 tile map, exported by the map editor */

int main(void) {

   int tile_setCharBaseBlock = 1;
   int my_mapScreenBaseBlock = 28;
   int i;

/* 
Initialize the display */
*(unsigned short*)0x04000000 = 0x0 | 0x400;

/* Load the palette */
unsigned short *tilePalette = (unsigned short*)0x05000000;
for(i = 0; i < 256; i++) {
      tilePalette[i] = my_tilespal[i];
}

/* Load the tiles */
unsigned short *tileData = 
  (unsigned short*)( 0x06000000 + (tile_setCharBaseBlock * 0x4000) ); 
for(i = 0; i < (my_tiles_WIDTH * my_tiles_HEIGHT) / 2; i++) { 
   tileData[i] = my_tilesdata[i]; 
}

/* Load the map */
unsigned short *tileMap =
  (unsigned short*) ( 0x6000000 + (my_mapScreenBaseBlock*0x800) ); 
unsigned short *myMapData = (unsigned short*)my_map;
for(i = 0; i < (64 * 64) / 2; i++) {
     tileMap[i] = myMapData[i];
}

/* Load the map into BG2 */
*(unsigned short*)0x400000C = (tile_setCharBaseBlock << 2)
   | (my_mapScreenBaseBlock << 8) | 0x80 | 0x8000;

}