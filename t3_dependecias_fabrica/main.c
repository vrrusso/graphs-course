#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "list.h"


int main(void){
    int no_tasks,no_dependencies,aux_task1,aux_task2,cycle_check = 0;
    Graph * tasks;

    scanf("%d %d",&no_tasks,&no_dependencies);
    tasks = create_graph(no_tasks);
    for(int i=0;i<no_dependencies;i++){
        scanf("%d %d",&aux_task1,&aux_task2);
        insert_directed_edge(tasks,aux_task1,aux_task2);
    }
    List * topological_list = topological_sort(tasks,&cycle_check);
    if(cycle_check){
        printf("-1\n");
    }
    else{
        printf("%d\n",find_maximum_time(tasks,topological_list));
    }

    erase_graph(&tasks);
    erase_list(&topological_list);
    return 0;
}