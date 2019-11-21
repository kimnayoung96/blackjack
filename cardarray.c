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
	
	//ī�� ��Ʈ ��
	for (i=0; i< N_CARDSET ; i++ ){
		 
		 
		 //��Ʈ�� ī�� �� 1-52 
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
	
	//card_no�� 0�� �Ǹ� ��� ī�尡 ������ 
	return card_no; 
	
}

//card tray�� ī�尡 �����ƴ��� Ȯ���ϱ�
 //ī�尡 �����ƴٸ� return ���� 1�� �ϰ�, ���� ī�尡 ���Ҵٸ� return ���� 0���� �ϱ�
 int emptyCardTray(void){
 	if(cardIndex >= totalCardNum){
 		return 1; //card tray�� ī�尡 ���������Ƿ� �������� ��  
	}
	else 
		return 0; //card tray�� ���� ī�尡 ���� ���  
	}
  


