#include "string.h"
#include "../drivers/screen.h"

void int_to_ascii(int n, char str[]){
  int i = 0;
  int sign = 0;

  if(n < 0){
    sign = -1;
    //two-compliment of the n if it is negative
    n = -n;
  }
  do{
    str[i++] = (n % 10) + '0';
  }while((n = n / 10) > 0);

  if(sign == -1){
    str[i++] = '-';
  }
    str[i--] = 0; //-1, because I dont want to reverse the (0 char) -> end of the string
    int j = 0;

    char tmp;

  while(i > j){
    tmp = str[j];
    str[j++] = str[i];
    str[i--] = tmp;
  }
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}


void print(char* str){
  kprint(str);
}

void print_int(u32 n){
  print_int_to_screen(n);
}

void print_hex(u32 n){
  print_hex_to_screen(n);
}

int strlen(char s[]){
  int i = 0;
  while(s[i] != 0) i++;
  return i;
}

void backspace(char s[]){
    int len = strlen(s);
    s[len-1] = '\0';
}

void append(char s[], char n){
  int len = strlen(s);
  s[len++] = n;
  s[len] = 0;
}

// Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

//if s1 contains s2, it returns 0 otherwise -1
int strcontains(char s1[], char s2[]){
    int s1len = strlen(s1);
    int s2len = strlen(s2);

    //controll if s1 longer than s2, so it can contain s2 in it
    if(s2len > s1len) return -1;

    for(int i = 0; i < s2len; i++){
        if(s1[i] != s2[i]) return -1;
    }
    return 0;
}
