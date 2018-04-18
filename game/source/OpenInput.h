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
