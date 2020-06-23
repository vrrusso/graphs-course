#include "list.h"
#include "graph.h"
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

//this is a recursive function tha makes the dfs while generating the topological list
void topological_visit(Graph * g, char * visited, int starting_vertex, List * list,int* cycle_check){
    int * adj = vectorize(g->lists_of_edges[starting_vertex]);
    visited[starting_vertex] = '1';
    for(int i = 0;i<list_size(g->lists_of_edges[starting_vertex]);i++){
        if(visited[adj[i]]=='0'){
            topological_visit(g,visited,adj[i],list,cycle_check);
        }
        if(visited[adj[i]]=='1'){
            (*cycle_check) = 1;
        }
    }
    free(adj);
    visited[starting_vertex] = '2';
    list_push_front(list, (void *)&starting_vertex);
}


List *  topological_sort(Graph * g,int* cycle_check){
    char * visited = (char *)malloc(sizeof(char)*g->no_vertex);
    memset(visited,'0',g->no_vertex);
    List * topological_order = create_list(sizeof(int));


    for(int i=0;i<g->no_vertex;i++){
        if(visited[i] == '0'){
            topological_visit(g, visited,i,topological_order,cycle_check);
        }
    }
    free(visited);
    return topological_order;
}

//auxiliar function tha inverts the directed edges of a graph
Graph * invert_graph(Graph* g){
    if(g!=NULL){
        Graph * inverse = create_graph(g->no_vertex);
        if(inverse != NULL){
            for(int i = 0;i<g->no_vertex;i++ ){
                int * adj = vectorize(g->lists_of_edges[i]);
                for(int j=0;j<list_size(g->lists_of_edges[i]);j++){
                    insert_directed_edge(inverse, adj[j],i);
                }
                free(adj);
            }
        }
        return inverse;
    }
    return NULL;
}



int find_maximum_time(Graph* g,List* topological_list){
    int* topological_vector = vectorize(topological_list);
    Graph* inverse_g = invert_graph(g);
    int * distancias = (int *)malloc(sizeof(int)*g->no_vertex);
    int tempo=0;


    for(int i=0;i<g->no_vertex;i++)
        distancias[i]=1;

    for(int i=0;i<g->no_vertex;i++){
        int * requisitos = vectorize(inverse_g->lists_of_edges[topological_vector[i]]);
        int maior = 0;
        for(int j=0;j<list_size(inverse_g->lists_of_edges[topological_vector[i]]);j++){
            if(distancias[requisitos[j]]>maior){
                maior = distancias[requisitos[j]];
            }
        }
        distancias[topological_vector[i]] = maior+1;
        if(distancias[topological_vector[i]]>tempo)
            tempo=distancias[topological_vector[i]];
        free(requisitos);
    }

    free(topological_vector);
    free(distancias);
    erase_graph(&inverse_g);
    return tempo;
}



//cemitério de tentativas
/*
void dfs_visit(Graph * g, int v, int * clock,int * relative_times){
    int * adj = vectorize(g->lists_of_edges[v]);
    (*clock)++;
    relative_times[v] = (*clock);
    //printf("%d->",v);
    for(int i = 0;i<list_size(g->lists_of_edges[v]);i++){
        if(relative_times[adj[i]] == 0)
            dfs_visit(g,adj[i],clock,relative_times);
    }
    (*clock)--;
    free(adj);
}

int find_maximum_time(Graph* g,List* topological_list){
    //list_print(topological_list,print_int);
    int* relative_times = (int *)malloc(sizeof(int)*g->no_vertex);
    int clock = 0;
    for(int i=0;i<g->no_vertex;i++)
        relative_times[i] = 0;
    int * vector = vectorize(topological_list);
    for(int i=0;i<g->no_vertex;i++){
        if(relative_times[vector[i]]==0)
            dfs_visit(g,vector[i],&clock,relative_times);
        //printf("\n");
    }

    for(int i=0;i<g->no_vertex;i++)
        printf("%d ",relative_times[i]);
    printf("\n");
    int maior = 0;
    for(int i=0;i<g->no_vertex;i++)
        if(relative_times[i]>maior)
            maior = relative_times[i];
    free(relative_times);
    free(vector);
    return maior;
}


*/
/*
int find_maximum_time(Graph* g,List* topological_list){
    int * vector = vectorize(topological_list);
    int time = 0, vertex_to_go = g->no_vertex;
    int * task_time = (int *)malloc(sizeof(int)*g->no_vertex);
    for(int i = 0;i<g->no_vertex;i++)
        task_time[i] = -1;
    
    int iterator = 0;
    while(vertex_to_go>0){
        List * paralleling_list = create_list(sizeof(int));
        time++;
        task_time[iterator]=time;
        vertex_to_go--;
        list_push_back(paralleling_list,&iterator);
        for(int j = iterator+1;j<g->no_vertex;j++){
            int * paralleling_vector = vectorize(paralleling_list);
            int flag=1;
            for(int k=0;k<list_size(paralleling_list);k++){
                if(list_search(g->lists_of_edges[paralleling_vector[k]],&j,equal_integers)){
                   flag=0;
                   break;
                }
            }
            if(flag){
                task_time[j]=time;
                vertex_to_go--;
                list_push_back(paralleling_list,&j);
            }
            free(paralleling_vector);
        }
        iterator++;
        while(iterator<g->no_vertex && task_time[iterator] == -1)
            iterator++;
        printf("%d",iterator);
        erase_list(&paralleling_list);
    }
    free(vector);
    free(task_time);
    return time;  
}
*/