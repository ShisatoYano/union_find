#include <cstdio>
#include <cstdlib>
using namespace std;

// edge in graph
struct Edge {
    int src, dst;
};

// graph
struct Graph {
    int V; // num of vertices
    int E; // num of edges

    struct Edge*edge; // array of edges
};

struct Subset {
    int parent;
    int rank;
};

// create a graph with V vertices and E edges
struct Graph* create_graph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    graph->V = V;
    graph->E = E;

    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));

    return graph;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }

    return subsets[i].parent;
}

void uniou_set(struct Subset subsets[], int x_root, int y_root) {
    if (subsets[x_root].rank < subsets[y_root].rank) {
        subsets[x_root].parent = y_root;
    } else if (subsets[x_root].rank > subsets[y_root].rank) {
        subsets[y_root].parent = x_root;
    } else {
        subsets[y_root].parent = x_root;
        subsets[x_root].rank++;
    }
}

int is_cycle(struct Graph* graph) {
    int V = graph->V;
    int E = graph->E;

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    for (int e = 0; e < E; ++e) {
        int x = find(subsets, graph->edge[e].src);
        int y = find(subsets, graph->edge[e].dst);

        if (x == y) {
            return 1;
        }

        uniou_set(subsets, x, y);
    }

    return 0;
}

int main() {
    int V = 3, E = 3;
    struct Graph* graph = create_graph(V, E);

    graph->edge[0].src = 0;
    graph->edge[0].dst = 1;

    graph->edge[1].src = 1;
    graph->edge[1].dst = 2;

    graph->edge[2].src = 0;
    graph->edge[2].dst = 2;

    if (is_cycle(graph)) {
        printf("Graph contains cycle");
    } else {
        printf("Graph doesn't contain cycle");
    }

    return 0;
}
