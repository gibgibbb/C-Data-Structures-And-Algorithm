    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #define MAX 5 // Number of vertices in the graph
    #define MAX_EDGES 0Xff
    #define INFINITY 9999

    typedef int set[MAX]; // Bit-vector implementation of Set

    typedef struct
    {
        int u, v;   // (u,v) represents the edge; i.e. v is adjacent to u
        int weight; // weight of the edge
    } edgeType;

    // Definition of a arraylist of edges, Version 2
    typedef struct Elist
    {
        edgeType edges[MAX_EDGES];
        int edgeCount; // number of edges in the list
    } *EdgeList;       // List

    // Definition of a Linked list of adjacent vertices with weight
    typedef struct adjNode
    {
        int vertex;
        int weight;
        struct adjNode *nxtAdjV; // Next adjacent vertex
    } *adjLL;

    // Definition of Adjacency List and Adjacency Matrix Implementations of Graph
    typedef adjLL AdjList[MAX];      // Adjacency List; an array type of size MAX
    typedef int AdjMatrix[MAX][MAX]; // Labeled Adjacency Matrix

    typedef struct
    {
        int cost;
        int vertex[5]; // Vertices in the shortest path
        int lastNdx;   // Index of the last vertex in the shortest path.
    } pathDetails;

    typedef struct
    {
        int sourceVertex;
        pathDetails path[MAX]; // For example: sourceVertex is 2. path[0] contains the cost and path from vertex 2 to vertex 0.
    } shortestPaths;

    // Function Prototypes
    // a) Problem 1
    EdgeList populateEdgeList();
    void initAdjList(AdjList AL);
    void insertSortedAdjList(adjLL *A, edgeType E);
    void buildAdjList(EdgeList L, AdjList AL);
    void displayAdjList(AdjList AL);

    // b) Problem 2
    void initAdjMatrix(AdjMatrix AM);
    void createLabeledMatrix(AdjList AL, AdjMatrix AM);
    void displayLabeledAdjMatrix(AdjMatrix AM);

    // c) Problem 3
    int findMinVertex(shortestPaths SP, set S);
    shortestPaths modifiedDjikstra(AdjMatrix G, int startVertex);
    void displayShortestPaths(shortestPaths SP);

    int main(void)
    {

        /**********************************************
         * Problem 1: Creating an Adjacency List      *
         *   a) Calls PopulateEdgeList()              *
         *   b) Calls buildAdjList()                  *
         *   c) Calls displayAdjList                  *
         **********************************************/
        printf("\n\nProblem 1: Creating an Adjacency List ");

        // Write variable declaration and function calls here
        adjLL AL;
        EdgeList edgeList = populateEdgeList();
        buildAdjList(edgeList, &AL);
        displayAdjList(&AL);

        /****************************************************
         * Problem 2: Creating a Labeled Adjacency Matrix   *
         *   a) Calls createLabeledAdjMatrix()              *
         *   b) Calls displayLabeledAdjList()               *
         ****************************************************/
        printf("\n\nProblem 2: Creating a Labeled Adjacency Matrix ");

        // Write variable declaration and function calls here
        AdjMatrix AM;
        createLabeledMatrix(&AL, AM);
        displayLabeledAdjMatrix(AM);
        /****************************************************
         * Problem 3: Djikstra's Algorithm                  *
         *   a) Allows user to input a source vertex        *
         *   b) Calls modifiedDjikstra()                    *
         *   c) Calls displayShortestPaths()                *
         ****************************************************/
        printf("\n\nProblem 3: Finding the Shortest Path ");

        // Write variable declaration and function calls here

        shortestPaths SP = modifiedDjikstra(AM, 0);
        displayShortestPaths(SP);

        return 0;
    }

    /***** Problem 1 Function definition *****/

    /**********************************************************
     * PopulateEdgeList(). The function will populate a list  *
     * of edges and returns it to the calling function.       *
     **********************************************************/
    EdgeList populateEdgeList()
    {
        edgeType edges[] = {
            {0, 1, 10},
            {0, 4, 100},
            {0, 3, 30},
            {1, 2, 50},
            {2, 0, 20},
            {2, 4, 10},
            {3, 2, 20},
            {3, 4, 60},
        };
        int numEdges = sizeof(edges) / sizeof(edges[0]);

        // Put your code below
        EdgeList list = (EdgeList)malloc(sizeof(struct Elist));
        list->edgeCount = numEdges;

        int i;

        for (i = 0; i < numEdges; i++)
        {
            list->edges[i] = edges[i];
        }

        return list;
    }

    /**********************************************************
     * The function will initialize the adjList to be empty.  *
     **********************************************************/
    void initAdjList(AdjList AL)
    {
        for (int i = 0; i < MAX; i++)
        {
            AL[i] = NULL;
        }
    }

    /*********************************************************************
     * Given a sorted list, the function will insert the given edge (u,v) *
     * to its appropriate position in the SORTED adjacency List. List is  *
     * sorted in ascending order according to weight.                     *
     **********************************************************************/
    void insertSortedAdjList(adjLL* A, edgeType E)
    {
        adjLL *trav;
        for(trav = A; *trav != NULL && (*trav)->weight < E.weight; trav = &(*trav)->nxtAdjV){}

        adjLL temp = (adjLL)malloc(sizeof(struct adjNode));
        if(temp != NULL){
            temp->weight = E.weight;
            temp->vertex = E.v;
            temp->nxtAdjV = *trav;
            *trav = temp;
        }
    }
    /******************************************************************************
     * Given an EdgeList and AdjList, the function will initialize adjacency list *
     * to be empty and populate it with edges from the given EdgeList             *
     ******************************************************************************/
    void buildAdjList(EdgeList L, AdjList AL)
    {
        initAdjList(AL); // Initialize the adjacency list

        // Process each edge in the edge list
        for (int i = 0; i < L->edgeCount; i++)
        {
            edgeType currentEdge = L->edges[i];
            insertSortedAdjList(&AL[currentEdge.u], currentEdge);
        }
    }

    /***********************************************************
     * The function will display the given adjacency list.     *
     ***********************************************************/
    void displayAdjList(AdjList AL)
    {
        printf("\nAdjacency List Representation:\n");

        for (int i = 0; i < MAX; i++)
        {
            printf("%d -> ", i);

            for (adjLL trav = AL[i]; trav != NULL; trav = trav->nxtAdjV)
            {
                printf("%d[%d]", trav->vertex, trav->weight);
                if (trav->nxtAdjV != NULL)
                {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
    }

    /***** Problem 2 Function definition *****/

    /*************************************************************
     * initAdjMatrix(). The function will intialize the labeled  *
     * adjacency matrix to be empty, i.e. MAX vertices but       *
     * NO edges                                                  *
     *************************************************************/
    void initAdjMatrix(AdjMatrix AM)
    {
        int i, j;
        for (i = 0; i < MAX; i++)
        {
            for (j = 0; j < MAX; j++)
            {
                AM[i][j] = INFINITY;
            }
        }
    }

    /*****************************************************************
     * createMatrix(). The function will create a labeled adjMatrix  *
     * representation from the given Adjacency list.                 *
     *****************************************************************/
    void createLabeledMatrix(AdjList AL, AdjMatrix AM)
    {
        // Write your code here
        initAdjMatrix(AM);
        for (int i = 0; i < MAX; i++)
        {
            AM[i][i] = 0;
        }
        for (int i = 0; i < MAX; i++)
        {
            for (adjLL trav = AL[i]; trav != NULL; trav = trav->nxtAdjV)
            {
                AM[i][trav->vertex] = trav->weight;
            }
        }
    }

    /**********************************************************************
     * displayLabeledAdjMatrix(). The function will display the labeled   *
     * adjacency Matrix, i.e. in table form.                              *
     * Note: For infinity, use the infinity symbol whose ASCII character  *
     * value is 236.                                                      *
     **********************************************************************/
    void displayLabeledAdjMatrix(AdjMatrix AM)
    {
        // Write your code here
        printf("\nLabeled Adjacency Matrix Representation:\n");
        printf("   ");
        for (int i = 0; i < MAX; i++)
        {
            printf("%20d", i);
        }
        printf("\n");

        printf("---");
        for (int i = 0; i < MAX * 6 + 1; i++)
        {
            printf("----");
        }
        printf("\n");

        for (int i = 0; i < MAX; i++)
        {
            printf("%2d |", i);
            for (int j = 0; j < MAX; j++)
            {
                if (AM[i][j] != INFINITY)
                {
                    printf("%4d", AM[i][j]);
                }
                else
                {
                    printf("%4c", 236);
                }
            }
        }
    }

    /***** Problem 3 Function definition *****/

    /***************************************************************
     * findMinVertex(). The function will return a vertex W in V-S, *
     * such as D[W] is the minimum, i.e. W is the vertex that is   *
     * is not yet in S.                                            *
     ***************************************************************/
    int findMinVertex(shortestPaths SP, set S)
    {
        // Write your code here
        int minCost = INFINITY, minVertex = -1;

        for(int i = 0; i < MAX; i++){
            if(S[i] != 1 && SP.path[i].cost < minCost){
                minCost = SP.path[i].cost;
                minVertex = i;
            }
        }
        return minVertex;
    }

    /***************************************************************
     * This function is Djikstra's algorithm and it determines the *
     * path from the source vertex to the destination vertex. The  *
     * list of vertices in the path, except the SOURCE vertex,     *
     * are stored in array Vertex and its initial first entry is   *
     * the destination vertex. LastNdx variable holds the index of *
     * the last vertex.                                             *
     ****************************************************************/
    shortestPaths modifiedDjikstra(AdjMatrix G, int startVertex)
    {
        shortestPaths SP;
        set S = {0};  // Initialize set S to all zeros
        SP.sourceVertex = startVertex;

        // Initialize all paths
        for(int i = 0; i < MAX; i++){
            if(i != startVertex){
                SP.path[i].cost = G[startVertex][i]; 
                SP.path[i].lastNdx = 0;
                if(G[startVertex][i] != INFINITY){
                    SP.path[i].vertex[0] = startVertex;
                    SP.path[i].vertex[1] = i;
                    SP.path[i].lastNdx = 2;
                }
            } else {
                SP.path[i].cost = 0; 
                SP.path[i].vertex[0] = startVertex;
                SP.path[i].lastNdx = 1;
                
            }
        }

        S[startVertex] = 1; 

        // Main Dijkstra loop
        for(int count = 0; count < MAX-1; count++){
            int w = findMinVertex(SP, S);
            if(w == -1) break; 
            
            S[w] = 1;  

            for(int v = 0; v < MAX; v++){
                if(!S[v] && G[w][v] != INFINITY){
                    int newCost = SP.path[w].cost + G[w][v];
                    if(newCost < SP.path[v].cost){
                        SP.path[v].cost = newCost;
                        
                        SP.path[v].lastNdx = 0;
                        for(int j = 0; j < SP.path[w].lastNdx; j++){
                            SP.path[v].vertex[SP.path[v].lastNdx++] = SP.path[w].vertex[j];
                        }
                        SP.path[v].vertex[SP.path[v].lastNdx++] = v;
                    }
                }
            }
        }
        return SP;
    }

    /******************************************************
     * The function will display the following:           *
     *   a) Vertices                                      *
     *   b) Cost of path from source vertex to the vertex *
     *       Note: if cost is INFINITY, display infinity  *
     *       symbol (a character with ASCII value 236)    *
     *   c) Path from source vertex to the vertex         *
     ******************************************************/
    void displayShortestPaths(shortestPaths SP)
    {
        printf("\nShortest paths from vertex %d:\n", SP.sourceVertex);
        printf("Vertex\tCost\tPath\n");
        printf("-----\t----\t----\n");

        for(int i = 0; i < MAX; i++){
            printf("%d\t", i);
            
            // Print cost
            if(SP.path[i].cost == INFINITY){
                printf("%c\t", 236); 
            } else {
                printf("%d\t", SP.path[i].cost);
            }

            if(SP.path[i].lastNdx > 0){
                // Print actual path
                for(int j = 0; j < SP.path[i].lastNdx; j++){
                    printf("%d", SP.path[i].vertex[j]);
                    if(j < SP.path[i].lastNdx - 1){
                        printf("->"); 
                    }
                }
            } else {
                printf("No path");
            }
            printf("\n");
        }
    }