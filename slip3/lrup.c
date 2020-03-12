#include<stdio.h>
#include<stdlib.h>

int pointer;
int faults ,hits;
void print(int frame_size,int frame[])
{
	for(int i=0;i<frame_size;i++)
	{
		if(frame[i]==-1)
			printf("- ");
		else
			printf("%d ",frame[i]);
	}

	printf("\n");
}

int predict(int reference_length, int references[],int frame_size,int frame[], int start)
{
	int pos = -1, farthest = start+1; 		//Assume the base value of farthest to be the one just ahead for now
	for(int i=0;i<frame_size;i++)
	{
		for(int j=start;j>=0;j--)			//Go through the list backwards and see where the last match for the currennt frame was
		{
			if(frame[i]==references[j])
			{
				if(j<farthest)				//If the match index is smaller than the current farthest change it to the new one
				{
					farthest=j;
					pos=i;
				}
				break;
			}
		}
		
	}
	if(pos == -1)
		return 0;
	else
		return pos;		//Return the value of the index of whose the value changes
}


void add(int frame_size,int frame[], int reference, int current_position,int reference_length, int references[])
{
	int allocated=1;
	for(int i=0;i<frame_size;i++)
	{
		
		if(frame[i]==reference)
		{
			printf("  Hit for %d | ", reference);
			hits++;
			allocated = 0;
			break;
		}
		else if(frame[i]==-1)
		{
			frame[i] = reference;
			printf("Fault for %d | ", reference);
			faults++;
			allocated = 0;
			break;
		}
	}
	if(allocated==1)
	{
		int j = predict(reference_length,references,frame_size,frame,current_position);  //Predict which position to insert the value on the basis of Least Recently Used algorithm

		frame[j] = reference; 		//Changes the value of the array depending on the value of j predicted by LRU
		printf("Fault for %d | ", reference);
		faults++;	
	}
	print(frame_size, frame);
}

int main()
{
	int frame_size,i,number_of_references;
	printf("Enter frame size: ");
	scanf("%d",&frame_size);
	int frame[frame_size];
	for(i=0;i<frame_size;i++)
	{
		frame[i] = -1;
	}

	print(frame_size,frame);
	
	printf("Enter the number of references: ");
	scanf("%d",&number_of_references);
	int reference[number_of_references];
	
	for(i=0;i<number_of_references;i++)
	{
		scanf("%d",&reference[i]);
		add(frame_size,frame,reference[i],i,number_of_references,reference);
	}
	printf("\nNumber of faults: %d \nNumber of hits: %d\n",faults,hits );
}
