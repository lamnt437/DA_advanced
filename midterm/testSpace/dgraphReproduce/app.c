#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jrb_dgraph.h"
#include "libfdr/dllist.h"

int inputGraph(Graph g, char *filename){
    FILE *input = fopen(filename, "r");
    if(input == NULL){
        printf("Input file doesn't exist!\n");
        return 0;
    }

    char line[100];
    char *temp;

    //read vertices
    char name[100];
    int numberOfVertices;
    fscanf(input, "%d\n", &numberOfVertices);
    int i;
    for(i = 0; i < numberOfVertices; i++){
        fgets(line, 99, input);
        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        temp = strtok(line, " \t");
        int id = atoi(temp);
        temp = strtok(NULL, " \t");
        strcpy(name, temp);

        addVertex(g, id, name);
    }

    //read edges
    int numberOfEdges;
    fscanf(input, "%d\n", &numberOfEdges);
    for(i = 0; i < numberOfEdges; i++){
        fgets(line, 99, input);
        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        temp = strtok(line, " \t");
        int v1 = atoi(temp);
        temp = strtok(NULL, " \t");
        int v2 = atoi(temp);

        addEdge(g, v1, v2);
    }

    fclose(input);
    return 1;
}

int main(int argc, char *argv[]){
	// Graph g = createGraph();
	// int x;
	// int n;
	// int output[100];

 //    addVertex(g, 0, "V0");
 //    addVertex(g, 1, "V1");
 //    addVertex(g, 2, "V2");
 //    addVertex(g, 3, "V3");
 //    addEdge(g, 0, 1);
 //    addEdge(g, 1, 2);
 //    // addEdge(g, 2, 0);
 //    addEdge(g, 1, 3);
 //    if (DAG(g)) printf("The graph is acycle\n");
 //    else printf("Have cycles in the graph\n");
 //    printf("Find number of outdegree: ");
 //    scanf("%d", &x);
 //    n = outdegree(g, x, output);
 //    int i;
 //    printf("\n%d:\n", n);
 //    for(i = 0; i < n; i++){
 //    	printf("%d ", output[i]);
 //    }
 //    printf("\n");

 //    printf("Find number of indegree: ");
 //    scanf("%d", &x);
 //    n = indegree(g, x, output);
 //    printf("\n%d:\n", n);
 //    for(i = 0; i < n; i++){
 //    	printf("%d ", output[i]);
 //    }
 //    printf("\n");

    if(argc != 2){
        puts("Wrong number of arguments!");
        return 1;
    }

    int n, i;
    int output[100];
    Graph g = createGraph();
    inputGraph(g, argv[1]);
    if(DAG(g)){
        topologicalSort(g, output, &n);
        printf("The topological order:\n");
        for (i=0; i<n; i++)
             printf("%s\n", getVertex(g, output[i]));
    }
    else{
        printf("Can not make topological sort\n"); 
    }

    dropGraph(g);

    return 0;
}