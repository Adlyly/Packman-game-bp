#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>


typedef struct Info
{
    char name[100];
    int ID;
    int level;
    int password;
    char map[20][20];
    int score;
    int condition;

    /*about conditions=
    1 means completely finished 
    0 means there is an incomplete play
    */

}Info;

typedef struct Main{

    Info Player;
    Main * pnext;

}Main;

typedef struct Ghost{

    int xghost;
    int yghost;

}Ghost;

typedef struct GhostMain{

    Ghost ghost;
    GhostMain * pnext;

}GhostMain;


Main * CopyFromFile( FILE * , Main *);
/*
Description : this function loads information from file (if there is any information).
Input : a pointer to the file we want to read from & a pointer to the head of linked list .
Output : it returns a pointer to the head of the linked list ( we should save the pointer for other changes).
*/
int CheckAccount(Main * );
/*
Description : this function search in the linked list to see if there is an account with this name and password or not.
Input : a pointer to the head of the linked list & the name and the password that user enters.
Output : it returns a number that show if the account were existed or not or the password was wrong.
*/
Main * MakeAccount(Main *);
/*
Description : this function makes an account ( add new structure ) if it hasnt existed with that username yet.
Input : a pointer to the head of the linked list.
Output : it returns a pointer to the head of the linked list
( Maybe we make first account and structure so we should save poiner of the head of the linked list ).
*/
void SaveInFile( FILE * , Main * );
/*
Description : this function writes information in file (if there is any information).
Input : a pointer to the file we want to write in 
and a pointer to the head of our linked list which includes information .
Output : nothing.
*/
void Review(Main * , int );
/*
Description : this function show the information we saved in linked list.
Input : a pointer to the head of our linked list which include information.
Output : nothing.
*/
void DelteAccount(Main ** , FILE * , int );
/*
Description : this function delete an account which user has logined yet.
Input : a pointer to the pointer ( Maybe wa want to delete first structure so we should change phead ) 
of head of our linked list which include information of users 
and a pointer to the file to rewrite the information ( because we deleted one structure of linked list).
and also ID of the user who we want to delete his/her information.
Output : nothing.
*/
void Game( Main * , int , FILE *);
/*
Description : int this function the whole design of game has been done.
Input : a pointer to the head of our linked list which have user info and a pointer to the map file to read from .
Output : nothing.
*/
void MapCopy(FILE * , char[20][20] , int );
/*
Description : this function copy a wanted map from mapfile to the string which show the map of our game.
Input : a pointer to the head of map file & our game string & a number that show the user chose which map.
Output : nothing.
*/
int FindGhost(char [20][20]);
/*
Description : this function find ghosts int the map and count them.
Input : our game string.
Output : number of our ghosts.
*/
int FindPill(char [20][20]);
/*
Description : this function find pills int the map and count them.
Input : our game string.
Output : number of our pills.
*/
GhostMain * GhostMake(GhostMain * , char [20][20]);
/*
Description : this function add new structure for each ghost( because number of our ghosts is unknown).
Input : a pointer to the head of the ghost linked list and our game string to search and find position of our ghosts.
Output : it returns a pointer to the head of the linked list
( Maybe we make first structure so we should save poiner of the head of the linked list ).
*/
int CheckMap(int , int , int , char [20][20]);
/*
Description : this function check the positon that packman want to go to see if it is a wall or space or ghost or pill.
Input : first a num that show which direction we chose , then the position of our packman & our game string.
Output : symbolic number for each statement.
*/
int GhostMove(GhostMain * , char [20][20]);
/*
Description : this function check the positon that ghost randomly want to go to see if it is a wall or space or packman or pill.
Input : a pointer to the head of ghosts leinked list ( because all ghosts should move ) & our game string.
Output : symbolic number for the statement in which ghost face packman.
*/
void FreeMemmory(Main *);
/*
Description : this function release the memmory which we allocated.
Input : a pointer to the head of our linked list.
Output : nothing.
*/


int main()
{

    SetConsoleOutputCP(65001);

    FILE * fp;
    Main * phead = NULL , * ptmp , *ptmp1;
    char c , strname[100];
    int pass , playerID , tmp;

        fp=fopen("Myplay.bin" , "r+b");
        if(fp==NULL){
        fp=fopen("Myplay.bin" , "w+b");
        if(fp==NULL){
            printf("file cannot be opened.\n");
            exit (0);
        }
    }

    fseek(fp , 0 , SEEK_END);
    long strcount = ftell(fp);
    int count = strcount/sizeof(Info);

    fseek(fp , 0 , SEEK_SET); 

    while(count){

        ptmp1=CopyFromFile(fp , phead );
        if(phead==NULL)
        phead=ptmp1;

         count--;
    }
    
    system("cls");
    for(int i=0 ; i<3 ; i++)
    printf("\n");
    printf("                                            ");
    printf("\033[1;31m");
    printf("Welcome ");
    printf("\033[1;32m");
    printf("To ");
    printf("\033[1;36m");
    printf("Pack ");
    printf("\033[1;35m");
    printf("Man ");
    printf("\033[1;33m");
    printf("Game :D");
    Sleep(3000);


    while(1){
        
        system("cls");
        printf("\n\n\n                                          ");
        for(int i=0 ; i<35 ; i++)
        printf("\u15E7");
        printf("\n                                         ");
        printf("if you want to login , Please enter 1\n");
        printf("                                   ");
        printf("if you want to make an account , Please enter 2\n");
        printf("                                         ");
        printf("if you want to exit , Please enter 0\n");
        printf("                                          ");
        for(int i=0 ; i<35 ; i++)
        printf("\u15E7");
        printf("\n                                                         ");
        

        scanf("%d" , &tmp);

        if(tmp==1 || tmp==2){

            if(tmp==1){

                playerID=CheckAccount(phead);
                if(playerID==0)
                continue;

            }

            else{

                ptmp=MakeAccount(phead);
        
                if(ptmp){
                    if(phead==NULL)
                    phead=ptmp;
                    playerID=ptmp->Player.ID;
                    SaveInFile(fp , phead);
                    system("cls");
                    printf("\n\n\n");
                    printf("                                        ");
                    printf("\U0001F600Your account is made successfuly \U0001F600");
                    Sleep(2000);
                    system("cls");
                }
                else
                continue;
            }

            while(1){
                
                printf("\033[1;33m");
                printf("\n\n\n                                      ");
                printf("Please enter 1 for Review information\n");
                printf("                                           ");
                printf("Please enter 2 to start game\n");
                printf("                                      ");
                printf("Please enter 3 to delete your account\n");
                printf("                                            ");
                printf("Please enter 0 to logout\n");
                printf("                                                       ");

                scanf("%d" , &tmp);
                system("cls");

                if(tmp==1)
                Review(phead , playerID);

                if(tmp==2){
                    Game(phead , playerID , fp);
                    SaveInFile(fp , phead);
                }
                
                if(tmp==3){
                    DelteAccount(&phead , fp , playerID);
                    SaveInFile(fp , phead);
                    system("cls");
                    printf("\n\n\n");
                    printf("                                        ");
                    printf("\U0001F600Your account deleted successfuly \U0001F600");
                    Sleep(3000);
                    system("cls");
                    break;
                }
                    
                if(tmp==0)
                break;

            }
            
            printf("\n\n\n");
            printf("                                    ");
            printf("Do you want to login/make another account?\n");
            printf("                                       ");
            printf("if you want enter y , if not enter n");
            printf("\n                                                         ");
            getchar();
            scanf("%c" , &c);
            system("cls");
            if(c=='n')
            break;
        }
        else{
            system("cls");
            for(int i=0 ; i<3 ; i++)
            printf("\n");
            printf("                                            ");
            printf("\033[1;31m");
            printf("Hope ");
            printf("\033[1;32m");
            printf("you ");
            printf("\033[1;33m");
            printf("have ");
            printf("\033[1;35m");
            printf("a good ");
            printf("\033[1;36m");
            printf("game :)");
            Sleep(3000);
            break;
        }

    }

    fclose(fp);
    FreeMemmory(phead);

    return 0;

}

Main * CopyFromFile( FILE * fp , Main * phead ){


    Main *ptmp = phead , *pnew;
    
    
    pnew=(Main *)malloc(sizeof(Main));
    pnew->pnext=NULL;
    fread( &((*pnew).Player) , sizeof(Info) , 1 , fp);

    while(ptmp){
        if(ptmp->pnext)
        ptmp=ptmp->pnext;
        else
        break;
    }

    if(phead)
    ptmp->pnext = pnew;

    return pnew;

}

int CheckAccount(Main * phead ){

    Main * ptmp=phead;
    char strname[100];
    int pass;

    system("cls");
    printf("\n\n\n");
    printf("                                             ");
    printf("Please enter your name.\n");
    printf("                                             ");
    getchar();
    gets(strname);

    while(ptmp && strcmp( ptmp->Player.name , strname )){
        ptmp=ptmp->pnext;
    }

    if(ptmp==NULL){

        system("cls");
        printf("\n\n\n");
        printf("                                        ");
        printf("There is no account with this name.");
        Sleep(3000);
        system("cls");
        return 0;

    }
    
    else{

        system("cls");
        printf("\n\n\n");
        printf("                                             ");
        printf("Please enter your password.\n");
        printf("                                             ");
                
        while(1){

            scanf("%d" , &pass);
            if(ptmp->Player.password==pass){
                system("cls");
                printf("\n\n\n");
                printf("                                             ");
                printf("\U0001F600You login successfuly \U0001F600");
                Sleep(3000);
                system("cls");
                return ptmp->Player.ID;
            }
            else{
                system("cls");
                printf("\n\n\n");
                printf("                                  ");
                printf("password is wrong , Please enter correct password\n");
                printf("                                                        ");
                continue;
            }
        }
    }
}

Main * MakeAccount(Main * phead){

    Main * ptmp = phead , * ptmp1 = phead , * pnew ;
    int counter=1;

    while(ptmp){
        counter++;
        if(ptmp->pnext)
        ptmp=ptmp->pnext;
        else
        break;
    }

    pnew=(Main *)malloc(sizeof(Main));
    pnew->pnext=NULL;

    system("cls");
    printf("\n\n\n");
    printf("                                             ");
    printf("Please enter your username\n");
    printf("                                             ");
    getchar();
    gets((*pnew).Player.name);

    while(ptmp1){

        if(strcmp(ptmp1->Player.name , (*pnew).Player.name )==0){
            system("cls");
            printf("\n\n\n");
            printf("                          ");
            printf("There is still an account with this user name which password is : %d" , ptmp1->Player.password );
            Sleep(3000);
            system("cls");
            return NULL;
        }
        else
        ptmp1=ptmp1->pnext;

    }
    system("cls");
    printf("\n\n\n");
    printf("                                             ");
    printf("Please enter your password\n");
    printf("                                             ");
    scanf("%d" , &((*pnew).Player.password));
    system("cls");
                    
    (*pnew).Player.ID=counter;
    (*pnew).Player.level=0;
    (*pnew).Player.score=0;
    (*pnew).Player.condition=1;
    for(int i=0 ; i<20 ; i++)
    (*pnew).Player.map[i][0]='\0';


    if(ptmp)
    ptmp->pnext=pnew;

    return pnew;

}

void SaveInFile( FILE * fp , Main * phead){

    Main * ptmp = phead;
    fclose(fp);
    fp=fopen("Myplay.bin" , "w+b");
    fseek(fp , 0 , SEEK_SET);

    while(ptmp){

        fwrite(&(ptmp->Player) , sizeof(Info) , 1 , fp);
        ptmp=ptmp->pnext;

    }


}

void FreeMemmory(Main * phead){

    Main * ptmp1 = phead , * ptmp2=phead;

    while(ptmp1){

        ptmp2=ptmp1->pnext;
        free((void*)ptmp1);
        ptmp1=ptmp2;

    }

}

void Review(Main * phead , int playerID){

    Main * ptmp = phead;

    while(ptmp && ptmp->Player.ID!=playerID ){
        ptmp=ptmp->pnext;
    }

    system("cls");
    printf("\n\n\n");
    printf("                                                ");
    printf("User Name : %s\n" , (* ptmp).Player.name);
    printf("                                                   ");
    printf("User ID : %d\n" , (* ptmp).Player.ID);
    printf("                                                 ");
    printf("User Level : %d\n" , (* ptmp).Player.level);
    printf("                                               ");
    printf("User Password : %d\n" , (* ptmp).Player.password);

    if((* ptmp).Player.condition == 0){
        
        printf("\n\n\n                                          ");
        printf("The user has an uncomplete game\n");
        printf("                                                  ");
        printf("that game is :\n\n");
        for(int i=0 ; (* ptmp).Player.map[i][0] != '\0' ; i++){
            printf("                                           ");
            for(int j=0 ; (* ptmp).Player.map[i][j] != '\0' ; j++){
                printf("%c" , (* ptmp).Player.map[i][j]);
                printf("  ");
            }
            printf("\n");
        }
        printf("\n\n");
        printf("                                    ");
        printf("and the score of this uncomplete game is : %d\n\n" , (* ptmp).Player.score);

    }
    else{
        printf("                                     ");
        printf("The user doesnt have any uncomplete game.");
    }

    Sleep(3000);
    system("cls");
}

void DelteAccount(Main ** phead , FILE * fp , int playerID){

    Main * ptmp = *phead , * ptmp1 = * phead , * ptmp2 ;

    while(ptmp){

        if(ptmp->Player.ID==playerID){

            ptmp2=ptmp->pnext;
            while(ptmp2){
                ptmp2->Player.ID--;
                ptmp2=ptmp2->pnext;
            }

            ptmp1->pnext=ptmp->pnext;
            break;
        }

        ptmp1 = ptmp;
        ptmp=ptmp->pnext;

    }

    if(ptmp==*phead){

        * phead=ptmp->pnext;

    }

}

void Game(Main *phead , int playerID , FILE * fp){

    Main * ptmp=phead;
    int Ghostnum , Pillnum , tmp , tmpmove , wholeScore , xPack  , xPacktmp , yPack , yPacktmp , flag =0 , tmpGhost;
    char strPlay[20][20] , ctmp , ctmp1 , ctmpove , ch;
    FILE * fpmap;
    GhostMain * pheadG=NULL , * ptmpG;


    fpmap=fopen("Mymap.bin" , "r+b");
    if(fpmap==NULL){
        printf("file cannot be opened.\n");
        exit (0);
    }

    while(ptmp && ptmp->Player.ID != playerID)
    ptmp=ptmp->pnext;

    if(ptmp->Player.condition==0){

        system("cls");
        printf("\n\n\n                             ");
        printf("You still have an uncomplete game , Do you want to continue it?\n");
        printf("                                     ");
        printf("if yes Please enter y , if no Please enter n.\n");
        printf("                         ");
        printf("(Remeber if you start a new game your uncomplete game will be deleted.)\n");
        printf("                                                        ");
        
        getchar();
        scanf("%c" , &ctmp);

        if(ctmp=='y'){
            
            (*ptmp).Player.condition=1;
            for(int i=0 ; i<20 ; i++)
            strcpy(strPlay[i] , (* ptmp).Player.map[i]);

        }
        else {
            
            (*ptmp).Player.condition=1;
            system("cls");
            printf("\n\n\n                           ");
            printf("Please choose difficulty of your game by entering the number of them\n\n");
            printf("                                                       ");
            printf("1.Easy\n");
            printf("                                                       ");
            printf("2.Normal\n");
            printf("                                                       ");
            printf("3.Hard\n");
            printf("                                                         ");

            while(1){

                scanf("%d" , &tmp);
                if(tmp==1 || tmp==2 || tmp==3){
                    MapCopy( fpmap , strPlay , tmp);
                    break;
                }
                else{
                    system("cls");
                    printf("\n\n\n                                     ");
                    printf("Number is invalid , Please enter valid num.\n");
                    printf("                                                       ");
                    continue;
                }
            }
        }
    }

    else{

        system("cls");
        printf("\n\n\n                           ");
        printf("Please choose difficulty of your game by entering the number of them\n\n");
        printf("                                                       ");
        printf("1.Easy\n");
        printf("                                                       ");
        printf("2.Normal\n");
        printf("                                                       ");
        printf("3.Hard\n");
        printf("                                                         ");


        while(1){

            scanf("%d" , &tmp);
            system("cls");
            if(tmp==1 || tmp==2 || tmp==3){
                MapCopy( fpmap , strPlay , tmp);
                break;
            }
            else{
                system("cls");
                printf("\n\n\n                                     ");
                printf("Number is invalid , Please enter valid num.\n");
                printf("                                                       ");
                continue;
            }
        }
    }

    for(int i =0 ; i<20 ; i++){
        for(int j=0 ; strPlay[i][j]!='\0' ; j++){
            if(strPlay[i][j]=='@'){
                xPack=i;
                yPack=j;
                flag=1;
                break;
            }
        }
        if(flag)
        break;
    }

    Ghostnum=FindGhost(strPlay);
    Pillnum=FindPill(strPlay);
    wholeScore=5*Pillnum;
    //each Pill has 5 score.


    while(Ghostnum){
        ptmpG=GhostMake(pheadG , strPlay);
        if(pheadG==NULL)
        pheadG=ptmpG;
        Ghostnum--;
    }

    (*ptmp).Player.score=0;

    system("cls");
    printf("\n\n\n                                                ");
    printf("\033[1;36m");
    printf("Lets start the game!!\n\n");
    printf("                                                      ");
    printf("\033[1;33m");
    printf("Notice : \n\n");
    printf("                                            ");
    printf("if you want to go up enter w.\n");
    printf("                                           ");
    printf("if you want to go down enter s.\n");
    printf("                                            ");
    printf("if you want to go left enter a.\n");
    printf("                                           ");
    printf("if you want to go right enter d.\n");
    printf("                                                         ");
    
    
    
    
    
    Sleep(3000);
    system("cls");

    printf("\n\n\n                                                 ");
    printf("User Name : %s\n" , (* ptmp).Player.name);
    printf("                                                   ");
    printf("User Score : %d\n\n\n" , (*ptmp).Player.score);

    for(int i=0 ; strPlay[i][0] != '\0' ; i++){
        printf("                                         ");
        for(int j=0 ; strPlay[i][j] != '\0' ; j++){
            if(strPlay[i][j]=='@'){
                printf("\033[1;35m");
                printf("%c" , strPlay[i][j]);
            }
            else if(strPlay[i][j]=='G'){
                printf("\033[1;31m");
                printf("%c" , strPlay[i][j]);
            }
            else if(strPlay[i][j]=='P'){
                printf("\033[1;32m");
                printf("%c" , strPlay[i][j]);
            }
            else{
                printf("\033[1;36m");
                printf("%c" , strPlay[i][j]);
            }
            printf("   ");
        }
        printf("\n");
    }

    
    printf("\n\n                                   ");
    printf("\033[1;33m");
    printf("Whenever you want to stop yor game , Please enter p.\n");
    printf("                                                          ");
   

    while(1){

        if(kbhit()){

            tmpGhost=GhostMove(pheadG , strPlay);
            if(tmpGhost==-1){
                (*ptmp).Player.level--;
                system("cls");
                printf("\033[1;31m");
                printf("\n\n\n                                                     ");
                printf("\U0001F480GAMR OVER \U0001F480\n");
                Sleep(2000);
                system("cls");
                printf("\033[1;33m");
                break;
            }
            getchar();
            scanf("%c" , &ch);
        
            if(ch=='w'){
                tmpmove=CheckMap(3 , xPack , yPack , strPlay);
                if(tmpmove==-1){
                    (*ptmp).Player.level--;
                    system("cls");
                    printf("\033[1;31m");
                    printf("\n\n\n                                                     ");
                    printf("\U0001F480GAMR OVER \U0001F480\n");
                    Sleep(2000);
                    system("cls");
                    printf("\033[1;33m");
                    break;
                }
                else if(tmpmove==1){
                    (* ptmp).Player.score+=5;

                    if((* ptmp).Player.score==wholeScore){
                        (*ptmp).Player.level+=3;
                        system("cls");
                        printf("\033[1;32m");
                        printf("\n\n\n                                                     ");
                        printf("\U0001F388You Wonnnnn \U0001F388\n");
                        Sleep(2000);
                        system("cls");
                        printf("\033[1;33m");
                        break;
                    }
                    else{
                        xPacktmp=xPack;
                        xPack--;
                        strPlay[xPack][yPack]='.';
                        ctmpove=strPlay[xPack][yPack];
                        strPlay[xPack][yPack]=strPlay[xPacktmp][yPack];
                        strPlay[xPacktmp][yPack]=ctmpove;
                    }
                }
                else if(tmpmove==2){
                    xPacktmp=xPack;
                    xPack--;
                    strPlay[xPack][yPack]='.';
                    ctmpove=strPlay[xPack][yPack];
                    strPlay[xPack][yPack]=strPlay[xPacktmp][yPack];
                    strPlay[xPacktmp][yPack]=ctmpove;
                }
            }
            else if(ch=='s'){
                tmpmove=CheckMap(1 , xPack , yPack , strPlay);
                if(tmpmove==-1){
                    (*ptmp).Player.level--;
                    system("cls");
                    printf("\033[1;31m");
                    printf("\n\n\n                                                     ");
                    printf("\U0001F480GAMR OVER \U0001F480\n");
                    Sleep(2000);
                    system("cls");
                    printf("\033[1;33m");
                    break;
                }
                else if(tmpmove==1){

                    (* ptmp).Player.score+=5;

                    if((* ptmp).Player.score==wholeScore){
                        (*ptmp).Player.level+=3;
                        system("cls");
                        printf("\033[1;32m");
                        printf("\n\n\n                                                     ");
                        printf("\U0001F388You Wonnnnn \U0001F388\n");
                        Sleep(2000);
                        system("cls");
                        printf("\033[1;33m");
                        break;
                    }
                    else{
                        xPacktmp=xPack;
                        xPack++;
                        strPlay[xPack][yPack]='.';
                        ctmpove=strPlay[xPack][yPack];
                        strPlay[xPack][yPack]=strPlay[xPacktmp][yPack];
                        strPlay[xPacktmp][yPack]=ctmpove;
                    }
                }
                else if(tmpmove==2){
                    xPacktmp=xPack;
                    xPack++;
                    strPlay[xPack][yPack]='.';
                    ctmpove=strPlay[xPack][yPack];
                    strPlay[xPack][yPack]=strPlay[xPacktmp][yPack];
                    strPlay[xPacktmp][yPack]=ctmpove;
                }
            }
            else if(ch=='a'){
                tmpmove=CheckMap(4 , xPack , yPack , strPlay);
                if(tmpmove==-1){
                    (*ptmp).Player.level--;
                    system("cls");
                    printf("\033[1;31m");
                    printf("\n\n\n                                                     ");
                    printf("\U0001F480GAMR OVER \U0001F480\n");
                    Sleep(2000);
                    system("cls");
                    printf("\033[1;33m");
                    break;
                }
                else if(tmpmove==1){

                    (* ptmp).Player.score+=5;

                    if((* ptmp).Player.score==wholeScore){
                        (*ptmp).Player.level+=3;
                        system("cls");
                        printf("\033[1;32m");
                        printf("\n\n\n                                                     ");
                        printf("\U0001F388You Wonnnnn \U0001F388\n");
                        Sleep(2000);
                        system("cls");
                        printf("\033[1;33m");
                        break;
                    }
                    else{
                        yPacktmp=yPack;
                        yPack--;
                        strPlay[xPack][yPack]='.';
                        ctmpove=strPlay[xPack][yPack];
                        strPlay[xPack][yPack]=strPlay[xPack][yPacktmp];
                        strPlay[xPack][yPacktmp]=ctmpove;
                    }
                }
                else if(tmpmove==2){
                    yPacktmp=yPack;
                    yPack--;
                    strPlay[xPack][yPack]='.';
                    ctmpove=strPlay[xPack][yPack];
                    strPlay[xPack][yPack]=strPlay[xPack][yPacktmp];
                    strPlay[xPack][yPacktmp]=ctmpove;
                }
            }
            else if(ch=='d'){
                tmpmove=CheckMap(2 , xPack , yPack , strPlay);
                if(tmpmove==-1){
                    (*ptmp).Player.level--;
                    system("cls");
                    printf("\033[1;31m");
                    printf("\n\n\n                                                     ");
                    printf("\U0001F480GAMR OVER \U0001F480\n");
                    Sleep(2000);
                    system("cls");
                    printf("\033[1;33m");
                    break;
                }
                else if(tmpmove==1){

                    (* ptmp).Player.score+=5;

                    if((* ptmp).Player.score==wholeScore){
                        (*ptmp).Player.level+=3;
                        system("cls");
                        printf("\033[1;32m");
                        printf("\n\n\n                                                     ");
                        printf("\U0001F388You Wonnnnn \U0001F388\n");
                        Sleep(2000);
                        system("cls");
                        printf("\033[1;33m");
                        break;
                    }
                    else{
                        yPacktmp=yPack;
                        yPack++;
                        strPlay[xPack][yPack]='.';
                        ctmpove=strPlay[xPack][yPack];
                        strPlay[xPack][yPack]=strPlay[xPack][yPacktmp];
                        strPlay[xPack][yPacktmp]=ctmpove;
                    }
                }
                else if(tmpmove==2){
                    yPacktmp=yPack;
                    yPack++;
                    strPlay[xPack][yPack]='.';
                    ctmpove=strPlay[xPack][yPack];
                    strPlay[xPack][yPack]=strPlay[xPack][yPacktmp];
                    strPlay[xPack][yPacktmp]=ctmpove;
                }
            }
        
            else if(ch== 'p'){
                system("cls");
                printf("\n\n\n                           ");
                printf("If you want to save your uncomplete game enter y , if not enter n.\n");
                printf("                                                 ");
                getchar();
                scanf("%c" , &ctmp1);
                system("cls");
                if(ctmp1 =='y'){

                    (*ptmp).Player.condition=0;
                    for(int i=0 ; i<20 ; i++)
                    strcpy((*ptmp).Player.map[i] , strPlay[i]);

                }
                break;
            }

            system("cls");
            printf("\n\n\n                                                 ");
            printf("User Name : %s\n" , (* ptmp).Player.name);
            printf("                                                   ");
            printf("User Score : %d\n\n\n" , (*ptmp).Player.score);

            for(int i=0 ; strPlay[i][0] != '\0' ; i++){
                printf("                                         ");
                for(int j=0 ; strPlay[i][j] != '\0' ; j++){
                    if(strPlay[i][j]=='@'){
                        printf("\033[1;35m");
                        printf("%c" , strPlay[i][j]);
                    }
                    else if(strPlay[i][j]=='G'){
                        printf("\033[1;31m");
                        printf("%c" , strPlay[i][j]);
                    }
                    else if(strPlay[i][j]=='P'){
                        printf("\033[1;32m");
                        printf("%c" , strPlay[i][j]);
                    }
                    else{
                        printf("\033[1;36m");
                        printf("%c" , strPlay[i][j]);
                    }
                    printf("   ");
                }
                printf("\n");
            }
            printf("\n\n                                   ");
            printf("\033[1;33m");
            printf("Whenever you want to stop yor game , Please enter p.\n");
            printf("                                                          ");
   
        }
       
    }
       
    

}

void MapCopy(FILE * fpmap , char str[20][20], int mapnum ){

    if(mapnum==1)
    fread(str , 400 , 1 , fpmap);

    else if(mapnum==2){

        fseek(fpmap , 400 , SEEK_SET);
        fread(str , 400 , 1 , fpmap);

    }
    else if(mapnum==3){

        fseek(fpmap , 800 , SEEK_SET);
        fread(str , 400 , 1 , fpmap);

    }

}

int FindGhost(char str[20][20]){

    int i , j , counter=0;

    for(i=0 ; i<20 ; i++){
        for(j=0 ; str[i][j]!='\0' ; j++){
            if(str[i][j]=='G')
            counter++;
        }
    }
    return counter;
}

int FindPill(char str[20][20]){

    int i , j , counter=0;

    for(i=0 ; i<20 ; i++){
        for(j=0 ; str[i][j]!='\0' ; j++){
            if(str[i][j]=='P')
            counter++;
        }
    }
    return counter;
}

GhostMain * GhostMake(GhostMain * phead , char str[20][20]){

    GhostMain * ptmp = phead , * pnew ;
    static int counter=1;
    int x , y , i , j , flag =0;

    while(ptmp){
        if(ptmp->pnext)
        ptmp=ptmp->pnext;
        else
        break;
    }

    pnew=(GhostMain *)malloc(sizeof(GhostMain));
    pnew->pnext=NULL;

    
    for(i=0 ; i<20 ; i++){
        for(j=0 ; str[i][j]!='\0' ; j++){
            if(str[i][j]=='G'){
                (*pnew).ghost.xghost=i;
                (*pnew).ghost.yghost=j;
                counter--;
                if(counter==0){
                    flag++;
                    break;
                }
            }
        }
        if(flag)
        break;
    }

    if(phead)
    ptmp->pnext=pnew;

    return pnew;
}

int CheckMap( int a , int x , int y , char str[20][20]){

    if(a==1){

        x++;

        if(str[x][y]=='|' || str[x][y]=='-')
        return 0;
        else if(str[x][y]=='G')
        return -1;
        else if(str[x][y]=='P')
        return 1;
        else if(str[x][y]=='.')
        return 2;
    }

    else if(a==2){

        y++;

        if(str[x][y]=='|' || str[x][y]=='-')
        return 0;
        else if(str[x][y]=='G')
        return -1;
        else if(str[x][y]=='P')
        return 1;
        else if(str[x][y]=='.')
        return 2;

    }

    else if(a==3){

        x--;

        if(str[x][y]=='|' || str[x][y]=='-')
        return 0;
        else if(str[x][y]=='G')
        return -1;
        else if(str[x][y]=='P')
        return 1;
        else if(str[x][y]=='.')
        return 2;

    }

    else if(a==4){

        y--;

        if(str[x][y]=='|' || str[x][y]=='-')
        return 0;
        else if(str[x][y]=='G')
        return -1;
        else if(str[x][y]=='P')
        return 1;
        else if(str[x][y]=='.')
        return 2;

    }
}

int GhostMove(GhostMain * phead , char str[20][20]){

    GhostMain * ptmp = phead;
    int RandomMove , counter  = 1 , countertmp = 1 , flag =0 , j , jtmp , i , itmp;
    char ctmp;

    while(ptmp){

        countertmp++;
        counter=countertmp;
    
        RandomMove= rand()%4;

        if(RandomMove==0) {

            for(i=0 ; i<20 ; i++){
                for(j=0 ; str[i][j]!='\0' ; j++){
                    if(str[i][j]=='G'){
                        counter--;
                        if(counter==1){
                            jtmp=j++;
                            if(str[i][j]=='@')
                            return -1;
                            else if(str[i][j]== '.'){
                            ctmp=str[i][j];
                            str[i][j]=str[i][jtmp];
                            str[i][jtmp]=ctmp;
                            (*ptmp).ghost.yghost++;
                            }
                            else if(str[i][j]== 'P'){
                                jtmp=j++;
                                ctmp=str[i][j];
                                str[i][j]=str[i][jtmp];
                                str[i][jtmp]=ctmp;
                                (*ptmp).ghost.yghost+=2;
                            }
                            flag++;
                            break;
                        }
                    }
                }
                if(flag)
                break;
            }
        }

        else if(RandomMove==1) {

            for(i=0 ; i<20 ; i++){
                for(j=0 ; str[i][j]!='\0' ; j++){
                    if(str[i][j]=='G'){
                        counter--;
                        if(counter==1){
                            jtmp=j--;
                            if(str[i][j]=='@')
                            return -1;
                            if(str[i][j]== '.'){
                            ctmp=str[i][jtmp];
                            str[i][jtmp]=str[i][j];
                            str[i][j]=ctmp;
                            (*ptmp).ghost.yghost--;
                            }
                            else if(str[i][j]== 'P'){
                                jtmp=j--;
                                ctmp=str[i][j];
                                str[i][j]=str[i][jtmp];
                                str[i][jtmp]=ctmp;
                                (*ptmp).ghost.yghost-=2;
                            }
                            flag++;
                            break;
                        }
                    }
                }
                if(flag)
                break;
            }
        }

        else if(RandomMove==2) {

            for(i=0 ; i<20 ; i++){
                for(j=0 ; str[i][j]!='\0' ; j++){
                    if(str[i][j]=='G'){
                        counter--;
                        if(counter==1){
                            itmp=i++;
                            if(str[i][j]=='@')
                            return -1;
                            if(str[i][j]== '.'){
                            ctmp=str[i][j];
                            str[i][j]=str[itmp][j];
                            str[itmp][j]=ctmp;
                            (*ptmp).ghost.xghost++;
                            }
                            else if(str[i][j]== 'P'){
                                itmp=i--;
                                ctmp=str[i][j];
                                str[i][j]=str[itmp][j];
                                str[itmp][j]=ctmp;
                                (*ptmp).ghost.xghost-=2;
                            }
                            flag++;
                            break;
                        }
                    }
                }
                if(flag)
                break;
            }
        }

        else if(RandomMove==3) {

            (*ptmp).ghost.xghost--;

            for(i=0 ; i<20 ; i++){
                for(j=0 ; str[i][j]!='\0' ; j++){
                    if(str[i][j]=='G'){
                        counter--;
                        if(counter==1){
                            itmp=i++;
                            if(str[i][j]=='@')
                            return -1;
                            if(str[i][j]== '.'){
                            ctmp=str[i][j];
                            str[i][j]=str[itmp][j];
                            str[itmp][j]=ctmp;
                            (*ptmp).ghost.xghost++;
                            }
                            else if(str[i][j]== 'P'){
                                itmp=i++;
                                ctmp=str[i][j];
                                str[i][j]=str[itmp][j];
                                str[itmp][j]=ctmp;
                                (*ptmp).ghost.xghost+=2;
                            }
                            flag++;
                            break;
                        }
                    }
                }
                if(flag)
                break;
            }
        }
        ptmp=ptmp->pnext;
    }
}