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

//각 player별로 배팅 진행(betting)   
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
			printf("->you only have $%d!\n bet again", dollar[0]);
			continue;
		}
		
		bet[0] =myBet;
		break;
	 
		} 
		
	printf("-----------------------------------------------------------\n"); 
	
	//컴퓨터 플레이어 betting
	for(i=1 ; i < n_user; i++){
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
	
	printf("\n");
	return 0;	
}
	 

//offering initial 2 cards
void offerCards(void) {
	int i,j;
	
	//1. give two card for each players
	
	//받은 카드를 저장하는 배열을 초기화  
	for (i=0; i<n_user + 1; i++){ //게임 시작과 동시에 dealer(server)와 Player n명에게 각각 카드를 2장씩  나눠준다.
		
		for(j=0; j < N_MAX_CARDHOLD; j++){
			cardhold[i][j] = 0;
		} 
	}
	
	//카드는 dealr-나-player1-player2........player(N-1) 순서로 카드를 나누어 준다.(한장씩 카드를 줌)
	
	//첫 번째 카드는 dealer(server)-나-player순으로 나눠줌
	cardhold[n_user][0] = pullcard();
		for(i=0; i<n_user; i++){
			
		cardhold[i][0] = pullCard();
	
		} 
	
	//두 번째 카드는 dealer(server)-나-player순으로 나눠줌
	cardhold[n_user][1] = pullCard();
	
		for(i=0; i < n_user; i++){
		cardhold[i][1] = pullCard();
		
	}
	return;
}

