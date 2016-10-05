//
//  main.cpp
//  assignment
//
//  Created by 종원 이 on 12. 11. 2..
//  Copyright (c) 2012년 jwonlee206@naver.com. All rights reserved.
//

#include <stdio.h>
int m[101][101];
int p[102];
int s[100][100];
void minofmulti(int i, int j){
    int k;
    int q;
    k = i;
    q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
    for(k=i;k<j;k++){
        if(q>=m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]){
            q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
            s[i][j]=k;
        }
    }m[i][j] = q; 
}
void printOptimalMulti(int i, int j){
    int k;
    k = s[i][j];
    
    if(i==j){
        printf("%d ",i);
    }else{
        printf("( ");
        printOptimalMulti(i, k);
        printOptimalMulti(k+1, j);
        printf(") ");
    }
}
int main(int argc, const char * argv[])
{
    int N;
    int i, j;
    scanf("%d",&N);
    for(int i=0;i<=N;i++){
        scanf("%d",&p[i]);
    }
    for(i=1;i<=N;i++){
        for(j=1;j<=N-i;j++){
            minofmulti(j, j+i);
        }
    }printf("%d\n",m[1][N]);
    /*for(i=1;i<=N;i++){
        for(j=i+1;j<=N;j++){
            printf("%d ",s[i][j]); 
        }printf("\n");
    }*/
    printOptimalMulti(1, N);
    printf("\n");
    return 0;
}

