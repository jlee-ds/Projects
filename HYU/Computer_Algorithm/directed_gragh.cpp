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
struct adjacency *adjlist[1001];
int count;
bool is_dag;
unsigned int time;
int asdf[1001];
int temp_v;
int** ADJ;
//함수
void DFS(int length);
void DFS_VISIT(int u, int vertex);
/*void addEdge(int u, int v){
    adj_s* newEdge;
    adj_s* tmp1;
    adj_s* tmp2;
    tmp1 = adjlist[u];
    newEdge = (adj_s*)malloc(sizeof(adj_s));
    newEdge->v = v;
    newEdge->p = NULL;
    if(tmp1==NULL)
        tmp1 = newEdge;
    else{
        while(tmp1!=NULL){
            if(tmp1->v > v){
                newEdge->p = tmp1;
                tmp1 = newEdge;
                break;
            }
            tmp2 = tmp1;
            tmp1 = tmp1->p;
        }
        if(tmp1==NULL)tmp2->p = newEdge;
    }
}*/
void AddEdge(int u, int v, int vertex){
    for(int i=1;i<=vertex;i++){
        for(int j=1;j<=vertex;j++){
            ADJ[u][v]=1;
        }
    }
}
//메인함수
int main(int argc, const char * argv[])
{
    int vertex;
    int i,j;
    //adj_s* tmp;
    //for(int i=0;i<=1000;i++) *adjlist[i]=NULL;
    
    scanf("%d",&vertex);
    temp_v=vertex;
    ADJ = (int**)malloc(sizeof(int*)*(vertex+1));
    for(i=0;i<vertex+1;i++){
        ADJ[i] = (int*)malloc(sizeof(int)*(vertex+1));
        for(j=0;j<vertex+1;j++){
            ADJ[i][j]=0;
        }
        
    }
    while(scanf("%d %d",&i,&j)!=EOF){
       //if(i!=-1&&j!=-1)
           AddEdge(i, j, vertex);
       //else break;
    }
    DFS(vertex);
    printf("%d\n",is_dag);
    if(is_dag==1)for(int i=1;i<vertex+1;i++) printf("%d ",asdf[i]);
   //if(is_dag==1){
    /*int tmp[vertex];
        for(int x=1;x<=vertex;x++){
            tmp[x]=V[x].f;
        }
        for(int i=1;i<=vertex;i++){
            for(int j=i+1;j<=vertex;j++){
                int temp;
                if(tmp[i]<tmp[j]){ temp=tmp[j]; tmp[j]=tmp[i]; tmp[i]=temp; }
            }
        }
        for(int x=1;x<=vertex;x++){
            for(int y=1;y<=vertex;y++){
                if(tmp[x]==V[y].f) printf("%d ",y);
            }
                   }*/
    //}
    
    return 0;
}

void DFS(int length){
    count = 0;
    is_dag = 1;
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
void DFS_VISIT(int u, int vertex){
    adj_s* tmp;
    
    tmp = adjlist[u];
    V[u].color = GRAY;
    time = time+1;
    V[u].d = time;
    V[u].component = count;
        for(int v=0;v<vertex+1;v++){
            if(ADJ[u][v]==1){
                if(V[v].color==GRAY){ 
                    //tmp->edgetype = 2;
                    is_dag=0;
                }
                //else if(V[v].color==BLACK){
                   // if(V[u].d<V[v].d) tmp->edgetype = 3;
                   // else if(V[u].d>V[v].d) tmp->edgetype =4;
                //}
                else if(V[v].color==WHITE){
                    //tmp->edgetype = 1;
                    V[v].pi = u;
                    DFS_VISIT(v, vertex);
                }
            }
        }
   /* while(tmp!=NULL){
        int v;
        v = tmp->v;
        if(V[v].color==GRAY){ 
            tmp->edgetype = 2;
            is_dag=0;
        }
        else if(V[v].color==BLACK){
            if(V[u].d<V[v].d) tmp->edgetype = 3;
            else if(V[u].d>V[v].d) tmp->edgetype =4;
        }else if(V[v].color==WHITE){
            tmp->edgetype = 1;
            V[v].pi = u;
            DFS_VISIT(v);
        }
        tmp = tmp->p;
    }*/
    V[u].color = BLACK;
    V[u].f = time = time+1;
    asdf[temp_v]=u;
    temp_v--;
}

