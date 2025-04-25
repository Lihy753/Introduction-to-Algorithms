#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <array>
#include <list>
#include <vector>


//direcr-address table
//关键字的全域 U 比较小时，直接寻址是一种简单而有效的技术。
template <typename T, size_t Size>
class DirectAddressTable
{
private:
    std::array<T, Size> table;
    std::array<bool, Size> occupied;
public:
    DirectAddressTable()
    {
        occupied.fill(false);
    };
    ~DirectAddressTable()
    {
    };

    void direct_address_insert(size_t key, const T& value)
    {
        if (key >= Size)
            throw std::out_of_range("The key is out of renge!");
        
        table[key] = value;
        occupied[key] = true;
    }

    void direct_address_remove(size_t key)
    {
        if (key >= Size)
            throw std::out_of_range("The key is out of renge!");

        occupied[key] = false;
    }

    T* direct_address_search(size_t key)
    {
        if (key >= Size || !occupied[key])
            return nullptr;

        return &table[key];  
    }
};

//使用链接法（chaining）的散列表。
template <typename Key, typename Value>
class ChainedHashTable
{
private:
    //定义链表
    struct Node
    {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v, Node* n = nullptr)
            : key(k), value(v), next(n){}
    };
    
    std::vector<Node*> table;
    size_t bucket_count;
    std::hash<Key> hash_function;

    //计算 key 的 hash 值，并确定其桶索引
    size_t getBucketIndex(const Key& key) const
    {
        return hash_function(key) & bucket_count;
    }

    void clearBucket(Node* head)
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        
    }
public:
    ChainedHashTable(size_t num_buckets) : bucket_count(num_buckets), table (num_buckets, nullptr){};
    ~ChainedHashTable(){
        for (Node* head : table)
        {
            clearBucket(head);
        }
    };

    void ChainedHashInsert(const Key& key, const Value& value)
    {
        size_t index = getBucketIndex(key);
        Node* head = table[index];

        for (Node* node = head; node != nullptr; node = node->next)
        {
            if (node->key == key)
            {
                node->value = value;
                return;
            }
        }

        table[index] = new Node(key, value, head);
    }

    Value* ChainedHashSearch(const Key& key)
    {
        size_t index = getBucketIndex(key);
        Node* head = table[index];

        for (Node* node = head; node != nullptr; node = node->next)
        {
            if (node->key == key)
            {
                return &node->value;
            }
        }
        return nullptr;
    }

    void ChainedHashDelete(const Key& key)
    {
        size_t index = getBucketIndex(key);
        Node* head = table[index];
        Node* prev = nullptr;

        while (head)
        {
            if (head->key == key)
            {
                if (prev)
                    prev->next = head->next;
                else
                    table[index] = head->next;

                delete head;
                return;
            }
            prev = head;
            head = head->next;
        }
    }

    void print() const 
    {
        for (size_t i = 0; i < bucket_count; ++i) 
        {
            std::cout << "Bucket " << i << ": ";
            for (Node* node = table[i]; node != nullptr; node = node->next) {
                std::cout << "[" << node->key << ": " << node->value << "] ";
            }
            std::cout << "\n";
        }
    }
};







#endif