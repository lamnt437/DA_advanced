#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_weight_ugraph.h"

int number_of_vertices = 0;
int number_of_edges = 0;


Graph loadGraph(FILE *input){
	Graph graph = createGraph();

	char line[100];
	while(fgets(line, 99, input) != NULL){
		int is_define = 0;
		int i = 0;
		while(line[i] != '\0'){
			if(line[i] == '='){
				is_define = 1;
				break;
			}
			i++;
		}

		if(is_define){
			//get id
			char id[ID_LENGTH];
			i = 0;
			while(line[i] != '='){
				id[i] = line[i];
				i++;
			}
			id[i] = '\0';

			//get name
			char *name_string = &line[i + 2];
			char *name = strdup(strtok(name_string, "\"\n"));

			//add vertex
			number_of_vertices += addVertex(graph, id, name);
		}
		else{
			char *id1 = strdup(strtok(line, " \n"));
			char *id2 = strdup(strtok(NULL, " \n"));
			char *weight_string = strdup(strtok(NULL, " \n"));
			double weight = atof(weight_string);

			number_of_edges += addEdge(graph, id1, id2, weight);
		}
	}

	return graph;
}

int listMostEdge(Graph graph, char output[][ID_LENGTH]){
	JRB jrb_ptr;

	//find max
	int max = 0;
	char adjList[100][ID_LENGTH];
	jrb_traverse(jrb_ptr, graph.vertices){
		char *id = jval_s(jrb_ptr->key);
		int number = outdegree(graph, id, adjList);
		if(number > max)
			max = number;
	}

	int counter = 0;
	jrb_traverse(jrb_ptr, graph.vertices){
		char *id = jval_s(jrb_ptr->key);
		int number = outdegree(graph, id, adjList);
		if(number == max){
			strcpy(output[counter], id);
			counter++;
		}
	}

	return counter;
}

char *getId(Graph graph, char *name){
	JRB jrb_ptr;
	jrb_traverse(jrb_ptr, graph.vertices){
		if(strcmp(jval_s(jrb_ptr->val), name) == 0)
			return strdup(jval_s(jrb_ptr->key));
	}
	return NULL;
}

int maxConnected(Graph g, char *id, char output[][ID_LENGTH]){
    JRB ptr;
    char path[100][ID_LENGTH];
    int length;
    int counter = 0;
    double findPath = 0;

    jrb_traverse(ptr, g.vertices){
        char *vertex = jval_s(ptr->key);
        // if(strcmp(vertex, id) == 0)
        //     continue;
        // else{
        findPath = shortestPath(g, vertex, id, &length, path);
        if(findPath < INFINITIVE_VALUE){
            strcpy(output[counter], vertex);
            counter++;
        }
        // }
    }
    return counter;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		puts("Wrong number of arguments!");
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	if(input == NULL){
		puts("Input file doesn't exist!");
		return 2;
	}

	// FILE *input = fopen("demo.txt", "r");

	Graph graph = loadGraph(input);
	fclose(input);

	int choice;
	JRB jrb_ptr1, jrb_ptr2;

	printf("\nMENU:\n\n1 - In thong tin chuyen bay\n2 - In so diem di, so duong bay\n3 - Tim tinh co chuyen bay thang den\n4 - In danh sach tinh co nhieu duong bay nhat\n5 - Danh sach mon hoc\n6 - Kiem tra tinh hop le\n7 - Tim duong bay voi gia re nhat\n8 - Exit...");
	scanf("%d", &choice);

	while(choice != 8){
		switch(choice){
			case 1:
				printf("\n==In thong tin chuyen bay==\n\n");
				jrb_traverse(jrb_ptr1, graph.edges){
					char *start = jval_s(jrb_ptr1->key);
					JRB tree = (JRB) jval_v(jrb_ptr1->val);
					jrb_traverse(jrb_ptr2, tree){
						char *end = jval_s(jrb_ptr2->key);
						double fee = jval_d(jrb_ptr2->val);

						printf("%s %s %.1lf\n", start, end, fee);
					}
				}
				
				break;

			case 2:
				printf("\n==In so diem di, so duong bay==\n\n");
				printf("So diem di: %d\n", number_of_vertices);
				printf("So duong bay: %d\n\n", number_of_edges);
				break;

			case 3:
				printf("\n==Tim tinh co chuyen bay thang den==\n\n");
				getchar();
				char chosen_name[ID_LENGTH];
				printf("Nhap ten tinh: ");
				fgets(chosen_name, ID_LENGTH - 1, stdin);
				if(chosen_name[strlen(chosen_name) - 1] == '\n')
					chosen_name[strlen(chosen_name) - 1] = '\0';

				char *chosen_id = getId(graph, chosen_name);

				if(chosen_id == NULL){
					printf("Khong ton tai tinh nay!\n");
				}

				else{
					char adjList[100][ID_LENGTH];
					int number_of_adj = outdegree(graph, chosen_id, adjList);

					printf("\nCac tinh co chuyen bay thang den %s:\n", chosen_name);
					for(int i = 0; i < number_of_adj; i++){
						printf("%s\n", getVertex(graph, adjList[i]));
					}
				}
				break;

			case 4:
				printf("\n==In danh sach tinh co nhieu duong bay nhat==\n\n");
				char maxList[100][ID_LENGTH];
				int number = listMostEdge(graph, maxList);
				printf("So duong bay: %d\n", number);
				for(int i = 0; i < number; i++){
					printf("%s\n", getVertex(graph, maxList[i]));
				}

				break;

			case 5:
				printf("\n==Tim duong bay giua 2 tinh==\n\n");
				getchar();
				char chosen_name1[ID_LENGTH];
				printf("Nhap ten tinh 1: ");

				fgets(chosen_name1, ID_LENGTH - 1, stdin);
				if(chosen_name1[strlen(chosen_name1) - 1] == '\n')
					chosen_name1[strlen(chosen_name1) - 1] = '\0';
				char *chosen_id1 = getId(graph, chosen_name1);

				char chosen_name2[ID_LENGTH];
				printf("Nhap ten tinh 2: ");
				fgets(chosen_name2, ID_LENGTH - 1, stdin);
				if(chosen_name2[strlen(chosen_name2) - 1] == '\n')
					chosen_name2[strlen(chosen_name2) - 1] = '\0';
				char *chosen_id2 = getId(graph, chosen_name2);

				char path[100][ID_LENGTH];
				int length;

				printf("%s - %s\n", chosen_id1, chosen_id2);
				double cost = shortestPath(graph, chosen_id1, chosen_id2, &length, path);

				if(cost == INFINITIVE_VALUE){
					printf("Khong co duong bay giua 2 tinh nay!\n");
				}
				else{
					printf("Duong bay:\n");
					for(int i = 0; i < length; i++){
						printf("%s  ", getVertex(graph, path[i]));
					}
					printf("\n");
				}
				
				break;

			case 6:
				printf("\n==In thanh phan lien thong lon nhat==\n\n");
				getchar();
				char input_name[ID_LENGTH];
				printf("Nhap ten tinh: ");
				fgets(input_name, ID_LENGTH - 1, stdin);
				if(input_name[strlen(input_name) - 1] == '\n')
					input_name[strlen(input_name) - 1] = '\0';
				char *input_id = getId(graph, input_name);

				char max_connect[100][ID_LENGTH];
				int max_connect_counter = maxConnected(graph, input_id, max_connect);
				printf("Thanh phan lien thong lon nhat:\n");
				for(int i = 0; i < max_connect_counter; i++){
					printf("%s  ", getVertex(graph, max_connect[i]));
				}

				break;

			case 7:
				printf("\n==Tim duong bay voi gia re nhat==\n\n");

				char input_id1[ID_LENGTH], input_id2[ID_LENGTH];
				printf("Nhap ma tinh 1: ");
				scanf("%s", input_id1);

				printf("Nhap ma tinh 2: ");
				scanf("%s", input_id2);

				char flight_path[100][ID_LENGTH];
				int flight_length;

				printf("%s - %s\n", input_id1, input_id2);
				double flight_cost = shortestPath(graph, input_id1, input_id2, &length, path);

				if(flight_cost == INFINITIVE_VALUE){
					printf("Khong co duong bay giua 2 tinh nay!\n");
				}
				else{
					printf("Duong bay:\n");
					for(int i = 0; i < length; i++){
						printf("%s  ", getVertex(graph, path[i]));
					}
					printf("\nGia ve: %.1lf\n", flight_cost);
				}
		}

		printf("\nMENU:\n\n1 - In thong tin chuyen bay\n2 - In so diem di, so duong bay\n3 - Tim tinh co chuyen bay thang den\n4 - In danh sach tinh co nhieu duong bay nhat\n5 - Danh sach mon hoc\n6 - Kiem tra tinh hop le\n7 - Tim duong bay voi gia re nhat\n8 - Exit...");
		scanf("%d", &choice);
	}

	return 0;
}