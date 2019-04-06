#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
	//stack allocated values
	int stackSize;
	struct bounds initialBounds;
	int lBound;
	int mBound;
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

	//loop to push and pop

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
				stack.one.lBound = (stack.one.mBound - size) + 1;
				break;
			case 2:
				stack.two.mBound = size*i;
				stack.two.lBound = (stack.two.mBound - size) + 1;
				break;
			case 3:
				stack.three.mBound = size*i+(stackSizeUsable-(size*2));
				stack.three.lBound = (stack.three.mBound - size) + 1;
				break;
			default:
				break;
		}
	}
	return stack;
}
