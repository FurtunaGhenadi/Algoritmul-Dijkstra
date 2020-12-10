//Tekwill in fiecare scoala

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int **read_graph_from_file();
int **create_empty_graph(int nodes_count);
void dijkstra(int **, int, int);
int find_min_node(int *, bool *, int);
void print_cost(int *, int, int);
void print_path(int *, int, int);

int main(void)
{
    int **graph;
    int nodes_count, start;

    graph = read_graph_from_file("graph.in", &nodes_count);
    printf("Introdu virful de start: ");
    scanf("%d", &start);

    dijkstra(graph, nodes_count, start);

    return 0;
}

void dijkstra(int **graph, int nodes_count, int start)
{
    int i, j, current_node;
    int *cost = (int *)malloc(nodes_count * sizeof(int));
    bool *visited = (bool *)calloc(nodes_count, sizeof(bool));
    int *path = (int *)malloc(nodes_count * sizeof(int));

    visited[start] = true;
    for (j = 0; j < nodes_count; j++)
    {
        cost[j] = graph[start][j];
        if (graph[start][j] != INT_MAX)
            path[j] = start;
    }

    for (i = 1; i < nodes_count - 1; i++)
    {
        current_node = find_min_node(cost, visited, nodes_count);
        visited[current_node] = true;
        for (j = 0; j < nodes_count; j++)
        {
            if (visited[j] == false &&
                graph[current_node][j] != INT_MAX &&
                cost[current_node] + graph[current_node][j] < cost[j])
            {
                cost[j] = cost[current_node] + graph[current_node][j];
                path[j] = current_node;
            }
        }
    }

    print_cost(cost, nodes_count, start);
    print_path(path, nodes_count, start);
    free(visited);
    free(cost);
}

void find_path(int *path, int current_node, int start)
{
    if (current_node == start)
    {
        printf("%d ", current_node);
        return;
    }

    find_path(path, path[current_node], start);
    printf("%d ", current_node);
}

void print_path(int *path, int nodes_count, int start)
{
    for (int i = 0; i < nodes_count; i++)
        if (i != start)
        {
            printf("%d -> %d: ", start, i);
            find_path(path, i, start);
            printf("\n");
        }
}

void print_cost(int *cost, int size, int start)
{
    printf("Cost:\n");
    for (int i = 0; i < size; i++)
        if (i != start)
            printf("(%d, %d) = %d\n", start, i, cost[i]);

    printf("\n");
}

int find_min_node(int *cost, bool *visited, int size)
{
    int min_cost, min_index;

    min_cost = INT_MAX;
    for (int i = 0; i < size; i++)
        if (cost[i] < min_cost && visited[i] == false)
        {
            min_cost = cost[i];
            min_index = i;
        }

    return min_index;
}

int **read_graph_from_file(char *path, int *nodes_count)
{
    FILE *input;
    int **graph;
    int src, dest, weight;

    input = fopen(path, "r");
    if (input == NULL)
    {
        printf("Eroare la deschiderea fisierului.");
        exit(-1);
    }

    fscanf(input, "%d", nodes_count);
    printf("Numarul de noduri: %d\n", *nodes_count);

    graph = create_empty_graph(*nodes_count);
    while (fscanf(input, "%d %d %d", &src, &dest, &weight) != EOF)
    {
        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }

    fclose(input);
    return graph;
}

int **create_empty_graph(int nodes_count)
{
    int **graph;

    graph = (int **)malloc(sizeof(int *) * nodes_count);
    for (int i = 0; i < nodes_count; i++)
        graph[i] = (int *)malloc(sizeof(int) * nodes_count);

    for (int i = 0; i < nodes_count; i++)
        for (int j = 0; j < nodes_count; j++)
            graph[i][j] = INT_MAX;

    return graph;
}