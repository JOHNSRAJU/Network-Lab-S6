#include <stdio.h>
#include <limits.h>

#define MAX_NODES 10

struct nodes {
    int dist[MAX_NODES];
    int through[MAX_NODES];
};

int main() {
    int n, i, j, k, matrix[MAX_NODES][MAX_NODES], distanceVector[MAX_NODES][MAX_NODES], through[MAX_NODES][MAX_NODES];

    // Get the number of nodes and distances between them
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    struct nodes node[n];

    // Get the distance between each node
    printf("Enter the distance between each node (if there is no connection, input -1):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                printf("Distance between %d and %d: ", i, j);
                scanf("%d", &node[i].dist[j]);
                if (node[i].dist[j] != -1) {
                    node[i].through[j] = j;
                } else {
                    node[i].through[j] = -1;
                }
            } else {
                node[i].dist[j] = 0;
                node[i].through[j] = -1;
            }
        }
    }

    // Print the initial table
    printf("\nInitial distance table:\n");
    printf("\t");
    for(i=0;i<n;i++){
        printf("%d\t",i);
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("Node %d:\t", i);
        for (j = 0; j < n; j++) {
            printf("%d\t", node[i].dist[j]);
            node[i].through[j]=j;
        }
        printf("\n");
    }

    // Implement the distance vector algorithm
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (node[i].dist[k] != -1 && node[k].dist[j] != -1) {
                    int newDistance = node[i].dist[k] + node[k].dist[j];
                    if (newDistance < node[i].dist[j] || node[i].dist[j] == -1) {
                        node[i].dist[j] = newDistance;
                        node[i].through[j] = node[i].through[k];
                    }
                }
            }
        }
    }

    // Print the final distance vectors and through nodes for each node
    for (i = 0; i < n; i++) {
        printf("\nDistance vectors for node %d:\n", i);
        printf("\t\t");
        for(j=0;j<n;j++){
            printf("%d\t",j);
        }
        printf("\n");
        printf("Distances:\t");
        for (j = 0; j < n; j++) {
            printf("%d\t", node[i].dist[j]);
        }
        printf("\n");
        printf("Through nodes:\t");
        for (j = 0; j < n; j++) {
            printf("%d\t", node[i].through[j]);
        }
        printf("\n");
    }
    return 0;
}

