#include "disk.h"
#include "../structure/structure.h"

int main(){

    file *f = malloc(sizeof(file));
    f->file_name = "hola";
    f->owner = "";
    f->creation_date = "25/01/1998";
    f->last_mod = "11/12/2020";
    f->bytes = 36;
    f->blocks[0] = 1;

    char * data = "111111000000222222333333444444555555";
    
    //init_disk(6);
    //new_item(f);
    //add_data(f, data);
    char * temp = malloc(sizeof(char)*10);
    sprintf(temp, "%d", f->blocks[0]);
    delete_file(temp);

    return 0;
}