#include "libfdr/jrb.h"

typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char *name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int outdegree(Graph graph, int v, int* output);
int indegree(Graph graph, int v, int* output);
int DAG(Graph graph);
void dropGraph(Graph graph);
void topologicalSort(Graph graph, int * output, int *n);