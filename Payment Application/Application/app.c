#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"
#include <stdio.h>
#include <stdlib.h>
char retry = 0;
extern char counter;
int main(void)
{
	do
	{
		system("cls");
		appStart();
		printf("Do you want another operation: \npress 0 to continue or any number to End\n");
		scanf(" %c",&retry);
		getchar();  // to clear scanf buffer
	}while(retry == '0');
}

void appStart(void)
{
	ST_transaction_t transactionData = {.transState = APPROVED};
	if(getCardHolderName(&transactionData.cardHolderData) != CARD_OK)
	{
		transactionData.transState = INTERNAL_SERVER_ERROR;
		recieveTransactionData(&transactionData);		
		printf("Invalid Name\n");
		return;
	}
	if(getCardExpiryDate(&transactionData.cardHolderData) != CARD_OK)
	{
		transactionData.transState = INTERNAL_SERVER_ERROR;
		recieveTransactionData(&transactionData);		
		printf("Invalid Date\n");
		return;
	}
	if(getCardPAN(&transactionData.cardHolderData) != CARD_OK)
	{
		transactionData.transState = INTERNAL_SERVER_ERROR;
		printf("Invalid PAN\n");
		return;
	}
	
	setMaxAmount(&transactionData.terminalData, 20000);

	getTransactionDate(&transactionData.terminalData);
	
	if(isCardExpired(&transactionData.cardHolderData, &transactionData.terminalData) != TERMINAL_OK)
	{
		transactionData.transState = INTERNAL_SERVER_ERROR;
		printf("Declined Expired Card\n");
	}
	getTransactionAmount(&transactionData.terminalData);
	
	if(isBelowMaxAmount(&transactionData.terminalData) != TERMINAL_OK)
	{
		transactionData.transState = INTERNAL_SERVER_ERROR;
		printf("Declined Amount Exceeding limit\n");
	}
	
	recieveTransactionData(&transactionData);		
	
 

}