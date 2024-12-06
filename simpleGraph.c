#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define INFINITY 999
#define NULL_VERTEX -1

typedef int LabelAdjMat[MAX][MAX];
typedef struct
{
    int u, w;
    int weight;
} edgeType;

typedef struct node
{
    edgeType N;
    struct node *next;
} *edgeList;

typedef edgeList LabelAdjList[MAX];

typedef struct
{
    int distance[MAX];
    int previous[MAX];
} Dijkstra;

typedef struct {
    edgeType edges[MAX];
    int lastNdx;    
}minHeapOrList;

typedef struct {
    minHeapOrList eList;
    int cost;
}MST;

void initLabelAdjMat(LabelAdjMat adjMat);
void populateAdjMat(LabelAdjMat adjMat);
void displayAdjMat(LabelAdjMat adjMat);
edgeList createEdgeList(LabelAdjMat adjMat);
void displayEdgeList(edgeList List);

//Dijkstra's Algorithm
int *findDijkstraAdjMatrix(LabelAdjMat adjMat, int source);
int *findDijkstraAdjList(edgeList List, int source);

//Kruskal's Algorithm
MST MSTKruskal(LabelAdjMat adjMat);
minHeapOrList createMinHeapOrList();
void insertMinHeap(minHeapOrList *eList, edgeType edge);
edgeType deleteMin(minHeapOrList *eList);
void displayKruskal(MST mst);

//Prim's Algorithm
MST MSTPrim(LabelAdjMat adjMat, int startV);
void displayPrim(MST mst);

void initLabelAdjMat(LabelAdjMat adjMat)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            adjMat[i][j] = 0;
        }
    }
}

void populateAdjMat(LabelAdjMat adjMat)
{
    edgeType edges[] = {
        {0, 1, 10},
        {0, 2, 3},
        {1, 2, 1},
        {1, 4, 4},
        {1, 3, 2}};

    int numEdges = sizeof(edges) / sizeof(edges[0]);

    for (int i = 0; i < numEdges; i++)
    {
        adjMat[edges[i].u][edges[i].w] = edges[i].weight;
        adjMat[edges[i].w][edges[i].u] = edges[i].weight;
    }
}

void displayAdjMatrix(LabelAdjMat adjMat)
{
    printf("\nAdjacency Matrix:\n");

    printf("    ");
    for (int i = 0; i < MAX; i++)
    {
        printf("%-4d", i);
    }
    printf("\n");

    printf("    ");
    for (int i = 0; i < MAX; i++)
    {
        printf("----");
    }
    printf("\n");

    for (int i = 0; i < MAX; i++)
    {
        printf("%-3d|", i); // Row label
        for (int j = 0; j < MAX; j++)
        {
            printf("%-4d", adjMat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

edgeList createEdgeList(LabelAdjMat adjMat)
{
    int x, y;
    edgeList List = NULL, *trav, temp;
    for (x = 0; x < MAX; x++)
    {
        for (y = 0; y < MAX; y++)
        {
            if (adjMat[x][y] != 0)
            {
                temp = (edgeList)malloc(sizeof(struct node));
                if (temp != NULL)
                {
                    temp->N.u = x;
                    temp->N.w = y;
                    temp->N.weight = adjMat[x][y];
                    for (trav = &List; *trav != NULL; trav = &(*trav)->next)
                    {
                    }
                    temp->next = *trav;
                    *trav = temp;
                }
            }
        }
    }
    return List;
}

void displayEdgeList(edgeList List)
{
    for (int i = 0; i < MAX; i++)
    {
        printf("%d -> ", i);
        for (edgeList trav = List; trav != NULL; trav = trav->next)
        {
            if (trav->N.u == i)
            {
                printf("%d[%d]", trav->N.w, trav->N.weight);
            }
        }
        printf("\n");
    }
}

int *findDijkstraAdjMatrix(LabelAdjMat adjMat, int source)
{
    int *D = (int *)malloc(MAX * sizeof(int));
    int S[MAX];
    // step 1: initialize D and S
    if (D != NULL)
    {
        for (int i = 0; i < MAX; i++)
        {
            D[i] = INFINITY;
            S[i] = 0;
        }
        // step 2:  initialize source distanc to 0
        D[source] = 0;

        // step 3: initialize D[i] with direct paths from the source
        // Find shortest path for all vertices
        for (int count = 0; count < MAX; count++)
        {
            // Find minimum distance vertex from the unvisited set
            int min = INFINITY;
            int u = -1;

            for (int v = 0; v < MAX; v++)
            {
                if (S[v] == 0 && D[v] < min)
                {
                    min = D[v];
                    u = v;
                }
            }

            // If we can't find a next vertex, undangi gaw
            if (u != -1)
            {
                // set to 1 if visited na
                S[u] = 1;

                // Update distances of adjacent vertices
                for (int v = 0; v < MAX; v++)
                {
                    // Update D[v] only if:
                    // 1. There is an edge from u to v
                    // 2. Vertex v is not visited
                    // 3. Total weight of path from source to v through u is less than current value of D[v]
                    if (!S[v] && adjMat[u][v] != 0 && D[u] != INFINITY && D[u] + adjMat[u][v] < D[v])
                    {
                        D[v] = D[u] + adjMat[u][v];
                    }
                }
            }
        }
    }
    return D;
}

int *findDijkstraAdjList(edgeList List, int source)
{
    int *D = (int *)malloc(MAX * sizeof(int));
    int S[MAX];

    if (D != NULL){
        for (int i = 0; i < MAX; i++){
            D[i] = INFINITY;
            S[i] = 0;
        }
        D[source] = 0;

        for (int i = 0; i < MAX; i++){
            int min = INFINITY;
            int u = -1;
            for (int v = 0; v < MAX; v++){
                if (S[v] == 0 && D[v] < min){
                    min = D[v];
                    u = v;
                }
            }

            if (u != -1){
                S[u] = 1;
                for (edgeList trav = List; trav != NULL; trav = trav->next){
                    if (trav->N.u == u && !S[trav->N.w] && D[u] != INFINITY && D[u] + trav->N.weight < D[trav->N.w]){
                        D[trav->N.w] = D[u] + trav->N.weight;
                    }
                }
            }
        }
    }
    return D;
}

MST MSTKruskal(LabelAdjMat A)
{
    MST mst;
    mst.cost = 0;
    mst.eList = createMinHeapOrList();
    minHeapOrList tempHeap = createMinHeapOrList();
    
    int components[MAX];
    for(int i = 0; i < MAX; i++) {
        components[i] = i;
    }
    
    for(int i = 0; i < MAX; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(A[i][j] != 0) {
                edgeType edge = {i, j, A[i][j]};
                insertMinHeap(&mst.eList, edge);
            }
        }
    }

    for(int edgeCount = 0; edgeCount < MAX - 1 && mst.eList.lastNdx > 0;) {
        edgeType edge = deleteMin(&mst.eList);
        
        int v1 = edge.u;
        int v2 = edge.w;
        
        for(; components[v1] != v1; v1 = components[v1]);
        for(; components[v2] != v2; v2 = components[v2]);
        
        if(v1 != v2) {
            components[v2] = v1;
            insertMinHeap(&tempHeap, edge); 
            mst.cost += edge.weight;
            edgeCount++;
        }
    }
    
    mst.eList = tempHeap;
    
    return mst;
}

minHeapOrList createMinHeapOrList(){
    minHeapOrList heap;
    heap.lastNdx = 0;
    return heap;
}

void insertMinHeap(minHeapOrList *eList, edgeType edge){
    if(eList->lastNdx < MAX){
        int trav = eList->lastNdx++;
        eList->edges[trav] = edge;
        for(int parent = (trav - 1)/2; trav > 0 && eList->edges[trav].weight < eList->edges[parent].weight; trav = parent, parent = (trav - 1)/2){
            edgeType temp = eList->edges[trav];
            eList->edges[trav] = eList->edges[parent];
            eList->edges[parent] = temp;
        }
    }
}

edgeType deleteMin(minHeapOrList *eList)
{
    edgeType minEdge = eList->edges[0];
    eList->edges[0] = eList->edges[--eList->lastNdx];
    
    int trav = 0;
    while(1) {
        int smallest = trav;
        int left = 2 * trav + 1;
        int right = 2 * trav + 2;
        
        if(left < eList->lastNdx && eList->edges[left].weight < eList->edges[smallest].weight) {
            smallest = left;
        }
        if(right < eList->lastNdx && eList->edges[right].weight < eList->edges[smallest].weight) {
            smallest = right;
        }
        
        if(smallest == trav) {
            break;  // Added break condition
        }
        
        // Swap
        edgeType temp = eList->edges[trav];
        eList->edges[trav] = eList->edges[smallest];
        eList->edges[smallest] = temp;
        trav = smallest;
    }
    
    return minEdge;
}

void displayKruskal(MST mst){
    printf("Minimum Spanning Tree:\n");
    printf("Total Cost: %d\n", mst.cost);
    printf("Edges:\n");

    for(int i = 0; i < mst.eList.lastNdx; i++){
        printf("(%d, %d, %d)\n", mst.eList.edges[i].u, mst.eList.edges[i].w, mst.eList.edges[i].weight);
    }
    printf("\n");
}

MST MSTPrim(LabelAdjMat adjMat, int startV){
    MST mst;
    mst.cost = 0;
    mst.eList = createMinHeapOrList();
    minHeapOrList tempHeap = createMinHeapOrList();

    int visited[MAX] = {0};
    visited[startV] = 1;
    for(int i = 0; i < MAX; i++){
        if(adjMat[startV][i] != 0){
            edgeType edge = {startV, i, adjMat[startV][i]};
            insertMinHeap(&mst.eList, edge);
        }
    }
    for(int edgeCount = 0; edgeCount < MAX - 1 && mst.eList.lastNdx > 0;) {
        edgeType edge = deleteMin(&mst.eList);
        
        if(!visited[edge.w]) {  // Only check if destination is not visited
            // Add edge to MST
            insertMinHeap(&tempHeap, edge);
            mst.cost += edge.weight;
            visited[edge.w] = 1;  // Mark new vertex as visited
            
            // Add all edges from newly visited vertex
            for(int i = 0; i < MAX; i++) {
                if(adjMat[edge.w][i] != 0 && !visited[i]) {
                    edgeType newEdge = {edge.w, i, adjMat[edge.w][i]};
                    insertMinHeap(&mst.eList, newEdge);
                }
            }
            edgeCount++;
        }
    }
    mst.eList = tempHeap;
    return mst;
}

void displayPrim(MST mst){
    printf("Minimum Spanning Tree:\n");
    printf("Total Cost: %d\n", mst.cost);
    printf("Edges:\n");

    for(int i = 0; i < mst.eList.lastNdx; i++){
        printf("(%d, %d, %d)\n", mst.eList.edges[i].u, mst.eList.edges[i].w, mst.eList.edges[i].weight);
    }
    printf("\n");
}

int main()
{

    LabelAdjMat adjMat;
    initLabelAdjMat(adjMat);
    edgeList list = NULL;

    printf("Adjacency Matrix: \n");
    populateAdjMat(adjMat);
    displayAdjMatrix(adjMat);

    printf("Adjacency List: \n");

    list = createEdgeList(adjMat);
    displayEdgeList(list);

    printf("\n");
    printf("Dijkstra's Algorithm: \n");
    int source = 0;
    int *shortestPaths = findDijkstraAdjMatrix(adjMat, source);

    if (shortestPaths != NULL)
    {
        printf("\nShortest paths from vertex %d:\n", source);
        printf("-----------\n");
        for (int i = 0; i < MAX; i++)
        {
            if (i != source)
            {
                if (shortestPaths[i] >= INFINITY)
                {
                    printf("%d\t%c\n", i, 236);
                }
                else
                {
                    printf("%d\t%d\n", i, shortestPaths[i]);
                }
            }
        }
        free(shortestPaths);
    }

    printf("\n");
    printf("\nDijkstra's Algorithm (Adjacency List): \n");
    int source2 = 0;
    int *shortestPath = findDijkstraAdjList(list, source2);

    if (shortestPath != NULL)
    {
        printf("\nShortest paths from vertex %d:\n", source2);
        printf("-----------\n");
        for (int i = 0; i < MAX; i++)
        {
            if (i != source2)
            {
                if (shortestPath[i] >= INFINITY)
                {
                    printf("%d\t%c\n", i, 236);
                }
                else
                {
                    printf("%d\t%d\n", i, shortestPath[i]);
                }
            }
        }
        free(shortestPath);
    }

    printf("\n");
    printf("MST Kruskal: \n");
    MST mstKruskal = MSTKruskal(adjMat);
    displayKruskal(mstKruskal);

    printf("\n");
    printf("MST Prim: \n");
    MST mstPrim = MSTPrim(adjMat, 0);
    displayKruskal(mstPrim);
    return 0;
}