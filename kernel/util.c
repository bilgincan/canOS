#include "util.h"

void memory_copy(char* source, char *dest, int nbytes){
  for(int i = 0;  i < nbytes; i++){
    *(dest + i) = *(source + i);
  }
}

void int_to_ascii(int n, char str[]){
  int i = 0;
  int sign = 0;

  if(n < 0){
    sign = -1;
    //two-compliment of the n if it is negative
    n = (!n) + 1;
  }
  do{
    str[i++] = (n % 10) + '0';
  }while((n = n / 10) > 0);

  if(sign == -1){
    str[i++] = '-';
  }
    str[i--] = 0; //-1, because I dont want to reverse the (0 char) -> end of the string
    char tmp[] = {0};
    int j = 0;

  for(i; i >= 0; i--){
    tmp[j] = str[i];
    j++;
  }
  str = tmp;
}

void print_int(int n){
  char str[20];
  int_to_ascii(n, str);
  kprint(str);
}
