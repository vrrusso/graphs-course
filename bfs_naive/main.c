#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "queue.h"
#include "list.h"

void myfunc(void * integer){
    printf("%d",*((int *)integer));
}

int main(void){
    int n;//number of vertex
    int m;//number of edges
    int aux_edge1,aux_edge2,no_operations,op;    
    Graph * g;
    scanf("%d %d",&n,&m);
    g = create_graph(n);
    for(int i=0;i<m;i++){
        scanf("%d %d",&aux_edge1,&aux_edge2);
        insert_directed_edge(g,aux_edge1,aux_edge2);
    }
    print_graph(g);
    bfs(g);
    dfs(g);
    int cicle = 0;
    List * l = topological_sort(g,&cicle);
    if(!cicle)
        list_print(l,myfunc);
    else
        printf("tem um ciclo :(");
    
    erase_list(&l);
    erase_graph(&g);


    return 0;
}