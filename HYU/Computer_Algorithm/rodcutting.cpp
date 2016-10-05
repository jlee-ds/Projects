//
//  rodcutting.cpp
//  sample
//
//  Created by 종원 이 on 12. 11. 2..
//  Copyright (c) 2012년 jwonlee206@naver.com. All rights reserved.
//

#include <stdio.h>
void CUT_ROD_PRINT(int p[],int N){
    int r[101]={0,};
    int s[101];
    int i,j;
    int n;
    int q = -1;
    n = N;
    for(i=1;i<=N;i++){
        for(j=1;j<=i;j++){
            if(q<p[j]+r[i-j]){
                q=p[j]+r[i-j];
                s[i]=j;
            }
        }r[i]=q;
    }printf("%d\n",r[N]);
    while(n>0){
        printf("%d ",s[n]);
        n = n - s[n];
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    int N;
    int p[100];
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        scanf("%d",&p[i]);
    }
    CUT_ROD_PRINT(p,N);
    return 0;
}
