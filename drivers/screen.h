#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define GREEN_ON_BLACK 0x0a
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#include "../cpu/types.h"

/* Public kernel API */
void clear_screen();
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void print_int_to_screen(u32 n);
void print_hex_to_screen(u32 n);

void kprint_backspace();
