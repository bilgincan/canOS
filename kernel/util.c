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
    int g = i / 2;

    char start;
    char end;

  while(i >= g && i != j){
    start = str[j];
    end = str[i];
    str[j++] = end;
    str[i--] = start;
  }
}
