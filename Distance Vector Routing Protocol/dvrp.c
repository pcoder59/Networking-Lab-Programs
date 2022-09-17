#include<stdio.h>

struct node {
    int dist[10];
    int from[10];
}rt[10];

int main() {
    int i, j, count, k, n, costmat[10][10];
    printf("Enter Number of Nodes: ");
    scanf("%d", &n);
    printf("Enter The Cost Matrix: \n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &costmat[i][j]);
            costmat[i][i] = 0;
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }
    do {
        count = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                for(k = 0; k < n; k++) {
                    if(rt[i].dist[j] > costmat[i][k]+rt[k].dist[j]) {
                        rt[i].dist[j] = rt[i].dist[k]+rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    }while(count != 0);
    for(i = 0; i < n; i++) {
        printf("For Router %d\n", i+1);
        for(j = 0; j < n; j++) {
            printf("Node %d Via %d Distance %d\n", j+1, rt[i].from[j], rt[i].dist[j]);
        }
    }
    return 0;
}