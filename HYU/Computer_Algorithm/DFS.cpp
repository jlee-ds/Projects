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
}Vertex;
typedef struct adjacency{
    struct adjacency *p;
    int v;
    int edgetype;
}adj_s;
//전역변수
Vertex V[1000];
struct adjacency *adjlist[1000]={NULL,};
int adj[1000][1000];
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
    adj_s* tmp;
    //for(int i=0;i<=1000;i++) adjlist[i]=NULL;
    
    scanf("%d",&vertex);
    while(scanf("%d %d",&i,&j)!=EOF){
            addEdge(i, j);
    }
    DFS(vertex);
    for(int x=1;x<=vertex;x++){
        tmp = adjlist[x];
        while(tmp!=NULL){
            printf("%d %d %d\n",x,tmp->v,tmp->edgetype);
            tmp = tmp->p;
        }
    }
 
    
    return 0;
}

void DFS(int length){
    for(int i=1;i<=length;i++){
        V[i].color = WHITE;
        V[i].pi = NULL;
    }
    time = 0;
    for(int i=1;i<=length;i++){
        if(V[i].color==WHITE) DFS_VISIT(i, length);
    }
}
void DFS_VISIT(int u, int length){
    adj_s* tmp;
    tmp = adjlist[u];
    V[u].color = GRAY;
    time = time+1;
    V[u].d = time;
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

