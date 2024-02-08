#ifndef PACKMAN_H
#define PACKMAN_H  

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE2 "\033[1;34m"
#define PURPLE "\033[1;35m"
#define BLUE "\033[1;36m"
#define RESET "\033[1;37m"

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

void CursorMove(int , int);
/*
Description : this function change the cursor position.
Input : two integar that show the wanted positon .
Output : nothing.
*/
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
& a pointer to the head of our linked list which includes information .
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
& a pointer to the file to rewrite the information ( because we deleted one structure of linked list).
& also ID of the user who we want to delete his/her information.
Output : nothing.
*/
void Game( Main * , int , FILE *);
/*
Description : int this function the whole design of game has been done.
Input : a pointer to the head of our linked list which have user info & a pointer to the map file to read from .
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
Input : a pointer to the head of the ghost linked list & our game string to search and find position of our ghosts.
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
int GhostMove_2( int * , int * , char [20][20] , GhostMain * , int , int *, int * );
/*
Description : this function is only used to manage codes in last function better.
Out put : -1 means Game over , 1 means that ghost hitted the wall so it whould move again , 0 means that there is space toward our ghost.
*/
int PackmanMove(char , int , Main * , int * , int * , int , char [20][20] );
/*
Description : this function change the posiotion of packman in the wanted direction.
Input : a char that show which direction packman want to go & an integar that show which character 
( wall or pill or ghost ) is in the wanted position & a pointer to the user structure for changing level and score 
& two integar pointer that show packman position that will may be change in this function 
& an integar that show whole score of the game to see with each move doese packman win or not & our game string .
Output : an integar that if we won or loose or we should continue.
*/
void FreeMemmory(Main *);
/*
Description : this function release the memmory which we allocated for users.
Input : a pointer to the head of our linked list.
Output : nothing.
*/
void FreeMemmoryG(GhostMain *);
/*
Description : this function release the memmory which we allocated for ghosts.
Input : a pointer to the head of our linked list.
Output : nothing.
*/

#endif 