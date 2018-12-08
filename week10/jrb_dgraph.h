#include "libfdr/jrb.h"
#define INFINITIVE_VALUE 1000000

typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
void addVertex(Graph graph, char *id, int value);
int getVertex(Graph graph, char *id);
int addEdge(Graph graph, char * v1, char * v2, int value);
int getEdgeValue(Graph graph, char * v1, char * v2);
// int adjacent(Graph graph, int v1, int v2);
// int getAdjacentVertices (Graph graph, char *v, char output[][5]);
int outdegree(Graph graph, char *v, char output[][50]);
void dropGraph(Graph graph);
void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));
int shortestPath(Graph graph, char * start, char * stop, char path[][5]);
