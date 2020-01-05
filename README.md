# Paging_emulator
 A program that simulates a virtual memory management system that implement the idea of "Paging"



- Run program via terminal in the same directory of "driver.c" and "inputFileName" files.  

- Output file is created automaticlly, just give it a name.  

- Compiling the program used "make" command (use some *nix OS).  

- Command to run the program (after compiling):  
	./driver isLRU inputFileName outputFileName m n  

    while:  
    driver - is the name of the executable file.  
    isLRU  - paging strategy. This parameter is an indicator of usage in a paging strategy. if useLRU=1 use "LRU" stragety, And for any other integer value use the "FIFO" stragety.  
    inputFileName - The name of the input file that contains the commands to the system.  
    outputFileName - The name of the output file to which we will write the output of the commands given to the system.  
    m - the size of the secondary memory.  
    n - the main memory size.  
    (** m>>n **)  

example: "./driver 1 inputFileName output 1000 5"  

**NOTE: The input file contain 3 commands(read, write, print), look the example input file attached "inputFileName".  

When running the program, run the 'htop' command at the same time from other terminal, and see the differnet cpu usage from other paging strategy,
(sudo apt install htop).


