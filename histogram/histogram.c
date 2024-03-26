#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int input; 
    int histogram[16] = {0}; 
    int binsize = 1;
    int range = 16 * binsize;

    printf("16 bins of size %d for range [%d,%d)\n", binsize, 0, range);

    while (scanf("%d", &input) != EOF) {
        if (input < 0){
            continue;
        }
        
        while (input >= range){
            for (int x = 0; x < 16 / 2; x++) {
                histogram[x] = histogram[x*2] + histogram[2*x+1];
            }
            
            memset(&histogram[16 / 2], 0, sizeof(histogram) / 2);
            binsize = binsize * 2;
            range = range * 2;
            printf("16 bins of size %d for range [%d,%d)\n", binsize, 0, range);
        }
        histogram[input / binsize]++;
         
    }

    for (int i = 0; i < 16; i++) {
        printf("[%d:%d] ", i*binsize, (i+1)*binsize-1);
        for (int j = 0; j < histogram[i]; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
