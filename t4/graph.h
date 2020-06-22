#ifndef GRAPH_AM_H
#define GRAPH_AM_H
typedef int bool;
#define true 1
#define false 0
#define ERROR -100
#include "list.h"

typedef struct graph_ Graph;

Graph * create_graph(int number_of_vertex);//allocates the mem for the graph
void erase_graph(Graph ** g);//erases the graph

int insert_edge(Graph * g, int vertex_a, int vertex_b,int time,int price);//creates a non-directed edge
int insert_directed_edge(Graph * g,int origin_vertex,int destiny_vertex,int time,int price);//creastes a directed edge

int remove_edge(Graph * g,int vertex_a,int vertex_b);//removes a non-directed edge
int remove_directed_edge(Graph * g,int origin_vertex,int destiny_vertex);//removes a directed edge

bool is_there_edge(Graph * g,int origin_vertex,int destiny_vertex);//verifies if is there a given edge
void print_graph(Graph *g);//prints the matrix


List *  topological_sort(Graph * g, int* cycle_check);//generates a list in topological order for a directed graph - verifies if there is a cycle
int find_maximum_time(Graph* g,List* topological_list);//returns the maximum distance betwen in any connected portion of the graph

#endif