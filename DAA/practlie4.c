#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset (used for Union-Find)
struct Subset {
    int parent, rank;
};

// Function to find the parent of a vertex (using Union-Find)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform Union of two subsets
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

// Kruskal's algorithm to find MST
void kruskal(struct Edge edges[], int V, int E) {
    struct Edge result[V];
    int e = 0, i = 0;

    // Sort edges in non-decreasing order of weight
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < E) {
        struct Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (int j = 0; j < e; j++)
        printf("%d -- %d (weight %d)\n", result[j].src, result[j].dest, result[j].weight);

    free(subsets);
}

int main() {
    int V = 6; // Number of vertices
    int E = 9; // Number of edges
    struct Edge edges[] = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2},
        {1, 0, 4}, {2, 0, 4}, {2, 1, 2},
        {2, 3, 3}, {2, 5, 2}, {2, 4, 4}
    };

    kruskal(edges, V, E);

    return 0;
}
