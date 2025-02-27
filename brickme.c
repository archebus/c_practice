#include <stdio.h>

int main() {
    int x = 5;
    int p = x;

    int a = 5;
    int *b = &a;

    printf("Curious: x is %d and p is %d\n",x ,p);
    printf("And now: a is %d and b is %p\n",a ,(void*)b);
    printf("And I can get the specific value here: %d\n", *b);

    return 0;
}
