#include "pseudo_terminal.h"

//compile with: gcc -o terminal pseudo_terminal.c  terminal.c $(pkg-config --cflags --libs gtk+-3.0)
int main(int argc, char* argv[]){
    init_gtk(argc, argv);
    return 0;
}