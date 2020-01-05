#include "functions.h"

void make_commands()
{
  int pipefd[2];
  int pipefd2[2];

  pipe(pipefd); // create pipe

  if(fork()==0)
  {
    dup2(pipefd[1],1); // send stdout to pipe
    close(pipefd[0]);
    close(pipefd[1]);
    execlp("cat", "cat", "./sample.txt", NULL);

    perror("cat faild!");
    exit(1);
  }

  pipe(pipefd2); // create second pipe

  if(fork()==0)
  {
    dup2(pipefd[0],0); // get stdout from pipe
    dup2(pipefd2[1],1); // send stdout to second pipe
    close(pipefd[0]);
    close(pipefd[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);
    execlp("grep", "grep", "-v","a", NULL);

    perror("grep faild!");
    exit(1);
  }

  close(pipefd[0]);
  close(pipefd[1]);

  if(fork()==0)
  {
    dup2(pipefd2[0],0);
    close(pipefd2[0]);
    close(pipefd2[1]);
    execlp("sort", "sort", "-r", NULL);

    perror("sort faild!");
    exit(1);
  }
  else{
    close(pipefd2[0]);
    close(pipefd2[1]);
  }

}
