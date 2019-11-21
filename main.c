#include <stdio.h>
#include <stdlib.h>
#include "cardprocessing.c"
#include "cardarray.c"
#include "SettingBettingOffering.c"
#include SumStatusCardnumCal.c
#include "CheckInitialEnd.c" 


#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;	
int totalCardNum = N_CARDSET * N_CARD;
int cardSetNum = N_CARDSET;
int roundNum = 0;
						


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold

//players hold
int cardSum[N_MAX_USER+1];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag  1:game end 
int userStatus[N_MAX_USER + 1];
int dealerDollar = 0; //dealer(server)�� �� �ݾ�  

//some utility functions

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	int cardIndex;
	int nGoStop;
	int cardnum;
	int playerResult;
	
 
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	n_user = configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		
		roundNum++;
		printf("\n\n-----------------ROUND %(cardIndex:%d)-------------------\n",roundNum,cardIndex);
		
		//player ���¸� �ʱ�ȭ
		plyerInitialization();
		
		//������ ����ƴ��� ���ο�  �Ļ��ڰ� �ִ��� Ȯ���ϱ�
		if(gameEnd() == 1) 
		 	break; //��������
			
		 
		betDollar();
		offerCards(); //1. give cards to all the players
		
	//������ ����ƴ����� Ȯ���ϱ�
		if(IsGameEnd() == 1){
			break; 
		} //��������
		
	//ROUND�� �����ϰ� 2�� �� ����� �Ŀ� card tray�� �ִ��� ���θ� Ȯ���ϱ� 	 
		
		if(EmptyCardTray() == 1){
			break;
		}//card tray�� ī�尡 �����Ǹ� ���� �����
		
		
		 
		//player�� �ʱ� ���¸� ����ϱ�  
		printCardInitialStatus(1);
		
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for (i=0; i < n_user + 1; i++) //each player
		{
			nGoStop = 1;
			while (nGoStop ==1 && userStatus[i] == 0) //do until the player dies or player says stop
			{
				cardnum = getReceivedCardNum(i); //���� ī�� ����� ���ϱ�  
				
				printUserCardStatus(i, cardnum) //print current card status printUserCardStatus();
				
				playerResult = calcStepResult(i);//check the card status ::: calcStepResult()
				                                 //���� player�� ������ ����ؼ� ���п��� �Ǵ��ϰ�, ��� �����Ҳ���..�Ǵ��ϱ�
												  
				//�հ������� 21���̸� ��, �� �̻� ī�带 ���� ����  
				if(playerResult == 4){
					if( i == n_user )
						prinf("[[[server result is ....%d ]]]\n\n",cardSum[i]);
						
					nGoStop = 0; //STOP
					continue;
				}
				
			if(i < n_user) //player�� ���
			{
				
				//�հ������� 21���� ũ�� ��  
				if(playerResult == 2){
					printf(" Lose!!");
					nGoStop = 0; //stop
					
				//������ ����ƴ��� ���� Ȯ��
				//player �� �� ���� �Ļ�(���� �ں��� ��� ����)�ϸ� ������ ����ǰ� ��
					if(isGameEnd() == 1)
						break; //���� ����!!
					
					//���� player�� �Ѿ   
					continue;
				}
			
				else if(platerResult == 3){
					
					printf("WIN(blackjack)");
					continue;
				}
			}
			
			if(i = 0){ 
				
				nGoStop = getAction();  //GO? STOP? ::: getAction()
				if(nGoStop == 1) {//Go
					cardhold[i][cardnum] = pullCard(); //ī�� 1���� �߰��� ����!! 
				}
				
				else{
					nGoStop = 0; //Stop
					printf("\n");
				}
			
			
			else{ //dealer(server)�� player�� ���!
				if(cardSum[i] < 17){ //���� ī������ 17�̸��̸� go!
					printf("::: Go!\n");
					cardhold[i][cardnum] = pullCard();
				}
			
				else {
					nGoStop = 0; //stop
					printf("Stay!\n\n");
				}
			
			}
			 
			
			//check if the turn ends or not
			//card tray�� ī�尡 �����ǰų� player �Ѹ��� �Ļ��ϸ� ��������!
			if(emptycardtray() == 1){
				
				break; //card tray�� ī�尡 �����Ǹ� ������ ����ȴ�. 
				
			} 
			
		}
		
		if(gameEnd == 1){
			break;
		} 
				
	}
	
		if(gameEnd == 0){
			checkResult(roundNum);
		}
		
	}
		
	
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
