void setmode(mode, bg) {
	*(unsigned int*)IO = mode | bg;
}

inline u16 MakeCol(u8 red, u8 green, u8 blue)
{
    return (red & 0x1F) | (green & 0x1F) << 5 | (blue & 0x1F) << 10;
}

void drawRect(struct vector2 position, struct vector2 dimensions, u16 clr)
{
    for (int y = 0; y < dimensions.y; ++y)
    {
        for (int x = 0; x < dimensions.x; ++x)
        {
    	   SCREENBUFFER[(position.y + y) * SCREEN_W + position.x + x] = clr;
        }
    }
}

inline void vsync()
{
  while (REG_VCOUNT >= 160)) {}
  while (REG_VCOUNT < 160)) {}
}

void moveRect(struct vector2 position, struct vector2 nextposition, struct vector2 dimensions, u16 clr, u16 bg_clr)
{
	drawRect(position, dimensions, bg_clr);
	drawRect(nextposition, dimensions, clr);
}