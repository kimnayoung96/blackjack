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
int dealerDollar = 0; //dealer(server)가 딴 금액  

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
		
		//player 상태를 초기화
		plyerInitialization();
		
		//게임이 종료됐는지 여부와  파산자가 있는지 확인하기
		if(gameEnd() == 1) 
		 	break; //게임종료
			
		 
		betDollar();
		offerCards(); //1. give cards to all the players
		
	//게임이 종료됐는지를 확인하기
		if(IsGameEnd() == 1){
			break; 
		} //게임종료
		
	//ROUND가 시작하고 2장 씩 배분한 후에 card tray가 있는지 여부를 확인하기 	 
		
		if(EmptyCardTray() == 1){
			break;
		}//card tray에 카드가 소진되면 게임 종료됨
		
		
		 
		//player의 초기 상태를 출력하기  
		printCardInitialStatus(1);
		
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for (i=0; i < n_user + 1; i++) //each player
		{
			nGoStop = 1;
			while (nGoStop ==1 && userStatus[i] == 0) //do until the player dies or player says stop
			{
				cardnum = getReceivedCardNum(i); //받은 카드 장수를 구하기  
				
				printUserCardStatus(i, cardnum) //print current card status printUserCardStatus();
				
				playerResult = calcStepResult(i);//check the card status ::: calcStepResult()
				                                 //현재 player의 점수를 계산해서 승패여부 판단하고, 계속 진행할껀지..판단하기
												  
				//합계점수가 21점이면 승, 더 이상 카드를 받지 않음  
				if(playerResult == 4){
					if( i == n_user )
						prinf("[[[server result is ....%d ]]]\n\n",cardSum[i]);
						
					nGoStop = 0; //STOP
					continue;
				}
				
			if(i < n_user) //player의 경우
			{
				
				//합계점수가 21보다 크면 패  
				if(playerResult == 2){
					printf(" Lose!!");
					nGoStop = 0; //stop
					
				//게임이 종료됐는지 여부 확인
				//player 중 한 명이 파산(가진 자본을 모두 잃음)하면 게임이 종료되게 됨
					if(isGameEnd() == 1)
						break; //게임 종료!!
					
					//다음 player로 넘어감   
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
					cardhold[i][cardnum] = pullCard(); //카드 1장을 추가로 받음!! 
				}
				
				else{
					nGoStop = 0; //Stop
					printf("\n");
				}
			
			
			else{ //dealer(server)나 player의 경우!
				if(cardSum[i] < 17){ //현재 카드합이 17미만이면 go!
					printf("::: Go!\n");
					cardhold[i][cardnum] = pullCard();
				}
			
				else {
					nGoStop = 0; //stop
					printf("Stay!\n\n");
				}
			
			}
			 
			
			//check if the turn ends or not
			//card tray에 카드가 소진되거나 player 한명이 파산하면 게임종료!
			if(emptycardtray() == 1){
				
				break; //card tray에 카드가 소진되면 게임이 종료된다. 
				
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
