#include "jrb_graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 100
#define NAME_LENGTH 30

// typedef JRB Graph;

// Graph createGraph();
// void addEdge(Graph graph, int v1, int v2);
// int adjacent(Graph graph, int v1, int v2);
// int getAdjacentVertices (Graph graph, int v, int* output);
// void dropGraph(Graph graph);

void read_metro_line(Graph g, char *line);
char * trim_string(char str[]);

int main(int argc, char *argv[]){
    //open file
    if(argc != 2){
    	printf("Wrong number of arguments!\n");
    	exit(1);
    }

    FILE *input_file = fopen(argv[1], "r");
    if(input_file == NULL){
    	printf("Coundn't open file!\n");
    	exit(2);
    }

    Graph g = createGraph();

	//read name of station
	char station_names[SIZE][NAME_LENGTH];
	int number_of_stations = 0;
	char line[100];
	char *temp = NULL;
	while(fgets(line, 99, input_file) != NULL){
		line[strlen(line) - 1] = '\0';
		if(strcmp(line, "[STATIONS]") == 0)
			continue;
		if(strcmp(line, "[LINES]") == 0)
			break;
		temp = strtok(line, "=");
		temp = strtok(NULL, "=");
		strcpy(station_names[number_of_stations++], temp);
	}

	//read metro line
	int number_of_lines = 0;
	while(fgets(line, 99, input_file) != NULL){		
		line[strlen(line) - 1] = '\0';
		temp = strtok(line, "=");
		temp = strtok(NULL, "=");
		read_metro_line(g, temp);
		number_of_lines++;
	}

	fclose(input_file);

	//check adjacent
	int choice, n;
	int output[100];

	printf("Enter station or -1 to end: ");
	scanf("%d", &choice);

	while(choice != -1){
		if(choice <= number_of_stations && choice > 0){
			int station_index = choice - 1;
			n = getAdjacentVertices(g, station_index, output);
			printf("Adjacent stations of station %s: ", station_names[station_index]);
			for(int i = 0; i < n; i++){
				printf("%d ", output[i] + 1);
			}
			printf("\n");
		}
		else{
			printf("Station doesn't exist!\n");
		}

		printf("Enter station or -1 to end: ");
		scanf("%d", &choice);
	}

	dropGraph(g);
	
	return 0;
}

char * trim_string(char str[]){
	//trim right
	if(strlen(str) <= 0)
		return str;

	int i = strlen(str) - 1;
	while(isspace(str[i]))
		i--;
	str[i + 1] = '\0';

	//trim left;
	i = 0;
	while(isspace(str[i]))
		i++;
	return &str[i];
}

void read_metro_line(Graph g, char *line){
	int prev = 0;
	int cur = 0;

	char line_cpy[100];
	strcpy(line_cpy, line);

	char *temp = strtok(line_cpy, " ");

	while(temp != NULL){
		cur = atoi(&temp[1]);

		//add edge to graph
		if(prev != 0){
			addEdge(g, cur - 1, prev - 1);
		}

		prev = cur;
		temp = strtok(NULL, " ");
	}
}