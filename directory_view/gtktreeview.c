
#include "gtktreeview.h"

GdkPixbuf *folder_img;
GdkPixbuf *file_img;
GtkWidget *treeview;

enum
{
	COLUMN_MOVE,
	COLUMN_COMMENTS,
	NUM_COLUMNS
};

/**
 * Inicializate the tree model
 * */
GtkTreeModel *create_model_treeview(void)
{
	GtkTreeStore *model_store;
	model_store = gtk_tree_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
	
	return GTK_TREE_MODEL(model_store);
}

/**
 * Add directories and files in tree.
 * */
static void add_row_tree (gchar *name, GtkTreeView *treeview, const gchar *path_string, gint t)
{
	GtkTreeModel *model;
	GtkTreeStore *model_store;
	GtkTreeIter iter, iter1;
	GtkTreeSelection *select;
	/* obtiene el modelo tipo arbol */
	model_store = (GtkTreeStore *) gtk_tree_view_get_model(treeview);
	select = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	gtk_tree_selection_get_selected (select, &model, NULL);

	gtk_tree_model_get_iter_from_string (model, &iter, path_string);
	gtk_tree_store_append(model_store, &iter1, &iter);
	if (t == 0)
	{
		gtk_tree_store_set(model_store, &iter1,
		COLUMN_MOVE,folder_img, 
		COLUMN_COMMENTS, name, 
		-1);
	}
	else
	{
		gtk_tree_store_set(model_store, &iter1,
		COLUMN_MOVE,file_img, 
		COLUMN_COMMENTS, name, 
		-1);
	}
	//g_print("From add row :%s \n", gtk_tree_model_get_string_from_iter (model, &iter));
	//g_print("add new row....\n");
}


/**
 * Create first directory in the three.
 * 
 * */
static void add_root(GtkTreeView *treeview)
{
	GtkTreeStore *model_store;
	GtkTreeIter iter;
	model_store = (GtkTreeStore *) gtk_tree_view_get_model(treeview);
	gtk_tree_store_append(model_store, &iter, NULL);
	gtk_tree_store_set(model_store, &iter,
			COLUMN_MOVE,folder_img, 
			COLUMN_COMMENTS, "root", 
			-1);
	//g_print("Directory root added\n");
}

/**
 * Create column for name and img. 
 * */
static void add_column_tree(GtkTreeView *treeview)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, "Directory Tree");
	renderer = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_column_pack_start (column, renderer, FALSE);
	gtk_tree_view_column_set_attributes (column,renderer,"pixbuf",0,NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_column_pack_start (column, renderer, FALSE);
	gtk_tree_view_column_set_attributes (column,renderer,"text",1,NULL);
	gtk_tree_view_append_column (treeview, column);
}
/**
int  main (int argc, char * argv[])
{
	file_system *root = NULL;
	show_disk(root, argc, argv);
}
**/

/**
 * Function to configure and inicializate gtk element.
 * */
void configure_vi(int argc, char * argv[], file_system *root)
{
	GtkWidget *window, *scroll;
	//GtkWidget *treeview;
	GtkWidget *box, *vbox;
	GtkTreeModel *model;
	
	gtk_init(&argc, &argv);
	folder_img =  gdk_pixbuf_new_from_file ("../directory_view/folder.png", NULL);
	file_img =  gdk_pixbuf_new_from_file ("../directory_view/file.png", NULL);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Directory");
	gtk_window_set_default_size(GTK_WINDOW(window), 600,800);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	scroll = gtk_scrolled_window_new(NULL, NULL);
	model = create_model_treeview();
	treeview = gtk_tree_view_new();
	add_column_tree(GTK_TREE_VIEW(treeview));
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
	g_object_unref(G_OBJECT(model));
	box = gtk_box_new(TRUE, 10);
	vbox = gtk_box_new(TRUE, 5);
	gtk_widget_set_name(box, "Box");
	
	gtk_container_add(GTK_CONTAINER(scroll), treeview);
	gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(vbox), box, TRUE, TRUE, 2);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	g_signal_connect(G_OBJECT(window), "destroy", 
			gtk_main_quit, NULL);

	add_root(GTK_TREE_VIEW(treeview));
	file_system *temp = root;
	char nivel[100] = "0";
	//printf("Show_disk_aux \n \n");
    show_disk_aux(temp->son_file, nivel, 0);
	gtk_widget_show_all(window);
	gtk_main();
}


/**
 *	Function to create and show  windows with tree directory.
 * */
void show_disk(file_system *root, int argc, char *argv[])
{
    configure_vi(argc, argv, root);
}

/**
 *	Recursive funtion for navigation the tree.  
 * */
void show_disk_aux(file_system* node, char *nivel, int parent)
{
    if (node != NULL)
    {   
		//printf("Nivel %s name %s \n", nivel, node->directory_name);
		add_row_tree(node->directory_name,
					 GTK_TREE_VIEW(treeview), nivel, 0);  
		if (node->son_file != NULL)
        {
			char snum[15];
			sprintf(snum, ":%d", parent);
			strcat(nivel, snum);
			show_disk_aux(node->son_file, nivel, 0);
			nivel[strlen(nivel)-2] = '\0'; 
			//printf("%s \n", nivel); 

        }
		if (node->file_!= NULL)
        {
            file *temp;
            temp = node->file_;
			char snum[15];
			sprintf(snum, ":%d", parent);
			strcat(nivel, snum);
            while (temp != NULL)
            {
				add_row_tree(temp->file_name, GTK_TREE_VIEW(treeview), nivel, 1);
                temp = temp->next_file;
            }   
			nivel[strlen(nivel)-2] = '\0';
		} 
		if (node->brother_file != NULL)
        {
			parent++;
			show_disk_aux(node->brother_file, nivel, parent);
        }
    }           
}
