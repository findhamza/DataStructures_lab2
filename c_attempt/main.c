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
	scanf("%d",&initialBounds.lBound);

	printf("\nPlease enter upper bound (M): ");
	scanf("%d",&initialBounds.mBound);

	stackSize = initialBounds.mBound - initialBounds.lBound;
	printf("\nStack size: %d\n",stackSize);

	printf("\nStack slot given to user is: [%d..%d]\n",usableBounds.lBound,usableBounds.mBound);

	//build initial multi stack bounds
	stack = EqualAlloc(stackSizeUsable);
	int mainArrSize = initialBounds.mBound-initialBounds.lBound;
	char mainArr[mainArrSize][35];

	//loop to push and pop
	char cmd; int numcmd;
	char name[35];
	scanf("%c",&cmd);
	while(cmd != 's')
	{
		if(cmd=='I')
		{
			scanf("%d %s",&numcmd,name);
			int pos = push(stack,numcmd);
			switch(numcmd)
			{
				case 1:
					stack.oneTop = pos;
					break;
				case 2:
					stack.twoTop = pos;
					break;
				case 3:
					stack.threeTop = pos;
					break;
				default:
					printf("INVALID STACK REFERENCE");
					break;
			}
			strcpy(mainArr[pos], name);

		}
		for(int i = 0; i<mainArrSize; i++)
		{
			if(mainArr[i] != "/0")
				printf("\n%d: %s",i ,mainArr[i]);
			else
				printf("\n%d: ===",i);
		}



		scanf("%c",&cmd);
	}

	return 0;
}

struct tripleStack EqualAlloc(int stackSizeUsable)
{
	int size = (int)trunc(stackSizeUsable/3);
	struct tripleStack stack;
	for(int i=1; i<=3; i++)
	{
		switch(i)
		{
			case 1:
				stack.one.mBound = size*i;
				stack.one.lBound = (stack.one.mBound - size);
				stack.oneTop = stack.one.lBound;
				break;
			case 2:
				stack.two.mBound = size*i;
				stack.two.lBound = (stack.two.mBound - size);
				stack.twoTop = stack.two.lBound;
				break;
			case 3:
				stack.three.mBound = size*i+(stackSizeUsable-(size*2));
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

