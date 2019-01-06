#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define ID_LENGTH 50
// typedef JRB Graph;
typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
int addVertex(Graph graph, char *id, char *name);
char *getVertex(Graph graph, char *id);
int addEdge(Graph graph, char * v1, char * v2);
int hasEdge(Graph graph, char * v1, char * v2);
int outdegree(Graph graph, char *v, char output[][ID_LENGTH]);
int indegree(Graph graph, char *v, char output[][ID_LENGTH]);
void DFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *));
void BFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *));
int DAG(Graph graph);
void dropGraph(Graph graph);
void topologicalSort(Graph graph, char output[][ID_LENGTH], int *n);