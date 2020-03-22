#include<stdio.h>
#include<stdlib.h>
#include "graph.h"

int main(void){
    Graph *g = create_graph(4);
    insert_edge(g,1,2,1);
    insert_edge(g,1,3,1);
    insert_edge(g,1,0,1);
    insert_edge(g,2,3,1);
    insert_edge(g,1,0,1);
    insert_edge(g,3,2,1);
    insert_edge(g,2,0,1);
    printf("%d\n",is_there_edge(g,1,2));
    printf("%d\n",is_there_edge(g,0,2));
    printf("%d\n",weight_of_edge(g,2,3));
    printf("%d\n",is_there_edge(g,3,0));
    remove_edge(g,1,2);
    printf("%d\n",is_there_edge(g,1,2));
    erase_graph(&g);
}