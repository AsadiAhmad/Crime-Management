//define librarys
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

// define structs
struct people{
    char user_name_of_people[20];
    char password_of_people[20];
    char national_code_of_people[20];
    int num_of_people;
};
struct viewer{
    char user_name_of_viewer[20];
    char password_of_viewer[20];
    char national_code_of_viewer[20];
    int num_of_viewer;
};
struct legal{
    char user_name_of_legal[20];
    char password_of_legal[20];
    char national_code_of_legal[20];
    int num_of_legal;
}; 
struct report{
    char Title[30];
    char Discription[530];
    char PlaceOfcrime[40];
    char NationalCode[10];
    char year[5];
    char mounth[3];
    char day[3];
    char hour[3];
    char minute[3];
    char second[3];
    char user_name[20];
    int num_of_report;
};
struct IsDeleted{
    char user_name[20];
    int ReportCode;
    int is_deleted;
    int num;
};
struct ImportantReport{
    char user_name[20];
    int ReportCode;
    int important_report;
    int num_of_important;
};
struct IsBlock{
    char user_name[20];
    char space[3];
    int num_of_user;
    int is_block;
};
struct Money{
    char user_name[20];
    char space[3];
    int num_of_user;
    int money;
};
struct Reception{
    char reason[160];
    char user_name[20];
    char space[3];
    int num_of_reception;
    int ReportCode;
    int status;
    char year[5];
    char mounth[3];
    char day[3];
    char hour[3];
    char minute[3];
    char second[3];
};
struct window{
    WINDOW *main_page;
    WINDOW *people_section_win;
    WINDOW *viewer_section_win;
    WINDOW *legal_section_win;
    WINDOW *about_win;
    WINDOW *sgin_in_win_for_people;
    WINDOW *log_in_win_for_people;
    WINDOW *sgin_in_win_for_viewer;
    WINDOW *log_in_win_for_viewer;
    WINDOW *sgin_in_win_for_legal;
    WINDOW *log_in_win_for_legal;
    WINDOW *people_menu_win;
    WINDOW *cardboard_for_viewer_win;
    WINDOW *legal_menu_win;
    WINDOW *cardboard_for_people_win;
    WINDOW *report_new_crime_win;
    WINDOW *arrange_list_win;
    WINDOW *edit_report_win;
    WINDOW *delete_report_win;
    WINDOW *show_related_reports_win;
    WINDOW *important_reports_win;
    WINDOW *buy_VIP_win;
    WINDOW *Inbox_for_people_win;
    WINDOW *History_for_people_win;
    WINDOW *Inbox_for_viewer_win;
    WINDOW *History_for_viewer_win;
    WINDOW *cardboard_for_legal_win;
    WINDOW *block_reporters_win;
    WINDOW *encourage_reporters_win;
    WINDOW *Inbox_for_legal_win;
    WINDOW *History_for_legal_win;
}; 
int counter_of_exist_report_for_delete (void);   
int is_report_deleted (int report_code_for_read); 
int get_report_code_for_delete (int num_of_nth_report); 
int which_num_is_for_report_code (int report_code_for_read);
void delete_reports (int num_of_nth_report);
int counter_num_of_block (void); 
void saving_is_blocked (char *user_name_save); 
int counter_num_of_encourage (void);
void saving_money (char *user_name_save);
int is_people_blocked (char *user_name_save);
int is_report_answered (int report_code_for_read);
void read_report_from_file_for_Inbox_people (int num, char *Title, char *year, char *mounth, char *day,
char *hour, char *minute, char *second);
int check_shell_window (void){
    int max_x_shell = 0, max_y_shell = 0;
    getmaxyx (stdscr, max_y_shell, max_x_shell);
    if (max_x_shell < 60 || max_y_shell < 25){
        mvprintw (max_y_shell / 2, (max_x_shell / 2) - 12, "bigger shell needed !");
        getch();
        return 0;
    }
    return 1;
}
void clu (int* x_start, int* y_start){
    int max_x_shell = 0, max_y_shell = 0;
    getmaxyx (stdscr, max_y_shell, max_x_shell); 
    if (max_x_shell % 2 == 0){
        *x_start = (max_x_shell - 60)/2;
    } 
    else {
        *x_start = (max_x_shell - 61)/2;        
    }
    if (max_y_shell % 2 == 0){
        *y_start = (max_y_shell - 26)/2;
    }
    else {
        *y_start = (max_y_shell - 25)/2;
    }
}
// this function create main page by cluing size of page where to start !
void create_main_page (WINDOW *main_page){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    main_page = newwin (25, 60, y_start, x_start);
    refresh();
    box (main_page, 0, 0);
    wrefresh (main_page);
}
void print_in_main_page_state_1 (int y_start,int x_start){
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 9 ,x_start + 19," 1-People section ");
    attroff (COLOR_PAIR (2));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 11,x_start + 19," 2-Viewer section ");
    mvprintw (y_start + 13,x_start + 19," 3-Legal section  ");
    mvprintw (y_start + 15,x_start + 19,"      4-About     ");
    mvprintw (y_start + 17,x_start + 19,"      5-Exit      ");
    attroff (COLOR_PAIR (1));
}
void print_in_main_page_state_2 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 9 ,x_start + 19," 1-People section ");
    mvprintw (y_start + 13,x_start + 19," 3-Legal section  ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 11,x_start + 19," 2-Viewer section ");
    attroff (COLOR_PAIR (2));
}
void print_in_main_page_state_3 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 11,x_start + 19," 2-Viewer section ");
    mvprintw (y_start + 15,x_start + 19,"      4-About     ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 13,x_start + 19," 3-Legal section  ");
    attroff (COLOR_PAIR (2));
}
void print_in_main_page_state_4 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 17,x_start + 19,"      5-Exit      ");
    mvprintw (y_start + 13,x_start + 19," 3-Legal section  ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 15,x_start + 19,"      4-About     ");
    attroff (COLOR_PAIR (2));
}
void print_in_main_page_state_5 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 9 ,x_start + 19," 1-People section ");
    mvprintw (y_start + 15,x_start + 19,"      4-About     ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 17,x_start + 19,"      5-Exit      ");
    attroff (COLOR_PAIR (2));
}
void printer_for_main_page (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 4,x_start + 8,"wellcom to the criminal management program !");  
    mvprintw (y_start + 6,x_start + 8,"please select a option with pressing enter !");
    mvprintw (y_start + 22,x_start + 15,"you are selecting option ( ) !");
    mvprintw (y_start + 20,x_start + 7,"to change selected option press 'w' or 's' key"); 
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 1,x_start + 1,"main page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 22, x_start + 41, "%d", num);
    attroff (COLOR_PAIR (3));
    if (num == 1){
        print_in_main_page_state_1(y_start, x_start);
    } 
    if (num == 2){
        print_in_main_page_state_2(y_start, x_start);
    } 
    if (num == 3){
        print_in_main_page_state_3(y_start, x_start);
    }
    if (num == 4){
        print_in_main_page_state_4(y_start, x_start);
    }
    if (num == 5){
        print_in_main_page_state_5(y_start, x_start);
    }
}
int controlle_menu (char key, int menu_num, int num){
    switch (key){
        case 's':
        num++;
        break;
        case 'w':
        num--;
        break;
    }
    if (num == 0){
        num = menu_num;
    }
    if (num == menu_num + 1){
        num = 1;
    }    
    return num;
}
int Main_page (WINDOW *main_page){
    char key;
    int num = 1;
    create_main_page (main_page);
    printer_for_main_page (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 5, num);
        printer_for_main_page (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    clear();
    refresh();
    delwin (main_page);
    return num;
}
//----------------------------------------------------------------------------------
void print_log_in_menu_state_1 (int y_start,int x_start){
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 8 ,x_start + 19,"     1-Sgin in    ");
    attroff (COLOR_PAIR (2));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 10,x_start + 19,"     2-Log in     ");
    mvprintw (y_start + 12,x_start + 19,"      3-Exit      ");
    attroff (COLOR_PAIR (1));
}
void print_log_in_menu_state_2 (int y_start,int x_start){
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 10,x_start + 19,"     2-Log in     ");
    attroff (COLOR_PAIR (2));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 8 ,x_start + 19,"     1-Sgin in    ");
    mvprintw (y_start + 12,x_start + 19,"      3-Exit      ");
    attroff (COLOR_PAIR (1));
}
void print_log_in_menu_state_3 (int y_start,int x_start){
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 12,x_start + 19,"      3-Exit      ");
    attroff (COLOR_PAIR (2));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 8 ,x_start + 19,"     1-Sgin in    ");
    mvprintw (y_start + 10,x_start + 19,"     2-Log in     ");
    attroff (COLOR_PAIR (1));
}
void printer_for_log_in_menu (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 22,x_start + 15,"you are selecting option ( ) !"); 
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 22, x_start + 41, "%d", num);
    attroff (COLOR_PAIR (3));
    if (num == 1){
        print_log_in_menu_state_1(y_start, x_start);
    } 
    if (num == 2){
        print_log_in_menu_state_2(y_start, x_start);
    } 
    if (num == 3){
        print_log_in_menu_state_3(y_start, x_start);
    }
}
//----------------------------------------------------------------------------------
void print_space_for_write (int high){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (4));
    mvprintw (y_start + high    ,x_start + 26, "____________________");
    mvprintw (y_start + high + 1,x_start + 25,"/                    \\");
    mvprintw (y_start + high + 2,x_start + 25,"\\____________________/");
    attroff (COLOR_PAIR (4));
}
void printer_for_log_in (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 8 ,x_start + 4, "O");
    mvprintw (y_start + 9 ,x_start + 3,"[_]");
    attroff (COLOR_PAIR (5));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 12,x_start + 3,"/\\___");
    mvprintw (y_start + 13,x_start + 3,"\\/ ||");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 8 ,x_start + 11,"user name   :");
    mvprintw (y_start + 12,x_start + 11,"password    :");
    attroff (COLOR_PAIR (3));
    print_space_for_write (7);
    print_space_for_write (11);
}
void printer_for_sgin_in (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);    
    printer_for_log_in (); 
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 16,x_start + 3,"o");
    mvprintw (y_start + 17,x_start + 3,"o o"); 
    attroff (COLOR_PAIR (6));
    print_space_for_write (15);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 16,x_start + 9,"national code :");
    attroff (COLOR_PAIR (3));
}
//----------------------------------------------------------------------------------
void text_on (void){
    curs_set (1);
    echo();
}
void text_off (void){
    noecho();
    curs_set (0);
}
void print_national_code_error (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (7));
    mvprintw (y_start + 19, x_start + 7 ,"Your national code must have 10 charachters !");
    mvprintw (y_start + 21, x_start + 13,"Please chack your national code !");
    attroff (COLOR_PAIR (7));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 23, x_start + 16,"press any key to continue !");
    attroff (COLOR_PAIR (6)); 
    getch();
}
void print_name_exist_error (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (7));
    mvprintw (y_start + 19, x_start + 16,"This name ia already exist !");
    mvprintw (y_start + 21, x_start + 14,"Maby your password in incorect !");
    attroff (COLOR_PAIR (7));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 23, x_start + 16,"press any key to continue !");
    attroff (COLOR_PAIR (6)); 
    getch();        
}
void print_sign_in_successful (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 20, x_start + 17,"You sign in sucsessfuly!");
    mvprintw (y_start + 22, x_start + 16,"press any key to continue !");
    attroff (COLOR_PAIR (6)); 
    getch();        
}
//----------------------------------------------------------------------------------
int counter_of_people_user (void){
    struct people userp[50];
    int num_of_user = 0; 
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *sign_data = fopen ("SignPeople.dat","rb");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    while (1 > 0){
        fread (&userp[num_of_user], sizeof(struct people), 1, sign_data);
        if (feof(sign_data)){
            break;
        }
        num_of_user++;
    } 
    fclose (sign_data);    
    return num_of_user;   
}
int counter_of_viewer_user (void){
    struct viewer userv[50];
    int num_of_user = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *sign_data = fopen ("SignViewer.dat","rb");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }  
    while (1 > 0){
        fread (&userv[num_of_user], sizeof(struct viewer), 1, sign_data);
        if (feof(sign_data)){
            break;
        }
        num_of_user++;
    } 
    fclose (sign_data);    
    return num_of_user;
}
int counter_of_legal_user (void){
    struct legal userl[50]; 
    int num_of_user = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start); 
    FILE *sign_data = fopen ("SignLegal.dat","rb");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }  
    while (1 > 0){
        fread (&userl[num_of_user], sizeof(struct legal), 1, sign_data);
        if (feof(sign_data)){
            break;
        }
        num_of_user++;
    }         
    fclose (sign_data);     
    return num_of_user;       
}
//----------------------------------------------------------------------------------
int check_people_user_name (char *user_name_check){
    struct people userp[50];    
    int num_of_user = 0;
    int access_of_userp = 1;
    int final_access_of_userp = 1;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);    
    FILE *sign_data = fopen ("SignPeople.dat","rb");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    while (1 > 0){
        fread (&userp[num_of_user], sizeof(struct people), 1, sign_data);
        if (feof (sign_data)){
            break;
        }
        access_of_userp = strcmp (userp[num_of_user].user_name_of_people, user_name_check);
        if (access_of_userp == 0){
            final_access_of_userp = 0;
        }
        num_of_user++;
    }        
    fclose (sign_data);
    return final_access_of_userp;
}
int check_viewer_user_name (char *user_name_check){
    struct viewer userv[50];
    int num_of_user = 0;
    int access_of_userv = 1;
    int final_access_of_userv = 1;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *sign_data = fopen ("SignViewer.dat","rb");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    while (1 > 0){
        fread (&userv[num_of_user], sizeof(struct viewer), 1, sign_data);
        if (feof (sign_data)){
            break;
        }
        access_of_userv = strcmp (userv[num_of_user].user_name_of_viewer, user_name_check);
        if (access_of_userv == 0){
            final_access_of_userv = 0;
        }
        num_of_user++;
    } 
    fclose (sign_data);
    return final_access_of_userv;
}
int check_legal_user_name (char *user_name_check){
    struct legal userl[50];
    int num_of_user = 0;
    int access_of_userl = 1;
    int final_access_of_userl = 1;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *sign_data = fopen ("SignLegal.dat","rb");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    while (1 > 0){
        fread (&userl[num_of_user], sizeof(struct legal), 1, sign_data);
        if (feof (sign_data)){
            break;
        }
        access_of_userl = strcmp (userl[num_of_user].user_name_of_legal, user_name_check);
        if (access_of_userl == 0){
            final_access_of_userl = 0;
        }
        num_of_user++;
    }
    fclose (sign_data);
    return final_access_of_userl;
}
//----------------------------------------------------------------------------------
int sign_in_people (void){
    struct people userp[50];
    char user_name_check[20];
    char password_check[20];
    char national_code_check[20];
    int num_of_user = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    text_on ();
    move(y_start + 8 , x_start + 26);
    mvscanw (y_start + 8, x_start + 26, "%s", &user_name_check);
    move(y_start + 12, x_start + 26);
    mvscanw (y_start + 12, x_start + 26, "%s", &password_check);
    move(y_start + 16, x_start + 26);
    mvscanw (y_start + 16, x_start + 26, "%s", &national_code_check);
    text_off ();
    if (strlen (national_code_check) != 10){
        print_national_code_error ();
        return 501;
    }
    num_of_user = counter_of_people_user();
    FILE *sign_data = fopen ("SignPeople.dat","ab+");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    if (check_people_user_name (user_name_check) == 0){
        print_name_exist_error ();
    }
    else {
        strcpy (userp[num_of_user].user_name_of_people, user_name_check);
        strcpy (userp[num_of_user].password_of_people, password_check);
        print_sign_in_successful ();
        fwrite (&userp[num_of_user], sizeof(struct people), 1, sign_data);
        saving_is_blocked (user_name_check);
        saving_money (user_name_check);
    }                  
    fclose (sign_data);
    return 0;
}
int sign_in_viewer (void){
    struct viewer userv[50];
    char user_name_check[20];
    char password_check[20];
    char national_code_check[20];
    int num_of_user = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    text_on ();
    move(y_start + 8 , x_start + 26);
    mvscanw (y_start + 8, x_start + 26, "%s", &user_name_check);
    move(y_start + 12, x_start + 26);
    mvscanw (y_start + 12, x_start + 26, "%s", &password_check);
    move(y_start + 16, x_start + 26);
    mvscanw (y_start + 16, x_start + 26, "%s", &national_code_check);
    text_off ();
    if (strlen (national_code_check) != 10){
        print_national_code_error ();
        return 501;
    }
    num_of_user = counter_of_viewer_user();
    FILE *sign_data = fopen ("SignViewer.dat","ab+");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    if (check_viewer_user_name (user_name_check) == 0){
        print_name_exist_error();
    }
    else {
        strcpy (userv[num_of_user].user_name_of_viewer, user_name_check);
        strcpy (userv[num_of_user].password_of_viewer, password_check);
        print_sign_in_successful ();
        fwrite (&userv[num_of_user], sizeof(struct viewer), 1, sign_data);
    }
    fclose (sign_data);
    return 0;
}
int sign_in_legal (void){
    struct legal userl[50];
    char user_name_check[20];
    char password_check[20];
    char national_code_check[20];
    int num_of_user = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    text_on ();
    move(y_start + 8 , x_start + 26);
    mvscanw (y_start + 8, x_start + 26, "%s", &user_name_check);
    move(y_start + 12, x_start + 26);
    mvscanw (y_start + 12, x_start + 26, "%s", &password_check);
    move(y_start + 16, x_start + 26);
    mvscanw (y_start + 16, x_start + 26, "%s", &national_code_check);
    text_off (); 
    if (strlen (national_code_check) != 10){
        print_national_code_error ();
        return 501;
    }  
    num_of_user = counter_of_legal_user();
    FILE *sign_data = fopen ("SignLegal.dat","ab+");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    if (check_legal_user_name (user_name_check) == 0){
        print_name_exist_error();
    }
    else {
        strcpy (userl[num_of_user].user_name_of_legal, user_name_check);
        strcpy (userl[num_of_user].password_of_legal, password_check);
        print_sign_in_successful ();
        fwrite (&userl[num_of_user], sizeof(struct legal), 1, sign_data);
    }
    fclose (sign_data);
    return 0;
}
//----------------------------------------------------------------------------------
void print_access (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 21, x_start + 18,"log in is successful !");
    mvprintw (y_start + 23, x_start + 16,"press any key to continue !");
    attroff (COLOR_PAIR (6)); 
    getch();
}
void print_wrong_password (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (7));
    mvprintw (y_start + 19, x_start + 16,"This name ia already exist !");
    mvprintw (y_start + 21, x_start + 14,"Maby your password in incorect !");
    attroff (COLOR_PAIR (7));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 23, x_start + 16,"press any key to continue !");
    attroff (COLOR_PAIR (6)); 
    getch();     
}
void print_access_denyed (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (7));
    mvprintw (y_start + 21, x_start + 22,"access denyed !");
    attroff (COLOR_PAIR (7));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 23, x_start + 16,"press any key to continue !");
    attroff (COLOR_PAIR (6)); 
    getch();    
}
void print_you_are_block (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (7));
    mvprintw (y_start + 20, x_start + 5,"sorry but you are blocked with the legal member !");
    attroff (COLOR_PAIR (7));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 22, x_start + 16,"press any key to continue !");
    attroff (COLOR_PAIR (6)); 
    getch();    
}
int check_name_and_password_of_people (char *user_name_check, char *password_check){
    struct people userp[50];
    int num_of_user = 0;
    int access_of_user = 1;
    int access_of_password = 1;
    int value = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start); 
    FILE *sign_data = fopen ("SignPeople.dat","ab+");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    while (1 > 0){
        fread (&userp[num_of_user], sizeof(struct people), 1, sign_data);
        if (feof(sign_data)){
            break;
        }
        access_of_user = strcmp (userp[num_of_user].user_name_of_people, user_name_check);
        access_of_password = strcmp (userp[num_of_user].password_of_people, password_check);
        if (access_of_user == 0 && access_of_password == 0){
            value = 1;
            break;
        }
        num_of_user++;
    }
    fclose (sign_data);
    return value;
}
int check_name_and_password_of_viewer (char *user_name_check, char *password_check){
    struct viewer userv[50];
    int num_of_user = 0;
    int access_of_user = 1;
    int access_of_password = 1;
    int value = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start); 
    FILE *sign_data = fopen ("SignViewer.dat","ab+");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    } 
    while (1 > 0){
        fread (&userv[num_of_user], sizeof(struct viewer), 1, sign_data);
        if (feof(sign_data)){
            break;
        }
        access_of_user = strcmp (userv[num_of_user].user_name_of_viewer, user_name_check);
        access_of_password = strcmp (userv[num_of_user].password_of_viewer, password_check);
        if (access_of_user == 0 && access_of_password == 0){
            value = 1;
            break;
        }
        num_of_user++;
    }
    fclose (sign_data);  
    return value;  
}
int check_name_and_password_of_legal (char *user_name_check, char *password_check){
    struct legal userl[50];
    int num_of_user = 0;
    int access_of_user = 1;
    int access_of_password = 1;
    int value = 0;
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start); 
    FILE *sign_data = fopen ("SignLegal.dat","ab+");   
    if (sign_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    while (1 > 0){
        fread (&userl[num_of_user], sizeof(struct legal), 1, sign_data);
        if (feof(sign_data)){
            break;
        }
        access_of_user = strcmp (userl[num_of_user].user_name_of_legal, user_name_check);
        access_of_password = strcmp (userl[num_of_user].password_of_legal, password_check);
        if (access_of_user == 0 && access_of_password == 0){
            value = 1;
            break;
        }
        num_of_user++;
    }
    fclose (sign_data); 
    return value;   
}
void get_login_name_of_people (char *user_name_save){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *login_data = fopen ("LoginPeople.txt","r");   
    if (login_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
    }
    while (fscanf (login_data, "%s", user_name_save) != EOF);
    fclose (login_data);    
}
int save_name_of_people (char *user_name_save){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *login_data = fopen ("LoginPeople.txt","w");   
    if (login_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    fprintf (login_data,"%s",user_name_save);
    fclose (login_data);
    return 0;
}
int log_in_people (void){
    int num = 1;
    char user_name_check[20];
    char password_check[20];
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);    
    text_on ();
    move(y_start + 8 , x_start + 26);
    mvscanw (y_start + 8, x_start + 26, "%s", &user_name_check);
    move(y_start + 12, x_start + 26);
    mvscanw (y_start + 12, x_start + 26, "%s", &password_check);    
    text_off ();
    if (is_people_blocked (user_name_check) == 1){
        print_you_are_block();
        return 1;
    }  
    if (check_name_and_password_of_people (user_name_check, password_check) == 1){
        print_access();
        save_name_of_people (user_name_check);
        num = 100;
    } 
    else if (check_people_user_name (user_name_check) == 0){
        print_wrong_password();
    }
    else{
        print_access_denyed();
    }
    return num;
}
void get_login_name_of_viewer (char *user_name_save){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *login_data = fopen ("LoginViewer.txt","r");   
    if (login_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch(); 
    }
    while (fscanf (login_data, "%s", user_name_save) != EOF);
    fclose (login_data);   
}
int log_in_viewer (void){
    int num = 2;
    char user_name_check[20];
    char password_check[20];
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);    
    text_on ();
    move(y_start + 8 , x_start + 26);
    mvscanw (y_start + 8, x_start + 26, "%s", &user_name_check);
    move(y_start + 12, x_start + 26);
    mvscanw (y_start + 12, x_start + 26, "%s", &password_check);    
    text_off ();
    if (check_name_and_password_of_viewer (user_name_check, password_check) == 1){
        print_access();
        num = 200;
    }
    else if (check_viewer_user_name (user_name_check) == 0){
        print_wrong_password();
    }
    else{
        print_access_denyed();
    } 
    return num;         
}
void get_login_name_of_legal (char *user_name_save){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *login_data = fopen ("LoginLegal.txt","r");   
    if (login_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch(); 
    }
    while (fscanf (login_data, "%s", user_name_save) != EOF);
    fclose (login_data);    
}
int log_in_legal (void){
    int num = 3;
    char user_name_check[20];
    char password_check[20];
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);    
    text_on ();
    move(y_start + 8 , x_start + 26);
    mvscanw (y_start + 8, x_start + 26, "%s", &user_name_check);
    move(y_start + 12, x_start + 26);
    mvscanw (y_start + 12, x_start + 26, "%s", &password_check);   
    text_off (); 
    if (check_name_and_password_of_legal (user_name_check, password_check) == 1){
        print_access ();
        num = 300;
    }
    else if (check_legal_user_name (user_name_check) == 0){
        print_wrong_password();
    }
    else{
        print_access_denyed();
    }
    return num;           
}
//----------------------------------------------------------------------------------
void create_sgin_in_page_for_people (WINDOW *sgin_in_win_for_people){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    sgin_in_win_for_people = newwin (25, 60, y_start, x_start);
    refresh();
    box (sgin_in_win_for_people, 0, 0);
    wrefresh (sgin_in_win_for_people);
}
void printer_for_sgin_in_people (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," sgin in page for people ");
    mvprintw (y_start + 1,x_start + 1,"main page/login people/sgin in people/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    printer_for_sgin_in ();
}
int sgin_in_page_for_people (WINDOW *sgin_in_win_for_people){
    sign_in_people();
    clear();
    refresh();
    delwin (sgin_in_win_for_people);
    return 1;
}
int sgin_in_for_people (WINDOW *sgin_in_win_for_people){
    int num = 0;
    create_sgin_in_page_for_people (sgin_in_win_for_people);
    printer_for_sgin_in_people();
    num = sgin_in_page_for_people (sgin_in_win_for_people);
    return num;
}
//----------------------------------------------------------------------------------
void create_log_in_page_for_people (WINDOW *log_in_win_for_people){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    log_in_win_for_people = newwin (25, 60, y_start, x_start);
    refresh();
    box (log_in_win_for_people, 0, 0);
    wrefresh (log_in_win_for_people);
}
void printer_for_log_in_people(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," Log in page for people ");
    mvprintw (y_start + 1,x_start + 1,"main page/login people/log in people/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    printer_for_log_in ();
}
int log_in_page_for_people (WINDOW *log_in_win_for_people){
    int num = 1;
    num = log_in_people ();
    clear();
    refresh();
    delwin (log_in_win_for_people);
    return num;
}
int log_in_for_people (WINDOW *log_in_win_for_people){
    int num = 0;
    create_log_in_page_for_people (log_in_win_for_people);
    printer_for_log_in_people();
    num = log_in_page_for_people (log_in_win_for_people);
    return num;
}
//----------------------------------------------------------------------------------
void create_sgin_in_page_for_viewer (WINDOW *sgin_in_win_for_viewer){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    sgin_in_win_for_viewer = newwin (25, 60, y_start, x_start);
    refresh();
    box (sgin_in_win_for_viewer, 0, 0);
    wrefresh (sgin_in_win_for_viewer);
}
void printer_for_sgin_in_viewer(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," sgin in page for viewer ");
    mvprintw (y_start + 1,x_start + 1,"main page/login viewer/sgin in viewer/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    printer_for_sgin_in ();
}
int sgin_in_page_for_viewer (WINDOW *sgin_in_win_for_viewer){
    sign_in_viewer ();
    clear();
    refresh();
    delwin (sgin_in_win_for_viewer);
    return 2;
}
int sgin_in_for_viewer (WINDOW *sgin_in_win_for_viewer){
    int num = 0;
    create_sgin_in_page_for_viewer (sgin_in_win_for_viewer);
    printer_for_sgin_in_viewer();
    num = sgin_in_page_for_viewer (sgin_in_win_for_viewer);
    return num;
}
//----------------------------------------------------------------------------------
void create_log_in_page_for_viewer (WINDOW *log_in_win_for_viewer){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    log_in_win_for_viewer = newwin (25, 60, y_start, x_start);
    refresh();
    box (log_in_win_for_viewer, 0, 0);
    wrefresh (log_in_win_for_viewer);

}
void printer_for_log_in_viewer(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," Log in page for viewer ");
    mvprintw (y_start + 1,x_start + 1,"main page/login viewer/log in viewer/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    printer_for_log_in ();
}
int log_in_page_for_viewer (WINDOW *log_in_win_for_viewer){
    int num = 2;
    num = log_in_viewer ();
    clear();
    refresh();
    delwin (log_in_win_for_viewer);
    return num;
}
int log_in_for_viewer (WINDOW *log_in_win_for_viewer){
    int num = 0;
    create_log_in_page_for_viewer (log_in_win_for_viewer);
    printer_for_log_in_viewer();
    num = log_in_page_for_viewer (log_in_win_for_viewer);
    return num;
}
//----------------------------------------------------------------------------------
void create_sgin_in_page_for_legal (WINDOW *sgin_in_win_for_legal){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    sgin_in_win_for_legal = newwin (25, 60, y_start, x_start);
    refresh();
    box (sgin_in_win_for_legal, 0, 0);
    wrefresh (sgin_in_win_for_legal);
}
void printer_for_sgin_in_legal(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," sgin in page for legal ");
    mvprintw (y_start + 1,x_start + 1,"main page/login legal/sgin in legal/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    printer_for_sgin_in ();
}
int sgin_in_page_for_legal (WINDOW *sgin_in_win_for_legal){
    sign_in_legal();
    clear();
    refresh();
    delwin (sgin_in_win_for_legal);
    return 3;
}
int sgin_in_for_legal (WINDOW *sgin_in_win_for_legal){
    int num = 0;
    create_sgin_in_page_for_legal (sgin_in_win_for_legal);
    printer_for_sgin_in_legal();
    num = sgin_in_page_for_legal (sgin_in_win_for_legal);
    return num;
}
//----------------------------------------------------------------------------------
void create_log_in_page_for_legal (WINDOW *log_in_win_for_legal){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    log_in_win_for_legal = newwin (25, 60, y_start, x_start);
    refresh();
    box (log_in_win_for_legal, 0, 0);
    wrefresh (log_in_win_for_legal);
}
void printer_for_Log_in_legal(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," Log in page for legal ");
    mvprintw (y_start + 1,x_start + 1,"main page/login legal/Log in legal/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    printer_for_log_in ();
}
int log_in_page_for_legal (WINDOW *log_in_win_for_legal){
    int num = 3;
    num = log_in_legal ();
    clear();
    refresh();
    delwin (log_in_win_for_legal);
    return num;
}
int log_in_for_legal (WINDOW *log_in_win_for_legal){
    int num = 0;
    create_log_in_page_for_legal (log_in_win_for_legal);
    printer_for_Log_in_legal();
    num = log_in_page_for_legal (log_in_win_for_legal);
    return num;
}
//----------------------------------------------------------------------------------
void create_people_section_page (WINDOW *people_section_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    people_section_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (people_section_win, 0, 0);
    wrefresh (people_section_win);
}
void printer_for_login_people(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," login people page ");
    mvprintw (y_start + 1,x_start + 1,"main page/login people/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int people_section_page (WINDOW *people_section_win){
    char key;
    int num = 1;
    create_people_section_page (people_section_win);
    printer_for_login_people();
    printer_for_log_in_menu (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 3, num);
        printer_for_log_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 10;
    if (num == 13){
        num = 0;
    }
    clear();
    refresh();
    delwin (people_section_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_viewer_section_page (WINDOW *viewer_section_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    viewer_section_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (viewer_section_win, 0, 0);
    wrefresh (viewer_section_win);
}
void printer_for_login_viewer(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," login viewer page ");
    mvprintw (y_start + 1,x_start + 1,"main page/login viewer/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int viewer_section_page (WINDOW *viewer_section_win){
    char key;
    int num = 1;
    create_viewer_section_page (viewer_section_win);
    printer_for_login_viewer();
    printer_for_log_in_menu (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 3, num);
        printer_for_log_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 20;
    if (num == 23){
        num = 0;
    }
    clear();
    refresh();
    delwin (viewer_section_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_legal_section_page (WINDOW *legal_section_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    legal_section_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (legal_section_win, 0, 0);
    wrefresh (legal_section_win);
}
void printer_for_login_legal(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," login legal page ");
    mvprintw (y_start + 1,x_start + 1,"main page/login legal/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int legal_section_page (WINDOW *legal_section_win){
    char key;
    int num = 1;
    create_legal_section_page (legal_section_win);
    printer_for_login_legal();
    printer_for_log_in_menu (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 3, num);
        printer_for_log_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 30;
    if (num == 33){
        num = 0;
    }
    clear();
    refresh();
    delwin (legal_section_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_of_money (void){
    struct Money mny[100];
    char user_name_save[20];
    int money = 0;
    get_login_name_of_people (user_name_save);
    int num_of_money = 0; 
    FILE *money_data = fopen ("Money.dat","rb");   
    while (1 > 0){
        fread (&mny[num_of_money], sizeof(struct Money), 1, money_data);
        if (feof(money_data)){
            break;
        }
        if (strcmp (mny[num_of_money].user_name, user_name_save) == 0){
            if (mny[num_of_money].money == 100){
                money++;
            }
        }
        num_of_money++;
    } 
    fclose (money_data);  
    money = money *100;  
    return money;
}
void create_people_menu_page (WINDOW *people_menu_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    people_menu_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (people_menu_win, 0, 0);
    wrefresh (people_menu_win);
}
void print_in_people_menu_state_1 (int y_start,int x_start){
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 6 ,x_start + 16,"      1-cardboard       ");
    attroff (COLOR_PAIR (2));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 8 ,x_start + 16,"   2-report new crime   ");
    mvprintw (y_start + 10,x_start + 16,"     3-arrange list     ");
    mvprintw (y_start + 12,x_start + 16,"     4-edit report      ");
    mvprintw (y_start + 14,x_start + 16,"    5-delete report     ");
    mvprintw (y_start + 16,x_start + 16," 6-show related reports ");
    mvprintw (y_start + 18,x_start + 16,"   7-important reports  ");
    mvprintw (y_start + 20,x_start + 16,"       8-buy VIP        ");
    mvprintw (y_start + 22,x_start + 16,"         9-Exit         ");
    attroff (COLOR_PAIR (1));
}
void print_in_people_menu_state_2 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 6 ,x_start + 16,"      1-cardboard       ");
    mvprintw (y_start + 10,x_start + 16,"     3-arrange list     ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 8 ,x_start + 16,"   2-report new crime   ");
    attroff (COLOR_PAIR (2));
}
void print_in_people_menu_state_3 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 8 ,x_start + 16,"   2-report new crime   ");
    mvprintw (y_start + 12,x_start + 16,"     4-edit report      ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 10,x_start + 16,"     3-arrange list     ");
    attroff (COLOR_PAIR (2));    
}
void print_in_people_menu_state_4 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 10,x_start + 16,"     3-arrange list     ");
    mvprintw (y_start + 14,x_start + 16,"    5-delete report     ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 12,x_start + 16,"     4-edit report      ");
    attroff (COLOR_PAIR (2));    
}
void print_in_people_menu_state_5 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 12,x_start + 16,"     4-edit report      ");
    mvprintw (y_start + 16,x_start + 16," 6-show related reports ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 14,x_start + 16,"    5-delete report     ");
    attroff (COLOR_PAIR (2));    
}
void print_in_people_menu_state_6 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 14,x_start + 16,"    5-delete report     ");
    mvprintw (y_start + 18,x_start + 16,"   7-important reports  ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 16,x_start + 16," 6-show related reports ");
    attroff (COLOR_PAIR (2));    
}
void print_in_people_menu_state_7 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 16,x_start + 16," 6-show related reports ");
    mvprintw (y_start + 20,x_start + 16,"       8-buy VIP        ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 18,x_start + 16,"   7-important reports  ");
    attroff (COLOR_PAIR (2));    
}
void print_in_people_menu_state_8 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 18,x_start + 16,"   7-important reports  ");
    mvprintw (y_start + 22,x_start + 16,"         9-Exit         ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 20,x_start + 16,"       8-buy VIP        ");
    attroff (COLOR_PAIR (2));    
}
void print_in_people_menu_state_9 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 6 ,x_start + 16,"      1-cardboard       ");
    mvprintw (y_start + 20,x_start + 16,"       8-buy VIP        ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 22,x_start + 16,"         9-Exit         ");
    attroff (COLOR_PAIR (2));    
}
void printer_for_people_menu (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 15," people section menu page ");
    mvprintw (y_start + 1,x_start + 1,"login people/Log in people/people menu page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    switch (num){
        case 1:
        print_in_people_menu_state_1 (y_start, x_start);
        break;
        case 2:
        print_in_people_menu_state_2 (y_start, x_start);
        break;
        case 3:
        print_in_people_menu_state_3 (y_start, x_start);
        break;
        case 4:
        print_in_people_menu_state_4 (y_start, x_start);
        break;
        case 5:
        print_in_people_menu_state_5 (y_start, x_start);
        break;
        case 6:
        print_in_people_menu_state_6 (y_start, x_start);
        break;
        case 7:
        print_in_people_menu_state_7 (y_start, x_start);
        break;
        case 8:
        print_in_people_menu_state_8 (y_start, x_start);
        break;
        case 9:
        print_in_people_menu_state_9 (y_start, x_start);
        break;
    }
}
int people_menu (WINDOW *people_menu_win){
    char key;
    int num = 1;
    create_people_menu_page (people_menu_win);
    printer_for_people_menu (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 9, num);
        printer_for_people_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 100;
    if (num == 109){
        num = 0;
    }
    clear();
    refresh();
    delwin (people_menu_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_cardboard_for_viewer_page (WINDOW *cardboard_for_viewer_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    cardboard_for_viewer_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (cardboard_for_viewer_win, 0, 0);
    wrefresh (cardboard_for_viewer_win);    
}
void print_in_cardboard_menu_state_1 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 12,x_start + 16,"         3-Exit         ");
    mvprintw (y_start + 10,x_start + 16,"       2-History        ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 8 ,x_start + 16,"        1-Inbox         ");
    attroff (COLOR_PAIR (2));
}
void print_in_cardboard_menu_state_2 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 12,x_start + 16,"         3-Exit         ");
    mvprintw (y_start + 8 ,x_start + 16,"        1-Inbox         ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 10,x_start + 16,"       2-History        ");
    attroff (COLOR_PAIR (2));
}
void print_in_cardboard_menu_state_3 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 8 ,x_start + 16,"        1-Inbox         ");
    mvprintw (y_start + 10,x_start + 16,"       2-History        ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 12,x_start + 16,"         3-Exit         ");
    attroff (COLOR_PAIR (2));
}
void printer_for_cardboard_viewer_page(int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," cardboard page ");
    mvprintw (y_start + 1,x_start + 1,"Log in viewer/viewer menu page/cardboard for viewer page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    switch (num){
        case 1:
        print_in_cardboard_menu_state_1 ();
        break;
        case 2:
        print_in_cardboard_menu_state_2 ();
        break;
        case 3:
        print_in_cardboard_menu_state_3 ();
        break;
    }
}
int cardboard_for_viewer (WINDOW *cardboard_for_viewer_win){
    char key;
    int num = 1;
    create_cardboard_for_viewer_page (cardboard_for_viewer_win);
    printer_for_cardboard_viewer_page (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 3, num);
        printer_for_cardboard_viewer_page (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 200;
    if (num == 203){
        num = 0;
    }
    clear();
    refresh();
    delwin (cardboard_for_viewer_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_Inbox_for_viewer_page (WINDOW *Inbox_for_viewer_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    Inbox_for_viewer_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (Inbox_for_viewer_win, 0, 0);
    wrefresh (Inbox_for_viewer_win);    
}
void printer_for_Inbox_viewer_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," Inbox page ");
    mvprintw (y_start + 1,x_start + 1,"viewer menu page/cardboard for viewer page/Inbox page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int Inbox_for_viewer_page (WINDOW *Inbox_for_viewer_win){
    clear();
    refresh();
    delwin (Inbox_for_viewer_win);
    return 200;
}
int Inbox_for_viewer (WINDOW *Inbox_for_viewer_win){
    int num = 0;
    create_Inbox_for_viewer_page (Inbox_for_viewer_win);
    printer_for_Inbox_viewer_page();
    getch();
    num = Inbox_for_viewer_page (Inbox_for_viewer_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_History_for_viewer_page (WINDOW *History_for_viewer_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    History_for_viewer_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (History_for_viewer_win, 0, 0);
    wrefresh (History_for_viewer_win);    
}
void printer_for_History_viewer_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," History page ");
    mvprintw (y_start + 1,x_start + 1,"viewer menu page/cardboard for viewer page/History page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int History_for_viewer_page (WINDOW *History_for_viewer_win){
    clear();
    refresh();
    delwin (History_for_viewer_win);
    return 200;
}
int History_for_viewer (WINDOW *History_for_viewer_win){
    int num = 0;
    create_History_for_viewer_page (History_for_viewer_win);
    printer_for_History_viewer_page();
    getch();
    num = History_for_viewer_page (History_for_viewer_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_legal_menu_page (WINDOW *legal_menu_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    legal_menu_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (legal_menu_win, 0, 0);
    wrefresh (legal_menu_win);
}
void print_in_legal_menu_state_1 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 10,x_start + 16,"   2-block reporters    ");
    mvprintw (y_start + 12,x_start + 16," 3-encourage reporters  ");
    mvprintw (y_start + 14,x_start + 16,"         4-Exit         ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 8 ,x_start + 16,"      1-cardboard       ");
    attroff (COLOR_PAIR (2));
}
void print_in_legal_menu_state_2 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 8 ,x_start + 16,"      1-cardboard       ");
    mvprintw (y_start + 12,x_start + 16," 3-encourage reporters  ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 10,x_start + 16,"   2-block reporters    ");
    attroff (COLOR_PAIR (2));
}
void print_in_legal_menu_state_3 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 14,x_start + 16,"         4-Exit         ");
    mvprintw (y_start + 10,x_start + 16,"   2-block reporters    ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 12,x_start + 16," 3-encourage reporters  ");
    attroff (COLOR_PAIR (2));
}
void print_in_legal_menu_state_4 (int y_start,int x_start){
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 8 ,x_start + 16,"      1-cardboard       ");
    mvprintw (y_start + 12,x_start + 16," 3-encourage reporters  ");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 14,x_start + 16,"         4-Exit         ");
    attroff (COLOR_PAIR (2));
}
void printer_for_legal_menu_page (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 16," legal section menu page ");
    mvprintw (y_start + 1,x_start + 1,"login legal/Log in legal/legal menu page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    switch (num){
        case 1:
        print_in_legal_menu_state_1 (y_start, x_start);
        break;
        case 2:
        print_in_legal_menu_state_2 (y_start, x_start);
        break;
        case 3:
        print_in_legal_menu_state_3 (y_start, x_start);
        break;
        case 4:
        print_in_legal_menu_state_4 (y_start, x_start);
        break;
    }
}
int legal_menu (WINDOW *legal_menu_win){
    char key;
    int num = 1;
    create_legal_menu_page (legal_menu_win);
    printer_for_legal_menu_page (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 4, num);
        printer_for_legal_menu_page (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 300;
    if (num == 304){
        num = 0;
    }
    clear();
    refresh();
    delwin (legal_menu_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_cardboard_for_people_page (WINDOW *cardboard_for_people_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    cardboard_for_people_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (cardboard_for_people_win, 0, 0);
    wrefresh (cardboard_for_people_win);    
}
void printer_for_cardboard_people_page(int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," cardboard page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/cardboard for people page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 18,x_start + 1,"total money :%d ",counter_of_money());
    attroff (COLOR_PAIR (5));
    switch (num){
        case 1:
        print_in_cardboard_menu_state_1 ();
        break;
        case 2:
        print_in_cardboard_menu_state_2 ();
        break;
        case 3:
        print_in_cardboard_menu_state_3 ();
        break;
    }
}
int cardboard_for_people (WINDOW *cardboard_for_people_win){
    char key;
    int num = 1;
    create_cardboard_for_people_page (cardboard_for_people_win);
    printer_for_cardboard_people_page (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 3, num);
        printer_for_cardboard_people_page (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 110;
    if (num == 113){
        num = 100;
    }
    clear();
    refresh();
    delwin (cardboard_for_people_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_report_new_crime_page (WINDOW *report_new_crime_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    report_new_crime_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (report_new_crime_win, 0, 0);
    wrefresh (report_new_crime_win);    
}
void printer_for_report_new_crime_page(WINDOW *write_win){
    wattron (write_win, COLOR_PAIR (3));
    mvwprintw (write_win, 2, 17," report new crime page ");
    mvwprintw (write_win, 0, 0,"Log in people/people menu page/report new crime page/");
    mvwprintw (write_win, 1, 0,"__________________________________________________________");
    wattroff (write_win, COLOR_PAIR (3));
    wattron (write_win, COLOR_PAIR (1));
    mvwprintw (write_win, 6 , 0," Decription :");
    wattroff (write_win, COLOR_PAIR (1));
    wattron (write_win, COLOR_PAIR (6));
    mvwprintw (write_win, 16, 0," Place of crime :");
    mvwprintw (write_win, 18, 0," National code :");
    wattroff (write_win, COLOR_PAIR (6));
    wattron (write_win, COLOR_PAIR (5));
    mvwprintw (write_win, 4, 0," Title : ");
    wattroff (write_win, COLOR_PAIR (5));
    wattron (write_win, COLOR_PAIR (4));
    mvwprintw (write_win, 5 , 0,"__________________________________________________________");
    mvwprintw (write_win, 15, 0,"__________________________________________________________");
    mvwprintw (write_win, 17, 0,"__________________________________________________________");
    mvwprintw (write_win, 19, 0,"__________________________________________________________");
    wattroff (write_win, COLOR_PAIR (4));
    refresh(); 
    wrefresh (write_win);
}
void get_strings (char *Title, char *Discription, char *PlaceOfCrime, char *NationalCode, WINDOW *write_win){
    text_on();
    mvwgetnstr (write_win, 4, 8, Title, 30);
    mvwgetnstr (write_win, 6, 13, Discription, 530);
    mvwgetnstr (write_win, 16, 17, PlaceOfCrime, 40);
    mvwgetnstr (write_win, 18, 16, NationalCode, 10);
    text_off();
}
int end_of_getting_new_report (WINDOW *report_new_crime_win, WINDOW *write_win){
    clear();
    refresh();
    delwin (report_new_crime_win);
    delwin (write_win);
    return 100;
}
void get_time_of_year (char *year, char *mounth, char *day){
    struct tm* local;
    time_t time_year = time (NULL);
    local = localtime (&time_year);
    strftime (year , sizeof(year), "%Y", local);
    strftime (mounth , sizeof(mounth), "%m", local);
    strftime (day , sizeof(day), "%d", local);
}
void get_time_of_hour (char *hour, char *minute, char *second){
    struct tm* local;
    time_t time_hour = time (NULL);
    local = localtime (&time_hour);
    strftime (hour , sizeof(hour), "%H", local);
    strftime (minute , sizeof(minute), "%M", local);
    strftime (second , sizeof(second), "%S", local);
}
int counter_of_reception (void){
    struct Reception rpio[100];
    int num_of_reception = 0; 
    FILE *reception_data = fopen ("Reception.dat","rb");   
    while (1 > 0){
        fread (&rpio[num_of_reception], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        num_of_reception++;
    } 
    fclose (reception_data);    
    return num_of_reception;   
}
int counter_of_important (void){
    struct ImportantReport imprpt[100];
    int num_of_important = 0; 
    FILE *important_data = fopen ("ImportantReport.dat","rb");   
    while (1 > 0){
        fread (&imprpt[num_of_important], sizeof(struct ImportantReport), 1, important_data);
        if (feof(important_data)){
            break;
        }
        num_of_important++;
    } 
    fclose (important_data);    
    return num_of_important;   
}
int counter_of_reports (void){
    struct report rpt[100];
    int num_of_report = 0; 
    FILE *report_data = fopen ("Reports.dat","rb");   
    while (1 > 0){
        fread (&rpt[num_of_report], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        }
        num_of_report++;
    } 
    fclose (report_data);    
    return num_of_report;   
}
int counter_of_num (void){
    struct IsDeleted isdel[100];
    int num = 0; 
    FILE *delete_data = fopen ("IsDeleted.dat","rb");   
    while (1 > 0){
        fread (&isdel[num], sizeof(struct IsDeleted), 1, delete_data);
        if (feof(delete_data)){
            break;
        }
        num++;
    } 
    fclose (delete_data);    
    return num;
}
void saving_reception_report (void){
    struct Reception rpio[100];
    int num_of_reception = 0;
    int num_of_report = 0;
    char user_name_save[20];
    num_of_reception = counter_of_reception ();
    num_of_report =  counter_of_reports ();
    get_login_name_of_people (user_name_save);
    strcpy (rpio[num_of_reception].user_name, user_name_save);
    rpio[num_of_reception].status = 2;
    rpio[num_of_reception].ReportCode = num_of_report;
    rpio[num_of_reception].num_of_reception = num_of_reception;
    FILE *reception_data = fopen ("Reception.dat","ab");
    fwrite (&rpio[num_of_reception], sizeof(struct Reception), 1, reception_data);
    fclose (reception_data);
}
void saving_important_report (void){
    struct ImportantReport imprpt[100];
    int num_of_important = 0;
    int num_of_report = 0;
    char user_name_save[20];
    num_of_important = counter_of_important ();
    num_of_report =  counter_of_reports ();
    get_login_name_of_people (user_name_save);
    strcpy (imprpt[num_of_important].user_name, user_name_save);
    imprpt[num_of_important].important_report = 0;
    imprpt[num_of_important].ReportCode = num_of_report;
    imprpt[num_of_important].num_of_important = num_of_important;
    FILE *important_data = fopen ("ImportantReport.dat","ab");
    fwrite (&imprpt[num_of_important], sizeof(struct ImportantReport), 1, important_data);
    fclose (important_data);
}
void saveing_is_deleted (void){
    struct IsDeleted isdel[100];
    int num = 0;
    int num_of_report = 0;
    char user_name_save[20];
    num = counter_of_num (); 
    num_of_report =  counter_of_reports ();
    get_login_name_of_people (user_name_save);
    strcpy (isdel[num].user_name, user_name_save);
    isdel[num].is_deleted = 0;
    isdel[num].ReportCode = num_of_report;
    isdel[num].num = num;
    FILE *delete_data = fopen ("IsDeleted.dat","ab");
    fwrite (&isdel[num], sizeof(struct IsDeleted), 1, delete_data);
    fclose (delete_data);
}
void saveing_report (char *Title, char *Discription, char *PlaceOfCrime, char *NationalCode,
    char *year, char *mounth, char *day, char *hour, char *minute, char *second){
    char user_name_save[20];
    get_login_name_of_people (user_name_save); 
    int num_of_report = 0; 
    num_of_report =  counter_of_reports ();
    struct report rpt[100];
    strcpy (rpt[num_of_report].Title, Title);
    strcpy (rpt[num_of_report].Discription, Discription);
    strcpy (rpt[num_of_report].PlaceOfcrime, PlaceOfCrime);
    strcpy (rpt[num_of_report].NationalCode, NationalCode);
    strcpy (rpt[num_of_report].year, year);
    strcpy (rpt[num_of_report].mounth, mounth);
    strcpy (rpt[num_of_report].day, day);
    strcpy (rpt[num_of_report].hour, hour);
    strcpy (rpt[num_of_report].minute, minute);
    strcpy (rpt[num_of_report].second, second);
    strcpy (rpt[num_of_report].user_name, user_name_save);
    rpt[num_of_report].num_of_report = num_of_report;
    saving_reception_report ();
    saveing_is_deleted ();
    saving_important_report ();
    FILE *report_data = fopen ("Reports.dat","ab");
    fwrite (&rpt[num_of_report], sizeof(struct report), 1, report_data);
    fclose (report_data);
}
int report_new_crime (WINDOW *report_new_crime_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    char Title[30];
    char Discription[530];
    char PlaceOfCrime[40];
    char NationalCode[10];
    char year[5], mounth[3], day[3];
    char hour[3], minute[3], second[3];
    int num = 0;
    WINDOW *write_win;
    create_report_new_crime_page (report_new_crime_win);
    write_win = newwin (23, 58, y_start + 1, x_start + 1);
    refresh();
    printer_for_report_new_crime_page (write_win);
    get_strings (Title, Discription, PlaceOfCrime, NationalCode, write_win);
    get_time_of_hour (hour, minute, second);
    get_time_of_year (year, mounth, day);
    saveing_report (Title, Discription, PlaceOfCrime, NationalCode, year, mounth, day, hour, minute, second);
    num = end_of_getting_new_report (report_new_crime_win, write_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_arrange_list_page (WINDOW *arrange_list_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    arrange_list_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (arrange_list_win, 0, 0);
    wrefresh (arrange_list_win);    
}
void printer_for_arrange_list_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," arrange list page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/arrange list page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int arrange_list_page (WINDOW *arrange_list_win){
    clear();
    refresh();
    delwin (arrange_list_win);
    return 100;
}
int arrange_list (WINDOW *arrange_list_win){
    int num = 0;
    create_arrange_list_page (arrange_list_win);
    printer_for_arrange_list_page();
    getch();
    num = arrange_list_page (arrange_list_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_edit_report_page (WINDOW *edit_report_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    edit_report_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (edit_report_win, 0, 0);
    wrefresh (edit_report_win);    
}
void create_write_page_for_edit (WINDOW *write_win_edit){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    write_win_edit = newwin (23, 58, y_start + 1, x_start + 1);
    refresh();    
}
void printer_for_edit_report_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 3,x_start + 18," edit report page ");
    mvprintw (y_start + 1, x_start + 1,"Log in people/people menu page/edit report page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 7 , x_start + 1," Decription :");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 17, x_start + 1," Place of crime :");
    mvprintw (y_start + 19, x_start + 1," National code :");
    attroff (COLOR_PAIR (6));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 5, x_start + 1," Title : ");
    attroff (COLOR_PAIR (5));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6 , x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 16, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 18, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 20, x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
}
void printer_error_for_edit_reports_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 3,x_start + 18," edit report page ");
    mvprintw (y_start + 1, x_start + 1,"Log in people/people menu page/edit report page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 14," There is no report to edit !");
    attroff (COLOR_PAIR (5));
}
void read_report_from_file (int num, char *Title, char *Discription, char *PlaceOfCrime, char *NationalCode){
    int counter = 0;
    struct report rpt[100];
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[counter], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        } 
        if (num == rpt[num].num_of_report){
            strcpy (Title, rpt[num].Title);
            strcpy (Discription, rpt[num].Discription);
            strcpy (PlaceOfCrime, rpt[num].PlaceOfcrime);
            strcpy (NationalCode, rpt[num].NationalCode);
            break;
        } 
        counter++;  
    }
    fclose (report_data);
}
void printer_for_edit_report_in_menu (int num_of_nth_report, WINDOW *edit_report_win, WINDOW *write_win_edit){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    edit_report_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (edit_report_win, 0, 0);
    wrefresh (edit_report_win);
    write_win_edit = newwin (23, 58, y_start + 1, x_start + 1);
    refresh ();  
    wrefresh(write_win_edit);
    printer_for_edit_report_page();
    int report_code_for_read = get_report_code_for_delete (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = num_of_report_for_read;
    char Title[30];
    char Discription[530];
    char PlaceOfCrime[40];
    char NationalCode[10];
    read_report_from_file (num, Title, Discription,PlaceOfCrime, NationalCode);
    mvwprintw (write_win_edit,  4, 9,"%s",Title);
    mvwprintw (write_win_edit,  6, 14,"%s",Discription);
    mvwprintw (write_win_edit, 16, 18, "%s",PlaceOfCrime);
    mvwprintw (write_win_edit, 18, 17,"%d",NationalCode);
    refresh();
    wrefresh (write_win_edit);
    refresh();
}
int which_report_is_going_to_edit (WINDOW *edit_report_win, WINDOW *write_win_edit){
    create_edit_report_page (edit_report_win);
    create_write_page_for_edit (write_win_edit);
    char key;
    int num = 1;
    printer_for_edit_report_in_menu (1, edit_report_win, write_win_edit);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (edit_report_win);
        delwin (write_win_edit);
        num = controlle_menu (key, counter_of_exist_report_for_delete (), num);
        printer_for_edit_report_in_menu (num, edit_report_win, write_win_edit);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void print_are_you_sure_for_edit_state_1 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 22,x_start + 40," Yes ");
    attron (COLOR_PAIR (2));
    attron (COLOR_PAIR (1)); 
    mvprintw (y_start + 23,x_start + 40,"  No "); 
    attron (COLOR_PAIR (1));  
}
void print_are_you_sure_for_edit_state_2 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 22,x_start + 40," Yes ");
    attron (COLOR_PAIR (1));
    attron (COLOR_PAIR (2)); 
    mvprintw (y_start + 23,x_start + 40,"  No "); 
    attron (COLOR_PAIR (2));  
}
void printer_for_are_you_sure_for_edit (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 22,x_start + 1," Are you sure to edit this report ? ");
    attron (COLOR_PAIR (1));
    switch (num){
        case 1:
        print_are_you_sure_for_edit_state_1 ();
        break;
        case 2:
        print_are_you_sure_for_edit_state_2 ();
        break;
    }
}
int Are_you_sure_for_edit (void){
    char key;
    int num = 1;
    printer_for_are_you_sure_for_edit (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 2, num);
        printer_for_are_you_sure_for_edit (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void get_time_of_year_edited (char *year, char *mounth, char *day, int num_of_nth_report){
    int report_code =  get_report_code_for_delete (num_of_nth_report);
    struct report rpt[100];
    int num = 0;
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[num], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        } 
        if (rpt[num].num_of_report == report_code){
            strcpy (year, rpt[num].year);
            strcpy (mounth, rpt[num].mounth);
            strcpy (day, rpt[num].day);
            break;
        } 
        num++;  
    }
    fclose (report_data);
}
void get_time_of_hour_edited (char *hour, char *minute, char *second, int num_of_nth_report){
    int report_code =  get_report_code_for_delete (num_of_nth_report);
    struct report rpt[100];
    int num = 0;
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[num], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        } 
        if (rpt[num].num_of_report == report_code){
            strcpy (hour, rpt[num].hour);
            strcpy (minute, rpt[num].minute);
            strcpy (second, rpt[num].second);
            break;
        } 
        num++;  
    }
    fclose (report_data);
}
void saveing_report_edited (char *Title, char *Discription, char *PlaceOfCrime, char *NationalCode,
    char *year, char *mounth, char *day, char *hour, char *minute, char *second){
    char user_name_save[20];
    get_login_name_of_people (user_name_save); 
    int num_of_report = 0; 
    num_of_report =  counter_of_reports ();
    struct report rpt[100];
    strcpy (rpt[num_of_report].Title, Title);
    strcpy (rpt[num_of_report].Discription, Discription);
    strcpy (rpt[num_of_report].PlaceOfcrime, PlaceOfCrime);
    strcpy (rpt[num_of_report].NationalCode, NationalCode);
    strcpy (rpt[num_of_report].year, year);
    strcpy (rpt[num_of_report].mounth, mounth);
    strcpy (rpt[num_of_report].day, day);
    strcpy (rpt[num_of_report].hour, hour);
    strcpy (rpt[num_of_report].minute, minute);
    strcpy (rpt[num_of_report].second, second);
    strcpy (rpt[num_of_report].user_name, user_name_save);
    rpt[num_of_report].num_of_report = num_of_report;
    saving_reception_report ();
    saveing_is_deleted ();
    saving_important_report ();
    FILE *report_data = fopen ("Reports.dat","ab");
    fwrite (&rpt[num_of_report], sizeof(struct report), 1, report_data);
    fclose (report_data);
}
int report_new_crime_edited (WINDOW *report_new_crime_win, int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    char Title[30];
    char Discription[530];
    char PlaceOfCrime[40];
    char NationalCode[10];
    char year[5], mounth[3], day[3];
    char hour[3], minute[3], second[3];
    int num = 0;
    WINDOW *write_win;
    create_report_new_crime_page (report_new_crime_win);
    write_win = newwin (23, 58, y_start + 1, x_start + 1);
    refresh();
    printer_for_report_new_crime_page (write_win);
    get_strings (Title, Discription, PlaceOfCrime, NationalCode, write_win);
    get_time_of_hour_edited (hour, minute, second, num_of_nth_report);
    get_time_of_year_edited (year, mounth, day, num_of_nth_report);
    saveing_report_edited (Title, Discription, PlaceOfCrime, NationalCode, year, mounth, day, hour, minute, second);
    num = end_of_getting_new_report (report_new_crime_win, write_win);
    return num;
}
void edit_reports (int num_of_nth_report, WINDOW *report_new_crime_win){
    delete_reports (num_of_nth_report);
    report_new_crime_edited (report_new_crime_win, num_of_nth_report);
}
int edit_report_page (WINDOW *edit_report_win){
    int num = 0;
    WINDOW *write_win_edit;
    if (counter_of_exist_report_for_delete () == 0){
        printer_error_for_edit_reports_page ();
        getch();
    }
    else {
        num = which_report_is_going_to_edit (edit_report_win, write_win_edit);
        if (Are_you_sure_for_edit () == 1){
            edit_reports (num, edit_report_win);
            clear();
            refresh();
            delwin (edit_report_win);
            delwin (write_win_edit);
        } 
    } 
    return 100;
}
int edit_report (WINDOW *edit_report_win){
    int num = 0;
    num = edit_report_page (edit_report_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_of_exist_report_for_delete (void){
    struct IsDeleted isdel[100];
    int num = 0; 
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    FILE *delete_data = fopen ("IsDeleted.dat","rb");   
    while (1 > 0){
        fread (&isdel[num], sizeof(struct IsDeleted), 1, delete_data);
        if (feof(delete_data)){
            break;
        }
        if (strcmp (isdel[num].user_name, user_name_save) == 0){
            if (isdel[num].is_deleted == 0){
                exist_num++;
            }
            if (isdel[num].is_deleted == 1){
                exist_num--;
            }
        }
        num++;
    } 
    fclose (delete_data);    
    return exist_num;
}
int is_report_deleted (int report_code_for_read){
    struct IsDeleted isdel[100];
    int num = 0;
    FILE *delete_data = fopen ("IsDeleted.dat","rb");
    while (1 > 0){
        fread (&isdel[num], sizeof(struct IsDeleted), 1, delete_data);
        if (feof(delete_data)){
            break;
        }
        if (isdel[num].ReportCode == report_code_for_read){
            if (isdel[num].is_deleted == 1){
                fclose (delete_data);
                return 1;
            }
        }
        num++;
    }
    fclose (delete_data);
    return 0;
}
int get_report_code_for_delete (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    struct IsDeleted isdel[100];
    num_of_nth_report--;
    FILE *delete_data = fopen ("IsDeleted.dat","rb");
    while (1 > 0){
        fread (&isdel[num], sizeof(struct IsDeleted), 1, delete_data);
        if (feof(delete_data)){
            break;
        }
        if (strcmp (isdel[num].user_name, user_name_save) == 0){
            if (is_report_deleted (isdel[num].ReportCode) == 0){
                if (num_of_nth_report == exist_num){
                    report_code_for_read = isdel[num].ReportCode;
                    fclose (delete_data);
                    return report_code_for_read;
                }
                else {
                    exist_num++;
                }
            }
        }
        num++;
    } 
    fclose (delete_data);
    return -1;
}
int which_num_is_for_report_code (int report_code_for_read){
    struct report rpt[100];
    int num = 0;
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[num], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        } 
        if (rpt[num].num_of_report == report_code_for_read){
            fclose (report_data);
            return num;
        } 
        num++;  
    }
    fclose (report_data);
    return -1;
}
void create_delete_report_page (WINDOW *delete_report_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    delete_report_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (delete_report_win, 0, 0);
    wrefresh (delete_report_win);    
}
void printer_for_delete_report_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," delete report page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/delete report page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 8,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 10,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 7,x_start + 1," Title :");
    mvprintw (y_start + 9,x_start + 1," Registered Time :");
    attroff (COLOR_PAIR (5));
}
void printer_error_for_delete_reports_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," delete report page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/delete report page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 13," There is no report to delete !");
    attroff (COLOR_PAIR (5));
}
void printer_for_delete_report_in_menu (int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    printer_for_delete_report_page();
    int report_code_for_read = get_report_code_for_delete (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = num_of_report_for_read;
    char Title[30];
    char year[5];
    char mounth[3];
    char day[3]; 
    char hour[3];
    char minute[3];
    char second[3];
    read_report_from_file_for_Inbox_people (num, Title, year, mounth, day, hour, minute, second);
    mvprintw (y_start + 7,x_start + 9,"%s", Title);
    mvprintw (y_start + 9,x_start + 19, "%s/%s/%s-%s:%s:%s", year, mounth, day, hour, minute, second);
}
int which_report_is_going_to_delete (WINDOW *delete_report_win){
    char key;
    int num = 1;
    printer_for_delete_report_in_menu (1);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (delete_report_win);
        create_delete_report_page (delete_report_win);
        num = controlle_menu (key, counter_of_exist_report_for_delete (), num);
        printer_for_delete_report_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void print_are_you_sure_state_1 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 20,x_start + 27," Yes ");
    attron (COLOR_PAIR (2));
    attron (COLOR_PAIR (1)); 
    mvprintw (y_start + 22,x_start + 27,"  No "); 
    attron (COLOR_PAIR (1));  
}
void print_are_you_sure_state_2 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 20,x_start + 27," Yes ");
    attron (COLOR_PAIR (1));
    attron (COLOR_PAIR (2)); 
    mvprintw (y_start + 22,x_start + 27,"  No "); 
    attron (COLOR_PAIR (2));  
}
void printer_for_are_you_sure_for_delete (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 18,x_start + 11," Are you sure to delete this report ? ");
    attron (COLOR_PAIR (1));
    switch (num){
        case 1:
        print_are_you_sure_state_1 ();
        break;
        case 2:
        print_are_you_sure_state_2 ();
        break;
    }
}
int Are_you_sure_for_delete (void){
    char key;
    int num = 1;
    printer_for_are_you_sure_for_delete (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 2, num);
        printer_for_are_you_sure_for_delete (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void delete_reports (int num_of_nth_report){
    struct IsDeleted isdel[100];
    int num = counter_of_num ();
    isdel[num].num = num;
    isdel[num].ReportCode = get_report_code_for_delete (num_of_nth_report);
    isdel[num].is_deleted = 1;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    strcpy (isdel[num].user_name, user_name_save);
    FILE *delete_data = fopen ("IsDeleted.dat","ab");
    fwrite (&isdel[num], sizeof(struct IsDeleted), 1, delete_data);
    fclose (delete_data);
}
int delete_report_page (WINDOW *delete_report_win){
    int num = 0;
    if (counter_of_exist_report_for_delete () == 0){
        printer_error_for_delete_reports_page ();
        getch();
    }
    else {
        num = which_report_is_going_to_delete (delete_report_win);
        if (Are_you_sure_for_delete () == 1){
            delete_reports (num);
        } 
    } 
    clear();
    refresh();
    delwin (delete_report_win);
    return 100;
}
int delete_report (WINDOW *delete_report_win){
    int num = 0;
    create_delete_report_page (delete_report_win);
    num = delete_report_page (delete_report_win);
    return num;
}
//----------------------------------------------------------------------------------
void get_title_of_report (char *title_for_search){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *title_data = fopen ("RelatedTitle.txt","r");   
    if (title_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
    }
    while (fscanf (title_data, "%s", title_for_search) != EOF);
    fclose (title_data);    
}
int save_title_of_report (char *title_for_search){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    FILE *title_data = fopen ("RelatedTitle.txt","w");   
    if (title_data == NULL){
        mvprintw (y_start + 20,x_start + 9, "Erorr your file address isnt clear!");
        getch();
        return 504; 
    }
    fprintf (title_data,"%s",title_for_search);
    fclose (title_data);
    return 0;
}
int counter_of_exist_report_for_related (void){
    struct report rpt[100];
    int num = 0; 
    int exist_num = 0;
    char title_for_search[30];
    get_title_of_report (title_for_search);
    FILE *report_data = fopen ("Reports.dat","rb");   
    while (1 > 0){
        fread (&rpt[num], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        }
        if (strcmp (rpt[num].Title, title_for_search) == 0){
            if (is_report_deleted (rpt[num].num_of_report) == 0){
                exist_num++;
            }
        }
        num++;
    } 
    fclose (report_data);    
    return exist_num;
}
int get_report_code_for_related_reports (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    char title_for_search[30];
    get_title_of_report (title_for_search);
    struct report rpt[100];
    num_of_nth_report--;
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[num], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        }
        if (strcmp (rpt[num].Title, title_for_search) == 0){
            if (is_report_deleted (rpt[num].num_of_report) == 0){
                if (num_of_nth_report == exist_num){
                    report_code_for_read = rpt[num].num_of_report;
                    fclose (report_data);
                    return report_code_for_read;
                }
                else {
                    exist_num++;
                }
            }
        }
        num++;
    } 
    fclose (report_data);
    return -1;
}
void create_show_related_reports_page (WINDOW *show_related_reports_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    show_related_reports_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (show_related_reports_win, 0, 0);
    wrefresh (show_related_reports_win);    
}
void printer_for_related_reports_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," show related reports page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/show related reports page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 8,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 10,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 12,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 7,x_start + 1," Title :");
    mvprintw (y_start + 9,x_start + 1," Registered Time :");
    mvprintw (y_start + 11,x_start + 1," user name :");
    attroff (COLOR_PAIR (5));
}
void printer_for_related_reports_page_2(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," show related reports page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/show related reports page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 8,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 7,x_start + 1," Title search :");
    attroff (COLOR_PAIR (5));
}
void printer_error_for_related_reports_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," show related reports page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/show related reports page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 7,x_start + 1," Nothing Found :");
    attroff (COLOR_PAIR (5));
}
void printer_for_related_report_in_menu (int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    printer_for_related_reports_page();
    int report_code_for_read = get_report_code_for_related_reports (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = num_of_report_for_read;
    int counter = 0;
    int err = 1;
    struct report rpt[100];
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        err = fread (&rpt[counter], sizeof(struct report), 1, report_data);
        if (err == 0){
            mvprintw (y_start + 13,x_start + 9,"bad");
            break;
        }
        if (feof(report_data)){
            break;
        } 
        if (num == counter){
            mvprintw (y_start + 7,x_start + 9,"%s",rpt[num].Title);
            mvprintw (y_start + 9,x_start + 19, "%s/%s/%s-%s:%s:%s", rpt[num].year, rpt[num].mounth,
            rpt[num].day, rpt[num].hour, rpt[num].minute, rpt[num].second);
            mvprintw (y_start + 11,x_start + 13,"%s",rpt[num].user_name);
            break;
        } 
        counter++;  
    }
    fclose (report_data);
}
int which_report_is_going_to_show (WINDOW *show_related_reports_win){
    char key;
    int num = 1;
    printer_for_related_report_in_menu (1);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (show_related_reports_win);
        create_show_related_reports_page (show_related_reports_win);
        num = controlle_menu (key, counter_of_exist_report_for_related (), num);
        printer_for_related_report_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void get_string_from_user (WINDOW *show_related_reports_win, char *title_for_search){
    printer_for_related_reports_page_2();
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    text_on();
    mvgetnstr (y_start + 7,x_start + 16,title_for_search, 30);
    text_off();
    clear();
    refresh();
    delwin (show_related_reports_win);
    create_show_related_reports_page (show_related_reports_win);
}
int show_related_reports_page (WINDOW *show_related_reports_win){
    char title_for_search[30];
    get_string_from_user (show_related_reports_win, title_for_search);
    save_title_of_report (title_for_search);
    if (counter_of_exist_report_for_related () == 0){
        printer_error_for_related_reports_page ();
        getch();
    }
    else {
        which_report_is_going_to_show (show_related_reports_win);
    }
    clear();
    refresh();
    delwin (show_related_reports_win);
    return 100;
}
int show_related_reports (WINDOW *show_related_reports_win){
    int num = 0;
    create_show_related_reports_page (show_related_reports_win);
    num = show_related_reports_page (show_related_reports_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_of_exist_report_for_important (void){
    struct ImportantReport imprpt[100];
    int num = 0; 
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    FILE *important_data = fopen ("ImportantReport.dat","rb");   
    while (1 > 0){
        fread (&imprpt[num], sizeof(struct ImportantReport), 1, important_data);
        if (feof(important_data)){
            break;
        }
        if (strcmp (imprpt[num].user_name, user_name_save) == 0){
            if (is_report_deleted (imprpt[num].ReportCode) == 0){
                if (imprpt[num].important_report == 0){
                    // 0 means report is not important
                    exist_num++;
                }
                if (imprpt[num].important_report == 1){
                    //1 means report is important
                    exist_num--;
                }
            }
        }
        num++;
    } 
    fclose (important_data);    
    return exist_num;
}
int is_report_important (int report_code_for_read){
    struct ImportantReport imprpt[100];
    int num = 0;
    FILE *important_data = fopen ("ImportantReport.dat","rb");
    while (1 > 0){
        fread (&imprpt[num], sizeof(struct ImportantReport), 1, important_data);
        if (feof(important_data)){
            break;
        }
        if (imprpt[num].ReportCode == report_code_for_read){
            if (imprpt[num].important_report == 1){
                fclose (important_data);
                return 1;
            }
        }
        num++;
    }
    fclose (important_data);
    return 0;
}
int get_report_code_for_important (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    struct ImportantReport imprpt[100];
    num_of_nth_report--;
    FILE *important_data = fopen ("ImportantReport.dat","rb");
    while (1 > 0){
        fread (&imprpt[num], sizeof(struct ImportantReport), 1, important_data);
        if (feof(important_data)){
            break;
        }
        if (strcmp (imprpt[num].user_name, user_name_save) == 0){
            if (is_report_deleted (imprpt[num].ReportCode) == 0){
                if (is_report_important (imprpt[num].ReportCode) == 0){
                    if (num_of_nth_report == exist_num){
                        report_code_for_read = imprpt[num].ReportCode;
                        fclose (important_data);
                        return report_code_for_read;
                    }
                    else {
                        exist_num++;
                    }
                }
            }
        }
        num++;
    } 
    fclose (important_data);
    return -1;
}
void create_important_reports_page (WINDOW *important_reports_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    important_reports_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (important_reports_win, 0, 0);
    wrefresh (important_reports_win);    
}
void printer_for_important_reports_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 17," important reports page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/important reports page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 8,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 10,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 7,x_start + 1," Title :");
    mvprintw (y_start + 9,x_start + 1," Registered Time :");
    attroff (COLOR_PAIR (5));
}
void printer_error_for_important_reports_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 17," important reports page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/important reports page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3)); 
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 11," There is no report to important it ! ");
    attroff (COLOR_PAIR (5));   
}
void printer_for_important_report_in_menu (int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    printer_for_important_reports_page();
    int report_code_for_read = get_report_code_for_important (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = num_of_report_for_read;
    int counter = 0;
    int err = 1;
    struct report rpt[100];
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        err = fread (&rpt[counter], sizeof(struct report), 1, report_data);
        if (err == 0){
            mvprintw (y_start + 13,x_start + 9,"bad");
            break;
        }
        if (feof(report_data)){
            break;
        } 
        if (num == counter){
            mvprintw (y_start + 7,x_start + 9,"%s",rpt[num].Title);
            mvprintw (y_start + 9,x_start + 19, "%s/%s/%s-%s:%s:%s", rpt[num].year, rpt[num].mounth,
            rpt[num].day, rpt[num].hour, rpt[num].minute, rpt[num].second);
            break;
        } 
        counter++;  
    }
    fclose (report_data);
}
int which_report_is_going_to_important (WINDOW *important_reports_win){
    char key;
    int num = 1;
    printer_for_important_report_in_menu (1);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (important_reports_win);
        create_important_reports_page (important_reports_win);
        num = controlle_menu (key, counter_of_exist_report_for_important (), num);
        printer_for_important_report_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void printer_for_are_you_sure_for_important (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 18,x_start + 10," Are you sure to important this report ? ");
    attron (COLOR_PAIR (1));
    switch (num){
        case 1:
        print_are_you_sure_state_1 ();
        break;
        case 2:
        print_are_you_sure_state_2 ();
        break;
    }
}
int Are_you_sure_for_important (void){
    char key;
    int num = 1;
    printer_for_are_you_sure_for_important (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 2, num);
        printer_for_are_you_sure_for_important (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void important_reports (int num_of_nth_report){
    struct ImportantReport imprpt[100];
    int num = counter_of_important ();
    imprpt[num].num_of_important = num;
    imprpt[num].ReportCode = get_report_code_for_important (num_of_nth_report);
    imprpt[num].important_report = 1;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    strcpy (imprpt[num].user_name, user_name_save);
    FILE *important_data = fopen ("ImportantReport.dat","ab");
    fwrite (&imprpt[num], sizeof(struct ImportantReport), 1, important_data);
    fclose (important_data);
}
int important_reports_page (WINDOW *important_reports_win){ 
    int num = 0;
    if (counter_of_exist_report_for_important () == 0){
        printer_error_for_important_reports_page ();
        getch();
    }
    else {
        num = which_report_is_going_to_important (important_reports_win);
        if (Are_you_sure_for_important () == 1){
            important_reports (num);
        } 
    } 
    clear();
    refresh();
    delwin (important_reports_win);
    return 100;
}
int important_report (WINDOW *important_reports_win){
    int num = 0;
    create_important_reports_page (important_reports_win);
    num = important_reports_page (important_reports_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_buy_VIP_page (WINDOW *buy_VIP_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    buy_VIP_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (buy_VIP_win, 0, 0);
    wrefresh (buy_VIP_win);    
}
void printer_for_buy_VIP_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," buy VIP page ");
    mvprintw (y_start + 1,x_start + 1,"Log in people/people menu page/buy VIP page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int buy_VIP_page (WINDOW *buy_VIP_win){
    clear();
    refresh();
    delwin (buy_VIP_win);
    return 100;
}
int buy_VIP (WINDOW *buy_VIP_win){
    int num = 0;
    create_buy_VIP_page (buy_VIP_win);
    printer_for_buy_VIP_page();
    getch();
    num = buy_VIP_page (buy_VIP_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_of_exist_report_for_show_in_Inbox (void){
    struct Reception rpio[100];
    int num = 0; 
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    FILE *reception_data = fopen ("Reception.dat","rb");   
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (strcmp (user_name_save, rpio[num].user_name) == 0){
                if (rpio[num].status == 2){
                    exist_num++;
                }
                if (rpio[num].status == 1 || rpio[num].status == 0){
                    exist_num--;
                }
            }
        }
        num++;
    } 
    fclose (reception_data);    
    return exist_num;
}
int get_report_code_for_Inbox_people (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    struct Reception rpio[100];
    num_of_nth_report--;
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (strcmp (user_name_save, rpio[num].user_name) == 0){
                if (is_report_answered (rpio[num].ReportCode) == 0){
                    if (num_of_nth_report == exist_num){
                        report_code_for_read = rpio[num].ReportCode;
                        fclose (reception_data);
                        return report_code_for_read;
                    }
                    else {
                        exist_num++;
                    }
                }
            }
        }
        num++;
    } 
    fclose (reception_data);
    return -1;
}
void create_Inbox_for_people_page (WINDOW *Inbox_for_people_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    Inbox_for_people_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (Inbox_for_people_win, 0, 0);
    wrefresh (Inbox_for_people_win);    
}
void printer_for_Inbox_people_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 23," Inbox page ");
    mvprintw (y_start + 1,x_start + 1,"people menu page/cardboard for people page/Inbox page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 13 , x_start + 1," Time :");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 15, x_start + 1," status : not answered yet");
    attroff (COLOR_PAIR (6));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 11, x_start + 1," Title : ");
    attroff (COLOR_PAIR (5));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 10 , x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 12, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 14, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 16, x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
}
void printer_error_for_Inbox_people_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 23," Inbox page ");
    mvprintw (y_start + 1,x_start + 1,"people menu page/cardboard for people page/Inbox page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 14," There is no report to see !");
    attroff (COLOR_PAIR (5));
    getch();
}
void read_report_from_file_for_Inbox_people (int num, char *Title, char *year, char *mounth, char *day,
char *hour, char *minute, char *second){
    int counter = 0;
    struct report rpt[100];
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[counter], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        } 
        if (num == rpt[num].num_of_report){
            strcpy (Title, rpt[num].Title);
            strcpy (year, rpt[num].year);
            strcpy (mounth, rpt[num].mounth);
            strcpy (day, rpt[num].day);
            strcpy (hour, rpt[num].hour);
            strcpy (minute, rpt[num].minute);
            strcpy (second, rpt[num].second);
            break;
        } 
        counter++;  
    }
    fclose (report_data);
}
void printer_for_Inbox_people_in_menu (int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    printer_for_Inbox_people_page();
    int report_code_for_read = get_report_code_for_Inbox_people (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = num_of_report_for_read;
    char Title[30];
    char year[5];
    char mounth[3];
    char day[3]; 
    char hour[3];
    char minute[3];
    char second[3];
    read_report_from_file_for_Inbox_people (num, Title, year, mounth, day,hour, minute, second);
    mvprintw (y_start + 11,x_start + 9,"%s",Title);
    mvprintw (y_start + 13,x_start + 9, "%s/%s/%s-%s:%s:%s", year, mounth,day, hour, minute, second);
}
int which_report_is_going_to_show_Ibox (WINDOW *Inbox_for_people_win){
    char key;
    int num = 1;
    printer_for_Inbox_people_in_menu (1);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (Inbox_for_people_win);
        create_Inbox_for_people_page (Inbox_for_people_win);
        num = controlle_menu (key, counter_of_exist_report_for_show_in_Inbox (), num);
        printer_for_Inbox_people_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
int Inbox_for_people_page (WINDOW *Inbox_for_people_win){
    int num = 0;
    if (counter_of_exist_report_for_show_in_Inbox () == 0){
        printer_error_for_Inbox_people_page ();
    }
    else {
        which_report_is_going_to_show_Ibox (Inbox_for_people_win);
    }
    clear();
    refresh();
    delwin (Inbox_for_people_win);
    return 101;
}
int Inbox_for_people (WINDOW *Inbox_for_people_win){
    int num = 0;
    create_Inbox_for_people_page (Inbox_for_people_win);
    num = Inbox_for_people_page (Inbox_for_people_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_of_exist_report_for_show_in_History (void){
    struct Reception rpio[100];
    int num = 0; 
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    FILE *reception_data = fopen ("Reception.dat","rb");   
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (rpio[num].status == 1 || rpio[num].status == 0){
                if (strcmp (user_name_save, rpio[num].user_name) == 0){
                    exist_num++;
                }
            }
        }
        num++;
    } 
    fclose (reception_data);    
    return exist_num;
}
int get_report_code_for_answered_History (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    struct Reception rpio[100];
    num_of_nth_report--;
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (rpio[num].status == 1 || rpio[num].status == 0){
                if (strcmp (user_name_save, rpio[num].user_name) == 0){
                    if (num_of_nth_report == exist_num){
                        report_code_for_read = rpio[num].ReportCode;
                        fclose (reception_data);
                        return report_code_for_read;
                    }
                    else {
                        exist_num++;
                    }
                }
            }
        }
        num++;
    } 
    fclose (reception_data);
    return -1;
}
void create_History_for_people_page (WINDOW *History_for_people_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    History_for_people_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (History_for_people_win, 0, 0);
    wrefresh (History_for_people_win);    
}
void printer_for_History_people_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," History page ");
    mvprintw (y_start + 1,x_start + 1,"people menu page/cardboard for people page/History page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 13 , x_start + 1," Time :");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 15, x_start + 1," status : ");
    attroff (COLOR_PAIR (6));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 11, x_start + 1," Title : ");
    attroff (COLOR_PAIR (5));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 10 , x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 12, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 14, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 16, x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
}
void printer_error_for_History_people_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," History page ");
    mvprintw (y_start + 1,x_start + 1,"people menu page/cardboard for people page/History page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 10," There is no report answered to see  !");
    attroff (COLOR_PAIR (5));
    getch();
}
void read_report_from_file_for_History_people (int num, char *Title){
    int counter = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    struct report rpt[100];
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[counter], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        } 
        if (num == rpt[num].num_of_report){
            if (strcmp (user_name_save, rpt[num].user_name) == 0){
                strcpy (Title, rpt[num].Title);
                break;
            }
        } 
        counter++;  
    }
    fclose (report_data);
}
int read_status_from_file_History (int report_code_for_read,char *status, char *year, char *mounth, char *day,
char *hour, char *minute, char *second){
    int num = 0;
    char user_name_save[20];
    get_login_name_of_people (user_name_save);
    struct Reception rpio[100];
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (rpio[num].status == 1 || rpio[num].status == 0){
                if (strcmp (user_name_save, rpio[num].user_name) == 0){
                    if (report_code_for_read == rpio[num].ReportCode){
                        switch (rpio[num].status){
                            case 0:
                            strcpy (status,"Decline");
                            break;
                            case 1:
                            strcpy (status,"Accept");
                            break;
                        }
                        strcpy (year, rpio[num].year);
                        strcpy (mounth, rpio[num].mounth);
                        strcpy (day, rpio[num].day);
                        strcpy (hour, rpio[num].hour);
                        strcpy (minute, rpio[num].minute);
                        strcpy (second, rpio[num].second);
                        fclose (reception_data);
                        return rpio[num].status;
                    }
                }
            }
        }
        num++;
    } 
    fclose (reception_data);
    return -1;
}
void printer_for_History_people_in_menu (int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    printer_for_History_people_page();
    int report_code_for_read = get_report_code_for_answered_History (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = num_of_report_for_read;
    char Title[30];
    char status[10];
    char year[5];
    char mounth[3];
    char day[3]; 
    char hour[3];
    char minute[3];
    char second[3];
    read_report_from_file_for_History_people (num, Title);
    read_status_from_file_History (num, status, year, mounth,day, hour, minute, second);
    mvprintw (y_start + 11,x_start + 9,"%s",Title);
    mvprintw (y_start + 15,x_start + 9, "%s",status);
    mvprintw (y_start + 13,x_start + 9, "%s/%s/%s-%s:%s:%s", year, mounth,day, hour, minute, second);
}
int which_report_is_going_to_show_History (WINDOW *History_for_people_win){
    char key;
    int num = 1;
    printer_for_History_people_in_menu (1);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (History_for_people_win);
        create_History_for_people_page (History_for_people_win);
        num = controlle_menu (key, counter_of_exist_report_for_show_in_History (), num);
        printer_for_History_people_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
int History_for_people_page (WINDOW *History_for_people_win){
    int num = 0;
    if (counter_of_exist_report_for_show_in_History () == 0){
        printer_error_for_History_people_page ();
    }
    else {
        which_report_is_going_to_show_History (History_for_people_win);
    }
    clear();
    refresh();
    delwin (History_for_people_win);
    return 101;
}
int History_for_people (WINDOW *History_for_people_win){
    int num = 0;
    create_History_for_people_page (History_for_people_win);
    num = History_for_people_page (History_for_people_win);
    return num;
}
//----------------------------------------------------------------------------------
void create_cardboard_for_legal_page (WINDOW *cardboard_for_legal_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    cardboard_for_legal_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (cardboard_for_legal_win, 0, 0);
    wrefresh (cardboard_for_legal_win);    
}
void printer_for_cardboard_legal_page(int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 21," cardboard page ");
    mvprintw (y_start + 1,x_start + 1,"Log in legal/legal menu page/cardboard for legal page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    switch (num){
        case 1:
        print_in_cardboard_menu_state_1 ();
        break;
        case 2:
        print_in_cardboard_menu_state_2 ();
        break;
        case 3:
        print_in_cardboard_menu_state_3 ();
        break;
    }
}
int cardboard_for_legal (WINDOW *cardboard_for_legal_win){
    char key;
    int num = 1;
    create_cardboard_for_legal_page (cardboard_for_legal_win);
    printer_for_cardboard_legal_page (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 3, num);
        printer_for_cardboard_legal_page (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    num = num + 310;
    if (num == 313){
        num = 300;
    }
    clear();
    refresh();
    delwin (cardboard_for_legal_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_of_exist_report_for_reception (void){
    struct Reception rpio[100];
    int num = 0; 
    int exist_num = 0;
    FILE *reception_data = fopen ("Reception.dat","rb");   
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (rpio[num].status == 2){
                exist_num++;
            }
            if (rpio[num].status == 1 || rpio[num].status == 0){
                exist_num--;
            }
        }
        num++;
    } 
    fclose (reception_data);    
    return exist_num;
}
int counter_of_exist_report_for_reception_and_important (void){
    struct Reception rpio[100];
    int num = 0; 
    int exist_num = 0;
    FILE *reception_data = fopen ("Reception.dat","rb");   
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (is_report_important (rpio[num].ReportCode) == 1){
                if (rpio[num].status == 2){
                    exist_num++;
                }
                if (rpio[num].status == 1 || rpio[num].status == 0){
                    exist_num--;
                }
            }
        }
        num++;
    } 
    fclose (reception_data);    
    return exist_num;
}
int is_report_answered (int report_code_for_read){
    struct Reception rpio[100];
    int num = 0;
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (rpio[num].ReportCode == report_code_for_read){
            if (is_report_deleted (rpio[num].ReportCode) == 0){
                if (rpio[num].status == 1 || rpio[num].status == 0){
                    fclose (reception_data);
                    return 1;
                }
            }
        }
        num++;
    }
    fclose (reception_data);
    return 0;
}
int get_report_code_for_reception_important (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    struct Reception rpio[100];
    num_of_nth_report--;
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (is_report_important (rpio[num].ReportCode) == 1){
                if (is_report_answered (rpio[num].ReportCode) == 0){
                    if (num_of_nth_report == exist_num){
                        report_code_for_read = rpio[num].ReportCode;
                        fclose (reception_data);
                        return report_code_for_read;
                    }
                    else {
                        exist_num++;
                    }
                }
            }
        }
        num++;
    } 
    fclose (reception_data);
    return -1;
}
int get_report_code_for_reception_not_important (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    struct Reception rpio[100];
    num_of_nth_report--;
    num_of_nth_report = num_of_nth_report - counter_of_exist_report_for_reception_and_important();
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (is_report_important (rpio[num].ReportCode) == 0){
                if (is_report_answered (rpio[num].ReportCode) == 0){
                    if (num_of_nth_report == exist_num){
                        report_code_for_read = rpio[num].ReportCode;
                        fclose (reception_data);
                        return report_code_for_read;
                    }
                    else {
                        exist_num++;
                    }
                }
            }
        }
        num++;
    } 
    fclose (reception_data);
    return -1;
}
int get_report_code_for_reception (int num_of_nth_report){
    int result = get_report_code_for_reception_important (num_of_nth_report);
    if (result != -1){
        return result;
    }
    result = get_report_code_for_reception_not_important(num_of_nth_report);
    return result;
}
void get_nth_user_name_for_Inbox_legal (int num_of_nth_report, char *user_name_save){
    int report_code = 0;
    report_code = get_report_code_for_reception (num_of_nth_report);
    int num = 0;
    struct report rpt[100];
    FILE *report_data = fopen ("Reports.dat","rb");
    while (1 > 0){
        fread (&rpt[num], sizeof(struct report), 1, report_data);
        if (feof(report_data)){
            break;
        }
        if (report_code == rpt[num].num_of_report){
            strcpy (user_name_save, rpt[num].user_name);
        }
        num++;
    } 
    fclose (report_data);
}
void create_Inbox_for_legal_page (WINDOW *Inbox_for_legal_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    Inbox_for_legal_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (Inbox_for_legal_win, 0, 0);
    wrefresh (Inbox_for_legal_win);    
}
void create_write_page_for_Inbox_legal (WINDOW *write_win_Inbox_legal){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    write_win_Inbox_legal = newwin (23, 58, y_start + 1, x_start + 1);
    refresh();    
}
void printer_for_Inbox_legal_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 23," Inbox page ");
    mvprintw (y_start + 1,x_start + 1,"legal menu page/cardboard for legal page/Inbox page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 7 , x_start + 1," Decription :");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 17, x_start + 1," Place of crime :");
    mvprintw (y_start + 19, x_start + 1," National code :");
    attroff (COLOR_PAIR (6));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 5, x_start + 1," Title : ");
    attroff (COLOR_PAIR (5));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6 , x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 16, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 18, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 20, x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
}
void printer_error_for_Inbox_legal_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 23," Inbox page ");
    mvprintw (y_start + 1,x_start + 1,"legal menu page/cardboard for legal page/Inbox page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 13," There is no report to answer !");
    attroff (COLOR_PAIR (5));
}
void printer_for_answer_report (WINDOW *write_win){
    wattron (write_win,COLOR_PAIR (3));
    mvwprintw (write_win,3,22," Inbox page ");
    mvwprintw (write_win,0,0,"legal menu page/cardboard for legal page/Inbox page/");
    mvwprintw (write_win,1,0,"__________________________________________________________");
    wattroff (write_win,COLOR_PAIR (3));
    wattron (write_win, COLOR_PAIR (5));
    mvwprintw (write_win, 7, 0," Reason : ");
    wattroff (write_win, COLOR_PAIR (5));
    wattron (write_win, COLOR_PAIR (4));
    mvwprintw (write_win, 6, 0,"__________________________________________________________");
    mvwprintw (write_win, 10, 0,"__________________________________________________________");
    wattroff (write_win, COLOR_PAIR (4));
    refresh(); 
    wrefresh (write_win);
}

void printer_for_Inbox_legal_in_menu (int num_of_nth_report, WINDOW *Inbox_for_legal_win, WINDOW *write_win_Inbox_legal){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    Inbox_for_legal_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (Inbox_for_legal_win, 0, 0);
    wrefresh (Inbox_for_legal_win);
    write_win_Inbox_legal = newwin (23, 58, y_start + 1, x_start + 1);
    refresh ();  
    wrefresh(write_win_Inbox_legal);
    printer_for_Inbox_legal_page();
    int report_code_for_read = get_report_code_for_reception (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = report_code_for_read;
    char Title[30];
    char Discription[530];
    char PlaceOfCrime[40];
    char NationalCode[10];
    read_report_from_file (num, Title, Discription,PlaceOfCrime, NationalCode);
    mvwprintw (write_win_Inbox_legal,  4, 9,"%s",Title);
    mvwprintw (write_win_Inbox_legal,  6, 14,"%s",Discription);
    mvwprintw (write_win_Inbox_legal, 16, 18, "%s",PlaceOfCrime);
    mvwprintw (write_win_Inbox_legal, 18, 17,"%d",NationalCode);
    refresh();
    wrefresh (write_win_Inbox_legal);
    refresh();
}
int which_report_is_going_to_answer (WINDOW *Inbox_for_legal_win, WINDOW *write_win_Inbox_legal){
    create_Inbox_for_legal_page (Inbox_for_legal_win);
    create_write_page_for_Inbox_legal (write_win_Inbox_legal);
    char key;
    int num = 1;
    printer_for_Inbox_legal_in_menu (1, Inbox_for_legal_win, write_win_Inbox_legal);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (Inbox_for_legal_win);
        delwin (write_win_Inbox_legal);
        num = controlle_menu (key, counter_of_exist_report_for_reception (), num);
        printer_for_Inbox_legal_in_menu (num, Inbox_for_legal_win, write_win_Inbox_legal);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void print_what_want_state_1 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 21,x_start + 35,"  Accept ");
    attron (COLOR_PAIR (2));
    attron (COLOR_PAIR (1)); 
    mvprintw (y_start + 22,x_start + 35," Decline "); 
    mvprintw (y_start + 23,x_start + 35,"  Cancel ");
    attron (COLOR_PAIR (1));  
}
void print_what_want_state_2 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 22,x_start + 35," Decline ");
    attron (COLOR_PAIR (2));
    attron (COLOR_PAIR (1)); 
    mvprintw (y_start + 21,x_start + 35,"  Accept ");
    mvprintw (y_start + 23,x_start + 35,"  Cancel ");
    attron (COLOR_PAIR (1));  
}
void print_what_want_state_3 (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (2));
    mvprintw (y_start + 23,x_start + 35,"  Cancel ");
    attron (COLOR_PAIR (2));
    attron (COLOR_PAIR (1)); 
    mvprintw (y_start + 21,x_start + 35,"  Accept "); 
    mvprintw (y_start + 22,x_start + 35," Decline ");
    attron (COLOR_PAIR (1));  
}
void printer_for_what_do_you_want (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 22,x_start + 1," what do you want to do ? ");
    attron (COLOR_PAIR (1));
    switch (num){
        case 1:
        print_what_want_state_1 ();
        break;
        case 2:
        print_what_want_state_2 ();
        break;
        case 3:
        print_what_want_state_3 ();
        break;
    }
}
int what_do_you_want (void){
    char key;
    int num = 1;
    printer_for_what_do_you_want (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 3, num);
        printer_for_what_do_you_want (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void accept_reports (int num_of_nth_report){
    struct Reception rpio[100];
    int num_of_reception = 0;
    int report_code = 0;
    char year[5], mounth[3], day[3];
    char hour[3], minute[3], second[3];
    get_time_of_year (year, mounth, day);
    get_time_of_hour (hour, minute, second);
    char user_name_save[20];
    num_of_reception = counter_of_reception ();
    report_code = get_report_code_for_reception (num_of_nth_report);
    get_nth_user_name_for_Inbox_legal (num_of_nth_report, user_name_save);
    strcpy (rpio[num_of_reception].user_name, user_name_save);
    strcpy (rpio[num_of_reception].year, year);
    strcpy (rpio[num_of_reception].mounth, mounth);
    strcpy (rpio[num_of_reception].day, day);
    strcpy (rpio[num_of_reception].hour, hour);
    strcpy (rpio[num_of_reception].minute, minute);
    strcpy (rpio[num_of_reception].second, second);
    rpio[num_of_reception].status = 1;
    rpio[num_of_reception].ReportCode = report_code;
    rpio[num_of_reception].num_of_reception = num_of_reception;
    FILE *reception_data = fopen ("Reception.dat","ab");
    fwrite (&rpio[num_of_reception], sizeof(struct Reception), 1, reception_data);
    fclose (reception_data);
}
void get_string (char *reason, WINDOW *write_win_Inbox_legal){
    text_on();
    mvwgetnstr (write_win_Inbox_legal, 7, 10, reason, 160);
    text_off();
}
int end_of_getting_reason (WINDOW *report_new_crime_win, WINDOW *write_win){
    clear();
    refresh();
    delwin (report_new_crime_win);
    delwin (write_win);
    return 100;
}
void saveing_answer_of_report (char *Reason, int num_of_nth_report){
    struct Reception rpio[100];
    int num_of_reception = 0;
    int report_code = 0;
    char year[5], mounth[3], day[3];
    char hour[3], minute[3], second[3];
    get_time_of_year (year, mounth, day);
    get_time_of_hour (hour, minute, day);
    char user_name_save[20];
    num_of_reception = counter_of_reception ();
    report_code = get_report_code_for_reception (num_of_nth_report);
    get_nth_user_name_for_Inbox_legal (num_of_nth_report, user_name_save);
    strcpy (rpio[num_of_reception].user_name, user_name_save);
    strncpy (rpio[num_of_reception].reason,Reason,160);
    strcpy (rpio[num_of_reception].year, year);
    strcpy (rpio[num_of_reception].mounth, mounth);
    strcpy (rpio[num_of_reception].day, day);
    strcpy (rpio[num_of_reception].hour, hour);
    strcpy (rpio[num_of_reception].minute, minute);
    strcpy (rpio[num_of_reception].second, second);
    rpio[num_of_reception].status = 0;
    rpio[num_of_reception].ReportCode = report_code;
    rpio[num_of_reception].num_of_reception = num_of_reception;
    FILE *reception_data = fopen ("Reception.dat","ab");
    fwrite (&rpio[num_of_reception], sizeof(struct Reception), 1, reception_data);
    fclose (reception_data);
}
int decline_reports (WINDOW *Inbox_for_legal_win, int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    char Reason[160];
    int num = 0;
    WINDOW *write_win;
    create_Inbox_for_legal_page (Inbox_for_legal_win);
    write_win = newwin (23, 58, y_start + 1, x_start + 1);
    refresh();
    printer_for_answer_report (write_win);
    get_string (Reason , write_win);
    saveing_answer_of_report (Reason, num_of_nth_report);
    num = end_of_getting_reason (Inbox_for_legal_win, write_win);
    return num;
}
int Inbox_for_legal_page (WINDOW *Inbox_for_legal_win){
    WINDOW *write_win_Inbox_legal;
    int num = 0;
    int num2 = 0;
    if (counter_of_exist_report_for_reception () == 0){
        printer_error_for_Inbox_legal_page ();
        getch();
    }
    else {
        num = which_report_is_going_to_answer (Inbox_for_legal_win, write_win_Inbox_legal);
        num2 = what_do_you_want ();
        if (num2 == 1){
            accept_reports (num);
        } 
        else if (num2 == 2){
            decline_reports (Inbox_for_legal_win, num);
        }
    }
    clear();
    refresh();
    delwin (Inbox_for_legal_win);
    delwin (write_win_Inbox_legal);
    return 301;
}
int Inbox_for_legal (WINDOW *Inbox_for_legal_win){
    int num = 0;
    create_Inbox_for_legal_page (Inbox_for_legal_win);
    printer_for_Inbox_legal_page();
    num = Inbox_for_legal_page (Inbox_for_legal_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_of_exist_report_for_history (void){
    struct Reception rpio[100];
    int num = 0; 
    int exist_num = 0;
    FILE *reception_data = fopen ("Reception.dat","rb");   
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (rpio[num].status == 1 || rpio[num].status == 0){
                exist_num++;
            }
        }
        num++;
    } 
    fclose (reception_data);    
    return exist_num;
}
int get_report_code_for_answered (int num_of_nth_report){
    int report_code_for_read;
    int num = 0;
    int exist_num = 0;
    struct Reception rpio[100];
    num_of_nth_report--;
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (rpio[num].status == 1 || rpio[num].status == 0){
                if (num_of_nth_report == exist_num){
                    report_code_for_read = rpio[num].ReportCode;
                    fclose (reception_data);
                    return report_code_for_read;
                }
                else {
                    exist_num++;
                }
            }
        }
        num++;
    } 
    fclose (reception_data);
    return -1;
}
void create_History_for_legal_page (WINDOW *History_for_legal_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    History_for_legal_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (History_for_legal_win, 0, 0);
    wrefresh (History_for_legal_win);    
}
void create_write_page_for_History_legal (WINDOW *write_win_Hstory_legal){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    write_win_Hstory_legal = newwin (23, 58, y_start + 1, x_start + 1);
    refresh();    
}
void printer_for_History_legal_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 3,x_start + 22," History page ");
    mvprintw (y_start + 1,x_start + 1,"legal menu page/cardboard for legal page/History page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 6 , x_start + 1," Decription :");
    attroff (COLOR_PAIR (1));
    attron (COLOR_PAIR (6));
    mvprintw (y_start + 16, x_start + 1," Place of crime :");
    mvprintw (y_start + 18, x_start + 1," National code :");
    attroff (COLOR_PAIR (6));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 4, x_start + 1," Title : ");
    mvprintw (y_start + 20, x_start + 1," Status : ");
    mvprintw (y_start + 21, x_start + 1," Reason : ");
    attroff (COLOR_PAIR (5));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 5 , x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 15, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 17, x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 19, x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
}
void printer_error_for_History_legal_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 3,x_start + 22," History page ");
    mvprintw (y_start + 1,x_start + 1,"legal menu page/cardboard for legal page/History page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 10," There is no report answered to see  !");
    attroff (COLOR_PAIR (5));
    getch();
}
int read_answer_from_file (int report_code_for_read,char *status, char *Reason){
    int num = 0;
    int max_struct_saved = 0;
    struct Reception rpio[100];
    FILE *reception_data = fopen ("Reception.dat","rb");
    while (1 > 0){
        fread (&rpio[num], sizeof(struct Reception), 1, reception_data);
        if (feof(reception_data)){
            break;
        }
        if (is_report_deleted (rpio[num].ReportCode) == 0){
            if (rpio[num].status == 1 || rpio[num].status == 0){
                if (report_code_for_read == rpio[num].ReportCode){
                    strncpy (Reason, rpio[num].reason, 160);
                    switch (rpio[num].status){
                        case 0:
                        strcpy (status,"Decline");
                        break;
                        case 1:
                        strcpy (status,"Accept");
                        break;
                    }
                    fclose (reception_data);
                    return rpio[num].status;
                }
            }
        }
        num++;
    } 
    fclose (reception_data);
    return -1;
}
void printer_for_History_legal_in_menu (int num_of_nth_report, WINDOW *History_for_legal_win, WINDOW *write_win_History_legal){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    History_for_legal_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (History_for_legal_win, 0, 0);
    wrefresh (History_for_legal_win);
    write_win_History_legal = newwin (23, 58, y_start + 1, x_start + 1);
    refresh ();  
    wrefresh(write_win_History_legal);
    printer_for_History_legal_page();
    int report_code_for_read = get_report_code_for_answered (num_of_nth_report);
    int num_of_report_for_read = which_num_is_for_report_code (report_code_for_read);
    int num = num_of_report_for_read;
    char Title[30];
    char Discription[530];
    char PlaceOfCrime[40];
    char NationalCode[10];
    char Reason[160];
    char status[10];
    read_report_from_file (num, Title, Discription,PlaceOfCrime, NationalCode);
    int n = read_answer_from_file (num, status, Reason);
    mvwprintw (write_win_History_legal,  3, 9,"%s",Title);
    mvwprintw (write_win_History_legal,  5, 14,"%s",Discription);
    mvwprintw (write_win_History_legal, 15, 18, "%s",PlaceOfCrime);
    mvwprintw (write_win_History_legal, 17, 17,"%d",NationalCode);
    mvwprintw (write_win_History_legal, 19, 10, "%s",status);
    mvwprintw (write_win_History_legal, 20, 10,"%s",Reason);
    refresh();
    wrefresh (write_win_History_legal);
    refresh();
}
int which_report_is_going_to_shpw_in_History_legal_page (WINDOW *History_for_legal_win, WINDOW *write_win_History_legal){
    create_History_for_legal_page (History_for_legal_win);
    create_write_page_for_History_legal (write_win_History_legal);
    char key;
    int num = 1;
    printer_for_History_legal_in_menu (1, History_for_legal_win, write_win_History_legal);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (History_for_legal_win);
        delwin (write_win_History_legal);
        num = controlle_menu (key, counter_of_exist_report_for_history (), num);
        printer_for_History_legal_in_menu (num, History_for_legal_win, write_win_History_legal);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
int History_for_legal_page (WINDOW *History_for_legal_win){
    WINDOW *write_win_History_legal;
    if (counter_of_exist_report_for_history() == 0){
        printer_error_for_History_legal_page();
    }
    else {
        which_report_is_going_to_shpw_in_History_legal_page (History_for_legal_win, write_win_History_legal);
    }
    clear();
    refresh();
    delwin (History_for_legal_win);
    return 301;
}
int History_for_legal (WINDOW *History_for_legal_win){
    int num = 0;
    create_History_for_legal_page (History_for_legal_win);
    num = History_for_legal_page (History_for_legal_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_num_of_block (void){
    struct IsBlock isblk[100];
    int num_of_block = 0; 
    FILE *block_data = fopen ("IsBlocked.dat","rb");   
    while (1 > 0){
        fread (&isblk[num_of_block], sizeof(struct IsBlock), 1, block_data);
        if (feof(block_data)){
            break;
        }
        num_of_block++;
    } 
    fclose (block_data);    
    return num_of_block;
}
void saving_is_blocked (char *user_name_save){
    struct IsBlock isblk[100];
    int num = 0;
    num = counter_num_of_block (); 
    strcpy (isblk[num].user_name, user_name_save);
    isblk[num].is_block = 0;
    isblk[num].num_of_user = num;
    FILE *block_data = fopen ("IsBlocked.dat","ab");
    fwrite (&isblk[num], sizeof(struct IsBlock), 1, block_data);
    fclose (block_data);
}
int counter_of_exist_people_for_is_blocked (void){
    struct IsBlock isblk[100];
    int num = 0; 
    int exist_num = 0;
    FILE *block_data = fopen ("IsBlocked.dat","rb");   
    while (1 > 0){
        fread (&isblk[num], sizeof(struct IsBlock), 1, block_data);
        if (feof(block_data)){
            break;
        }
        if (isblk[num].is_block == 0){
            exist_num++;
        }
        if (isblk[num].is_block == 1){
            exist_num--;
        }
        num++;
    } 
    fclose (block_data);    
    return exist_num;
}
int is_people_blocked (char *user_name_save){
    struct IsBlock isblk[100];
    int num = 0;
    FILE *block_data = fopen ("IsBlocked.dat","rb");
    while (1 > 0){
        fread (&isblk[num], sizeof(struct IsBlock), 1, block_data);
        if (feof(block_data)){
            break;
        }
        if (strcmp (isblk[num].user_name , user_name_save) == 0){
            if (isblk[num].is_block == 1){
                fclose (block_data);
                return 1;
            }
        }
        num++;
    }
    fclose (block_data);
    return 0;
}
void get_nth_user_name_for_block (int num_of_nth_user, char *user_name_save){
    int num = 0;
    int exist_num = 0;
    struct IsBlock isblk[100];
    num_of_nth_user--;
    FILE *block_data = fopen ("IsBlocked.dat","rb");
    while (1 > 0){
        fread (&isblk[num], sizeof(struct IsBlock), 1, block_data);
        if (feof(block_data)){
            break;
        }
        if (is_people_blocked (isblk[num].user_name) == 0){
            if (num_of_nth_user == exist_num){
                strcpy (user_name_save, isblk[num].user_name);
                break;
            }
            else {
                exist_num++;
            }
        }
        num++;
    } 
    fclose (block_data);
}
void create_block_reporters_page (WINDOW *block_reporters_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    block_reporters_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (block_reporters_win, 0, 0);
    wrefresh (block_reporters_win);    
}
void printer_for_block_reporters_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," block reporters page ");
    mvprintw (y_start + 1,x_start + 1,"/log in legal/legal menu page/block reporters page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 8,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 7,x_start + 1," user name :");
    attroff (COLOR_PAIR (5));
}
void printer_error_for_block_reports_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," block reporters page ");
    mvprintw (y_start + 1,x_start + 1,"/log in legal/legal menu page/block reporters page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 13," There is no user to block !");
    attroff (COLOR_PAIR (5));
}
void printer_for_block_people_in_menu (int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    char user_name_save[20];
    get_nth_user_name_for_block (num_of_nth_report, user_name_save);
    printer_for_block_reporters_page();
    mvprintw (y_start + 7,x_start + 13,"%s", user_name_save);
}
int which_people_is_going_to_block (WINDOW *block_reporters_win){
    char key;
    int num = 1;
    printer_for_block_people_in_menu (1);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (block_reporters_win);
        create_block_reporters_page (block_reporters_win);
        num = controlle_menu (key, counter_of_exist_people_for_is_blocked (), num);
        printer_for_block_people_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void printer_for_are_you_sure_for_block (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 18,x_start + 12," Are you sure to Block this user ? ");
    attron (COLOR_PAIR (1));
    switch (num){
        case 1:
        print_are_you_sure_state_1 ();
        break;
        case 2:
        print_are_you_sure_state_2 ();
        break;
    }
}
int Are_you_sure_for_block (void){
    char key;
    int num = 1;
    printer_for_are_you_sure_for_block (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 2, num);
        printer_for_are_you_sure_for_block (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void block_user (int num_of_nth_user){
    struct IsBlock isblk[100];
    int num = 0;
    num = counter_num_of_block (); 
    char user_name_save[20];
    get_nth_user_name_for_block (num_of_nth_user, user_name_save);
    strcpy (isblk[num].user_name, user_name_save);
    isblk[num].is_block = 1;
    isblk[num].num_of_user = num ;
    FILE *block_data = fopen ("IsBlocked.dat","ab");
    fwrite (&isblk[num], sizeof(struct IsBlock), 1, block_data);
    fclose (block_data);    
}
int block_reporters_page (WINDOW *block_reporters_win){
    int num = 0;
    if (counter_of_exist_people_for_is_blocked () == 0){
        printer_error_for_block_reports_page ();
        getch();
    }
    else {
        num = which_people_is_going_to_block (block_reporters_win);
        if (Are_you_sure_for_block () == 1){
        block_user (num);
        } 
    }
    clear();
    refresh();
    delwin (block_reporters_win);
    return 300;
}
int block_reporters (WINDOW *block_reporters_win){
    int num = 0;
    create_block_reporters_page (block_reporters_win);
    num = block_reporters_page (block_reporters_win);
    return num;
}
//----------------------------------------------------------------------------------
int counter_num_of_encourage (void){
    struct Money mny[100];
    int num_of_money = 0; 
    FILE *money_data = fopen ("Money.dat","rb");   
    while (1 > 0){
        fread (&mny[num_of_money], sizeof(struct Money), 1, money_data);
        if (feof(money_data)){
            break;
        }
        num_of_money++;
    } 
    fclose (money_data);    
    return num_of_money;
}
void saving_money (char *user_name_save){
    struct Money mny[100];
    int num = 0;
    num = counter_num_of_encourage (); 
    strcpy (mny[num].user_name, user_name_save);
    mny[num].money = 0;
    mny[num].num_of_user = num;
    FILE *money_data = fopen ("Money.dat","ab");
    fwrite (&mny[num], sizeof(struct Money), 1, money_data);
    fclose (money_data);
}
int counter_of_exist_report_for_encourage (void){
    struct Money mny[100];
    int num = 0; 
    int exist_num = 0;
    FILE *money_data = fopen ("Money.dat","rb");   
    while (1 > 0){
        fread (&mny[num], sizeof(struct Money), 1, money_data);
        if (feof(money_data)){
            break;
        }
        if (is_people_blocked (mny[num].user_name) == 0){
            if (mny[num].money == 0){
                exist_num++;
            }
        }
        num++;
    } 
    fclose (money_data);    
    return exist_num;
}
void get_nth_user_name_for_encourage (int num_of_nth_user, char *user_name_save){
    int num = 0;
    int exist_num = 0;
    struct Money mny[100];
    num_of_nth_user--;
    FILE *money_data = fopen ("Money.dat","rb");
    while (1 > 0){
        fread (&mny[num], sizeof(struct IsBlock), 1, money_data);
        if (feof(money_data)){
            break;
        }
        if (is_people_blocked (mny[num].user_name) == 0){
            if (mny[num].money == 0){
                if (num_of_nth_user == exist_num){
                    strcpy (user_name_save, mny[num].user_name);
                    break;
                }
                else {
                    exist_num++;
                }
            }
        }
        num++;
    } 
    fclose (money_data);
}
void create_encourage_reporters_page (WINDOW *encourage_reporters_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    encourage_reporters_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (encourage_reporters_win, 0, 0);
    wrefresh (encourage_reporters_win);    
}
void printer_for_encourage_reporters_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," encourage reporters page ");
    mvprintw (y_start + 1,x_start + 1,"/log in legal/legal menu page/encourage reporters page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (4));
    mvprintw (y_start + 6,x_start + 1,"__________________________________________________________");
    mvprintw (y_start + 8,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (4));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 7,x_start + 1," user name :");
    attroff (COLOR_PAIR (5));
}
void printer_error_for_encourage_reports_page (void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," encourage reporters page ");
    mvprintw (y_start + 1,x_start + 1,"/log in legal/legal menu page/encourage reporters page/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
    attron (COLOR_PAIR (5));
    mvprintw (y_start + 12,x_start + 10," There is no user to encourage !");
    attroff (COLOR_PAIR (5));
}
void printer_for_encourage_people_in_menu (int num_of_nth_report){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    char user_name_save[20];
    get_nth_user_name_for_encourage (num_of_nth_report, user_name_save);
    printer_for_encourage_reporters_page();
    mvprintw (y_start + 7,x_start + 13,"%s", user_name_save);
}
int which_people_is_going_to_encourage (WINDOW *encourage_reporters_win){
    char key;
    int num = 1;
    printer_for_encourage_people_in_menu (1);
    while (1 > 0){
        key = getch();
        clear();
        refresh();
        delwin (encourage_reporters_win);
        create_encourage_reporters_page (encourage_reporters_win);
        num = controlle_menu (key, counter_of_exist_report_for_encourage (), num);
        printer_for_encourage_people_in_menu (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void printer_for_are_you_sure_for_encourage (int num){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (1));
    mvprintw (y_start + 18,x_start + 10," Are you sure to encourage this user ? ");
    attron (COLOR_PAIR (1));
    switch (num){
        case 1:
        print_are_you_sure_state_1 ();
        break;
        case 2:
        print_are_you_sure_state_2 ();
        break;
    }
}
int Are_you_sure_for_encourage (void){
    char key;
    int num = 1;
    printer_for_are_you_sure_for_encourage (1);
    while (1 > 0){
        key = getch();
        num = controlle_menu (key, 2, num);
        printer_for_are_you_sure_for_encourage (num);
        if (key == 10 || key == 13){
            break;
        } 
    }
    return num;
}
void encourage_user (int num_of_nth_user){
    struct Money mny[100];
    int num = 0;
    num = counter_num_of_encourage (); 
    char user_name_save[20];
    get_nth_user_name_for_encourage (num_of_nth_user, user_name_save);
    strcpy (mny[num].user_name, user_name_save);
    mny[num].money = 100;
    mny[num].num_of_user = num;
    FILE *money_data = fopen ("Money.dat","ab");
    fwrite (&mny[num], sizeof(struct Money), 1, money_data);
    fclose (money_data);    
}
int encourage_reporters_page (WINDOW *encourage_reporters_win){
    int num = 0;
    if (counter_of_exist_report_for_encourage () == 0){
        printer_error_for_encourage_reports_page ();
        getch();
    }
    else {
        num = which_people_is_going_to_encourage (encourage_reporters_win);
        if (Are_you_sure_for_encourage () == 1){
            encourage_user (num);
        } 
    }
    clear();
    refresh();
    delwin (encourage_reporters_win);
    return 300;
}
int encourage_reporters (WINDOW *encourage_reporters_win){
    int num = 0;
    create_encourage_reporters_page (encourage_reporters_win);
    num = encourage_reporters_page (encourage_reporters_win);
    return num;
}
//-----------------------------------------------------------------------------------
void create_about_page (WINDOW *about_win){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    about_win = newwin (25, 60, y_start, x_start);
    refresh();
    box (about_win, 0, 0);
    wrefresh (about_win);    
}
void printer_for_about_creator_page(void){
    int x_start = 0, y_start = 0;
    clu (&x_start, &y_start);
    attron (COLOR_PAIR (3));
    mvprintw (y_start + 4,x_start + 19," about creator page ");
    mvprintw (y_start + 1,x_start + 1,"main page/about creator/");
    mvprintw (y_start + 2,x_start + 1,"__________________________________________________________");
    attroff (COLOR_PAIR (3));
}
int about_page (WINDOW *about_win){
    clear();
    refresh();
    delwin (about_win);
    return 0;
}
int about_section (WINDOW *about_win){
    int num = 0;
    create_about_page (about_win);
    printer_for_about_creator_page();
    getch();
    num = about_page (about_win);
    return num;
}
//----------------------------------------------------------------------------------
// choose a new page after finishing the curent page
int manegment_1 (int num){
    struct window win;
    switch (num){
        case 0:
        num = Main_page (win.main_page);
        break;
        case 1:
        num = people_section_page (win.people_section_win);
        break;
        case 2:
        num = viewer_section_page (win.viewer_section_win);
        break;
        case 3:
        num = legal_section_page (win.legal_section_win);
        break;
        case 4:
        num = about_section (win.about_win);
        break;
        case 11:
        num = sgin_in_for_people (win.sgin_in_win_for_people);
        break;
        case 12:
        num = log_in_for_people (win.log_in_win_for_people);
        break;
        case 21:
        num = sgin_in_for_viewer (win.sgin_in_win_for_viewer);
        break;
    }
    return num;
}
int manegment_2 (int num){
    struct window win;
    switch (num){
        case 22:
        num = log_in_for_viewer (win.log_in_win_for_viewer);
        break;
        case 31:
        num = sgin_in_for_legal (win.sgin_in_win_for_legal);
        break;
        case 32:
        num = log_in_for_legal (win.log_in_win_for_legal);
        break;
        case 100:
        num = people_menu (win.people_menu_win);
        break;
        case 200:
        num = cardboard_for_viewer (win.cardboard_for_viewer_win);
        break;
        case 300:
        num = legal_menu (win.legal_menu_win);
        break;
        case 101:
        num = cardboard_for_people (win.cardboard_for_people_win);
        break;
        case 102:
        num = report_new_crime (win.report_new_crime_win);
        break;
    }
    return num;
}
int manegment_3 (int num){
    struct window win;
    switch (num){
        case 103:
        num = arrange_list (win.arrange_list_win);
        break;
        case 104:
        num = edit_report (win.edit_report_win);
        break;
        case 105:
        num = delete_report (win.delete_report_win);
        break;
        case 106:
        num = show_related_reports (win.show_related_reports_win);
        break;
        case 107:
        num = important_report (win.important_reports_win);
        break;
        case 108:
        num = buy_VIP (win.buy_VIP_win);
        break;
        case 111:
        num = Inbox_for_people (win.Inbox_for_people_win);
        break;
        case 112:
        num = History_for_people (win.History_for_people_win);
        break;
    }
    return num;
}
int manegment_4 (int num){
    struct window win;
    switch (num){
        case 201:
        num = Inbox_for_viewer (win.Inbox_for_viewer_win);
        break;
        case 202:
        num = History_for_viewer (win.History_for_viewer_win);
        break;
        case 301:
        num = cardboard_for_legal (win.cardboard_for_legal_win);
        break;
        case 302:
        num = block_reporters (win.block_reporters_win);
        break;
        case 303:
        num = encourage_reporters (win.encourage_reporters_win);
        break;
        case 311:
        num = Inbox_for_legal (win.Inbox_for_legal_win);
        break;
        case 312:
        num = History_for_legal (win.History_for_legal_win);
        break;
    }
    return num;
}
void init_the_color (void){
    //stat color mod
    start_color();
    // define the color pairs
    init_pair (1, COLOR_YELLOW, COLOR_BLACK);
    init_pair (2, COLOR_YELLOW, COLOR_BLUE);
    init_pair (3, COLOR_BLUE, COLOR_BLACK);
    init_pair (4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair (5, COLOR_GREEN, COLOR_BLACK);
    init_pair (6, COLOR_CYAN, COLOR_BLACK);
    init_pair (7, COLOR_RED, COLOR_BLACK);
}
void get_time_of_now (char *hour){
    struct tm* local;
    time_t time_hour = time (NULL);
    local = localtime (&time_hour);
    strftime (hour , sizeof(hour), "%H", local);
}
int check_the_time_for_entering (void){
    char hour[2];
    get_time_of_now (hour);
    if (strcmp (hour, "9") == 0){
        return 1;
    }
    if (strcmp (hour, "10") == 0){
        return 1;
    }
    if (strcmp (hour, "11") == 0){
        return 1;
    }
    if (strcmp (hour, "12") == 0){
        return 1;
    }
    if (strcmp (hour, "16") == 0){
        return 1;
    }
    if (strcmp (hour, "17") == 0){
        return 1;
    }
    if (strcmp (hour, "18") == 0){
        return 1;
    }
    if (strcmp (hour, "19") == 0){
        return 1;
    }
    return 0;
}
void start (void){
    int max_x_shell = 0, max_y_shell = 0;
    getmaxyx (stdscr, max_y_shell, max_x_shell);
    int num = 0;
    int i = 2;
    // it checking the size of stdscr on the shell is enuogh to run
    i = check_shell_window(); 
    // if the size of the shell is enuogh the code will run else it writes error
    if (i == 1 && check_the_time_for_entering () == 1){
        while (1 > 0){
            num = manegment_1 (num);
            num = manegment_2 (num);
            num = manegment_3 (num);
            num = manegment_4 (num);
            // if the key the user pressed is exit it return 5 then exit from program
            if (num == 5){
                break;
            }
        }
    }  
    if (check_the_time_for_entering () == 0){
        mvprintw (max_y_shell / 2, (max_x_shell / 2) - 15, "you cant enter because of bad time !");
        getch();
    }
        
}
int main(){
    // start curser mod
    initscr();
    noecho();
    curs_set(0);
    init_the_color();
    start();
    endwin();
    return 0;
}