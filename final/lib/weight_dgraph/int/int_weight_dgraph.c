#include "int_weight_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITIVE_VALUE 1000000

Graph createGraph(){
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

int addVertex(Graph graph, int id, char *name){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL){
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
        return 1;
    }
    return 0;
}

char *getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node != NULL)
        return jval_s(node->val);
    return NULL;
}

int addEdge(Graph graph, int v1, int v2, double weight){//from v1 to v2
    // CHECK IF V1 AND V2 EXIST IN Graph's vertice list
    JRB node = jrb_find_int(graph.vertices, v1);
    if(node == NULL) return 0;
    node = jrb_find_int(graph.vertices, v2);
    if(node == NULL) return 0;

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
    if(node != NULL)
        return 0;
    jrb_insert_int(tree, v2, new_jval_d(weight));
    return 1;
}

double getEdgeValue(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL)
        return INFINITIVE_VALUE;
    JRB tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if(node == NULL)
        return INFINITIVE_VALUE;
    return jval_d(node->val);
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
    //init
    JRB visited = make_jrb();
    Dllist stack = new_dllist();

    //find if start node exists
    JRB find_start = jrb_find_int(graph.vertices, start);
    if(find_start == NULL) return;

    //push start
    dll_prepend(stack, new_jval_i(start));
    while(!dll_empty(stack)){
        Dllist popped_node = dll_first(stack);
        int node_id = jval_i(popped_node->val);
        dll_delete_node(popped_node);

        if(jrb_find_int(visited, node_id) == NULL){
            func(graph, node_id);
            jrb_insert_int(visited, node_id, new_jval_i(1));
        }

        if(node_id == stop)
            break;

        int outList[100];
        int n = outdegree(graph, node_id, outList);
        for(int i = 0; i < n; i++){
            int child_id = outList[i];

            if(jrb_find_int(visited, child_id) == NULL)
                dll_prepend(stack, new_jval_i(child_id));
        }
    }
}

void BFS(Graph graph, int start, int stop, void (*func)(Graph, int)){
    //init
    JRB visited = make_jrb();
    Dllist queue = new_dllist();

    //find if start node exists
    JRB find_start = jrb_find_int(graph.vertices, start);
    if(find_start == NULL) return;

    //enqueue start
    dll_append(queue, new_jval_i(start));
    while(!dll_empty(queue)){
        Dllist dequeued_node = dll_first(queue);
        int node_id = jval_i(dequeued_node->val);
        dll_delete_node(dequeued_node);

        if(jrb_find_int(visited, node_id) == NULL){
            func(graph, node_id);
            jrb_insert_int(visited, node_id, new_jval_i(1));
        }

        if(node_id == stop)
            break;

        int outList[100];
        int n = outdegree(graph, node_id, outList);
        for(int i = 0; i < n; i++){
            int child_id = outList[i];

            if(jrb_find_int(visited, child_id) == NULL)
                dll_append(queue, new_jval_i(child_id));
        }
    }
}

// void printQueue(Dllist queue){
//     Dllist ptr;
//     dll_traverse(ptr, queue){
//         printf("%d ", jval_i(ptr->val));
//     }
//     printf("\n");
// }

// void printJRB(JRB visited){
//     JRB ptr;
//     jrb_traverse(ptr, visited){
//         printf("%d ", jval_i(ptr->key));
//     }
//     printf("\n");
// }

/*topological sort*/

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

/*end topo*/

int pdequeue(Dllist pqueue, JRB valueMap){
    double minValue = INFINITIVE_VALUE;
    double temp;

    Dllist ptr, minNodePtr;
    int minNode;

    dll_traverse(ptr, pqueue){
        int currentNode = jval_i(ptr->val);
        JRB jrb_ptr = jrb_find_int(valueMap, currentNode);
        temp = jval_d(jrb_val(jrb_ptr));
        if(temp < minValue){
            minValue = temp;
            minNodePtr = ptr;
            minNode = currentNode;
        }
    }

    dll_delete_node(minNodePtr);
    return minNode;
}

int checkInQueue(Dllist pqueue, int v){
    Dllist ptr;
    dll_traverse(ptr, pqueue){
        if(jval_i(ptr->val) == v)
            return 1;
    }
    return 0;
}

double shortestPath(Graph graph, int start, int stop, int *length, int *path){
    //find start
    *length = 0;

    JRB sPtr = jrb_find_int(graph.edges, start);
    if(sPtr == NULL) return INFINITIVE_VALUE;

    //init
    Dllist pqueue = new_dllist();
    JRB visited = make_jrb();
    JRB valueMap = make_jrb();
    JRB parentMap = make_jrb();

    //enqueue start
    dll_append(pqueue, new_jval_i(start));
    jrb_insert_int(valueMap, start, new_jval_d(0));
    jrb_insert_int(parentMap, start, new_jval_i(start));

    int parent_id = -1;

    while(!dll_empty(pqueue)){
        //pdequeue
        parent_id = pdequeue(pqueue, valueMap);
        jrb_insert_int(visited, parent_id, new_jval_i(1));

        if(parent_id == stop)
            break;

        double parent_value = jval_d(jrb_val(jrb_find_int(valueMap, parent_id)));

        //get outlist
        int outList[100];
        int numberOfOut = outdegree(graph, parent_id, outList);

        //foreach elm in adjacent list 
        for(int i = 0; i < numberOfOut; i++){
            int child_id = outList[i];
            //check visit
            JRB check_visited = jrb_find_int(visited, child_id);
            if(check_visited != NULL) continue;
            //enqueue
            if(!checkInQueue(pqueue, child_id))
                dll_append(pqueue, new_jval_i(child_id));
            //relax
            double temp_value = parent_value + getEdgeValue(graph, parent_id, child_id);
            JRB current_value_ptr = jrb_find_int(valueMap, child_id);
            if(current_value_ptr == NULL){
                jrb_insert_int(valueMap, child_id, new_jval_d(temp_value));
                jrb_insert_int(parentMap, child_id, new_jval_i(parent_id));
            }
            else{
                double current_value = jval_d(current_value_ptr->val);
                if(temp_value < current_value){
                    current_value_ptr->val = new_jval_d(temp_value);
                    JRB current_parent_ptr = jrb_find_int(parentMap, child_id);
                    current_parent_ptr->val = new_jval_i(parent_id);
                }
            }
        }
    }

    if(parent_id != stop)
        return INFINITIVE_VALUE;

    // //print value map
    // JRB map_ptr;
    // jrb_traverse(map_ptr, valueMap){
    //     printf("%d: %lf\n", jval_i(map_ptr->key), jval_d(map_ptr->val));
    // }

    double path_weight = jval_d(jrb_val(jrb_find_int(valueMap, parent_id)));

    //write path
    int counter = 0;
    while(1){
        path[counter] = parent_id;
        counter++;
        if(parent_id == start)
            break;
        parent_id = jval_i(jrb_val(jrb_find_int(parentMap, parent_id)));
    }

    //reverse path
    int i = 0, j = counter - 1;
    int temp;

    while(i < j){
        temp = path[i];
        path[i] = path[j];
        path[j] = temp;
        i++;
        j--;
    }

    *length = counter;
    return path_weight;
}