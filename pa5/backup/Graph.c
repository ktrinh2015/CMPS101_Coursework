// -----------------------------------------------------------------------
// Kevin Trinh
// Summer CMPS 101 2019
// kevatrin
// Graph.c
// Contains Graph ADT manipulation routines
// -----------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

 typedef struct GraphObj{
    int order;
    int size;
    List* vertex; 
    int* color;
    int* parent;
    int* discover;
    int* finish;
 }GraphObj;
 typedef GraphObj* Graph;

 Graph newGraph(int n){
 Graph G = malloc(sizeof(GraphObj)); 
 G->vertex = malloc(sizeof(List)*(n+1));
 G->color = malloc(sizeof(int)*(n+1));
 G->parent = malloc(sizeof(int)*(n+1));
 G->discover = malloc(sizeof(int)*(n+1));
 G->finish = malloc(sizeof(int)*(n+1));

    for (int i = 1; i < n+1; i++){
       G->vertex[i] = newList();
       G->discover[i] = UNDEF;
       G->finish[i] = UNDEF;
    }
 G->order = n;
 G->size = 0;
 return G; 
 }

 void freeGraph(Graph *pG){
    for(int i = 1; i < getOrder(*pG)+1; i++){
       freeList(&((*pG)->vertex[i]));
    }
 free((*pG)->vertex);
 free((*pG)->color);
 free((*pG)->parent);
 free((*pG)->discover);
 free((*pG)->finish);
 free(*pG);
 pG = NULL;
 }

 /*** Access functions ***/
 int getOrder(Graph G){
 return G->order;
 }

 int getSize(Graph G){
 return G->size;
 }
 
 // Pre: 1<=u<=getOrder(G)
 int getParent(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
       fprintf(stderr,"Graph Error: Cannot access parent off List\n");
       exit(1);
    }
    if(G->parent[u] == NIL) {
       return NIL;
    }
 return G->parent[u];
 }

 //Pre: 1<=u<=getOrder(G)
 int getDiscover(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
       fprintf(stderr,"Graph Error: Cannot call getDiscover() on vertex off Graph\n");
       exit(1);
    }
 return G->discover[u];
 }
 
 //Pre: 1<=u<=getOrder(G)
 int getFinish(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
       fprintf(stderr,"Graph Error: Cannot call getFinish() on vertex off Graph\n");
       exit(1);
    }
 return G->finish[u];
 }

 // Pre: 1<=u<=getOrder(G); 1<=v<=getOrder(G)
 void addEdge(Graph G, int u, int v){
    if(u < 1 || u > getOrder(G)){
       fprintf(stderr,"Graph Error: Can only add edge at valid vertex address\n");
       exit(1);
    }
    if(v < 1 || v > getOrder(G)){
       fprintf(stderr,"Graph Error: Can only add arc between valid vertex addresses\n");
       exit(1);
    }
 addArc(G,u,v);
 addArc(G,v,u);
 G->size--;
 return;
 }
 
 // Pre: 1<=u<=getOrder(G); 1<=v<=getOrder(G)
 void addArc(Graph G, int u, int v){
    if(u < 1 || u > getOrder(G)){
       fprintf(stderr,"Graph Error: Can only add arc at valid vertex address\n");
       exit(1);
    }
    if(v < 1 || v > getOrder(G)){
       fprintf(stderr,"Graph Error: Can only add arc between valid vertex addresses\n");
       exit(1);
    }
    if(length(G->vertex[u]) == 0){
       append(G->vertex[u],v);
       G->size++;
       return;
    }
    
    moveFront(G->vertex[u]);
       if(length(G->vertex[u]) != 0){
          while(index(G->vertex[u]) != -1){
             if(v > get(G->vertex[u])){
                moveNext(G->vertex[u]);
             }
             else{
                insertBefore(G->vertex[u],v);
                break;
             }
          } 
       }
    
    if(index(G->vertex[u]) == -1){
       append(G->vertex[u],v);
    }
 G->size++;
 return;
 }

 void DFS(Graph G, List S){
 int temp;
    if(length(S) != getOrder(G)){
       fprintf(stderr,"Graph Error: DFS must be called with List and Graph of equal size\n");
       exit(1);
    }
    for(int i = 1; i < getOrder(G)+1; i++){
       G->color[i] = white;
       G->parent[i] = NIL;
    }
 List L = newList();
 int time = 0;
 
 moveFront(S);
    while(index(S) != -1){
       temp = get(S);
          if(G->color[temp] == white){
             visit(temp, &time, &G, &L);
          }
    moveNext(S);
    }
 
 clear(S);
 moveFront(L);
    while(index(L) != -1){
       append(S, get(L));
       moveNext(L);
    }
 freeList(&L);  
 } 

 void visit(int u, int *time, Graph *G, List *L){
 int temp;
 (*G)->color[u] = gray;
 (*G)->discover[u] = ++(*time);
    if(length((*G)->vertex[u]) != 0){
       moveFront((*G)->vertex[u]);
          for(moveFront((*G)->vertex[u]); index((*G)->vertex[u]) != -1; moveNext((*G)->vertex[u])){
             temp = get((*G)->vertex[u]);
                if((*G)->color[temp] == white){
                   (*G)->parent[temp] = u;
                   visit(temp, time, G, L);
                }  
             
          }
    }
 (*G)->color[u] = black;
 (*G)->finish[u] = ++(*time);
 prepend(*L,u);  
 }

 Graph transpose(Graph G){
 int temp;
 Graph tran = newGraph(getOrder(G));
    for(int i = 1; i < getOrder(G)+1; i++){
       if(length(G->vertex[i]) != 0){
          moveFront(G->vertex[i]);
             while(index(G->vertex[i]) != -1){
                temp = get(G->vertex[i]);
                addArc(tran, temp, i);
                moveNext(G->vertex[i]);
             } 
       }
    }
 return tran;
 }

 Graph copyGraph(Graph G){
 Graph copy = newGraph(getOrder(G));
 int temp = 0;
    for(int i = 1; i < getOrder(G)+1; i++){
       if(length(G->vertex[i]) != 0){
          moveFront(G->vertex[i]);
             while(index(G->vertex[i]) != -1){
                temp = get(G->vertex[i]);
                addArc(copy, i,temp);
                moveNext(G->vertex[i]); 
             }
       }
    }
 return copy;
 }

 void printGraph(FILE *out, Graph G){
    if(out == NULL){
       fprintf(stderr,"Graph Error: Cannot pass NULL value for output file\n");
       exit(1);
    }
    if(G == NULL){
       fprintf(stderr,"Graph Error: Cannot pass NULL Graph to printGraph\n");
       exit(1);
    }
    for(int i = 1; i < getOrder(G)+1; i++){
       fprintf(out,"%d: ", i);
       printList(out, G->vertex[i]);
    }
    fprintf(out,"\n");
 }

