#include "jrb_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdlib.h>


Graph createGraph(){
    Graph g = make_jrb();
    return g;
}

void addVertex(Graph graph, int id, char *name){
    JRB node = jrb_find_int(graph, id);
    if(node == NULL){
        JRB tree = make_jrb();
        jrb_insert_int(graph, id, new_jval_v(tree));
    }
}

char *getVertex(Graph graph, int id){

}

void addEdge(Graph graph, int v1, int v2){//from v1 to v2
    JRB tree;

    //for v1

    //find if v1 already in graph
    JRB node = jrb_find_int(graph, v1);
    //if no, insert v1
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph, v1, new_jval_v(tree));
    }
    //if yes
    else{
        tree = (JRB)jval_v(node->val);
    }
    //insert v2 to v1's tree
    //check if v2 already in v1's tree
    node = jrb_find_int(tree, v2);
    if(node == NULL)
        jrb_insert_int(tree, v2, new_jval_i(1));
}

int hasEdge(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph, v1);
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
    JRB node = jrb_find_int(graph, v);
    if(node != NULL){
        JRB tree = (JRB)jval_v(node->val);
        JRB ptr;
        jrb_traverse(ptr, tree){
            output[counter++] = jval_i(ptr->key);
        }
    }

    return counter;
}

int indegree(Graph graph, int v, int* output){
    JRB ptr, tree, node;
    int counter = 0;
    jrb_traverse(ptr, graph){
        tree = (JRB)jval_v(ptr->val);
        node = jrb_find_int(tree, v);
        if(node != NULL){
            output[counter++] = jval_i(ptr->key);
        }
    }
}

// int adjacent(Graph graph, int v1, int v2){
//     JRB node = jrb_find_int(graph, v1);
//     if(node == NULL)
//         return 0;
//     else{
//         JRB tree = (JRB)jval_v(node->val);
//         JRB check = jrb_find_int(tree, v2);
//         if(jval_i(check->val) == 1)
//             return 1;
//         return 0;
//     }
// }

int getAdjacentVertices (Graph graph, int v, int* output){
    int counter = 0;
    JRB node = jrb_find_int(graph, v);
    if(node != NULL){
        JRB tree = (JRB)jval_v(node->val);
        JRB ptr;
        jrb_traverse(ptr, tree){
            output[counter++] = jval_i(ptr->key);
        }
    }

    return counter;
}

int dag_start;
int dag_check = 0;

void dag_visit(Graph g){
    dag_check = hasEdge(g, v, dag_start);
}

int DAG(Graph graph){
    // Dllist queue = new_dllist();
    // int start = 0;
    // dll_append(queue, new_jval_i(start)); 
    // JRB visited = make_jrb();

    // //loop until empty queue or meet stop value
    // while(!dll_empty(queue)){
    //     //dequeue
    //     Dllist node = dll_first(queue);
    //     int v = jval_i(node->val);
    //     dll_delete_node(node);

    //     if(jrb_find_int(visited, v) != NULL){//visit twice
    //         // func(v);
    //         // jrb_insert_int(visited, v, new_jval_i(1));
    //         jrb_free_tree(visited);
    //         return 1;
    //     }

    //     int output[100];
    //     int n = getAdjacentVertices(graph, v, output);
    //     int i;
    //     for(i = 0; i < n; i++){
    //         if(jrb_find_int(visited, output[i]) == NULL)
    //             dll_append(queue, new_jval_i(output[i]));
    //     }
    // }
    // jrb_free_tree(visited);
    // return 0;
    JRB node;
    JRB dag_start;
    jrb_traverse(node, graph){
        dag_start = node;
        BFS(graph, dag_start, -1, dag_visit)
    }
}

void dropGraph(Graph graph){
    //traverse through tree
    JRB ptr;
    jrb_traverse(ptr, graph){
        //free sub-tree
        jrb_free_tree((JRB)jval_v(ptr->val));
    }
    jrb_free_tree(graph);
}

void BFS(Graph graph, int start, int stop, void (*func)(int)){
    Dllist queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    JRB visited = make_jrb();

    //loop until empty queue or meet stop value
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
}

// void DFS(Graph graph, int start, int stop, void (*func)(int)){
//     JRB visited = make_jrb();
//     Dllist stack = new_dllist();
//     JRB start_node = jrb_find_int(graph, start);
//     if(start_node != NULL){
//         dll_prepend(stack, new_jval_i(start));
//         while(!dll_empty(stack)){
//             Dllist node = dll_first(stack);
//             int v = jval_i(node->val);
//             dll_delete_node(node);

//             if(jrb_find_int(visited, v) == NULL){
//                 func(v);
//                 jrb_insert_int(visited, v, new_jval_i(1));
//             }

//             if(v == stop)
//                 break;

//             int output[100];
//             int n = getAdjacentVertices(graph, v, output);
//             int i;
//             for(i = 0; i < n; i++){
//                 if(jrb_find_int(visited, output[i]) == NULL)
//                     dll_prepend(stack, new_jval_i(output[i]));
//             }
//         }
//     }
//     jrb_free_tree(visited);
// }
