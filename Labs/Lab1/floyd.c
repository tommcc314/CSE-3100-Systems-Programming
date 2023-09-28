/* Implementing Floyd's triangle */

#include <stdio.h>

int main(void)
{
    int n = 0;
    printf("Enter number of rows: ");

    /* TODO: Read in the number of rows from the user, and place it in n */
    scanf("%d", &n);
    int num = 1;
    for(int i = 1; i <= n; i++){
        /*

        TODO: Print row i of the Floyd triangle.
        
        */
        for (int j = 0; j < i; ++j, ++num) {
            printf("%d ", num);
        }
        //This printf prints a newline.
        printf("\n");
    }
    return 0;
}
