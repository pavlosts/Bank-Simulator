#include <stdio.h>
#include <stdlib.h>
#include "Cashiers.h"

void CreateCashier(Cashier *cashier){
	cashier->TimeBusy = 0;
	cashier->TimeInactive = 0;
	cashier->ClientNumber = 0;
	cashier->TimeLeft = 0;
	cashier->Open_Cashier = 0;
}

void CashierNewCustomer(Cashier *cashier){
	cashier->ClientNumber++;
}

void CashierSetTime(Cashier *cashier, int duration){
	cashier->TimeLeft = duration;
}

void CashierNoWork(Cashier *cashier){
	cashier->TimeInactive++;
}

void CashierBusy(Cashier *cashier){
	cashier->TimeBusy++;
	cashier->TimeLeft--;
}

void ChangeCashierState(Cashier *cashier){
	cashier->Open_Cashier = !cashier->Open_Cashier;
}

int CashierFree(Cashier cashier){
	if(cashier.TimeLeft == 0){
		return 1;
	}else{
		return 0;
	}
}

int CashierGetClientNumber(Cashier *cashier){
	return cashier->ClientNumber;
}

int CashierGetTimeLeft(Cashier *cashier){
	return cashier->TimeLeft;
}

int CashierGetInactiveTime(Cashier *cashier){
	return cashier->TimeInactive;
}

int CashierGetBusyTime(Cashier *cashier){
	return cashier->TimeBusy;
}

int CashierGetState(Cashier *cashier){
	return cashier->Open_Cashier;
}

