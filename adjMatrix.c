#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INF 99999999

typedef int adjMatrix[MAX][MAX];
typedef struct{
    int u, v;
    int weight;
}edgeType;

typedef struct node{
    edgeType E;
    struct node *next;
}*edgeList;

edgeList createEdgeList(adjMatrix AM);
void displayEdgeList(edgeList EL);

edgeList createEdgeList(adjMatrix AM){
    int x, y;
    edgeList retList = NULL, temp, *trav;
    for(x = 1; x < MAX; x++){
        for(y = 0; y < x; y++){
            if(AM[x][y] != INF){
                temp = (edgeList)malloc(sizeof(struct node));
                temp->E.u = x;
                temp->E.v = y;
                temp->E.weight = AM[x][y];
                temp->next = NULL;
                for(trav = &retList; *trav != NULL && (*trav)->E.weight < temp->E.weight; trav = &(*trav)->next){}
                temp->next = *trav;
                *trav = temp;
            }
        }
    }
    return retList;
}

void displayEdgeList(edgeList EL){

}

int main(){

    adjMatrix AM;

    return 0;
}