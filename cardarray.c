#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	int i,j;
	
	
	printf(" -->card is mixed and put into the tray\n");
	
	cardIndex = 0;
	
	//카드 세트 수
	for (i=0; i< N_CARDSET ; i++ ){
		 
		 
		 //세트별 카드 수 1-52 
		 for (j < N_CARD; j++){
		 	
		 	CardTray[(i+1) * j] = (i+1) *(j+1);

		 	
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
 int emptyCardTray(void){
 	if(cardIndex >= totalCardNum){
 		return 1; //card tray에 카드가 소진됐으므로 게임종료 됨  
	}
	else 
		return 0; //card tray에 아직 카드가 남은 경우  
	}
  


