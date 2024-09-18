#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

// Widgets for main window
GtkWidget *window, *fixed, *button1, *button2, *button3, *button4, *image;

// Widgets for add_schedule
GtkWidget *new_window1,*image1 ,*label1, *label2, *entry1,*entry2, *submit_button,*fixed1;

//widget for file_opener
int act_count;
char filename[1000];
GtkWidget *scrolled_window,*fixed2;
GtkWidget *array1[1000];
GtkWidget *array2[1000];
GtkWidget *array3[1000];
GtkWidget *array4[1000];
GtkWidget *array5[1000];
GtkWidget *array6[1000];
GtkWidget *array7[1000];
GtkWidget *array8[1000];
GtkWidget *array9[1000];
GtkWidget *label3, *label4, *label5, *label6, *label7;
GtkWidget *entry3, *entry4, *combo1;
GtkWidget *submit_button1;

//widget for input_receiver
GtkWidget *label8;

//Widget for print_full_schedule
GtkWidget *new_window2,*image2, *label9, *entry5, *scrolled_window1,*fixed3,*submit_button2 ;

//widget for full print
GtkWidget *label10;

//widget for show_activity
GtkWidget *new_window3, *image3, *label11, *entry6, *label12, *label13, *entry7, *label14, *entry8, *label15, *combo2, *submit_button3, *fixed4 ;

//widget for print_specific
GtkWidget *label16;

char* minute_to_IMp(int time) {     //return time in I:M p format 
    static char ftime[200]; 
    char M1[10] ;
    int hour1, minute1;

    
    hour1 = time / 60;
    minute1 = time- hour1*60;

    
    if (hour1 >= 12) {
        strcpy(M1, "PM"); 
        if (hour1 > 12) {
            hour1 -= 12;  
        }
    }
    else {
        strcpy(M1,"AM");
    }
    
    
    if (hour1 == 0) {
        hour1 = 12; 
    }

    sprintf(ftime, "%d:%02d %s", hour1, minute1, M1); 

    return ftime; 
}

int IMp_to_minute(int hour, int minute, int am_pm) {  //returns minutes from midnight (12:00AM)
    int total_times = 0;
    
    if (am_pm == 1 && hour != 12) { 
        hour += 12;
    }
    if (am_pm == 0 && hour == 12) {   
        hour = 0;
    }
  
    total_times = hour * 60 + minute;

    return total_times;
}

void full_print(){
char temp[1000][1000];
char temp3[1000000];
strcpy(temp3,"Full schedule :\n");
const char *user_name=gtk_entry_get_text(GTK_ENTRY(entry5));
char filename[100];
strcpy(filename,user_name);
strcat(filename,".txt");

FILE*file=fopen(filename,"r");

if(file){
int i=0;
while(fgets(temp[i],1000,file)){
    i++;
}

for(int j=0;j<i-1;j++){
if(j%2==0){  //time
char *s_time=minute_to_IMp(atoi(temp[j]));
strcat(temp3,s_time);
strcat(temp3," -> ");
char *end_time=minute_to_IMp(atoi(temp[j+2])-1);
strcat(temp3,end_time);
strcat(temp3,"  :  ");
}
else{  //activity
strcat(temp3,temp[j]);
}
}
label10=gtk_label_new(temp3);
}


else {
label10=gtk_label_new("No schedule is found ");
}
gtk_container_remove(GTK_CONTAINER(fixed3), submit_button2);
gtk_container_remove(GTK_CONTAINER(fixed3), label9);
gtk_container_remove(GTK_CONTAINER(fixed3), entry5);
gtk_container_add(GTK_CONTAINER(scrolled_window1),label10);

gtk_widget_show_all(new_window2);
}

void print_specific(){
char temp[1000][1000];
char temp3[1000];

const char *user_name=gtk_entry_get_text(GTK_ENTRY(entry6));

const char *hour_text=gtk_entry_get_text(GTK_ENTRY(entry7));
const char *minute_text=gtk_entry_get_text(GTK_ENTRY(entry8));
int AmPm=gtk_combo_box_get_active(GTK_COMBO_BOX(combo2));

int time=IMp_to_minute(atoi(hour_text),atoi(minute_text),AmPm);

char filename[100];
strcpy(filename,user_name);
strcat(filename,".txt");

FILE*file=fopen(filename,"r");
if(file){
int i=0;
while(fgets(temp[i],1000,file)){
    i++;
}

bool found=false;
char activity[1000];
strcpy(activity,"Activity : ");

for(int j=0;j<i-2;j=j+2){
if(atoi(temp[j])<=time && time<atoi(temp[j+2])){
strcat(activity,temp[j+1]);
found=true;
break;
}
}
if(found==false){
strcat(activity,"not available");
}

label16=gtk_label_new(activity);
}

else{
label16=gtk_label_new("No schedule is found");
}

gtk_container_remove(GTK_CONTAINER(fixed4), submit_button3);
gtk_container_remove(GTK_CONTAINER(fixed4), label11);
gtk_container_remove(GTK_CONTAINER(fixed4), label12);
gtk_container_remove(GTK_CONTAINER(fixed4), label13);
gtk_container_remove(GTK_CONTAINER(fixed4), label14);
gtk_container_remove(GTK_CONTAINER(fixed4), label15);
gtk_container_remove(GTK_CONTAINER(fixed4), entry6);
gtk_container_remove(GTK_CONTAINER(fixed4), entry7);
gtk_container_remove(GTK_CONTAINER(fixed4), entry8);
gtk_container_remove(GTK_CONTAINER(fixed4), combo2);

gtk_fixed_put(GTK_FIXED(fixed4),label16,150,350);

gtk_widget_show_all(new_window3);
}

void input_receiver(){
int hour;
int min;
int AmPm;
int total_time;


FILE *insert=fopen(filename,"w");

for(int i=0;i<act_count;i++){

const char *hour_text=gtk_entry_get_text(GTK_ENTRY(array3[i]));
hour=atoi(hour_text);

const char *min_text=gtk_entry_get_text(GTK_ENTRY(array5[i]));
min=atoi(min_text);

AmPm=gtk_combo_box_get_active(GTK_COMBO_BOX(array7[i]));

total_time=IMp_to_minute(hour,min,AmPm);

fprintf(insert,"%d\n",total_time);

const char *activity=gtk_entry_get_text(GTK_ENTRY(array9[i]));

fprintf(insert,"%s\n",activity);


}

const char *hour_text=gtk_entry_get_text(GTK_ENTRY(entry3));
hour=atoi(hour_text);

const char *min_text=gtk_entry_get_text(GTK_ENTRY(entry4));
min=atoi(min_text)+1;

AmPm=gtk_combo_box_get_active(GTK_COMBO_BOX(combo1));

total_time=IMp_to_minute(hour,min,AmPm);

fprintf(insert,"%d\n",total_time);

fclose(insert);

gtk_container_remove(GTK_CONTAINER(scrolled_window), fixed2);

 label8 = gtk_label_new("Schedule is added successfully");
 gtk_fixed_put(GTK_FIXED(fixed1), label8, 180, 15);
 gtk_widget_show_all(new_window1);

}

void file_opener() {

    const char *act_count_str = gtk_entry_get_text(GTK_ENTRY(entry2));  
    act_count = atoi(act_count_str);  

    const char *user_name = gtk_entry_get_text(GTK_ENTRY(entry1));
    
    snprintf(filename, sizeof(filename), "%s.txt", user_name);

    FILE *file = fopen(filename, "r");

    if (file) {
        fclose(file);
            label7 = gtk_label_new("A schedule already exists with the same name.");
            gtk_fixed_put(GTK_FIXED(fixed1), label7, 150, 220);
    } 
    
    else {

        scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_size_request(scrolled_window, 600, 650);
        gtk_fixed_put(GTK_FIXED(fixed1), scrolled_window, 0,0);
        fixed2 = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(scrolled_window), fixed2);
        
        int x = 135;
        int y = 10;
        for (int i = 0; i < act_count; i++) {
            char arr[1000];
            sprintf(arr, "Enter starting time of activity no. %d:", i + 1);
            array1[i] = gtk_label_new(arr);
            array2[i] = gtk_label_new("Enter hour:");
            array3[i] = gtk_entry_new();
            array4[i] = gtk_label_new("Enter minute:");
            array5[i] = gtk_entry_new();
            array6[i] = gtk_label_new("Select AM/PM:");
            array7[i] = gtk_combo_box_text_new();
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(array7[i]), "AM");
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(array7[i]), "PM");
            array8[i] = gtk_label_new("Enter activity:");
            array9[i] = gtk_entry_new();

            gtk_fixed_put(GTK_FIXED(fixed2), array1[i], x, y);
            gtk_fixed_put(GTK_FIXED(fixed2), array2[i], x, y + 50);
            gtk_fixed_put(GTK_FIXED(fixed2), array3[i], x + 190, y + 50);
            gtk_fixed_put(GTK_FIXED(fixed2), array4[i], x, y + 100);
            gtk_fixed_put(GTK_FIXED(fixed2), array5[i], x + 190, y + 100);
            gtk_fixed_put(GTK_FIXED(fixed2), array6[i], x, y + 150);
            gtk_fixed_put(GTK_FIXED(fixed2), array7[i], x + 190, y + 150);
            gtk_fixed_put(GTK_FIXED(fixed2), array8[i], x, y + 200);
            gtk_fixed_put(GTK_FIXED(fixed2), array9[i], x + 190, y + 200);

            y += 250;
        }

        label3 = gtk_label_new("Enter the end time:");
        label4 = gtk_label_new("Enter hour:");
        entry3 = gtk_entry_new();
        label5 = gtk_label_new("Enter minute:");
        entry4 = gtk_entry_new();
        label6 = gtk_label_new("Select AM/PM:");
        combo1 = gtk_combo_box_text_new();
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo1), "AM");
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo1), "PM");
        submit_button1 = gtk_button_new_with_label("Submit");

        gtk_fixed_put(GTK_FIXED(fixed2), label3, x, y);
        gtk_fixed_put(GTK_FIXED(fixed2), label4, x, y + 50);
        gtk_fixed_put(GTK_FIXED(fixed2), entry3, x + 190, y + 50);
        gtk_fixed_put(GTK_FIXED(fixed2), label5, x, y + 100);
        gtk_fixed_put(GTK_FIXED(fixed2), entry4, x + 190, y + 100);
        gtk_fixed_put(GTK_FIXED(fixed2), label6, x, y + 150);
        gtk_fixed_put(GTK_FIXED(fixed2), combo1, x + 190, y + 150);
        gtk_fixed_put(GTK_FIXED(fixed2), submit_button1, 250, y + 200);
        
        g_signal_connect(submit_button1, "clicked", G_CALLBACK(input_receiver), NULL);

        
    }
    gtk_container_remove(GTK_CONTAINER(fixed1), submit_button);
    gtk_container_remove(GTK_CONTAINER(fixed1), label1);
    gtk_container_remove(GTK_CONTAINER(fixed1), label2);
    gtk_container_remove(GTK_CONTAINER(fixed1), entry1);
    gtk_container_remove(GTK_CONTAINER(fixed1), entry2);
    
    gtk_widget_show_all(new_window1);
}

void on_about() {
    GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window), "About Us");
    gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 700);
    gtk_window_set_resizable(GTK_WINDOW(new_window), FALSE);
    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    GtkWidget *image = gtk_image_new_from_file("bg2.jpeg");
    GtkWidget *fixed = gtk_fixed_new();
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<a href=\"https://github.com/kamrulhasantanbir/scheduler-with-GUI\">Rate us</a>");
    
    gtk_container_add(GTK_CONTAINER(new_window), fixed);
    
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), label, 175, 665);
    
    gtk_widget_show_all(new_window);
}

void show_activity() {
    new_window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window3), "Show Activity (Specific Time)");
    gtk_window_set_default_size(GTK_WINDOW(new_window3), 600, 700);
    gtk_window_set_resizable(GTK_WINDOW(new_window3), FALSE);
    g_signal_connect(new_window3, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
    
    image3 = gtk_image_new_from_file("bg1.jpeg");
    label11 = gtk_label_new("Enter name here: ");
    entry6 = gtk_entry_new();
    label12 = gtk_label_new("Enter time here: ");
    label13 = gtk_label_new("Enter hour:");
    entry7 = gtk_entry_new();
    label14 = gtk_label_new("Enter minute:");
    entry8 = gtk_entry_new();
    label15 = gtk_label_new("Select AM/PM:");
    combo2 = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), "AM");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), "PM");

    submit_button3 = gtk_button_new_with_label("Submit");

    fixed4 = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(new_window3), fixed4);

    gtk_fixed_put(GTK_FIXED(fixed4), image3, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed4), label11, 100, 50);
    gtk_fixed_put(GTK_FIXED(fixed4), entry6, 300, 50);
    gtk_fixed_put(GTK_FIXED(fixed4), label12, 100, 100);
    gtk_fixed_put(GTK_FIXED(fixed4), label13, 100, 150);
    gtk_fixed_put(GTK_FIXED(fixed4), entry7, 300, 150);
    gtk_fixed_put(GTK_FIXED(fixed4), label14, 100, 200);
    gtk_fixed_put(GTK_FIXED(fixed4), entry8, 300, 200);
    gtk_fixed_put(GTK_FIXED(fixed4), label15, 100, 250);
    gtk_fixed_put(GTK_FIXED(fixed4), combo2, 300, 250);
    gtk_fixed_put(GTK_FIXED(fixed4), submit_button3, 250, 300);
    
    g_signal_connect(submit_button3,"clicked",G_CALLBACK(print_specific),NULL);

    gtk_widget_show_all(new_window3);
}

void print_full_schedule() {
    new_window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window2), "Print full schedule");
    gtk_window_set_default_size(GTK_WINDOW(new_window2), 600, 700);
    gtk_window_set_resizable(GTK_WINDOW(new_window2), FALSE);
    g_signal_connect(new_window2, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    image2 = gtk_image_new_from_file("bg1.jpeg");
    label9 = gtk_label_new("Enter name here : ");
    entry5 = gtk_entry_new();
    submit_button2 = gtk_button_new_with_label("Submit");

    fixed3 = gtk_fixed_new();
    scrolled_window1=gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window1, 600, 550);
    
    gtk_container_add(GTK_CONTAINER(new_window2), fixed3);
    

    gtk_fixed_put(GTK_FIXED(fixed3), image2, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed3), label9, 100, 50);
    gtk_fixed_put(GTK_FIXED(fixed3), entry5, 300, 50);
    gtk_fixed_put(GTK_FIXED(fixed3), submit_button2, 250, 100);
    gtk_fixed_put(GTK_FIXED(fixed3), scrolled_window1, 0, 150);
    
    
    g_signal_connect(submit_button2,"clicked",G_CALLBACK(full_print),NULL);

    gtk_widget_show_all(new_window2);
}

void add_schedule() {
    new_window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window1), "Add Schedule");
    gtk_window_set_default_size(GTK_WINDOW(new_window1), 600, 700);
    gtk_window_set_resizable(GTK_WINDOW(new_window1), FALSE);
    g_signal_connect(new_window1, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    image1 = gtk_image_new_from_file("bg1.jpeg");

    label1 = gtk_label_new("Enter your name here: ");
    entry1 = gtk_entry_new();

    label2 = gtk_label_new("Enter the number of activities: ");
    entry2 = gtk_entry_new();

    submit_button = gtk_button_new_with_label("Submit");

    fixed1 = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(new_window1), fixed1);
    
    gtk_fixed_put(GTK_FIXED(fixed1), image1, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed1), label1, 100, 20);
    gtk_fixed_put(GTK_FIXED(fixed1), entry1, 350, 20);
    gtk_fixed_put(GTK_FIXED(fixed1), label2, 100, 65);
    gtk_fixed_put(GTK_FIXED(fixed1), entry2, 350, 65);
    gtk_fixed_put(GTK_FIXED(fixed1), submit_button, 240, 110);
    
    g_signal_connect(submit_button, "clicked", G_CALLBACK(file_opener), NULL);

    gtk_widget_show_all(new_window1);
}

int main() {
    gtk_init(NULL, NULL);

    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scheduler");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 700);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create buttons and place them in the fixed layout
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    button1 = gtk_button_new_with_label("Add Schedule");
    button2 = gtk_button_new_with_label("Print full schedule");
    button3 = gtk_button_new_with_label("Show Activity (specific time)");
    button4 = gtk_button_new_with_label("About Us");

    image = gtk_image_new_from_file("bg3.jpeg");
    
    gtk_widget_set_size_request(button1, 230, 40);
    gtk_widget_set_size_request(button2, 230, 40);
    gtk_widget_set_size_request(button3, 230, 40);
    gtk_widget_set_size_request(button4, 230, 40);
    
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 185, 400);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 185, 450);
    gtk_fixed_put(GTK_FIXED(fixed), button3, 185, 500);
    gtk_fixed_put(GTK_FIXED(fixed), button4, 185, 550);

    g_signal_connect(button1, "clicked", G_CALLBACK(add_schedule),        NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(print_full_schedule), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(show_activity),       NULL);
    g_signal_connect(button4, "clicked", G_CALLBACK(on_about),            NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
