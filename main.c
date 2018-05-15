/*
* Copyright (c) 2018 Mike Parker. All rights reserved.
* Licensed under the MIT (Expat) License.
* See accompanying LICENSE file in project root for full license information.
*/

#include <stdio.h>
#include <time.h>
#include <math.h>

#include "fast12throot.h"

int main(int argc, const char * argv[]) {

    clock_t begint, endt;
    double x0, dt;
    double dx = 0.1;
    double result;
    //double onethird = 1.0/3.0;
    //double onetwelfth = 1.0/12.0;
    long N = 1000000;

    x0 = 0.0;
    result = 0.0;
    begint = clock();

    printf("--------------------------------\n");
    printf("benchmarking cbrt(sqrt(sqrt(x)))\n");
    printf("--------------------------------\n");
    for (long i=0; i<N; i++) {
        result += cbrt(sqrt(sqrt(x0)));
        x0 += dx;
    }

    endt = clock();
    dt = (double)(endt-begint)/CLOCKS_PER_SEC;

    printf("ans %.17f\n in %f secs\n\n", result, dt);

    x0 = 0.0;
    result = 0.0;
    begint = clock();

    printf("----------------------------\n");
    printf("benchmarking fast12throot(x)\n");
    printf("----------------------------\n");
    for (long i=0; i<N; i++) {
        result += fast12throot(x0);
        x0 += dx;
    }

    endt = clock();
    dt = (double)(endt-begint)/CLOCKS_PER_SEC;

    printf("ans %.17f\n in %f secs\n\n", result, dt);

    x0 = 0.0;
    result = 0.0;
    begint = clock();

    printf("---------------------\n");
    printf("benchmarking x^(1/12)\n");
    printf("---------------------\n");
    for (long i=0; i<N; i++) {
        result += pow(x0,1.0/12.0);
        x0 += dx;
    }

    endt = clock();
    dt = (double)(endt-begint)/CLOCKS_PER_SEC;

    printf("ans %.17f\n in %f secs\n", result, dt);

    return 0;
}
