#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(void){
  FILE* fp;
  if((fp = fopen("input.txt", "r")) == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  const char *pattern = "mul(";
  const char *donut = "don't()";
  int doIdx = 0;
  int pIdx = 0;

  bool enabled = true;

  int numIdx = 0;
  char buffer[3][4] = {{0}}; //its best to store nums in this buffer and later strtol() them
  long sum = 0;
  int c;

  while((c = fgetc(fp)) != EOF){

    //do() & don't() logic
    if(doIdx == 6 && c == ')'){
      enabled = false;
      doIdx = 0;
    }
    if(c == donut[doIdx]){
      doIdx++;
    }else if(doIdx == 2 && c == '('){
      enabled = true;
      doIdx = 0;
    }else{
      doIdx = 0;
    }
    if(enabled){
      if(pIdx < 4){
        if(c == pattern[pIdx]){
          pIdx++;
        }else{
          pIdx = 0; //reset lol
        }
      }else if(isdigit(c) && numIdx < 3){ //storing nums here
        int len = strlen(buffer[numIdx]);
        if (len < 3) {
          buffer[numIdx][len] = c;
          buffer[numIdx][len + 1] = '\0';
        }
      }else if(c == ',' && numIdx == 0){
        numIdx = 1;
      }else if(c == ')' && numIdx == 1){
        //do mult stuff
        long num1 = strtol(buffer[0], NULL, 10);
        long num2 = strtol(buffer[1], NULL, 10);
        sum += num1 * num2;

        //reset logic for next match
        pIdx = 0;
        numIdx = 0;
        for(int i = 0; i < 2; i++)
          buffer[i][0] = '\0';
      }else{ //reset logic on every invalid character
        pIdx = 0;
        numIdx = 0;
        for(int i = 0; i < 2; i++){
          buffer[i][0] = '\0';
        }
      }
    }
  }
  printf("%ld", sum);
}