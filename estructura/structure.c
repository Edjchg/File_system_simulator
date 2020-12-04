#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEEPNESS 1000;
//Compile with: gcc -o structure structure.c
typedef struct file_list{
    char* filename;
    struct file_list *next_file;
}file_list;

typedef struct node
{
    struct node *next;
    char* directory_name;
    //struct file_list;
}node;



typedef struct file_system{
    struct file_system* brother_file;
    struct file_system* son_file;
    struct file_system* father_file;
    struct node* file;
    char* directory_name;
}file_system;



node* head = NULL;

file_system* root = NULL;
file_system* file_pointer = NULL;

//---------Linked list-----------
void add_node(char* directory_name);
void print_list(void);
int lk_len(void);
char* get_file(int index);
int push_in(int index, char* file_name);
int push_to_head(char* file_name);
int delete_in(int index);
//------------Linked list-----------
//-----------File system------------
void init_root(void); //Init the root of the file system.
void mkdir(char* new_directory); // Create a directory inside a father directory.
void cd(char* next_directory); // Get inside a child directory.
void ls(void); // Print all the directories.
void rmdir(char* directory); // Remove a certain directory.
//-----------File system------------
int main(){
    init_root();
    /*
    mkdir("Hola");
    mkdir("usr");
    mkdir("jaja");
    cd("jaja");
    printf("El current nombre del archivo es %s, su padre es %s\n", file_pointer->directory_name, file_pointer->father_file->directory_name);
    mkdir("dentro_de_jaja");
    cd("dentro_de_jaja");
    printf("El current nombre del archivo es %s, su padre es %s\n", file_pointer->directory_name, file_pointer->father_file->directory_name);
    cd("..");
    printf("El current nombre del archivo es %s, su padre es %s\n", file_pointer->directory_name, file_pointer->father_file->directory_name);
    mkdir("jaja2");
    cd("..");
    cd("jaja");
    */

    /*
    mkdir("usr");
    cd("usr");
    mkdir("inside_user");
    cd("inside_user");
    mkdir("Hola");
    cd("Hola");
    printf("El current nombre del archivo es %s, su padre es %s\n", file_pointer->directory_name, file_pointer->father_file->directory_name);

    cd("..");
    printf("El current nombre del archivo es %s, su padre es %s\n", file_pointer->directory_name, file_pointer->father_file->directory_name);
    cd("..");
    printf("El current nombre del archivo es %s, su padre es %s\n", file_pointer->directory_name, (file_pointer->father_file->directory_name!=NULL)?file_pointer->father_file->directory_name:"NULL");
    cd("..");

    */
    mkdir("usr");
    mkdir("lib");
    mkdir("include");
    cd("usr");
    mkdir("game1");
    mkdir("game2");
    cd("..");
    cd("lib");
    mkdir("libgpioman");
    mkdir("libmath");
    cd("..");
    cd("include");
    mkdir("header1");
    mkdir("header2");
    cd("..");

    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("usr");
    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("game1");
    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("GTA");

    cd("..");
    cd("..");

    cd("lib");
    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("libmath");
    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("Hola");

    cd("..");
    cd("..");

    cd("include");
    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("header1");
    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("Vars");
    cd("..");
    cd("header2");
    printf("El current nombre del archivo es %s\n", file_pointer->directory_name);
    cd("Vars");
    ls();

    cd("..");
    ls();
    cd("..");
    ls();
    rmdir("JAJAJA");

    free(root);
    /*
    add_node("root");
    add_node("sub_file");
    add_node("adios");
    add_node("diay");
    print_list();
    printf("El largo de la lista es: %i\n", lk_len());
    printf("El file obtenido es: %s\n", get_file(1));
    push_in(3, "adiooooooos");
    print_list();
    printf("El largo de la lista es: %i\n", lk_len());
    delete_in(3);
    delete_in(0);
    print_list();
    free(head);*/
}
//----------------------File system--------------------------------------
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
}
void rmdir(char* directory){
    file_system* temp = file_pointer->son_file;
    if (temp == NULL)
    {
        printf("\033[1;31m Can not remove inexisting directory. \033[0m \n");
    }else
    {
        while (strcmp(temp->directory_name, directory) != 0)
        {
            temp = temp->brother_file;
            if (temp == NULL)
            {
                /*printf("\033[1;31m Can not remove inexisting directory. \033[0m \n", next_directory);
                return;*/
                break;
            }
        }
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