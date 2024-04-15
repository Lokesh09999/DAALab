#include <iostream>
#include <limits.h>

#define MAX 100
#define TEMP 0
#define PERM 1
#define infinity INT_MAX
#define NIL -1

int adj[MAX][MAX];
int pathLength[MAX];
int predecessor[MAX];
int status[MAX];

int n;

void findPath(int s, int v);
void Dijkstra(int s);
int min_temp();
void createGraph();

int main() {
    createGraph();

    int s, v;
    std::cout << "Enter source vertex: ";
    std::cin >> s;
    Dijkstra(s);

    while (1) {
        std::cout << "Enter destination vertex (-1 to quit): ";
        std::cin >> v;

        if (v == -1)
            break;

        if (v < 0 || v >= n)
            std::cout << "This vertex does not exist\n";
        else if (v == s)
            std::cout << "Source and destination vertices are the same\n";
        else if (pathLength[v] == infinity)
            std::cout << "There is no path from source to destination vertex\n";
        else
            findPath(s, v);
    }

    return 0;
}

void Dijkstra(int s) {
    int i, current;

    for (i = 0; i < n; i++) {
        predecessor[i] = NIL;
        pathLength[i] = infinity;
        status[i] = TEMP;
    }

    pathLength[s] = 0;

    while (1) {
        current = min_temp();
        if (current == NIL)
            return;

        status[current] = PERM;
        for (int i = 0; i < n; i++) {
            if (status[i] == TEMP && adj[current][i] != 0 &&
                pathLength[current] + adj[current][i] < pathLength[i]) {
                pathLength[i] = pathLength[current] + adj[current][i];
                predecessor[i] = current;
            }
        }
    }
}

int min_temp() {
    int min = infinity, index = NIL;

    for (int i = 0; i < n; i++) {
        if (status[i] == TEMP && pathLength[i] < min) {
            min = pathLength[i];
            index = i;
        }
    }

    return index;
}

void findPath(int s, int v) {
    int path[MAX], count = 0;

    while (v != s) {
        path[count++] = v;
        v = predecessor[v];
    }

    path[count++] = s;

    std::cout << "Shortest Path: ";
    for (int i = count - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i > 0)
            std::cout << " -> ";
    }

    std::cout << "\nPath Length: " << pathLength[v] << std::endl;
}

void createGraph() {
    std::cout << "Enter the number of vertices: ";
    std::cin >> n;

    std::cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
         {
            std::cin >> adj[i][j];
        }
    }
}