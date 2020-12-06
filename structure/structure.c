
#include "structure.h"

node* head = NULL;
file_system* root = NULL;
file_system* file_pointer = NULL;

void init_root(void){
    root = (file_system*)malloc(sizeof(file_system));
    root->brother_file = NULL;
    root->father_file = NULL;
    root->son_file = NULL;
    root->directory_name = "root";
    file_pointer = root;
}
void mkdir(char* new_directory){
    if (root->son_file == NULL)
    {
        root->son_file = (file_system*)malloc(sizeof(file_system));
        root->son_file->directory_name = new_directory;
        root->son_file->father_file = root;
        root->son_file->son_file = NULL;
        root->son_file->brother_file = NULL;
        //file_pointer = root;
    }else
    {
        file_system* temp = file_pointer->son_file;
        if(temp != NULL){
            while (temp->brother_file != NULL)
            {
                temp = temp->brother_file;
            }
            temp->brother_file = (file_system*)malloc(sizeof(file_system));
            temp->brother_file->directory_name = new_directory;
            temp->brother_file->son_file = NULL;
            temp->brother_file->father_file = temp->father_file;
            temp->brother_file->brother_file = NULL;
        }else{
            file_pointer->son_file = (file_system*)malloc(sizeof(file_system));
            file_pointer->son_file->directory_name = new_directory; 
            file_pointer->son_file->father_file = file_pointer;
            file_pointer->son_file->son_file = NULL;
            file_pointer->son_file->brother_file = NULL;
        }
        
    }
}
void cd(char* next_directory){
    //file_pointer = root;
    file_system* temp = file_pointer->son_file;

    if (strcmp(next_directory, "..") ==  0)
    {
        //printf("Se detectó un ..\n");
        if (file_pointer->father_file != NULL)
        {
            printf("Tiene papá ..\n");
            file_pointer = file_pointer->father_file;
            //printf("%s\n", file_pointer->directory_name);
        }else{
            printf("No tiene papá ..\n");
            return;
        }
    }else{
        //printf("Se intenta entrar a otro archivo\n");
        if (temp != NULL)
        {
            while (strcmp(temp->directory_name, next_directory) != 0)
            {
                temp = temp->brother_file;
                if (temp == NULL)
                {
                    printf("\033[1;31m %s: No such file or directory. \033[0m \n", next_directory);
                    return;
                }
            }
            file_pointer = temp;
            //printf("%s\n", file_pointer->directory_name);
        }else
        {
            printf("\033[1;31m %s: No such file or directory. \033[0m \n", next_directory);
        }  
    }
}
void ls(void){
//Print all directories:
    file_system* temp = file_pointer;
    if (temp->son_file == NULL)
    {
        printf("\033[0;34m . ..\033[0m \n");
    }else
    {
        temp = temp->son_file;
        printf("\033[0;34m . ..\033[0m ");
        while (temp != NULL)
        {
            printf("\033[0;34m %s \033[0m", temp->directory_name);
            temp = temp->brother_file;
        }
        printf("\n");
        
    }
//Print all files:
    file* temp1 = file_pointer->file_;
    if (temp1 == NULL)
    {
        return;
    }else
    {
        while (temp1 != NULL)
        {
            printf("\033[0;32m %s \033[0m", temp1->file_name);
            temp1 = temp1->next_file;
        }
        printf("\n");
        
    }
    
    
}
void rmdir(char* directory){
    file_system* temp = file_pointer->son_file;
    int len = get_len();
    int counter = 0;
    if (temp == NULL)
    {
        printf("\033[1;31m Can not remove inexisting directory. \033[0m \n");
    }else
    {
        while (strcmp(temp->directory_name, directory) != 0)
        {
            temp = temp->brother_file;
            counter++;
            if (temp == NULL)
            {
                printf("\033[1;31m Can not remove inexisting directory. \033[0m \n");
                return;
            }
        }
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
        
        
        
        
    }
}

void free_all(void){
    free(root);
    free(head);
}
file_system* export_current_pointer(void){
    return file_pointer;
}
void rename_file(char* actual_name, char* new_name){
    file_system* temp = file_pointer->son_file;
    if (temp != NULL)
    {
        while (strcmp(temp->directory_name, actual_name) != 0)
        {
            temp = temp->brother_file;
            if (temp == NULL)
            {
                printf("\033[1;31m %s to %s: Can not rename inexisting directory. \033[0m \n", actual_name, new_name);
                return;
            }
            
        }
        temp->directory_name = new_name;
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

void touch(char* file_name){
    if (file_pointer->file_ == NULL)
    {
        file_pointer->file_ = (file*)malloc(sizeof(file));
        file_pointer->file_->file_name = file_name;
        file_pointer->file_->bytes = 0;
        file_pointer->file_->owner = "owner";
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
        temp->next_file->bytes = 0;
        temp->next_file->owner = "owner";
        temp->next_file->next_file = NULL;
        
    }
}
void mv(char* old_name, char* new_name){
    file* temp = file_pointer->file_;
    if (temp != NULL)
    {
        while (strcmp(temp->file_name, old_name) != 0)
        {
            temp = temp->next_file;
            if (temp == NULL)
            {
                printf("\033[1;31m %s to %s: Can not rename inexisting file. \033[0m \n", old_name, new_name);
                return;
            }
            
        }
        temp->file_name = new_name;   
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
void rm(char* file_name){
    file* temp = file_pointer->file_;
    int counter = 0;
    int len = get_file_list_len();
    if (temp == NULL)
    {
        printf("\033[1;31mCan not remove inexisting file. \033[0m \n");
    }else
    {
        while (strcmp(temp->file_name, file_name) != 0)
        {
            counter++;
            temp = temp->next_file;
            if (temp == NULL)
            {
                printf("\033[1;31mCan not remove inexisting file. \033[0m \n");
            }
        }
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
    }
}
void lsattr(char* file_name){
    file* temp = file_pointer->file_;
    if (temp == NULL)
    {
        printf("\033[1;31m %s: No such file or directory. \033[0m \n", file_name);
    }else
    {
        while (strcmp(temp->file_name, file_name) != 0)
        {
            temp = temp->next_file;
            if (temp == NULL)
            {
                printf("\033[1;31m %s: No such file or directory. \033[0m \n", file_name);
                return;
            }
        }
        printf("=> Name: %s\n", temp->file_name);
        printf("=> Owner: %s\n", temp->owner);
        printf("=> Bytes: %i\n", temp->bytes);
        printf("=> Creation date: %s\n", temp->creation_date);
        printf("=> Last modification date: %s\n", temp->last_mod);
    }
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
        printf("%s, ", temp->directory_name);
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
