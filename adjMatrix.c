#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INFINITY 99999999
#define NULL_VERTEX -1

typedef int LabelAdjMat[MAX][MAX];
typedef struct {
    int u, v, weight;
}edgeType;

edgeType *populateEdgeType();
void populateAdjMat(LabelAdjMat adjMat, edgeType *edges, int numEdges);

void populateAdjMat(LabelAdjMat adjMat, edgeType *edges, int numEdges){
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            adjMat[i][j] = 0;
        }
    }
    
    for(int i = 0; i < numEdges; i++){
        adjMat[edges[i].u][edges[i].v] = edges[i].weight;
    }
}

edgeType *populateEdgeType(){
    edgeType edges[] = {
        {0, 1, 10},
        {0, 2, 3},
        {1, 2, 1},
        {2, 1, 4},
        {1, 3, 2},
        {2, 3, 2},
        {3, 4, 7},
        {3, 0, 8},  
        {4, 3, 9},
        {4, 0, 5}
    };

    return edges;
}

int main(){
    LabelAdjMat adjMat;
    edgeType *edges = populateEdgeType();
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    populateAdjMat(adjMat, edges, numEdges);

    return 0;
}


