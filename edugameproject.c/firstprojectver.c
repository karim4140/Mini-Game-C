#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<stdbool.h>
#include<time.h>


#define MAX 50 
#define max_line 500 

int level = 1 , curr_player = -1 , in_row = 0 , master = 0 , c_easy = 0 , w_easy =0, c_med=0 , w_med = 0 , 
 c_hard =0 , w_hard = 0 , curr1 =0 , curr2 =0, curr3 =0 , randomq = 1;
char tmp[max_line];
typedef struct {
    char name[50] ;
    float score ;
} player ;

typedef struct {
    char question[max_line] ;
    char choice12[max_line] ;
    char choice34[max_line] ;
    char answer[max_line] ;

} General_Q ;


General_Q easy_q[20] ; General_Q medium_q[20] ; General_Q hard_q[20] ;

player players_arr[MAX]; 


char home() ;
void start() ;
void show_score() ;
int choices(int level , int place , int res ) ;
void comment(int flag);
void generate_question() ;
void edit_score(int player , int flag) ;
void help() ;
int cmp(const void* a ,const void* b) ; 
int general_question() ;
void read_files() ;





int main() {
    if(curr_player == 50) return 0 ;
    if(curr_player == -1) read_files() ;
    char c = home() ;
    if(c == 'S') { 
        level = 1 ;
        curr_player++;
        in_row = 0 ;
        c_easy = 0 ; w_easy =0 ; c_med=0 ; w_med = 0 ; c_hard =0 , w_hard = 0 ;
        curr1 =0 ; curr2 =0 ; curr3 =0;
        start() ;
    } 
    else if(c == 'V') show_score() ;
    else if(c == 'H') help() ;
    else if(c == 'Q') exit(0);
}

char home() {

    puts("") ; puts("") ;
    printf("%55s\n" ,"Educational Game") ;
    puts("___________________________________________________________________________________________________") ;
    puts("") ;
    printf("%51s\n%48s\n%53s\n" , "WELCOME"  ,"TO" , "THE EDU GAME" ) ;
    puts("___________________________________________________________________________________________________") ;
    puts("") ;
    puts("___________________________________________________________________________________________________") ;
    puts("") ;
    printf("%25s" , "DO You Want to Master Sciences?!") ;
    puts("") ;
    puts("___________________________________________________________________________________________________") ;
    puts("") ;
    puts("___________________________________________________________________________________________________") ;
    puts("") ;
    puts("<-- Press S to start the game") ;
    puts("<-- Press V to view the highest score") ;
    puts("<-- Press H for Help") ;
    puts("<-- Press Q for Quit") ;
    puts("") ;
    puts("___________________________________________________________________________________________________") ;
    puts("") ;
    printf("Please Enter Your Choice Here : ") ;
        scanf("%s" , &tmp) ;
        fflush(stdin) ;
        if(strlen(tmp)== 1) {
            if((tmp[0] == 'S' || tmp[0] == 'V' || tmp[0] == 'Q' || tmp[0] == 'H')) return tmp[0] ;
            else {
        printf("\n<--INVALID INPUT\n") ;
        printf("\nPlease Enter Your Choice Here : ") ;
        scanf("%s" , tmp);
        fflush(stdin) ;
            }
        }
    while(1) {

        if(strlen(tmp)==1) if(tmp[0] == 'S' || tmp[0] == 'V' || tmp[0] == 'Q' || tmp[0] == 'H') return tmp[0] ;
        printf("\n<--INVALID INPUT\n") ;
        printf("\nPlease Enter Your Choice Here : ") ;
        scanf("%s" , tmp);
        fflush(stdin) ;
    }
}

void start() {

    char name[100] ;
    int count = 0 ;
    srand(time(NULL)) ;
    puts("\n###################################################################################################") ;
    puts("") ;
    printf("Please Enter your username :  ") ;
    scanf("\n%[^\n]s" , &name);
    strcpy(players_arr[curr_player].name , name) ; players_arr[curr_player].score = 0 ;
    puts("") ;
    puts("###################################################################################################\n") ;
     while(count++ < 20 ) {
        generate_question() ;
     }
     puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") ;
     float curr_score = (players_arr[curr_player].score) ;
     printf("\nYour score is %.2f\n" , curr_score) ;
     printf("<--LEVEL\tCORRECT\t\tWRONG\n<--EASY\t\t%-5d\t\t%-3d\n<--MEDIUM\t%d\t\t%d\n<--HARD\t\t%-5d\t\t%-3d\nYOUR PERCENTAGE IS %.2f\n" , c_easy , w_easy , c_med , w_med , c_hard , w_hard , (curr_score/20 *100));
     char *massage = (curr_score/20 *100) >= 75 ? "<-- Congratulations, you are ready to go to the next level!" : "Unfortunately, You need to ask for extra help" ;
     printf("%s\n" , massage) ;
     puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
     if(curr_score > players_arr[master].score) master = curr_player ;
     printf("\n<-- press N to Go for Home page :  ") ;
     scanf("%s" , tmp) ;
     fflush(stdin) ;
     while(true) {

        if(strlen(tmp)==1) if(tmp[0] == 'N') break; 
        printf("\n<--INVALID INPUT\n") ;
        printf("Please Enter Your Choice Here : ") ;
        scanf("%s" , tmp);
        fflush(stdin) ;
    }
     main() ;
}
void show_score() {
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
    if(curr_player == -1) puts("No one has played this game before.\nYou are the first one.\nGood luck and Enjoy :)\n") ;
    else {
        qsort(players_arr , curr_player+1 , sizeof(player) , cmp) ;
        printf("  <-- 1-%s achieved the highest score %.2f\n" ,players_arr[0].name , players_arr[0].score) ;
        for(int i=1 ; i < curr_player+1 ; i++) {
            printf("  <-- %d-%s achieved score %.2f\n" , i+1 ,players_arr[i].name , players_arr[i].score) ;
        }
    }
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") ;
    puts(""); puts("") ;
    printf("\n<-- press N to Go for Home page :  ") ;
    scanf("%s" , tmp) ;
    fflush(stdin) ;
    while(true) {

        if(strlen(tmp)==1) if(tmp[0] == 'N') break; 
        printf("\n<--INVALID INPUT\n") ;
        printf("Please Enter Your Choice Here : ") ;
        scanf("%s" , tmp);
        fflush(stdin) ;
    }
    main();
    
}

int choices(int level , int place , int res) {
    
    // (rand() % (high - low + 1)) + low; 
    // formula to generate numbers in specific range from low to high
    int n1 , n2 , n3 ;
    char c ;
    if (level==1){
        do{
          n1 = (rand() % (100 - 4 + 1)) + 4 ;
          n2 =(rand() % (100 - 4 + 1)) + 4 ;
          n3 = (rand() % (100 - 4 + 1)) + 4 ;
        } while(n1 == res || n2 == res || n3 == res) ; 
    }
    else if(level == 2) {
        do{
          n1 = (rand() % (10000 - 100 + 1)) + 100;
          n2 =(rand() % (10000 - 4500 + 1)) + 4500;
          n3 = (rand() % (10000 - 1000 + 1)) + 1000;
        } while(n1 == res || n2 == res || n3 == res) ;
    }
    else {
        do{
          n1 = (rand() % (1000000 - 10000 + 1)) + 10000;
          n2 =(rand() % (1000000  - 500000 + 1)) + 500000;
          n3 = (rand() % (1000000  - 250000 + 1)) + 250000;
        } while(n1 == res || n2 == res || n3 == res) ;
    }
    if(place==1) printf("A)%-6d\t\tB)%-6d\n\nC)%-6d\t\tD)%-6d\n" , res , n2 , n1 , n3 ) ;
    else if(place == 2) printf("A)%-6d\t\tB)%-6d\n\nC)%-6d\t\tD)%-6d\n" , n3 , res , n1 , n2 ) ;
    else if(place == 3) printf("A)%-6d\t\tB)%-6d\n\nC)%-6d\t\tD)%-6d\n" , n2 , n1 , res , n3 ) ;
    else if(place==4) printf("A)%-6d\t\tB)%-6d\n\nC)%-6d\t\tD)%-6d\n" , n1 , n3 , n2 , res ) ;
    printf("\nPlease Enter your choice here: ") ;
    scanf("%s" , tmp) ;
    fflush(stdin) ;
    while(true) {
    if(strlen(tmp)== 1) if((tmp[0] == 'A' || tmp[0] == 'B' || tmp[0] == 'C' || tmp[0] == 'D')) { c = tmp[0] ; break; }
        printf("\n<--INVALID INPUT\n") ;
        printf("______________________________________") ;
        printf("\nPlease Enter Your Choice Here : ") ;
        scanf("%s" , tmp);
        fflush(stdin) ;
     }
  
    if(place == c - 'A'+ 1) return 1 ;
    else return 0 ;
}

void comment(int flag) {

    if(flag) {
        int n = rand() % 4;
        switch(n) {
            case 0 : puts("\n<--Very Good\n") ; break ;
            case 1 : puts("\n<--Exellent\n") ; break ;
            case 2 : puts("\n<--Nice Work\n") ; break ;
            case 3 : puts("\n<--Keep Up good work!\n") ; break ;
        }
    }
    else {
            int n = rand() % 4;
            switch(n) {
            case 0 : puts("\n<--No , Please try again\n") ; break ;
            case 1 : puts("\n<--wrong , Try once again\n") ; break ;
            case 2 : puts("\n<--Dont Give up\n") ; break ;
            case 3 : puts("\n<--No , Keep trying\n") ; break ;
        }
    }
}

void generate_question() {
     if(randomq) {
        int place , x , y;
        if(level == 1) {
        x = (rand() % (9 - 2 + 1)) + 2;  y = (rand() % (9 - 2 + 1)) + 2;
        place = (rand() % (4 - 1+1 )) + 1 ;
     }
     else if(level == 2) {
         x = (rand() % (99 - 10 + 1)) + 10;  y = (rand() % (99 - 10 + 1)) + 10;
        place = (rand() % (4 - 1 + 1)) + 1 ;
     }
     else {

         x = (rand() % (999 - 100 + 1)) + 100;   y = (rand() % (999 - 100 + 1)) + 100;
        place = (rand() % (4 - 1 + 1 )) + 1 ;
    }
    printf("How much is %d times %d ?\n\n" , x , y) ;
    int res = choices(level , place , x*y) ;
    if(res) {
        edit_score(curr_player , 1) ; 
        if(level ==1 || level == 2) in_row++ ;
        if(in_row == 3 && level != 3) { printf("\n<--You got promoted to the next level!\n"); level++ ; in_row = 0;}
        comment(1) ;
        puts("----------------------------------------");
    }
    else{
        comment(0) ; edit_score(curr_player , 0) ; in_row = 0 ; puts("----------------------------------------");
    }

   }
   else {
    int res2 = general_question() ;
    if(res2) {
        edit_score(curr_player , 1) ;
        if(level!=3) in_row++ ;
        if(in_row==3 && level !=3) {  printf("\n<--You got promoted to the next level!\n"); level++ ; in_row = 0 ;}
        comment(1) ;
        puts("----------------------------------------");
    }
    else {
        edit_score(curr_player , 0) ;
        comment(0) ;
        puts("----------------------------------------");
        in_row = 0 ;
    }
  }
   randomq = !randomq ;
}

void edit_score(int player , int flag) {
        if(flag) players_arr[player].score += 1 ;
        if(flag) {
            if(level == 1) c_easy++ ;
            else if(level == 2) c_med++ ;
            else c_hard++ ;
        }
        else {
            if(level == 1) w_easy++ ;
            else if(level == 2) w_med++ ;
            else w_hard++ ;
        }
}

void help() {
    printf("\nWELCOME :) , THIS IS OUR EDU GAME. \n") ;
    printf("\n                 <--OUR RULES ARE SIMPLE-->\n") ;
    printf("\n<--This Game icludes many graded questions in different fields.\n<--There are 3 levels of difficulty.") ;
    printf("\n<--You got 20 attempts to answer.\n<--One point for each correct answer, NO points for wrong ones.");
    printf("\n<--Make sure to enter your answers in capital letters.\n<--For each 3 consecutive correct answers; You will be promoted to the next level.");
    printf("\n<--After 20 attempts, You will get a detailed result.");
    printf("\n----------------------------------------------------------------------------------------------------------\n");
    printf("\nTHANK YOU!!\nOur team members wish you best luck :)");
    printf("\n\n<-- press N to Go for Home page :  ") ;
    scanf("%s" , tmp) ;
    fflush(stdin) ;
    while(true) {

        if(strlen(tmp)==1) if(tmp[0] == 'N') break;
        printf("\n<--INVALID INPUT\n") ;
        printf("Please Enter Your Choice Here : ") ;
        scanf("%s" , tmp);
        fflush(stdin) ;
    }
    main() ;   
}

int cmp(const void* a ,const void* b){
    player A = *(player*)a ;
    player B = *(player*) b ;
    return B.score - A.score ;
}

void read_files() {
    FILE *file ;
    file = fopen("easy.txt" , "r") ;
    char g[max_line] , b[max_line], s[max_line] , c[max_line];
    if(file == NULL) printf("\nCOULD NOT OPEN INPUT FILE\n") ;
    else {
        for(int i=0 ; i < 20 ; i++) {
        fgets(g , max_line , file) ; fgets(s , max_line , file) ; fgets(b , max_line , file) ; fgets(c , max_line , file) ;
        strcpy(easy_q[i].question , g) ; strcpy(easy_q[i].choice12 , s) ; strcpy(easy_q[i].choice34 , b) ; strcpy(easy_q[i].answer , c) ;
    }
    }
    fclose(file) ;
    file= fopen("med.txt" , "r") ;
    if(file == NULL) printf("\nCOULD NOT OPEN INPUT FILE\n") ;
    else {
        for(int i=0 ; i < 20 ; i++) {
        fgets(g , max_line , file) ; fgets(s , max_line , file) ; fgets(b , max_line , file) ; fgets(c , max_line , file) ;
        strcpy(medium_q[i].question , g) ; strcpy(medium_q[i].choice12 , s) ; strcpy(medium_q[i].choice34 , b) ; strcpy(medium_q[i].answer , c) ;
    }
    }
    fclose(file) ;
    file= fopen("hard.txt" , "r") ;
    if(file == NULL) printf("\nCOULD NOT OPEN INPUT FILE\n") ;
    else {
        for(int i=0 ; i < 20 ; i++) {
        fgets(g , max_line , file) ; fgets(s , max_line , file) ; fgets(b , max_line , file) ; fgets(c , max_line , file) ;
        strcpy(hard_q[i].question , g) ; strcpy(hard_q[i].choice12 , s) ; strcpy(hard_q[i].choice34 , b) ; strcpy(hard_q[i].answer , c) ;
    }
    fclose(file) ;
  }
}

int general_question() {
    int res = 0 ;
    char c ;
    if(level == 1)  printf("%s\n%s\n%s\n" , easy_q[curr1].question , easy_q[curr1].choice12 , easy_q[curr1].choice34) ;
    else if(level == 2) printf("%s\n%s\n%s\n" , medium_q[curr2].question , medium_q[curr2].choice12 , medium_q[curr2].choice34) ;
    else printf("%s\n%s\n%s\n" , hard_q[curr3].question , hard_q[curr3].choice12 , hard_q[curr3].choice34) ; ;
        printf("Please Enter your choice here: ") ;
        scanf("%s" , tmp) ; 
        fflush(stdin) ;
        while(true) {
        if(strlen(tmp)== 1) if((tmp[0] == 'A' || tmp[0] == 'B' || tmp[0] == 'C' || tmp[0] == 'D')) { c = tmp[0] ; break; }
        printf("\n<--INVALID INPUT\n") ;
        printf("______________________________________\n") ; 
        printf("Please Enter Your Choice Here : ") ;
        scanf("%s" , tmp);
        fflush(stdin) ;

      }
        if(level == 1) {
            if(c == easy_q[curr1].answer[0]) res = 1 ;
            curr1++ ;
        }

        else if(level == 2) 
             {
                if(c == medium_q[curr2].answer[0]) res = 1 ;
                curr2++ ;
             }
        else 
            {
                if(c == hard_q[curr3].answer[0]) res = 1 ;
                curr3++ ; 
            }

        
        return res ;
}