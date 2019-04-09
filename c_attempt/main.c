#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main()
{
	//stack allocated values
	int stackSize;
	struct bounds initialBounds;
	struct bounds usableBounds;
	usableBounds.lBound = 0;
	usableBounds.mBound = 37;
	int stackSizeUsable = usableBounds.mBound - usableBounds.lBound;
	struct tripleStack stack;


	//initial user interaction for values and boundaries
	printf("Please enter lower bound (L): ");
	scanf("%d",&initialBounds.lBound); printf("%d",initialBounds.lBound);

	printf("\nPlease enter upper bound (M): ");
	scanf("%d",&initialBounds.mBound); printf("%d",initialBounds.mBound);

	stackSize = initialBounds.mBound - initialBounds.lBound;
	printf("\nStack size: %d\n",stackSize);

	printf("\nStack slot given to user is: [%d..%d]\n",usableBounds.lBound,usableBounds.mBound);

	//build initial multi stack bounds
	stack = EqualAlloc(stackSizeUsable,initialBounds.lBound);
	int mainArrSize = initialBounds.mBound-initialBounds.lBound;
	char mainArr[mainArrSize][35];
	for(int i=0; i<mainArrSize;i++)
	{
		mainArr[i][0] = 0;
	}


	//loop to push and pop
	char cmd; int numcmd;
	char name[35];
	memset(name,0,sizeof(name));
//	scanf("%c",&cmd);
	while(cmd != 's')
	{
		//push instructions
		if(cmd=='I')
		{
			scanf("%d%s",&numcmd,name);
			int pos = push(stack,numcmd);
			switch(numcmd)
			{
				case 1:
					if(stack.oneTop < stack.one.mBound)
						stack.oneTop = pos;
					else
						stack.oneTop = stack.one.mBound;
					break;
				case 2:
					if(stack.twoTop < stack.two.mBound)
						stack.twoTop = pos;
					else
					{
						struct tripleStack tempStack = repack(mainArr,stack,stackSizeUsable);
						char tempArr[mainArrSize][35];
						int oneOffset = stack.one.lBound - tempStack.one.lBound;
						int twoOffset = stack.two.lBound - tempStack.two.lBound;
						int threeOffset = stack.three.lBound - tempStack.three.lBound;

						for(int i=0; i<mainArrSize; i++)
						{
							if(i<=stack.one.mBound)
								strcpy(tempArr[i-oneOffset],mainArr[i]);
							else if(i>stack.two.lBound && i<=stack.two.mBound)
								strcpy(tempArr[i-twoOffset],mainArr[i]);
							else if(i>stack.three.lBound)
								strcpy(tempArr[i-threeOffset],mainArr[i]);
						}
						for(int i=0; i<mainArrSize; i++)
							strcpy(mainArr[i],tempArr[i]);
						stack = tempStack; printf("\nstack 2 top: %d\n",tempStack.twoTop);
						stack.twoTop += 2;
						pos = stack.twoTop;
					}
//						stack.twoTop = stack.two.mBound;
					break;
				case 3:
					if(stack.threeTop < stack.three.mBound)
						stack.threeTop = pos;
					else
					{
						struct tripleStack tempStack = repack(mainArr,stack,stackSizeUsable);
						char tempArr[mainArrSize][35];
						int oneOffset = stack.one.lBound - tempStack.one.lBound;
						int twoOffset = stack.two.lBound - tempStack.two.lBound;
						int threeOffset = stack.three.lBound - tempStack.three.lBound;

						for(int i=0; i<mainArrSize; i++)
						{
							if(i<=stack.one.mBound)
								strcpy(tempArr[i-oneOffset],mainArr[i]);
							else if(i>stack.two.lBound && i<=stack.two.mBound)
								strcpy(tempArr[i-twoOffset],mainArr[i]);
							else if(i>stack.three.lBound)
								strcpy(tempArr[i-threeOffset],mainArr[i]);
						}
						for(int i=0; i<mainArrSize; i++)
							strcpy(mainArr[i],tempArr[i]);
						stack = tempStack; printf("\nstack 3 top: %d\n",tempStack.threeTop);
						stack.threeTop += 6;
						pos = stack.threeTop;
					}
//						stack.threeTop = stack.three.mBound;
					break;
				default:
					printf("INVALID STACK REFERENCE");
					break;
			}
			strcpy(mainArr[pos], name);
		}

		//pop instructions
		else if(cmd=='D')
		{
			scanf("%d",&numcmd);
			switch(numcmd)
			{
				case 1:
					mainArr[stack.oneTop][0]=0;
					if(stack.oneTop > stack.one.lBound)
						stack.oneTop -= 1;
					break;
				case 2:
					mainArr[stack.twoTop][0]=0;
					if(stack.twoTop > stack.two.lBound)
						stack.twoTop -= 1;
					break;
				case 3:
					mainArr[stack.threeTop][0]=0;
					if(stack.threeTop > stack.three.lBound)
						stack.threeTop -= 1;
					break;
				default:
					break;
			}
			printf("\nOperation: %c%d",cmd,numcmd);
			memset(name,0,sizeof(name));
		}
		if(strlen(name)>0)
			printf("\nOperation: %c%d %s",cmd,numcmd,name);
		for(int i = 0; i<mainArrSize; i++)
		{
			if(strlen(mainArr[i])!=0)
				printf("\n%d: %s",i+initialBounds.lBound ,mainArr[i]);
		}


		printf("\n");
		scanf("%*c%c",&cmd);
	}

	return 0;
}

struct tripleStack EqualAlloc(int stackSizeUsable, int offset)
{
	int size = (int)trunc(stackSizeUsable/3);
	struct tripleStack stack;
	for(int i=1; i<=3; i++)
	{
		switch(i)
		{
			case 1:
				stack.one.mBound = size*i+(offset*-1);
				stack.one.lBound = (stack.one.mBound - size);
				stack.oneTop = stack.one.lBound;
				break;
			case 2:
				stack.two.mBound = size*i+(offset*-1);
				stack.two.lBound = (stack.two.mBound - size);
				stack.twoTop = stack.two.lBound;
				break;
			case 3:
				stack.three.mBound = size*i+(stackSizeUsable-(size*3))+(offset*-1);
				stack.three.lBound = (stack.three.mBound - size);
				stack.threeTop = stack.three.lBound;
				break;
			default:
				break;
		}
	}
	return stack;
}

int push(struct tripleStack sData, int sNum)
{
	switch(sNum)
	{
		case 1:
			if(sData.oneTop < sData.two.lBound)
				return sData.oneTop+1;
			else
				return sData.oneTop;
			break;
		case 2:
			if(sData.twoTop < sData.three.lBound)
				return sData.twoTop+1;
			else
				return sData.twoTop;
			break;
		case 3:
			if(sData.threeTop < sData.three.mBound)
				return sData.threeTop+1;
			else
				return sData.threeTop;
			break;
		default:
			break;
	}

	return -1;
}

struct tripleStack repack(char mainArr[][35], struct tripleStack stkptr, int usable)
{
	int oneSize = stkptr.oneTop-stkptr.one.lBound;
	int twoSize = stkptr.twoTop-stkptr.two.lBound;
	int threeSize = stkptr.threeTop-stkptr.three.lBound;
	int arrSize = sizeof(mainArr[0])/sizeof(mainArr[0][0]);

/*	for(int i=0;i<arrSize;i++)
	{
		if(i<=stkptr.one.mBound)
		{
			if(strlen(mainArr[i])>0)
				oneSize++;
		}
		else if(i>stkptr.two.lBound && i<=stkptr.two.mBound)
		{
			if(strlen(mainArr[i])>0)
				twoSize++;
		}
		else if(i>stkptr.three.lBound)
		{
			if(strlen(mainArr[i])>0)
				threeSize++;
		}
	}
*/
	int emptySpace = usable-oneSize-twoSize-threeSize;
	int equalSpace = (int)trunc(emptySpace*.23);
	int dynamicSpace = emptySpace - equalSpace;
	int utilizedSpace = oneSize+twoSize+threeSize;

	double oneFrac = oneSize/utilizedSpace;
	stkptr.one.mBound = stkptr.one.lBound+oneSize+equalSpace+((int)trunc(oneFrac*dynamicSpace));
	stkptr.oneTop = stkptr.one.lBound+oneSize;

	double twoFrac = twoSize/utilizedSpace;
	stkptr.two.lBound = stkptr.one.mBound+1;
	stkptr.two.mBound = stkptr.two.lBound+twoSize+equalSpace+((int)trunc(twoFrac*dynamicSpace));
	stkptr.twoTop = stkptr.two.lBound+twoSize;

	double threeFrac = threeSize/utilizedSpace;
	stkptr.three.lBound = stkptr.two.mBound+1;
	stkptr.three.mBound = stkptr.three.lBound+threeSize+equalSpace+((int)trunc(threeFrac*dynamicSpace));
	stkptr.threeTop = stkptr.three.lBound+threeSize;

	printf("\nStack One (L,T,M):   (%d  ,%d  ,%d) size: %d",stkptr.one.lBound-11,stkptr.oneTop-11,stkptr.one.mBound-11,oneSize);
	printf("\nStack Two (L,T,M):   (%d  ,%d  ,%d) size: %d",stkptr.two.lBound-11,stkptr.twoTop-11,stkptr.two.mBound-11,twoSize);
	printf("\nStack Three (L,T,M): (%d  ,%d  ,%d) size: %d",stkptr.three.lBound-11,stkptr.threeTop-11,stkptr.three.mBound-11,threeSize);

	return stkptr;
}
