#ifndef GRAPH_AM_H
#define GRAPH_AM_H
typedef int bool;
#define true 1
#define false 0
#define ERROR -100

typedef struct graph_ Graph;

Graph * create_graph(int number_of_vertex);//allocates the mem for the graph
void erase_graph(Graph ** g);//erases the graph

int insert_edge(Graph * g, int vertex_a, int vertex_b);//creates a non-directed edge
int insert_directed_edge(Graph * g,int origin_vertex,int destiny_vertex);//creastes a directed edge

int remove_edge(Graph * g,int vertex_a,int vertex_b);//removes a non-directed edge
int remove_directed_edge(Graph * g,int origin_vertex,int destiny_vertex);//removes a directed edge

bool is_there_edge(Graph * g,int origin_vertex,int destiny_vertex);//verifies if is there a given edge
void print_graph(Graph *g);//prints the matrix

#endif