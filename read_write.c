
#include "functions.h"

void read_(int key, struct Queue **que, int qSize, char **A, int useLru)
{
  int flag = 0;
  int index;
  char tmp_str[MAX_STR_SIZE];

  for(int i=0; i < qSize ; i++) // checks page in first memory.
  {
    if(que[i]->key == key)
    {
      // Return data of page from Queue to the secondary memory (queue)
      strcpy(A[key], que[key]->str);
      flag = 1;
      index=i;
      strcpy(tmp_str, que[i]->str);
      break;
    }
  }

  if(flag == 1 && useLru == 1) //update queue for Lru
  {
    for(int i=index ; i<qSize-1 ; i++)
    {
      strcpy(que[i]->str, que[i+1]->str);
      que[i]->key = que[i+1]->key;
    }
    strcpy(que[qSize-1]->str, tmp_str);
    que[qSize-1]->key = key;
  }

  if(flag == 0) //if page in second memory
  {
    struct Queue *tmp = pop(que, qSize); //pop from queue (FIFO)
    strcpy(A[tmp->key], tmp->str); //save popped val in second memory (A)
    free(tmp->str); //free str tmp
    free(tmp);  // free tmp

    //add page to the first memory (queue)
    strcpy(que[qSize-1]->str, A[key]);
    que[qSize-1]->key = key;

  }

}

void write_(int key, char chr, struct Queue **que, int qSize, char ** A, int useLru)
{
  int flag = 0;
  char tmp_str[MAX_STR_SIZE];
  int index;

  for(int i=0; i < qSize ; i++) // searching page in first memory.
  {
    if(que[i]->key == key) //if page in first memory(queue) -> update it
    {
      flag = 1;
      append(que[i]->str, chr); //concatenate char to the end of a string
      index=i;
      strcpy(tmp_str, que[i]->str);

      break;
    }
  }//endfor

  if(flag == 1 && useLru == 1) //update queue for Lru
  {
    for(int i=index ; i<qSize-1 ; i++)
    {
      strcpy(que[i]->str, que[i+1]->str);
      que[i]->key = que[i+1]->key;
    }
    strcpy(que[qSize-1]->str, tmp_str);
    que[qSize-1]->key = key;
  }


  if(flag == 0) //if page in second memory
  {
    struct Queue *tmp = pop(que, qSize); //pop from queue (FIFO)
    strcpy(A[tmp->key], tmp->str); //save popped val in second memory (A)
    free(tmp->str); //free str tmp
    free(tmp);  // free tmp

    //add page to the first memory (queue)
    strcpy(que[qSize-1]->str, A[key]);
    que[qSize-1]->key = key;
    append(que[qSize-1]->str, chr);
  }

}
