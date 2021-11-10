// -----------------------------------------------------------------------------
// Kevin Trinh
// Summer CMPS 101 2019
// kevatrin
// FindComponents.c
// Contains client for DFS operations
// -----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

 int main(int argc, char* argv[]){
 Graph G;
 Graph temp;
 FILE *in, *out;
 int order, x, y, k, compNum;
 List stack;
 List comp;
 
    if(argc != 3){
       fprintf(stderr,"Usage: %s <infile> <outfile>\n", argv[0]);
       exit(1);
    }
 in = fopen(argv[1],"r");
 out = fopen(argv[2],"w");

    if(in == NULL){
       fprintf(stderr,"Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }
    if(out == NULL){
       fprintf(stderr,"Unable to open file %s for writing\n",argv[2]);
       exit(1);
    }
 fscanf(in, "%d", &order);
 G = newGraph(order);
    while(fscanf(in,"%d %d ", &x, &y) != EOF){
       if(x != 0 && y != 0){
         addArc(G,x,y);    
       }
    }
 fprintf(out,"Adjacency list representation of G:\n");
 printGraph(out,G);

 stack = newList();
    for(int i = 1; i < order+1; i++){
       append(stack,i);
    }

 DFS(G, stack);
 temp = transpose(G); 
 DFS(temp, stack);
 moveFront(stack);
    while(index(stack)!= -1){
       if(getParent(temp, get(stack)) == NIL){
          k++;
       }
    moveNext(stack);
    }
 fprintf(out,"G contains %d strongly connected components: \n",k);

 comp = newList();
 moveBack(stack);
 compNum = 1;
    while(index(stack) != -1){
       if(getParent(temp, get(stack)) != NIL){
          prepend(comp, get(stack));
       }
       else{
          prepend(comp, get(stack));
          fprintf(out,"Component %d: ",compNum);
          printList(out,comp);
          compNum++;
          clear(comp);
       }
    movePrev(stack);
    }

 freeGraph(&G);
 freeGraph(&temp);
 freeList(&stack);
 freeList(&comp);

 fclose(in);
 fclose(out);
 return 0;

 }

















