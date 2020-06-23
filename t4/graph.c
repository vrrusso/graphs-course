#include "list.h"
#include "graph.h"
#include <string.h>
#include <stdio.h>
#define INF 1000000

//descobrir depois como representar infinito


struct graph_{
    List ** lists_of_edges;
    int no_edges;
    int no_vertex;
};



//<!this 2 functions are meant to be passed to the generic list ADT
bool equal_destinations(void * a,void * b){
    return ((Route *) a)->destination==((Route *)b)->destination ?true:false;
}

void print_route(void * route){
    Route a = *((Route *)route);
    printf("(%d,%d,%d)",a.destination,a.time,a.price);
}

void print_list(void* integer){
    printf("%d",*((int *)integer));
}


Graph * create_graph(int number_of_vertex){
    Graph * g = (Graph *)allocate(sizeof(Graph));
    g->no_vertex=number_of_vertex;
    g->no_edges=0;
    g->lists_of_edges = (List **)allocate(sizeof(List *)*number_of_vertex);
    for(int i=0;i<number_of_vertex;i++){
        g->lists_of_edges[i] = create_list(sizeof(Route));
    }
    return g;
}

void erase_graph(Graph ** g){
    if( (*g) != NULL){
        for(int i=0;i<(*g)->no_vertex;i++)
            erase_list(&((*g)->lists_of_edges[i]));
        free((*g)->lists_of_edges);
        free((*g));
        g = NULL;
    }
}

int insert_directed_edge(Graph * g,int origin_vertex,int destiny_vertex,int time,int price){
        Route aux;
        aux.destination = destiny_vertex;aux.price=price;aux.time=time;
        if(g == NULL ||origin_vertex<0||origin_vertex>=g->no_vertex||destiny_vertex<0||destiny_vertex>=g->no_vertex || list_search(g->lists_of_edges[origin_vertex],&(aux),equal_destinations)){
            return ERROR;
        }
        list_push_back(g->lists_of_edges[origin_vertex], &(aux));
        return 1;
}

int insert_edge(Graph * g, int vertex_a, int vertex_b,int time,int price){
    if(insert_directed_edge(g,vertex_a,vertex_b,time,price)!= ERROR)
        return insert_directed_edge(g,vertex_b,vertex_a,time,price);
    return ERROR;
}



void print_graph(Graph *g){
    if(g!=NULL){
        for(int i=0;i<g->no_vertex;i++){
            printf("%d: ",i);
            list_print(g->lists_of_edges[i],print_route);
        }
    }
    printf("\n");
}

//working and
void relaxing(Graph *g, int u,int v,int weigth,int * distances,int * parents,int price,int* prices){
    if(g!=NULL && distances[v]>distances[u]+weigth){
        distances[v] = distances[u]+weigth;
        prices[v] = prices[u]+price;
        parents[v] = u;
    }
}


//algoritmo de dijkstra sem priority queue O(v²) :(
void minimum_path(Graph * g, int source,int destiny){
    int * parents = (int *)malloc(sizeof(int)*g->no_vertex);
    int * distances_from_source = (int *)malloc(sizeof(int)*g->no_vertex);
    int * prices = (int *)malloc(sizeof(int)*g->no_vertex);
    int * visited = (int *)malloc(sizeof(int)*g->no_vertex);
    int index_min = 0;
    int min = INF;
    int n = g->no_vertex;
    for(int i=0;i<g->no_vertex;i++){
        parents[i] = -1;
        distances_from_source[i] = INF;
        visited[i]=0;
        prices[i]=0;
    }

    //marcar o vertice fonte
    distances_from_source[source] = 0;
    visited[source] = 1;n--;
    //relaxing the adj
    Route * adj = vectorize(g->lists_of_edges[source]);
    for(int i=0;i<list_size(g->lists_of_edges[source]);i++){
        relaxing(g,source,adj[i].destination,adj[i].time,distances_from_source,parents,adj[i].price,prices);
    }
    free(adj);
    for(int i=0;i<g->no_vertex;i++){
        if(visited[i]!=1 && distances_from_source[i]<min){
            min = distances_from_source[i];
            index_min = i;
        }
    }

    //fazer a mesma coisa para todos os outros vértices
    while(n){
        visited[index_min] = 1;n--;
        //relaxing
        Route * adj = vectorize(g->lists_of_edges[index_min]);
        for(int i=0;i<list_size(g->lists_of_edges[index_min]);i++){
            relaxing(g,index_min,adj[i].destination,adj[i].time,distances_from_source,parents,adj[i].price,prices);
        }
        free(adj);
        index_min = 0;
        min = INF;
        for(int i=0;i<g->no_vertex;i++){
            if(visited[i]!=1 && distances_from_source[i]<min){
                min = distances_from_source[i];
                index_min = i;
            }
        }
    }
    List * path = create_list(sizeof(int));
    int v = destiny;
    while(v != -1){
        list_push_front(path,(void*)&v);
        v = parents[v];
    }
    list_print(path,print_list);
    printf("%d %d\n",distances_from_source[destiny],prices[destiny]);



    erase_list(&path);
    free(parents);
    free(distances_from_source);
    free(visited);
}