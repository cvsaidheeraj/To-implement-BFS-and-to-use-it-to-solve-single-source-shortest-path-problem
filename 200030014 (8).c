#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int vertex) {
    // Create a new node and initialize its data and next pointer
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = vertex;
    newNode->next = NULL;
    return newNode;
}

void insert(Node* arr[], int x, int y) {
    // Insert nodes at the beginning of the linked list for vertices x and y
    Node* temp1 = createNode(x);
    Node* temp2 = createNode(y);

    if (arr[x] == NULL) {
        // If the linked list for vertex x is empty, make the new node temp2 the head
        arr[x] = temp2;
    } else {
        // Otherwise, insert the new node temp2 at the beginning of the linked list
        temp2->next = arr[x];
        arr[x] = temp2;
    }

    if (arr[y] == NULL) {
        // If the linked list for vertex y is empty, make the new node temp1 the head
        arr[y] = temp1;
    } else {
        // Otherwise, insert the new node temp1 at the beginning of the linked list
        temp1->next = arr[y];
        arr[y] = temp1;
    }
}

void enqueue(int arr[], int* head, int* tail, int element) {
    if (*head == -1) {
        // If the queue is empty, increment head and tail and add the element to the queue
        *tail = *tail + 1;
        *head = *head + 1;
        arr[*tail] = element;
        return;
    }

    // Increment tail and add the element to the queue
    *tail = *tail + 1;
    arr[*tail] = element;
}

int dequeue(int arr[], int* head, int* tail) {
    int var;
    if (*head != -1) {
        // If the queue is not empty, remove and return the element at the head
        var = arr[*head];
        int i = 0;
        while (i < *tail) {
            // Shift the remaining elements in the queue to the left
            arr[i] = arr[i + 1];
            i++;
        }
        arr[*tail] = arr[*tail] - 1;
        *tail = *tail - 1;

        if (*head == 0 && *tail == -1) {
            // If the head is at the beginning and the tail is at the end, set head to -1 to indicate an empty queue
            *head = -1;
        }
    }
    return var;
}

typedef struct Vertex {
    int colour;
    int before;
    int distance;
} Vertex;

int main(int argc, char* argv[]) {
    int vertex, edge, x_vertex, y_vertex;
    int ele = 0;
    int a;

    FILE* infile = fopen(argv[1], "r");
    FILE* outfile = fopen("sd.txt", "w");

    fscanf(infile, "%d %d", &vertex, &edge);

    Node* graph[vertex];
    int queue[vertex];
    Vertex corner[vertex];

    for (int i = 0; i < vertex; i++) {
        // Initialize the adjacency list and vertex properties
        graph[i] = NULL;
        corner[i].colour = -1;
        corner[i].distance = -1;
        corner[i].before = -1;
    }

    while (fscanf(infile, "%d %d", &x_vertex, &y_vertex) != EOF) {
        // Read the graph edges and insert them into the adjacency list
        insert(graph, x_vertex, y_vertex);
    }

    corner[0].colour = 0;
    corner[0].before = -1;
    corner[0].distance = 0;

    int head = -1;
    int tail = -1;

    enqueue(queue, &head, &tail, ele);

    while (head != -1) {
        // Perform breadth-first search traversal
        a = dequeue(queue, &head, &tail);
        Node* rand = graph[a];

        while (rand != NULL) {
            int b = rand->data;
            if (corner[b].colour == -1) {
                // Process unvisited vertices
                corner[b].colour = 0;
                corner[b].before = a;
                corner[b].distance = corner[a].distance + 1;

                enqueue(queue, &head, &tail, b);
            }
            rand = rand->next;
        }

        corner[a].colour = 1;
    }

    for (int i = 0; i < vertex; i++) {
        // Write the distances from the source vertex to each vertex in the output file
        fprintf(outfile, "%d\n", corner[i].distance);
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}
