
#include "functions.h"

void printMemo(char **A, int size, char *str)
{
  printf("%s=[ ", str);
  for(int i=0; i<size-1 ; i++)
    printf("%s, ", A[i]);

  printf("%s]\n", A[size-1]);

}

void freeMemo(char **A, int size)
{
  for(int i=0 ; i < size ; i++)
    free(A[i]);

  free(A);
}

void freeQueueMemo(struct Queue **que, int size)
{
  for(int i=0 ; i < size ; i++)
  {
    free(que[i]->str);
    free(que[i]);
  }
  free(que);
}

void initSecMemo(char **A, int size)
{
  for(int i=0 ; i < size ; i++)
  {
    A[i] = (char *)malloc(sizeof(char) * MAX_STR_SIZE);
    strcpy(A[i], "");
  }
}

void printQueue(struct Queue **que, int size)
{
  printf("FirstMemory(Queue)=[ ");
  for(int i=0; i<size-1 ; i++)
  {
    printf("(%s,%d), ", que[i]->str, que[i]->key);
  }
  printf("(%s,%d)]\n", que[size-1]->str, que[size-1]->key);

}

void initQueue(struct Queue **que, int qSize, char **A)
{
  // Create Queue
  for(int i=0 ; i<qSize ; i++)
  {
    que[i] = (struct Queue *)malloc(sizeof(struct Queue));
    que[i]->str = (char *)malloc(sizeof(char) * MAX_STR_SIZE);
    que[i]->key = -1;
  }

  // Add the firsts n pages
  for(int i=0 ; i < qSize ; i++)
  {
    strcpy(que[i]->str, A[i]);
    que[i]->key = i;
  }

}

struct Queue *pop(struct Queue **que, int size)
{
  //save the pop var for return
  struct Queue *poppedVal  = (struct Queue *)malloc(sizeof(struct Queue));
  poppedVal->str = (char *)malloc(sizeof(char) * MAX_STR_SIZE);
  strcpy(poppedVal->str, que[0]->str);
  poppedVal->key = que[0]->key;

  //poping
  for(int i=0 ; i<size-1 ; i++)
  {
    strcpy(que[i]->str, que[i+1]->str);
    que[i]->key = que[i+1]->key;
  }
  return poppedVal;
}

void append(char *str, char c)
{
  int len = strlen(str);
  str[len] = c;
  str[len+1] = '\0';
}

void checksInput(int argc, char **argv)
{
  int flag=0;

  //checks amount of params
  if(argc != 6)
  {
    printf("Incorrect amount of parameters!\n");
    exit(1);
  }

  //checks useLru is integer
  for(int i=0 ; i<strlen(argv[1]) ; i++)
    if(argv[1][i] < '0' || argv[1][i] > '9')
      flag=1;

  //checks m is an integer
  for(int i=0 ; i<strlen(argv[4]) ; i++)
    if(argv[4][i] < '0' || argv[4][i] > '9')
      flag=1;

  //checks n is an integer
  for(int i=0 ; i<strlen(argv[5]) ; i++)
    if(argv[5][i] < '0' || argv[5][i] > '9')
      flag=1;


  if(flag == 1)
  {
    printf("Invalid integer !!!\n");
    exit(1);
  }

  //checks if m<=n
  if(atoi(argv[4]) <= atoi(argv[5]))
    {
      printf("ERROR: first memory can't be bigger then second memory!\n");
      exit(1);
    }
}

int amountLines(char *inFileName, char ***inStr)
{
  char str[MAX_STR_SIZE];
  int size=0;
  FILE *fp = fopen(inFileName, "r");

  if(fp == NULL)
  {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  //read amount of lines
  while(fgets(str, MAX_STR_SIZE, fp) != NULL)
    size++;

  // goto position 0 in file
  FILE *fp2 = fopen(inFileName, "r");
  rewind(fp);
  fclose(fp2);
  fclose(fp);

  //alloc memory to inStr value
  *inStr = (char **)malloc(sizeof(char *) * size);

  return size;

}

void readInputFile(char **inStr, int size, char *inFileName)
{
  char str[MAX_STR_SIZE];
  int index=0;
  FILE *fp = fopen(inFileName, "r");

  for(int i=0 ; i<size ; i++)
    inStr[i] = (char *)malloc(sizeof(char) * MAX_STR_SIZE);

  while(fgets(str, MAX_STR_SIZE, fp) != NULL) // read lines from file.
    strcpy(inStr[index++], str);

  fclose(fp);
}

void writeToFile(char *outFileName, char **A, int size)
{
  FILE *fp = fopen(outFileName, "w+");

  if(fp == NULL)
  {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);

  fputs("secondaryMemory=[", fp);
  for(int i=0; i<size-1 ; i++)
  {
    fputs(A[i], fp);
    fputs(", ", fp);
  }
  fputs(A[size-1], fp);
  fputs("]\n", fp);

  fseek(fp, 0, SEEK_SET);
  fclose(fp);

}
