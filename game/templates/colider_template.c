#include "OpenEngine.h"
#include "OpenGraphics.h"
#include "OpenInput.h"

void loop();

vector2 playerpos;
vector2 playerposnext;
vector2 playerdimensions;
vector2 floorpos;
vector2 floordimensions;

void main() {
	for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
    {
    	SCREENBUFFER[i] = MakeCol(0,0,31);
    }
	setmode3();
	playerpos.x = 100;
	playerpos.y = 0;
	playerposnext.x = 100;
	playerposnext.y = 0;
	playerdimensions.x = 10;
	playerdimensions.y = 10;
	floorpos.x = 0;
	floorpos.y = (SCREEN_H - 10);
	floordimensions.x = 240;
	floordimensions.y = 10;
	drawRect(playerpos, playerdimensions, MakeCol(0,31,0));
	drawRect(floorpos, floordimensions, MakeCol(31, 0, 0));
	loop();
	return 0;
}

void loop() {
	while(1) {
		vsync();
		while (!(box2d_col(playerpos, floorpos, playerdimensions, floordimensions))) {
			
		}
		playerposnext.y = gravity(playerpos.y);
		moveRect(playerpos, playerposnext, playerdimensions, MakeCol(0,31,0), MakeCol(0,0,31));
		playerpos.y = playerposnext.y;
	}
}