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
	 
	num= cardnum % N_MAX_CARDNUM; //������ A,1,2,3,,,,,10,J,Q,K(13��) 
	
	if (num == 0){
		num = N_MAX_CARDNUM;
	} 
	
	if (num ==1)
		no = 11; // A�̸� �ϴ� 11�� �ϱ�. 
	else if(num >=2 && num <=10)
		no = num;
	else if(num>=11 && num <= 13)
		no = 10;
		
	return no;		
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	int share = cardnum / (N_MAX_CARDNUM * cardSetNum); // ������ A,1,2,3,4,5,6,7,8,9,10,J,Q �� 13�� , ��
	int rem = cardnum % N_MAX_CARDNUM; // ������ A,1,2,3,4,5,6,7,8,9,10,J,Q �� 13��, ������
	
	if (rem == 0) 
	rem =   N_MAX_CARDNUM; // 13���� ���� �������� 0�̸� 13�� ����(13,26,39,52)
	
	if(share == 0){
		printf("HRT");
	} 
	
	if(share == 1){
		printf("DIA");
	}
	
	if(share == 2){
		printf("SPD");
	}

	else 
		printf("CLV");
		
	
	if(rem == 1){
		printf("A");
	}
	else if(rem == 11)
		printf("J");
		
	else if(rem == 12)
		printf("Q");
		
	else if(rem ==13)
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
	
	//ī�� ��Ʈ ��
	for (i=0; i< N_CARDSET ; i++ ){
		 
		 //ī�� ��Ʈ ��
		 for (j < N_CARD; j++){
		 	CardTray[(i+j)*j)] = (i+1) *(j+1);
		 	} 
	} 


}

//get one card from the tray
int pullCard(void) {
	
	
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {
	
	int numofusers = 0; //user �� 0���� �ʱ�ȭ
	 
	printf("Input the number of players(Max:5)): ") ;
	numofusers = getIntegerInput();
	
	while(1){
	
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

printf("--------------------------------
           -----ROUND1("CardIndex: 0)");
           

//betting
printf("-----BETTING STEP-----");

int betDollar(void) {
	
	int i;
	int mybettingamount;
	
	while (1){
		printft("your betting (total:$50)");
		my bettingamount  = getIntegerInput();
		
		if (mybettingamount <= 0){
			printf("invalid input for betting : ");
			scanf("%d", &mybettingamount);
			continue;}
			
		if (mybettingamout > dollar[0]){
			printf("you only have $50! bet again");
			continue;
		}
		
		} 
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
	int cardnum; //���� ī�尡 ��Ÿ���� ����  
	int sum = 0;
	
	i = player;
	
	//�հ����� ���ϱ� 
	for(j=0 ; cardhold[i][j] > 0 ; j++); //���� 0���� ū ���̾�� ī�带 ���� �� 
		{
			sum = sum + getCardNum(cardhold[i][j]);
		}	
	
	//�հ������� 21���� ũ�� Aī�尡 �ִ��� �˻��ؼ� 11�� 1�� �����ؼ� ����ϵ��� ��
	if(sum >21){
			for(j = 0; cardhold[i][j] > 0 ; j++) //���� 0���� ū ���̾�� ī�带 ���� ��
			{
				if(cardnum == 11) // Aī������ Ȯ���ؼ� 11�� 1�� ����
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
	
	//ROUND �հ�����
	for( i=0; i< numofusers + 1; i++)
		cardSum[i] = getSum[i];
	for (i=0; i< numofusers; i++ ){
		if ()
	} 
	
	// Dealer(Server)�� blackjack�̸� player�� ��� �й��ϰ�, ���� ������ �ݾ׸�ŭ ����
	deaelSum = cardSUm[n_user];
	if () 
	
	
	//Dealer(Server�� 21�� �ʰ��ϸ� ���� player���� ��� �¸��ϸ�, ���� ������ �ݾ׸�ŭ ����
	if(dealerSum > 21){
	 	for(i=0; i<numofusers; i++){
	 		 //userstatus[i] �� 0�̸� ���� ���а� �������� ���� ������
			  
		 if (userstatus[i] == 0){  
		 	dollar[i]  = dollar[i] + bet[i];
			 userStatus[i] = 1; //userstatus[i]�� 1�� �Ǹ� �¸�
		 	}
		 }
	}
	
	//������ ���� player ����ó��
	//Dealer ī�� �պ��� player�� ���� ���ų� ũ�� �¸��ϰ� ������ �ݾ׸�ŭ ����
	 
 
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
