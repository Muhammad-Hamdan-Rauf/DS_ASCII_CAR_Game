
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <ctime>

#include "coordinate.hpp"
#include "LinkedList.hpp"
#include "priorityQueue.hpp"

using namespace std;

class Box
{
    char item[4][4];

public:
    Box()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                item[i][j] = ' ';
            }
        }
    }
    Box(char a)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                item[i][j] = a;
            }
        }
    }
    void makeCar()
    {
        char car[2][3] = {
            {char(178), char(178), char(178)},
            {char(153), ' ', char(153)}};
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                item[i][j] = car[i][j];
            }
        }
    }

    // make obstacle using ascii values 239 and 206
    

    bool operator==(Box other)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (item[i][j] != other.item[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(Box other)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (item[i][j] == other.item[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    void Dispaly(int i, int j)
    {
        cout << item[i][j];
    }
};

Box START('S');

Box FINISH('F');

Box CAR('C');

Box OBSTACLE('#');

Box TURN('T');

Box PATH('-');

Box b;

// const int row = 10;
// const int col = 20;

int dijkstra(Box maze[row][col], int startX, int startY, int finishX, int finishY, LinkedList<Coordintate> &shortestPath)
{
    Coordintate start(0, startX, startY);
    Coordintate Finish(0, finishX, finishY);
    int distance[row][col] = {0};
    bool visited[row][col] = {0};
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            distance[i][j] = INT_MAX;
            visited[i][j] = 0;
        }
    }

    PriorityQueue<Coordintate> pq;
    pq.Enqueue(start);
    distance[startX][startY] = 0;

    while (!pq.empty())
    {
        int x = pq.top().x;
        int y = pq.top().y;
        int dist = pq.top().distance;
        pq.Dequeue();

        if (maze[x][y] == TURN || (x == finishX && y == finishY))
        {
            int currentX = x;
            int currentY = y;
            while (currentX != startX || currentY != startY)
            {
                shortestPath.insert(Coordintate(0, currentX, currentY));

                int dx[] = {-1, 0, 1, 0};
                int dy[] = {0, 1, 0, -1};
                for (int i = 0; i < 4; ++i)
                {
                    int newX = currentX + dx[i];
                    int newY = currentY + dy[i];
                    if (isValid(newX, newY) && distance[newX][newY] + 1 == distance[currentX][currentY])
                    {
                        currentX = newX;
                        currentY = newY;

                        // Check if the current position is a TURN
                        if (maze[currentX][currentY] == TURN)
                        {
                            shortestPath.insert(Coordintate(0, currentX, currentY));

                            // Move to the next row (car can only move from turn to turn)
                            while (currentX == newX)
                            {
                                currentX = newX;
                                currentY = newY;
                                newX = currentX + dx[i];
                                newY = currentY + dy[i];
                            }
                        }
                        break;
                    }
                }
            }
            shortestPath.insert(start);

            // Reverse the linked list to get the correct order
            shortestPath.reverse();
            return dist;
        }

        if (!visited[x][y])
        {
            visited[x][y] = true;

            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, 1, 0, -1};

            for (int i = 0; i < 4; ++i)
            {
                int newX = x + dx[i];
                int newY = y + dy[i];

                if (isValid(newX, newY) && maze[newX][newY] != OBSTACLE && !visited[newX][newY])
                {
                    int weight = 1;

                    if (distance[x][y] + weight < distance[newX][newY])
                    {
                        distance[newX][newY] = distance[x][y] + weight;
                        Coordintate c(distance[newX][newY], newX, newY);
                        pq.Enqueue(c);
                    }
                }
            }
        }
    }

    return -1;
}

// int dijkstra(Box maze[row][col], int startX, int startY, int finishX, int finishY, LinkedList<Coordintate> &shortestPath)
// {
//     Coordintate start(0, startX, startY);
//     Coordintate Finish(0, finishX, finishY);
//     int distance[row][col] = {0};
//     bool visited[row][col] = {0};
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < col; j++)
//         {
//             distance[i][j] = INT_MAX;
//             visited[i][j] = 0;
//         }
//     }

//     PriorityQueue<Coordintate> pq;
//     pq.Enqueue(start);
//     distance[startX][startY] = 0;

//     while (!pq.empty())
//     {
//         int x = pq.top().x;
//         int y = pq.top().y;
//         int dist = pq.top().distance;
//         pq.Dequeue();

//         if (maze[x][y] == TURN || (x == finishX && y == finishY))
//         {
//             int currentX = x;
//             int currentY = y;
//             while (currentX != startX || currentY != startY)
//             {
//                 // shortestPath.insert(Coordintate(0, currentX, currentY));
//                 // int dx[] = {-1, 0, 1, 0};
//                 // int dy[] = {0, 1, 0, -1};
//                 // for (int i = 0; i < 4; ++i)
//                 // {
//                 //     int newX = currentX + dx[i];
//                 //     int newY = currentY + dy[i];
//                 //     if (isValid(newX, newY) && distance[newX][newY] + 1 == distance[currentX][currentY])
//                 //     {
//                 //         currentX = newX;
//                 //         currentY = newY;
//                 //         break;
//                 //     }
//                 // }
//                 // // Check if the current position is a TURN
//                 // if (maze[currentX][currentY] == TURN)
//                 // {
//                 //     shortestPath.insert(Coordintate(0, currentX, currentY));
//                 // }

//                 shortestPath.insert(Coordintate(0, currentX, currentY));
//                 int dx[] = {-1, 0, 1, 0};
//                 int dy[] = {0, 1, 0, -1};
//                 for (int i = 0; i < 4; ++i)
//                 {
//                     int newX = currentX + dx[i];
//                     int newY = currentY + dy[i];
//                     if (isValid(newX, newY) && distance[newX][newY] + 1 == distance[currentX][currentY])
//                     {
//                         currentX = newX;
//                         currentY = newY;

//                         // Check if the current position is a TURN
//                         if (maze[currentX][currentY] == TURN)
//                         {
//                             shortestPath.insert(Coordintate(0, currentX, currentY));

//                             // Move to the next row (car can only move from turn to turn)
//                             while (currentX == newX)
//                             {
//                                 currentX = newX;
//                                 currentY = newY;
//                                 newX = currentX + dx[i];
//                                 newY = currentY + dy[i];
//                             }
//                         }
//                         break;
//                     }
//                 }
//             }
//             shortestPath.insert(start);
//             return dist;
//         }

//         if (!visited[x][y])
//         {
//             visited[x][y] = true;

//             int dx[] = {-1, 0, 1, 0};
//             int dy[] = {0, 1, 0, -1};

//             for (int i = 0; i < 4; ++i)
//             {
//                 int newX = x + dx[i];
//                 int newY = y + dy[i];

//                 if (isValid(newX, newY) && maze[newX][newY] != OBSTACLE && !visited[newX][newY])
//                 {
//                     int weight = 1;

//                     if (distance[x][y] + weight < distance[newX][newY])
//                     {
//                         distance[newX][newY] = distance[x][y] + weight;
//                         Coordintate c(distance[newX][newY], newX, newY);
//                         pq.Enqueue(c);
//                     }
//                 }
//             }
//         }
//     }

//     return -1;
// }

void displayMaze(Box maze[row][col], LinkedList<Coordintate> &path)
{

    Box tempMaze[row][col] = {};
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            tempMaze[i][j] = maze[i][j];
        }
    }
    Node<Coordintate> *node = path.getHead()->next;
    while (node->next)
    {
        tempMaze[node->data.x][node->data.y] = PATH;
        node = node->next;
    }

    cout << setw(83) << setfill('_');
    cout << "\n";

    for (int i = 0; i < row; ++i)
    {
        cout << "|";
        for (int j = 0; j < col; ++j)
        {
            for (int k = 0; k < 3; k++)
            {
                tempMaze[i][j].Dispaly(0, k);
            }
            cout << ' ';
        }
        cout << "|";
        cout << endl;
        cout << "|";
        for (int j = 0; j < col; ++j)
        {
            for (int k = 0; k < 3; k++)
            {
                tempMaze[i][j].Dispaly(1, k);
            }
            cout << ' ';
        }
        cout << "|";
        cout << endl;
    }
    cout << setw(83) << setfill('-');
    cout << "\n";
}

void generateRandomMaze(Box maze[row][col])
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (rand() % 10 == 0)
            {
                if (rand() % 2 == 0)
                {
                    maze[i][j] = OBSTACLE;
                }
                else
                {
                    maze[i][j] = TURN;
                }
            }
            else
            {
                maze[i][j] = b;
            }
        }
    }
    maze[0][3] = TURN;
    maze[1][6] = TURN;
    maze[2][8] = TURN;
    maze[3][10] = TURN;
    maze[4][5] = TURN;
    maze[5][11] = TURN;
    maze[6][14] = TURN;
    maze[7][2] = TURN;
    maze[8][4] = TURN;
    maze[9][7] = TURN;

    maze[9][17] = START;
    maze[0][1] = FINISH;
}

int main()
{
    CAR.makeCar();
    START.makeCar();
    Box maze[row][col];
    generateRandomMaze(maze);
    while (true)
    {
        system("cls");
        cout << "Select mode:\n";
        cout << "1. Manual Mode\n";
        cout << "2. Automated Mode\n";
        cout << "3. Exit\n";

        char modeChoice = _getch();
        generateRandomMaze(maze);
        int carRow = 0;
        int carCol = 0;

        if (modeChoice == '1')
        {
            Box x = b;
            while (true)
            {
                system("cls");
                int startX = 0, startY = 0, finishX = 0, finishY = 0;
                for (int i = 0; i < row; ++i)
                {
                    for (int j = 0; j < col; ++j)
                    {
                        if (maze[i][j] == START)
                        {
                            startX = carRow = i;
                            startY = carCol = j;
                        }
                        else if (maze[i][j] == FINISH)
                        {
                            finishX = i;
                            finishY = j;
                        }
                    }
                }
                LinkedList<Coordintate> shortestPath;
                int shortestPathLength = dijkstra(maze, startX, startY, finishX, finishY, shortestPath);
                cout << shortestPathLength << endl;
                if (shortestPathLength != -1)
                {
                    cout << "Shortest path length: " << shortestPathLength << endl;
                    displayMaze(maze, shortestPath);
                }

                char input = _getch();
                switch (input)
                {
                case 'w':
                    if (carRow > 0 && maze[carRow - 1][carCol] != OBSTACLE)
                        if (x == TURN)
                        {
                            maze[carRow][carCol] = x;
                            carRow--;
                            x = maze[carRow][carCol];
                        }
                    break;
                case 'a': // Move left
                    if (carCol > 0 && maze[carRow][carCol - 1] != OBSTACLE)
                    {
                        maze[carRow][carCol] = x;
                        carCol--;
                        x = maze[carRow][carCol];
                    }
                    break;
                case 's': // Move down
                    if (carRow < row - 1 && maze[carRow + 1][carCol] != OBSTACLE)
                        if (x == TURN)
                        {
                            maze[carRow][carCol] = x;
                            carRow++;
                            x = maze[carRow][carCol];
                        }
                    break;
                case 'd': // Move right
                    if (carCol < col - 1 && maze[carRow][carCol + 1] != OBSTACLE)
                    {
                        maze[carRow][carCol] = x;
                        carCol++;
                        x = maze[carRow][carCol];
                    }
                    break;
                case 'q':
                    exit(0);
                    break;
                }

                // Check if the car reached the finish
                if (maze[carRow][carCol] == FINISH)
                {
                    cout << "Congratulations! You reached the finish." << endl;
                    break;
                }

                // Update the car position in the maze
                maze[carRow][carCol] = START;
            }
        }

        else if (modeChoice == '2')
        { // Automated Mode
            int startX, startY, finishX, finishY;

            // Define start and finish points (you can change these values)
            startX = 0;
            startY = 0;
            finishX = 9;
            finishY = 19;

            LinkedList<Coordintate> shortestPath;
            int shortestPathLength = dijkstra(maze, startX, startY, finishX, finishY, shortestPath);

            if (shortestPathLength != -1)
            {
                cout << "Shortest path length: " << shortestPathLength << endl;
                displayMaze(maze, shortestPath);

                // Move the car along the shortest path
                for (Node<Coordintate> *node = shortestPath.getHead(); node != nullptr; node = node->next)
                {
                    system("cls");
                    maze[carRow][carCol] = b; // Clear the current position
                    carRow = node->data.x;
                    carCol = node->data.y;
                    maze[carRow][carCol] = CAR; // Set the new position
                    displayMaze(maze, shortestPath);

                    // Check if the car reached the finish in each iteration
                    if (carRow == finishX && carCol == finishY)
                    {
                        cout << "Congratulations! You reached the finish." << endl;
                        break;
                    }

                    Sleep(500); // Adjust the sleep duration (milliseconds) to control the speed
                }

                cout << "Press any key to continue...";
                _getch();
            }
            else
            {
                cout << "No valid path found.\n";
                cout << "Press any key to continue...";
                _getch();
            }
        }

        else if (modeChoice == '3')
        { // Exit
            exit(0);
        }

        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
