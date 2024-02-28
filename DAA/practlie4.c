#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function prototypes
int find(struct Subset subsets[], int i);
void unionSets(struct Subset subsets[], int x, int y);
int compareEdges(const void *a, const void *b);
void kruskal(struct Edge edges[], int V, int E);

int main() {
    // Example graph representation
    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Applying Kruskal's algorithm
    kruskal(edges, V, E);

    return 0;
}

// Find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Perform union of two sets (uses union by rank)
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparison function for sorting edges based on weight
int compareEdges(const void *a, const void *b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Kruskal's algorithm to find the minimum spanning tree
void kruskal(struct Edge edges[], int V, int E) {
    // Allocate memory for the subsets
    struct Subset *subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Create V subsets with single elements
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // Sort the edges in non-decreasing order of weight
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    // Initialize result
    struct Edge *result = (struct Edge*)malloc((V-1) * sizeof(struct Edge));

    int i = 0; // Index used to pick the next edge to include in the result

    // Number of edges to be included in the result
    int e = 0;

    // Loop until we reach V-1 edges in the result
    while (e < V - 1) {
        // Pick the smallest edge and increment the index for next iteration
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, add it to the result and increment the edge count
        if (x != y) {
            result[e++] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    // Print the resulting minimum spanning tree
    printf("Edges in the Minimum Spanning Tree:\n");
    for (i = 0; i < e; i++) {
        printf("(%d, %d) with weight %d\n", result[i].src, result[i].dest, result[i].weight);
    }

    // Free allocated memory
    free(subsets);
    free(result);
}
