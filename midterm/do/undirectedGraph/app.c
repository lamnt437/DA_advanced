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

    int hang = 0;
    int cot = 0;
    char line[100];
    int counter = 0;

    while(fgets(line, 99, input) != NULL){
        // printf("%s", line);
        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        char id[3];
        char *temp = strtok(line, " \t");

        cot = 0;
        while(temp){
            // printf("%s ", temp);
            if(strcmp(temp, "0") == 0){
                id[0] = hang + '0';
                id[1] = cot + '0';
                id[2] = '\0';

                addVertex(g, id, id);
                counter++;
            }
            cot++;
            temp = strtok(NULL, " \t");
        }

        hang++;
        *row = hang;
        *col = cot;
    }

    return counter;
}

int inputEdges(Graph g, int hang, int cot){
    JRB ptr;
    char *strId;
    char i, j;
    int targetHang;
    int targetCot;
    char targetId[3];
    JRB node;

    int counter = 0;

    //0 <= i < hang
    //0 <= j < cot
    jrb_traverse(ptr, g.vertices){
        strId = jval_s(ptr->key);
        // printf("%s", strId);
        i = strId[0];
        char iStr[2];
        iStr[0] = i;
        iStr[1] = '\0';
        int iInt = atoi(iStr);
        printf("%d", iInt);

        j = strId[1];
        char jStr[2];
        jStr[0] = j;
        jStr[1] = '\0';
        int jInt = atoi(jStr);
        printf("%d\n", jInt);

        //up
        targetHang = iInt - 1;
        targetCot = jInt;
        if(targetHang >= 0 && targetHang < hang){
            if(targetCot >= 0 && targetCot < cot){
                targetId[0] = targetHang + '0';
                targetId[1] = targetCot + '0';
                targetId[2] = '\0';
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    addEdge(g, strId, targetId);
                    counter++;
                }
            }
        }
        //down
        targetHang = iInt + 1;
        targetCot = jInt;
        if(targetHang >= 0 && targetHang < hang){
            if(targetCot >= 0 && targetCot < cot){
                targetId[0] = targetHang + '0';
                targetId[1] = targetCot + '0';
                targetId[2] = '\0';
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    addEdge(g, strId, targetId);
                    counter++;
                }
            }
        }

        //left
        targetHang = iInt;
        targetCot = jInt - 1;
        if(targetHang >= 0 && targetHang < hang){
            if(targetCot >= 0 && targetCot < cot){
                targetId[0] = targetHang + '0';
                targetId[1] = targetCot + '0';
                targetId[2] = '\0';
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    addEdge(g, strId, targetId);
                    counter++;
                }
            }
        }

        //right
        targetHang = iInt;
        targetCot = jInt + 1;
        if(targetHang >= 0 && targetHang < hang){
            if(targetCot >= 0 && targetCot < cot){
                targetId[0] = targetHang + '0';
                targetId[1] = targetCot + '0';
                targetId[2] = '\0';
                // printf("%s-%s\n", strId, targetId);
                node = jrb_find_str(g.vertices, targetId);
                if(node != NULL){
                    addEdge(g, strId, targetId);
                    counter++;
                }
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
    char strId[3];
    int i, j;
    int numberOfEdges;

    int numberOfVertices = inputGraph(g, argv[1], &hang, &cot);
    if(numberOfVertices == 0){
        return 2;
    }

    numberOfEdges = inputEdges(g, hang, cot);

    int choice;
	printf("MENU\n\n1 - In ma tran\n2 - So nut, canh\n3 - Tim lien thong\n4 - Lien thong lon nhat\n5 - \n6 - \n7 - \n8 - exit\n...");
    scanf("%d", &choice);

    while(choice != 8){
        switch(choice){
            case 1:
                printf("In ma tran\n");
                for(i = 0; i < hang; i++){
                    for(j = 0; j < cot; j++){
                        strId[0] = i + '0';
                        strId[1] = j + '0';
                        strId[2] = '\0';
                        JRB node = jrb_find_str(g.vertices, strId);
                        if(node != NULL)
                            printf("0 ");
                        else
                            printf("1 ");
                    }
                    printf("\n");
                }
                break;

            case 2:
                printf("So dinh: %d\n", numberOfVertices);
                printf("So canh: %d\n", numberOfEdges);
                break;

            case 3:
                printf("Danh sach ke");
                char target[5];
                getchar();
                fgets(target, 4, stdin);
                if(target[strlen(target) - 1] == '\n')
                    target[strlen(target) - 1] = '\0';
                char output[100][5];
                int numberOfAdjacent = getAdjacentVertices(g, target, output);
                if(numberOfAdjacent > 0){
                    for(i = 0; i < numberOfAdjacent; i++){
                        printf("%s\n", output[i]);
                    }
                }
                else{
                    printf("No adjacent!\n");
                }
                break;

            case 4:
                printf("Lien thong lon nhat");
                JRB nodePtr;
                int max = -1;
                char *maxNode;
                char aOutput[100][5];
                jrb_traverse(nodePtr, g.vertices){
                    char *v = jval_s(nodePtr->key);
                    int nAdj = getAdjacentVertices(g, v, aOutput);
                    if(nAdj > max){
                        max = nAdj;
                    }
                }

                char maxList[100][5];
                int counter = 0;
                jrb_traverse(nodePtr, g.vertices){
                    char *v = jval_s(nodePtr->key);
                    int nAdj = getAdjacentVertices(g, v, aOutput);
                    if(nAdj == max){
                        strcpy(maxList[counter], v);
                        counter++;
                    }
                }

                int i;
                printf("Danh sach lien thong toi da:\n");
                for(i = 0; i < counter; i++){
                    printf("%s ", maxList[i]);
                }
                printf("\n");
                break;

            case 5:
            printf("Danh sach nut dao:\n");

            JRB nPtr;
            
            char outputList[100][5];
            int daoCounter = 0;
            char daoList[100][5];

            jrb_traverse(nPtr, g.vertices){
                char *currentNode = jval_s(nPtr->val);
                int numberAd = getAdjacentVertices(g, currentNode, outputList);
                
                
                if(numberAd == 0){
                    strcpy(daoList[daoCounter], currentNode);
                    daoCounter++;
                }
            }

            for(int k = 0; k < daoCounter; k++){
                printf("%s ", daoList[k]);
            }

            printf("\n");

            break;

            case 6:
            printf("");
            break;

            case 7:
            printf("");
            break;

            default:
                break;
        }

        printf("MENU\n\n1 - In ma tran\n2 - So nut, canh\n3 - Tim lien thong\n4 - Lien thong lon nhat\n5 - \n6 - \n7 - \n8 - exit\n...");
        scanf("%d", &choice);
    }

    printf("Exit\n");
    return 0;
}