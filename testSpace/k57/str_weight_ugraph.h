#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define ID_LENGTH 50
#define INFINITIVE_VALUE 1000000

typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
int addVertex(Graph graph, char *id, char *name);
char *getVertex(Graph graph, char *id);
int addEdge(Graph graph, char *v1, char *v2, double weight);
int hasEdge(Graph graph, char * v1, char * v2);
double getEdgeValue(Graph graph, char *v1, char *v2);
int outdegree(Graph graph, char *v, char output[][ID_LENGTH]);
int indegree(Graph graph, char *v, char output[][ID_LENGTH]);
void BFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *));
void DFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *));
int DAG(Graph graph);
void topologicalSort(Graph graph, char output[][ID_LENGTH], int *n);
int checkInQueue(Dllist pqueue, char *id);
double shortestPath(Graph graph, char *start, char *stop, int *length, char path[][ID_LENGTH]);