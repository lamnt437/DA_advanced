#include "jrb_wgraph.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Graph loadGraph(FILE *f){
	Graph g = createGraph();
	int numberOfVertices;
	int i;
	char temp[21];
	int temp_id;

	fscanf(f, "%d", &numberOfVertices);
	for(i = 0; i < numberOfVertices; i++){
		fscanf(f, "%d", &temp_id);
		fscanf(f, "%s", temp);
		addVertex(g, temp_id, temp);
	}

	int numberOfEdges;
	int id1, id2;
	double weight;

	fscanf(f, "%d", &numberOfEdges);
	for(i = 0; i < numberOfEdges; i++){
		fscanf(f, "%d", &id1);
		fscanf(f, "%d", &id2);
		fscanf(f, "%lf", &weight);
		addEdge(g, id1, id2, weight);
		addEdge(g, id1, id2, weight);
	}

	return g;
}

// int checkInQueue(Dllist queue, int id){
// 	Dllist dll_ptr;
// 	dll_traverse(dll_ptr, queue){
// 		if(id == jval_i(dll_ptr->val))
// 			return 1;
// 	}
// 	return 0;
// }

int main(int argc, char *argv[]){
	Graph graph;
	int i;

	if(strcmp(argv[1], "-h") == 0){
		printf("C-Advanced, HK20152\n");
	}
	else if(strcmp(argv[1], "-v") == 0){
		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		graph = loadGraph(input);
		JRB jrb_ptr;
		jrb_traverse(jrb_ptr, graph.vertices){
			printf("%d %s\n", jval_i(jrb_ptr->key), jval_s(jrb_ptr->val));
		}
	}
	else if(strcmp(argv[1], "-w") == 0){
		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		graph = loadGraph(input);
		int id1 = atoi(argv[3]);
		int id2 = atoi(argv[4]);
		int weight = getEdgeValue(graph, id1, id2);
		if(weight == 1000000)
			printf("%d\n", -1);
		else
			printf("%d\n", weight);
	}
	else if(strcmp(argv[1], "-p") == 0){
		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		graph = loadGraph(input);
		int id1 = atoi(argv[3]);
		// printf("%d\n", id1);
		int id2 = atoi(argv[4]);
		// printf("%d\n", id2);

		int id_path[100];
		int length;
		int weight;
		weight = shortestPath(graph, id1, id2, &length, id_path);
		printf("%d\n", weight);
		for(i = 0; i < length; i++){
			printf("%s\n", getVertex(graph, id_path[i]));
		}
	}
	else if(strcmp(argv[1], "-n") == 0){
		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		graph = loadGraph(input);
		int id1 = atoi(argv[3]);
		// printf("%d\n", id1);

		int output[100];
		int n = outdegree(graph, id1, output);
		printf("%d\n", n);
		for(int i = 0; i < n; i++){
			printf("%d %s %d\n", output[i], getVertex(graph, output[i]), (int) getEdgeValue(graph, id1, output[i]));
		}
	}
	else if(strcmp(argv[1], "-s") == 0){
		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		graph = loadGraph(input);

		int i = 3;
		int n = 0;
		// int set[100];
		Dllist queue = new_dllist();

		// while(argv[i] != NULL){
		// 	int id = atoi(argv[i]);
		// 	dll_append(queue, new_jval_i(id));
		// }
		for(i = 3; i < argc; i++){
			int id = atoi(argv[i]);
			dll_append(queue, new_jval_i(id));
			n++;
		}

		printf("%d\n", n);
		Dllist dll_ptr2;
		dll_traverse(dll_ptr2, queue){
			int id = jval_i(dll_ptr2->val);
			printf("%d %s\n", id, getVertex(graph, id));
		}

		int outList[100];
		char outputEdge[100][20];
		int counter = 0;
		JRB visited = make_jrb();

		while(!dll_empty(queue)){
			Dllist dequeued_node = dll_first(queue);
			int node_id = jval_i(dequeued_node->val);
			dll_delete_node(dequeued_node);

			jrb_insert_int(visited, node_id, new_jval_i(1));

			int outNumber = outdegree(graph, node_id, outList);
			for(i = 0; i < outNumber; i++){
				if(checkInQueue(queue, outList[i])){
					// printf("%d - %d\n", node_id, outList[i]);
					// printf("*");
					if(jrb_find_int(visited, outList[i]) == NULL){
						// printf("%d - %d\n", node_id, outList[i]);
						int edgeValue = (int) getEdgeValue(graph, node_id, outList[i]);
						sprintf(outputEdge[counter], "%d %d %d", node_id, outList[i], edgeValue);
						counter++;
					}
				}
			}
		}

		printf("%d\n", counter);
		for(i = 0; i < counter; i++){
			printf("%s\n", outputEdge[i]);
		}
	}
	else{
		printf("Invalid!\n");
	}

	return 0;
}