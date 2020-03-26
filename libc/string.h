#ifndef STRINGS_H
#define STRINGS_H

#include "../cpu/types.h"

void int_to_ascii(int n, char str[]);
void print(char* str);
void print_int(u32 n);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
int strcontains(char s1[], char s2[]);
void print_hex(u32 n);
void hex_to_ascii(int n, char str[]);

#endif
