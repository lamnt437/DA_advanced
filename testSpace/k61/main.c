#include "int_weight_ugraph.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define NAME_LENGTH 50

Graph loadGraph(FILE *input, int so_loai, JRB khohang){
	Graph graph = createGraph();
	// int numberOfVertices;
	// int i;
	// char temp[21];
	// int temp_id;

	// fscanf(f, "%d", &numberOfVertices);
	// for(i = 0; i < numberOfVertices; i++){
	// 	fscanf(f, "%d", &temp_id);
	// 	fscanf(f, "%s", temp);
	// 	addVertex(g, temp_id, temp);
	// }

	// int numberOfEdges;
	// int id1, id2;
	// double weight;

	// fscanf(f, "%d", &numberOfEdges);
	// for(i = 0; i < numberOfEdges; i++){
	// 	fscanf(f, "%d", &id1);
	// 	fscanf(f, "%d", &id2);
	// 	fscanf(f, "%lf", &weight);
	// 	addEdge(g, id1, id2, weight);
	// 	addEdge(g, id1, id2, weight);
	// }

	int number_of_kho;
	char kho_name[NAME_LENGTH];
	int kho_id;
	// printf("so_loai: %d\n", so_loai);

	fscanf(input, "%d", &number_of_kho);
	for(int i = 0; i < number_of_kho; i++){
		fscanf(input, "%s", kho_name);
		
		fscanf(input, "%d", &kho_id);

		// printf("%s  %d\n", kho_name, kho_id);
		addVertex(graph, kho_id, kho_name);

		JRB tree = make_jrb();
		int id_sanpham;
		int soluong;
		for(int j = 0; j < so_loai; j++){
			fscanf(input, "%d", &id_sanpham);
			fscanf(input, "%d", &soluong);
			jrb_insert_int(tree, id_sanpham, new_jval_i(soluong));
		}
		jrb_insert_int(khohang, kho_id, new_jval_v(tree));
	}

	int number_of_ways;
	fscanf(input, "%d", &number_of_ways);
	for(int i = 0; i < number_of_ways; i++){
		int id1, id2;
		double weight;
		// printf("%d %d %lf\n", id1, id2, weight);
		fscanf(input, "%d %d %lf", &id1, &id2, &weight);
		addEdge(graph, id1, id2, weight);
	}

	return graph;
}

JRB loadSanpham(FILE *input, int *so_loai){
	JRB sanpham_table = make_jrb();

	int n_sampham;
	char name[NAME_LENGTH];
	int id;

	fscanf(input, "%d", &n_sampham);
	for(int i = 0; i < n_sampham; i++){
		fscanf(input, "%s", name);
		fscanf(input, "%d", &id);

		jrb_insert_int(sanpham_table, id, new_jval_s(strdup(name)));
	}

	*so_loai = n_sampham;
	return sanpham_table;
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
	JRB khohang = make_jrb();
	JRB sanpham_table, jrb_ptr, jrb_ptr1;
	int so_loai;
	int i;

	if(strcmp(argv[1], "-t") == 0){
		printf("C-Advanced, HK20182\n");
	}

	//LOAD SANPHAM
	else if(strcmp(argv[1], "-s") == 0){
		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		// graph = loadGraph(input);
		sanpham_table = loadSanpham(input, &so_loai);
		printf("Loai san pham:\n");

		jrb_traverse(jrb_ptr, sanpham_table){
			printf("%s %d\n", jval_s(jrb_ptr->val), jval_i(jrb_ptr->key));
		}
	}

	//LOAD KHO HANG
	else if(strcmp(argv[1], "-w") == 0){

		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		FILE *input_sanpham = fopen(argv[3], "r");
		if(input == NULL) return 2;

		sanpham_table = loadSanpham(input_sanpham, &so_loai);
		graph = loadGraph(input, so_loai, khohang);

		int id1 = atoi(argv[4]);
		int id2 = atoi(argv[5]);
		double distance = getEdgeValue(graph, id1, id2);

		if(distance == INFINITIVE_VALUE)
			printf("%d\n", -1);
		else
			printf("%d\n", (int) distance);
	}

	else if(strcmp(argv[1], "-a") == 0){

		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		FILE *input_sanpham = fopen(argv[3], "r");
		if(input == NULL) return 2;

		sanpham_table = loadSanpham(input_sanpham, &so_loai);
		graph = loadGraph(input, so_loai, khohang);

		jrb_traverse(jrb_ptr, khohang){
			int kho_id = jval_i(jrb_ptr->key);
			char *kho_name = getVertex(graph, kho_id);
			printf("%s\n", kho_name);

			JRB tree = (JRB)jval_v(jrb_ptr->val);
			jrb_traverse(jrb_ptr1, tree){
				int hang_id = jval_i(jrb_ptr1->key);
				char *hang_name = jval_s(jrb_val(jrb_find_int(sanpham_table, hang_id)));
				printf("%s %d\n", hang_name, jval_i(jrb_ptr1->val));
			}
			printf("----\n");
		}
	}

	else if(strcmp(argv[1], "-h") == 0){
		FILE *input = fopen(argv[2], "r");
		if(input == NULL) return 1;

		FILE *input_sanpham = fopen(argv[3], "r");
		if(input == NULL) return 2;

		sanpham_table = loadSanpham(input_sanpham, &so_loai);
		graph = loadGraph(input, so_loai, khohang);

		int hang_id = atoi(argv[4]);
		int kho_id = atoi(argv[5]);

		//kt kho kho_id
		JRB kho_ptr = jrb_find_int(khohang, kho_id);
		char *kho_name = getVertex(graph, kho_id);

		printf("%s\n", kho_name);
		//lay ten hang_id
		JRB hang_name_ptr = jrb_find_int(sanpham_table, hang_id);
		char *hang_name = jval_s(hang_name_ptr->val);
		printf("%s ", hang_name);

		//tim hang hang_id
		JRB hang_ptr = jrb_find_int((JRB) jval_v(kho_ptr->val), hang_id);
		printf("%d\n", jval_i(hang_ptr->val));

		//lay danh sach kho ke
		int adjList[100];
		int n_adj = outdegree(graph, kho_id, adjList);
		printf("---Cac kho ke la:\n");
		for(int i = 0; i < n_adj; i++){
			//lay ten
			kho_id = adjList[i];
			kho_ptr = jrb_find_int(khohang, kho_id);
			kho_name = getVertex(graph, kho_id);
			printf("%s\n", kho_name);

			//lay hang
			printf("%s ", hang_name);
			hang_ptr = jrb_find_int((JRB) jval_v(kho_ptr->val), hang_id);
			printf("%d\n", jval_i(hang_ptr->val));
		}
	}

	/*
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

	*/

	return 0;
}