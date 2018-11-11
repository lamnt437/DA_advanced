#include "jrb_graph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdlib.h>
#include <string.h>

Graph createGraph(){
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

void addVertex(Graph graph, int id, char *name){
    JRB ptr = jrb_find_int(graph.vertices, id);
    if(ptr == NULL){
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
    }
}

char *getVertex(Graph graph, int id){
    JRB ptr = jrb_find_int(graph.vertices, id);
    if(ptr == NULL) return NULL;

    return jval_s(ptr->val);
}

void addEdge(Graph graph, int v1, int v2){
    JRB ptr = jrb_find_int(graph.vertices, v1);
    if(ptr == NULL) return;
    ptr = jrb_find_int(graph.vertices, v2);
    if(ptr == NULL) return;

    //for v1

    JRB tree;
    ptr = jrb_find_int(graph.edges, v1);
    if(ptr == NULL){
        tree = make_jrb();
        jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }
    else{
        tree = (JRB)jval_v(ptr->val);
    }

    ptr = jrb_find_int(tree, v2);
    if(ptr == NULL)
        jrb_insert_int(tree, v2, new_jval_i(1));

    //for v2

    ptr = jrb_find_int(graph.edges, v2);
    if(ptr == NULL){
        tree = make_jrb();
        jrb_insert_int(graph.edges, v2, new_jval_v(tree));
    }
    else{
        tree = (JRB)jval_v(ptr->val);
    }
    ptr = jrb_find_int(tree, v1);
    if(ptr == NULL)
        jrb_insert_int(tree, v1, new_jval_i(1));
}

int adjacent(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL)
        return 0;
    else{
        JRB tree = (JRB)jval_v(node->val);
        JRB check = jrb_find_int(tree, v2);
        if(jval_i(check->val) == 1)
            return 1;
        return 0;
    }
}

int getAdjacentVertices (Graph graph, int v, int* output){
    int counter = 0;
    JRB node = jrb_find_int(graph.edges, v);
    if(node != NULL){
        JRB tree = (JRB)jval_v(node->val);
        JRB ptr;
        jrb_traverse(ptr, tree){
            output[counter++] = jval_i(ptr->key);
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

void BFS(Graph graph, int start, int stop, void (*func)(int)){
    Dllist queue = new_dllist();
    JRB visited = make_jrb();

    JRB startNode = jrb_find_int(graph.vertices, start);
    if(startNode == NULL) return;

    dll_append(queue, new_jval_i(start));
    while(!dll_empty(queue)){
        //dequeue
        Dllist node = dll_first(queue);
        int v = jval_i(node->val);
        dll_delete_node(node);

        if(jrb_find_int(visited, v) == NULL){
            func(v);
            jrb_insert_int(visited, v, new_jval_i(1));
        }

        if(v == stop)
            break;
        int output[100];
        int n = getAdjacentVertices(graph, v, output);
        int i;
        for(i = 0; i < n; i++){
            if(jrb_find_int(visited, output[i]) == NULL)
                dll_append(queue, new_jval_i(output[i]));
        }
    }
    jrb_free_tree(visited);
    free_dllist(queue);
}

void DFS(Graph graph, int start, int stop, void (*func)(int)){
    JRB visited = make_jrb();
    Dllist stack = new_dllist();

    JRB startNode = jrb_find_int(graph.vertices, start);
    if(startNode == NULL) return;
    
    dll_prepend(stack, new_jval_i(start));
    while(!dll_empty(stack)){
        Dllist node = dll_first(stack);
        int v = jval_i(node->val);
        dll_delete_node(node);

        if(jrb_find_int(visited, v) == NULL){
            func(v);
            jrb_insert_int(visited, v, new_jval_i(1));
        }

        if(v == stop)
            break;

        int output[100];
        int n = getAdjacentVertices(graph, v, output);
        int i;
        for(i = 0; i < n; i++){
            if(jrb_find_int(visited, output[i]) == NULL)
                dll_prepend(stack, new_jval_i(output[i]));
        }
    }

    jrb_free_tree(visited);
    free_dllist(stack);
}

int shortestPath(Graph graph, int start, int stop, int *path){
    Dllist queue = new_dllist();
    JRB visited = make_jrb();
    JRB prevTable = make_jrb();

    JRB startNode = jrb_find_int(graph.vertices, start);
    if(startNode == NULL) return 0;

    int prev = 0;
    int v = start;

    dll_append(queue, new_jval_i(start));
    jrb_insert_int(prevTable, start, new_jval_i(prev));

    while(!dll_empty(queue)){
        //dequeue
        Dllist node = dll_first(queue);
        v = jval_i(node->val);
        dll_delete_node(node);

        if(jrb_find_int(visited, v) == NULL){
            jrb_insert_int(visited, v, new_jval_i(1));
        }

        if(v == stop)
            break;

        prev = v;
        int output[100];
        int n = getAdjacentVertices(graph, v, output);
        int i;
        for(i = 0; i < n; i++){
            if(jrb_find_int(visited, output[i]) == NULL){
                dll_append(queue, new_jval_i(output[i]));
                jrb_insert_int(prevTable, output[i], new_jval_i(prev));
            }
        }
    }

    //check if the last node visited is stop
    int counter = 0;
    if(v == stop){
    	JRB ptr;
    	int ptrIndex = v;
        path[counter] = ptrIndex;
        counter++;
    	while(ptrIndex != start){
    		ptr = jrb_find_int(prevTable, ptrIndex);
    		ptrIndex = jval_i(ptr->val);
    		path[counter] = ptrIndex;
    		counter++;
    	}

        //reverse path
        int i = 0, j = counter - 1, temp;
        while(i < j){
            temp = path[i];
            path[i] = path[j];
            path[j] = temp;
            i++;
            j--;
        }
    }

    
    jrb_free_tree(visited);
    jrb_free_tree(prevTable);
    free_dllist(queue);

    return counter;
}