#ifndef BASICDATASTRUCTURE_H
#define BASICDATASTRUCTURE_H

#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <array>


//后进先出
class stack
{
public:
    stack()
        : m_top_index(-1)
    {
    }

    bool STACK_EMPTY()
    {
        return m_top_index == -1;
    }

    int top()
    {
        return m_top_index;
    }

    void PUSH(int x)
    {
        ++m_top_index;
        m_array[m_top_index] = x;
    }

    void POP(int x)
    {
        if (STACK_EMPTY())
            std::cout << "error : underflow" << std::endl;
        else
            m_top_index--;
    }

public:
    std::vector<int> m_array;
    int m_top_index;

};

template <size_t N>
class queue
{
public : 
    queue()
    {
        head = tail = 0;
    }

    void ENQUEUE(int x)
    {
        if ((tail == N && head == 0) || head == tail + 1)
        {
            std::cout << "error : overflow" << std::endl;
            return;
        }

        m_array[tail] = x;
        if (tail == N)
            tail = 0;
        else
            ++tail;
    }

    int DEQUEUE()
    {
        if (head == tail)
            std::cout << "error : underflow" << std::endl;

        int x = m_array[head];
        if (head == N )
            head = 0;
        else
            ++head;
        
        return x;
    }

    void fetch_array(std::array<int, N + 1>& result)
    {
        result = m_array;
    }

public:
    int head;
    int tail;
    std::array<int, N + 1> m_array;
};
namespace linkedList
{
    class Node
    {
    public:
        Node(int val) 
            : date(val), 
             prev(nullptr), 
             next(nullptr) 
        {
        }
        int date;
        Node* prev;
        Node* next;
    };

    class DoublyLinkedList
    {
        public:
            DoublyLinkedList() 
            : head(nullptr), 
              tail(nullptr)
              {
              }

            ~DoublyLinkedList()
            {
                while (head != nullptr)
                {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
            }

            void append(int value)
            {
                Node* newNode = new Node(value);
                if (tail == nullptr)
                {
                    head = tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
            }

            void prepend(int value)
            {
                Node* newNode = new Node(value);
                if (head == nullptr)
                {
                    head = tail = newNode;
                }
                else
                {
                    newNode->next = head;
                    head->prev = newNode;
                    head = newNode;
                }
            }

            void remove(int value)
            {
                Node* current = head;
                while (current != nullptr)
                {
                    if (current->date == value)
                    {
                        if (current->prev != nullptr)
                            current->prev->next = current->next;
                        else
                            head = current->next;
                        
                        if (current->next != nullptr)
                            current->next->prev = current->prev;
                        else
                            tail = current->prev;
                        
                        delete current;
                        return;
                    }
                    current = current->next;
                }
            }

            void printList()
            {
                Node* current = head;
                while (current != nullptr)
                {
                    std::cout << current->date << " ";
                    current = current->next;
                }
                std::cout << std::endl;
            }

        private:
            Node* head;
            Node* tail;
    };

        


}

#endif