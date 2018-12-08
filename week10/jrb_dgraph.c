#include "jrb_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Graph createGraph(){
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

void addVertex(Graph graph, char *id, int value){
    JRB ptr = jrb_find_str(graph.vertices, id);
    if(ptr == NULL){
        jrb_insert_str(graph.vertices, strdup(id), new_jval_i(value));
    }
}

int getVertex(Graph graph, char *id){
    JRB ptr = jrb_find_str(graph.vertices, id);
    if(ptr == NULL) return -1;

    return jval_i(ptr->val);
}

int addEdge(Graph graph, char * v1, char * v2, int value){
    JRB ptr = jrb_find_str(graph.vertices, v1);
    if(ptr == NULL) return 0;
    ptr = jrb_find_str(graph.vertices, v2);
    if(ptr == NULL) return 0;

    //for v1

    JRB tree;
    ptr = jrb_find_str(graph.edges, v1);
    if(ptr == NULL){
        tree = make_jrb();
        jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
    }
    else{
        tree = (JRB)jval_v(ptr->val);
    }

    ptr = jrb_find_str(tree, v2);
    if(ptr != NULL)
        return 0;
        
    jrb_insert_str(tree, strdup(v2), new_jval_i(value));

    return 1;
}

int getEdgeValue(Graph graph, char *v1, char *v2){
    JRB node = jrb_find_str(graph.edges, v1);
    if(node == NULL)
        return INFINITIVE_VALUE;
    JRB tree = (JRB)jval_v(node->val);
    node = jrb_find_str(tree, v2);
    if(node == NULL)
        return INFINITIVE_VALUE;
    return jval_i(node->val);
}

int hasEdge(Graph graph, char * v1, char * v2){
    JRB node = jrb_find_str(graph.edges, v1);
    if(node == NULL)
        return 0;
    JRB tree = (JRB)jval_v(node->val);
    node = jrb_find_str(tree, v2);
    if(node == NULL)
        return 0;
    return 1;
}

int outdegree(Graph graph, char *v, char output[][50]){
    int counter = 0;
    // printf("find adjacent for: %s\n", v);
    JRB node = jrb_find_str(graph.edges, v);
    if(node != NULL){
        JRB tree = (JRB)jval_v(node->val);
        JRB ptr;
        jrb_traverse(ptr, tree){
            strcpy(output[counter], jval_s(ptr->key));
            counter++;
        }
    }

    return counter;
}

void dropGraph(Graph graph){
    //free vertices
    JRB ptr;
    jrb_traverse(ptr, graph.vertices)
        free(jval_s(ptr->val));
    jrb_free_tree(graph.vertices);

    //free edges;
    jrb_traverse(ptr, graph.edges)
        jrb_free_tree((JRB)jval_v(ptr->val));
    jrb_free_tree(graph.edges);
}

// void BFS(Graph graph, int start, int stop, void (*func)(int)){
//     Dllist queue = new_dllist();
//     JRB visited = make_jrb();

//     JRB startNode = jrb_find_int(graph.vertices, start);
//     if(startNode == NULL) return;

//     dll_append(queue, new_jval_i(start));
//     while(!dll_empty(queue)){
//         //dequeue
//         Dllist node = dll_first(queue);
//         int v = jval_i(node->val);
//         dll_delete_node(node);

//         if(jrb_find_int(visited, v) == NULL){
//             func(v);
//             jrb_insert_int(visited, v, new_jval_i(1));
//         }

//         if(v == stop)
//             break;
//         int output[100];
//         int n = getAdjacentVertices(graph, v, output);
//         int i;
//         for(i = 0; i < n; i++){
//             if(jrb_find_int(visited, output[i]) == NULL)
//                 dll_append(queue, new_jval_i(output[i]));
//         }
//     }
//     jrb_free_tree(visited);
//     free_dllist(queue);
// }

// void DFS(Graph graph, int start, int stop, void (*func)(int)){
//     JRB visited = make_jrb();
//     Dllist stack = new_dllist();

//     JRB startNode = jrb_find_int(graph.vertices, start);
//     if(startNode == NULL) return;
    
//     dll_prepend(stack, new_jval_i(start));
//     while(!dll_empty(stack)){
//         Dllist node = dll_first(stack);
//         int v = jval_i(node->val);
//         dll_delete_node(node);

//         if(jrb_find_int(visited, v) == NULL){
//             func(v);
//             jrb_insert_int(visited, v, new_jval_i(1));
//         }

//         if(v == stop)
//             break;

//         int output[100];
//         int n = getAdjacentVertices(graph, v, output);
//         int i;
//         for(i = 0; i < n; i++){
//             if(jrb_find_int(visited, output[i]) == NULL)
//                 dll_prepend(stack, new_jval_i(output[i]));
//         }
//     }

//     jrb_free_tree(visited);
//     free_dllist(stack);
// }

// int shortestPath(Graph graph, char * start, char * stop, char path[][100]){
//     Dllist queue = new_dllist();
//     JRB visited = make_jrb();
//     JRB prevTable = make_jrb();

//     JRB startNode = jrb_find_str(graph.vertices, start);
//     if(startNode == NULL) return 0;

//     char *prev = "-1";
//     char *v = start;

//     dll_append(queue, new_jval_s(strdup(start)));
//     jrb_insert_str(prevTable, strdup(start), new_jval_s(strdup(prev)));

//     while(!dll_empty(queue)){
//         //dequeue
//         Dllist node = dll_first(queue);
//         v = jval_s(node->val);
//         dll_delete_node(node);

//         if(jrb_find_str(visited, v) == NULL){
//             jrb_insert_str(visited, strdup(v), new_jval_i(1));
//         }

//         if(strcmp(v, stop) == 0)
//             break;

//         prev = v;
//         char output[100][5];
//         int n = getAdjacentVertices(graph, v, output);
//         int i;
//         for(i = 0; i < n; i++){
//             if(jrb_find_str(visited, output[i]) == NULL){
//                 dll_append(queue, new_jval_s(strdup(output[i])));
//                 jrb_insert_str(prevTable, strdup(output[i]), new_jval_s(strdup(prev)));
//             }
//         }
//     }

//     //check if the last node visited is stop
//     int counter = 0;
//     if(strcmp(v, stop) == 0){
//     	JRB ptr;
//     	char * ptrIndex = v;
//         // path[counter] = ptrIndex;
//         strcpy(path[counter], ptrIndex);
//         counter++;
//     	while(strcmp(ptrIndex, start) != 0){
//     		ptr = jrb_find_str(prevTable, ptrIndex);
//     		ptrIndex = jval_s(ptr->val);
//     		// path[counter] = ptrIndex;
//             strcpy(path[counter], ptrIndex);
//     		counter++;
//     	}

//         //reverse path
//         int i = 0, j = counter - 1;
//         char temp[5];
//         while(i < j){
//             // temp = path[i];
//             strcpy(temp, path[i]);
//             // path[i] = path[j];
//             strcpy(path[i], path[j]);
//             // path[j] = temp;
//             strcpy(path[j], temp);
//             i++;
//             j--;
//         }
//     }

    
//     jrb_free_tree(visited);
//     jrb_free_tree(prevTable);
//     free_dllist(queue);

//     return counter;
// }