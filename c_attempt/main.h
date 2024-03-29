/* libraries for multi stack */
#include <math.h>

/* structs to be used for multistack organization */
struct bounds
{
        int lBound;
        int mBound;
};

struct tripleStack
{
        struct bounds one;
        struct bounds two;
        struct bounds three;
        int oneTop;
        int twoTop;
        int threeTop;
};

/* function prototypes */
struct tripleStack EqualAlloc(int,int);
int push(struct tripleStack,int);
struct tripleStack repack(char[][35],struct tripleStack,int);
void stackStat(struct tripleStack);
