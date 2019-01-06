#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_weight_dgraph.h"

int number_of_vertices = 0;
int number_of_edges = 0;

// double longestPath(Graph graph, char *start, char *stop, int *length, char path[][ID_LENGTH]);

char *findMinus(char *string){
	int i = 0;
	while(string[i] != '\0'){
		// printf("*");
		if(string[i] == '-')
			break;
		i++;
	}
	if(string[i] == '-')
		return &string[i];
	return NULL;
}

Graph loadGraph(FILE *input){
	Graph graph = createGraph();

	char line[100];
	while(fgets(line, 99, input) != NULL){
		char *current_job = strdup(strtok(line, " :"));
		number_of_vertices += addVertex(graph, current_job, current_job);

		char *next_string = NULL;
		char required_job[ID_LENGTH];
		int required_weight;

		while((next_string = strtok(NULL, " :\n")) != NULL){
			char temp1, temp2;
			sscanf(next_string, "%c%c-%d", &temp1, &temp2, &required_weight);
			sprintf(required_job, "%c%c", temp1, temp2);

			// printf("required_weight: %d\n", required_weight);
			number_of_vertices += addVertex(graph, required_job, required_job);
			number_of_edges += addEdge(graph, required_job, current_job, required_weight);
		}
	}

	return graph;
}

int findPrevious(Graph graph, char * start, char list[][ID_LENGTH]){
    JRB visited = make_jrb();
    Dllist queue = new_dllist();
    JRB start_node = jrb_find_str(graph.vertices, start);

    int counter = 0;

    if(start_node != NULL){
    	dll_append(queue, new_jval_s(strdup(start)));
        while(!dll_empty(queue)){
            Dllist node = dll_first(queue);
            char *v = strdup(jval_s(node->val));
            dll_delete_node(node);

            if(jrb_find_str(visited, v) == NULL){
                strcpy(list[counter], v);
            	counter++;
                jrb_insert_str(visited, strdup(v), new_jval_i(1));
            }

            char output[100][ID_LENGTH];
            int n = indegree(graph, v, output);
            int i;
            for(i = 0; i < n; i++){
                if(jrb_find_str(visited, output[i]) == NULL){
                    dll_append(queue, new_jval_s(strdup(output[i])));
                }
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(queue);

    return counter;
}

double findMinimumWeight(Graph graph, char *chosen_job){
	double minWeight = INFINITIVE_VALUE;

	char output[100][ID_LENGTH];
	int job_counter;
	topologicalSort(graph, output, &job_counter);

	//shift by 1
	char procedure[100][ID_LENGTH];
	for(int i = 0; i < job_counter; i++){
		strcpy(procedure[i + 1], output[i]);
	}

	//list of nodes with indegree = 0;
	int list0_counter = 0;
	char list0[100][ID_LENGTH];
	JRB jrb_ptr;
	jrb_traverse(jrb_ptr, graph.vertices){
		char *job_considering = jval_s(jrb_ptr->key);
		char small_in_list[100][ID_LENGTH];
		int in_number = indegree(graph, job_considering, small_in_list);
		if(in_number == 0){
			strcpy(list0[list0_counter], job_considering);
			list0_counter++;
		}
	}

	//add a virtual node at the beginning
	strcpy(procedure[0], "A0");
	addVertex(graph, "A0", "A0");
	for(int i = 0; i < list0_counter; i++){
		addEdge(graph, "A0", list0[i], 0);
	}

	//init
	JRB distance = make_jrb();
	jrb_insert_str(distance, "A0", new_jval_d(0));
	for(int i = 1; i <= job_counter; i++){
		double d = getEdgeValue(graph, "A0", procedure[i]);
		jrb_insert_str(distance, strdup(procedure[i]), new_jval_d(d));
	}

	//relax
	for(int i = 1; i <= job_counter; i++){		
		char *v = procedure[i];
		char outList[100][ID_LENGTH];
		int outNumber = outdegree(graph, v, outList);

		for(int j = 0; j < outNumber; j++){
			JRB current_value_ptr = jrb_find_str(distance, outList[j]);
			double current_value = jval_d(jrb_val(current_value_ptr)); //= INFINITE
			double temp_value = jval_d(jrb_val(jrb_find_str(distance, v))) + getEdgeValue(graph, v, outList[j]); //>= INFINITE
			if(current_value == INFINITIVE_VALUE){
				if(temp_value < INFINITIVE_VALUE){
					current_value_ptr->val = new_jval_d(temp_value);
				}
			}
			else{
				if(temp_value < INFINITIVE_VALUE){
					if(temp_value > current_value){
						current_value_ptr->val = new_jval_d(temp_value);
					}
				}
			}
		}
	}

	//delete virtual node 0
	JRB find_node0 = jrb_find_str(graph.vertices, "A0");
	jrb_delete_node(find_node0);
	find_node0 = jrb_find_str(graph.edges, "A0");
	jrb_delete_node(find_node0);

	minWeight = jval_d(jrb_val(jrb_find_str(distance, chosen_job)));
	return minWeight;
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

	printf("MENU:\n\n1 - In so nut, so canh\n2 - Number of prerequisite jobs\n3 - Number of prerequisite subjects\n4 - In trinh tu\n5 - Danh sach mon hoc\n6 - Kiem tra tinh hop le\n7 - Exit...");
	scanf("%d", &choice);

	while(choice != 7){
		switch(choice){
			case 1:
				printf("\n==In so nut, so canh==\n\n");
				printf("So dinh: %d\n", number_of_vertices);
				printf("So canh: %d\n\n", number_of_edges);
				break;

			case 2:
				printf("\n==Number of prerequisite jobs==\n\n");
				int repeat_choice;
				do{
					printf("Nhap cong viec: ");
					char name[100];
					
					scanf("%s", name);

					JRB jrb_ptr = jrb_find_str(graph.vertices, name);
					if(jrb_ptr == NULL)
						printf("Cong viec khong co trong chuong trinh!\n");
					else{
						char inList[100][ID_LENGTH];
						char previousList[100][ID_LENGTH];
						int number_of_required_jobs = indegree(graph, name, inList);
						printf("So cong viec phai lam ngay truoc la: %d\n", number_of_required_jobs);
						for(int i = 0; i < number_of_required_jobs; i++){
							printf("%s ", inList[i]);
						}
						printf("\n");

						int number_of_previous_jobs = findPrevious(graph, name, previousList);
						printf("So cong viec phai lam truoc la: %d\n", number_of_previous_jobs - 1);
						for(int i = 1; i < number_of_previous_jobs; i++){
							printf("%s ", previousList[i]);
						}
						printf("\n");
					}
					
					printf("Co muon tim tiep khong?(1 - co, 0 - khong)...");
					scanf("%d", &repeat_choice);
				}while(repeat_choice != 0);

			case 4:
				printf("\n==In trinh tu==\n\n");
				int number_of_jobs;
				char output[100][ID_LENGTH];
				topologicalSort(graph, output, &number_of_jobs);
				for(int i = 0; i < number_of_jobs; i++){
					if(i < number_of_jobs - 1)
						printf("%s => ", output[i]);
					else{
						printf("%s\n", output[i]);
					}
				}
				printf("\n");
				break;

			case 5:
				printf("\n==Tim thoi gian toi thieu==\n\n");
				printf("Nhap cong viec: ");
				char chosen_job[100];
					
				scanf("%s", chosen_job);
				JRB jrb_ptr = jrb_find_str(graph.vertices, chosen_job);
				if(jrb_ptr == NULL)
					printf("Cong viec khong co trong chuong trinh!\n");
				else{
					printf("Thoi gian toi thieu: %d\n", (int) findMinimumWeight(graph, chosen_job));
				}

				break;

			case 6:
				printf("\n==Kiem tra tinh hop le==\n\n");
				if(DAG(graph))
					printf("Do thi hop le (khong co chu trinh)!\n\n");
				else{
					printf("Do thi khong hop le!\n\n");
				}
				break;
		}

		printf("MENU:\n\n1 - In so nut, so canh\n2 - Number of prerequisite jobs\n3 - Number of prerequisite subjects\n4 - In trinh tu\n5 - Danh sach mon hoc\n6 - Kiem tra tinh hop le\n7 - Exit...");
		scanf("%d", &choice);
	}

	return 0;
}

// /* find shortest path */

// char *maxdequeue(Dllist pqueue, JRB value_map){	//dequeue node with max value
// 	double max_value = -1;
// 	double current_value;

// 	Dllist dll_ptr, max_node_ptr;
// 	JRB jrb_ptr;

// 	dll_traverse(dll_ptr, pqueue){
// 		char *id = jval_s(dll_ptr->val);
// 		jrb_ptr = jrb_find_str(value_map, id);
// 		current_value = jval_d(jrb_ptr->val);
// 		if(current_value > max_value){
// 			max_node_ptr = dll_ptr;
// 			max_value = current_value;
// 		}
// 	}

// 	char *dequeued_id = (char *)malloc(sizeof(char) * ID_LENGTH);
// 	strcpy(dequeued_id, jval_s(max_node_ptr->val));
// 	dll_delete_node(max_node_ptr);

// 	return dequeued_id;
// }

// double longestPath(Graph graph, char *start, char *stop, int *length, char path[][ID_LENGTH]){
// 	*length = 0;
// 	JRB start_ptr = jrb_find_str(graph.vertices, start);
// 	if(start_ptr == NULL) return INFINITIVE_VALUE;

// 	//init
// 	Dllist pqueue = new_dllist();
// 	JRB visited = make_jrb();
// 	JRB value_map = make_jrb();
// 	JRB parent_map = make_jrb();

// 	//enqueue start node
// 	jrb_insert_str(value_map, strdup(start), new_jval_d(0));
// 	jrb_insert_str(parent_map, strdup(start), new_jval_s(start));
// 	dll_append(pqueue, new_jval_s(strdup(start)));

// 	char *parent_id;

// 	while(!dll_empty(pqueue)){
// 		//get parent id
// 		parent_id = maxdequeue(pqueue, value_map);
// 		jrb_insert_str(visited, strdup(parent_id), new_jval_i(1));

// 		if(strcmp(parent_id, stop) == 0) break;

// 		//get parent value
// 		JRB parent_value_ptr = jrb_find_str(value_map, parent_id);
// 		double parent_value = jval_d(parent_value_ptr->val);

// 		//get outlist of parent node
// 		char outlist[100][ID_LENGTH];
// 		int number_of_children = outdegree(graph, parent_id, outlist);

// 		//enqueue children
// 		for(int i = 0; i < number_of_children; i++){
// 			char *child_id = outlist[i];

// 			//find if child is visited
// 			JRB find_child = jrb_find_str(visited, child_id);
// 			if(find_child != NULL) continue;
			
// 			//enqueue child
// 			if(!checkInQueue(pqueue, child_id))
// 				dll_append(pqueue, new_jval_s(strdup(child_id)));

// 			//relax
// 			double temp_value = parent_value + getEdgeValue(graph, parent_id, child_id);
// 			JRB child_value_ptr = jrb_find_str(value_map, child_id);
// 			if(child_value_ptr == NULL){
// 				jrb_insert_str(value_map, strdup(child_id), new_jval_d(temp_value));
// 				jrb_insert_str(parent_map, strdup(child_id), new_jval_s(parent_id));
// 			}
// 			else{
// 				double child_value = jval_d(child_value_ptr->val);
// 				if(temp_value > child_value){
// 					child_value_ptr->val = new_jval_d(temp_value);
// 					JRB child_parent_ptr = jrb_find_str(parent_map, child_id);
// 					child_parent_ptr->val = new_jval_s(strdup(parent_id));
// 				}
// 			}
// 		}
// 	}

// 	if(strcmp(parent_id, stop) != 0) return INFINITIVE_VALUE;

// 	// //print value map
// 	// JRB value_ptr;
// 	// jrb_traverse(value_ptr, value_map){
// 	// 	printf("%s: %lf\n", jval_s(value_ptr->key), jval_d(value_ptr->val));
// 	// }

// 	//get path weight
// 	JRB find_value = jrb_find_str(value_map, parent_id);
// 	double path_weight = jval_d(find_value->val);

// 	//write path
// 	int counter = 0;
// 	char *current_id = parent_id;
// 	while(1){
// 		strcpy(path[counter], current_id);
// 		counter++;
// 		if(strcmp(current_id, start) == 0)
// 			break;
// 		current_id = jval_s(jrb_val(jrb_find_str(parent_map, current_id)));
// 	}

// 	//reverse path
// 	int i = 0, j = counter - 1;
// 	char temp[ID_LENGTH];

// 	while(i < j){
// 		strcpy(temp, path[i]);
// 		strcpy(path[i], path[j]);
// 		strcpy(path[j], temp);
// 		i++;
// 		j--;
// 	}

// 	*length = counter;
// 	return path_weight;
// }

// /* end shortest path */