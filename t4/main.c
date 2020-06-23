#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "list.h"


int main(void){
    Graph * g;
    int number_vertex,number_edges, ori_vertex,dest_vertex,time,price,source,destiny;
    scanf("%d %d", &number_vertex,&number_edges);
    g = create_graph(number_vertex);
    for(int i=0;i<number_edges;i++){
        scanf("%d %d %d %d",&ori_vertex,&dest_vertex,&time,&price);
        insert_directed_edge(g,ori_vertex,dest_vertex,time,price);
    }
    //print_graph(g);
    scanf("%d %d",&source,&destiny);
    
    minimum_path(g,source,destiny);
    erase_graph(&g);
    return 0;
}