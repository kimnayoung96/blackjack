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
	
	//ROUND 합계점수 구하기  
	for( i=0; i< n_user + 1; i++)
		cardSum[i] = getSum(i);
	for (i=1; i<n_user; i++ ){
		if (getReceivedCardNum(i) == 2 && cardSum[i] < 17){
			printf("");
		}
	} 
	
	//Dealer(server)가 blackjack이면 남은 player는 모두 패배하며, 배팅 금액만큼 잃게됨 
	dealerSum = cardSum[n_user];
	if(getReceivedCardNum(n_user)==2 && dealeSum = 21){
		
		//마지막까지 남은 player는 패배처리되고, 배팅한 금액을 잃게됨
		for(i=0; i<n_user; i++){
			
			if(userStatus[i]==0){
				dollar[i] = dollar[i] - bet[i]; //배팅한 금액을 잃게됨 
				dealerDollar = dealerDollar + bet[i]; //player가 배팅했던 금액은 dealer(server)가 딴 금액에 더해짐 
				userStatus[i] = 3; //패배!!
			 
			}
		} 
	} 
	
	
	//Dealer(Server가 21을 초과하면 남은 player들은 모두 승리하며, 각자 배팅한 금액만큼 얻음
	if(dealerSum > 21){
		//마지막까지 남은 player는 승리하게 되고 배팅한 금액을 받게됨  
	 	for(i=0; i<n_user; i++){
	 		
	 		if (userstatus[i] == 0){  //userstatus[i] 가 0이면 아직 승패가 결정되지 않은 상태임
		 	dollar[i]  = dollar[i] + bet[i];
			 userStatus[i] = 2; //userstatus[i]가 2가  되면 승리
		 	}
		 }
	}
	
	//마지막 남은 player 승패처리
	//Dealer 카드 합보다 player의 합이 같거나 크면 승리하고 배팅한 금액만큼 받음
		for(i=0 ; i <n_user; i++){
			if(userStatus[i] == 0){
				if (cardSum[i] >= dealerSum){
					dollar[i] = dollar[i] + bet[i]; //배팅한 금액만큼 더해진다.
					userStatus[i] = 2; //userstatus[i]가 2가  되면 승리  
				
				}
			else {
				dollar[i] = dollar[i] - bet[i]; //배팅한 금액만큼 잃게 됨
				dealerDollar = dealerDollar + bet[i];
				userStatus[i] =3;  //userstatus[i]가 3이 되면 패배!! 
			}
			}
		}
	 
	printf("--------------ROUND %d result ....\n", roundNum);
	
	//Player별 상태 출력
	printCardInitialStatus(0);
	
	
	//dealer(server) turn이후 승패 결과 및 각자 갖고 있는 달러 상황 출력 
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


//게임종료 후 최종결과 
int checkWinner() {
	int i;
	
	int max =0;
	
	printf("\n\n------------------------Result--------------------------\n");
	
	//갖고 있는 금액이 가장 큰 금액 찾기(동일한 금액이 있을 수 있음)
	
	for(i=0; i < n_user; i++){
		if(dollar[i]> max)
			max = dollar[i];
			
		if(i == 0);
			printf("you      -(sum:$%d)\n",dollar[i]);
		else
			printf("player %d  -(sum:$%d)\n",i, dollar[i]); 
		}
		
	printf("---------------------------------------------------------");
	
	//최종 winner
	printf("winner:");
	
	//갖고 있는 금액이 가장 큰 금액과 같은 사용자를 최종winner로 출력하기
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
	


//ROUND마다 PLAYER 관련변수 초기화시키기  
void playerInitialization(){
	int i;

	//player 상태를 초기화시키기 	
	for(i = 0; i < n_user + 1; i++){
		userStatus[i] = 0;
	 	cardSum[i] = 0;
	} 
}




//게임이 종료됐는지 판단하기
//card tray에 카드가 소진되거나 player 한명이 파산(가진 자본을 모두 잃음)하면 게임이 종료됨
int IsGameEnd(){
	
	int i;
	
	if(emptycardtray() == 1){          //card tray에 카드가 소진되면, 게임 종료!! 
		{	
		printf("card ran out of the tray!! finishing the game...\n") ;
		gameEnd = 1;
		}
	}
	else {
		//player 한 명이 파산(가진 자본을 모두 잃음)하면 게임이 종료됨
		for(i = 0; i < n_user ; i++){
			if(i = 0; i < n_user; i++){
				printf("game end! your money: $%d, players's money : $%d, $%d", dollar[i]);
				gameEnd = 1;
				break; //게임 종료 
			}
		}
				
	}	
return gameEnd;		
}



