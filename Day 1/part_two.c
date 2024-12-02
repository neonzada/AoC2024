#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Compare(const void* a, const void* b){
  return (*(int*)a - *(int*)b);
}

int main(void){
  FILE *fp;
  if((fp = fopen("input.txt", "r")) == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  int lists[2][1000];
  char c[15];
  int i = 0, j = 0;

  while(fgets(c, 15, fp)){
    char *token = strtok(c, " ");
    while(token){
      int num = atoi(token);
      lists[i][j] = num;
      token = strtok(NULL, " ");
      i ? i-- : i++;
    }
    j++;
  }

  qsort(lists[0], sizeof(lists[0]) / sizeof(int), sizeof(int), Compare);
  qsort(lists[1], sizeof(lists[1]) / sizeof(int), sizeof(int), Compare);
  int sum = 0;
  j = 0;
  for(int i = 0; i < sizeof(lists[0]) / sizeof(int); i++){
    while(lists[0][j] < lists[1][i]){
      j++;
    }
    if(lists[0][j] == lists[1][i]) sum += lists[1][i];
  }
  printf("%d", sum);

  fclose(fp);
  return 0;
}