#include <stdio.h>
#include "Clients.h"

void ClientSetEnterTime(Client *elempentPtr, int sim_time)
{
	elempentPtr->EnterTime=sim_time;
}

int ClientGetEnterTime(Client *elempentPtr)
{
	return elempentPtr->EnterTime;
}
void Client_setValue(Client *elempentPtr, Client testdata)
{   
	elempentPtr->EnterTime = testdata.EnterTime;  /* basic type assignment */
}
void Client_printValue(Client testdata)
{ printf("|Enter sim_time = %d|", testdata.EnterTime);
}

int Client_readValue(Client *testdata)
{ 
	if (scanf("%d", &(testdata->EnterTime))!= 1)
		return 0;
	else return 1;
}

void ClientSetServiceTime(Client *elempentPtr, int duration){
	elempentPtr->ServiceTime = duration;
}

int ClientGetServiceTime(Client *elempentPtr){
	return elempentPtr->ServiceTime;
}
