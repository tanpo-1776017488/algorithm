#include <stdio.h>
#include <time.h>
#include "Event.h"
#include "PriorityQueue_Event.h" 


#define TOTAL_NUM_EVENTS 50
#define MAX_EVENTS_PER_ROUND 5 
#define MAX_ROUND 100 
#define INIT_PriQ_SIZE 1 

void main()
{
	PriQ_Ev *PriQ_Event;  
	Event *pEv = NULL;      
	int data;    
	FILE *fout;    
	int processed_events = 0;    
	int generated_events = 0;     
	int num_events = 0;
	fout = fopen("output3.txt", "w");   
	
	if (fout == NULL) 
	{ 
		printf("Error in output.txt file open in write mode !!\n");   
		exit(-1); 
	}      
	PriQ_Event = (PriQ_Ev *)malloc(sizeof(PriQ_Ev));    
	
	if (PriQ_Event == NULL) 
	{
		printf("Error in malloc() for PriorityQueue_Event !\n");  
		fclose(fout);      
		exit(-1);
	}      initPriQ_Ev(PriQ_Event, "PriorityQueue_Event", INIT_PriQ_SIZE);

	srand(time(0));  
	
	for (int round = 0; round < MAX_ROUND; round++)
	{
		if (generated_events < TOTAL_NUM_EVENTS)
		{ 
			num_events = rand() % MAX_EVENTS_PER_ROUND;    
			
			if ((generated_events + num_events) > TOTAL_NUM_EVENTS)       
				num_events = TOTAL_NUM_EVENTS - generated_events; 
			fprintf(fout, ">>> enque %2d events\n", num_events);
			printf( ">>> enque %2d events\n", num_events);
			
			for (int i = 0; i < num_events; i++) 
			{ 
				pEv = genEvent(pEv, 0, generated_events, TOTAL_NUM_EVENTS - generated_events - 1);
				if (pEv == NULL)
				{ 
					printf("Error in generation of event !!\n");   
					fclose(fout);                         
					exit(-1);
				}                    
				fprintf(fout, " *** enqued event : ");   
				printf( " *** enqued event : ");
				fprintEvent(fout, pEv);
				printEvent( pEv);
				insertPriQ_Ev(PriQ_Event, pEv); //up-bubble      
				generated_events++;              
				fprintPriQ_Ev(fout, PriQ_Event);
				printPriQ_Ev( PriQ_Event);
			} 
		}

		num_events = rand() % MAX_EVENTS_PER_ROUND;    
		
		if ((processed_events + num_events) > TOTAL_NUM_EVENTS)     
			num_events = TOTAL_NUM_EVENTS - processed_events;   
		fprintf(fout, "<<< dequeue %2d events\n", num_events); 
		printf( "<<< dequeue %2d events\n", num_events);
		for (int i = 0; i < num_events; i++) 
		{
			pEv = removeMinPriQ_Ev(PriQ_Event);
			if (pEv == NULL)
			{ 
				fprintf(fout, "  PriQ is empty\n"); 
				printf("  PriQ is empty\n");
				break;
			}

			fprintf(fout, " *** dequeued event : ");  
			printf( " *** dequeued event : ");
			fprintEvent(fout, pEv);    
			printEvent( pEv);
			fprintPriQ_Ev(fout, PriQ_Event);  
			printPriQ_Ev( PriQ_Event);
			processed_events++;
		}                  
		fprintf(fout, "\nRound(%2d): total_generated_events(%3d), total_processed_events(%3d),  PriQ capacity (%2d), events_in_PriQ(%3d)\n", round, generated_events, processed_events, PriQ_Event->priQ_capacity, PriQ_Event->priQ_size);
		printf( "\nRound(%2d): total_generated_events(%3d), total_processed_events(%3d),  PriQ capacity (%2d), events_in_PriQ(%3d)\n", round, generated_events, processed_events, PriQ_Event->priQ_capacity, PriQ_Event->priQ_size);
		fflush(fout);   
		if (processed_events >= TOTAL_NUM_EVENTS)    
			break;
	}     
	deletePriQ_Ev(PriQ_Event);    
	fprintf(fout, "\n");  
	printf( "\n");
	fclose(fout);
}
