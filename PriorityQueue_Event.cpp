#include "PriorityQueue_Event.h" 
#include "Event.h"

bool hasLeftChild(int pos, PriQ_Ev*pPriQ_Ev) 
{ 
	if (pos* 2 <= pPriQ_Ev->priQ_size) 
		return true; 
	else 
		return false; 
}

bool hasRightChild(int pos, PriQ_Ev*pPriQ_Ev) 
{ 
	if (pos* 2 + 1 <= pPriQ_Ev->priQ_size) 
		return true;
	else 
		return false; 
} 

PriQ_Ev*initPriQ_Ev(PriQ_Ev*pPriQ_Ev,const char *name, int capacity ) 
{ 
	strcpy(pPriQ_Ev->PriQ_name, name); 
	pPriQ_Ev->priQ_capacity= capacity;
	pPriQ_Ev->pCBT_Ev= (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));
	pPriQ_Ev->priQ_size= 0; pPriQ_Ev->pos_last= 0; 
	
	return pPriQ_Ev; 
}

void deletePriQ_Ev(PriQ_Ev*pPriQ_Ev) 
{ 
	CBTN_Event*pCBTN_Ev;
	for (int i = 0; i < pPriQ_Ev->priQ_size; i++) 
	{ 
		pCBTN_Ev = &(pPriQ_Ev->pCBT_Ev)[i];
		
		if (pCBTN_Ev != NULL) 
		{ 
			if (pCBTN_Ev->pEv != NULL) 
				free(pCBTN_Ev->pEv); free(pCBTN_Ev); 
		} 
	} 
} 

int insertPriQ_Ev(PriQ_Ev *pPriQ_Ev, Event *pEv)
{
	int pos, pos_parent; 
	CBTN_Event CBTN_Ev_tmp; 
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity) 
	{ 
		// Priority Queue is full 
		/* Expand the capacity twice, and copy the entries *///수용가능 용량보다 size가크면 capacity를 2배로생성
		CBTN_Event*newCBT_Event; 
		int newCapacity; 
		newCapacity= 2 * pPriQ_Ev->priQ_capacity;
		newCBT_Event= (CBTN_Event*)malloc((newCapacity+ 1) * sizeof(CBTN_Event)); 
		
		if (newCBT_Event== NULL)
		{ 
			printf("Error in expanding CompleteBinaryTreefor Priority Queue !!\n");
			exit(-1);
		}

		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++) //인덱스 은 안쓰니까 for loof 에서 =있음
		{ 
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Ev[pos];
		} 
		free(pPriQ_Ev->pCBT_Ev);
		pPriQ_Ev->pCBT_Ev = newCBT_Event; 
		pPriQ_Ev->priQ_capacity = newCapacity;

	} // end -if 
	/* insert at the last position */
	pos= pos_parent = ++pPriQ_Ev->priQ_size;
	pPriQ_Ev->pCBT_Ev[pos].priority = pEv->event_pri;
	pPriQ_Ev->pCBT_Ev[pos].pEv= pEv; 
	/* up-heap bubbling*/ 
	
	while (pos!= POS_ROOT)
	{ 
		pos_parent= pos/ 2; 
		
		if (pPriQ_Ev->pCBT_Ev[pos].priority >= pPriQ_Ev->pCBT_Ev[pos_parent].priority) 
		{
			break; // if the priority of the new packet is lower than its parent's priority, 
				   // just stop up-heap bubbling 
		}
		else 
		{ 
			CBTN_Ev_tmp= pPriQ_Ev->pCBT_Ev[pos_parent];
			pPriQ_Ev->pCBT_Ev[pos_parent] = pPriQ_Ev->pCBT_Ev[pos]; 
			pPriQ_Ev->pCBT_Ev[pos] = CBTN_Ev_tmp;
			pos= pos_parent; 
		} 

	} // end -while
}
Event *removeMinPriQ_Ev(PriQ_Ev*pPriQ_Ev)
{
	Event *pEv;
	CBTN_Event CBT_Event_tmp; 
	int pos, pos_root = 1, pos_last, pos_child;
	
	if (pPriQ_Ev->priQ_size <= 0) 
		return NULL;  // Priority queue is empty
	
	pEv= pPriQ_Ev->pCBT_Ev[1].pEv; // get the packet address of current top
	pos_last= pPriQ_Ev->priQ_size;
	--pPriQ_Ev->priQ_size;//하나 제거했으니까 size도 하나 빼줌
	
	if (pPriQ_Ev->priQ_size> 0)
	{ 
		/* put the last node into the top position */
		pPriQ_Ev->pCBT_Ev[pos_root] = pPriQ_Ev->pCBT_Ev[pos_last];
		pos_last--; 
		/* down heap bubbling */
		pos= pos_root;
		
		while (hasLeftChild(pos, pPriQ_Ev))//왼쪽 자식이 있는지
		{ 
			pos_child= pos* 2; 
			
			if (hasRightChild(pos, pPriQ_Ev))//오른쪽 자식이 있는지
			{ 
				if (pPriQ_Ev->pCBT_Ev[pos_child].priority >pPriQ_Ev->pCBT_Ev[pos_child+1].priority) 
					pos_child= pos* 2 + 1; // if right child has higher priority, then select it 
				else if (pPriQ_Ev->pCBT_Ev[pos_child].priority == pPriQ_Ev->pCBT_Ev[pos_child + 1].priority)//우선순위가 같을때
				{
					if (pPriQ_Ev->pCBT_Ev[pos_child].pEv->event_no > pPriQ_Ev->pCBT_Ev[pos_child + 1].pEv->event_no)
						pos_child = pos * 2 + 1;
					else
						pos_child = pos * 2;
				}

			}
			/* if the Event in pos_childhas higher priority than Event in pos, swap them */ 
			if (pPriQ_Ev->pCBT_Ev[pos_child].priority <pPriQ_Ev->pCBT_Ev[pos].priority) 
			{ 
				
				CBT_Event_tmp = pPriQ_Ev->pCBT_Ev[pos];
				pPriQ_Ev->pCBT_Ev[pos] = pPriQ_Ev->pCBT_Ev[pos_child];
				pPriQ_Ev->pCBT_Ev[pos_child] = CBT_Event_tmp;
			}
			else if (pPriQ_Ev->pCBT_Ev[pos_child].priority == pPriQ_Ev->pCBT_Ev[pos].priority)
			{
				if (pPriQ_Ev->pCBT_Ev[pos].pEv->event_no < pPriQ_Ev->pCBT_Ev[pos_child].pEv->event_no)
					break;
				else
					CBT_Event_tmp = pPriQ_Ev->pCBT_Ev[pos];
					pPriQ_Ev->pCBT_Ev[pos] = pPriQ_Ev->pCBT_Ev[pos_child];
					pPriQ_Ev->pCBT_Ev[pos_child] = CBT_Event_tmp;
			}
			else 
			{ 
				break;
			} 
			
			pos = pos_child;
		} // end while 
	} // end if 
	return pEv;
}
void fprintPriQ_Ev(FILE *fout, PriQ_Ev *pPriQ_Ev) 
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1; 
	Event *pEv;
	
	if (pPriQ_Ev->priQ_size == 0)
	{ 
		fprintf(fout, "PriorityQueue_Eventis empty !!\n");
		return; 
	} 
	pos = 1; 
	count = 1;

	level = 0;
	level_count = 1; // level_count= 2^^level 
	fprintf(fout, "\n CompBinTree:\n", level); 
	
	while (count <= pPriQ_Ev->priQ_size)
	{ 
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0; 
		
		while (count_per_line < level_count) 
		{ 
			pEv = pPriQ_Ev->pCBT_Ev[pos].pEv; eventPriority = pPriQ_Ev->pCBT_Ev[pos].priority; 
			fprintEvent(fout, pEv); pos++; count++;
			
			if (count > pPriQ_Ev->priQ_size) 
				break;
			count_per_line++; 
			
			if ((count_per_line% EVENT_PER_LINE) == 0) 
			{ 
				if (count_per_line < level_count) 
					fprintf(fout, "\n           ");
				else fprintf(fout, "\n"); 
			} 
		}  // end -while 
		if ((count_per_line% EVENT_PER_LINE) != 0) 
			fprintf(fout, "\n"); 
		level++;
		level_count*= 2; 
	} // end -while 
	fprintf(fout, "\n");
}
void printPriQ_Ev(PriQ_Ev*pPriQ_Ev)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event *pEv;

	if (pPriQ_Ev->priQ_size == 0)
	{
		printf( "PriorityQueue_Eventis empty !!\n");
		return;
	}
	pos = 1;
	count = 1;

	level = 0;
	level_count = 1; // level_count= 2^^level 
	printf( "\n CompBinTree:\n", level);

	while (count <= pPriQ_Ev->priQ_size)
	{
		printf( " level%2d : ", level);
		count_per_line = 0;

		while (count_per_line < level_count)
		{
			pEv = pPriQ_Ev->pCBT_Ev[pos].pEv; eventPriority = pPriQ_Ev->pCBT_Ev[pos].priority;
			printEvent( pEv); 
			pos++; 
			count++;

			if (count > pPriQ_Ev->priQ_size)
				break;
			count_per_line++;

			if ((count_per_line% EVENT_PER_LINE) == 0)
			{
				if (count_per_line < level_count)
					printf( "\n           ");
				else printf( "\n");
			}
		}  // end -while 
		if ((count_per_line% EVENT_PER_LINE) != 0)
			printf( "\n");
		level++;
		level_count *= 2;
	} // end -while 
	printf( "\n");
}