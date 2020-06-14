#include "list.h"
#include "graph.h"
#include "queue.h"
#include <string.h>
#include <stdio.h>

struct graph_{
    List ** lists_of_edges;
    int no_edges;
    int no_vertex;
};

//<!this 2 functions are meant to be passed to the generic list ADT
bool equal_integers(void * a,void * b){
    return *((int *) a)==*((int *)b)?true:false;
}

void print_int(void * integer){
    printf("%d",*((int *)integer));
}


Graph * create_graph(int number_of_vertex){
    Graph * g = (Graph *)allocate(sizeof(Graph));
    g->no_vertex=number_of_vertex;
    g->no_edges=0;
    g->lists_of_edges = (List **)allocate(sizeof(List *)*number_of_vertex);
    for(int i=0;i<number_of_vertex;i++){
        g->lists_of_edges[i] = create_list(sizeof(int));
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

int insert_directed_edge(Graph *g,int origin_vertex,int destiny_vertex){
        if(g == NULL ||origin_vertex<0||origin_vertex>=g->no_vertex||origin_vertex<0||origin_vertex>=g->no_vertex || list_search(g->lists_of_edges[origin_vertex],&(destiny_vertex),equal_integers)){
            return ERROR;
        }
        list_push_back(g->lists_of_edges[origin_vertex], &(destiny_vertex));
        return 1;
}

int insert_edge(Graph *g,int vertex_a,int vertex_b){
    if(insert_directed_edge(g,vertex_a,vertex_b)!= ERROR)
        return insert_directed_edge(g,vertex_b,vertex_a);
    return ERROR;
}



void print_graph(Graph *g){
    if(g!=NULL){
        for(int i=0;i<g->no_vertex;i++){
            printf("%d: ",i);
            list_print(g->lists_of_edges[i],print_int);
        }
    }
    printf("\n");
}



bool is_there_edge(Graph *g,int origin_vertex,int destiny_vertex){
    if(g == NULL ||origin_vertex<0||origin_vertex>=g->no_vertex||origin_vertex<0||origin_vertex>=g->no_vertex){
            return ERROR;
    }
    return list_search(g->lists_of_edges[origin_vertex],&(destiny_vertex),equal_integers);
}

int remove_directed_edge(Graph * g,int origin_vertex,int destiny_vertex){
    if(g == NULL ||origin_vertex<0||origin_vertex>=g->no_vertex||origin_vertex<0||origin_vertex>=g->no_vertex)
            return ERROR;
    //<!-- in the case where theres no item to be removed the list returns a NULL, so we must filter that
    void * op = list_remove(g->lists_of_edges[origin_vertex],&(destiny_vertex),equal_integers);
    return op == NULL?ERROR:*((int *) op);
}

int remove_edge(Graph *g, int vertex_a,int vertex_b){
    if(remove_directed_edge(g,vertex_a,vertex_b)!= ERROR)
        return remove_directed_edge(g,vertex_b,vertex_a);
    return ERROR;
}

void bfs(Graph * g){
    Queue * q = create_queue();
    int * dist = (int *)malloc(sizeof(int)*g->no_vertex);
    for(int i=0;i<g->no_vertex;i++){
        dist[i] = -1;
    }
    char * color = (char *)malloc(sizeof(char)*g->no_vertex);
    memset(color,'b',g->no_vertex);
    enqueue(q,0);
    color[0]='c';
    dist[0] = 0;
    while(!empty_queue(q)){

        int v = dequeue(q);
        color[v] = 'p';
        int * vector = vectorize(g->lists_of_edges[v]);
        for(int i=0;i<list_size(g->lists_of_edges[v]);i++){
            if(color[vector[i]]=='b'){
                enqueue(q,vector[i]);
                color[vector[i]] = 'c';
                dist[vector[i]] = dist[v]+1;
                printf("Vertice 0->%d  distancia:%d\n",vector[i],dist[vector[i]]);
            }
        }
        free(vector);
    }
    free(color);
    free(dist);
    erase_queue(&q);
}

void dfs_visit(Graph * g, char * visited, int starting_vertex){
    int * adj = vectorize(g->lists_of_edges[starting_vertex]);
    visited[starting_vertex] = '1';
    printf("%d->",starting_vertex);
    for(int i = 0;i<list_size(g->lists_of_edges[starting_vertex]);i++){
        if(visited[adj[i]]=='0'){
            dfs_visit(g,visited,adj[i]);
        }
    }
    free(adj);
    visited[starting_vertex] = '2';
}


void dfs(Graph * g){
    char * visited = (char *)malloc(sizeof(char)*g->no_vertex);
    memset(visited,'0',g->no_vertex);

    for(int i=0;i<g->no_vertex;i++){
        if(visited[i] == '0'){
            dfs_visit(g, visited,i);
            printf("\n");
        }
    }


    free(visited);
}

void topological_visit(Graph * g, char * visited, int starting_vertex, List * list,int* cicle_check){
    int * adj = vectorize(g->lists_of_edges[starting_vertex]);
    visited[starting_vertex] = '1';
    for(int i = 0;i<list_size(g->lists_of_edges[starting_vertex]);i++){
        if(visited[adj[i]]=='0'){
            topological_visit(g,visited,adj[i],list,cicle_check);
        }
        if(visited[adj[i]]=='1'){
            (*cicle_check) = 1;
        }
    }
    free(adj);
    visited[starting_vertex] = '2';
    list_push_front(list, (void *)&starting_vertex);
}


List *  topological_sort(Graph * g,int* cicle_check){
    char * visited = (char *)malloc(sizeof(char)*g->no_vertex);
    memset(visited,'0',g->no_vertex);
    List * topological_order = create_list(sizeof(int));


    for(int i=0;i<g->no_vertex;i++){
        if(visited[i] == '0'){
            topological_visit(g, visited,i,topological_order,cicle_check);
        }
    }
    free(visited);
    return topological_order;
}
