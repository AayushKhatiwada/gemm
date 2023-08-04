#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include<assert.h>
#include<math.h>


#define N 1024

//float _align(64) A[N][N];
float  A[N][N];
float  B[N][N];
float  C[N][N];
float val[N][N];

uint64_t nanos(){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    return (uint64_t)start.tv_sec*1000000000 + (uint64_t)start.tv_nsec;
}

#define BLOCK 32

int main() {
    assert (N%BLOCK == 0 ); 
    //test
    //for (int k=0; k<N*N; k++) A[k] = rand();
    //for (int k=0; k<N*N; k++) B[k] = rand();

    // uint64_t start =nanos();
 /*   for (int y = 0; y<N; y++){
        for (int x = 0; x<N; x++){
            float acc = 0;  
            for (int k= 0; k<N ; k++){
                acc += A[y][k]*B[k][x]; //transpose it for faster results
                //acc += A[k][y]*B[x][k]; // transposing does not make it faster
            }
            C[y][x] = acc;
        }
    }
*/
    uint64_t start =nanos();
    for (int by= 0 ; by<N ; by +=BLOCK ){
        for(int bx = 0; bx<N; bx+= BLOCK ){

            //compute
            float tc[BLOCK][BLOCK];
            for (int y  = 0; y<BLOCK; y++){
                for (int x= 0;  x<N ; x++){
                    float acc = 0; 
                    for(int k= 0 ;  k<N ; k++){
                        acc += A[by+y][k]*B[k][bx+x];
                        //acc += A[by+y][k]*B[bx+x][k]; assuming the matrices are pretransposed
                
                    }
                    tc[y][x]=acc ; 

                }
            // store
            for (int y= 0 ;  y< BLOCK ; y++){
                for (int x= 0 ; x<BLOCK; x++ ){
                    C[by+y][bx+x] = tc[y][x];

                }
            }



            }
        }
    }

    uint64_t end = nanos();
    double gflop = (2.0*N*N*N)*1e-9;
    double s = (end-start)*1e-9;
    printf("%f GFLOPS\n", gflop/s);

    for (int y= 0; y<N ; y++){
        for (int x = 0 ; x<N ; x++) {
            if (C[y][x] != val[y][x]) {
                printf("MISMATCH AT %dx%d , %f != %f \n ", y , x , C[y][x], val[y][x]);
                return -1; 
            
            }
        }
    }



    return 0; 
    // create a new github repository test

    
}


