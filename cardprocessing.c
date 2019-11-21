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
	
	else if(share == 1){ //���� 1�̸� DIA��� 
		printf("DIA");
	}
	
	else if(share == 2){ //���� 2�̸� SPD���  
		printf("SPD");
	}

	else 
		printf("CLV"); //���� ��찡 �ƴ϶�� CLV���  
		
		
	
	if(rem == 1){ //�������� 1�̸� A���  
		printf("A");
	}
	else if(rem == 11) //�������� 11�̸� Jack���  
		printf("Jack");
		
	else if(rem == 12) //�������� 12�̸� Queen ���  
		printf("Queen");
		
	else if(rem ==13) //�������� 13�̸� King ���   
		printf("King");
		
	else printf("%d", rem);  
	
	}
	
			


