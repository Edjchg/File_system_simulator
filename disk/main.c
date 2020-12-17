#include "disk.h"
// gcc -o main main.c ../structure/structure.c disk.c
int main(){

    file *f = malloc(sizeof(file));
    f->file_name = "hola";
    f->owner = "";
    f->creation_date = "25/01/1998";
    f->last_mod = "11/12/2020";
    f->blocks[0] = 1;

    char * data = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam id commodo mi. Vivamus ultrices erat sed tortor tincidunt laoreet. Nam non condimentum magna. Cras consectetur nisi sit amet tempor tempor. Ut interdum massa vitae imperdiet tempor. Morbi ac consequat odio. Phasellus sagittis molestie pulvinar";
    f->bytes = strlen(data);
    //init_disk(6);
    //new_item(f);
    printf("%s\n", get_info("modification", "2"));
    //add_data(f, data);
    //char * temp = malloc(sizeof(char)*10);
    //sprintf(temp, "%d", f->blocks[0]);
    //delete_file(temp);

/*
    char * temp_block = (char*)malloc(sizeof(f->blocks[0])+1000);
    sprintf(temp_block, "%d", f->blocks[0]);
    char * data_complete = get_info("data", temp_block);
    printf("%s\n", data_complete);*/

    return 0;
}