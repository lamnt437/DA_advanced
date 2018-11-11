#include "libfdr/jrb.h"

typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
void addVertex(Graph graph, char *id, char *name);
char *getVertex(Graph graph, char *id);
void addEdge(Graph graph, char * v1, char * v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices (Graph graph, char *v, char output[][5]);
void dropGraph(Graph graph);
void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));
int shortestPath(Graph graph, int start, int stop, int *path);