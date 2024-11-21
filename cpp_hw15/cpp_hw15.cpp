#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    void dequeue() {
        if (isEmpty()) {
            throw runtime_error("Очередь пуста");
        }
        Node<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    T front() const {
        if (isEmpty()) {
            throw runtime_error("Очередь пуста");
        }
        return head->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void add(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void print() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    DoublyLinkedList clone() const {
        DoublyLinkedList newList;
        Node<T>* current = head;
        while (current) {
            newList.add(current->data);
            current = current->next;
        }
        return newList;
    }

    DoublyLinkedList operator+(const DoublyLinkedList& other) const {
        DoublyLinkedList result = this->clone();
        Node<T>* current = other.head;
        while (current) {
            result.add(current->data);
            current = current->next;
        }
        return result;
    }

    DoublyLinkedList operator*(const DoublyLinkedList& other) const {
        DoublyLinkedList result;
        Node<T>* currentA = head;
        while (currentA) {
            Node<T>* currentB = other.head;
            while (currentB) {
                if (currentA->data == currentB->data) {
                    result.add(currentA->data);
                    break;
                }
                currentB = currentB->next;
            }
            currentA = currentA->next;
        }
        return result;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

template <typename T>
class Array {
private:
    vector<T> elements;
    size_t grow;

public:
    Array() : grow(1) {}

    size_t GetSize() const {
        return elements.size();
    }

    void SetSize(size_t size, size_t grow = 1) {
        this->grow = grow;
        if (size > elements.size()) {
            elements.resize(size);
        }
        else {
            elements.erase(elements.begin() + size, elements.end());
        }
    }

    int GetUpperBound() const {
        return elements.empty() ? -1 : elements.size() - 1;
    }

    bool IsEmpty() const {
        return elements.empty();
    }

    void FreeExtra() {
        elements.shrink_to_fit();
    }

    void RemoveAll() {
        elements.clear();
    }

    T GetAt(size_t index) const {
        if (index >= elements.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        return elements[index];
    }

    void SetAt(size_t index, T value) {
        if (index >= elements.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        elements[index] = value;
    }

    T& operator[](size_t index) {
        return elements[index];
    }

    const T& operator[](size_t index) const {
        return elements[index];
    }

    void Add(T value) {
        if (elements.size() == elements.capacity()) {
            elements.reserve(elements.size() + grow);
        }
        elements.push_back(value);
    }

    Array operator+(const Array& other) const {
        Array result;
        result.elements = elements;
        result.elements.insert(result.elements.end(), other.elements.begin(), other.elements.end());
        return result;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }

    const T* GetData() const {
        return elements.data();
    }

    void InsertAt(size_t index, T value) {
        if (index > elements.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        elements.insert(elements.begin() + index, value);
    }

    void RemoveAt(size_t index) {
        if (index >= elements.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        elements.erase(elements.begin() + index);
    }
};

int main() {
    cout << "Очередь:" << endl;
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    cout << "Первый элемент: " << queue.front() << endl;
    queue.dequeue();
    cout << "После удаления первый элемент: " << queue.front() << endl;

    cout << "\nДвусвязный список:" << endl;
    DoublyLinkedList<int> list1, list2;
    list1.add(1);
    list1.add(2);
    list1.add(3);
    list2.add(3);
    list2.add(4);
    list2.add(5);
    cout << "Список 1: ";
    list1.print();
    cout << "Список 2: ";
    list2.print();
    cout << "Объединение: ";
    (list1 + list2).print();
    cout << "Пересечение: ";
    (list1 * list2).print();

    cout << "\nМассив:" << endl;
    Array<int> array;
    array.SetSize(5);
    for (int i = 0; i < 5; ++i) {
        array[i] = i + 1;
    }
    array.Add(6);
    cout << "Массив: ";
    for (int i = 0; i <= array.GetUpperBound(); ++i) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}
