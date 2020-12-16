#pragma once
#include <cstddef>


namespace task {


class list {

public:

    list();
    list(const list& other);
    list(size_t count, const int& value = int());

    ~list();
    list& operator=(const list& other);


    int& front();
    const int& front() const;

    int& back();
    const int& back() const;


    bool empty() const;
    size_t size() const;
    void clear();


    void push_back(const int& value);
    void pop_back();
    void push_front(const int& value);
    void pop_front();
    void resize(size_t count);
    void swap(list& other);


    void remove(const int& value);
    void unique();
    void sort();

    

private:

    struct Node {
        Node* prev;
        Node* next;
        
        int value;

        Node(Node* _prev, Node* _next, const int& val) : prev(_prev), next(_next), value(val) { }
        Node() : prev(nullptr), next(nullptr), value(0) { }
    };

    void __push_first__(const int& value);
    void __remove_node_(Node* nd);

    Node* head;
    Node* tail;

    int _size;

};

}  // namespace task
