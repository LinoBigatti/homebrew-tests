unsigned short input_cur = 0x03FF;
unsigned short input_prev = 0x03FF;

inline void key_poll()
{
    input_prev = input_cur;
    input_cur = REG_KEYINPUT | KEY_MASK;
}

inline unsigned short wasKeyPressed(unsigned short key_code)
{
    return (key_code) & (~input_cur & input_prev);
}

inline unsigned short wasKeyReleased(unsigned short key_code)
{
    return  (key_code) & (input_cur & ~input_prev);
}

inline unsigned short getKeyState(unsigned short key_code)
{
    return !(key_code & (input_cur) );
}

s8 key_tri_h() {
	s8 x = 0;
	if (getKeyState(KEY_LEFT)) {x -= 1;}
	if (getKeyState(KEY_RIGHT)) {x += 1;}
	return x;
}

s8 key_tri_v() {
	s8 y = 0;
	if (getKeyState(KEY_DOWN)) {y += 1;}
	if (getKeyState(KEY_UP)) {y -= 1;}
	return y;
}

s8 key_tri_s() {
	s8 s = 0;
	if (getKeyState(KEY_R)) {s += 1;}
	if (getKeyState(KEY_L)) {s -= 1;}
	return s;
}