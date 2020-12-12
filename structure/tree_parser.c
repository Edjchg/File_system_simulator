
#include "tree_parser.h"


char *tree_parser_wr(file_system *root)
{
    file_system* temp = root;
    char *structure_str = malloc(1000);
    if (root != NULL)
    {
        strcat(structure_str, "{");
        tree_parser_aux_wr(root, structure_str);
        strcat(structure_str, "}");
        FILE *file = fopen("output.dat", "wb");
        if (file != NULL)
        {
            //Saving the B-tree in disk: 
            fwrite(structure_str, strlen(structure_str),1, file);
            fclose(file);
        }
        return structure_str;
    }
    else
    {
        strcat(structure_str, "{}");
        FILE *file = fopen("output.dat", "wb");
        if (file != NULL)
        {
            //Saving the B-tree in disk: 
            fwrite(structure_str, strlen(structure_str),1, file);
            fclose(file);
        }
        return structure_str;
    }
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
        /*strcat(structure_str, "},{");
        if (node->father_file != NULL)
        {
            strcat(structure_str, node->father_file->directory_name);
        }*/
        strcat(structure_str, "},{");
        if (node->father_file != NULL)
        {
            //Llamar a la funcion para files...            
        }   
        strcat(structure_str,"}"); 
    }
           
}


file_system *tree_parser_rd(char *file_name)
{
    FILE* file = fopen(file_name, "rb");
    if (file == NULL)
    {
        perror("Tree parser reader: File not found!\n");
    }
    fseek(file, 0, SEEK_END); 
    int size = ftell(file);
    fseek(file, 0, SEEK_SET); 
    char *content = malloc(size);
    fread(content, 1, size, file);
    fclose(file);
    //printf("%s \n", content);
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
            //printf("cd(%s) \n", commd[i].n_file);
            cd(commd[i].n_file);
        }
        else if (commd[i].command == 2)
        {
            //printf("mkdir(%s) \n", commd[i].n_file);
            mkdir(commd[i].n_file);
        }
    }
    free(content);
    free(pointer_init);
    free(pointer_cmd);
}


file_system *tree_parser_aux_rd(char *tree_source, int *pointer_rd, struct restore_tree *commd, int *pointer_cmd)
{
    //printf("%s \n", &tree_source[*pointer_rd]);
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
            //printf("%s \n", name);

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
                    /*if (strcmp(name_fh,"root") != 0)
                    {
                        printf("cd(%s) \n",name_fh);
                    }*/      
                }
                (*pointer_rd)++;   
            }

            //printf("mkdir(%s) \n", name);
            commd[*pointer_cmd].command = 2;
            strcpy(commd[*pointer_cmd].n_file,name);
            (*pointer_cmd)++;
            //mkdir(name);
            //ls();
            (*pointer_rd)++;
            tree_parser_aux_rd(tree_source, pointer_rd,commd, pointer_cmd);
            //printf("Bro %d \n", *pointer_rd);
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
            //printf("%s \n", name);

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
                    memset(name_fh,'\0',len_fh+1   );
                    strncpy(name_fh, &tree_source[(*pointer_rd)-len_fh],len_fh);
                    if (strcmp(name_fh,"root") != 0)
                    {
                        //printf("cd(%s) \n",name_fh);
                        commd[*pointer_cmd].command = 1;
                        strcpy(commd[*pointer_cmd].n_file, name_fh);
                        (*pointer_cmd)++;
                        //cd(name_fh);
                    }         
                }
                (*pointer_rd)++;   
            }

            //printf("mkdir(%s) \n", name);
            commd[*pointer_cmd].command = 2;
            strcpy(commd[*pointer_cmd].n_file, name);
            (*pointer_cmd)++;
            //mkdir(name);
            //ls();
            (*pointer_rd)++;
            tree_parser_aux_rd(tree_source, pointer_rd, commd, pointer_cmd); 
            //if(strcmp(export_current_pointer()->directory_name, "root") != 0)           
            //{
                //printf("cd(..) \n");
                commd[*pointer_cmd].command = 1;
                strcpy(commd[*pointer_cmd].n_file, "..");
                (*pointer_cmd)++;
                //cd("..");
                //ls();
            //}
            //printf("Son %d \n", *pointer_rd);
        }
        (*pointer_rd)++;   
    }
    (*pointer_rd)++;
    if (tree_source[*pointer_rd] == '{')
    {
        (*pointer_rd)++;
        if (tree_source[*pointer_rd] != '}')
        {
            //file parser    
        }
        (*pointer_rd)++;   
    }
    //printf("Final %d %s \n", *pointer_rd, &tree_source[*pointer_rd]);
}
 