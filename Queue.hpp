#include <iostream>
#include <fstream>
#include <string>
#include <initializer_list>
#include <cstddef>

using namespace std;

template <typename T>
struct Node {
    T znach;
    Node<T> *next;
};

template <typename T>
struct ForwardList {
    Node<T> *head;
    Node<T> *last;
    void fill(ForwardList *&, T );
    int count_elements (ForwardList *&);
    void delete_element (ForwardList *&);
    void deleting (ForwardList *&);

};

template <typename T>
class Queue {
    public:
    Queue();
    Queue(initializer_list<T> );
    Queue(const Queue& );
    auto swap(Queue& ) -> void;
    auto operator=(const Queue& ) -> void;
    auto empty() -> bool;
    auto size() -> int;
    auto push(T) -> void;
    auto pop() -> void;
    auto front() -> T&;
    auto back() -> T&;
    bool operator==(const Queue& );
    ~Queue();
    template <typename T2>
    friend std::ostream& operator<< (std::ostream&, Queue<T2>&);
    template <typename T3>
    friend std::istream& operator>> (std::istream&, Queue<T3>&);

    private:
    ForwardList<T>* list;
};

template <typename T>
void ForwardList<T>::fill(ForwardList *&list, T integer1) {
    Node<T> *curr = new Node<T> {integer1, nullptr};
    if (list->head == nullptr)
    {   list->head = curr;
        list->last=curr;
    }
    else {
        if (list->head->next == nullptr) list->head->next = curr;
        if (list->last != nullptr) list->last->next = curr;
        list->last = curr;
    }
}

template <typename T>
int ForwardList<T>::count_elements (ForwardList *&list)
{
    Node<T> *curr= list->head;
    int count=0;
    while (curr!= nullptr) {
        ++count;
        curr= curr->next;
    }
    return count;
}

template <typename T>
void ForwardList<T>::delete_element (ForwardList *&list) {
    if (list->head==nullptr) return;
    Node<T> *curr= list->head;
    if (curr->next==nullptr) {
        delete list->head;
        list->head=nullptr;
        list->last= nullptr;
        return;
    }
    curr=list->head->next;
    delete list->head;
    list->head= curr;
    return;
}

template <typename T>
void ForwardList<T>::deleting (ForwardList *&list) {
    if (list->head!=nullptr) {
        Node<T>*curr= list->head;
        Node<T>*next_curr= list->head->next;
        while (next_curr!=nullptr) {
            delete curr;
            curr= next_curr;
            next_curr= next_curr->next;
        };
        delete curr;
    }
}

template <typename T>
Queue<T>::Queue() {
    ForwardList<T> *listik= new ForwardList <T> {nullptr,nullptr};
    list=listik;
}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> list_) {
    ForwardList<T> *listik= new ForwardList<T> {nullptr,nullptr};
    list=listik;
    for (auto x:list_) {
        list->fill(list,x);
    }
}

template <typename T>
Queue<T>::Queue(const Queue<T>& q) {
    this->list=q.list;
}

template <typename T>
auto Queue<T>:: swap(Queue<T>& q) -> void {
    ForwardList<T> *a = q.list;
    q.list= this->list;
    this->list =a;
}

template <typename T>
auto Queue<T>::operator=(const Queue<T>& q) ->void {
    this->list= q.list;
    return;
}

template <typename T>
auto Queue<T>::empty() -> bool {
    if (this->list->head==nullptr) {
        return true;
    }
    else return false;
}

template <typename T>
auto Queue<T>::size() -> int {
    return list->count_elements (list);
}

template <typename T>
auto Queue<T>::push(T x) -> void {
    list->fill (list, x);
}

template <typename T>
auto Queue<T>::pop() -> void {
    list-> delete_element(list);
}

template <typename T>
auto Queue<T>::front() -> T& {
    if (list->head==nullptr) {
        Node<T> * curr= new Node<T> {0,nullptr};
        list->head= curr;
        list->last=curr;
    }
    return *&(list->head->znach);
}

template <typename T>
auto Queue<T>::back() -> T& {
    if (list->last==nullptr) {
        Node<T> * curr= new Node<T> {0,nullptr};
        list->last = curr;
        list->head = curr;
    }
    return *&(list->last->znach);
}

template <typename T>
bool Queue<T>::operator==(const Queue& q) {
    Node<T> * curr1= this->list->head;
    Node<T> *curr2= (q.list)->head;
    while ((curr1->next!=nullptr) || (curr2->next!=nullptr)) {
        if (curr1->znach != curr2->znach) return false;
        curr1=curr1->next;
        curr2=curr2->next;
    }
    if ((curr1->next==nullptr) && (curr2->next==nullptr))
        return true;
    return false;
}

template <typename T>
std::ostream& operator<<(std::ostream& File, Queue<T>& q) {
    Node<T> *curr= q.list->head;
    if (curr==nullptr) {
        File<<"empty list";
        return File;
    }
    while (1) {
        if (curr->next!=nullptr) File<< curr->znach << " ";
        else {
            File<< curr->znach;
            break;
        }
        curr=curr->next;
    }
    return File;
}

template <typename T>
std::istream& operator>>(std::istream& File, Queue<T>& q) {
    T integer1;
    File>>integer1;
    while (File) {
        q.list->fill(q.list, integer1);
        File>>integer1;
    }
    return File;
}

template <typename T>
Queue<T>::~Queue() {
    list->deleting (list);
    list->head=nullptr;
    list->last=nullptr;
}
