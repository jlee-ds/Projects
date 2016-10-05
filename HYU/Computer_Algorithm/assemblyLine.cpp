//
//  assemblyLine.cpp
//  sample
//
//  Created by 종원 이 on 12. 11. 2..
//  Copyright (c) 2012년 jwonlee206@naver.com. All rights reserved.
//

#include <stdio.h>

int Min(int a, int b){
    if(a>b) return b;
    else return a;
}
int Fromwhere(int a, int b){
    if(a>b) return 2;
    else return 1;
}
void printAll(int a[], int b[], int Lop, int N){
    if(N>1){ 
        if(Lop==1){
            printAll(a, b, a[N-2], N-1);
            printf("%d %d\n", a[N-2], N-1);
        }else if(Lop==2){
            printAll(a, b, b[N-2], N-1);
            printf("%d %d\n", b[N-2], N-1);
        }
    }
}

int main(int argc, char* argv[]){
    int N;
    int e1,e2,x1,x2;
    int i=0;
    int Foptimal;
    int Loptimal;
    int A1[100];
    int A2[100];
    int T1[99];
    int T2[99];
    int L1[99];
    int L2[99];
    int F1[100];
    int F2[100];
    scanf("%d",&N);
    scanf("%d %d",&e1,&e2);
    scanf("%d %d",&x1,&x2);
    for(i=0;i<N;i++){
        scanf("%d",&A1[i]);
    }for(i=0;i<N;i++){
        scanf("%d",&A2[i]);
    }for(i=0;i<N-1;i++){
        scanf("%d",&T1[i]);
    }for(i=0;i<N-1;i++){
        scanf("%d",&T2[i]);
    }
    F1[0] = e1 + A1[0];
    F2[0] = e2 + A2[0];
    for(i=1;i<N;i++){
        F1[i]=Min(F1[i-1]+A1[i],F2[i-1]+T2[i-1]+A1[i]);
        F2[i]=Min(F1[i-1]+T1[i-1]+A2[i],F2[i-1]+A2[i]);
        L1[i-1]=Fromwhere(F1[i-1]+A1[i],F2[i-1]+T2[i-1]+A1[i]);
        L2[i-1]=Fromwhere(F1[i-1]+T1[i-1]+A2[i],F2[i-1]+A2[i]);
    }
    Foptimal=Min(F1[N-1]+x1,F2[N-1]+x2);
    Loptimal=Fromwhere(F1[N-1]+x1,F2[N-1]+x2);
    printf("%d\n",Foptimal);
    printAll(L1,L2,Loptimal,N);
    if(Loptimal==1) printf("1 %d\n",N);
    else if(Loptimal==2) printf("2 %d\n",N);
    
    return 0;
}
