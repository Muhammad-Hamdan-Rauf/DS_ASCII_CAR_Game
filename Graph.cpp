#include "LinkedList.hpp"
#include "priorityQueue.hpp"
#include "coordinate.hpp"
#include <iomanip>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <windows.h>
using namespace std;

const char START = 'S';
const char FINISH = 'F';
const char CAR = 'C';
const char OBSTACLE = '#';
const char TURN = 'T';
const char PATH = '-';

class Graph
{
private:
    LinkedList<int> *adjacencyList; // Adjacency list for each cell
    int vertices;                   // Total number of cells (vertices)

public:
    Graph(int totalVertices)
    {
        vertices = totalVertices;
        adjacencyList = new LinkedList<int>[totalVertices];

        // Initialize the adjacency list for each cell
        for (int i = 0; i < totalVertices; ++i)
        {
            adjacencyList[i] = LinkedList<int>();
        }
    }

    // Add an edge (path) between two cells
    void addEdge(int source, int destination)
    {
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }

    void addVertex(int vertex, char maze[row][col])
    {
        if (vertex >= 0 && vertex < vertices)
        {
            // Check if the vertex represents an obstacle, turn, start, or finish
            char cell = maze[vertex / col][vertex % col];
            if (cell == OBSTACLE || cell == TURN || cell == START || cell == FINISH)
            {
                // Do not reset the adjacency list, just skip the rest of the function
                return;
            }
        }
        // If the vertex is not a special cell, add it to the adjacency list
        adjacencyList[vertex] = LinkedList<int>();
    }

    // Display the adjacency list for debugging purposes
    void displayGraph()
    {
        for (int i = 0; i < vertices; ++i)
        {
            cout << "Vertex " << i << ": ";
            Node<int> *current = adjacencyList[i].getHead();
            while (current != nullptr)
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
    }

    // Getter for the adjacency list
    LinkedList<int> *getAdjacencyList()
    {
        return adjacencyList;
    }

    // Getter for the number of vertices
    int getVertices()
    {
        return vertices;
    }

    void updateGraph(char maze[row][col])
    {
        // Reset the adjacency list
        for (int i = 0; i < vertices; ++i)
        {
            adjacencyList[i] = LinkedList<int>();
        }

        // Add edges based on maze structure
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                int currentVertex = i * col + j;

                if (maze[i][j] != OBSTACLE)
                {
                    if (i > 0 && maze[i - 1][j] != OBSTACLE)
                        addEdge(currentVertex, (i - 1) * col + j);

                    if (j > 0 && maze[i][j - 1] != OBSTACLE)
                        addEdge(currentVertex, i * col + (j - 1));

                    if (i < row - 1 && maze[i + 1][j] != OBSTACLE)
                        addEdge(currentVertex, (i + 1) * col + j);

                    if (j < col - 1 && maze[i][j + 1] != OBSTACLE)
                        addEdge(currentVertex, i * col + (j + 1));
                }
            }
        }
    }

    void displayMaze(char maze[row][col], const LinkedList<Coordintate> &path, int carRow, int carCol)
    {
        char tempMaze[row][col] = {};

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                tempMaze[i][j] = maze[i][j];
            }
        }

        // Update the path in tempMaze
        for (Node<Coordintate> *node = path.getHead(); node != nullptr; node = node->next)
        {
            tempMaze[node->data.x][node->data.y] = PATH;
        }

        // Update the car's position in tempMaze
        tempMaze[carRow][carCol] = CAR;

        // Display the maze
        cout << setw(73) << setfill('_');
        cout << "                               ";
        cout << setw(43) << setfill('_');
        cout << "\n";

        for (int i = 0; i < row; ++i)
        {
            cout << "|";
            for (int j = 0; j < col; ++j)
            {
                cout << maze[i][j] << ' ';
            }
            cout << "|                               |";
            for (int j = 0; j < col; ++j)
            {
                cout << tempMaze[i][j] << ' ';
            }
            cout << "|";
            cout << endl;
        }
        cout << setw(73) << setfill('-');
        cout << "                               ";
        cout << setw(43) << setfill('-');
        cout << "\n";
    }

    ~Graph()
    {
        delete[] adjacencyList;
    }
};

void generateRandomMaze(char maze[row][col], Graph &graph)
{
    srand(static_cast<unsigned int>(time(0)));

    // Fill the maze with random obstacles
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (rand() % 8 == 0)
            {
                maze[i][j] = OBSTACLE;
            }
            else
            {
                maze[i][j] = ' ';
            }
        }
    }

    // Place the START and FINISH points at random locations
    int startVertex = 0;
    // the row = 17 and col = 18 for finish vertex
    int finishVertex = (row - 1) * col + (col - 1);

    maze[startVertex / col][startVertex % col] = START;
    maze[finishVertex / col][finishVertex % col] = FINISH;

    // Add edges based on maze structure
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            int currentVertex = i * col + j;

            if (maze[i][j] != OBSTACLE)
            {
                if (i > 0 && maze[i - 1][j] != OBSTACLE)
                    graph.addEdge(currentVertex, (i - 1) * col + j);

                if (j > 0 && maze[i][j - 1] != OBSTACLE)
                    graph.addEdge(currentVertex, i * col + (j - 1));

                if (i < row - 1 && maze[i + 1][j] != OBSTACLE)
                    graph.addEdge(currentVertex, (i + 1) * col + j);

                if (j < col - 1 && maze[i][j + 1] != OBSTACLE)
                    graph.addEdge(currentVertex, i * col + (j + 1));
            }
        }
    }

    // Add vertices based on START and FINISH points
    graph.addVertex(startVertex, maze);
    graph.addVertex(finishVertex, maze);
}

int findShortestPathLength(char maze[row][col], Graph &graph, LinkedList<Coordintate> &shortestPath)
{
    // Create a priority queue to store the vertices
    LinkedListPriorityQueue<Coordintate> priorityQueue;

    // Create an array to store the distance of each vertex from the start vertex
    int *distance = new int[graph.getVertices()];

    // Create an array to store the previous vertex for each vertex
    int *previous = new int[graph.getVertices()];

    // Initialize the distance and previous arrays
    for (int i = 0; i < graph.getVertices(); ++i)
    {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    // Set the distance of the start vertex to 0
    distance[0] = 0;

    // Add the start vertex to the priority queue
    priorityQueue.Enqueue(Coordintate(0, 0, 0));

    // Loop until the priority queue is empty
    while (!priorityQueue.empty())
    {
        // Get the vertex with the shortest distance from the priority queue
        Coordintate current = priorityQueue.top();
        priorityQueue.Dequeue();

        // Check if the current vertex is the finish vertex
        if (current.x == (row - 1) && current.y == (col - 1))
        {
            // Loop until the start vertex is reached
            while (previous[current.x * col + current.y] != -1)
            {
                // Add the current vertex to the front of the path
                shortestPath.push_front(current);

                // Get the previous vertex
                current = Coordintate(0, previous[current.x * col + current.y] / col, previous[current.x * col + current.y] % col);
            }

            // Add the start vertex to the front of the path
            shortestPath.push_front(current);

            // Return the length of the shortest path
            return shortestPath.size() - 1;
        }

        // Get the adjacency list for the current vertex
        LinkedList<int> *adjacencyList = graph.getAdjacencyList();

        // Loop through the adjacency list
        for (Node<int> *node = adjacencyList[current.x * col + current.y].getHead(); node != nullptr; node = node->next)
        {
            // Get the vertex in the adjacency list
            int vertex = node->data;

            // Calculate the distance of the vertex from the start vertex
            int distanceFromCurrent = distance[current.x * col + current.y] + 1;

            // Check if the distance is shorter than the current distance
            if (distanceFromCurrent < distance[vertex])
            {
                // Update the distance
                distance[vertex] = distanceFromCurrent;

                // Update the previous vertex
                previous[vertex] = current.x * col + current.y;

                // Add the vertex to the priority queue
                priorityQueue.Enqueue(Coordintate(distance[vertex], vertex / col, vertex % col));
            }
        }
    }

    // If the finish vertex is not reached, the path is not found, and shortestPath will be empty.
    return -1;
}

// Function to move the car along the shortest path automatically
void moveCarAutomatically(char maze[row][col], Graph &graph, int &carRow, int &carCol, LinkedList<Coordintate> &shortestPath)
{
    // Get the next vertex in the shortest path
    Coordintate nextVertex = shortestPath.getHead()->next->data;

    // Check if the car is at the next vertex
    if (carRow == nextVertex.x && carCol == nextVertex.y)
    {
        // Remove the next vertex from the shortest path
        shortestPath.pop_front();

        // Get the next vertex in the shortest path
        nextVertex = shortestPath.getHead()->next->data;
    }

    // Move the car towards the next vertex
    if (carRow > nextVertex.x)
    {
        maze[carRow][carCol] = TURN;
        carRow--;
    }
    else if (carRow < nextVertex.x)
    {
        maze[carRow][carCol] = TURN;
        carRow++;
    }
    else if (carCol > nextVertex.y)
    {
        maze[carRow][carCol] = TURN;
        carCol--;
    }
    else if (carCol < nextVertex.y)
    {
        maze[carRow][carCol] = TURN;
        carCol++;
    }
}

int main()
{
    // Create a 2D array to store the maze
    char maze[row][col];

    // Create a graph to store the maze
    Graph graph(row * col);

    int carRow = 0;
    int carCol = 0;

    LinkedList<Coordintate> shortestPath;

    // Generate a random maze
    generateRandomMaze(maze, graph);

    while (true)
    {
        system("cls");

        cout << "Select mode:\n";
        cout << "1. Manual Mode\n";
        cout << "2. Auto Mode\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";

        char modeChoice = _getch();

        switch (modeChoice)
        {
        case '1': // Manual Mode
            while (true)
            {
                // Update the graph based on the new maze state
                graph.updateGraph(maze);

                // Find the shortest path if the car position has changed
                if (shortestPath.empty() || carRow != shortestPath.getHead()->data.x || carCol != shortestPath.getHead()->data.y)
                {
                    shortestPath.clear();
                    int shortestPathLength = findShortestPathLength(maze, graph, shortestPath);

                    if (shortestPathLength == -1)
                    {
                        cout << "No path found!" << endl;
                    }
                    else
                    {
                        cout << "Shortest path length: " << shortestPathLength << endl;
                    }
                }

                // Display the maze and the shortest path
                graph.displayMaze(maze, shortestPath, carRow, carCol);

                char input = _getch();

                // Move the car based on user input
                switch (input)
                {
                case 'w': // Move up
                    if (carRow > 0 && maze[carRow - 1][carCol] != OBSTACLE)
                    {
                        maze[carRow][carCol] = ' ';
                        carRow--;
                    }
                    break;

                case 'a': // Move left
                    if (carCol > 0 && maze[carRow][carCol - 1] != OBSTACLE)
                    {
                        maze[carRow][carCol] = ' ';
                        carCol--;
                    }
                    break;
                case 's': // Move down
                    if (carRow < row - 1 && maze[carRow + 1][carCol] != OBSTACLE)
                    {
                        maze[carRow][carCol] = ' ';
                        carRow++;
                    }
                    break;
                case 'd': // Move right
                    if (carCol < col - 1 && maze[carRow][carCol + 1] != OBSTACLE)
                    {
                        maze[carRow][carCol] = ' ';
                        carCol++;
                    }
                    break;
                case 'm':
                    break; // Stay in manual mode
                case 'q':
                    exit(0);
                    break;
                }
                // Update the car position in the maze
                maze[carRow][carCol] = CAR;

                // Check if the car reached the finish
                if (maze[carRow][carCol] == FINISH)
                {
                    cout << "Congratulations! You reached the finish." << endl;
                    break;
                }
            }
            break;

        case '2': // Auto Mode
            while (true)
            {
                // Update the graph based on the new maze state
                graph.updateGraph(maze);

                // Find the shortest path if the car position has changed
                if (shortestPath.empty() || carRow != shortestPath.getHead()->data.x || carCol != shortestPath.getHead()->data.y)
                {
                    shortestPath.clear();
                    int shortestPathLength = findShortestPathLength(maze, graph, shortestPath);

                    if (shortestPathLength == -1)
                    {
                        cout << "No path found!" << endl;
                    }
                    else
                    {
                        cout << "Shortest path length: " << shortestPathLength << endl;
                    }
                }

                // Display the maze and the shortest path
                graph.displayMaze(maze, shortestPath, carRow, carCol);

                // Move the car automatically
                moveCarAutomatically(maze, graph, carRow, carCol, shortestPath);

                // Check if the car reached the finish
                if (maze[carRow][carCol] == FINISH)
                {
                    cout << "Congratulations! You reached the finish." << endl;
                    break;
                }

                // Wait for 1 second
                Sleep(1000);
            }
            break;
        case '3': // Quit
            exit(0);
            break;

        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    }

    return 0;
}
