#include "jrb_graph.h"
#include "libfdr/jrb.h"
#include <stdlib.h>


Graph createGraph(){
    Graph g = make_jrb();
    return g;
}
void addEdge(Graph graph, int v1, int v2){
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
    jrb_insert_int(tree, v2, new_jval_i(1));

    //for v2
    node = jrb_find_int(graph, v2);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph, v2, new_jval_v(tree));
    }
    else{
        tree = (JRB)jval_v(node->val);
    }
    jrb_insert_int(tree, v1, new_jval_i(1));
}
int adjacent(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph, v1);
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
void dropGraph(Graph graph){
    //traverse through tree
    JRB ptr;
    jrb_traverse(ptr, graph){
        //free sub-tree
        jrb_free_tree((JRB)jval_v(ptr->val));
    }
    jrb_free_tree(graph);
}