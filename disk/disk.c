#include "disk.h"

int block_cont = 0;
int block_size_;
const char * path = "disk.txt";
const char * path_aux = "replace.txt";
const char * bval_start = "<bit>";
const char * bval_end = "</bit>";
const char * num_block_start = "<numblock>";
const char * num_block_end = "</numblock>";
const char * next_block_start = "<nextblock>";
const char * next_block_end = "</nextblock>";
const char * name_start = "<name>";
const char * name_end = "</name>";
const char * owner_start = "<owner>";
const char * owner_end = "</owner>";
const char * creation_start = "<creation>";
const char * creation_end = "</creation>";
const char * modification_start = "<modification>";
const char * modification_end = "</modification>";
const char * size_start = "<size>";
const char * size_end = "</size>";
const char * data_start = "<data>";
const char * data_end = "</data>";

void init_disk(int block_size){
    FILE * fPtr;
    fPtr = fopen(path, "w");
    if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    block_size_ = block_size;
    file *f = malloc(sizeof(file));
    f->file_name = "";
    f->owner = "";
    f->creation_date = "";
    f->last_mod = "";
    f->bytes = 0;
    char * data = "";

    char * block_ = malloc(sizeof(char)*10);

    for (int i = 1; i <= 1000; i++){
        sprintf(block_, "%d", i);
        char * res = create_block(f, "0", block_, block_, data);
        fputs(res, fPtr);
    }
    fclose(fPtr);
    printf("Se creó el disco de almacenamiento\n");
}

void new_item(file *file_){
    char * avalaible_block = find("block", get_free_block());
    char * bit = "1";
    char * data = " ";
    replace_block(avalaible_block, file_, avalaible_block, bit, data);
    printf("File %s added succesfull to disk to block number %s\n", file_->file_name, avalaible_block);
    file_->blocks[0] = atoi(avalaible_block);
}

char * create_block(file *file_, char *bval, char *act_block, char *next_block, char * data){
    char * save = malloc(sizeof(char)*file_->bytes + 500);
    strcpy(save, bval_start);
    strcat(save, bval);
    strcat(save, bval_end);

    strcat(save, num_block_start);
    strcat(save, act_block);
    strcat(save, num_block_end);

    strcat(save, next_block_start);
    strcat(save, next_block);
    strcat(save, next_block_end);

    strcat(save, name_start);
    strcat(save, file_->file_name);
    strcat(save, name_end);

    strcat(save, owner_start);
    strcat(save, file_->owner);
    strcat(save, owner_end);

    strcat(save, creation_start);
    strcat(save, file_->creation_date);
    strcat(save, creation_end);

    strcat(save, modification_start);
    strcat(save, file_->last_mod);
    strcat(save, modification_end);

    char conv[100];
    sprintf(conv, "%d", file_->bytes);
    strcat(save, size_start);
    strcat(save, conv);
    strcat(save, size_end);

    strcat(save, data_start);
    strcat(save, data);
    strcat(save, data_end);

    strcat(save, "\n");
    save[strlen(save)] = '\0'; 
    return save;
}

char * get_info(char * item, char * block_){
    return find(item, find_line_by_block(atoi(block_)));
}

char * find(char * item, char * block_){
    printf("item %s \n", item);
    if(strcmp(item, "name") == 0){
        return return_string_helper2(find_aux(block_, name_start, name_end));
    }else if (strcmp(item, "bit") == 0){
        return  return_string_helper2(find_aux(block_, bval_start, bval_end));
    }else if (strcmp(item, "block") == 0){
        return return_string_helper2(find_aux(block_, num_block_start, num_block_end));       
    }else if (strcmp(item, "nblock") == 0){
        return return_string_helper2(find_aux(block_, next_block_start, next_block_end));       
    }else if (strcmp(item, "creation") == 0){
        return find_aux(block_, creation_start, creation_end);       
    }else if (strcmp(item, "owner") == 0){
        return return_string_helper2(find_aux(block_, owner_start, owner_end));     
    }else if (strcmp(item, "modification") == 0){
        
        //printf("%s\n", find_aux(block_, modification_start, modification_end));
        printf("F\n");
        return return_string_helper2(find_aux(block_, modification_start, modification_end));    
    }else if (strcmp(item, "size") == 0){
        return return_string_helper2(find_aux(block_, size_start, size_end));       
    }else if (strcmp(item, "data") == 0){
        char * full_line = block_;
        char * first_block_ = find_aux(full_line, num_block_start, num_block_end);
        char * next_block_ = find_aux(full_line, next_block_start, next_block_end);
        int temp;
        if(strcmp(first_block_, next_block_) == 0){
            return return_string_helper2(find_aux(full_line, data_start, data_end));
        }else{
            char * data_ = malloc(100);//malloc(atoi(find_aux(full_line, size_start, size_end)));
            strcpy(data_, " ");
            while(strcmp(first_block_, next_block_) != 0){
                strcat(data_, find_aux(full_line, data_start, data_end));
                first_block_ = next_block_;
                full_line = find_line_by_block(atoi(first_block_));
                next_block_ = find_aux(full_line, next_block_start, next_block_end);
            }
            strcat(data_, find_aux(full_line, data_start, data_end));
            //data_[atoi(find_aux(full_line, size_start, size_end))] = '\0';
            strcat(data_, "\0");
            return return_string_helper2(data_);
        }
    }else{
        printf("Entre a un else\n");
        return return_string_helper2("             ");
    }

}

char * find_aux(char * item, const char * p1, const char * p2){
    char *target = NULL;
    char *start, *end;
    if (start = strstr(item, p1))
    {
        start += strlen(p1);
        if ( end = strstr( start, p2))
        {
            target = (char *)malloc(end - start + 1);
            memcpy( target, start, end - start );
            target[end - start] = '\0';
        }
    }
    char * t2 = return_string_helper2(target);
    //printf("%s\n", t2);
    return t2;
}

char * get_free_block(){
    FILE * f;
    f = fopen(path, "r");
    if(f == NULL){
        printf("Unable to open file!");
        exit(1);
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char * b = "0";
    while ((read = getline(&line, &len, f)) != -1) {
        if(strcmp(find("bit", line), b) == 0){
            fclose(f);
            return line;
        }        
    }
    if(line == NULL){
        printf("The memory storage is full!\n");
    }
    fclose(f);
    return line;
}

void replace_block(char * num_block, file * file_, char * next_block, char * bval, char * data){
    FILE * fPtr;
    FILE * fTemp;
    char * path = "disk.txt";

    int line = atoi(num_block);
    int count;

    char * new_ = create_block(file_, bval, num_block, next_block, data);
    int BUFFER_SIZE = sizeof(get_free_block());
    char buffer[BUFFER_SIZE];
    fPtr  = fopen(path, "r");
    fTemp = fopen(path_aux, "w"); 

    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }
    count = 1;
    char * line_ = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line_, &len, fPtr)) != -1)
    {
        if (count == line)
            fputs(new_, fTemp);
        else
            fputs(line_, fTemp);
        count++;
    }
    fclose(fPtr);
    fclose(fTemp);
    remove(path);
    rename("replace.txt", path);
}

char * find_line_by_block(int num_block){
    FILE * f;
    f = fopen(path, "r");
    if(f == NULL){
        printf("Unable to open file!");
        exit(1);
    }
    int cont = 1;
    char * line_ = NULL;
    size_t len = 0;
    ssize_t read;
    while (cont <= num_block){
        getline(&line_, &len, f);
        cont ++;
    }
    return line_;
}

void add_data(file *file_, char * data){
    int temp = file_->blocks[0];
    char * first_block = (char *) malloc(sizeof(int));
    sprintf(first_block, "%d", temp);
    char * bit = "1";
    //int size_bytes = atoi(find("size", find_line_by_block(file_->blocks[0])));
    int size_bytes = strlen(data);
    file_->bytes = size_bytes;
    if(size_bytes <= block_size_){
        replace_block(first_block, file_, first_block, bit, data);
    }else{
        int size_ = 0;
        int cont = 0;
        if(size_bytes%block_size_ != 0){
            size_ = (size_bytes/block_size_) + 1;
            char * next_block = find("block", get_free_block());
            int int_next_block = atoi(next_block);
            char * chunk = malloc(block_size_);
            while (cont < size_){
                memset(chunk,0,block_size_);
                chunk[block_size_] = '\0';
                if(cont == size_-1){
                    strncpy(chunk, data+cont*block_size_, size_bytes%block_size_);
                    replace_block(first_block, file_, first_block, bit, chunk);
                    //free(chunk);
                    break;
                }else{
                    strncpy(chunk, data+cont*block_size_, block_size_);
                    char * blank_data = "";
                    replace_block(next_block, file_, next_block, bit, blank_data);
                }
                replace_block(first_block, file_, next_block, bit, chunk);
                file_->blocks[cont + 1] = int_next_block;
                first_block = next_block;
                next_block = find("block", get_free_block());
                int_next_block = atoi(next_block);
                cont++;
            }
            free(chunk);
            free(next_block);
        }else{
            size_ = (size_bytes/block_size_);
            char * next_block = find("block", get_free_block());
            int int_next_block = atoi(next_block);
            char * chunk = malloc(block_size_);
            while (cont < size_){
                memset(chunk, 0, block_size_);
                chunk[block_size_] = '\0';
                strncpy(chunk, data+cont*block_size_, block_size_);
                char * blank_data = "";

                if(cont == size_-1){
                    replace_block(first_block, file_, first_block, bit, chunk);
                    //free(chunk);
                    break;
                }else{   
                    replace_block(next_block, file_, next_block, bit, blank_data);
                }
            
                replace_block(first_block, file_, next_block, bit, chunk);
                //printf("%d, %d, %ld\n", cont*block_size_, cont*block_size_ + block_size_, strlen(data));
                file_->blocks[cont + 1] = int_next_block;
                first_block = next_block;
                next_block = find("block", get_free_block());
                int_next_block = atoi(next_block);
                cont++;
            }
            free(chunk);
            free(next_block);
        } 
    }
}

char* return_string_helper2(char* string_to_return){
    int len = strlen(string_to_return);
    char *string_r = (char *)malloc(sizeof(char)*len);
    memset(string_r, '0', len);
    int counter = 0;
    while (counter < len)
    {
        string_r[counter] = string_to_return[counter];
        counter++;
    }
    string_r[counter] = '\0';
    return string_r;
}

void delete_file(char * block_){
    char * full_line = find_line_by_block(atoi(block_));
    char * first_block_ = find_aux(full_line, num_block_start, num_block_end);
    char * next_block_ = find_aux(full_line, next_block_start, next_block_end);
    int temp;

    file *f = malloc(sizeof(file));
    f->file_name = "";
    f->owner = "";
    f->creation_date = "";
    f->last_mod = "";
    f->bytes = 0;
    f->blocks[0] = 0;

    char * bit = "0";
    char * data = "";

    if(strcmp(first_block_, next_block_) == 0){
            replace_block(first_block_, f, first_block_, bit, data);
    }else{
        char * data_ = malloc(atoi(find_aux(full_line, size_start, size_end)));
        while(strcmp(first_block_, next_block_) != 0){
            replace_block(first_block_, f, first_block_, bit, data);
            first_block_ = next_block_;
            full_line = find_line_by_block(atoi(first_block_));
            next_block_ = find_aux(full_line, next_block_start, next_block_end);
        }
        replace_block(next_block_, f, next_block_, bit, data);
        free(f);
    }
}
void modify_attribute(file * file_, char * data_){
    char * temp = malloc(1000);
    sprintf(temp, "%d", file_->blocks[0]);
    if(strcmp(data_, " ") == 0){
        char * data = find("data", find_line_by_block(file_->blocks[0]));
        delete_file(temp);
        new_item(file_);
        add_data(file_, data);
    }else{
        delete_file(temp);
        new_item(file_);
        add_data(file_, data_);
    }  
}
