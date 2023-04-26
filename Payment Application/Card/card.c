#include "card.h"
#include <stdio.h>
#include <ctype.h>

char *card_State[] = {"CARD_OK", "WRONG_NAME", "WRONG_EXP_DATE", "WRONG_PAN"};
/*
int main(void)
{
	ST_cardData_t y;
	EN_cardError_t a = getCardHolderName(&y);
	if(a == CARD_OK)
	{
		printf("%s \n",y.cardHolderName);
	}
	else
	{
		printf("Wrong Card Holder Name\n");
	}
	a = getCardExpiryDate(&y);
	if(a == CARD_OK)
	{
		printf("%s \n",y.cardExpirationDate);
	}
	else
	{
		printf("Wrong Card Expiration Date\n");
	}
	a = getCardPAN(&y);
	if(a == CARD_OK)
	{
		printf("%s \n",y.primaryAccountNumber);
	}
	else
	{
		printf("Wrong Primary Account Number\n");
	}

}
*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
     char x[25],i = 0;
	 printf("\nEnter Card Holder Name: ");
	 ScanString(x);
	 while(x[i] != '\0')
	 {
		if(!isalpha(x[i])&& x[i] != ' ')
		{
			return WRONG_NAME;
		}
		i++;
	 }
	 if(i < 20 || i > 24)
	 {
		 return WRONG_NAME;
	 }
	 else
	 {
		 i = 0;
		while(x[i] != '\0')
		{
			cardData -> cardHolderName[i] = x[i];
			i++;
		}
		cardData -> cardHolderName[i] = '\0';
	 }
	 return CARD_OK;
	
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	char x[6],i = 0;
	printf("Enter Card Expiry Date: ");
	ScanString(x);
	int month = (x[0] - '0')*10 + x[1] - '0';
	if(month > 12 || month == 0 || x[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	while(x[i] != '\0')
	{
		if((!isdigit(x[i]) && i != 2))
		{
			return WRONG_EXP_DATE;
		}
		i++;
	}
	if(i != 5)
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		i = 0;
		while(x[i] != '\0')
		{
			cardData -> cardExpirationDate[i] = x[i];
			i++;
		}
		cardData -> cardExpirationDate[i] = '\0';
	}
	return CARD_OK;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	char x[20],i = 0;
	printf("Enter PAN: ");
	ScanString(x);
	while(x[i] != '\0')
	{
		if(!isdigit(x[i]))
		{
			return WRONG_PAN;
		}
		i++;
	}
	if(i < 16 || i > 19)
	{
		return WRONG_PAN;
	}
	else
	{
		i = 0;
		while(x[i] != '\0')
		{
			cardData -> primaryAccountNumber[i] = x[i];
			i++;
		}
		cardData -> primaryAccountNumber[i] = '\0';
	}
	return CARD_OK;
}
void ScanString(char* str)
{
	char reading = 0;
	char index = 0;
	while(reading != '\n')
	{
		reading = getchar();
		
		str[index] = reading;
		index++;		
	}
	str[index - 1] = '\0';
}


/******************Test Functions**********************/

void getCardHolderNameTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 4: \n"); 
	printf("Input Data: Mohamed Wael Mohamed Hazim\n");
	printf("Expected Result: Wrong Name\n");
	ST_cardData_t cardData;
	printf("Actual Result: %s\n",card_State[getCardHolderName(&cardData)]);
}

void getCardExpiryDateTest (void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: 12/27\n");
	printf("Expected Result: CARD_OK\n");
	ST_cardData_t cardData;
	printf("Actual Result: %s\n",card_State[getCardExpiryDate(&cardData)]);
	
	printf("\nTest Case 2: \n"); 
	printf("Input Data: 24/27\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: %s\n",card_State[getCardExpiryDate(&cardData)]);
	
	printf("\nTest Case 3: \n"); 
	printf("Input Data: NULL\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: %s\n",card_State[getCardExpiryDate(&cardData)]);
	
	printf("\nTest Case 4: \n"); 
	printf("Input Data: 05/06/2000\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: %s\n",card_State[getCardExpiryDate(&cardData)]);
}

void getCardPANTest (void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getCardPAN\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: 12345678912345678\n");
	printf("Expected Result: CARD_OK\n");
	ST_cardData_t cardData;
	printf("Actual Result: %s\n",card_State[getCardPAN(&cardData)]);
	
	printf("\nTest Case 2: \n"); 
	printf("Input Data: 1234567891234\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: %s\n",card_State[getCardPAN(&cardData)]);
	
	printf("\nTest Case 3: \n"); 
	printf("Input Data: NULL\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: %s\n",card_State[getCardPAN(&cardData)]);
	
	printf("\nTest Case 4: \n"); 
	printf("Input Data: 123456789123456788912345678\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: %s\n",card_State[getCardPAN(&cardData)]);
}

/*****************************************************/