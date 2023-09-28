// Maximum Sum Subarray
#include <stdio.h>
#include <stdlib.h>

struct SubArray{
   int start;
   int end;
   int sum;
};

struct SubArray kadane(int* numbers, int length){
    struct SubArray bestSubArray = {0, 0, numbers[0]};
    struct SubArray prevSubArray = {0, 0, numbers[0]};

    for(int j = 1; j < length; j++){
        prevSubArray = (struct SubArray){prevSubArray.start, j, prevSubArray.sum + numbers[j]};
        if (prevSubArray.sum <= 0) {
            prevSubArray = (struct SubArray){j + 1, j + 1, 0};
        }    
        else {
            if (prevSubArray.sum > bestSubArray.sum)
                bestSubArray = prevSubArray;
        }
    }
    return bestSubArray;
}

int main(int argc, char* argv[]){
    printf("Enter numbers (then press 0 and enter): ");
    int numbersLength = 1;
    int* numbers = (int*)malloc(numbersLength * sizeof(int)); 
    int x = 0;
    int i = 0;
    while(scanf("%d", &x) == 1 && x != 0){
        if(i == numbersLength){
            numbers = (int*)realloc(numbers, (numbersLength + 1) * sizeof(int));
            numbersLength++;
        }
        numbers[i] = x;
        i++;
    }
    struct SubArray result = kadane(numbers, i);
    printf("Max Sub Array: ");
    for(i = result.start; i <= result.end; i++){
        printf("%d ", numbers[i]);
    }
    printf("\n");
    free(numbers);
    return 0;
}
