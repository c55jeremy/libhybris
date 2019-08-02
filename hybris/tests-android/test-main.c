/*
 * test-main.c
 *
 *  Created on: 2019 M07 30
 *      Author: jeremychen
 */
#include <stdio.h>
extern double mysqrt(double r);

int main(int argc, char** argv) {
    printf("\n%lf\n", mysqrt(7));
    return 0;
}
