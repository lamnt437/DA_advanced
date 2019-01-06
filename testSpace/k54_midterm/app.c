#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb_graph.h"
#include "libfdr/dllist.h"

void printVertex(int v){
    printf("%d  ", v);
}

int inputGraph(Graph g, char *filename, int *row, int *col){
    FILE *input = fopen(filename, "r");
    if(input == NULL){
        printf("input file doesn't exist!\n");
        return 0;
    }

    int hang, cot = 0;
    int size;
    char line[100];
    int vertexCounter = 0;

    //read size;
    fscanf(input, "%d\n", &size);

    //read matrix
    for(hang = 0; hang < size; hang++){
        fgets(line, 99, input);
        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        char id[3];
        char *temp = strtok(line, " \t");
        cot = 0;

        if(strcmp(temp, "0") == 0){
            sprintf(id, "%.2d", (hang + 1) * 10 + (cot + 1));
            addVertex(g, id, id);
            // printf("%s ", id);
            vertexCounter++;
        }

        for(cot = 1; cot < size; cot++){
            temp = strtok(NULL, " \t");
            if(strcmp(temp, "0") == 0){
                sprintf(id, "%.2d", (hang + 1) * 10 + (cot + 1));
                addVertex(g, id, id);
                // printf("%s ", id);
                vertexCounter++;
            }
        }
    }

    *row = size;
    *col = size;
    return vertexCounter;
}

int inputEdges(Graph g, int hang, int cot){
    JRB ptr;

    char *strId;
    int targetHang;
    int targetCot;
    char targetId[3];
    JRB node;

    int counter = 0;

    //0 <= i < hang
    //0 <= j < cot
    jrb_traverse(ptr, g.vertices){
        strId = jval_s(ptr->key);
        int index = atoi(strId);
        // printf("%s", strId);
        // i = strId[0];
        // char iStr[2];
        // iStr[0] = i;
        // iStr[1] = '\0';
        int iInt = index / 10;
        // printf("%d", iInt);

        // j = strId[1];
        // char jStr[2];
        // jStr[0] = j;
        // jStr[1] = '\0';
        int jInt = index % 10;
        // printf("%d\n", jInt);

        //up
        targetHang = iInt - 1;
        targetCot = jInt;
        if(targetHang >= 1 && targetHang <= hang){
            if(targetCot >= 1 && targetCot <= cot){
                // targetId[0] = targetHang + '0';
                // targetId[1] = targetCot + '0';
                // targetId[2] = '\0';
                sprintf(targetId, "%.2d", targetHang * 10 + targetCot);
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    counter += addEdge(g, strId, targetId);
                }
            }
        }

        //down
        targetHang = iInt + 1;
        targetCot = jInt;
        if(targetHang >= 1 && targetHang <= hang){
            if(targetCot >= 1 && targetCot <= cot){
                // targetId[0] = targetHang + '0';
                // targetId[1] = targetCot + '0';
                // targetId[2] = '\0';
                sprintf(targetId, "%.2d", targetHang * 10 + targetCot);
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    counter += addEdge(g, strId, targetId);
                }
            }
        }

        //left
        targetHang = iInt;
        targetCot = jInt - 1;
        if(targetHang >= 1 && targetHang <= hang){
            if(targetCot >= 1 && targetCot <= cot){
                // targetId[0] = targetHang + '0';
                // targetId[1] = targetCot + '0';
                // targetId[2] = '\0';
                sprintf(targetId, "%.2d", targetHang * 10 + targetCot);
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    counter += addEdge(g, strId, targetId);
                }
            }
        }

        //right
        targetHang = iInt;
        targetCot = jInt + 1;
        if(targetHang >= 1 && targetHang <= hang){
            if(targetCot >= 1 && targetCot <= cot){
                // targetId[0] = targetHang + '0';
                // targetId[1] = targetCot + '0';
                // targetId[2] = '\0';
                sprintf(targetId, "%.2d", targetHang * 10 + targetCot);
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    counter += addEdge(g, strId, targetId);
                }
            }
        }
    }

    return counter;
}

int gateCount(Graph g, int size, char output[][5]){
    JRB ptr;
    int counter = 0;
    char *id;
    char leftBound = '1';
    char rightBound = size + '0';

    jrb_traverse(ptr, g.vertices){
        id = jval_s(ptr->key);
        if(id[0] == leftBound ||
            id[0] == rightBound ||
            id[1] == leftBound ||
            id[1] == rightBound){
            strcpy(output[counter], id);
            counter++;
        }
    }
    return counter;
}

int isWalkable(Graph g, char *id){
    JRB ptr = jrb_find_str(g.vertices, id);
    if(ptr == NULL)
        return 0;
    return 1;
}

int countConnect(Graph g, char *id, char output[][5]){
    JRB ptr;
    char path[100][5];
    int counter = 0;
    int findPath = 0;

    jrb_traverse(ptr, g.vertices){
        char *vertex = jval_s(ptr->key);
        if(strcmp(vertex, id) == 0)
            continue;
        else{
            findPath = shortestPath(g, vertex, id, path);
            if(findPath != 0){
                strcpy(output[counter], vertex);
                counter++;
            }
        }
    }
    return counter;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Wrong number of arguments!\n");
        return 1;
    }

    Graph g = createGraph();

    int hang;
    int cot;
    int size;
    // char strId[3];
    int i;
    int numberOfGates;
    char listOfGates[100][5];

    int numberOfVertices = inputGraph(g, argv[1], &hang, &cot);
    if(numberOfVertices == 0){
        return 2;
    }

    int numberOfEdges = inputEdges(g, hang, cot);
    size = hang;

    int choice;
	printf("\nMENU\n\n1 - Number of Vertices and Edges\n2 - Number of Gates\n3 - Number of Isles\n4 - Connected cells\n5 - Check if treasure is reachable\n6 - Exit\n...");
    scanf("%d", &choice);

    while(choice != 6){
        switch(choice){
            case 1:
                // printf("\nMatrix\n");
                // for(i = 1; i <= hang; i++){
                //     for(j = 1; j <= cot; j++){
                //         strId[0] = i + '0';
                //         strId[1] = j + '0';
                //         strId[2] = '\0';
                //         JRB node = jrb_find_str(g.vertices, strId);
                //         if(node != NULL)
                //             printf("0 ");
                //         else
                //             printf("1 ");
                //     }
                //     printf("\n");
                // }
                printf("\n*Number of Vertices: %d\n", numberOfVertices);
                printf("*Number of Edges: %d\n", numberOfEdges);
                break;

            case 2:
                numberOfGates = gateCount(g, size, listOfGates);
                for(i = 0; i < numberOfGates; i++){
                    printf("%s ", listOfGates[i]);
                }

                printf("\n*Number of Gates: %d\n", numberOfGates);
                break;

            case 3:
                printf("\nIsles:\n");      
                char outputList[100][5];
                int isleCounter = 0;
                char isleList[100][5];

                JRB nPtr;
                jrb_traverse(nPtr, g.vertices){
                    char *currentNode = jval_s(nPtr->val);
                    int numberAd = getAdjacentVertices(g, currentNode, outputList);
                    
                    
                    if(numberAd == 0){
                        strcpy(isleList[isleCounter], currentNode);
                        isleCounter++;
                    }
                }

                for(int k = 0; k < isleCounter; k++){
                    printf("%s ", isleList[k]);
                }

                printf("\n*Number of Isles: %d\n", isleCounter);

                break;

            case 4:
                printf("\nConnected cells\n");
                char target[5];

                printf("Enter a cell: ");
                scanf("%s", target);

                if(!isWalkable(g, target)){
                    printf("This cell is not walkable!\n");
                }
                else{
                    char connectList[100][5];
                    int numberOfConnects = countConnect(g, target, connectList);
                    printf("*Number of connected cells: %d\n", numberOfConnects + 1);
                    // for(i = 0; i < numberOfConnects; i++){
                    //     printf("%s ", connectList[i]);
                    // }
                    // printf("\n");
                }
                break;

            case 5:
                printf("\nCheck if treasure is reachable\n");
                char treasureId[5];
                char gateId[5];

                printf("*Enter treasure cell: ");
                scanf("%s", treasureId);

                int hasPath;
                // int isReachable = 0;
                int isGate = 0;
                char gatePath[100][5];

                if(!isWalkable(g, treasureId))
                    printf("->This cell is not walkable!\n");
                else{
                    printf("*Enter gate: ");
                    scanf("%s", gateId);

                    isGate = 0;
                    numberOfGates = gateCount(g, size, listOfGates);
                    for(i = 0; i < numberOfGates; i++){
                        if(strcmp(gateId, listOfGates[i]) == 0){
                            isGate = 1;
                        }
                    }

                    if(isGate == 0)
                        printf("->This is not a gate!\n");
                    else{
                        hasPath = shortestPath(g, gateId, treasureId, gatePath);
                        if(hasPath != 0)
                            printf("->Treasure is reachable!\n");
                        else
                            printf("->Treasure is unreachable!\n");
                    }
                }
                break;

            default:
                printf("*!!!Please choose number from 1 to 6!\n");
                break;
        }

        printf("\nMENU\n\n1 - Number of Vertices and Edges\n2 - Number of Gates\n3 - Number of Isles\n4 - Connected cells\n5 - Check if treasure is reachable\n6 - Exit\n...");
        scanf("%d", &choice);
    }

    printf("Exit\n");
    return 0;
}