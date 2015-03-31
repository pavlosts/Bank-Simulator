#ifndef __TAMIAS__
#define __TAMIAS__



typedef struct {
	int TimeBusy; //sim_time apasxolisis tou tamia
	int TimeInactive; //sim_time adranias tou tamia
	int ClientNumber; //arithmos pelatwn pou eksipiretise
	int TimeLeft; //sim_time pou apomenei gia tin eksipiretisi tou pelati
	int Open_Cashier;
} Cashier;

/*Dilwsi sunartisewn*/

void CreateCashier(Cashier *cashier); //arxikopoiei to struct tou tamia

void CashierNewCustomer(Cashier *cashier); //prostheti pelati kai auksanei ta lepta kata 1

void CashierSetTime(Cashier *cashier, int duration); //arxikopoiei enapominanta xrono

void CashierNoWork(Cashier *cashier); //auksanei xrono adranias

void CashierBusy(Cashier *cashier); //auksanei xrono apasxolisis

void ChangeCashierState(Cashier *cashier);

int CashierFree(Cashier cashier); //elegxei an einai diathesimos

int CashierGetClientNumber(Cashier *cashier); //epistrefei arithmo pelatwn

int CashierGetTimeLeft(Cashier *cashier); //epistrefei enapomenon xrono

int CashierGetInactiveTime(Cashier *cashier); //epistrefei xrono adraneias

int CashierGetBusyTime(Cashier *cashier); //epistrefei xrono apasxolisis

int CashierGetState(Cashier *cashier); //epistrefei tin katastasi tou tameia (anoixto/kleisto)

#endif
