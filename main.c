#include <stdio.h>
#include <stdlib.h>

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


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

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


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	int no = 0;
	int num;
	 
	num= cardnum % N_MAX_CARDNUM; //종류별 A,1,2,3,,,,,10,J,Q,K(13장) 
	
	if (num == 0){       //13으로 나눈 나머지가 0이면 13세팅하기
			num = N_MAX_CARDNUM;
	} 
	
	if (num ==1)
		no = 11; // A이면 일단 11로 하기. 
	else if(num >=2 && num <=10)
		no = num;
	else if(num>=11 && num <= 13)
		no = 10;
		
	return no;		
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	int share;
	share = cardnum / (N_MAX_CARDNUM * cardSetNum); // 종류별 A,1,2,3,4,5,6,7,8,9,10,J,Q,K 의 13장 , 몫
	int rem;
	rem = cardnum % N_MAX_CARDNUM; // 종류별 A,1,2,3,4,5,6,7,8,9,10,J,Q,K 의 13장, 나머지
	
	if (rem == 0) 
	rem =   N_MAX_CARDNUM; // 13으로 나눈 나머지가 0이면 13을 세팅(13,26,39,52)
	
	if(share == 0){ //몫이 0이면 HRT출력 
		printf("HRT");
	} 
	
	if(share == 1){ //몫이 1이면 DIA출력 
		printf("DIA");
	}
	
	if(share == 2){ //몫이 2이면 SPD출력  
		printf("SPD");
	}

	else 
		printf("CLV"); //위의 경우가 아니라면 CLV출력  
		
	
	if(rem == 1){ //나머지가 1이면 A출력  
		printf("A");
	}
	else if(rem == 11) //나머지가 11이면 J출력  
		printf("J");
		
	else if(rem == 12) //나머지가 12이면 Q출력  
		printf("Q");
		
	else if(rem ==13) //나머지가 13이면 K출력  
		printf("K");
		
	else printf("%d", rem);  
	
	}
	
			
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	int i,j;
	
	
	printf(" -->card is mixed and put into the tray\n");
	
	cardIndex = 0;
	
	//카드 세트 수
	for (i=0; i< N_CARDSET ; i++ ){
		 
		 //카드 세트 수
		 for (j < N_CARD; j++){
		 	CardTray[(i+j)*j)] = (i+1) *(j+1);
		 	} 
	} 


}

//get one card from the tray
int pullCard(void) {
	int card_no = 0;
	
	if(cardIndex < totalCardNum){
		card_no = CardTray[cardIndex];
		cardIndex++;
		
	}
	//card_no가 0이 되면 모든 카드가 소진됨 
	
	return card_no; 
	
}

//card tray에 카드가 소진됐는지 확인하기
 //카드가 소진됐다면 return 값을 1로 하고, 아직 카드가 남았다면 return 값을 0으로 하기
 int emptycardtray(void){
 	if(cardIndex >= totalCardNum){
 		return 1; //card tray에 카드가 소진됐으므로 게임종료 됨  
	}
	else 
		return 0;
	 }
 } 

//playing game functions -----------------------------

//player settiing
int configUser(void) {
	
	int n_user = 0; //user 수 0으로 초기화
	 
	printf("Input the number of players(Max:5): ") ;
	n_user = getIntegerInput();
	
	while(1){
	
		if(n_user <=0){
			printf("invalid input players %d\n, n_user);
			continue;
		}
	
		if(n_user > N_MAX_USER){
			printf("Too many players!\n");
			continue;
		}
	
			return n_user;
	
	}
}

//각 player별로 배팅 진행  
int betDollar(void) {
	
	int i;
	int myBet; //내가 배팅한 금액  
	
	while (1){
		printf("->your betting (total:$%d)", dollar[0]);
		myBet  = getIntegerInput();
		
		if (myBet <= 0){    //내가 입력한  배팅한 금액이 배팅최대 금액보다 적을 때   
			printf("->invalid input for betting : %d\n",myBet);
			continue;
		}
			
		if (myBet > dollar[0]){  //내가 입력한  배팅한 금액이 배팅가능한 최대 금액보다 많으면  
			printf("->you only have $%d!\n bet again",dollar[0]);
			continue;
		}
		
		bet[0] =myBet;
		break;
	 
		} 
		
	printf("-----------------------------------------------------------\n"); 
	
	//컴퓨터 플레이어 betting
	for(i=0 ; i < n_user; i++){
		myBet = rand() % N_MAX_BET +1 // 1~5 dollar
		
		if(myBet > dollar[i])
			myBet = dollar[i];
			bet[i] = myBet;
		
	}
	
	//베팅금액 출력
	printf("------------BETTING STEP--------------\n");
	
	for(i = 0; i < n_user; i++){
		if(i = 0){
			printf(" -> your betting(total %d) : $%d\n",dollar[i],bet[i]);
		}
		else
			printf(" -> player %d bets $%d (out of $%d)\n", bet[i], dollar[i]);
	}
	
	return 0;	
}
	 

//offering initial 2 cards
void offerCards(void) {
	int i,j;
	//1. give two card for each players
	for (i=0;i<numofusers + 1;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[numofusers][0] = pullCard();
	
	cardhold[numofusers][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	if(player == 0){
			printf(">>> player 1 turn!------------
			        ->card :                      ");
	else if (player == n_user)
			printf(">>> player 2 turn!------------
			        ->card :                      ");
	else printf(">>> server turn!-----------------
	                ->card:                       ");
	}

	
}

int getAction(void) {
	int num = 0;
	printf(":::Action?(0 - go, others -stay)");
	num = getIntegerInput();
	return num;
	
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
	int i,j;
	int cardnum; //받은 카드가 나타내는 숫자  
	int sum = 0;
	
	i = player;
	
	//합계점수 구하기 
	for(j=0 ; cardhold[i][j] > 0 ; j++); //값이 0보다 큰 값이어야 카드를 받은 것 
		{
			sum = sum + getCardNum(cardhold[i][j]);
		}	
	
	//합계점수가 21보다 크면 A카드가 있는지 검사해서 11을 1로 변경해서 계산하도록 함
	if(sum >21){
			for(j = 0; cardhold[i][j] > 0 ; j++) //값이 0보다 큰 값이어야 카드를 받은 것
			{
				if(cardnum == 11) // A카드인지 확인해서 11을 1로 변경
				{
					sum = sum - 11;
					sum = sum + 1;
					
					if(sum < 21){
						break;
	
					} 
				  }  
			  } 
	} 
	cardSum[i] = sum;
	
	return sum;
		
}

int checkResult() {
	int i ;
	int dealerSum;
	
	//ROUND 합계점수
	for( i=0; i< numofusers + 1; i++)
		cardSum[i] = getSum[i];
	for (i=0; i< numofusers; i++ ){
		if ()
	} 
	
	// Dealer(Server)가 blackjack이면 player는 모두 패배하고, 각자 배팅한 금액만큼 잃음
	deaelSum = cardSUm[n_user];
	if () 
	
	
	//Dealer(Server가 21을 초과하면 남은 player들은 모두 승리하며, 각자 배팅한 금액만큼 얻음
	if(dealerSum > 21){
	 	for(i=0; i<numofusers; i++){
	 		 //userstatus[i] 가 0이면 아직 승패가 결정되지 않은 상태임
			  
		 if (userstatus[i] == 0){  
		 	dollar[i]  = dollar[i] + bet[i];
			 userStatus[i] = 1; //userstatus[i]가 1이 되면 승리
		 	}
		 }
	}
	
	//마지막 남은 player 승패처리
	//Dealer 카드 합보다 player의 합이 같거나 크면 승리하고 배팅한 금액만큼 받음
	 
 
}


printf("\n---------------------------------------------------------\n");
 
 
int checkWinner() {
	
	
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for (i=0; i < N_USER + 1; i++) //each player
		{
			while () //do until the player dies or player says stop
			{
				print("-->card: ");     //print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
