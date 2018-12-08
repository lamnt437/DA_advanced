#include "jrb_dgraph.h"
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

void addVertex(Graph graph, int id, int value){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL)
        jrb_insert_int(graph.vertices, id, new_jval_i(value));
}

int getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node != NULL)
        return jval_i(node->val);
    return -1;
}

void addEdge(Graph graph, int v1, int v2){//from v1 to v2
    // CHECK IF V1 AND V2 EXIST IN Graph's vertice list
    JRB node = jrb_find_int(graph.vertices, v1);
    if(node == NULL) return;
    node = jrb_find_int(graph.vertices, v2);
    if(node == NULL) return;

    // ADD EDGE
    JRB tree;
    node = jrb_find_int(graph.edges, v1);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }
    else{
        tree = (JRB)jval_v(node->val);
    }

    node = jrb_find_int(tree, v2);
    if(node == NULL)
        jrb_insert_int(tree, v2, new_jval_i(1));
}

int hasEdge(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL)
        return 0;
    JRB tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if(node == NULL)
        return 0;
    return 1;
}

int outdegree(Graph graph, int v, int* output){
    int counter = 0;
    JRB node = jrb_find_int(graph.edges, v);
    if(node != NULL){
        JRB tree = (JRB)jval_v(node->val);
        JRB ptr;
        jrb_traverse(ptr, tree){
            output[counter] = jval_i(ptr->key);
            counter++;
        }
    }

    return counter;
}

int indegree(Graph graph, int v, int* output){
    JRB ptr, tree, node;
    int counter = 0;
    jrb_traverse(ptr, graph.edges){
        tree = (JRB)jval_v(ptr->val);
        node = jrb_find_int(tree, v);
        if(node != NULL){
            output[counter] = jval_i(ptr->key);
            counter++;
        }
    }
    return counter;
}

void DFS(Graph graph, int start, int stop, void (*func)(Graph, int)){
    JRB visited = make_jrb();
    Dllist stack = new_dllist();
    JRB start_node = jrb_find_int(graph.edges, start);
    if(start_node != NULL){
        dll_prepend(stack, new_jval_i(start));
        while(!dll_empty(stack)){
            Dllist node = dll_first(stack);
            int v = jval_i(node->val);
            dll_delete_node(node);

            if(jrb_find_int(visited, v) == NULL){
                func(graph, v);
                jrb_insert_int(visited, v, new_jval_i(1));
            }

            if(v == stop)
                break;

            int output[100];
            int n = outdegree(graph, v, output);
            int i;
            for(i = 0; i < n; i++){
                if(jrb_find_int(visited, output[i]) == NULL)
                    dll_prepend(stack, new_jval_i(output[i]));
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(stack);
}

void BFS(Graph graph, int start, int stop, void (*func)(Graph, int)){
    JRB visited = make_jrb();
    Dllist queue = new_dllist();
    JRB start_node = jrb_find_int(graph.edges, start);

    if(start_node != NULL){
        dll_append(queue, new_jval_i(start));
        while(!dll_empty(queue)){
            Dllist node = dll_first(queue);
            int v = jval_i(node->val);
            dll_delete_node(node);

            if(jrb_find_int(visited, v) == NULL){
                func(graph, v);
                jrb_insert_int(visited, v, new_jval_i(1));
            }

            if(v == stop)
                break;
            int output[100];
            int n = outdegree(graph, v, output);
            int i;
            for(i = 0; i < n; i++){
                if(jrb_find_int(visited, output[i]) == NULL)
                    dll_append(queue, new_jval_i(output[i]));
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(queue);
}

int dag_start;
int dag_check = 0;

void dag_visit(Graph g, int v){
    dag_check = hasEdge(g, v, dag_start);
}

int DAG(Graph graph){
    JRB node;
    dag_check = 0;
    jrb_traverse(node, graph.vertices){
        dag_start = jval_i(node->key);
        DFS(graph, dag_start, -1, dag_visit);
        if(dag_check != 0)
            return 0;
    }
    return 1;
}

void dropGraph(Graph graph){
    //traverse through tree
    JRB ptr;
    jrb_traverse(ptr, graph.vertices){
        //free sub-tree
        free(jval_s(ptr->val));
    }
    jrb_free_tree(graph.vertices);

    jrb_traverse(ptr, graph.edges){
        jrb_free_tree((JRB)jval_v(ptr->val));
    }
    jrb_free_tree(graph.edges);
}

void topologicalSort(Graph graph, int * output, int *n){
    //create indegree table
    JRB indegreeTable = make_jrb();
    Dllist queue = new_dllist();
    
    JRB ptr;
    int inNumber;
    int inList[100];
    int outNumber;
    int outList[100];
    int i;

    jrb_traverse(ptr, graph.vertices){
        int verticeIndex = jval_i(ptr->key);
        inNumber = indegree(graph, verticeIndex, inList);
        jrb_insert_int(indegreeTable, verticeIndex, new_jval_i(inNumber));
        if(inNumber == 0){
            dll_append(queue, new_jval_i(verticeIndex));
        }
    }

    //sort
    int counter = 0;
    while(!dll_empty(queue)){
        Dllist dequeuedNode = dll_first(queue);
        int visitingVertice = jval_i(dll_val(dequeuedNode));
        dll_delete_node(dequeuedNode);

        output[counter] = visitingVertice;
        counter++;

        outNumber = outdegree(graph, visitingVertice, outList);
        for(i = 0; i < outNumber; i++){
            JRB decreaseIndegreeNode = jrb_find_int(indegreeTable, outList[i]);
            int newIndegree = jval_i(decreaseIndegreeNode->val) - 1;
            decreaseIndegreeNode->val = new_jval_i(newIndegree);

            if(newIndegree == 0)
                dll_append(queue, new_jval_i(outList[i]));
        }
    }

    *n = counter;
    jrb_free_tree(indegreeTable);
    free_dllist(queue);
}