#include "int_weight_ugraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITIVE_VALUE 1000000

typedef struct nodeMap{
    int prev;
    double val;
}NodeMap;

Graph createGraph(){
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

void addVertex(Graph graph, int id, char *name){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL)
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node != NULL)
        return jval_s(node->val);
    return NULL;
}

void addEdge(Graph graph, int v1, int v2, double weight){
    // CHECK IF V1 AND V2 EXIST IN Graph's vertice list

    //from v1 to v2
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
        jrb_insert_int(tree, v2, new_jval_d(weight));

    //from v2 to v1
    node = jrb_find_int(graph.edges, v2);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph.edges, v2, new_jval_v(tree));
    }
    else{
        tree = (JRB) jval_v(node->val);
    }

    node = jrb_find_int(tree, v1);
    if(node == NULL)
        jrb_insert_int(tree, v1, new_jval_d(weight));
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

double shortestPath(Graph graph, int s, int t, int *length, int *path){
    //find s
    *length = 0;

    JRB sPtr = jrb_find_int(graph.edges, s);
    if(sPtr == NULL) return INFINITIVE_VALUE;

    //init
    Dllist pqueue = new_dllist();
    JRB visited = make_jrb();
    JRB valueMap = make_jrb();
    JRB parentMap = make_jrb();

    //enqueue s
    dll_append(pqueue, new_jval_i(s));
    jrb_insert_int(valueMap, s, new_jval_i(0));
    jrb_insert_int(parentMap, s, new_jval_i(s));

    int parentNode = -1;

    while(!dll_empty(pqueue)){
        //pdequeue
        parentNode = pdequeue(pqueue, valueMap);
        JRB checkVisit = jrb_find_int(visited, parentNode);
        if(checkVisit != NULL) continue;

        jrb_insert_int(visited, parentNode, new_jval_i(1));

        if(parentNode == t)
            break;

        int parentVal = jval_i(jrb_val(jrb_find_int(valueMap, parentNode)));
        //get adjacent list
        int outList[100];
        int numberOfOut = outdegree(graph, parentNode, outList);

        //foreach elm in adjacent list 
        for(int i = 0; i < numberOfOut; i++){
            //check visit
            checkVisit = jrb_find_int(visited, outList[i]);
            if(checkVisit != NULL) continue;
            //enqueue
            if(!checkInQueue(pqueue, outList[i]))
                dll_append(pqueue, new_jval_i(outList[i]));
            //relax
            int newVal = parentVal + getEdgeValue(graph, parentNode, outList[i]);
            JRB currentValPtr = jrb_find_int(valueMap, outList[i]);
            if(currentValPtr == NULL){
                jrb_insert_int(valueMap, outList[i], new_jval_i(newVal));
                jrb_insert_int(parentMap, outList[i], new_jval_i(parentNode));
            }
            else{
                int currentVal = jval_i(currentValPtr->val);
                if(newVal < currentVal){
                    currentValPtr->val = new_jval_i(newVal);
                    JRB currentParPtr = jrb_find_int(parentMap, outList[i]);
                    currentParPtr->val = new_jval_i(parentNode);
                }
            }
        }
    }

    if(parentNode != t)
        return INFINITIVE_VALUE;

    int pathWeight = jval_i(jrb_val(jrb_find_int(valueMap, parentNode)));
    int counter = 0;
    while(1){
        path[counter] = parentNode;
        counter++;
        if(parentNode == s)
            break;
        parentNode = jval_i(jrb_val(jrb_find_int(parentMap, parentNode)));
    }

    //reverse path
    int start = 0, end = counter - 1;
    int temp;

    while(start < end){
        temp = path[start];
        path[start] = path[end];
        path[end] = temp;
        start++;
        end--;
    }

    *length = counter;
    return pathWeight;
}

// double shortestPath(Graph graph, int s, int t, int *length, int *path){
//     //find s
//     *length = 0;

//     JRB sPtr = jrb_find_int(graph.edges, s);
//     if(sPtr == NULL) return INFINITIVE_VALUE;

//     //init
//     Dllist pqueue = new_dllist();
//     JRB visited = make_jrb();
//     JRB valueMap = make_jrb();
//     JRB parentMap = make_jrb();

//     //enqueue s
//     dll_append(pqueue, new_jval_i(s));
//     jrb_insert_int(valueMap, s, new_jval_i(0));
//     jrb_insert_int(parentMap, s, new_jval_i(s));

//     int parentNode = -1;

//     while(!dll_empty(pqueue)){
//         //pdequeue
//         parentNode = pdequeue(pqueue, valueMap);
//         JRB checkVisit = jrb_find_int(visited, parentNode);
//         if(checkVisit != NULL) continue;

//         jrb_insert_int(visited, parentNode, new_jval_i(1));

//         // if(parentNode == t)
//         //     break;

//         int parentVal = jval_i(jrb_val(jrb_find_int(valueMap, parentNode)));
//         //get adjacent list
//         int outList[100];
//         int numberOfOut = outdegree(graph, parentNode, outList);

//         //foreach elm in adjacent list 
//         for(int i = 0; i < numberOfOut; i++){
//             //check visit
//             checkVisit = jrb_find_int(visited, outList[i]);
//             if(checkVisit != NULL) continue;
//             //enqueue
//             if(!checkInQueue(pqueue, outList[i]))
//                 dll_append(pqueue, new_jval_i(outList[i]));
//             //relax
//             int newVal = parentVal + getEdgeValue(graph, parentNode, outList[i]);
//             JRB currentValPtr = jrb_find_int(valueMap, outList[i]);
//             if(currentValPtr == NULL){
//                 jrb_insert_int(valueMap, outList[i], new_jval_i(newVal));
//                 jrb_insert_int(parentMap, outList[i], new_jval_i(parentNode));
//             }
//             else{
//                 int currentVal = jval_i(currentValPtr->val);
//                 if(newVal < currentVal){
//                     currentValPtr->val = new_jval_i(newVal);
//                     JRB currentParPtr = jrb_find_int(parentMap, outList[i]);
//                     currentParPtr->val = new_jval_i(parentNode);
//                 }
//             }
//         }
//     }

//     // if(parentNode != t)
//     //     return INFINITIVE_VALUE;
//     JRB jrb_ptr1 = jrb_find_int(valueMap, t);
//     if(jrb_ptr1 == NULL)
//         return INFINITIVE_VALUE;

//     int pathWeight = jval_i(jrb_val(jrb_ptr1));
//     int counter = 0;
//     parentNode = t;
//     while(1){
//         path[counter] = parentNode;
//         counter++;
//         if(parentNode == s)
//             break;
//         parentNode = jval_i(jrb_val(jrb_find_int(parentMap, parentNode)));
//     }

//     //reverse path
//     int start = 0, end = counter - 1;
//     int temp;

//     while(start < end){
//         temp = path[start];
//         path[start] = path[end];
//         path[end] = temp;
//         start++;
//         end--;
//     }

//     *length = counter;
//     return pathWeight;
// }