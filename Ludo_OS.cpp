/*
Member 1 Name: Muhammad Saad Bajwa
Member 1 Roll: 19i-1974
Member 2 Name: Fajr Naveed
Member 2 Roll: 19i-0436
*/

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

char board[88];
int dice;
int player1hometokencount=0;
int player2hometokencount=0;
int player3hometokencount=0;
int player4hometokencount=0;
pthread_t master,player1,player2,player3,player4;
sem_t semplayer1,semplayer2,semplayer3,semplayer4;
int semaphorecount=0;

typedef struct//Player structure
{
string playername="";
bool hitrate=false;
int tokens=4;
int wintokens=0;
int tokensinhome[4]={0,0,0,0};
int *arr;
}player;

player p1,p2,p3,p4;

void printgrid()//Prints Grid
{
	cout << "1 " << "1 " << "1 " << "1 " << "1 " << "1 " << board[26] << " " << board[27] << " " << board[33] << " " << "2 " << "2 " << "2 " << "2 " << "2 " << "2 " << endl;
	cout << "1 " << "  " << "  " << "  " << "  " << "1 " << board[25] << " " << board[28] << " " << board[34] << " " << "2 " << "  " << "  " << "  " << "  " << "2 " << endl;
	cout << "1 " << "  " << board[0] << " " << board[1] << " " << "  " << "1 " << board[24] << " " << board[29] << " " << board[35] << " " << "2 " << "  " << board[4] << " " << board[5] << " " << "  " << "2 " << endl;
	cout << "1 " << "  " << board[2] << " " << board[3] << " " << "  " << "1 " << board[23] << " " << board[30] << " " << board[36] << " " << "2 " << "  " << board[6] << " " << board[7] << " " << "  " << "2 " << endl;
	cout << "1 " << "  " << "  " << "  " << "  " << "1 " << board[22] << " " << board[31] << " " << board[37] << " " << "2 " << "  " << "  " << "  " << "  " << "2 " << endl;
	cout << "1 " << "1 " << "1 " << "1 " << "1 " << "1 " << board[21] << " " << board[32] << " " << board[38] << " " << "2 " << "2 " << "2 " << "2 " << "2 " << "2 " << endl;
	cout << board[87] << " " << board[16] << " " << board[17] << " " << board[18] << " " << board[19] << " " << board[20] << " " << "1 " << "2 " << "4 " << board[39] << " " << board[40] << " " << board[41] << " " << board[42] << " " << board[43] << " " << board[44] << endl;
	cout << board[81] << " " << board[82] << " " << board[83] << " " << board[84] << " " << board[85] << " " << board[86] << " " << "1 " << "2 " << "4 " << board[50] << " " << board[49] << " " << board[48] << " " << board[47] << " " << board[46] << " " << board[45] << endl;
	cout << board[80] << " " << board[79] << " " << board[78] << " " << board[77] << " " << board[76] << " " << board[75] << " " << "1 " << "3 " << "4 " << board[56] << " " << board[55] << " " << board[54] << " " << board[53] << " " << board[52] << " " << board[51] << endl;
	cout << "3 " << "3 " << "3 " << "3 " << "3 " << "3 " << board[74] << " " << board[68] << " " << board[57] << " " << "4 " << "4 " << "4 " << "4 " << "4 " << "4 " << endl;
	cout << "3 " << "  " << "  " << "  " << "  " << "3 " << board[73] << " " << board[67] << " " << board[58] << " " << "4 " << "  " << "  " << "  " << "  " << "4 " << endl;
	cout << "3 " << "  " << board[8] << " " << board[9] << " " << "  " << "3 " << board[72] << " " << board[66] << " " << board[59] << " " << "4 " << "  " << board[12] << " " << board[13] << " " << "  " << "4 " << endl;
	cout << "3 " << "  " << board[10] << " " << board[11] << " " << "  " << "3 " << board[71] << " " << board[65] << " " << board[60] << " " << "4 " << "  " << board[14] << " " << board[15] << " " << "  " << "4 " << endl;
	cout << "3 " << "  " << "  " << "  " << "  " << "3 " << board[70] << " " << board[64] << " " << board[61] << " " << "4 " << "  " << "  " << "  " << "  " << "4 " << endl;
	cout << "3 " << "3 " << "3 " << "3 " << "3 " << "3 " << board[69] << " " << board[63] << " " << board[62] << " " << "4 " << "4 " << "4 " << "4 " << "4 " << "4 " << endl;
  cout<<endl;
}

void *playermovfunc(void *arg)//player movement
{
    if(semaphorecount==0)
    {
      sem_wait(&semplayer2);
      sem_wait(&semplayer3);
      sem_wait(&semplayer4);
    }
    else if (semaphorecount==1)
    {
      sem_wait(&semplayer1);
      sem_wait(&semplayer3);
      sem_wait(&semplayer4);
    }
    else if (semaphorecount==2)
    {
      sem_wait(&semplayer1);
      sem_wait(&semplayer2);
      sem_wait(&semplayer4);
    }
    else if(semaphorecount==3)
    {
      sem_wait(&semplayer1);
      sem_wait(&semplayer2);
      sem_wait(&semplayer3);
    }
   int player1traversal[] = {16,17,18,19,20,21,22,23,24,25,26,27,33,34,35,36,37,38,39,40,41,42,43,44,45,51,52,53,54,55,56,57,58,59,60,61,62,63,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86};
   int player2traversal[] = {34,35,36,37,38,39,40,41,42,43,44,45,51,52,53,54,55,56,57,58,59,60,61,62,63,69,70,71,72,73,74,75,76,77,78,79,80,81,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
   int player3traversal[] = {70,71,72,73,74,75,76,77,78,79,80,81,16,17,18,19,20,21,22,23,24,25,26,27,33,34,35,36,37,38,39,40,41,42,43,44,45,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68};
   int player4traversal[] = {52,53,54,55,54,57,58,59,60,61,62,63,69,70,71,72,73,74,75,76,77,78,79,80,81,16,17,78,19,20,21,22,23,24,25,26,27,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
   p1.arr=new int[56];
   for (int i=0;i<56;i++){
    p1.arr[i]=player1traversal[i];
   }
   p2.arr=new int[55];
   for (int i=0;i<55;i++){
    p2.arr[i]=player2traversal[i];
   }
   p3.arr=new int[55];
   for (int i=0;i<55;i++){
    p3.arr[i]=player3traversal[i];
   }
   p4.arr=new int[55];
   for (int i=0;i<55;i++){
    p4.arr[i]=player4traversal[i];
   }
   int player1traverse = 0;
   int player2traverse = 0;
   int player3traverse = 0;
   int player4traverse = 0;
   srand(time(0));
	 int times=0;
	 int oldposition1 = player1traverse;
	 int newposition1 = oldposition1;
	 int oldposition2 = player2traverse;
	 int newposition2 = oldposition2;
	 int oldposition3 = player3traverse;
	 int newposition3 = oldposition3;
	 int oldposition4 = player4traverse;
	 int newposition4 = oldposition4;
	 int tempvar=0;
	 int traversal=0;
	 while(times<36 || (p1.wintokens==4) || (p2.wintokens==4) || (p3.wintokens==4) || (p4.wintokens==4)){
	 sleep(2);
   dice = rand() % 6 + 1;
   cout<<"The number is "<<dice<<endl;
   if (dice==6){
	 int var=dice;
   int tempsix = 0;
   int sixcount = 0;
   while (dice == 6)
   {
     cout<<"6 rolled! "<<endl;
	   if (sixcount < 2) {
		   tempsix = dice;
		   dice = rand() % 6 + 1;
		   dice += tempsix;
		   sixcount++;
	   }
	   else
	   {
       cout<<"Six Greater than 2 times!"<<endl;
		   dice=0;
	   }
   }
   cout << "The number is: " << dice << endl;
	 if (traversal==0 || traversal==4 || traversal==8 || traversal==12 || traversal==16 || traversal==20){
	 			oldposition1=newposition1;
   			newposition1=oldposition1+dice;
	 }
	 else if (traversal==1 || traversal==5 || traversal==9 || traversal==13 || traversal==17 || traversal==21){
				oldposition2=newposition2;
					newposition2=oldposition2+dice;
	 }
	 else if (traversal==2 || traversal==6 || traversal==10 || traversal==14 || traversal==18 || traversal==22){
				oldposition3=newposition3;
					newposition3=oldposition3+dice;
	 }
	 else {
				oldposition4=newposition4;
					newposition4=oldposition4+dice;
	 }
	 int pos;
	 if(traversal==0 || traversal==4 || traversal==8 || traversal==12 || traversal==16 || traversal==20){
   pos = player1traversal[newposition1];
	 board[0]=' ';
	 p1.tokensinhome[player1hometokencount]=1;
	 player1hometokencount++;
 	 }
	 else if (traversal==1 || traversal==5 || traversal==9 || traversal==13 || traversal==17 || traversal==21){
	 pos = player2traversal[newposition2];
	 board[4]=' ';
	 p2.tokensinhome[player2hometokencount]=1;
	 player2hometokencount++;
 	 }
	 else if (traversal==2 || traversal==6 || traversal==10 || traversal==14 || traversal==18 || traversal==22){
	 pos = player3traversal[newposition3];
	 board[8]=' ';
	 p3.tokensinhome[player3hometokencount]=1;
	 player3hometokencount++;
 	 }
	 else {
	 pos = player4traversal[newposition4];
	 board[12]=' ';
	 p4.tokensinhome[player4hometokencount]=1;
	 player4hometokencount++;
   }
   cout << "The traverse is: " << pos << endl;
	 if (traversal==0 || traversal==4 || traversal==8 || traversal==12 || traversal==16 || traversal==20)
   board[pos] = '1';
	 else if (traversal==1 || traversal==5 || traversal==9 || traversal==13 || traversal==17 || traversal==21)
	 board[pos] = '2';
	 else if(traversal==2 || traversal==6 || traversal==10 || traversal==14 || traversal==18 || traversal==22)
	 board[pos] = '3';
	 else
	 board[pos] = '4';
   }
	 times++;
	 traversal++;
   printgrid();
   if(semaphorecount==0)
   {
     sem_post(&semplayer2);
     sem_post(&semplayer3);
     sem_post(&semplayer4);
     if(p1.wintokens==4)
     pthread_cancel(pthread_self());
   }
   else if (semaphorecount==1)
   {
     sem_post(&semplayer1);
     sem_post(&semplayer3);
     sem_post(&semplayer4);
     if(p2.wintokens==4)
     pthread_cancel(pthread_self());
   }
   else if (semaphorecount==2)
   {
     sem_post(&semplayer1);
     sem_post(&semplayer2);
     sem_post(&semplayer4);
     if(p3.wintokens==4)
     pthread_cancel(pthread_self());
   }
   else if(semaphorecount==3)
   {
     sem_post(&semplayer1);
     sem_post(&semplayer2);
     sem_post(&semplayer3);
     if(p4.wintokens==4)
     pthread_cancel(pthread_self());
   }
   semaphorecount++;
   if (semaphorecount>=3)
   semaphorecount=0;
   }
pthread_exit(NULL);
}

void *Master_func(void *arg )//Master thread
{
printgrid();
cout<<"Enter the number of tokens: ";
cin>>p1.tokens;
while (p1.tokens<1 || p1.tokens>4){
  cout<<"Enter the number of tokens again! ";
  cin>>p1.tokens;
}
p2.tokens=p1.tokens;
p3.tokens=p1.tokens;
p4.tokens=p1.tokens;
cout<<endl;
sem_init(&semplayer1,0,1);
sem_init(&semplayer2,0,1);
sem_init(&semplayer3,0,1);
sem_init(&semplayer4,0,1);
pthread_create(&player1, NULL,playermovfunc ,NULL);
pthread_join(player1,NULL) ;
pthread_create(&player2, NULL,playermovfunc ,NULL);
pthread_join(player2,NULL) ;
pthread_create(&player3, NULL,playermovfunc ,NULL);
pthread_join(player3,NULL) ;
pthread_create(&player4, NULL,playermovfunc ,NULL);
pthread_join(player4,NULL) ;
printgrid();
pthread_exit(NULL);
}

int main()
{

 cout << "<<<<<<<<<<<<<<<<<<<<<<<Ludo Grid!>>>>>>>>>>>>>>>>"<<endl;
   cout << endl;
   cout<<"Enter the name of player1: ";
   cin>>p1.playername;
   cout<<"Enter the name of player2: ";
   cin>>p2.playername;
   cout<<"Enter the name of player3: ";
   cin>>p3.playername;
   cout<<"Enter the name of player4: ";
   cin>>p4.playername;
   cout<<endl;
   cout << "Player 1: 1" << "  Name: "<<p1.playername<<endl;
   cout << "Player 2: 2" << "  Name: "<<p2.playername<< endl;
   cout << "Player 3: 3" << "  Name: "<<p3.playername<< endl;
   cout << "Player 4: 4" << "  Name: "<<p4.playername<< endl;
   cout << "\t \t \t \t \t Ludo Grid!"<<endl;
   cout << endl;
   /*char grid[15][15] = {'1','1','1','1','1','1','0','0','0','2','2','2','2','2','2',{'1',' ',' ',' ',' ','1','0','2','2','2',' ',' ',' ',' ','2'},{'1',' ','1','1',' ','1','9','2','0','2',' ','2','2',' ','2'},{'1',' ','1','1',' ','1','0','2','0','2',' ','2','2',' ','2'},{'1',' ',' ',' ',' ','1','0','2','0','2',' ',' ',' ',' ','2'},{'1','1','1','1','1','1','0','2','0','2','2','2','2','2','2'},{'0','1','0','0','0','0','1','2','4','0','0','0','9','0','0'},{'0','1','1','1','1','1','1','2','4','4','4','4','4','4','0'},{'0','0','9','0','0','0','1','3','4','0','0','0','0','4','0'},{'3','3','3','3','3','3','0','3','0','4','4','4','4','4','4'},{'3',' ',' ',' ',' ','3','0','3','0','4',' ',' ',' ',' ','4'},{'3',' ','3','3',' ','3','0','3','0','4',' ','4','4',' ','4'},{'3',' ','3','3',' ','3','0','3','9','4',' ','4','4',' ','4'},{'3',' ',' ',' ',' ','3','3','3','0','4',' ',' ',' ',' ','4'},{'3','3','3','3','3','3','0','0','0','4','4','4','4','4','4'} };
   char player1stratingindex=grid[6][1];
   char player2stratingindex = grid[1][8];
   char player3stratingindex = grid[13][7];
   char player4stratingindex = grid[8][13];
   cout << "starting indes is: " << player1stratingindex;
   cout << "starting indes is: " << player2stratingindex;
   cout << "starting indes is: " << player3stratingindex;
   cout << "starting indes is: " << player4stratingindex;
   system("cls");
   grid[2][2] = ' ';
   grid[2][3] = ' ';
   for (int i = 0;i < 15;i++)
   {
	   for (int j = 0;j < 15;j++)
	   {
		   cout << grid[i][j] << " ";
	   }
	   cout << endl;
	   //cout << "\t\t\t\t";
   }*/
   for (int i = 0;i <=15;i++)
   {
	   if (i <= 3)
	   {
		   board[i] = '1';
	   }
	   else if (i > 3 && i <= 7)
	   {
		   board[i] = '2';
	   }
	   else if (i > 7 && i <= 11)
	   {
		   board[i] = '3';
	   }
	   else
	   {
		   board[i] = '4';
	   }
   }
   int player1startingindex = 16;
   board[player1startingindex] = '1';
   int count = 0;
   for (int i = 17;i <= 27;i++)
	   board[i] = '0';
   for (int i = 28;i <= 32;i++)
	   board[i] = '2';
   board[33] = '0';
   int player2startingindex = 34;
   board[player2startingindex] = '2';
   for (int i = 35;i <= 45;i++)
	   board[i] = '0';
   for (int i = 46;i <= 50;i++)
	   board[i] = '4';
   board[51] = '0';
   int player4startingindex = 52;
   board[player4startingindex] = '4';
   for (int i = 53;i <= 63;i++)
	   board[i] = '0';
   for (int i = 64;i <= 68;i++)
	   board[i] = '3';
   board[69] = '0';
   int player3startingindex = 70;
   board[player3startingindex] = '3';
   for (int i = 71;i <= 81;i++)
	   board[i] = '0';
   for (int i = 82;i <= 86;i++)
	   board[i] = '1';
   board[87] = '0';
   cout << endl;
   pthread_create(&master,NULL,Master_func,NULL) ;
   pthread_join(master,NULL);
   return 0;
}
