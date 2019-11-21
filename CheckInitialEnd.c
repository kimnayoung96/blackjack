#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30



int checkResult(int roundNum) {
	int i ;
	int dealerSum;
	
	//ROUND �հ����� ���ϱ�  
	for( i=0; i< n_user + 1; i++)
		cardSum[i] = getSum(i);
	for (i=1; i<n_user; i++ ){
		if (getReceivedCardNum(i) == 2 && cardSum[i] < 17){
			printf("");
		}
	} 
	
	//Dealer(server)�� blackjack�̸� ���� player�� ��� �й��ϸ�, ���� �ݾ׸�ŭ �ҰԵ� 
	dealerSum = cardSum[n_user];
	if(getReceivedCardNum(n_user)==2 && dealeSum = 21){
		
		//���������� ���� player�� �й�ó���ǰ�, ������ �ݾ��� �ҰԵ�
		for(i=0; i<n_user; i++){
			
			if(userStatus[i]==0){
				dollar[i] = dollar[i] - bet[i]; //������ �ݾ��� �ҰԵ� 
				dealerDollar = dealerDollar + bet[i]; //player�� �����ߴ� �ݾ��� dealer(server)�� �� �ݾ׿� ������ 
				userStatus[i] = 3; //�й�!!
			 
			}
		} 
	} 
	
	
	//Dealer(Server�� 21�� �ʰ��ϸ� ���� player���� ��� �¸��ϸ�, ���� ������ �ݾ׸�ŭ ����
	if(dealerSum > 21){
		//���������� ���� player�� �¸��ϰ� �ǰ� ������ �ݾ��� �ްԵ�  
	 	for(i=0; i<n_user; i++){
	 		
	 		if (userstatus[i] == 0){  //userstatus[i] �� 0�̸� ���� ���а� �������� ���� ������
		 	dollar[i]  = dollar[i] + bet[i];
			 userStatus[i] = 2; //userstatus[i]�� 2��  �Ǹ� �¸�
		 	}
		 }
	}
	
	//������ ���� player ����ó��
	//Dealer ī�� �պ��� player�� ���� ���ų� ũ�� �¸��ϰ� ������ �ݾ׸�ŭ ����
		for(i=0 ; i <n_user; i++){
			if(userStatus[i] == 0){
				if (cardSum[i] >= dealerSum){
					dollar[i] = dollar[i] + bet[i]; //������ �ݾ׸�ŭ ��������.
					userStatus[i] = 2; //userstatus[i]�� 2��  �Ǹ� �¸�  
				
				}
			else {
				dollar[i] = dollar[i] - bet[i]; //������ �ݾ׸�ŭ �Ұ� ��
				dealerDollar = dealerDollar + bet[i];
				userStatus[i] =3;  //userstatus[i]�� 3�� �Ǹ� �й�!! 
			}
			}
		}
	 
	printf("--------------ROUND %d result ....\n", roundNum);
	
	//Player�� ���� ���
	printCardInitialStatus(0);
	
	
	//dealer(server) turn���� ���� ��� �� ���� ���� �ִ� �޷� ��Ȳ ��� 
	for( i = 0 ; i <n_user ;i++){
	
	if(i == 0){
		printf("->your result: %s (sum:%d)\n", userStatus[i] ==1 ? "WIN(blackjack)" : userStatus[i]==2? "WIN" :  dollar[i] < 0? "LOSE", dollar[i]);
		
	}
	else{
		printf("->%d's players result: %s (sum:%d)\n", userStatus[i] ==1 ? "WIN(blackjack)" : userStatus[i]==2? "WIN" :  dollar[i] < 0? "LOSE", dollar[i]);
	}
	
	
	printf("------------------------------------------------------\n"); 
 
 	return 0 ;
}


//�������� �� ������� 
int checkWinner() {
	int i;
	
	int max =0;
	
	printf("\n\n------------------------Result--------------------------\n");
	
	//���� �ִ� �ݾ��� ���� ū �ݾ� ã��(������ �ݾ��� ���� �� ����)
	
	for(i=0; i < n_user; i++){
		if(dollar[i]> max)
			max = dollar[i];
			
		if(i == 0);
			printf("you      -(sum:$%d)\n",dollar[i]);
		else
			printf("player %d  -(sum:$%d)\n",i, dollar[i]); 
		}
		
	printf("---------------------------------------------------------");
	
	//���� winner
	printf("winner:");
	
	//���� �ִ� �ݾ��� ���� ū �ݾװ� ���� ����ڸ� ����winner�� ����ϱ�
	for(i=0; i< n_user; i++){
		if(dollar[i] >max )
			max = dollar[i];
			
		if(i == 0)
			printf("you   -(sum:$%d)\n",dollar[i])
		else
			prinf("player %d   -(sum:$%d)",i, dollar[i]);
		}
	} 
	
	printf("-----------------------------------------------------------------------");
	
	return 0;
	} 
	


//ROUND���� PLAYER ���ú��� �ʱ�ȭ��Ű��  
void playerInitialization(){
	int i;

	//player ���¸� �ʱ�ȭ��Ű�� 	
	for(i = 0; i < n_user + 1; i++){
		userStatus[i] = 0;
	 	cardSum[i] = 0;
	} 
}




//������ ����ƴ��� �Ǵ��ϱ�
//card tray�� ī�尡 �����ǰų� player �Ѹ��� �Ļ�(���� �ں��� ��� ����)�ϸ� ������ �����
int IsGameEnd(){
	
	int i;
	
	if(emptycardtray() == 1){          //card tray�� ī�尡 �����Ǹ�, ���� ����!! 
		{	
		printf("card ran out of the tray!! finishing the game...\n") ;
		gameEnd = 1;
		}
	}
	else {
		//player �� ���� �Ļ�(���� �ں��� ��� ����)�ϸ� ������ �����
		for(i = 0; i < n_user ; i++){
			if(i = 0; i < n_user; i++){
				printf("game end! your money: $%d, players's money : $%d, $%d", dollar[i]);
				gameEnd = 1;
				break; //���� ���� 
			}
		}
				
	}	
return gameEnd;		
}



