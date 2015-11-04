
#include <gtk/gtk.h>
#include "talk-client.h"

typedef struct {
        GtkWidget *s_add;
		GtkWidget *s_port;
		GtkWidget *u_name;
		GtkWidget *u_pass;
		GtkWidget *u_confrim;
		GtkWidget *r_name;
		GtkWidget *window;
		GtkWidget *main_window;
		//int is;
} EntryArray;

typedef struct {
        GtkWidget *u;
		GtkWidget *r;
		//int is;
} SelectArray;

void close_window(GtkWidget *widget, gpointer window);
int updata_message(GtkWidget *widget, gpointer window);
void update_list_rooms(GtkWidget *widget, gpointer window);
void update_list_users(GtkWidget *widget, gpointer window);
void static start_loop();
void static stop_loop();
int static save_settings(GtkWidget * g, EntryArray * entrys);
void create_user_process_with_login(GtkWidget * g, EntryArray * entrys);
void create_user_process_without_login(GtkWidget * g, EntryArray * entrys); 
void create_room_process(GtkWidget * g, EntryArray * entrys);
void on_room_select_change(GtkWidget *widget, gpointer label); 
void leave_room_process(GtkWidget * g, void * array);
void enter_room_process(GtkWidget * g, void * array);
static GtkWidget *create_list( const char * titleColumn, GtkListStore *model , int type);
static void begin_text( GtkTextBuffer *buffer, const char * initialText );
static void insert_text( GtkTextBuffer *buffer, const char * initialText ); 
static GtkWidget *create_text( const char * initialText, int type);
static GtkWidget * create_popup( const char * initialText); 
void setup(GtkWidget *widget, gpointer w);
void create_user(GtkWidget *widget, gpointer w);
void send_message_process(GtkWidget *widget, gpointer window);
gboolean on_popup_out (GtkWidget *widget, GdkEventFocus *event, gpointer data); 
int main( int   argc, char *argv[] ); 