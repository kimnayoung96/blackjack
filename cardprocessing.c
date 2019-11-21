#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30

//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	int no = 0;
	int num;
	 
	num= cardnum % N_MAX_CARDNUM; //종류별 A,1,2,3,,,,,10,J,Q,K(13장) 
	
	if (num == 0){       //13으로 나눈 나머지가 0이면 13세팅하기
			num = N_MAX_CARDNUM;
	} 
	
	if (num ==1)
		no = 11; // A이면 일단 11로 하기. 
	else if(num >=2 && num <=10)
		no = num;
	else if(num>=11 && num <= 13)
		no = 10;
		
	return no;		
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	int share;
	share = cardnum / (N_MAX_CARDNUM * cardSetNum); // 종류별 A,1,2,3,4,5,6,7,8,9,10,J,Q,K 의 13장 , 몫
	int rem;
	rem = cardnum % N_MAX_CARDNUM; // 종류별 A,1,2,3,4,5,6,7,8,9,10,J,Q,K 의 13장, 나머지
	
	if (rem == 0) 
	rem =   N_MAX_CARDNUM; // 13으로 나눈 나머지가 0이면 13을 세팅(13,26,39,52)
	
	if(share == 0){ //몫이 0이면 HRT출력 
		printf("HRT");
	} 
	
	else if(share == 1){ //몫이 1이면 DIA출력 
		printf("DIA");
	}
	
	else if(share == 2){ //몫이 2이면 SPD출력  
		printf("SPD");
	}

	else 
		printf("CLV"); //위의 경우가 아니라면 CLV출력  
		
		
	
	if(rem == 1){ //나머지가 1이면 A출력  
		printf("A");
	}
	else if(rem == 11) //나머지가 11이면 Jack출력  
		printf("Jack");
		
	else if(rem == 12) //나머지가 12이면 Queen 출력  
		printf("Queen");
		
	else if(rem ==13) //나머지가 13이면 King 출력   
		printf("King");
		
	else printf("%d", rem);  
	
	}
	
			


