#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pseudo_terminal.h"

#include "../structure/tree_parser.h"
//Compile with: gcc -o terminal  terminalV2.c ../disk/disk.c ../structure/structure.c pseudo_terminal.c $(pkg-config --cflags --libs gtk+-3.0)

int main(int argc, char* argv[]){
    char command[10000];
    //init_disk(atoi(argv[1]));
    tree_parser_rd("../structure/output.dat");
    //init_root();
    printf("----- Pseudo terminal. -----\n");
    while (1)
    {
        //printf("$ ");
        char command[1000000];
        //scanf("%s\n", command);
        fgets (command, sizeof(command), stdin);
        printf("%s\n", command);
        parse_command(command);
        memset(command, 0, strlen(command));
    } 
}