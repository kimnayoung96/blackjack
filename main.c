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
	
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
	if ()
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {


}

//get one card from the tray
int pullCard(void) {
	
	
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {
	
	int numofusers = 0; //user 수 0으로 초기화
	 
	printf("Input the number of players(Max:5)): ") ;
	numofusers = getIntegerInput();
	
	if(numofusers <=0){
		printf("invalid input players("%d")", numofusers);
		continue;
	}
	
	if(numofusers > N_MAX_USER){
		printf("Too many players!");
		continue;
	}
	
	return numofusers;
	
}


//betting
printf("-----BETTING STEP-----");

int betDollar(void) {
	
	int i;
	int mybettingamount;
	
	while (1){
		printft("your betting (total:$50)");
		my betting  = getIntegerInput();
		
		if (mybettingamount < 0){
			printf("invalid input for betting : ");
			scanf("%d", &mybetting);
			continue;}
			
		if (){
		}
		
		printf("")
			
			
		} 
	}
	
	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	
}

int getAction(void) {
	
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
	
	int i;
	int cardnum; //받은 카드 장 수
	 
	for(i=0 ; i < N_USER + 1; i++); //서버도 추가되니까 +1 
		{
			
		}	
	
	for (i=0 ; i <N_USER +1 ; i++)
		{
		cardnum = getCardNum(i); //받은 카드 장 수를 가져옴
		
		if(i == 0) //만약 내가 받은 카드 장 수가 0이라면 
		{
		printf("") 
		}	
}

int checkResult() {
	
}

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
