#ifndef __Clients__ 
#define __Clients__

typedef struct {
	int EnterTime; /* Minute of entering queue */
	int ServiceTime; /* Service sim_time for each client */
} Client;

void ClientSetEnterTime(Client *elempentPtr, int sim_time);
int ClientGetEnterTime(Client *elempentPtr);

void Client_setValue(Client *elempentPtr, Client testdata);

void Client_printValue(Client testdata);
int  Client_readValue(Client *testdata);

void ClientSetServiceTime(Client *elempentPtr, int duration);
int ClientGetServiceTime(Client *elempentPtr);

#endif
