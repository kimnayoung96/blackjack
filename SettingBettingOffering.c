#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


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

//�� player���� ���� ����(betting)   
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
			printf("->you only have $%d!\n bet again", dollar[0]);
			continue;
		}
		
		bet[0] =myBet;
		break;
	 
		} 
		
	printf("-----------------------------------------------------------\n"); 
	
	//��ǻ�� �÷��̾� betting
	for(i=1 ; i < n_user; i++){
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
	
	printf("\n");
	return 0;	
}
	 

//offering initial 2 cards
void offerCards(void) {
	int i,j;
	
	//1. give two card for each players
	
	//���� ī�带 �����ϴ� �迭�� �ʱ�ȭ  
	for (i=0; i<n_user + 1; i++){ //���� ���۰� ���ÿ� dealer(server)�� Player n���� ���� ī�带 2�徿  �����ش�.
		
		for(j=0; j < N_MAX_CARDHOLD; j++){
			cardhold[i][j] = 0;
		} 
	}
	
	//ī��� dealr-��-player1-player2........player(N-1) ������ ī�带 ������ �ش�.(���徿 ī�带 ��)
	
	//ù ��° ī��� dealer(server)-��-player������ ������
	cardhold[n_user][0] = pullcard();
		for(i=0; i<n_user; i++){
			
		cardhold[i][0] = pullCard();
	
		} 
	
	//�� ��° ī��� dealer(server)-��-player������ ������
	cardhold[n_user][1] = pullCard();
	
		for(i=0; i < n_user; i++){
		cardhold[i][1] = pullCard();
		
	}
	return;
}

