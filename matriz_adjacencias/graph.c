#include "graph.h"
#include<stdio.h>
#include<stdlib.h>
#define ERROR -100

struct graph_{
    int ** matrix;
    int no_vertex;
    int no_edges;
};


Graph * create_graph(int number_of_vertex){
    if(number_of_vertex <= 0)
        return NULL;
    Graph * g = (Graph *) malloc(sizeof(Graph));
    if(g != NULL){
        g->no_vertex = number_of_vertex;
        g->no_edges  = 0;
        g->matrix = (int **)malloc(sizeof(int *)*number_of_vertex);
        for(int i=0;i<number_of_vertex;i++)
            g->matrix[i]=(int *)malloc(sizeof(int)*number_of_vertex);
        for(int i=0;i<number_of_vertex;i++)
            for(int j=0;j<number_of_vertex;j++)
                g->matrix[i][j]=BLANK;
    }
    return g;
}

void erase_graph(Graph ** g){
    if( (*g) != NULL && (*g)->no_vertex != 0 ){
        for(int i=0;i<(*g)->no_vertex;i++)
           free((*g)->matrix[i]);
        free((*g)->matrix);
        free(*g);
        g=NULL;
    }
}

int weight_of_edge(Graph * g, int origin_vertex,int destiny_vertex){
    if( g!= NULL )
        return g->matrix[origin_vertex][destiny_vertex];
    else
        return ERROR;
}

bool is_there_edge(Graph * g, int origin_vertex,int destiny_vertex){
    int weight = weight_of_edge(g,origin_vertex,destiny_vertex);
    return weight==ERROR?ERROR:weight!=BLANK ?1:0; 
}

int insert_directed_edge(Graph *g,int origin_vertex,int destiny_vertex,int weight){
    if(g!=NULL){
        g->matrix[origin_vertex][destiny_vertex] = weight;
        return 1;
    }
    else{
        return ERROR;
    }
}

int insert_edge(Graph * g, int vertex_a, int vertex_b,int weight){
    insert_directed_edge(g,vertex_a,vertex_b,weight);
    return insert_directed_edge(g,vertex_b,vertex_a,weight);
}


int remove_directed_edge(Graph *g,int origin_vertex,int destiny_vertex){
    if(g!=NULL){
        g->matrix[origin_vertex][destiny_vertex] = BLANK;
        return 1;
    }
    else{
        return ERROR;
    }
}
int remove_edge(Graph * g,int vertex_a,int vertex_b){
    remove_directed_edge(g,vertex_a,vertex_b);
    return remove_directed_edge(g,vertex_b,vertex_a);
}