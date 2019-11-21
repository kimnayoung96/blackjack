#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//player�� ī�� �հ� ������ ���Ѵ�.
int getSUm(int player){
	int i,j;
	int cardNo;
	int sum;
	
	
	i = player;
	sum = 0;
	
	//�հ����� ���ϱ�
	for( j=0 ; cardhold[i][j] > 0; j++){ // ���� 0���� Ŀ�� ī�带 ���� �� 
		sum = sum + getCardNum(cardhold[i][j]);
	} 
	
	
	//�հ������� 21���� ũ�� Aī�尡 �ִ��� �˻��ؼ� 11->1�� �����Ͽ� ����ϵ��� ��
	if(sum > 21){
		for(j =0 ; cardhold[i][j] > 0 ; j++){ //���� 0���� Ŀ�� ī�带 ���� ��  
			cardNo =  getCardNum(cardhold[i][j]);
			
			if(cardNo ==11){ //Aī������ Ȯ���ϰ� 11�� 1�� �����ϵ��� �� 
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
  //���� ������ ��� player�� ī�� ������ ���̰� ��ġ,
  //dealer(server)�� �ι�° �常 ���̰� ù ��° ���� ������ �ʵ��� ����� ��ġ�ϵ��� �� 
void printCardInitialStatus(void) {
	int i;
	int j;
	int card_num;
	
	if(firstHidden == 1)
		printf("--------------CARD OFFERING-----------------\n");
	
	for(i = 0; cardhold[n_user][i]>0; i++){
		
		if(i == 0){
			printf("---server  :");
			
			if(firstHidden == 1) //dealer(server)�� ù ��° ī�带 �Ⱥ����ش�. 
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
		dollar[j] = dollar[j] + bet[j] * 2;  //���� ���� �ִ� �� + ������ �ݾ��� 2�� 
		dealerDollar = dealerDollar - (bet[i]*2);
		userStatus[j] = 1; //�¸�-blackjack 
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

//���� player�� ī�带 �����ش�.  
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

    
//�ش� player�� ���� ī�� ����� ���ϱ�
//player: player�� index
int getReceivedCardNum(int playr){
	int i;
	int card_num = 0;
	
	//���� ī�� ����� ���Ѵ�.
	
	for(i = 0; i<N_MAX_CARDHOLD && cardhold[player][i] > 0 ; i++){ //���� 0���� ū ���̾�� ī�带 ���� ��!!  
		
		card_num++;
		
	} 
		return card_num;
} 



// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
//player : player�� index  
int calcStepResult(int player) {
	
	int i;
	int card_num; //���� ī�� ��� 
	int rc = 0; //return ��
	 
	
	//�հ����� ���ϱ� 
	for(i = 0 ; i < n_user +1  ; i++);  
		{
			cardSum[i] = getSum(i);
		}	

	i = player;
	card_num = getReceivedCardNum(i); //�ش� player�� ���� ī���� ����� ���������� ��  
	
	if(cardSum[i] <21) 
		rc = 1;
	else if(cardSum[i] > 21 ){
		rc = 2;// ī�� ���� 21���� ũ�� �Ǵϱ� �� 
		 if(player < n_user){ //player�� 
		 	dollar[i] = dollar[i] - bet[i] ; //���� �ִ� ������ ������ �ݾ��� ����.  
		 	dealerDollar = dealerDollar + bet[i]; //player�� ������ �ݾ��� dealer(server)�� �� ���� ������ 
			userStatus[i] = 3; //lose!!
		} 
	}
	else{
		if(card_num == 2){
			rc = 3; //blackjack
				if(player < n_user){ //player�� 
	 				dollar[i] = dollar[i] + bet[i] *2; //blackjack�̸� �̱�Ŵϱ� �����ִ� �ݾ׿� ������ �ݾ��� 2�谡 ��������. 
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
	
		

