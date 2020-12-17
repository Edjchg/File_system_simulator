
#ifndef gtktreeview_H
#define gtktreeview_H

#include <gtk/gtk.h>

#include "../structure/structure.h"

GtkTreeModel *create_model_treeview(void);
static void add_row_tree (gchar *name, GtkTreeView *treeview, const gchar *path_string, gint t);
static void add_root(GtkTreeView *treeview);
void configure_vi(int argc, char *argv[], file_system *root);
void show_disk(file_system *root, int argc, char *argv[]);
void show_disk_aux(file_system* node, char *nivel, int parent);

#endif