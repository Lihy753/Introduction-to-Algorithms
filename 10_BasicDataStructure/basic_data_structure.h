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

    ~stack()
    {
        m_array.clear();
        m_top_index = -1;
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
        if (head == tail + 1)
        {
            std::cout << "error : overflow" << std::endl;
            return;
        }

        m_array[tail] = x;
        if (tail == N - 1)
            tail = -1;
        else
            ++tail;
    }

    int DEQUEUE()
    {
        if (head == tail)
            std::cout << "error : underflow" << std::endl;

        int x = m_array[head];
        if (head == N - 1)
            head = 0;
        else
            ++head;
        
        return x;
    }

    void fetch_array(std::array<int, N>& result)
    {
        result = m_array;
    }

public:
    int head;
    int tail;
    std::array<int, N> m_array;
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
            friend class ListOperation;
            Node* head;
            Node* tail;
    };

    class DoublyLinkedListWithSentinel
    {
        public:
            DoublyLinkedListWithSentinel() 
            : nil(nullptr)
              {
              }

            ~DoublyLinkedListWithSentinel()
            {
                while (nil->next != nullptr)
                {
                    Node* temp = nil->next;
                    nil->next = nil->next->next;
                    delete temp;
                }
            }     

        private:
            friend class ListOperation;  
            Node* nil;
    };

    class ListOperation 
    {
        public:
            ListOperation(){}

            ~ListOperation(){}

            //搜索到 date == k 的节点并返回指向该节点的地址；
            Node* LIST_SEARCH(DoublyLinkedList& L, int k)
            {
                Node* x = L.head;
                while (x != NULL && x->date != k)
                {
                    x = x->next;
                }
                return x;
            }

            Node* LIST_SEARCH(DoublyLinkedListWithSentinel& L, int k)
            {
                Node* x = L.nil->next;
                while (x != L.nil && x->date != k)
                {
                    x = x->next;
                }
                return x;
            }

            //将节点 x 插入到链表的前段；
            void LIST_INSERT(DoublyLinkedList& L, Node* x)
            {
                x->next = L.head;
                if (L.head != NULL)
                    L.head->prev = x;
                L.head = x;
                x->prev = NULL;
            }

            void LIST_INSERT(DoublyLinkedListWithSentinel& L, Node* x)
            {
                x->next = L.nil->next;
                L.nil->next->prev = x;
                L.nil->next = x;
                x->prev = L.nil;
            }

            //删掉节点 x；
            void LIST_DELETE(DoublyLinkedList& L, Node* x)
            {
                if (x->prev != NULL)
                    x->prev->next = x->next;
                else
                    L.head = x->next;

                if (x->next != NULL)
                    x->next->prev = x->prev;
            }

            void LIST_DELETE(DoublyLinkedListWithSentinel& L, Node* x)
            {
                x->prev->next = x->next;
                x->next->prev = x->prev;
            }
    };
}


#endif