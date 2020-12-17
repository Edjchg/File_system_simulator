
#include "tree_parser.h"


char *tree_parser_wr(file_system *root)
{
    file_system* temp = root;
    char *structure_str = malloc(10000);
    if (root != NULL)
    {
        strcat(structure_str, "{");
        tree_parser_aux_wr(root, structure_str);
        strcat(structure_str, "}");
    }
    else
    {
        strcat(structure_str, "{}");
    }
    FILE *file = fopen("output.dat", "wb");
        if (file != NULL)
        {
            fwrite(structure_str, strlen(structure_str),1, file);
            fclose(file);
        }
        printf("Successfully saved tree... \n ");
        return structure_str;
    free(structure_str);
}

void tree_parser_aux_wr(file_system* node, char *structure_str)
{
    if (node->directory_name != NULL)
    {    
        strcat(structure_str, node->directory_name);
        strcat(structure_str, "(");
        if (node->father_file != NULL)
        {
            strcat(structure_str, node->father_file->directory_name);
        }
        strcat(structure_str,"):{");
        if (node->brother_file != NULL)
        {
            tree_parser_aux_wr(node->brother_file, structure_str);
        }
        strcat(structure_str, "},{");
        if (node->son_file != NULL)
        {
            tree_parser_aux_wr(node->son_file, structure_str);
        }
        strcat(structure_str, "},{");
        if (node->file_!= NULL)
        {
            file *temp;
            temp = node->file_;
            while ( temp != NULL)
            {
                printf("%s \n", temp->file_name);
                strcat(structure_str, "[");
                strcat(structure_str, node->directory_name);strcat(structure_str, ",");
                strcat(structure_str, temp->file_name);strcat(structure_str, ",");
                strcat(structure_str, temp->owner);strcat(structure_str, ",");
                strcat(structure_str, temp->creation_date);strcat(structure_str, ",");
                strcat(structure_str, temp->last_mod);strcat(structure_str, ",");
                char str[12];
                sprintf(str, "%d", temp->bytes);
                strcat(structure_str, str);
                strcat(structure_str, "]");
                temp = temp->next_file;
                
            }       
        }   
        strcat(structure_str,"}"); 
    }
           
}


void *tree_parser_rd(char *file_name)
{
    FILE* file = fopen(file_name, "rb");
    if (file == NULL)
    {
        perror("Tree parser reader: File not found!\n");
        init_root();
        return NULL;
    }
    fseek(file, 0, SEEK_END); 
    int size = ftell(file);
    fseek(file, 0, SEEK_SET); 
    char *content = malloc(size);
    fread(content, 1, size, file);
    fclose(file);
    if(content[0] == '{')
    {
        if(content[1] != '}')
        {
            char name[4];
            strncpy(name, content+1, 4);
            printf("%s \n", name);
        }
    }
    init_root();
    int *pointer_cmd = malloc(sizeof(int));
    *pointer_cmd = 0;
    struct restore_tree commd[1000];
    int *pointer_init = malloc(sizeof(int));
    *pointer_init = 8;
    tree_parser_aux_rd(content, pointer_init, commd, pointer_cmd);
    for (size_t i = 0; i < *pointer_cmd; i++)
    {
        if (commd[i].command == 1)
        {
            cd_(commd[i].n_file);
        }
        else if (commd[i].command == 2)
        {
            mkdir_(commd[i].n_file);
        }
        else if (commd[i].command == 3)
        {
            touch_restore(commd[i].file_info.file_name,commd[i].file_info.bytes,
            commd[i].file_info.owner, commd[i].file_info.creation_date, commd[i].file_info.last_mod);
        }
    }
    free(content);
    free(pointer_init);
    free(pointer_cmd);
}


void tree_parser_aux_rd(char *tree_source, int *pointer_rd, struct restore_tree *commd, int *pointer_cmd)
{
    if(tree_source[*pointer_rd] == '{')
    {
        (*pointer_rd)++;
        if(tree_source[*pointer_rd] != '}')
        {
            int len = 0;
            while (tree_source[*pointer_rd] != '(')
            {
                len++;
                (*pointer_rd)++;
            }
            char name[len+1];
            memset(name,'\0',len+1);
            strncpy(name, &tree_source[(*pointer_rd)-len],len);
            if (tree_source[*pointer_rd] == '(')
            {
                (*pointer_rd)++;
                if (tree_source[*pointer_rd] != ')')
                {
                    int len_fh = 0;
                    while (tree_source[*pointer_rd] != ')')
                    {
                        len_fh++;
                        (*pointer_rd)++;
                    }
                    char name_fh[len_fh+1];
                    memset(name_fh,'\0',len_fh+1);
                    strncpy(name_fh, &tree_source[(*pointer_rd)-len_fh],len_fh);     
                }
                (*pointer_rd)++;   
            }
            commd[*pointer_cmd].command = 2;
            strcpy(commd[*pointer_cmd].n_file, name);
            (*pointer_cmd)++;
            (*pointer_rd)++;
            tree_parser_aux_rd(tree_source, pointer_rd,commd, pointer_cmd);
        }
        (*pointer_rd)++;
    }
    (*pointer_rd)++;
    if (tree_source[*pointer_rd] == '{')
    {
        (*pointer_rd)++;
        if (tree_source[*pointer_rd] != '}')
        {
            int len = 0;
            while (tree_source[*pointer_rd] != '(')
            {
                len++;
                (*pointer_rd)++;
            }
            char name[len+1];
            memset(name,'\0',len+1);
            strncpy(name, &tree_source[(*pointer_rd)-len],len);
            if (tree_source[*pointer_rd] == '(')
            {
                (*pointer_rd)++;
                if (tree_source[*pointer_rd] != ')')
                {
                    int len_fh = 0;
                    while (tree_source[*pointer_rd] != ')')
                    {
                        len_fh++;
                        (*pointer_rd)++;
                    }
                    char name_fh[len+1];
                    memset(name_fh,'\0',len_fh+1);
                    strncpy(name_fh, &tree_source[(*pointer_rd)-len_fh],len_fh);
                    if (strcmp(name_fh,"root") != 0)
                    {
                        commd[*pointer_cmd].command = 1;
                        strcpy(commd[*pointer_cmd].n_file, name_fh);
                        (*pointer_cmd)++;
                    }         
                }
                (*pointer_rd)++;   
            }
            commd[*pointer_cmd].command = 2;
            strcpy(commd[*pointer_cmd].n_file, name);
            (*pointer_cmd)++;
            (*pointer_rd)++;
            tree_parser_aux_rd(tree_source, pointer_rd, commd, pointer_cmd); 
            commd[*pointer_cmd].command = 1;
            strcpy(commd[*pointer_cmd].n_file, "..");
            (*pointer_cmd)++;
        }
        (*pointer_rd)++;   
    }
    (*pointer_rd)++;
    if (tree_source[*pointer_rd] == '{')
    {
        (*pointer_rd)++;
        if (tree_source[*pointer_rd] != '}')
        {
            while (tree_source[*pointer_rd] != '}')
            {   
                (*pointer_rd)++;
                int len_file_attr = 0;
                while (tree_source[*pointer_rd] != ']')
                {
                    (*pointer_rd)++;
                    len_file_attr++;
                }
                char file_attr[len_file_attr];
                memset(file_attr, '\0', len_file_attr+1);
                strncpy(file_attr, &tree_source[*pointer_rd-len_file_attr], len_file_attr);
                char *attr;
                attr = strtok(file_attr, ",");
                commd[*pointer_cmd].command = 1;
                strcpy(commd[*pointer_cmd].n_file, attr);
                (*pointer_cmd)++;
                commd[*pointer_cmd].command = 3;
                attr = strtok(NULL, ",");
                strcpy(commd[*pointer_cmd].file_info.file_name, attr);
                attr = strtok(NULL, ",");
                strcpy(commd[*pointer_cmd].file_info.owner, attr);
                attr = strtok(NULL, ",");
                strcpy(commd[*pointer_cmd].file_info.creation_date, attr);
                attr = strtok(NULL, ",");
                strcpy(commd[*pointer_cmd].file_info.last_mod, attr);
                attr = strtok(NULL, ",");
                commd[*pointer_cmd].file_info.bytes = atoi(attr);
                (*pointer_rd)++;
                (*pointer_cmd)++;
                commd[*pointer_cmd].command = 1;
                strcpy(commd[*pointer_cmd].n_file, "..");
                (*pointer_cmd)++;
            }
        }
        (*pointer_rd)++;   
    }
}
 
/**

 void touch_restore(char* file_name, int bytes, char *owner, char* creation_date, char *last_mod)
{
    if (file_pointer->file_ == NULL)
    {
        file_pointer->file_ = (file*)malloc(sizeof(file));
        file_pointer->file_->file_name = file_name;
        file_pointer->file_->bytes = bytes;
        file_pointer->file_->owner = owner;
        file_pointer->file_->creation_date = creation_date;
        file_pointer->file_->last_mod = last_mod;
        file_pointer->file_->next_file = NULL; 
    }else
    {
        file* temp = file_pointer->file_;
        while (temp->next_file != NULL)
        {
            temp = temp->next_file;
        }
        temp->next_file = (file*)malloc(sizeof(file));
        temp->next_file->file_name = file_name;
        temp->next_file->bytes = bytes;
        temp->next_file->owner = owner;
        temp->next_file->creation_date = creation_date;
        temp->next_file->last_mod = last_mod;
        temp->next_file->next_file = NULL;
        
    }
}
**/
