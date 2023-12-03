#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include<string>
#include <chrono>
#include <thread>
using namespace std;
class Box {
	char item[4][4];
public:
	Box() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				item[i][j] = ' ';
			}
		}
		item[0][0] = char(196);
		item[0][1] = char(196);
		item[0][2] = char(196);
		item[1][0] = char(196);
		item[1][1] = char(196);
		item[1][2] = char(196);
	}
	Box(char a) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				item[i][j] = a;
			}
		}
	}
	void makeCar() {
	char car[2][3] = {
	{char(220), char(219), char(220)},
	{char(233), ' ', char(233)}
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			item[i][j] = car[i][j];
		}
	}

	}
	void makeObstacle() {
		char car[2][3] = {
		{' ', char(157), ' '},
		{' ', char(219), ' '}
		};
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				item[i][j] = car[i][j];
			}
		}

	}
	void MakeTurn() {
		char car[2][3] = {
		{'=', char(202), '='},
		{'=', char(203), '='}
		};
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				item[i][j] = car[i][j];
			}
		}

	}
	void Makepath() {
		char car[2][3] = {
		{' ', '*', ' '},
		{' ', ' ', ' '}
		};
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				item[i][j] = car[i][j];
			}
		}

	}

	bool operator==(Box other) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (item[i][j] != other.item[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(Box other)  {
		if (!(*this == other)) {
			return 1;
		}
		return 0;


	}
	void Display(int i, int j) {
		cout << item[i][j];
	}

};

Box START('S');
Box FINISH('F');
Box CAR('C');
Box OBSTACLE('#');
Box TURN('T');
Box PATH('-');
Box PowerUP('!');
Box b;

class Achivement {
public:
	string a;
	bool status;
	int scoreReq;
	int timeReq;

	Achivement(int sc,int t) {
		a = "Complete Level while having score greater than " + to_string(sc) + " and time less than " + to_string(t);
		status = 0;
		scoreReq = sc;
		timeReq = t;
	}
	Achivement() {

	}

	bool isCompleted(int s,int t) {
		if (status == 0) {
			if (scoreReq >= s && timeReq <= t) {
				status = 1;
				return 1;
			}
		}
		return 0;
	}
	void display() {
		cout << "Achievement: " << a << "Status: ";
		if (status) {
			cout << "Completed\n";
		}
		else
		{
			cout << "Not Completed\n";

		}
	}

};
class Coordintate
{
public:
	int distance;
	int x, y;
	Coordintate()
	{
		x = 0;
		y = 0;
		distance = 0;
	}
	Coordintate(int d, int a, int b)
	{
		distance = d;
		x = a;
		y = b;
	}
	bool operator<( Coordintate& other) 
	{
		return distance < other.distance;
	}
	bool operator==(Coordintate& other)
	{
		if (x == other.x && y == other.y) {
			return 1;
		}
		return 0;
	}
};


template <typename T>
class Node
{
public:
	T data;
	Node* next;

	Node(const T& value)
	{
		data = value;
		next = nullptr;
	}
};
template <typename T>
class LinkedList{
private:
	Node<T>* head;

public:
	LinkedList(){
		head = NULL;
	}

	Node<T>* getHead() {
		return head;
	}

	void insert(T value){
		Node<T>* newNode = new Node<T>(value);

		if (!head){
			head = newNode;
		}
		else{
			Node<T>* current = head;
			while (current->next)
			{
				current = current->next;
			}
			current->next = newNode;
		}
	}
	void clear() {
		Node<T>* current = head;
		while (current)
		{	
			Node<T>* temp = current;
			current = current->next;
			delete temp;

		}
		head = NULL;
	}
	void reverse()
	{
		Node<T>* current = head;
		Node<T>* prev = NULL;
		Node<T>* next = NULL;

		while (current)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		head = prev;
	}


};
template <typename T>
class PriorityQueueNode{
public:
	T data;
	PriorityQueueNode* next;
	PriorityQueueNode(T value){
		data = value;
		next = NULL;
	}
};
template <typename T>
class PriorityQueue{
private:
	PriorityQueueNode<T>* Top;
public:
	PriorityQueue(){
		Top = NULL;
	}

	void Enqueue(T &value){
		PriorityQueueNode<T>* newNode = new PriorityQueueNode<T>(value);
		if (!Top || value < Top->data)
		{
			newNode->next = Top;
			Top = newNode;
			return;
		}
		else {
			PriorityQueueNode<T>* current = Top;
			while (current->next && current->next->data < value){
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
	}

	void Dequeue(){
		if (Top){
			PriorityQueueNode<T>* temp = Top;
			Top = Top->next;
			delete temp;
		}
	}

	T *top() {
		if (Top){
			return &Top->data;
		}

	}

	bool empty(){
		if (Top) {
			return 0;
		}
		return 1;
	}
};


class Timer {
public:
	Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

	void reset() {
		start_time = std::chrono::high_resolution_clock::now();
	}

	double elapsed() const {
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
		return duration.count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};


template <typename T>
class QueueNode {
public:
	QueueNode* Next = NULL;
	T data = T();
};

template <typename T>
class Queue {
	QueueNode<T>* front;
	QueueNode<T>* rear;

public:
	Queue() {
		front = NULL;
		rear = NULL;
	}
	void enqueue(T a) {
		QueueNode<T>* newNode = new QueueNode<T>;
		newNode->data = a;
		if (isEmpty()) {
			front = newNode;
			rear = newNode;
		}
		else {
			rear->Next = newNode;
			rear = newNode;
		}
	}
	T dequeue() {
		QueueNode<T>* deleteNode = front;
		if (isEmpty()) {
			cout << "Queue is already empty\n";
			return T();
		}
		else {
			T num = front->data;
			QueueNode<T>* temp = front->Next;
			delete front;
			front = temp;
			if (isEmpty()) {
				rear = NULL;
			}
			return num;
		}
	}
	T showFront() {
		if (isEmpty()) {
			cout << "Queue is empty\n";
			return T();
		}
		return front->data;
	}
	bool isEmpty() {
		return (front == NULL);
	}
};
class Maze {
	Box** maze;
	int row, col;
public:
	Maze() {
		row = 10;
		col = 20;
		maze = new Box * [row];
		for (int i = 0; i < row; i++)
		{
			maze[i] = new Box[col];
		}
	}
	void generateRandomMaze(Queue<Box> q, Queue<Box> q2)
	{
		srand(time(0));
		row = rand() % 5 + 10;  //10-14
		col = rand() % 5 + 22;  //22-26
		maze = new Box * [row];
		for (int i = 0; i < row; i++)
		{
			maze[i] = new Box[col];
		}

		srand((time(0)));

		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				maze[i][j] = b;
			}
		}

		for (int i = 0; i < row; i++) {
			maze[i][rand() % col] = TURN;
		}
		Sleep(1);
		for (int i = 0; i < row; i++) {
			maze[i][rand() % col] = TURN;
		}

		maze[0][rand() % col] = START;
		maze[row - 1][rand() % col] = FINISH;
		while (!q.isEmpty())
		{

			int x1 = rand() % row, y1 = rand() % col;
			while (maze[x1][y1] != b) {
				x1 = rand() % row, y1 = rand() % col;
			}
			
			maze[x1][y1] = q.showFront();
			LinkedList<Coordintate> path;
			int a = dijkstra(path);
			if (a == -1) {
				maze[x1][y1] = b;
				continue;
			}
			else {

				//displayMaze();
				//Sleep(200);
				//system("cls");
				q.dequeue();
			}

		}
		while (!q2.isEmpty())
		{
			int x1 = rand() % row, y1 = rand() % col;
			while (maze[x1][y1] != b) {
				x1 = rand() % row, y1 = rand() % col;
			}
			maze[x1][y1] = q2.showFront();
			//displayMaze();
			//Sleep(200);
			//system("cls");
			q2.dequeue();

		}
	}
	void displayMaze(LinkedList<Coordintate>& path) {

		Box **tempMaze = new Box * [row];
		for (int i = 0; i < row; i++)
		{
			tempMaze[i] = new Box[col];
		}

		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				tempMaze[i][j] = maze[i][j];
			}
		}

		Node<Coordintate>* node = path.getHead();
		while (node->next) {
			if (maze[node->data.x][node->data.y] != TURN)
				tempMaze[node->data.x][node->data.y] = PATH;
			node = node->next;
		}

		cout << char(218);
		cout << setw(col * 4 + 1) << setfill(char(196));
		cout << char(191) << "\n";

		for (int i = 0; i < row; ++i)
		{
			cout << char(179);
			for (int j = 0; j < col; ++j)
			{
				for (int k = 0; k < 3; k++) {
					tempMaze[i][j].Display(0, k);

				}
				cout << ' ';
			}
			cout << char(179);
			cout << endl;
			cout << char(179);
			for (int j = 0; j < col; ++j)
			{
				for (int k = 0; k < 3; k++) {
					tempMaze[i][j].Display(1, k);

				}
				cout << ' ';
			}
			cout << char(179);
			cout << endl;
		}
		cout << char(192);
		cout << setw(col * 4 + 1) << setfill(char(196));
		cout << char(217) << "\n";
	}
	void displayMaze() {
		cout << char(195);
		cout << setw(col * 4 + 1) << setfill(char(196));
		cout <<char(180) <<"\n";

		for (int i = 0; i < row; ++i)
		{
			cout << char(179);
			for (int j = 0; j < col; ++j)
			{
				for (int k = 0; k < 3; k++) {
					maze[i][j].Display(0, k);

				}
				cout << ' ';
			}
			cout << char(179);
			cout << endl;
			cout << char(179);
			for (int j = 0; j < col; ++j)
			{
				for (int k = 0; k < 3; k++) {
					maze[i][j].Display(1, k);

				}
				cout << ' ';
			}
			cout << char(179);
			cout << endl;
		}
		cout << char(192);
		cout << setw(col * 4 + 1) << setfill(char(196));
		cout << char(217) << "\n";
	}

	int dijkstra(LinkedList<Coordintate>& path) {
		int startX = 0, startY = 0, finishX = 0, finishY = 0;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (maze[i][j] == START)
				{
					startX = i;
					startY = j;
				}
				else if (maze[i][j] == FINISH)
				{
					finishX = i;
					finishY = j;
				}
			}
		}
		Coordintate start(0, startX, startY);
		Coordintate Finish(0, finishX, finishY);
		int** distance = new int* [row];
		bool** visited = new bool* [row];
		int** Parentx = new int* [row];
		int** Parenty = new int* [row];
		for (int i = 0; i < row; i++)
		{
			distance[i] = new int[col];
			visited[i] = new bool[col];
			Parentx[i] = new int[col];
			Parenty[i] = new int[col];
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				distance[i][j] = 100;
				visited[i][j] = 0;
				Parentx[i][j] = -1;
				Parenty[i][j] = -1;
			}
		}

		PriorityQueue<Coordintate> pq;
		pq.Enqueue(start);
		distance[startX][startY] = 0;

		while (!pq.empty()) {
			Coordintate* current=pq.top();
			if (!visited[current->x][current->y]) {
				visited[current->x][current->y] = 1;

				if (isValid(current->x - 1, current->y) && maze[current->x - 1][current->y] != OBSTACLE) {
					if (maze[current->x][current->y] == TURN || maze[current->x - 1][current->y] == TURN) {
						if (distance[current->x][current->y] + 1 < distance[current->x - 1][current->y]) {
							distance[current->x - 1][current->y] = distance[current->x][current->y] + 1;
							Coordintate c(distance[current->x - 1][current->y], current->x - 1, current->y);

							Parentx[current->x - 1][current->y] = current->x;
							Parenty[current->x - 1][current->y] = current->y;
							pq.Enqueue(c);
						}
					}
				}
				if (isValid(current->x + 1, current->y) && maze[current->x + 1][current->y] != OBSTACLE) {//Down
					if (maze[current->x][current->y] == TURN || maze[current->x + 1][current->y] == TURN) {
						if (distance[current->x][current->y] + 1 < distance[current->x + 1][current->y]) {
							distance[current->x + 1][current->y] = distance[current->x][current->y] + 1;
							Coordintate c(distance[current->x + 1][current->y], current->x + 1, current->y);
							Parentx[current->x + 1][current->y] = current->x;
							Parenty[current->x + 1][current->y] = current->y;
							pq.Enqueue(c);
						}
					}
				}

				if (isValid(current->x, current->y - 1) && maze[current->x][current->y - 1] != OBSTACLE) {
						if (distance[current->x][current->y] + 1 < distance[current->x][current->y - 1]) {
							distance[current->x][current->y - 1] = distance[current->x][current->y] + 1;
							Coordintate c(distance[current->x][current->y-1], current->x, current->y-1);
							Parentx[current->x][current->y-1] = current->x;
							Parenty[current->x][current->y-1] = current->y;
							pq.Enqueue(c);
						}

					
				}
				if (isValid(current->x, current->y + 1)&& maze[current->x][current->y + 1] != OBSTACLE) {
						if (distance[current->x][current->y] + 1 < distance[current->x][current->y + 1]) {
							distance[current->x][current->y + 1] = distance[current->x][current->y] + 1;
							Coordintate c(distance[current->x][current->y + 1], current->x, current->y + 1);
							Parentx[current->x][current->y + 1] = current->x;
							Parenty[current->x][current->y + 1] = current->y;
							pq.Enqueue(c);
						}

					
				}
				pq.Dequeue();

			}


		}

		int d = 0;
		while (!(finishX == startX && finishY == startY)) {
			if (!(Parentx[finishX][finishY] == -1 && Parenty[finishX][finishY] == -1)) {
				int X = Parentx[finishX][finishY];
				int Y = Parenty[finishX][finishY];
				path.insert(Coordintate(0, X, Y));
				finishX = X;
				finishY = Y;
				d++;
			}
			else {
				return -1;
			}
		}
		path.reverse();
		return d;

	}
	bool isValid(int x, int y)
	{

		if (x >= 0 && x < row && y >= 0 && y < col) {
			return 1;
		}
		return 0;
	}
	void playManualMode() {
		Timer timer;

		Box x = b;
		int carlife = 5;
		int score = 0;
		while (carlife) {
			system("cls");
			cout << col << endl;
			cout << char(218);
			cout << setw(col * 4 + 1) << setfill(char(196));
			cout << char(191) << "\n";
			cout << setfill(' ');
			cout << char(179);
			cout << "Car Health Remaining:  " << setw(2)<<carlife << "       Score:    "<<setw(5)<<score;
			cout << "          Elapsed Time: " << setw(4 * col - 79) << timer.elapsed() << " seconds";
			cout << char(179) << endl;

			displayMaze();
			Sleep(100);
			int carRow = 0, carCol = 0;
			char input = _getch();
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					if (maze[i][j] == START)
					{
						carRow = i;
						carCol = j;
					}
				}
			}
			switch (input)
			{
			case 72://up
				if (isValid(carRow-1,carCol) && maze[carRow - 1][carCol] != OBSTACLE)
					if (x == TURN || maze[carRow - 1][carCol] == TURN)
					{
						maze[carRow][carCol] = x;
						carRow--;
						x = maze[carRow][carCol];
					}
				break;
			case 75: // Move left
				if (isValid(carRow, carCol-1)) {
					if (maze[carRow][carCol - 1] == OBSTACLE) {
						carlife--;
					}

					maze[carRow][carCol] = x;
					carCol--;
					x = maze[carRow][carCol];

				}

				break;
			case 80: //down
				if (isValid(carRow+1, carCol) && maze[carRow + 1][carCol] != OBSTACLE)
					if (x == TURN || maze[carRow + 1][carCol] == TURN)
					{
						maze[carRow][carCol] = x;
						carRow++;
						x = maze[carRow][carCol];
					}
				break;
			case 77: //Right
				if (isValid(carRow, carCol+1)) {
					if (maze[carRow][carCol + 1] == OBSTACLE) {
						carlife--;
					}
					maze[carRow][carCol] = x;
					carCol++;
					x = maze[carRow][carCol];

				}
				break;
			case 'q':
				return;
				break;
			}

			if (maze[carRow][carCol] == FINISH)
			{
				cout << "Congratulations! You reached the finish." << endl;
				break;
			}

			maze[carRow][carCol] = START;


		}
		if (carlife == 0) {
			system("cls");
			cout << "Game over\n";
		}
	}
	void displayMaze(Coordintate path) {

		Box** tempMaze = new Box * [row];
		for (int i = 0; i < row; i++)
		{
			tempMaze[i] = new Box[col];
		}

		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				tempMaze[i][j] = maze[i][j];
			}
		}

				tempMaze[path.x][path.y] = CAR;

		cout << char(218);
		cout << setw(col * 4 + 1) << setfill(char(196));
		cout << char(191) << "\n";

		for (int i = 0; i < row; ++i)
		{
			cout << char(179);
			for (int j = 0; j < col; ++j)
			{
				for (int k = 0; k < 3; k++) {
					tempMaze[i][j].Display(0, k);

				}
				cout << ' ';
			}
			cout << char(179);
			cout << endl;
			cout << char(179);
			for (int j = 0; j < col; ++j)
			{
				for (int k = 0; k < 3; k++) {
					tempMaze[i][j].Display(1, k);

				}
				cout << ' ';
			}
			cout << char(179);
			cout << endl;
		}
		cout << char(192);
		cout << setw(col * 4 + 1) << setfill(char(196));
		cout << char(217) << "\n";
	}

	void autoMode() {
		int shortestpath;
		LinkedList<Coordintate> path;
		shortestpath = dijkstra(path);
		Node<Coordintate>* current=path.getHead();
		while (current)
		{
			system("cls");
			displayMaze(current->data);
			Sleep(500);
			current = current->next;
		}
		
	}

};

int main()
{
	LinkedList<Achivement> Achivements;
	Achivement ach(100,10);
	Achivements.insert(ach);
	CAR.makeCar();
	START.makeCar();
	TURN.MakeTurn();
	PATH.Makepath();
	OBSTACLE.makeObstacle();
	Maze m;

	LinkedList<Coordintate> path;
	while (1) {
		cout << "1 for manual mode\n 2 for auto mode\n";


		char input = _getch();

		if (input == '1') {
			Queue<Box> Obstacles;
			for (int i = 0; i < 15; i++) {
				Obstacles.enqueue(OBSTACLE);
			}
			Queue<Box> PowerUps;
			for (int i = 0; i < 15; i++) {
				PowerUps.enqueue(PowerUP);
			}
			m.generateRandomMaze(Obstacles, PowerUps);
			m.playManualMode();
		}
		else if (input == '2') {
			Queue<Box> Obstacles;
			for (int i = 0; i < 15; i++) {
				Obstacles.enqueue(OBSTACLE);
			}
			Queue<Box> PowerUps;
			for (int i = 0; i < 15; i++) {
				PowerUps.enqueue(PowerUP);
			}
			m.generateRandomMaze(Obstacles, PowerUps);
			m.autoMode();
		}
	}
	return 0;
}