/* ceil example */
#include <stdio.h> /* printf */
#include <math.h>  /* ceil */
 
int main()
{
    printf("ceil of 2.3 is %.1f\n", ceil(2));       //ceil of 2.3 is 2.0
    printf("ceil of 2.3 is %.1f\n", ceil(2.0));     //ceil of 2.3 is 2.0
    printf("ceil of 2.3 is %.1f\n", ceil(2.3));     //ceil of 2.3 is 3.0
    printf("ceil of 3.8 is %.1f\n", ceil(3.8));     //ceil of 3.8 is 4.0

    printf("ceil of -2.3 is %.1f\n", ceil(-2.0));   //ceil of -2.3 is -2.0    
    printf("ceil of -2.3 is %.1f\n", ceil(-2.3));   //ceil of -2.3 is -2.0    
    printf("ceil of -3.8 is %.1f\n", ceil(-3.8));   //ceil of -3.8 is -3.0    
    
    printf("--------------------------------\n");
    printf("ceil of 2.3 is %.1f\n", floor(2.0));    //ceil of 2.3 is 2.0
    printf("ceil of 2.3 is %.1f\n", floor(2.3));    //ceil of 2.3 is 2.0

    printf("ceil of -2.3 is %.1f\n", floor(-2.3));  //ceil of -2.3 is -3.0
    printf("ceil of -3.8 is %.1f\n", floor(-3.8));  //ceil of -3.8 is -4.0    
    printf("ceil of -3.8 is %.1f\n", floor(-3.0));  //ceil of -3.8 is -3.0

    return 0;
}