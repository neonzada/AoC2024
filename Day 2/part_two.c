#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool checkSafe(int* arr, int size){
  bool isIncreasing = false;
  bool isDecreasing = false;
  for(int j = 0; j < size - 1; j++){
    int diff = arr[j+1] - arr[j];
    if(diff > 0) isIncreasing = true;
    if(diff < 0) isDecreasing = true;
    if((diff == 0) || (isIncreasing && isDecreasing) || (abs(diff) > 3)) return false;
  }
  return true;
}

int main(void){
  FILE *fp;
  if((fp = fopen("input.txt", "r")) == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  int sum = 0;
  int arr[50] = {0};
  char c[50];
  while(fgets(c, 50, fp)){
    int i = 0;
    char *token = strtok(c, " ");
    bool isSafe = true;
    while(token){
      int num = atoi(token);
      arr[i] = num;
      token = strtok(NULL, " ");
      i++;
    }

    // check if removing an element from the array makes the damn thing safe
    
    sum += checkSafe(arr, i);
  }
  printf("%d", sum);
}