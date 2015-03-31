#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Queue.h"
#include "Clients.h"
#include "Cashiers.h"

#define CASHIERS 10

int main(void)
{	Queue      		queue;				 			/*Clients' queue*/
	float			arrival_prob; 					/*Probability of client's arrival*/
	unsigned int	max_service_time;				/*Max sim_time a client will be served*/ 
	unsigned int	bank_working_hours; 			/*The sim_time until bank will take clients*/
	
	unsigned int	sim_time;				 			/*Simulator's clock*/
	unsigned int	wait_time;	 			/*Total wait sim_time*/
	Client		Client;		 				/*Client in queue*/
	float			average_time;		 			/*Average wait sim_time*/
	float			random_arrival;
	time_t			t;
	
	Cashier			cashier[CASHIERS]; 				//Array of cashier structs for each cashier
	int next_cashier_spot = 0;					//The cashier which will serve the next client
	int duration;									//Client's service sim_time
	int i,j;
	int clients_number = 0;						//The number of clients entered the bank
	int next_cashier = 0;							//Next cashier to open if queue is too long
	int flag = 0;
	char choice;									//choice gia tin leitourgia tis prosomiosis (erwtima 6 i 7)
	int free_cashier[CASHIERS];						//An array with the inactive cashiers
	int busy_cashier = 1;							//1 if there is a busy cashier


	printf("Would you like a different policy to be applied? (Y/N)\n");
	choice = getchar();
	
	printf("Give working time (0 <=), probability of arrival (0,1) and max service time (>=1) )\n");
	scanf("%u %f %u",&bank_working_hours,&arrival_prob,&max_service_time);
	getchar();
	
	printf("Bank will stay open for %4u minutes.\n",bank_working_hours);
	printf("Probability of client to arrive: %4.2f.\n",arrival_prob);
	printf("Max service time is: %d minutes.\n",max_service_time);

	CreateQueue(&queue);
	sim_time = 0;
	
	for(i=0; i<CASHIERS; i++){
		CreateCashier(&cashier[i]); 				//Init of every cashier
	}
	
	
	if(choice == 'Y'){								//if choice is Yes
		ChangeCashierState(&cashier[0]);				//it opens just the first cashier
	}else{											//else
		for(i=0;i<CASHIERS;i++){
			ChangeCashierState(&cashier[i]);			//it opens every cashier
		}
		for(i=0; i<CASHIERS; i++){
			free_cashier[i] = i;						//init array
		}
	}

	wait_time = 0;
	srand(time(&t));

	while( (sim_time < bank_working_hours || !QueueEmpty(queue)) || busy_cashier == 1 ) //Runs while : bank is open, queue is not empty and cashiers are not free
	{
		busy_cashier = 0;

		random_arrival = (float)rand()/(float)RAND_MAX;
		
		if ( random_arrival < arrival_prob && sim_time < bank_working_hours){
			clients_number++;						//increases number of clients entered the bank
			ClientSetEnterTime(&Client, sim_time);
			duration = rand()%max_service_time + 1; //service sim_time
			ClientSetServiceTime(&Client, duration);	
			if (!QueueAddition(&queue, Client)){
                printf("Queue is small! Simulation stops! \n");
                getchar();
                return 0;
        	}
    	}
    	
    	if(choice == 'Y'){
    		if(QueueSize(queue) > bank_working_hours/CASHIERS){					//if queue size is longer than a number
    			if(next_cashier <= CASHIERS){								//and there is available cashier
    				ChangeCashierState(&cashier[next_cashier]);				//cashier opens
    				next_cashier++;										//and index for next cashier increases
    			}
    		}else if(QueueSize(queue) < bank_working_hours/(CASHIERS*2)){			//else if queue size is lesser than a number
    			next_cashier--;											//index for next cashier decreases
    			ChangeCashierState(&cashier[next_cashier]);					//and last cashier closes
    		}
    	
    		/*Searches for the cashier which will serve next client*/
    		for(i = next_cashier_spot; i < next_cashier - 1; i++){
    			if(CashierFree(cashier[i]) == 1){
    				next_cashier_spot = i;
    				flag = 1;												//if the is no free cashier in this field
    				break;
    			}
    		}
    		if(!flag){														//starts again from  0
    			for(i = 0; i < next_cashier_spot; i++){
    				next_cashier_spot = i;
    				break;
    			}
    		}
    		
    		/* Increases Busy and Inactive sim_time of each cashier*/
    		for(i = 0; i < next_cashier - 1; i++){
	    		if(CashierFree(cashier[i])){
	    			CashierNoWork(&cashier[i]);
	    		}else{
	    			CashierBusy(&cashier[i]);
	    		}
	    	}
	    	
    		flag = 0;
    		for(i = 0; i < next_cashier -1; i++){
				if(CashierFree(cashier[i]) == 0){
					busy_cashier = 1;
					break;
				}
			}
    	}else if(choice == 'O'){
    		/* Auksanei tous xronous Busy kai Inactive tou kathe tameia*/
    		for(i = 0; i < CASHIERS; i++){
	    		if(CashierFree(cashier[i])){
	    			CashierNoWork(&cashier[i]);
	    		}else{
	    			CashierBusy(&cashier[i]);
	    		}
	    	}
	    	
	    	/*Updates free_cashier array with free cashiers*/
    		for(i = 0; i < CASHIERS; i++){
    			if(CashierFree(cashier[i]) == 1){
    				for(j = 0; j < CASHIERS; j++){
    					if(free_cashier[j] == i )
    						break;
    						
    					if(free_cashier[j] == -1){
    						free_cashier[j] = i;
    						break;
    					}
    				}
    			}
    		}
    		/* Chooses the first of available cashiers to serve the next client*/
    		if(free_cashier[0] != -1){
	    		next_cashier_spot = free_cashier[0];
	    		for(i = 1; i < CASHIERS; i++){
	    			free_cashier[i-1] = free_cashier[i]; 			//moves cashiers one spot to the left
	    		}
	    		free_cashier[CASHIERS - 1] = -1;					//sets -1 to last spot as empty
    		}
    		for(i = 0; i < CASHIERS; i++){
				if(CashierFree(cashier[i]) == 0){
					busy_cashier = 1;
					break;
				}
			}
    	}
    	

		if ( CashierFree(cashier[next_cashier_spot]))							/*If there is free cashier*/
			if (!QueueEmpty(queue))												/*and a client*/
			{	QueueLeave(&queue,&Client);								/*client goes to cashier*/
				wait_time += sim_time - ClientGetEnterTime(&Client);	/*calculates wait sim_time*/
				CashierNewCustomer(&cashier[next_cashier_spot]);
				CashierSetTime(&cashier[next_cashier_spot], ClientGetServiceTime(&Client));
			}
		
		sim_time++; /*simulator clock increases*/
		
	} 

	if (CashierGetClientNumber(&cashier[next_cashier_spot]) == 0)
		average_time = 0.0;
	else
		average_time = ((float)wait_time)/((float)clients_number);

	printf("\nClients Served : %d\n",clients_number);
	printf("Average wait time : %4.2f minutes.\n",average_time);
	printf("Total working time: %d\n",sim_time);
	printf("Time after working hour: %d\n", sim_time - bank_working_hours);
	
	for(i = 0; i < CASHIERS; i++){
		printf("Cashier : %d\n", i+1);
		printf("\tClient number : %d\n", cashier[i].ClientNumber);
		printf("\tBusy time : %d\n", cashier[i].TimeBusy);
		printf("\tInactive time : %d\n", cashier[i].TimeInactive);
	}
    getchar();
	return 0;
}
