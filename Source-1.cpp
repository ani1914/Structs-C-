#include <iostream>
#include <initializer_list>

template <class T>
class L
{
	struct Node
	{
		Node(const T& val = T(), Node *next = nullptr);
		T data;
		Node* next;
	};
	
public:
	L();
    L(const std::initializer_list<T>& values);
	L(const L& other);
	L& operator=(const L& other);
	~L();
	const T& at(size_t i) const;
	class iterator;
	iterator begin();
	iterator end() const;
	bool isEmpty() const;
	size_t size() const;
	void insertFront(const T& e);
	void insertBack(const T& e);
	void insert(size_t p, const T& e);
	void eraseFront();
	void eraseBack();
	T erase(size_t p);
	void set(size_t i, const T& e);

private:
	Node* head, * tail;
	size_t sz;
	void copy(const L& other);
	void freeHeap();
};
template<class T>
class L<T>::iterator
{
    friend iterator L<T>::begin();
    friend iterator L<T>::end() const;

    L<T>::Node* ptr;
    iterator(L<T>::Node* ptr)
        : ptr(ptr) {}

public:
    bool valid() const { return ptr; }
    operator bool() const { return ptr; }

    T& operator*() { return ptr->data; }
    T* operator->() { return &ptr->data; }
    const T& operator*() const { return ptr->data; }
    const T* operator->() const { return &ptr->data; }
};

template<class T>
inline L<T>::Node::Node(const T& val, Node* next)
    :data(val), next(next)
{}

template<class T>
inline void L<T>::copy(const L<T>& other)
{
    Node dummy;
    Node* iter = &dummy;
    Node* curr = other.head;
    while (curr) {
        iter->next = new Node(curr->data);
        iter = iter->next;
        curr = curr->next;
    }
    head = dummy.next;
    tail = head ? iter : nullptr;
    sz = other.sz;
}

template<class T>
inline void L<T>::freeHeap()
{
    Node* iter = head;
    Node* detach = head;

    for (size_t i = 0; i < sz; ++i) {
        detach = iter;
        iter = iter->next;
        delete detach;
    }

    tail = head = nullptr;
    sz = 0;
}

template<class T>
inline L<T>::L()
    :head(nullptr), tail(nullptr), sz(0) {}

template<class T>
inline L<T>::L(const std::initializer_list<T>& values)
    : head(nullptr), tail(nullptr), sz(0)
{
    for (const T& val : values) {
        push_end(val);
    }
}

template<class T>
inline L<T>::L(const L& other)
    :L()
{
    copy(other);
}

template<class T>
inline L<T>& L<T>::operator=(const L<T>& other)
{
    if (this != &other) {
        freeHeap();
        copy(other);
    }

    return *this;
}

template<class T>
inline L<T>::~L()
{
    freeHeap();
}

template<class T>
inline const T& L<T>::at(size_t i) const
{
    if (isEmpty() || i >= sz) {
        throw std::invalid_argument("Index out of bounds\n");
    }

    if (i == sz - 1) {
        return tail->data;
    }

    const Node* iter = head;
    for (size_t j = 0; j < i; ++j, iter = iter->next)
        ;
    return iter->data;
}

template<class T>
inline size_t L<T>::size() const
{
    return sz;
}

template<class T>
inline typename L<T>::iterator L<T>::begin()
{
    return iterator(head);
}

template<class T>
inline typename L<T>::iterator L<T>::end() const
{
    return iterator(nullptr);
}

template<class T>
inline void L<T>::insert(size_t p, const T& e)
{
    if (p > sz) {
        throw std::invalid_argument("Index out of bounds\n");
    }

    if (p == 0) {
        head = new Node(e, head);
        if (!sz) tail = head;
    }
    else if (p == sz) {
        tail->next = new Node(e);
        tail = tail->next;
    }
    else {
        Node* iter = head;
        for (size_t i = 0; i < p - 1; ++i, iter = iter->next)
            ;

        iter->next = new Node(e, iter->next);
    }

    ++sz;
}

template<class T>
inline void L<T>::insertFront(const T& e)
{
    insert(0, e);
}

template<class T>
inline void L<T>::insertBack(const T& e)
{
    insert(sz, e);
}

template<class T>
inline T L<T>::erase(size_t p)
{
    if (isEmpty() || p > sz - 1) {
        throw std::invalid_argument("Index out of bounds\n");
    }

    Node* detach = head;

    if (p == 0) {
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    }
    else {
        Node* iter = head;
        for (size_t i = 0; i < p - 1; ++i, iter = iter->next)
            ;

        detach = iter->next;
        iter->next = detach->next;

        if (detach == tail) {
            tail = iter;
        }
    }
    --sz;
    T store = detach->data;
    delete detach;
    return store;
}

template<class T>
inline void L<T>::eraseFront()
{
    erase(0);
}

template<class T>
inline void L<T>::eraseBack()
{
    erase(sz - 1);
}

template<class T>
inline bool L<T>::isEmpty() const
{
    return sz == 0;
}

template<class T>
inline void L<T>::set(size_t i, const T& e)
{
    erase(i);
    insert(i, e);
}

int main()
{

	return 0;
}