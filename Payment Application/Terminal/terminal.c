#include "terminal.h"
#include <stdio.h>
#include <ctype.h>



char *terminal_State[] = {"TERMINAL_OK", "WRONG_DATE", "EXPIRED_CARD", "INVALID_CARD", "INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT"};
/*
int main(void)
{
	/*ST_cardData_t cardData;
	EN_cardError_t card_status = getCardExpiryDate(&cardData);	
	ST_terminalData_t termData;
	termData.maxTransAmount = MAX_TRANS_AMOUNT;  // The default maxAmount is 20000
	EN_terminalError_t trans_status = getTransactionDate(&termData);
	
	if(card_status == CARD_OK && trans_status == TERMINAL_OK)
	{
		trans_status = isCardExpired(&cardData,&termData);
		if(trans_status == TERMINAL_OK)
		{
			printf("Successfull\n");
		}
		else
		{
			printf("Expired Card");
		}
	}
	float max;
	printf("Enter the max Transaction Amount: ");
	scanf("%f",&max);
	trans_status = setMaxAmount(&termData,max);
	if(trans_status == TERMINAL_OK)
	{
		printf("Successfull\n");
	}
	else
	{
		printf("EXCEED_MAX_AMOUNT");
	}
	trans_status = getTransactionAmount(&termData);
	if(trans_status == TERMINAL_OK)
	{
		printf("Successfull\n");
	}
	else
	{
		printf("INVALID_AMOUNT");
	}
	trans_status = isBelowMaxAmount(&termData);
	if(trans_status == TERMINAL_OK)
	{
		printf("Successfull\n");
	}
	else
	{
		printf("INVALID_MAX_AMOUNT");
	}

}
*/

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	char x[11],i = 0;
	printf("Enter Transaction Date: ");
	ScanString(x);
	int day = (x[0] - '0')*10 + x[1] - '0';
	int month = (x[3] - '0')*10 + x[4] - '0';
	if(day >31 || month > 12 || day == 0 || month == 0 || x[2] != '/' || x[5] != '/')
	{
		return WRONG_DATE;
	}
	
	while(x[i] != '\0')
	{
		if((!isdigit(x[i]) && i != 2 && i != 5))
		{
			return WRONG_DATE;
		}
		i++;
	}
	
	if(i != 10)
	{
		return WRONG_DATE;
	}
	else
	{
		i = 0;
		while(x[i] != '\0')
		{
			termData -> transactionDate[i] = x[i];
			i++;
		}
		termData -> transactionDate[i] = '\0';
	}
	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	int card_month,trans_month, trans_year, card_year;
	card_month = (cardData -> cardExpirationDate[0] - '0')*10 + cardData -> cardExpirationDate[1] - '0';
	card_year = (cardData -> cardExpirationDate[3] - '0')*10 + cardData -> cardExpirationDate[4] - '0';
	trans_month = (termData -> transactionDate[3] - '0')*10 + termData -> transactionDate[4] - '0';
	trans_year = (termData -> transactionDate[8] - '0')*10 + termData -> transactionDate[9] - '0';
	
	if (trans_year > card_year)
	{
		return EXPIRED_CARD;
	}
	else if (trans_year == card_year && trans_month > card_month)
	{
		return EXPIRED_CARD;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	float x;
	printf("Enter Transaction Amount: ");
	scanf("%f",&x);
	if(x <= 0)
	{
		return INVALID_AMOUNT;
	}
	else 
	{
		termData -> transAmount = x;
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if (termData -> transAmount > termData -> maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
	
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
	if(maxAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		termData -> maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
}



/******************Test Functions**********************/
void getTransactionDateTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getTransactionDate\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: 01/06/2000\n");
	printf("Expected Result: TERMINAL_OK\n");
	ST_terminalData_t termData;
	printf("Actual Result: %s\n",terminal_State[getTransactionDate(&termData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getTransactionDate\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: NULL\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: %s\n",terminal_State[getTransactionDate(&termData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getTransactionDate\n");
	printf("Test Case 3: \n"); 
	printf("Input Data: 01/06/\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: %s\n",terminal_State[getTransactionDate(&termData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getTransactionDate\n");
	printf("Test Case 4: \n"); 
	printf("Input Data: 8/5/2000\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: %s\n",terminal_State[getTransactionDate(&termData)]);
}
void isCardExpriedTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isCardExpried\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: Transaction: 01/06/2018 Expiration: 01/25\n");
	printf("Expected Result: TERMINAL_OK\n");
	ST_terminalData_t termData;
	ST_cardData_t cardData = {.cardExpirationDate = "01/25"};
	getTransactionDate(&termData);
	printf("Actual Result: %s\n",terminal_State[isCardExpired(&cardData,&termData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isCardExpried\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: Transaction: 01/06/2027 Expiration: 01/25	\n");
	printf("Expected Result: EXPIRED_CARD\n");
	getTransactionDate(&termData);
	printf("Actual Result: %s\n",terminal_State[isCardExpired(&cardData,&termData)]);
	
	
}
void getTransactionAmountTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: 25 \n");
	printf("Expected Result: TERMINAL_OK\n");
	ST_terminalData_t termData;
	printf("Actual Result: %s\n",terminal_State[getTransactionAmount(&termData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: 0 \n");
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("Actual Result: %s\n",terminal_State[getTransactionAmount(&termData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Test Case 3: \n"); 
	printf("Input Data: -100 \n");
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("Actual Result: %s\n",terminal_State[getTransactionAmount(&termData)]);
}
void isBelowMaxAmountTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: 25 default max 20000\n");
	printf("Expected Result: TERMINAL_OK\n");
	ST_terminalData_t termData = {.maxTransAmount = 20000};
	getTransactionAmount(&termData);
	printf("Actual Result: %s\n",terminal_State[isBelowMaxAmount(&termData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: 40000 default max 20000\n");
	printf("Expected Result: EXCEED_MAX_AMOUNT\n");
	getTransactionAmount(&termData);
	printf("Actual Result: %s\n",terminal_State[isBelowMaxAmount(&termData)]);
}
void setMaxAmountTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: 25000\n");
	printf("Expected Result: TERMINAL_OK\n");
	ST_terminalData_t termData;
	printf("Actual Result: %s\n",terminal_State[setMaxAmount(&termData,25000)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: 0\n");
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	printf("Actual Result: %s\n",terminal_State[setMaxAmount(&termData,0)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 3: \n"); 
	printf("Input Data: -100\n");
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	printf("Actual Result: %s\n",terminal_State[setMaxAmount(&termData,-100)]);
}

/*****************************************************/