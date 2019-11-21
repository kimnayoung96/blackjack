#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//player의 카드 합계 점수를 구한다.
int getSUm(int player){
	int i,j;
	int cardNo;
	int sum;
	
	
	i = player;
	sum = 0;
	
	//합계점수 구하기
	for( j=0 ; cardhold[i][j] > 0; j++){ // 값이 0보다 커야 카드를 받은 것 
		sum = sum + getCardNum(cardhold[i][j]);
	} 
	
	
	//합계점수가 21보다 크면 A카드가 있는지 검사해서 11->1로 변경하여 계산하도록 함
	if(sum > 21){
		for(j =0 ; cardhold[i][j] > 0 ; j++){ //값이 0보다 커야 카드를 받은 것  
			cardNo =  getCardNum(cardhold[i][j]);
			
			if(cardNo ==11){ //A카드인지 확인하고 11을 1로 변경하도록 함 
				sum = sum -11;
				sum = sum +1;
				
				if(sum < 21){
					break;
				} 
				
			}
		}
	} 
	
	cardSum[i] = sum;
	
	return sum;
	
}
	
	
//print initial card status
  //나를 포함한 모든 player는 카드 내용이 보이게 배치,
  //dealer(server)는 두번째 장만 보이고 첫 번째 장은 보이지 않도록 뒤집어서 배치하도록 함 
void printCardInitialStatus(void) {
	int i;
	int j;
	int card_num;
	
	if(firstHidden == 1)
		printf("--------------CARD OFFERING-----------------\n");
	
	for(i = 0; cardhold[n_user][i]>0; i++){
		
		if(i == 0){
			printf("---server  :");
			
			if(firstHidden == 1) //dealer(server)의 첫 번째 카드를 안보여준다. 
				printf("X");
			else
				printCard(cardhold[n_user][i]);
		}
		else{
			printf(", ");
			printCard(cardhold[n_user][i]);
		}
	
}

	printf("(%d)\n",getSum(n_user));
	

	for(j = 0; j < n_user; j++){
		if(j=0)
			printf("   ->you   :");
		else
			printf("   ->player %d   :", j);

		card_num = 0;
		
		
	
	
	//Blakjack
	if(fisrtHidden == 1 && card_num == 2 && getSum(j) == 21){
		dollar[j] = dollar[j] + bet[j] * 2;  //원래 갖고 있던 돈 + 배팅한 금액의 2배 
		dealerDollar = dealerDollar - (bet[i]*2);
		userStatus[j] = 1; //승리-blackjack 
	}
	
	printf("(%d)\n",getSum(j));
			
			
	}			
			
}

int getAction(void) {
	int num = 0;
	printf(":::Action?(0 - go, others -stay):");
	num = getIntegerInput();
	return num;
	
}

//현재 player의 카드를 보여준다.  
void printUserCardStatus(int user, int cardcnt) {
		int i;
		
		if(player == 0){
			if (cardcnt == 2)
				printf(">>> my turn!------------\n");
			      printf("  ->card :   ");
		}
	
		else if (player == n_user){
			if(cardcnt == 2)
				printf(">>> server turn!---------\n");
			    	printf("  ->card :   ");
		}	
	
	
		else {
			if(cardcnt == 2)
				printf(">>> player %d turn!-------------\n",player);
	             	printf("  ->card:   ");
		}
		
		for(i = 0; i <cardcnt; i++){
			if(player == n_user && i == 0){ //dealer
			
				printf("X");
				continue; 
			}
		
			if(i =! 0)
				printf(",");
			
			printCard(cardhold[player][i]);
		}
	
		printf("(%d)", getSum(player));
}

    
//해당 player가 받은 카드 장수를 구하기
//player: player의 index
int getReceivedCardNum(int playr){
	int i;
	int card_num = 0;
	
	//받은 카드 장수를 구한다.
	
	for(i = 0; i<N_MAX_CARDHOLD && cardhold[player][i] > 0 ; i++){ //값이 0보다 큰 값이어야 카드를 받은 것!!  
		
		card_num++;
		
	} 
		return card_num;
} 



// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
//player : player의 index  
int calcStepResult(int player) {
	
	int i;
	int card_num; //받은 카드 장수 
	int rc = 0; //return 값
	 
	
	//합계점수 구하기 
	for(i = 0 ; i < n_user +1  ; i++);  
		{
			cardSum[i] = getSum(i);
		}	

	i = player;
	card_num = getReceivedCardNum(i); //해당 player의 받은 카드의 장수를 가져오도록 함  
	
	if(cardSum[i] <21) 
		rc = 1;
	else if(cardSum[i] > 21 ){
		rc = 2;// 카드 합이 21보다 크게 되니까 패 
		 if(player < n_user){ //player만 
		 	dollar[i] = dollar[i] - bet[i] ; //갖고 있는 돈에서 배팅한 금액을 뺀다.  
		 	dealerDollar = dealerDollar + bet[i]; //player가 배팅한 금액은 dealer(server)가 딴 돈에 더해짐 
			userStatus[i] = 3; //lose!!
		} 
	}
	else{
		if(card_num == 2){
			rc = 3; //blackjack
				if(player < n_user){ //player만 
	 				dollar[i] = dollar[i] + bet[i] *2; //blackjack이면 이긴거니까 갖고있던 금액에 배팅한 금액의 2배가 더해진다. 
					dealerDollar = dealerDollar = (bet[i]*2);
					userStatus[i] =2; //win!!
					 
				}
		}
		else{
			rc= 4;
		}
	}
	return rc;
}
	
		

