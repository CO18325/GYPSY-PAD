#include <gtk/gtk.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>//system error number.

/*
static void menu_response(GtkWidget *menu_item,gpointer data){
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"New")==0){
		g_print("you have pressed New");
	}
        if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"About")==0){
                g_print("you have pressed about");
        }
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Save")==0){
                g_print("you have pressed save");
	}
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Cut")==0){
                g_print("you have pressed cut");
        }
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Copy")==0){
                g_print("you have pressed copy");
        }
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Paste")==0){
                g_print("you have pressed paste");
        }
}
*/

static void open_dialog(GtkWidget *menu_item,gpointer window){
	GtkWidget *dialog;
        GtkTextBuffer *buffer;
	dialog=gtk_file_chooser_dialog_new("Open File",GTK_WINDOW(window),
	GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(window));	
	gtk_widget_show_all(dialog);
	gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
	if(resp==GTK_RESPONSE_OK){
		g_print("%s\n",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));//it gets printed in the terminal
		gchar *cha;//corresponds to standard C char type 
		gsize bits;//an unsigned integer type of the result of the sizeof operator,corresponding to the size_t type defined in C99. 
		g_file_get_contents(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)),&cha,&bits,NULL);
		gtk_text_buffer_set_text(buffer,cha,-1);
            				
	}
	else
		g_print("u pressed cancel");
	gtk_widget_destroy(dialog);

}

static void save_dialog(GtkWidget *menu_item,gpointer window){
	GtkWidget *dialog;
        GtkTextBuffer *buffer;
	dialog=gtk_file_chooser_dialog_new("Save File",GTK_WINDOW(window),
	GTK_FILE_CHOOSER_ACTION_SAVE,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(window));	
	gtk_widget_show_all(dialog);
	GtkTextIter start,end;
	gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
	if(resp==GTK_RESPONSE_OK){
		gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer),&start);
		gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer),&end);
		FILE *f;
		f=fopen(gtk_file_chooser_get_filename(dialog),"w");
		fprintf(f,"%s",gtk_text_buffer_get_text(buffer,&start,&end,-1));
		fclose(f);
                
		
		
				
	}
	else
		g_print("u pressed cancel");

	gtk_widget_destroy(dialog);



}

static void about_label(GtkWidget *menu_item,gpointer window){
	GtkWidget *window_1,*label_1;
	window_1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window_1),900,900);
	gtk_window_set_title(GTK_WINDOW(window_1), "ABOUT");
	label_1=gtk_label_new("IT IS IS A SIMPLE EDITOR MADE IN GTK  \nMade by INDERPREET SINGH");
	g_signal_connect(window_1,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_add(GTK_CONTAINER(window_1),label_1);
	gtk_widget_show_all(window_1);
	
}	


/*
  update_statusbar(GtkTextBuffer *buffer,GtkStatusbar  *statusbar) {
  gchar *msg;
  gint row, col;
  GtkTextIter iter;
  
  gtk_statusbar_pop(statusbar, 0); 

  gtk_text_buffer_get_iter_at_mark(buffer,
      &iter, gtk_text_buffer_get_insert(buffer));

  row = gtk_text_iter_get_line(&iter);
  col = gtk_text_iter_get_line_offset(&iter);

  msg = g_strdup_printf("Col: %d Ln: %d", col+1, row+1);

  gtk_statusbar_push(statusbar, 0, msg);

  g_free(msg);
}


void mark_set_callback(GtkTextBuffer *buffer, const GtkTextIter *new_location, GtkTextMark *mark, gpointer data) {
                       
  update_statusbar(buffer, GTK_STATUSBAR(data));
}
*/
GdkPixbuf *create_pixbuf(const gchar *filename){
	GdkPixbuf *pixbuf;
	GError *error=NULL;
	pixbuf=gdk_pixbuf_new_from_file(filename,&error);

	if(!pixbuf){
		fprintf(stderr,"%s\n",error->message);//error.h
		g_error_free(error);

	}
	return pixbuf;
}

int main(int argc, char *argv[]) {



  GtkWidget *window;
  GtkWidget *cer; //widget for a scrolled window 
  GtkWidget *vbox;
  GtkWidget *menu_bar,*menu_item,*file_menu,*help_menu;//*edit_menu;
  GtkWidget *toolbar;
  GtkWidget *view;
  //GtkWidget *statusbar;
  GtkToolItem *exit,*sep,*saveTb,*newTb,*openTb;
  GtkTextBuffer *buffer;
  GdkPixbuf *icon;
  view = gtk_text_view_new();//it creates a new GtkTextView widget which is used to display and edit multiline text
  
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),900,900);//settings for default window size
  gtk_window_set_title(GTK_WINDOW(window), "THE GIPSY PAD");

//adding an icon:-----

icon=create_pixbuf("wicon.ico");
gtk_window_set_icon(GTK_WINDOW(window),icon);



cer=gtk_scrolled_window_new(NULL,NULL);//a scrolled window is created
vbox = gtk_vbox_new(FALSE, 0);//vbox is a container that organizes its child widgets into a single column
gtk_container_add(GTK_CONTAINER(window), vbox);
menu_bar=gtk_menu_bar_new();//it creates a new GtkMenu
file_menu=gtk_menu_new();
help_menu=gtk_menu_new();
//edit_menu=gtk_menu_new();



menu_item=gtk_menu_item_new_with_label("File");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),file_menu);
gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);

menu_item=gtk_menu_item_new_with_label("Help");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),help_menu);
gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);

/*
menu_item=gtk_menu_item_new_with_label("Edit");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),edit_menu);
gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);
*/
menu_item=gtk_menu_item_new_with_label("New");
gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(main),NULL);

menu_item=gtk_menu_item_new_with_label("Open");
gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(open_dialog),view);

menu_item=gtk_menu_item_new_with_label("Save");
gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(save_dialog),view);


/*
menu_item=gtk_menu_item_new_with_label("Exit");
gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(gtk_main_quit),NULL);
*/


menu_item=gtk_menu_item_new_with_label("About");
gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(about_label),NULL);


/*
menu_item=gtk_menu_item_new_with_label("Cut");
gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(menu_response),NULL);

menu_item=gtk_menu_item_new_with_label("Copy");
gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(menu_response),NULL);

menu_item=gtk_menu_item_new_with_label("Paste");
gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),menu_item);
g_signal_connect(menu_item,"activate",G_CALLBACK(menu_response),NULL);
*/





  gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);

  toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exit, -1);
 
  sep=gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

  saveTb = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);

  newTb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);

  openTb = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openTb, -1);


  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

 
  gtk_container_add(GTK_CONTAINER(cer),view);
gtk_container_add(GTK_CONTAINER(vbox),cer);

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

  /*
  statusbar = gtk_statusbar_new();
  gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);
  */

  g_signal_connect(G_OBJECT(exit), "clicked", 
        G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(openTb),"clicked",
	G_CALLBACK(open_dialog),view);

 g_signal_connect(G_OBJECT(newTb),"clicked",
	G_CALLBACK(main),NULL);
 g_signal_connect(G_OBJECT(saveTb),"clicked",
	G_CALLBACK(save_dialog),view);


/*
  g_signal_connect(buffer, "changed",
        G_CALLBACK(update_statusbar), statusbar);

  g_signal_connect_object(buffer, "mark_set", 
        G_CALLBACK(mark_set_callback), statusbar, 0);
*/
  g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  //update_statusbar(buffer, GTK_STATUSBAR(statusbar));
  gtk_object_unref(icon);
  gtk_main();

  return 0;
}
