#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale>
#include "IRCClient.h"






GtkListStore * list_rooms;
GtkListStore * list_users;


char * USER_NAME = strdup("bowiegou");
char * USER_PASS = strdup("123");
char * SERVER_ADDRESS = strdup("localhost");
char * RESPONSE;
LinkedList * RESPONSE_LIST;
GtkWidget * MAIN_MEG_BOX;
GtkWidget * MAIN_INPUT_BOX;
GtkWidget * MAIN_ROOM_LIST;
GtkWidget * MAIN_USER_LIST;
char * CURRENT_ROOM = strdup("Lobby");
char * selected_room = strdup("Lobby");
//char COMMAND[20*1024];
int SERVER_PORT = 10000;
int MESSAGE_LINE = 0;
int STARTED = 0;

guint room_interval = -1;
guint user_interval = -1;
guint message_interval = -1;


void close_window(GtkWidget *widget, gpointer window) {
    gtk_widget_destroy(GTK_WIDGET(window));
}
void start_up_close(GtkWidget *w, gpointer ww) {
	if(!STARTED) {
		gtk_main_quit();
	}
}
int updata_message(GtkWidget *widget, gpointer window) {
	if(strcmp(CURRENT_ROOM,"Lobby") && 
	get_messages(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,MESSAGE_LINE,CURRENT_ROOM,&RESPONSE_LIST) != 2){
	
		int i;
		char * t_message;
		char msg[20*1024+10];
		int num_of_ele = llist_number_elements(RESPONSE_LIST);
		for(i = num_of_ele; i>=1; i--){
			llist_get_ith(RESPONSE_LIST,i,&t_message);
			sprintf(msg, "%s\n", t_message);
			MESSAGE_LINE ++;
			insert_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),(const char*) msg);
		}
	} else {
		//char msg[20*1024+10];
		//sprintf(msg, "%s", "");
		printf("IN %s, NO-NEW-MSG\n", CURRENT_ROOM);
		//insert_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),(const char*) msg);
	}
	
	return 1;
	
	
}
void update_list_rooms(GtkWidget *widget, gpointer window) {
    GtkTreeIter iter;
    int i;
	char * room_name;
	
	gtk_list_store_clear(GTK_LIST_STORE(list_rooms));
	
	gchar *msg = g_strdup_printf ("Lobby");
    gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
    gtk_list_store_set (GTK_LIST_STORE (list_rooms), 
	                    &iter,
                            0, msg,
	                    -1);
	
	print_rooms(SERVER_ADDRESS, SERVER_PORT, USER_NAME, USER_PASS, &RESPONSE_LIST);
	int num_of_ele = llist_number_elements(RESPONSE_LIST);
    /* Add some messages to the window */
    for (i = 1; i <=num_of_ele; i++) {
		llist_get_ith(RESPONSE_LIST, i, &room_name);
        msg = g_strdup_printf ("%s", room_name);
        gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_rooms), 
	                    &iter,
                            0, msg,
	                    -1);
		g_free (msg);
    }
	////free(RESPONSE_LIST);
	////free(room_name);
}
void update_list_users(GtkWidget *widget, gpointer window) {
	
	
	
    GtkTreeIter iter;
    int i;
	
	if(!strcmp(selected_room, "Lobby") || !strcmp(selected_room, "")){
		print_users(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,&RESPONSE_LIST);
	} else {
		print_users_in_room(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,selected_room,&RESPONSE_LIST);
	}
	gtk_list_store_clear(GTK_LIST_STORE(list_users));
	int num_of_ele = llist_number_elements(RESPONSE_LIST);
	char * n;
    /* Add some messages to the window */
    for (i = 1; i <= num_of_ele; i++) {
		llist_get_ith(RESPONSE_LIST, i, &n);
        gchar *msg = g_strdup_printf ("%s", n);
        gtk_list_store_append (GTK_LIST_STORE (list_users), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_users), 
                      &iter,
                      0, msg,
                      -1);
	g_free (msg);
    }
	////free(RESPONSE_LIST);
	////free(n);
}
void static start_loop() {
	if(room_interval == -1&& user_interval == -1){
		room_interval = g_timeout_add(5001, (GSourceFunc) update_list_rooms, NULL);
		user_interval = g_timeout_add(5100, (GSourceFunc) update_list_users, NULL);
		message_interval = g_timeout_add(5200, (GSourceFunc) updata_message, NULL);
	}
}
void static stop_loop() {
	g_source_remove(room_interval);
	g_source_remove(user_interval);
	g_source_remove(message_interval);
	room_interval = -1;
	user_interval = -1;
	message_interval = -1;
}
int static save_settings(GtkWidget * g, EntryArray * entrys) {
	if(entrys->u_name != NULL && entrys->u_pass != NULL && entrys->s_add != NULL && entrys->s_port != NULL){
		
	GtkWidget * msgbox;
	GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	int blank = 1;
	char c;
	char * cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: User name is empty");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return 0;
	}
	free(cc);
	blank = 1;
	cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->s_add)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Server Address is empty");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return 0;
	}
	free(cc);
		blank = 1;
	cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->s_port)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Server Port is empty");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return 0;
	}
	free(cc);
	
	
	int fd = open_client_socket(strdup(gtk_entry_get_text(GTK_ENTRY(entrys->s_add))), 
	atoi(strdup(gtk_entry_get_text(GTK_ENTRY(entrys->s_port)))));
	if(fd == -1) {
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Cannot reach server");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return 0;
	}
	close(fd);
	
 	if(check_password(strdup(gtk_entry_get_text(GTK_ENTRY(entrys->s_add))), 
						atoi(strdup(gtk_entry_get_text(GTK_ENTRY(entrys->s_port)))),
						strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name))), 
						strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass))))){
							
							
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Username or Password Incorrect");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return 0;
		} 
		
		
		
		
		
		
		
		
		
		USER_NAME = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name)));
		USER_PASS = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass)));
		SERVER_ADDRESS = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->s_add)));
		SERVER_PORT = (int) gtk_spin_button_get_value (GTK_SPIN_BUTTON(entrys->s_port));
		STARTED = 1;
		if(entrys->main_window != NULL) {
			gtk_widget_show (entrys->main_window);
		}
		gtk_widget_destroy(GTK_WIDGET(entrys->window));
		update_list_rooms(NULL,NULL);
		update_list_users(NULL,NULL);
		start_loop();
		return 1;
	}
	else{
		return 0;
	}
	
	
	
}
void create_user_process_with_login(GtkWidget * g, EntryArray * entrys) {
	GtkWidget * msgbox;
	GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	//char * command;
	
	if(strcmp(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass)),gtk_entry_get_text(GTK_ENTRY(entrys->u_confrim)))){
	
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Password not matched");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return;
	}
	int blank = 1;
	char c;
	char * cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: User name is empty");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return;
	}
	blank = 1;
	cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Password is empty");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return;
	}
	
	free(cc);
	
	char * t_username = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name)));
	char * t_uaerpass = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass)));
	
	// sprintf(COMMAND, "ADD-USER %s %s", strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name))),
										// strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass))));
	
	
	
	
	add_user(SERVER_ADDRESS,SERVER_PORT,t_username,t_uaerpass,&RESPONSE);
	
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_OK,
									"%s", RESPONSE);
		if(!strcmp(RESPONSE,"OK\r\n")){						
			g_signal_connect_swapped (msgbox, "response",
									G_CALLBACK (gtk_widget_destroy),
									entrys->window);
									
			char t[20*1024];
			sprintf(t,"User changed to %s\n", t_username);
			gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),t,-1);
			USER_NAME = strdup(t_username);
			USER_PASS = strdup(t_uaerpass);
			////free(t);
		}
		else {
			g_signal_connect_swapped (msgbox, "response",
									G_CALLBACK (gtk_widget_destroy),
									msgbox);
		}
		////free(t_username);
		////free(t_uaerpass);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		leave_room_process(NULL,NULL);
		update_list_rooms(NULL,NULL);
		update_list_users(NULL,NULL);
		start_loop();
		
		return;
	
	
	
	
	

}
void create_user_process_without_login(GtkWidget * g, EntryArray * entrys) {
	GtkWidget * msgbox;
	GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	//char * command;
	
	if(strcmp(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass)),gtk_entry_get_text(GTK_ENTRY(entrys->u_confrim)))){
	
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Password not matched");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return;
	}
	int blank = 1;
	char c;
	char * cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: User name is empty");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return;
	}
	blank = 1;
	cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Password is empty");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return;
	}
	
	free(cc);
	
	char * t_username = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name)));
	char * t_uaerpass = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass)));
	
	// sprintf(COMMAND, "ADD-USER %s %s", strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name))),
										// strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass))));
	
	
	
	
	add_user(SERVER_ADDRESS,SERVER_PORT,t_username,t_uaerpass,&RESPONSE);
	
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_OK,
									"%s", RESPONSE);
		if(!strcmp(RESPONSE,"OK\r\n")){						
			g_signal_connect_swapped (msgbox, "response",
									G_CALLBACK (gtk_widget_destroy),
									entrys->window);
			//USER_NAME = strdup(t_username);
			//USER_PASS = strdup(t_uaerpass);
		}
		else {
			g_signal_connect_swapped (msgbox, "response",
									G_CALLBACK (gtk_widget_destroy),
									msgbox);
		}
		////free(t_username);
		////free(t_uaerpass);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		update_list_rooms(NULL,NULL);
		update_list_users(NULL,NULL);
		start_loop();
		
		return;
	

} 
void create_room_process(GtkWidget * g, EntryArray * entrys){
	GtkWidget * msgbox;
	GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	int blank = 1;
	char c;
	char * cc = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->r_name)));
	
	for(int i = 0; i < strlen(cc); i++){
		c = cc[i];
		
		if(!isspace(c)){
			blank = 0;
		}
	}
	
	if(blank){
	
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									"Error: Room name invalid");
									
		g_signal_connect_swapped (msgbox, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          msgbox);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		
		return;
	}
	
	//char * t_username = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name)));
	char * t_room = strdup(gtk_entry_get_text(GTK_ENTRY(entrys->r_name)));
	
	// sprintf(COMMAND, "ADD-USER %s %s", strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_name))),
										// strdup(gtk_entry_get_text(GTK_ENTRY(entrys->u_pass))));
	
	
	
	
	create_room(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,t_room,&RESPONSE);
	
		msgbox =  gtk_message_dialog_new (GTK_WINDOW(entrys->window),
									flags,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_OK,
									"%s", RESPONSE);
		if(!strcmp(RESPONSE,"OK\r\n")){						
			g_signal_connect_swapped (msgbox, "response",
									G_CALLBACK (gtk_widget_destroy),
									entrys->window);
			//USER_NAME = strdup(t_username);
			//USER_PASS = strdup(t_uaerpass);
		}
		else {
			g_signal_connect_swapped (msgbox, "response",
									G_CALLBACK (gtk_widget_destroy),
									msgbox);
		}
		free(t_room);
		////free(t_uaerpass);
									
		gtk_dialog_run (GTK_DIALOG (msgbox));
		update_list_rooms(NULL,NULL);
		update_list_users(NULL,NULL);
		
		start_loop();
		
		return;
	
}
void on_room_select_change(GtkWidget *widget, gpointer label) {
  GtkTreeIter iter;
  GtkTreeModel *model;
  char *value;


  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) {
	if(model != NULL){
		gtk_tree_model_get(model, &iter, 0, &value,  -1);
	}else {
		value = strdup("Lobby");
	}
	selected_room = strdup(value);
    //gtk_label_set_text(GTK_LABEL(label), value);
	update_list_users(NULL,NULL);
    g_free(value);
  }
}
void leave_room_process(GtkWidget * g, void * array) {
	char msg[20*1024+10];
	char * r = strdup(CURRENT_ROOM);
	send_message(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,CURRENT_ROOM,strdup("<Left the Room>"),&RESPONSE);
	leave_room(SERVER_ADDRESS, SERVER_PORT,USER_NAME, USER_PASS, r, &RESPONSE);
	if(!strcmp(RESPONSE,"OK\r\n")){
		sprintf(msg,"SYSTEM: You have Left Room: %s\n", r);
		CURRENT_ROOM = strdup("Lobby");
		
	}else{
		sprintf(msg,"SYSTEM: %s\n", RESPONSE);
	}
	insert_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),(const char*) msg);
	MESSAGE_LINE = 0;
	
}
void enter_room_process(GtkWidget * g, void * array) {
	
	char msg[20*1024+10];
	char * r = strdup(selected_room);
	send_message(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,CURRENT_ROOM,strdup("<Left the Room>"),&RESPONSE);
	leave_room(SERVER_ADDRESS, SERVER_PORT,USER_NAME, USER_PASS, CURRENT_ROOM, &RESPONSE);
	enter_room(SERVER_ADDRESS, SERVER_PORT,USER_NAME, USER_PASS, r, &RESPONSE);
	if(!strcmp(RESPONSE,"OK\r\n")){
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),strdup(""),-1);
		CURRENT_ROOM = strdup(r);
		sprintf(msg,"SYSTEM: You have Enter Room: %s\n", r);
		send_message(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,CURRENT_ROOM,strdup("<Entered the Room>"),&RESPONSE);
		MESSAGE_LINE = 0;
	}else if(strcmp(r,"Lobby")){
		sprintf(msg,"SYSTEM: %s\n", RESPONSE);
	}else if(strcmp(CURRENT_ROOM,"Lobby")){
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),strdup(""),-1);
		sprintf(msg,"SYSTEM: You have exited to Lobby\n");
		CURRENT_ROOM = strdup("Lobby");
	} else {
		sprintf(msg,"SYSTEM: You are already in Lobby\n");
	}
	//gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),msg,-1);
	insert_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),(const char*) msg);
	
}
static GtkWidget *create_list( const char * titleColumn, GtkListStore *model , int type) {
    GtkWidget *scrolled_window;
	GtkWidget **tree_view;
	if(type == 1){
		
		tree_view = &MAIN_ROOM_LIST;
	} else if( type ==2) {
		tree_view = &MAIN_USER_LIST;
	}
    //GtkListStore *model;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    int i;
   
    /* Create a new scrolled window, with scrollbars only if needed */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
				    GTK_POLICY_AUTOMATIC, 
				    GTK_POLICY_AUTOMATIC);
   
    //model = gtk_list_store_new (1, G_TYPE_STRING);
    *tree_view = gtk_tree_view_new ();
    gtk_container_add (GTK_CONTAINER (scrolled_window), *tree_view);
    gtk_tree_view_set_model (GTK_TREE_VIEW (*tree_view), GTK_TREE_MODEL (model));
    gtk_widget_show (*tree_view);
   
    cell = gtk_cell_renderer_text_new ();

    column = gtk_tree_view_column_new_with_attributes (titleColumn,
                                                       cell,
                                                       "text", 0,
                                                       NULL);
  
    gtk_tree_view_append_column (GTK_TREE_VIEW (*tree_view),
	  		         GTK_TREE_VIEW_COLUMN (column));

    return scrolled_window;
}
static void begin_text( GtkTextBuffer *buffer, const char * initialText ) {
   GtkTextIter iter;
 
   gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
   gtk_text_buffer_insert (buffer, &iter, initialText,-1);
}
static void insert_text( GtkTextBuffer *buffer, const char * initialText ) {
   GtkTextIter iter;
 
   gtk_text_buffer_get_end_iter (buffer, &iter);
   gtk_text_buffer_insert (buffer, &iter, initialText,-1);
}
static GtkWidget *create_text( const char * initialText, int type) {
   GtkWidget *scrolled_window;
   GtkWidget ** view;
   if(type == 1){
		view = &MAIN_MEG_BOX;
   }else if(type == 2){
		view = &MAIN_INPUT_BOX;
   }
   GtkTextBuffer *buffer;

   *view = gtk_text_view_new ();
   buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (*view));

   scrolled_window = gtk_scrolled_window_new (NULL, NULL);
   gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
		   	           GTK_POLICY_AUTOMATIC,
				   GTK_POLICY_AUTOMATIC);

   gtk_container_add (GTK_CONTAINER (scrolled_window), *view);
   begin_text (buffer, initialText);

   gtk_widget_show_all (scrolled_window);

   return scrolled_window;
}
static GtkWidget * create_popup( const char * initialText) {
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), initialText);
    g_signal_connect (window, "destroy",
                G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 40, 50);



    GtkWidget *table = gtk_table_new (10, 10, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    gtk_table_set_row_spacings(GTK_TABLE (table), 5);
    gtk_table_set_col_spacings(GTK_TABLE (table), 5);

    return window;

}
void setup(GtkWidget *widget, gpointer w) {
	
	
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *server_add = gtk_entry_new ();
	GtkWidget *server_port = gtk_spin_button_new_with_range (1,65535,1);
	GtkWidget *user_name = gtk_entry_new ();
	GtkWidget *user_pass = gtk_entry_new ();
	GtkWidget *confirm =  gtk_button_new_with_label ("Confirm");
	GtkWidget *cancel = gtk_button_new_with_label ("Cancel");
	GtkWidget *confirm_user =  gtk_button_new_with_label ("Confirm");
	GtkWidget *cancel_user = gtk_button_new_with_label ("Cancel");
	
	//GtkWidget ** entryArray = (GtkWidget **) malloc(sizeof(GtkWidget *) * 4);
	//Array Storing data of Entry Widgets
	
	EntryArray * entrys = (EntryArray *) malloc (sizeof(EntryArray));
	entrys->u_name = user_name;
	entrys->u_pass = user_pass;
	entrys->s_add = server_add;
	entrys->s_port = server_port;
	entrys->window = window;
	
	
	
	GtkWidget *text_server_add = gtk_accel_label_new ("Server Address:");
	GtkWidget *text_server_port = gtk_accel_label_new ("Server Port:");
	GtkWidget *text_user_name = gtk_accel_label_new ("User name:");
	GtkWidget *text_user_pass = gtk_accel_label_new ("Password:");
	
	
	stop_loop(); // Stop Updating Room and User
	//Initialize window
	gtk_window_set_title (GTK_WINDOW (window), "Setup");
	g_signal_connect (window, "destroy",
                G_CALLBACK (on_popup_out), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (GTK_WIDGET (window), 400, 300);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_decorated (GTK_WINDOW (window), TRUE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_skip_pager_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	
	
	
	
	//Initialize Base Table
	GtkWidget *base = gtk_table_new (10, 10, TRUE);
	gtk_container_add (GTK_CONTAINER (window), base);
	gtk_table_set_row_spacings(GTK_TABLE (base), 5);
	gtk_table_set_col_spacings(GTK_TABLE (base), 5); 
	
	
	
	
	//Initialize Notebook
	GtkWidget * notebook = gtk_notebook_new();
	GtkWidget * label;
	// char bufferf[32];
	// char bufferl[32];
	
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook),GTK_POS_TOP);
	//gtk_container_add (GTK_CONTAINER (window), notebook);
	gtk_table_attach_defaults(GTK_TABLE (base), notebook, 0, 11, 0, 11); 
	gtk_notebook_set_show_border(GTK_NOTEBOOK(notebook), FALSE);
	
	 // for (int i=0; i < 2; i++) {
        // sprintf(bufferf, "Append Frame %d", i+1);
        // sprintf(bufferl, "Page %d", i+1);
        
        // frame = gtk_frame_new (bufferf);
        // gtk_container_border_width (GTK_CONTAINER (frame), 10);
        // gtk_widget_set_usize (frame, 100, 75);
        // gtk_widget_show (frame);
        
        // label = gtk_label_new (bufferf);
        // gtk_container_add (GTK_CONTAINER (frame), label);
        // gtk_widget_show (label);
        
       // label = gtk_label_new (bufferl);
       // gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
    //
	//                                                                                Server Info Page
	GtkWidget *server_table = gtk_table_new (10, 10, TRUE);
	label = gtk_label_new("Server");
	//gtk_container_add (GTK_CONTAINER (window), server_table);
	gtk_table_set_row_spacings(GTK_TABLE (server_table), 5);
	gtk_table_set_col_spacings(GTK_TABLE (server_table), 5); 
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), server_table, label);
	
	
	//Server Address Entry
	gtk_entry_set_max_length (GTK_ENTRY (server_add), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (server_add), SERVER_ADDRESS);
    gtk_editable_select_region (GTK_EDITABLE (server_add),
			        0, GTK_ENTRY (server_add)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (server_table), server_add, 2, 8, 3, 4); 
    gtk_widget_show (server_add);
	
	
	//Server Port Entry
	//	gtk_entry_set_max_length (GTK_ENTRY (server_port), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
   // gtk_entry_set_text (GTK_ENTRY (server_port), SERVER_PORT);
    //tmp_pos = GTK_ENTRY (server_port)->text_length;
   // gtk_editable_insert_text (GTK_EDITABLE (server_port), " world", -1, &tmp_pos);
    //gtk_editable_select_region (GTK_EDITABLE (server_port),
	//		        0, GTK_ENTRY (server_port)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(server_port) , SERVER_PORT);
	gtk_table_attach_defaults(GTK_TABLE (server_table), server_port, 2, 8, 5, 7); 
    gtk_widget_show (server_port);
	
	//Lable of Server Entry
	gtk_table_attach_defaults(GTK_TABLE(server_table), text_server_add, 2, 8, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(server_table), text_server_port, 2, 8, 4, 5);
	
	//Button of Server Entry
	g_signal_connect (confirm, "clicked",
          G_CALLBACK (save_settings), entrys);
		  
	g_signal_connect (cancel, "clicked",
          G_CALLBACK (close_window), G_OBJECT(window));
	gtk_table_attach_defaults(GTK_TABLE(server_table), confirm, 2, 5, 7, 9);
	gtk_table_attach_defaults(GTK_TABLE(server_table), cancel, 5, 8, 7, 9);
	
	
	
	
	
	
	
	
	
	
	
	//                                                                               User Info Page 
	GtkWidget *user_table = gtk_table_new (10, 10, TRUE);
	label = gtk_label_new("User");
	//gtk_container_add (GTK_CONTAINER (window), user_table);
	gtk_table_set_row_spacings(GTK_TABLE (user_table), 5);
	gtk_table_set_col_spacings(GTK_TABLE (user_table), 5); 
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), user_table, label);
	
	gtk_entry_set_max_length (GTK_ENTRY (user_name), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (user_name), USER_NAME);
    gtk_editable_select_region (GTK_EDITABLE (user_name),
			        0, GTK_ENTRY (user_name)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (user_table), user_name, 2, 8, 3, 4); 
    gtk_widget_show (user_name);
	
	//User Password Entry
		gtk_entry_set_max_length (GTK_ENTRY (user_pass), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (user_pass), USER_PASS);
    //tmp_pos = GTK_ENTRY (server_port)->text_length;
   // gtk_editable_insert_text (GTK_EDITABLE (server_port), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (user_pass),
			        0, GTK_ENTRY (user_pass)->text_length);
					
	gtk_entry_set_visibility (GTK_ENTRY(user_pass), FALSE);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (user_table), user_pass, 2, 8, 5, 6); 
    gtk_widget_show (user_pass);
	
	//Lable of Server Entry
	gtk_table_attach_defaults(GTK_TABLE(user_table), text_user_name, 2, 8, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(user_table), text_user_pass, 2, 8, 4, 5);
	
	//Button of Server Entry
	g_signal_connect (confirm_user, "clicked",
          G_CALLBACK (save_settings), entrys);
	g_signal_connect (cancel_user, "clicked",
          G_CALLBACK (close_window), G_OBJECT(window));
		  
	gtk_table_attach_defaults(GTK_TABLE(user_table), confirm_user, 2, 5, 7, 9);
	gtk_table_attach_defaults(GTK_TABLE(user_table), cancel_user, 5, 8, 7, 9);
	
	start_loop();
	
	
	
	
	
	
	
	
	gtk_widget_show_all (window);
	gtk_widget_grab_focus (window);
	
	
	
}
void create_user(GtkWidget *widget, gpointer w){
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	GtkWidget *user_name = gtk_entry_new ();
	GtkWidget *user_pass = gtk_entry_new ();
	GtkWidget *user_pass_confirm = gtk_entry_new ();
	GtkWidget *room_name = gtk_entry_new ();
	
	EntryArray * entrys = (EntryArray *) malloc( sizeof(EntryArray));
	entrys->window = window;
	entrys->u_name = user_name;
	entrys->u_pass = user_pass;
	entrys->u_confrim = user_pass_confirm;
	entrys->r_name = room_name;
	
	GtkWidget *save_using =  gtk_button_new_with_label ("Create and Login");
	GtkWidget *save_only =  gtk_button_new_with_label ("Create Only");
	GtkWidget *cancel = gtk_button_new_with_label ("Cancel");
	
	GtkWidget *r_cancel = gtk_button_new_with_label ("Cancel");
	GtkWidget *r_confrim = gtk_button_new_with_label ("Confirm");
	
	GtkWidget *text_user_name = gtk_accel_label_new ("User name:");
	GtkWidget *text_user_pass = gtk_accel_label_new ("Password:");
	GtkWidget *text_user_pass_confirm = gtk_accel_label_new ("Confirm Password:");
	
	GtkWidget *text_r_name = gtk_accel_label_new ("Room name:");
	
	stop_loop(); // Stop Updating Room and User
	
	gtk_window_set_title (GTK_WINDOW (window), "Create");
	g_signal_connect (window, "destroy",
					G_CALLBACK (on_popup_out), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (GTK_WIDGET (window), 400, 300);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_decorated (GTK_WINDOW (window), TRUE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_skip_pager_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	
	
	GtkWidget *base = gtk_table_new (10, 10, TRUE);
	gtk_container_add (GTK_CONTAINER (window), base);
	gtk_table_set_row_spacings(GTK_TABLE (base), 5);
	gtk_table_set_col_spacings(GTK_TABLE (base), 5); 
	
	
	
	GtkWidget * notebook = gtk_notebook_new();
	GtkWidget * label;
	// char bufferf[32];
	// char bufferl[32];
	
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook),GTK_POS_TOP);
	//gtk_container_add (GTK_CONTAINER (window), notebook);
	gtk_table_attach_defaults(GTK_TABLE (base), notebook, 0, 11, 0, 11); 
	gtk_notebook_set_show_border(GTK_NOTEBOOK(notebook), FALSE);
	
	


	GtkWidget *table = gtk_table_new (11, 10, TRUE);
	label = gtk_label_new("Create User");
	gtk_table_set_row_spacings(GTK_TABLE (table), 5);
	gtk_table_set_col_spacings(GTK_TABLE (table), 5); 
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), table, label);
	
	
	
	
	
	
	
	GtkWidget *r_table = gtk_table_new (11, 10, TRUE);
	label = gtk_label_new("Create Room");
	gtk_table_set_row_spacings(GTK_TABLE (r_table), 5);
	gtk_table_set_col_spacings(GTK_TABLE (r_table), 5); 
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), r_table, label);
	
	
	gtk_entry_set_max_length (GTK_ENTRY (room_name), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (room_name), "");
    gtk_editable_select_region (GTK_EDITABLE (room_name),
			        0, GTK_ENTRY (room_name)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (r_table), room_name, 2, 8, 4, 6); 
    gtk_widget_show (room_name);
	
	gtk_table_attach_defaults(GTK_TABLE(r_table), text_r_name, 2, 8, 3, 4);
	
	g_signal_connect (r_cancel, "clicked",
          G_CALLBACK (close_window), G_OBJECT(window));
	g_signal_connect (r_confrim, "clicked",
          G_CALLBACK (create_room_process), entrys);
		  
	gtk_table_attach_defaults(GTK_TABLE(r_table), r_confrim, 1, 5, 7, 11);
	gtk_table_attach_defaults(GTK_TABLE(r_table), r_cancel, 5, 9, 7, 11);
	
	
	
	
	
	
	gtk_entry_set_max_length (GTK_ENTRY (user_name), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (user_name), "");
    gtk_editable_select_region (GTK_EDITABLE (user_name),
			        0, GTK_ENTRY (user_name)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (table), user_name, 2, 8, 2, 3); 
    gtk_widget_show (user_name);
	
	
	gtk_entry_set_max_length (GTK_ENTRY (user_pass), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (user_pass), "");
    //tmp_pos = GTK_ENTRY (server_port)->text_length;
   // gtk_editable_insert_text (GTK_EDITABLE (server_port), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (user_pass),
			        0, GTK_ENTRY (user_pass)->text_length);
					
	gtk_entry_set_visibility (GTK_ENTRY(user_pass), FALSE);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (table), user_pass, 2, 8, 4, 5); 
    gtk_widget_show (user_pass);
	
	gtk_entry_set_max_length (GTK_ENTRY (user_pass_confirm), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (user_pass_confirm), "");
    //tmp_pos = GTK_ENTRY (server_port)->text_length;
   // gtk_editable_insert_text (GTK_EDITABLE (server_port), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (user_pass_confirm),
			        0, GTK_ENTRY (user_pass_confirm)->text_length);
					
	gtk_entry_set_visibility (GTK_ENTRY(user_pass_confirm), FALSE);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (table), user_pass_confirm, 2, 8, 6, 7); 
    gtk_widget_show (user_pass_confirm);
	
	gtk_table_attach_defaults(GTK_TABLE(table), text_user_name, 2, 8, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), text_user_pass, 2, 8, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(table), text_user_pass_confirm, 2, 8, 5, 6);
	
	g_signal_connect (save_using, "clicked",
          G_CALLBACK (create_user_process_with_login), entrys);
	g_signal_connect (save_only, "clicked",
          G_CALLBACK (create_user_process_without_login), entrys);
		  
	g_signal_connect (cancel, "clicked",
          G_CALLBACK (close_window), G_OBJECT(window));
	
	
	gtk_table_attach_defaults(GTK_TABLE(table), save_using, 1, 5, 7, 11);
	gtk_table_attach_defaults(GTK_TABLE(table), save_only, 5, 9, 7, 9);
	gtk_table_attach_defaults(GTK_TABLE(table), cancel, 5, 9, 9, 11);
	
	
	gtk_widget_show_all (window);
	gtk_widget_grab_focus (window);
	
	



}
void send_message_process(GtkWidget *widget, gpointer window){
	if(!strcmp(CURRENT_ROOM,"Lobby")){
		return;
	}
	stop_loop();
	GtkTextIter startIter;
	GtkTextIter endIter;
	gtk_text_buffer_get_start_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_INPUT_BOX)), &startIter);
	gtk_text_buffer_get_end_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_INPUT_BOX)), &endIter);
	char r[20*1024+5];
	char * msg = gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_INPUT_BOX)),&startIter,&endIter,FALSE);
	send_message(SERVER_ADDRESS,SERVER_PORT,USER_NAME,USER_PASS,CURRENT_ROOM,msg,&RESPONSE);
	//sprintf(r, "%s: %s\n", USER_NAME, msg);
	//insert_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_MEG_BOX))),(const char*) r);
	//MESSAGE_LINE ++;
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(MAIN_INPUT_BOX))),strdup(""),-1);
	updata_message(NULL,NULL);
	start_loop();
}
gboolean on_popup_out (GtkWidget *widget, GdkEventFocus *event, gpointer data) {
  gtk_widget_destroy (widget);
  start_loop();
  return TRUE;
}


void static startup_in(GtkWidget * main_window){
		
	
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *server_add = gtk_entry_new ();
	GtkWidget *server_port = gtk_spin_button_new_with_range (1,65535,1);
	GtkWidget *user_name = gtk_entry_new ();
	GtkWidget *user_pass = gtk_entry_new ();
	GtkWidget *confirm =  gtk_button_new_with_label ("Confirm");
	GtkWidget *cancel = gtk_button_new_with_label ("Close");
	GtkWidget *confirm_user =  gtk_button_new_with_label ("Confirm");
	GtkWidget *cancel_user = gtk_button_new_with_label ("Close");
	
	//GtkWidget ** entryArray = (GtkWidget **) malloc(sizeof(GtkWidget *) * 4);
	//Array Storing data of Entry Widgets
	
	EntryArray * entrys = (EntryArray *) malloc (sizeof(EntryArray));
	entrys->u_name = user_name;
	entrys->u_pass = user_pass;
	entrys->s_add = server_add;
	entrys->s_port = server_port;
	entrys->window = window;
	entrys->main_window = main_window;
	
	GtkWidget *text_server_add = gtk_accel_label_new ("Server Address:");
	GtkWidget *text_server_port = gtk_accel_label_new ("Server Port:");
	GtkWidget *text_user_name = gtk_accel_label_new ("User name:");
	GtkWidget *text_user_pass = gtk_accel_label_new ("Password:");
	
	
	//stop_loop(); // Stop Updating Room and User
	//Initialize window
	gtk_window_set_title (GTK_WINDOW (window), "Welcome to IRCClient");
	g_signal_connect (window, "destroy",
                G_CALLBACK (start_up_close), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (GTK_WIDGET (window), 400, 300);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_decorated (GTK_WINDOW (window), TRUE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_skip_pager_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	
	
	
	
	//Initialize Base Table
	GtkWidget *base = gtk_table_new (10, 10, TRUE);
	gtk_container_add (GTK_CONTAINER (window), base);
	gtk_table_set_row_spacings(GTK_TABLE (base), 5);
	gtk_table_set_col_spacings(GTK_TABLE (base), 5); 
	
	
	
	
	//Initialize Notebook
	GtkWidget * notebook = gtk_notebook_new();
	GtkWidget * frame;
	GtkWidget * label;
	GtkWidget * label_Server;
	// char bufferf[32];
	// char bufferl[32];
	
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook),GTK_POS_TOP);
	//gtk_container_add (GTK_CONTAINER (window), notebook);
	gtk_table_attach_defaults(GTK_TABLE (base), notebook, 0, 11, 0, 11); 
	gtk_notebook_set_show_border(GTK_NOTEBOOK(notebook), FALSE);
	
	 // for (int i=0; i < 2; i++) {
        // sprintf(bufferf, "Append Frame %d", i+1);
        // sprintf(bufferl, "Page %d", i+1);
        
        // frame = gtk_frame_new (bufferf);
        // gtk_container_border_width (GTK_CONTAINER (frame), 10);
        // gtk_widget_set_usize (frame, 100, 75);
        // gtk_widget_show (frame);
        
        // label = gtk_label_new (bufferf);
        // gtk_container_add (GTK_CONTAINER (frame), label);
        // gtk_widget_show (label);
        
       // label = gtk_label_new (bufferl);
       // gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
    //
	//                                                                                Server Info Page
	GtkWidget *server_table = gtk_table_new (10, 10, TRUE);
	label_Server = gtk_label_new("Server");
	//gtk_container_add (GTK_CONTAINER (window), server_table);
	gtk_table_set_row_spacings(GTK_TABLE (server_table), 5);
	gtk_table_set_col_spacings(GTK_TABLE (server_table), 5); 

	
	
	//Server Address Entry
	gtk_entry_set_max_length (GTK_ENTRY (server_add), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (server_add), SERVER_ADDRESS);
    gtk_editable_select_region (GTK_EDITABLE (server_add),
			        0, GTK_ENTRY (server_add)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (server_table), server_add, 2, 8, 3, 4); 
    gtk_widget_show (server_add);
	
	
	//Server Port Entry
	//	gtk_entry_set_max_length (GTK_ENTRY (server_port), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
   // gtk_entry_set_text (GTK_ENTRY (server_port), SERVER_PORT);
    //tmp_pos = GTK_ENTRY (server_port)->text_length;
   // gtk_editable_insert_text (GTK_EDITABLE (server_port), " world", -1, &tmp_pos);
    //gtk_editable_select_region (GTK_EDITABLE (server_port),
	//		        0, GTK_ENTRY (server_port)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(server_port) , SERVER_PORT);
	gtk_table_attach_defaults(GTK_TABLE (server_table), server_port, 2, 8, 5, 7); 
    gtk_widget_show (server_port);
	
	//Lable of Server Entry
	gtk_table_attach_defaults(GTK_TABLE(server_table), text_server_add, 2, 8, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(server_table), text_server_port, 2, 8, 4, 5);
	
	//Button of Server Entry
	g_signal_connect (confirm, "clicked",
          G_CALLBACK (save_settings), entrys);
		  
	g_signal_connect (cancel, "clicked",
          G_CALLBACK (gtk_main_quit), G_OBJECT(window));
	gtk_table_attach_defaults(GTK_TABLE(server_table), confirm, 2, 5, 7, 9);
	gtk_table_attach_defaults(GTK_TABLE(server_table), cancel, 5, 8, 7, 9);
	
	
	
	
	
	
	
	
	
	
	
	//                                                                               User Info Page 
	GtkWidget *user_table = gtk_table_new (10, 10, TRUE);
	label = gtk_label_new("User");
	//gtk_container_add (GTK_CONTAINER (window), user_table);
	gtk_table_set_row_spacings(GTK_TABLE (user_table), 5);
	gtk_table_set_col_spacings(GTK_TABLE (user_table), 5); 
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), user_table, label);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), server_table, label_Server);
	gtk_entry_set_max_length (GTK_ENTRY (user_name), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (user_name), USER_NAME);
    gtk_editable_select_region (GTK_EDITABLE (user_name),
			        0, GTK_ENTRY (user_name)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (user_table), user_name, 2, 8, 3, 4); 
    gtk_widget_show (user_name);
	
	//User Password Entry
		gtk_entry_set_max_length (GTK_ENTRY (user_pass), 50);
/*     g_signal_connect (server_add, "activate",
		      G_CALLBACK (enter_callback),
		      server_add); */
    gtk_entry_set_text (GTK_ENTRY (user_pass), USER_PASS);
    //tmp_pos = GTK_ENTRY (server_port)->text_length;
   // gtk_editable_insert_text (GTK_EDITABLE (server_port), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (user_pass),
			        0, GTK_ENTRY (user_pass)->text_length);
					
	gtk_entry_set_visibility (GTK_ENTRY(user_pass), FALSE);
    //gtk_box_pack_start (GTK_BOX (vbox), server_add, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE (user_table), user_pass, 2, 8, 5, 6); 
    gtk_widget_show (user_pass);
	
	//Lable of Server Entry
	gtk_table_attach_defaults(GTK_TABLE(user_table), text_user_name, 2, 8, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(user_table), text_user_pass, 2, 8, 4, 5);
	
	//Button of Server Entry
	g_signal_connect (confirm_user, "clicked",
          G_CALLBACK (save_settings), entrys);
	g_signal_connect (cancel_user, "clicked",
          G_CALLBACK (gtk_main_quit), G_OBJECT(window));
		  
	gtk_table_attach_defaults(GTK_TABLE(user_table), confirm_user, 2, 5, 7, 9);
	gtk_table_attach_defaults(GTK_TABLE(user_table), cancel_user, 5, 8, 7, 9);
	
	
	
	
	
	
	
	
	
	gtk_widget_show_all (window);
	gtk_widget_grab_focus (window);
	
	
	
	
	
}
int main( int   argc, char *argv[] ) {
	
    GtkWidget *window;
    GtkWidget *list;
    GtkWidget *users;
    GtkWidget *messages;
    GtkWidget *myMessage;
	
	SelectArray * selectArray = (SelectArray *) malloc(sizeof(SelectArray));
	
    gtk_init (&argc, &argv);
   
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "IRC Client");
    g_signal_connect (window, "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 600, 500);

    // Create a table to place the widgets. Use a 7x4 Grid (7 rows x 4 columns)
    GtkWidget *table = gtk_table_new (10, 11, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    gtk_table_set_row_spacings(GTK_TABLE (table), 5);
    gtk_table_set_col_spacings(GTK_TABLE (table), 5);
    gtk_widget_show (table);

    // Add list of rooms. Use columns 0 to 4 (exclusive) and rows 0 to 4 (exclusive)
    list_rooms = gtk_list_store_new (1, G_TYPE_STRING);
    //update_list_rooms(NULL,NULL);
    list = create_list ("Rooms", list_rooms, 1);
    gtk_table_attach_defaults (GTK_TABLE (table), list, 0, 4, 3, 8);
    gtk_widget_show (list);
	g_signal_connect(GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(MAIN_ROOM_LIST))), "changed", 
		G_CALLBACK(on_room_select_change), NULL);


    //Users
    
	list_users = gtk_list_store_new (1, G_TYPE_STRING);
    //update_list_users(NULL,NULL);
    users = create_list ("Users", list_users, 2);
    gtk_table_attach_defaults (GTK_TABLE (table), users, 0, 4, 0, 3);
    gtk_widget_show (users);
   


    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive) 
    messages = create_text ("" , 1);
    gtk_table_attach_defaults (GTK_TABLE (table), messages, 4, 11, 0, 6);
    gtk_widget_show (messages);
	gtk_text_view_set_editable (GTK_TEXT_VIEW(MAIN_MEG_BOX),FALSE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(MAIN_MEG_BOX),FALSE);




    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive) 

    myMessage = create_text ("", 2);
    gtk_table_attach_defaults (GTK_TABLE (table), myMessage, 4, 11, 6, 9);
    gtk_widget_show (myMessage);

    //Enter-room
    GtkWidget *enter_room_button = gtk_button_new_with_label ("Enter Room");
    gtk_table_attach_defaults(GTK_TABLE (table), enter_room_button, 0, 2, 8, 9); 
    gtk_widget_show (enter_room_button);
	g_signal_connect (enter_room_button, "clicked",
          G_CALLBACK (enter_room_process), selectArray);

    //Leave-room
	
	selectArray->u = users;
	selectArray->r = list;
    GtkWidget *leave_room_button = gtk_button_new_with_label ("Leave Room");
    gtk_table_attach_defaults(GTK_TABLE (table), leave_room_button, 2, 4, 8, 9); 
    gtk_widget_show (leave_room_button);
	g_signal_connect (leave_room_button, "clicked",
          G_CALLBACK (leave_room_process), selectArray);


    //Create-user
    GtkWidget *create_user_button = gtk_button_new_with_label ("Create");
    gtk_table_attach_defaults(GTK_TABLE (table), create_user_button, 0, 2, 9, 10); 
    gtk_widget_show (create_user_button);    
    g_signal_connect (create_user_button, "clicked",
          G_CALLBACK (create_user), NULL);




    //Change-user
    GtkWidget *change_user_button = gtk_button_new_with_label ("Setup");
    gtk_table_attach_defaults(GTK_TABLE (table), change_user_button, 2, 4, 9, 10); 
    gtk_widget_show (change_user_button);
    g_signal_connect (change_user_button, "clicked",
          G_CALLBACK (setup), NULL);






    // Add send button. Use columns 0 to 1 (exclusive) and rows 4 to 7 (exclusive)
    GtkWidget *send_button = gtk_button_new_with_label ("Send");
    gtk_table_attach_defaults(GTK_TABLE (table), send_button, 8, 11, 9, 10); 
    gtk_widget_show (send_button);
    g_signal_connect (send_button, "clicked",
          G_CALLBACK (send_message_process), NULL);
	
    
    gtk_widget_show (table);
	startup_in(window);
	

    gtk_main ();

    return 0;
}

