#include "int_weight_ugraph.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define NAME_LENGTH 50

Graph loadGraph(FILE *input){
	Graph graph = createGraph();

	char line[100];
	while(fgets(line, 99, input) != NULL){
		char *id_string = strtok(line, " \n");
		int id = atoi(id_string);

		char *name = strtok(NULL, " \n");
		// printf("%d - %s\n", id, name);
		addVertex(graph, id, name);
	}
	
	return graph;
}

void loadEdge(FILE *input, Graph graph){
	char line[100];
	int id_arr[100];

	while(fgets(line, 99, input) != NULL){
		int counter = 0;
		char *id_string = strtok(line, " \n");
		int id;
		while(id_string != NULL){
			id = atoi(id_string);
			id_arr[counter] = id;
			counter++;

			id_string = strtok(NULL, " \n");
		}

		for(int i = 0; i < counter; i++){
			char *name = getVertex(graph, id_arr[i]);
			printf("%s ", name);
		}
		printf("\n");

		for(int i = 0; i < counter; i++){
			for(int j = i + 1; j < counter; j++){
				addEdge(graph, id_arr[i], id_arr[j], 1);
			}
		}
	}
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
	

	if(argc != 3){
		puts("Wrong number of arguments!");
		return 1;
	}

	FILE *input_sanpham = fopen(argv[1], "r");
	if(input_sanpham == NULL){
		puts("Input san pham file doesn't exist!");
		return 2;
	}

	FILE *input_order = fopen(argv[2], "r");
	if(input_order == NULL){
		puts("Input order file doesn't exist!");
		return 2;
	}

	Graph graph = loadGraph(input_sanpham);

	int choice;
	JRB jrb_ptr, jrb_ptr1, jrb_ptr2;

	printf("\nMENU:\n\n1 - In danh sach san pham\n2 - In danh sach giao dich\n3 - Tim tinh co chuyen bay thang den\n4 - In danh sach tinh co nhieu duong bay nhat\n5 - Danh sach mon hoc\n6 - Kiem tra tinh hop le\n7 - Tim duong bay voi gia re nhat\n8 - Exit...");
	scanf("%d", &choice);

	while(choice != 8){
		switch(choice){
			case 1:
				printf("\n==In danh sach san pham==\n\n");
				jrb_traverse(jrb_ptr, graph.vertices){
					printf("Ma san pham: %d\n", jval_i(jrb_ptr->key));
					printf("Ten san pham: %s\n\n", jval_s(jrb_ptr->val));
				}
				break;

			case 2:
				printf("\n==In danh sach giao dich==\n\n");
				loadEdge(input_order, graph);
				break;

			case 3:
				printf("\n==Hien thi muc do lien quan==\n\n");
				int id1, id2;
				printf("Nhap ma san pham 1: ");
				scanf("%d", &id1);

				printf("Nhap ma san pham 2: ");
				scanf("%d", &id2);

				double weight = getEdgeValue(graph, id1, id2);
				if(weight == INFINITIVE_VALUE)
					printf("-1\n");
				else
					printf("%d\n", (int) weight);
		}

		printf("\nMENU:\n\n1 - In danh sach san pham\n2 - In danh sach giao dich\n3 - Tim tinh co chuyen bay thang den\n4 - In danh sach tinh co nhieu duong bay nhat\n5 - Danh sach mon hoc\n6 - Kiem tra tinh hop le\n7 - Tim duong bay voi gia re nhat\n8 - Exit...");
		scanf("%d", &choice);
	}

	return 0;
}