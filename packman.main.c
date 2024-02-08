#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "packman.h"

int main()
{

    SetConsoleOutputCP(65001);

    FILE * fp ;
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
    printf("\033[4;44H");
    printf(BLUE2);
    printf("Welcome ");
    printf(GREEN);
    printf("To ");
    printf(BLUE);
    printf("Pack ");
    printf(PURPLE);
    printf("Man ");
    printf(RED);
    printf("Game :D");
    Sleep(3000);


    while(1){
        
        system("cls");
        printf("\033[3;41H");
        printf(YELLOW);
        for(int i=0 ; i<37 ; i++)
        printf("\u263B");
        printf("\033[4;41H");
        printf("if you want to login , Please enter 1\n");
        printf("\033[5;35H");
        printf("if you want to make an account , Please enter 2\n");
        printf("\033[6;41H");
        printf("if you want to exit , Please enter 0\n");
        printf("\033[7;41H");
        for(int i=0 ; i<37 ; i++)
        printf("\u263B");
        printf("\033[8;58H");
        

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
                    printf("\033[4;39H");
                    printf("\u2022\u035C\u2022 Your account is made successfuly \u2022\u035C\u2022");
                    Sleep(2000);
                    system("cls");
                }
                else
                continue;
            }

            while(1){
                
                printf(YELLOW);
                printf("\033[4;40H");
                printf("Please enter 1 for Review information");
                printf("\033[5;45H");
                printf("Please enter 2 to start game");
                printf("\033[6;40H");
                printf("Please enter 3 to delete your account");
                printf("\033[7;46H");
                printf("Please enter 0 to logout");
                printf("\033[8;56H");

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
                    printf("\033[4;39H");
                    printf("\u2022\u035C\u2022 Your account deleted successfuly \u2022\u035C\u2022");
                    Sleep(1500);
                    system("cls");
                    break;
                }
                    
                if(tmp==0)
                break;

            }
            
            printf("\033[4;39H");
            printf("Do you want to login/make another account?");
            printf("\033[5;42H");
            printf("if you want enter y , if not enter n");
            printf("\033[6;58H");
            getchar();
            scanf("%c" , &c);
            system("cls");
            if(c=='n')
            break;
        }
        else
            break;
    }

    system("cls");
    printf("\033[4;45H");
    printf(BLUE2);
    printf("Hope ");
    printf(GREEN);
    printf("you ");
    printf(RED);
    printf("have ");
    printf(PURPLE);
    printf("a good ");
    printf(BLUE);
    printf("game :)");
    Sleep(2000);

    fclose(fp);
    FreeMemmory(phead);

    return 0;

}

