//
//  main.c
//  open_mp_ej3
//
//  Created by Abraham Esses on 4/18/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

//#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define C1 1.0
#define C2 2.0
#define GOOD 1
#define STOP 0
int main(int argc, const char * argv[]) {
    double matrix[5000][3];
    double c1x,c1y,c2x,c2y;
    int jx,jy;
    double distc1x,distc1y,distc1,distc2x,distc2y,distc2;
    double acumC1x,acumC2x,acumC1y,acumC2y,tC1,tC2;
    int keepGoing = GOOD;
    
#pragma omp parallel for shared(i)
    //filling-matrix
    for (int i = 0; i < 5000; i++) {
        matrix[i][0] = (double)rand()/10.0;
        matrix[i][1] = (double)rand()/10.0;
    }
    printf("Terminé de llenar matriz\n");
    //selecting numbers
    jx = rand()%5000;
    jy = rand()%5000;
    c1x = matrix[jx][0];
    c1y = matrix[jx][1];
    c2x = matrix[jy][0];
    c2y = matrix[jy][1];
    while(keepGoing == GOOD){
    //Calculating distance
#pragma omp parallel for shared (j)
    for (int j = 0; j < 5000; j++) {
        // distance of element j to C1
        distc1x = c1x - matrix[j][0];
        distc1y = c1y - matrix[j][1];
        distc1 = distc1x/distc1y;
        // distance of element j to C2
        distc2x = c2x - matrix[j][0];
        distc2y = c2y - matrix[j][1];
        distc2 = distc2x/distc2y;
        // labeling
        if (distc1 < distc2)
            matrix[j][2] = C1;
        else
            matrix[j][2] = C2;
    
        if (fabs(distc1) <= 0.01 || fabs(distc2) <= 0.01)
        {
            printf("Se debe terminar el proceso\n");
            keepGoing = STOP;
        }
        
    }
    // getting the average
        tC1 = 0;
        tC2 = 0;
        acumC1x = 0;
        acumC1y = 0;
        acumC2x = 0;
        acumC2y = 0;
#pragma omp parallel for
    for (int k = 0; k < 5000 ; k++) {
        //look for C1
        if (matrix[k][2] == C1) {
            acumC1x = matrix[k][0];
            acumC1y = matrix[k][1];
            tC1++;
            c1x = acumC1x/tC1;
            c1y = acumC1y/tC1;
            
        }
        else if (matrix[k][2] == C2){
            acumC2x = matrix[k][0];
            acumC2y = matrix[k][1];
            tC2++;
            c2x = acumC2x/tC2;
            c2y = acumC2y/tC2;
        }
    }
    }//End of while
    return 0;
}
