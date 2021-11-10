#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

 int main(int argc, char* argv[]){
 FILE *in, *out;
 int order;
 int x, y;
 Graph G;
 List L = newList();
    if(argc != 3){
       printf("Usage: %s <input file> <output file>\n",argv[0]);
       exit(1);
    }
 in = fopen(argv[1],"r");
 out = fopen(argv[2],"w");
      
    if(in == NULL){
       printf("Unable to open file %s for reading\n",argv[1]);
       exit(1);
    }
    if(out == NULL){
       printf("Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }
 fscanf(in, "%d", &order);
 G = newGraph(order);
    while((fscanf(in, "%d %d", &x, &y) != EOF) && (x != 0 && y != 0)) {
             addEdge(G, x, y);          
    }

 printGraph(out, G); 
    while(fscanf(in, "%d %d ", &x, &y) != EOF){
       if(x != 0 && y != 0){ 
           BFS(G,x);
           getPath(L,G,y);
             if(back(L) == NIL){
                fprintf(out,"The distance from %d to %d is %s\n",x,y,"infinity");
                fprintf(out,"No %d-%d path exists\n",x,y);
             } 
             else{
                fprintf(out,"The distance from %d to %d is %d\n",x,y,getDist(G,y));
                fprintf(out,"A shortest %d-%d path is: ",x,y);
                printList(out,L); 
                fprintf(out,"\n");
             }
       clear(L);
       }
    }
 freeGraph(&G); 
 freeList(&L); 
 fclose(in);
 fclose(out);
 }
