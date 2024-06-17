#include <stdio.h>

void function(double *p){

}

int main(void){
    double *p;
    int N;
    p = (double *)malloc(N * sizeof(double));

    printf("%lf\n", p);

    free(p);

    return 0;
}