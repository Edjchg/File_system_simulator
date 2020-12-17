
#include "structure.h"

node* head = NULL;
file_system* root = NULL;
file_system* file_pointer = NULL;
int level;
int column;
char directories[1000000000];


void init_root(void){
    printf("Se llamó a init_root\n");
    root = (file_system*)malloc(sizeof(file_system));
    memset(root, '0', sizeof(file_system));
    root->brother_file = NULL;
    root->father_file = NULL;
    root->son_file = NULL;
    root->directory_name = "root";
    root->file_ = NULL;
    file_pointer = root;
    return;
}

char* mkdir_(char* new_directory){
    int len = strlen(new_directory);
    char* name;
    if (len > 0)
    {
        name = return_string_helper1(new_directory);
    }
    if (root->son_file == NULL)
    {
        root->son_file = (file_system*)malloc(sizeof(file_system));
        root->son_file->directory_name = name;//new_directory;
        root->son_file->father_file = root;
        root->son_file->son_file = NULL;
        root->son_file->brother_file = NULL;
        root->son_file->file_ = NULL;
        level += 1;
        root->son_file->level = level;
        root->son_file->brother_number = 0;
        
        return return_string_helper1(" ");//file_pointer = root;
    }else
    {
        file_system* temp = file_pointer->son_file;
        int compare;
        if (check_file_names(new_directory))
        {
            if(temp != NULL){
                while (temp->brother_file != NULL)
                {
                    temp = temp->brother_file;  
                }
                    temp->brother_file = (file_system*)malloc(sizeof(file_system));
                    temp->brother_file->directory_name = name;//new_directory;
                    temp->brother_file->son_file = NULL;
                    temp->brother_file->father_file = temp->father_file;
                    temp->brother_file->brother_file = NULL;
                    temp->brother_file->file_ = NULL;
                    temp->brother_file->level = level;
                    temp->brother_file->brother_number = get_len() - 1;
                    return return_string_helper1(" ");
            
            }else{
                file_pointer->son_file = (file_system*)malloc(sizeof(file_system));
                file_pointer->son_file->directory_name = name;//new_directory; 
                file_pointer->son_file->father_file = file_pointer;
                file_pointer->son_file->son_file = NULL;
                file_pointer->son_file->brother_file = NULL;
                file_pointer->son_file->file_ = NULL;
                file_pointer->level = level;
                file_pointer->brother_number = get_len() - 1;
                return return_string_helper1(" ");
            }
        }else
        {
            return return_string_helper1("Name is not available.");
        }
        
        
    }
}
char* cd_(char* next_directory){
    if (strcmp(next_directory, "..") ==  0)
    {
        //printf("Se detectó un ..\n");
        if (file_pointer->father_file != NULL)
        {
            file_pointer = file_pointer->father_file;
            //chdir("..");
            level -= 1;
            //printf("%s\n", file_pointer->directory_name);
            return return_string_helper1(" ");
        }else{
            //return;
            return return_string_helper1("No father directory, you are in root.");
        }
    }else{
        //printf("Se intenta entrar a otro archivo\n");
        if (file_pointer->son_file != NULL)
        {
            file_system* temp = file_pointer->son_file;
            //while (strcmp(temp->directory_name, next_directory) != 0)
            while(compare_strings1(temp->directory_name, next_directory) != 1)
            {
                printf("en cd voy por: %s\n", temp->directory_name);
                temp = temp->brother_file;
                if (temp == NULL)
                {
                    printf("\033[1;31m %s: No such file or directory. \033[0m \n", next_directory);
                    return return_string_helper1("No such file or directory.");
                }
            }
            if (temp != NULL)
            {
                file_pointer = temp;
                level += 1;
                return return_string_helper1(" ");
            }
        }else
        {
            printf("\033[1;31m %s: No such file or directory. \033[0m \n", next_directory);
            return return_string_helper1("No such file or directory.");
        }  
    }
}
int check_file_names(char* name){
    file_system* temp;
    int flag;
    if (file_pointer->son_file != NULL)
    {
        temp = file_pointer->son_file;
        while (temp != NULL)
        {
            if (compare_strings1(temp->directory_name, name))
            {
                flag = 0;
                break;
            }else
            {
                temp = temp->brother_file;
                flag = 1;
            }
        }
    }else
    {
        flag = 1;
    }
    return flag;   
}
char* ls_(void){
//Print all directories:
    file_system* temp; //= file_pointer;
    char result[1000];
    memset(result, 0, 1000);
    //if (temp->son_file == NULL)
    strcat(result, ". ..");
    if(file_pointer->son_file == NULL)
    {
        printf("\033[0;34m . ..\033[0m");
        
    }else
    {
        //temp = temp->son_file;
        temp = file_pointer->son_file;
        printf("\033[0;34m . ..\033[0m ");
        while (temp != NULL)
        {
            printf("\033[0;34m %s \033[0m", temp->directory_name);
            //printf("%s\n", temp->directory_name);
            int len1 = strlen(temp->directory_name);
            strcat(result, temp->directory_name);
            strcat(result, " ");
            temp = temp->brother_file;
        }
    }
//Print all files:
    //strcat(result, "\n");
    file* temp1;
    
    if (file_pointer->file_ == NULL)
    {
        ;
    }else
    {
        temp1 = file_pointer->file_;
        while (temp1 != NULL)
        {
            printf("\033[0;32m %s \033[0m", temp1->file_name);
            strcat(result, temp1->file_name);
            temp1 = temp1->next_file;
        }
    }
    printf("\n");
    int len = strlen(result);
    char* result1 = (char *)malloc(sizeof(char)*len);
    //memset(result1, 0, len);
    int index = 0;
    while (index < len)
    {
        result1[index] = result[index];
        index++;
    }
    result1[index] = '\0';
    return result1;
    
}
char* rmdir_(char* directory){
    file_system* temp = file_pointer->son_file;
    int len = get_len();
    int counter = 0;
    if (temp == NULL)
    {
        printf("\033[1;31m Can not remove inexisting directory. \033[0m \n");
        return return_string_helper1("Can not remove inexisting directory.");
    }else
    {
        while (strcmp(temp->directory_name, directory) != 0)
        {
            temp = temp->brother_file;
            counter++;
            if (temp == NULL)
            {
                printf("\033[1;31m Can not remove inexisting directory. \033[0m \n");
                return return_string_helper1("Can not remove inexisting directory.");
                
            }
        }
        if (temp != NULL)
        {
            if (counter == 0)
            {
                file_pointer->son_file = file_pointer->son_file->brother_file;
            }else if (counter == len - 1)
            {
                temp = file_pointer->son_file;
                while (temp->brother_file->brother_file != NULL)
                {
                    temp = temp->brother_file;
                }
                temp->brother_file = NULL;
                
                //temp->brother_file = NULL;
            }else
            {
                temp = file_pointer->son_file;
                int counter2 = 0;
                while (counter2 < counter - 1)
                {
                    counter2++;
                    temp = temp->brother_file;

                }
                temp->brother_file = temp->brother_file->brother_file;   
            }
            return return_string_helper1(" ");
        }
         
    }
}

void free_all(void){
    free(root);
    //free(head);
}
file_system* export_current_pointer(void){
    return file_pointer;
}
file_system* export_root(void){
    return root;
}
char* rename_file(char* actual_name, char* new_name){
    int len = strlen(new_name);
    char* name;
    if (len > 0)
    {
        name = return_string_helper1(new_name);
    }
    
    file_system* temp = file_pointer->son_file;
    if (temp != NULL)
    {
        //while (strcmp(temp->directory_name, actual_name) != 0)
        while(compare_strings1(temp->directory_name, actual_name) != 1)
        {
            temp = temp->brother_file;
            
            if (temp == NULL)
            {
                printf("\033[1;31m %s to %s: Can not rename inexisting directory. \033[0m \n", actual_name, new_name);
                return return_string_helper1("Can not rename inexisting directory.");
            }
            
        }
        temp->directory_name = name;//new_name;
        return return_string_helper1(" ");
    }else
    {
        printf("\033[1;31m %s to %s: Can not rename inexisting directory. \033[0m \n", actual_name, new_name);
        return return_string_helper1("Can not rename inexisting directory.");
    }
    
    
}
int get_len(void){
    file_system* temp = file_pointer->son_file;
    int counter = 0;

    if (root == NULL)
    {
        return counter;
    }else{
        while (temp != NULL)
        {
            counter++;
            temp = temp->brother_file;
        }
        return counter;
    }
}

void touch_(char* file_name){
    printf(" File name touch %s \n", file_name);
    int len = strlen(file_name);
    char* name;
    name = return_string_helper1(file_name);


    printf("aqui \n");
    if (file_pointer->file_ == NULL)
    {
        file_pointer->file_ = (file*)malloc(sizeof(file));
        file_pointer->file_->file_name = name;//file_name;
        file_pointer->file_->bytes = 0;
        file_pointer->file_->owner = "owner";
        file_pointer->file_->next_file = NULL;
        file_pointer->file_->creation_date = "0/0/0";
        file_pointer->file_->last_mod = "0/0/0"; 
    
        new_item(file_pointer->file_);
    }else
    {
        file* temp = file_pointer->file_;
        while (temp->next_file != NULL)
        {
            temp = temp->next_file;
        }
        temp->next_file = (file*)malloc(sizeof(file));
        temp->next_file->file_name = name;//file_name;
        temp->next_file->bytes = 0;
        temp->next_file->owner = "owner";
        temp->next_file->creation_date = "0/0/0";
        temp->next_file->last_mod = "0/0/0";
        temp->next_file->next_file = NULL; 
        
        new_item(temp->next_file);
    }
}
char* mv(char* old_name, char* new_name){
    int len = strlen(new_name);
    char* name;
    if (len > 0)
    {
        name = return_string_helper1(new_name);
    }
    
    file* temp = file_pointer->file_;
    if (temp != NULL)
    {
        printf("\033[1;31m %s to %s \033[0m \n", old_name, new_name);
        while (strcmp(temp->file_name, old_name) != 0)
        //while (compare_strings1(old_name, temp->file_name) != 1)
        {
            temp = temp->next_file;
            if (temp == NULL)
            {
                printf("\033[1;31m %s to %s: Can not rename inexisting file. \033[0m \n", old_name, new_name);
                return return_string_helper1("Can not rename inexisting file.");
            }
        }
        temp->file_name = name;//new_name; 
        return return_string_helper1(" ");  
    }else
    {
        printf("\033[1;31m %s to %s: Can not rename inexisting file. \033[0m \n", old_name, new_name);
        return return_string_helper1("Can not rename inexisting file.");
    }
}
int get_file_list_len(void){
    file* temp = file_pointer->file_;
    int counter = 0;
    while (temp != NULL)
    {
        counter++;
        temp = temp->next_file;
    }
    return counter;
}
char* rm(char* file_name){
    file* temp = file_pointer->file_;
    int counter = 0;
    int len = get_file_list_len();
    if (temp == NULL)
    {
        printf("\033[1;31mCan not remove inexisting file. \033[0m \n");
        return return_string_helper1("Can not remove inexisting file.");
    }else
    {
        while (strcmp(temp->file_name, file_name) != 0)
        {
            temp = temp->next_file;
            if (temp == NULL)
            {
                printf("\033[1;31mCan not remove inexisting file. \033[0m \n");
                return return_string_helper1("Can not remove inexisting file.");
            }
            counter++;
        }
        if (temp != NULL)
        {  
            char * temp_block = malloc(sizeof(temp->blocks[0]));
            sprintf(temp_block, "%d", temp->blocks[0]);
            delete_file(temp_block);
            if (counter == 0)
            {
                file_pointer->file_ = file_pointer->file_->next_file;
            }else if (counter == len - 1)
            {
                temp = file_pointer->file_;
                while (temp->next_file->next_file != NULL)
                {
                    temp = temp->next_file;
                }
                temp->next_file = NULL;
            }else
            {
                temp = file_pointer->file_;
                int counter2 = 0;
                while (counter2 < counter - 1)
                {
                    counter2++;
                    temp = temp->next_file;
                }
                temp->next_file = temp->next_file->next_file;
            }
            return return_string_helper1(" ");
        }else
        {
            return return_string_helper1("Can not remove inexisting file.");
        }
        
    }
}
char* lsattr(char* file_name){

    file* temp;// = file_pointer->file_;
    //if (temp == NULL)
    if(file_pointer->file_ == NULL)
    {
        printf("\033[1;31m %s: No such file or directory. \033[0m \n", file_name);
        return return_string_helper1("No such file or directory.");
        
    }else
    {
        temp = file_pointer->file_;
        //while (strcmp(file_name, temp->file_name ) != 0)
        while(compare_strings1(file_name, temp->file_name) != 1)
        {
            temp = temp->next_file;
            if (temp == NULL)
            {
                printf("\033[1;31m %s: -No such file or directory. \033[0m \n", file_name);
                //return;
                break;
            }
        }
        if (temp != NULL)
        {
            //Agregar el resto
            /*
            printf("=> Name: %s\n", find("name", temp->blocks[0]));
            printf("=> Owner: %s\n", find("owner", temp->blocks[0]));
            printf("=> Bytes: %i\n", find("size", temp->blocks[0]));
            printf("=> Creation date: %s\n", find("creation", temp->blocks[0]));
            printf("=> Last modification date: %s\n", find("modification", temp->blocks[0]));
            */

            char attrs[] = "                                                                                           ";
            char * block_temp = malloc(sizeof(temp->blocks[0]));
            sprintf(block_temp, "%d", temp->blocks[0]);
            strcpy(attrs, "=> Name: ");
            strcat(attrs, get_info("name", block_temp));
            strcat(attrs, "\n");
            strcat(attrs, "=> Owner: ");
            strcat(attrs, get_info("owner", block_temp));
            strcat(attrs, "\n");
            strcat(attrs, "=> Bytes: ");
            char bytes[50];
            sprintf(bytes, "%s", get_info("size", block_temp));
            strcat(attrs, bytes);
            strcat(attrs, "\n");
            strcat(attrs, "=> Creation date: ");
            strcat(attrs, get_info("creation", block_temp));
            strcat(attrs, "\n");
            strcat(attrs, "=> Last modification date: ");
            strcat(attrs, get_info("modification", block_temp));
            return return_string_helper1(attrs);
        }else
        {
            return return_string_helper1("No such file or directory.");
        }
    }
}
char* echo_(char* file_name, char* data){
    file* temp;
    if (file_pointer->file_ != NULL)
    {
        temp = file_pointer->file_ ;
        while (temp != NULL)
        {
            if (strcmp(temp->file_name, file_name) == 0)
            {
                break;
            }
            temp = temp->next_file;
        }
        if (temp == NULL)
        {
            return return_string_helper1("No such file.");
        }else
        {
            //poner echo

            printf("dato: %s\n", data);
            add_data(temp, data);
            return return_string_helper1("           ");
        }
    }else
    {
        return return_string_helper1("No such file.");
    } 
}
char* cat_(char* file_name){
    file* temp;
    if (file_pointer->file_ != NULL)
    {
        temp = file_pointer->file_;
        while (temp != NULL)
        {
            if (strcmp(temp->file_name, file_name) == 0)
            {
                break;
            }
            temp = temp->next_file;
        }
        if (temp == NULL)
        {
            return return_string_helper1("No such file.");
        }else
        {   
            char * temp_block = (char*)malloc(sizeof(temp->blocks[0])+1000);
            sprintf(temp_block, "%d", temp->blocks[0]);
            char *all_info = get_info("data", temp_block);
            printf("%s \n", all_info);
            return all_info;
            //return return_string_helper1("           ");
        }   
    }else
    {
        return return_string_helper1("No such file.");
    }
    
}
void trace_file_system(void){
    file_system* temp = root;
    if (root != NULL)
    {
        strcpy(directories, root->directory_name);
        strcat(directories, "\n");
        trace_file_aux(root);
    }
    else
    {
        printf("Can not trace an empty tree\n");
    }
}

void trace_file_aux(file_system* node){
    //if (node->son_file != NULL)
    if(node->son_file != NULL && node->son_file->visited != 1)
    {
        node = node->son_file;
        node->visited = 1;
        strcat(directories,"\n");
        strcat(directories, node->directory_name);
        trace_son(node);
        /*
        if (node->brother_file != NULL)
        {
            trace_file_aux(node->brother_file);
        }*/
        
    } else if (node->brother_file != NULL)
    {
        node = node->brother_file;
        strcat(directories, node->directory_name);
        trace_file_aux(node);
    }else if (node->father_file != NULL && node->father_file != root)
    {
        node = node->father_file;
        strcat(directories, "\b");
        trace_file_aux(node);
    }else
    {
        return;
    }
    
}
void trace_son(file_system* node){
    if (node->son_file == NULL)
    {
        if (node->brother_file != NULL)
        {
            node = node->brother_file;
            strcat(directories, node->directory_name);
            trace_son(node);
        }else
        {
            node = node->father_file;
            strcat(directories, "\b");
            trace_file_aux(node);
        }
          
    }else
    {
        node = node->son_file;
        node->visited = 1;
        strcat(directories, "\n");
        strcat(directories, node->directory_name);
        trace_son(node);
    }
}

char* return_directories(void){
    return directories;
}


//----------------------File system--------------------------------------

//----------------------------Linked list------------------------------
void add_node(char* name){
    // If the head is null, so we have to reserve memory for this first element:
    if (head == NULL)
    {
        //Reserve memory for head:
        head = (node*)malloc(sizeof(node));
        //Assign the attribute directory_name:
        head->directory_name = name;
        //Now the next pointer is null
        head->next = NULL;
    }else{
        node* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (node*)malloc(sizeof(node));
        temp->next->directory_name = name;
        temp->next->next = NULL;
    }
}

void print_list(){
    node* temp = head;
    while (temp != NULL)
    {
        temp = temp->next;
    }
    printf("\n");
}
int lk_len(void){
    node* temp = head;
    int counter = 0;
    if (head == NULL){
        return counter;
    }else{
        while (temp != NULL)
        {
            counter++;
            temp = temp->next;
        }
        return counter;
    }
    
}

char* get_file(int index){
    node* temp = head;
    int counter = 0;
    int len = lk_len();
    char* msg = "Nothing";
    if (head == NULL)
    {
        return msg;
    }else if (index > len - 1)
    {
        return msg;
    }else
    {
        node* temp = head;
        while (counter != index)
        {
            temp = temp->next;
            counter++;
        }

        return temp->directory_name;
        
    }
}

int push_in(int index, char* file_name){
    int len = lk_len();
    int counter = 0;
    if (head == NULL || index > len-1)
    {
        add_node(file_name);
    }else if(index == 0){
        push_to_head(file_name);
    }
    else
    {
        node* temp = head;
        while (counter < index - 1)
        {
            temp = temp->next;
            counter++;
        }
        node* actual;
        actual = (node* )malloc(sizeof(node));
        actual->directory_name = file_name;
        actual->next = temp->next;
        temp->next = actual;
        return 1;
    }  
}
int push_to_head(char* file_name){
    node* new_head;
    new_head = (node*) malloc(sizeof(node));
    new_head->directory_name = file_name;
    new_head->next = head;
    head = new_head;
}

int delete_in(int index){
    if (index == 0)
    {
        head = head->next;
    }else if (index == lk_len()-1)
    {
        node* temp = head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = NULL;
    }else
    {
        int counter = 0;
        node* temp = head;
        while (counter < index-1)
        {
            temp = temp->next;
            counter++;
        }
        temp->next = temp->next->next;
        
    }
    return 0;
}
//---------------Linked list---------------------------------
int compare_strings1(char* str1, char* str2){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 == len2)
    {
        int index = 0;
        while (index < len1)
        {
            if (str1[index] != str2[index])
            {
                return 0;
            }
            index++;
        }
        return 1;
    }else
    {
        return 0;
    }
}
char* return_string_helper1(char* string_to_return){
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

//--------------  Tree restoring ---------------------
void touch_restore(char* file_name, int bytes, char *owner, char* creation_date, char *last_mod)
{
    char* name;
    name = return_string_helper1(file_name); 
    char* owner_temp;
    owner_temp = return_string_helper1(owner); 
    char* creation_date_temp;
    creation_date_temp = return_string_helper1(creation_date); 
    char* last_mod_temp;
    last_mod_temp = return_string_helper1(last_mod);     
    if (file_pointer->file_ == NULL)
    {
        file_pointer->file_ = (file*)malloc(sizeof(file));
        file_pointer->file_->file_name = name;
        file_pointer->file_->bytes = bytes;
        file_pointer->file_->owner = owner_temp;
        file_pointer->file_->creation_date = creation_date_temp;
        file_pointer->file_->last_mod = last_mod_temp;
        file_pointer->file_->next_file = NULL; 
    }else
    {
        file* temp = file_pointer->file_;
        while (temp->next_file != NULL)
        {
            temp = temp->next_file;
        }
        temp->next_file  = (file*)malloc(sizeof(file));
        temp->next_file->file_name = name;
        temp->next_file->bytes = bytes;
        temp->next_file->owner = owner_temp;
        temp->next_file->creation_date = creation_date_temp;
        temp->next_file->last_mod = last_mod_temp;
        temp->next_file->next_file = NULL; 
    }
}