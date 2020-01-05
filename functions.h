#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_STR_SIZE 2048

struct Queue
{
  char *str;
  int key;
};


void initSecMemo(char **A, int size);
void printMemo(char **A, int size, char *str);
void freeMemo(char **A, int size);
void initQueue(struct Queue **que, int qSize, char **A);
void write_(int key, char chr, struct Queue **que, int qSize, char ** A, int useLru);
void read_(int key, struct Queue **que, int qSize, char **A, int useLru);
void writeToFile(char *outFileName, char **A, int size);
void printQueue(struct Queue **que, int size);
void freeQueueMemo(struct Queue **que, int size);
struct Queue *pop(struct Queue **que, int size);
void append(char *str, char c);
void checksInput(int argc, char **argv);
void readInputFile(char **inStr, int size, char *inFileName);
int amountLines(char *inFileName, char ***inStr);
void make_commands();

#endif
