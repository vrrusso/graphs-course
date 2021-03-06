#include<stdio.h>
#include<stdlib.h>
#include "graph.h"

int main(void){
    int n;//number of vertex
    int m;//number of edges
    int aux_edge1,aux_edge2,no_operations,op;    
    Graph * g;
    scanf("%d %d",&n,&m);
    g = create_graph(n);
    for(int i=0;i<m;i++){
        scanf("%d %d",&aux_edge1,&aux_edge2);
        insert_edge(g,aux_edge1,aux_edge2);
    }
    scanf("%d",&no_operations);
    while(no_operations--){
        //print_graph(g);
        scanf("%d",&op);
        switch(op){
            case 1:
                scanf("%d %d",&aux_edge1,&aux_edge2);
                insert_edge(g,aux_edge1,aux_edge2);
                break;
            case 2:
                scanf("%d %d",&aux_edge1,&aux_edge2);
                remove_edge(g,aux_edge1,aux_edge2);
                break;
            case 3:
                print_graph(g);
        }
    }
    erase_graph(&g);
    /*Graph * g = create_graph(7);
    insert_directed_edge(g,2,5);
    erase_graph(&g);*/
    return 0;
}