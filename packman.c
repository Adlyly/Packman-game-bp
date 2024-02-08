#include "packman.h"


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
    printf("\033[4;46H");
    printf("Please enter your name");
    printf("\033[5;46H");
    getchar();
    gets(strname);

    while(ptmp && strcmp( ptmp->Player.name , strname )){
        ptmp=ptmp->pnext;
    }

    if(ptmp==NULL){

        system("cls");
        printf("\033[4;40H");
        printf("There is no account with this name");
        Sleep(1500);
        system("cls");
        return 0;

    }
    
    else{

        system("cls");
        printf("\033[4;46H");
        printf("Please enter your password");
        printf("\033[5;46H");
                
        while(1){

            scanf("%d" , &pass);
            if(ptmp->Player.password==pass){
                system("cls");
                printf("\033[4;44H");
                printf("\u2022\u035C\u2022 You login successfuly \u2022\u035C\u2022");
                Sleep(1500);
                system("cls");
                return ptmp->Player.ID;
            }
            else{
                system("cls");
                printf("\033[4;38H");
                printf("password is wrong , Please enter correct password");
                printf("\033[5;60H");
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
    printf("\033[4;46H");
    printf("Please enter your username");
    printf("\033[5;46H");
    getchar();
    gets((*pnew).Player.name);

    while(ptmp1){

        if(strcmp(ptmp1->Player.name , (*pnew).Player.name )==0){
            system("cls");
            printf("\033[4;30H");
            printf("There is still an account with this user name which password is : %d" , ptmp1->Player.password );
            Sleep(1500);
            system("cls");
            return NULL;
        }
        else
        ptmp1=ptmp1->pnext;

    }
    system("cls");
    printf("\033[4;46H");
    printf("Please enter your password");
    printf("\033[5;46H");
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

    fclose(fp);


}

void FreeMemmory(Main * phead){

    Main * ptmp1 = phead , * ptmp2=phead;

    while(ptmp1){

        ptmp2=ptmp1->pnext;
        free((void*)ptmp1);
        ptmp1=ptmp2;

    }

}

void FreeMemmoryG(GhostMain * phead){

    GhostMain * ptmp1 = phead , * ptmp2=phead;

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
    printf("\n\n");
    printf("                                                 ");
    printf("User Name : %s\n" , (* ptmp).Player.name);
    printf("                                                   ");
    printf("User ID : %d\n" , (* ptmp).Player.ID);
    printf("                                                 ");
    printf("User Level : %d\n" , (* ptmp).Player.level);
    printf("                                               ");
    printf("User Password : %d\n" , (* ptmp).Player.password);

    if((* ptmp).Player.condition == 0){
        
        printf("                                         ");
        printf("The user has an uncomplete game\n");
        printf("                                                  ");
        printf("that game is :\n\n");

        int x=8 , y=33 , xtmp;
        CursorMove(y , x);
        for(int i=0 ; (*ptmp).Player.map[i][0] !='\0'; i++){
            for(int j=0 ; (*ptmp).Player.map[i][j]!='\0' ; j++){
                if((*ptmp).Player.map[i][j]=='G'){
                    printf(RED);
                    printf("\u2022\u0060O\u00B4\u2022");
                    y+=5;
                }
                else if((*ptmp).Player.map[i][j]=='P'){
                    y+=5;
                    printf(GREEN);
                    printf("  \u2665  ");
                }
                else if((*ptmp).Player.map[i][j]=='@'){
                    printf(YELLOW);
                    printf(" ^\u1D25^ ");
                    y+=5;
                }
                else if((*ptmp).Player.map[i][j]=='|'|| (*ptmp).Player.map[i][j]=='-'){
                    printf(BLUE);
                    printf("\u2022\u2022\u2022\u2022\u2022");
                    xtmp=x;
                    xtmp++;
                    CursorMove(y,xtmp);
                    printf("\u2022\u2022\u2022\u2022\u2022");

                    y+=5;
                    CursorMove(y , x);
                }
                else if((*ptmp).Player.map[i][j]=='.'){
                    printf("     ");
                    y+=5;
                }
            }
        x+=2;
        y=33;
        CursorMove(y , x);
        }

        printf(YELLOW);
        printf("\n                                    ");
        printf("and the score of this uncomplete game is : %d\n\n" , (* ptmp).Player.score);

    }
    else{
        printf("                                    ");
        printf("The user doesnt have any uncomplete game.");
    }

    Sleep(3000);
    system("cls");
}

void CursorMove(int x, int y){

    COORD pos={x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);
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
    int Ghostnum , Pillnum , tmp , tmpPack , tmpmove , wholeScore , xPack  , yPack , flag =0 , tmpGhost , flag2=0 , x , y , xtmp;
    char strPlay[20][20] , ctmp , ctmp1 , ctmpove , ch;
    FILE * fpmap;
    GhostMain * pheadG=NULL , * ptmpG;

    fpmap=fopen("MyMap.bin" , "r+b");
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
    printf(BLUE);
    printf("Lets start the game!!\n\n");
    printf("                                                      ");
    printf(YELLOW);
    printf("Notice : \n\n");
    printf("                                            ");
    printf("if you want to go up enter w.\n");
    printf("                                           ");
    printf("if you want to go down enter s.\n");
    printf("                                           ");
    printf("if you want to go left enter a.\n");
    printf("                                           ");
    printf("if you want to go right enter d.\n");
    printf("                                                         ");
    
    Sleep(3000);
    system("cls");

    printf("\n                                                 ");
    printf("User Name : %s\n" , (* ptmp).Player.name);
    printf("                                                   ");
    printf("User Score : %d\n\n" , (*ptmp).Player.score);

    x=4 , y=33 ;
    CursorMove(y , x);
    for(int i=0 ; strPlay[i][0] !='\0'; i++){
        for(int j=0 ; strPlay[i][j]!='\0' ; j++){
            if(strPlay[i][j]=='G'){
                printf(RED);
                printf("\u2022\u0060O\u00B4\u2022");
                y+=5;
            }
            else if(strPlay[i][j]=='P'){
                y+=5;
                printf(GREEN);
                printf("  \u2665  ");
            }
            else if(strPlay[i][j]=='@'){
                printf(YELLOW);
                printf(" ^\u1D25^ ");
                y+=5;
            }
            else if(strPlay[i][j]=='|'|| strPlay[i][j]=='-'){
                printf(BLUE);
                printf("\u2022\u2022\u2022\u2022\u2022");
                xtmp=x;
                xtmp++;
                CursorMove(y,xtmp);
                printf("\u2022\u2022\u2022\u2022\u2022");
        
                y+=5;
                CursorMove(y , x);
            }
            else if(strPlay[i][j]=='.'){
                printf("     ");
                y+=5;
            }
    }
    x+=2;
    y=33;
    CursorMove(y , x);
    }
    
    printf("\n                                   ");
    printf(YELLOW);
    printf("Whenever you want to stop yor game , Please enter p.\n");
    printf("                                                          ");
   
    while(1){

        if(kbhit()){

            ch=_getch();
            while(ch!='w'  && ch!='a' && ch!='s'  && ch!='d' && ch!='p')
            ch=_getch();

        
            if(ch=='w'){
                tmpmove=CheckMap(3 , xPack , yPack , strPlay);
                tmpPack=PackmanMove( 'w' , tmpmove , ptmp , &xPack , &yPack , wholeScore , strPlay );
                
                if(tmpPack == 0)
                break;
            }
            else if(ch=='s'){
                tmpmove=CheckMap(1 , xPack , yPack , strPlay);
                tmpPack=PackmanMove( 's' , tmpmove , ptmp , &xPack , &yPack , wholeScore , strPlay );
                
                if(tmpPack == 0)
                break;
            }
            else if(ch=='a'){
                tmpmove=CheckMap(4 , xPack , yPack , strPlay);
                tmpPack=PackmanMove( 'a' , tmpmove , ptmp , &xPack , &yPack , wholeScore , strPlay );
                
                if(tmpPack == 0)
                break;
            }
            else if(ch=='d'){
                tmpmove=CheckMap(2 , xPack , yPack , strPlay);
                tmpPack=PackmanMove( 'd' , tmpmove , ptmp , &xPack , &yPack , wholeScore , strPlay );
                
                if(tmpPack == 0)
                break;
            }
        
            else if(ch== 'p'){
                system("cls");
                printf("\n\n\n                           ");
                printf("If you want to save your uncomplete game enter y , if not enter n.\n");
                printf("                                                       ");
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
   
        }

        tmpGhost=GhostMove(pheadG , strPlay);
        if(tmpGhost==-1){
            (*ptmp).Player.level--;
            system("cls");
            printf(RED);
            printf("\n\n\n                                              ");
            printf("\u00B4\u2022\u032A\u2022\u0060 GAMR OVER \u00B4\u2022\u032A\u2022\u0060\n");
            Sleep(2000);
            system("cls");
            printf(YELLOW);
            break;
        }

        system("cls");
        printf("\n                                                 ");
        printf("User Name : %s\n" , (* ptmp).Player.name);
        printf("                                                   ");
        printf("User Score : %d\n\n" , (*ptmp).Player.score);

        
    x=4 , y=33;
    CursorMove(y , x);
    for(int i=0 ; strPlay[i][0]!='\0'; i++){
        for(int j=0 ; strPlay[i][j]!='\0' ; j++){
            if(strPlay[i][j]=='G'){
                printf(RED);
                printf("\u2022\u0060O\u00B4\u2022");
                y+=5;
            }
            else if(strPlay[i][j]=='P'){
                y+=5;
                printf(GREEN);
                printf("  \u2665  ");
            }
            else if(strPlay[i][j]=='@'){
                printf(YELLOW);
                printf(" ^\u1D25^ ");
                y+=5;
            }
            else if(strPlay[i][j]=='|'|| strPlay[i][j]=='-'){
                printf(BLUE);
                printf("\u2022\u2022\u2022\u2022\u2022");
                xtmp=x;
                xtmp++;
                CursorMove(y,xtmp);
                printf("\u2022\u2022\u2022\u2022\u2022");
        
                y+=5;
                CursorMove(y , x);
            }
            else if(strPlay[i][j]=='.'){
                printf("     ");
                y+=5;
            }
    }
    x+=2;
    y=33;
    CursorMove(y , x);
    }
        printf("\n                                   ");
        printf(YELLOW);
        printf("Whenever you want to stop yor game , Please enter p.\n");
        printf("                                                          ");
        Sleep(500);
       
    }

    FreeMemmoryG(pheadG);

}

int PackmanMove(char ctmp , int tmpmove , Main * ptmp , int * xPack , int * yPack , int wholeScore , char strPlay [20][20] ){

    int xPacktmp=*xPack , yPacktmp=*yPack ;
    char ctmpove ;

    if(tmpmove==-1){
        (*ptmp).Player.level--;
        system("cls");
        printf(RED);
        printf("\n\n\n                                              ");
        printf("\u00B4\u2022\u032A\u2022\u0060 GAMR OVER \u00B4\u2022\u032A\u2022\u0060\n");
        Sleep(2000);
        system("cls");
        printf(YELLOW);
        return 0;
                    
    }
    else if(tmpmove==1){
        (* ptmp).Player.score+=5;
        if((* ptmp).Player.score==wholeScore){
            (*ptmp).Player.level+=3;
            system("cls");
            printf(GREEN);
            printf("\n\n\n                                               ");
            printf("\u2022\u033A\u2022 You Wonnnnn \u2022\u033A\u2022");
            Sleep(2000);
            system("cls");
            printf(YELLOW);
            return 0;
                        
        }
        else{
            if(ctmp=='w')
            (*xPack)--;
            else if(ctmp=='a')
            (*yPack)--;
            else if(ctmp=='s')
            (*xPack)++;
            else if(ctmp=='d')
            (*yPack)++;
            strPlay[*xPack][*yPack]='.';

            ctmpove=strPlay[*xPack][*yPack];
            strPlay[*xPack][*yPack]=strPlay[xPacktmp][yPacktmp];
            strPlay[xPacktmp][yPacktmp]=ctmpove;
            return 1;
        }
    }
    else if(tmpmove==2){
        if(ctmp=='w')
        (*xPack)--;
        else if(ctmp=='a')
        (*yPack)--;
        else if(ctmp=='s')
        (*xPack)++;
        else if(ctmp=='d')
        (*yPack)++;

        ctmpove=strPlay[*xPack][*yPack];
        strPlay[*xPack][*yPack]=strPlay[xPacktmp][yPacktmp];
        strPlay[xPacktmp][yPacktmp]=ctmpove;
        return 1;
    }
    else
    return 1;

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
    int RandomMove , counter  = 1 , countertmp = 1 , j , i , xtmp , flag=0 , flag2=1 ;

    //flag is used to see if the ghost has found in the array or not
    //flag2 is used to see if the doesnt want to move to position which is wall

    while(ptmp){

        countertmp++;
        counter=countertmp;

        while(1){
    
            RandomMove= rand()%4;

            if(RandomMove==0) {

                xtmp=GhostMove_2(&counter , &countertmp , str , ptmp , 0 , &flag , &flag2);
                if(xtmp==-1)
                return -1;
                else if(xtmp==0)
                break;
                else if(xtmp==1)
                continue;
                
            }

            else if(RandomMove==1) {

                xtmp=GhostMove_2(&counter , &countertmp , str , ptmp , 1 , &flag , &flag2);
                if(xtmp==-1)
                return -1;
                else if(xtmp==0)
                break;
                else if(xtmp==1)
                continue;
                
            }

            else if(RandomMove==2) {

                xtmp=GhostMove_2(&counter , &countertmp , str , ptmp , 2 , &flag , &flag2);
                if(xtmp==-1)
                return -1;
                else if(xtmp==0)
                break;
                else if(xtmp==1)
                continue;

            }

            else if(RandomMove==3) {

                xtmp=GhostMove_2(&counter , &countertmp , str , ptmp , 3 , &flag , &flag2);
                if(xtmp==-1)
                return -1;
                else if(xtmp==0)
                break;
                else if(xtmp==1)
                continue;

            }
        }
        ptmp=ptmp->pnext;
        flag=0;
        flag2=1;
    }
}

int GhostMove_2( int * counter  , int * countertmp , char str[20][20] , GhostMain * ptmp , int x, int * flag , int * flag2){

    int i , j , itmp , jtmp ;
    char ctmp;

    for(i=0 ; str[i][0]!='\0' ; i++){
        for(j=0 ; str[i][j]!='\0' ; j++){
            if(str[i][j]=='G'){
                (*counter)--;
                if((*counter)==1){
                    if(x==0){
                        itmp=i;
                        jtmp=j++;
                    }
                    else if(x==1){
                        itmp=i;
                        jtmp=j--;
                    }
                    else if(x==2){
                        itmp=i++;
                        jtmp=j;
                    }
                    else if(x==3){
                        itmp=i--;
                        jtmp=j;
                    }
                    if(str[i][j]=='@')
                    return -1;
                    if(str[i][j]== '.'){
                    ctmp=str[i][j];
                    str[i][j]=str[itmp][jtmp];
                    str[itmp][jtmp]=ctmp;
                    (*ptmp).ghost.xghost--;
                    }
                    else if( str[i][j]== '-' || str[i][j]== '|'){
                        *counter=*countertmp;
                        *flag2=0;
                    }

                    (*flag)++;
                    break;
                }
            }
    }
        if(*flag)
        break;
    }
    if(*flag2)
    return 0;
    else {
        *flag=0;
        *flag2=1;
        return 1;
    }
}