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
	
	if (num == 0){       //13���� ���� �������� 0�̸� 13�����ϱ�
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
	int share;
	share = cardnum / (N_MAX_CARDNUM * cardSetNum); // ������ A,1,2,3,4,5,6,7,8,9,10,J,Q,K �� 13�� , ��
	int rem;
	rem = cardnum % N_MAX_CARDNUM; // ������ A,1,2,3,4,5,6,7,8,9,10,J,Q,K �� 13��, ������
	
	if (rem == 0) 
	rem =   N_MAX_CARDNUM; // 13���� ���� �������� 0�̸� 13�� ����(13,26,39,52)
	
	if(share == 0){ //���� 0�̸� HRT��� 
		printf("HRT");
	} 
	
	if(share == 1){ //���� 1�̸� DIA��� 
		printf("DIA");
	}
	
	if(share == 2){ //���� 2�̸� SPD���  
		printf("SPD");
	}

	else 
		printf("CLV"); //���� ��찡 �ƴ϶�� CLV���  
		
	
	if(rem == 1){ //�������� 1�̸� A���  
		printf("A");
	}
	else if(rem == 11) //�������� 11�̸� J���  
		printf("J");
		
	else if(rem == 12) //�������� 12�̸� Q���  
		printf("Q");
		
	else if(rem ==13) //�������� 13�̸� K���  
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
	int card_no = 0;
	
	if(cardIndex < totalCardNum){
		card_no = CardTray[cardIndex];
		cardIndex++;
		
	}
	//card_no�� 0�� �Ǹ� ��� ī�尡 ������ 
	
	return card_no; 
	
}

//card tray�� ī�尡 �����ƴ��� Ȯ���ϱ�
 //ī�尡 �����ƴٸ� return ���� 1�� �ϰ�, ���� ī�尡 ���Ҵٸ� return ���� 0���� �ϱ�
 int emptycardtray(void){
 	if(cardIndex >= totalCardNum){
 		return 1; //card tray�� ī�尡 ���������Ƿ� �������� ��  
	}
	else 
		return 0;
	 }
 } 

//playing game functions -----------------------------

//player settiing
int configUser(void) {
	
	int n_user = 0; //user �� 0���� �ʱ�ȭ
	 
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

//�� player���� ���� ����  
int betDollar(void) {
	
	int i;
	int myBet; //���� ������ �ݾ�  
	
	while (1){
		printf("->your betting (total:$%d)", dollar[0]);
		myBet  = getIntegerInput();
		
		if (myBet <= 0){    //���� �Է���  ������ �ݾ��� �����ִ� �ݾ׺��� ���� ��   
			printf("->invalid input for betting : %d\n",myBet);
			continue;
		}
			
		if (myBet > dollar[0]){  //���� �Է���  ������ �ݾ��� ���ð����� �ִ� �ݾ׺��� ������  
			printf("->you only have $%d!\n bet again",dollar[0]);
			continue;
		}
		
		bet[0] =myBet;
		break;
	 
		} 
		
	printf("-----------------------------------------------------------\n"); 
	
	//��ǻ�� �÷��̾� betting
	for(i=0 ; i < n_user; i++){
		myBet = rand() % N_MAX_BET +1 // 1~5 dollar
		
		if(myBet > dollar[i])
			myBet = dollar[i];
			bet[i] = myBet;
		
	}
	
	//���ñݾ� ���
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
