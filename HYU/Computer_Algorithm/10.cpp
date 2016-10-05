//
//  main.cpp
//  algorithm9
//
//  Created by 종원 이 on 12. 12. 6..
//  Copyright (c) 2012년 jwonlee206@naver.com. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define WHITE 1
#define GRAY 2
#define BLACK 3
//구조체
typedef struct V{
    int color;
    int d;
    int f;
    int pi;
    int component;
}Vertex;
typedef struct adjacency{
    struct adjacency *p;
    int v;
    int edgetype;
}adj_s;
//전역변수
Vertex V[1001];
struct adjacency *adjlist[1001]={NULL,};
int count;
unsigned int time;
//함수
void DFS(int length);
void DFS_VISIT(int u, int length);
void addEdge(int u, int v){
    adj_s* newEdge;
    adj_s* tmp;
    tmp = adjlist[u];
    newEdge = (adj_s*)malloc(sizeof(adj_s));
    newEdge->v = v;
    newEdge->p = NULL;
    if(adjlist[u]==NULL)
        adjlist[u] = newEdge;
    else{
        while(tmp->p!=NULL){
            tmp = tmp->p;
        }
        tmp->p = newEdge;
    }
}
//메인함수
int main(int argc, const char * argv[])
{
    int vertex;
    int i,j;
    //adj_s* tmp;
    //for(int i=0;i<=1000;i++) adjlist[i]=NULL;
    
    scanf("%d",&vertex);
    while(scanf("%d %d",&i,&j)!=EOF){
        addEdge(i, j);
        addEdge(j, i);
    }
    DFS(vertex);
    printf("%d\n",count);
    for(int x=1;x<=vertex;x++){
        printf("%d\n",V[x].component);
    }
    
    
    return 0;
}

void DFS(int length){
    count = 0;
    for(int i=1;i<=length;i++){
        V[i].color = WHITE;
        V[i].pi = NULL;
    }
    time = 0;
    for(int i=1;i<=length;i++){
        if(V[i].color==WHITE){ 
            count++;
            DFS_VISIT(i, length);
        }
    }
}
void DFS_VISIT(int u, int length){
    adj_s* tmp;
    tmp = adjlist[u];
    V[u].color = GRAY;
    time = time+1;
    V[u].d = time;
    V[u].component = count;
    while(tmp!=NULL){
        int v;
        v = tmp->v;
        if(V[v].color==GRAY) tmp->edgetype = 2;
        else if(V[v].color==BLACK){
            if(V[u].d<V[v].d) tmp->edgetype = 3;
            else if(V[u].d>V[v].d) tmp->edgetype =4;
        }else if(V[v].color==WHITE){
            tmp->edgetype = 1;
            V[v].pi = u;
            DFS_VISIT(v, length);
        }
        tmp = tmp->p;
    }
    V[u].color = BLACK;
    V[u].f = time = time+1;
}

