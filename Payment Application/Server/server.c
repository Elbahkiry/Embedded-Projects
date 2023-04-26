#include "server.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define database_size  10

ST_accountsDB_t accountsDB[255] = {
		{2000.0, RUNNING, "8989374615436851"},
		{100000.0, BLOCKED, "5807007076043875"},
		{12000.0, RUNNING, "8989374615436852"},
		{150000.0, BLOCKED, "5807007076043876"},
		{2800.0, RUNNING, "8989374615436853"},
		{190000.0, BLOCKED, "5807007076043877"},
		{7700.0, RUNNING, "8989374615436854"},
		{160000.0, BLOCKED, "5807007076043878"},
		{6000.0, RUNNING, "8989374615436855"},
		{10000.0, BLOCKED, "5807007076043879"},
		
	};
ST_transaction_t  transaction[255];
char counter = 0;
char *transState_enum[] = {"APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR"};
char *serverState_enum[] = {"SERVER_OK", "SAVING_FAILED", "TRANSACTION_NOT_FOUND", "ACCOUNT_NOT_FOUND", "LOW_BALANCE", "BLOCKED_ACCOUNT"}; // for testing functions
/*
int main(void)
{
	
	ST_transaction_t y = {.cardHolderData = {.primaryAccountNumber="8989374615438851"},.transState = INTERNAL_SERVER_ERROR,.terminalData ={.transAmount=1000}};
	recieveTransactionData(&y);
	ST_transaction_t z = {.cardHolderData = {.primaryAccountNumber="5807007076043875"},.transState = INTERNAL_SERVER_ERROR,.terminalData ={.transAmount=200000}};
	recieveTransactionData(&z);
	listSavedTransactions();

}
*/



EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
	if(transData -> transState != INTERNAL_SERVER_ERROR)
	{
		char found = 0;
		int i;
		for(i = 0; i < database_size; i++)
		{
			if(isValidAccount(&(transData -> cardHolderData),&accountsDB[i]) == SERVER_OK)
			{
				found = 1;
				break;
			}
		}
		if(!found)
		{
			transData -> transState = FRAUD_CARD;
			printf("FRAUD_CARD\n");
		}
		else if(isAmountAvailable(&(transData -> terminalData),&accountsDB[i]))
		{
			transData -> transState = DECLINED_INSUFFECIENT_FUND;
			printf("DECLINED INSUFFECIENT FUND\n");
		}
		else if(isBlockedAccount(&accountsDB[i]) == BLOCKED_ACCOUNT)
		{
			transData -> transState = DECLINED_STOLEN_CARD;
			printf("DECLINED STOLEN CARD\n");
		}

	}
	saveTransaction(transData);
	printf("Save Transaction\n");
	listSavedTransactions();
	return transData -> transState;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
	if(strcmp(cardData -> primaryAccountNumber, accountRefrence -> primaryAccountNumber) == 0)
	{
		return SERVER_OK;
	}	
	else
	{
		return ACCOUNT_NOT_FOUND;
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	if(accountRefrence -> state == BLOCKED)
	{
		return BLOCKED_ACCOUNT;
	}
	else
	{
		return SERVER_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
	if(termData -> transAmount > accountRefrence -> balance)
	{
		return LOW_BALANCE;
	}
	else
	{
		accountRefrence -> balance -= termData -> transAmount;
		return SERVER_OK;
	}
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	transaction[counter] = *transData;
	transaction[counter].terminalData.transAmount = transData -> terminalData.transAmount;
	transaction[counter].transactionSequenceNumber = counter;
	counter++;
	return SERVER_OK;
}
void listSavedTransactions(void)
{
	for(int i = 0; i < counter; i++)
	{
		printf("#########################\n");
		printf("Transaction Sequence Number: %d\n",transaction[i].transactionSequenceNumber);
		printf("Transaction Date: %s \n",transaction[i].terminalData.transactionDate);
		printf("Transaction Amount: %0.1f\n",transaction[i].terminalData.transAmount);
		printf("Transaction State: %s \n",transState_enum[transaction[i].transState]);
		printf("Terminal Max Amount: %0.1f\n", transaction[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s \n", transaction[i].cardHolderData.cardHolderName);
		printf("PAN: %s \n", transaction[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s \n",transaction[i].cardHolderData.cardExpirationDate);

	}
}

/******************Test Functions**********************/
void recieveTransactionDataTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: PAN=8989374615438851 Invalid PAN\n");
	printf("Expected Result: FRAUD_CARD\n");
	ST_transaction_t transData = {.cardHolderData = {.primaryAccountNumber="8989374615438851"}};
	printf("Actual Result: %s\n",transState_enum[recieveTransactionData(&transData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: PAN=8989374615436851 Valid PAN and transAmount = 3000 \n");
	printf("Expected Result: DECLINED_INSUFFECIENT_FUND\n");
	ST_transaction_t transData2 = {.cardHolderData = {.primaryAccountNumber="8989374615436851"},.terminalData = {.transAmount = 3000}};
	printf("Actual Result: %s\n",transState_enum[recieveTransactionData(&transData2)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 3: \n"); 
	printf("Input Data: PAN=5807007076043875 BLOCKED PAN \n");
	printf("Expected Result: DECLINED_STOLEN_CARD\n");
	ST_transaction_t transData3 = {.cardHolderData = {.primaryAccountNumber="5807007076043875"}};
	printf("Actual Result: %s\n",transState_enum[recieveTransactionData(&transData3)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 4: \n"); 
	printf("Input Data: PAN=8989374615438851 Valid PAN and transState = INTERNAL_SERVER_ERROR\n");
	printf("Expected Result: INTERNAL_SERVER_ERROR\n");
	ST_transaction_t transData4 = {.cardHolderData = {.primaryAccountNumber="58070070760438abc"},.transState = INTERNAL_SERVER_ERROR};
	printf("Actual Result: %s\n",transState_enum[recieveTransactionData(&transData4)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 5: \n"); 
	printf("Input Data: PAN=8989374615436851 Valid PAN \n");
	printf("Expected Result: APPROVED\n");
	ST_transaction_t transData5 = {.cardHolderData = {.primaryAccountNumber="8989374615436851"}};
	printf("Actual Result: %s\n",transState_enum[recieveTransactionData(&transData5)]);
}

void isValidAccountTest(void)
{
	ST_accountsDB_t accountsDB[255] = {
		{2000.0, RUNNING, "8989374615436851"},
		{100000.0, BLOCKED, "5807007076043875"},
	};
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: PAN=8989374615438851 Invalid PAN\n");
	printf("Expected Result: ACCOUNT_NOT_FOUND\n");
	ST_cardData_t cardData = {.primaryAccountNumber="8989374615438851"};
	printf("Actual Result: %s\n",serverState_enum[isValidAccount(&cardData,&accountsDB[0])]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: PAN=8989374615436851 Valid PAN\n");
	printf("Expected Result: SERVER_OK\n");
	ST_cardData_t cardData2 = {.primaryAccountNumber = "8989374615436851"};
	printf("Actual Result: %s\n",serverState_enum[isValidAccount(&cardData2,&accountsDB[0])]);
	
}
void isBlockedAccountTest(void)
{
	ST_accountsDB_t accountsDB[255] = {
		{2000.0, RUNNING, "8989374615436851"},
		{100000.0, BLOCKED, "5807007076043875"},
	};
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: PAN=8989374615436851 RUNNING\n");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: %s\n",serverState_enum[isBlockedAccount(&accountsDB[0])]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: PAN=5807007076043875 BLOCKED\n");
	printf("Expected Result: BLOCKED_ACCOUNT\n");
	printf("Actual Result: %s\n",serverState_enum[isBlockedAccount(&accountsDB[1])]);
}
void isAmountAvailableTest(void)
{
	ST_accountsDB_t accountsDB[255] = {
		{2000.0, RUNNING, "8989374615436851"},
		{12000.0, RUNNING, "8989374615436852"},
	};
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isAmountAvailable\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: PAN=8989374615436851\n");
	printf("Expected Result: LOW_BALANCE\n");
	ST_terminalData_t termData = {.transAmount = 5000};
	printf("Actual Result: %s\n",serverState_enum[isAmountAvailable(&termData,&accountsDB[0])]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: isAmountAvailable\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: PAN=8989374615436852 \n");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: %s\n",serverState_enum[isAmountAvailable(&termData,&accountsDB[1])]);
}
void saveTransactionTest(void)
{
	printf("Tester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 1: \n"); 
	printf("Input Data: transState = APPROVED\n");
	printf("Expected Result: SERVER_OK\n");
	ST_transaction_t transData = {.transState = APPROVED};
	printf("Actual Result: %s\n",serverState_enum[saveTransaction(&transData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: transState = DECLINED_INSUFFECIENT_FUND\n");
	printf("Expected Result: SERVER_OK\n");
	transData.transState = DECLINED_INSUFFECIENT_FUND;
	printf("Actual Result: %s\n",serverState_enum[saveTransaction(&transData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 3: \n"); 
	printf("Input Data: transState = DECLINED_STOLEN_CARD\n");
	printf("Expected Result: SERVER_OK\n");
	transData.transState = DECLINED_STOLEN_CARD;
	printf("Actual Result: %s\n",serverState_enum[saveTransaction(&transData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: transState = FRAUD_CARD\n");
	printf("Expected Result: SERVER_OK\n");
	transData.transState = FRAUD_CARD;
	printf("Actual Result: %s\n",serverState_enum[saveTransaction(&transData)]);
	
	printf("\nTester Name: Mohamed Wael Mohamed\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 2: \n"); 
	printf("Input Data: transState = INTERNAL_SERVER_ERROR\n");
	printf("Expected Result: SERVER_OK\n");
	transData.transState = INTERNAL_SERVER_ERROR;
	printf("Actual Result: %s\n",serverState_enum[saveTransaction(&transData)]);
	listSavedTransactions();
}
void listSavedTransactionsTest(void)
{
	ST_transaction_t transaction1 = {
		.cardHolderData = {"Mohamed Wael Mohamed", "8989374615436851", "12/24"},
		.terminalData = {1000, 20000, "01/06/2000"},
		.transState = APPROVED,
		.transactionSequenceNumber = 0
		};
	transaction[0] = transaction1;
	counter++;
	listSavedTransactions();
}

/*****************************************************/