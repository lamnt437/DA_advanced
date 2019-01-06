#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
// typedef JRB Graph;
typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
int addVertex(Graph graph, int id, char *name);
char *getVertex(Graph graph, int id);
int addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
int outdegree(Graph graph, int v, int* output);
int indegree(Graph graph, int v, int* output);
void DFS(Graph graph, int start, int stop, void (*func)(Graph, int));
void BFS(Graph graph, int start, int stop, void (*func)(Graph,int));
double shortestPath(Graph graph, int s, int t, int *length, int *path);