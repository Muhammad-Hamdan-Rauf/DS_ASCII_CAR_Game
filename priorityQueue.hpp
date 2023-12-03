#include <iostream>
using namespace std;

template <typename T>
class PriorityQueueNode
{
public:
    T data;
    PriorityQueueNode *next;
    PriorityQueueNode(T value)
    {
        data = value;
        next = NULL;
    }
};

template <typename T>
class PriorityQueue
{
private:
    PriorityQueueNode<T> *Top;

public:
    PriorityQueue()
    {
        Top = NULL;
    }

    void Enqueue(T value)
    {
        PriorityQueueNode<T> *newNode = new PriorityQueueNode<T>(value);
        if (!Top || value < Top->data)
        {
            newNode->next = Top;
            Top = newNode;
            return;
        }
        else
        {
            PriorityQueueNode<T> *current = Top;
            while (current->next && current->next->data < value)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void Dequeue()
    {
        if (Top)
        {
            PriorityQueueNode<T> *temp = Top;
            Top = Top->next;
            delete temp;
        }
    }

    T top()
    {
        if (Top)
        {
            return Top->data;
        }
    }

    bool empty()
    {
        if (Top)
        {
            return 0;
        }
        return 1;
    }
};
