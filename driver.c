
#include "functions.h"

int main(int argc, char *argv[])
{
  clock_t start, end;
  double runTime;

  start = clock();

  checksInput(argc, argv);

  int useLru = atoi(argv[1]); //choosing paging-managment (1 = LRU, else FIFO)
  char * inFileName = argv[2];
  char * outFileName = argv[3];
  int m = atoi(argv[4]); //sec memo size
  int n = atoi(argv[5]); //first  memo size
  char **inStr; //strings array for input file

  //read from file
  int inStrSize = amountLines(inFileName, &inStr);
  readInputFile(inStr, inStrSize, inFileName);

  //init secondary and first memorys
  char **A = (char **)malloc(sizeof(char *) * m); //secondary memory
  initSecMemo(A, m);
  struct Queue **queue = (struct Queue **)malloc(sizeof(struct Queue *) * n); //alloc memory for queue (first memo)
  initQueue(queue, n, A);

  printQueue(queue, n);
  
  // Execute commands line by line
  for(int line=0 ; line<inStrSize ; line++)
  {
    char command = '\0';
    int key;
    char ch = '\0';
    char word[MAX_STR_SIZE]="\0";
    int i=0;

    // Find command
    for( ; i<strlen(inStr[line]) ; i++)
    {
      append(word,inStr[line][i]);

      if(strcmp(word, "print") == 0)
        command = 'p';
      if(strcmp(word, "write") == 0)
        command = 'w';
      if(strcmp(word, "read") == 0)
        command = 'r';

      if (command != '\0') {
        strcpy(word,"");
        break;
      }
    }//endfor
    if(command == 'p')
    {
      writeToFile(outFileName, A, m);
      continue;
    }

    // Find key.
    i+=2;
    for( ; i<strlen(inStr[line]) ; i++)
    {
      append(word,inStr[line][i]);

      if(inStr[line][i] == ' ' || inStr[line][i] == '\n')
      {
        key = atoi(word);
        strcpy(word,"");
        break;
      }
    }//endfor

    if(key >= m)
    {
      printf("ERROR: input!\n");
      exit(EXIT_FAILURE);
    }

    if(command == 'r')
    {
      read_(key, queue, n, A, useLru);
      continue;
    }

    // Find ch.
    i++;
    strcpy(word,"");
    for( ; i<strlen(inStr[line]) ; i++)
    {
      append(word,inStr[line][i]);
      if(inStr[line][i] == '\n')
      {
        ch = word[0];
        strcpy(word,"");
        break;
      }
    }//endfor
    if(command == 'w')
    {
      write_(key, ch, queue, n, A, useLru);
      printQueue(queue, n);
      continue;
    }
  }// end for.

  end = clock();
  runTime = (end - start) / (double) CLOCKS_PER_SEC;
  printf("runTime: %g\n", runTime);

  freeMemo(inStr, inStrSize); // free strings input array
  freeMemo(A, m); // free secondary memory
  freeQueueMemo(queue, n); // free queue memory

  return 0;

}
