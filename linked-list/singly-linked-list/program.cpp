#include <iostream>

template <typename T>
struct Node {
    T value;
    Node<T>* nextNode;

    Node(T value) : value(value), nextNode(nullptr) { }
    ~Node() { delete nextNode; }
};

template <typename T>
class SinglyLinkedList {
    private:
        Node<T>* rootNode;

    public:
        // Instantiation
        SinglyLinkedList(): rootNode(nullptr) { }
        ~SinglyLinkedList() { delete rootNode; }
        // Insertion
        void push_front(T value) {
            Node<T>* newNode = new Node<T>(value);
            newNode->nextNode = rootNode;
            rootNode = newNode;
        };
        void push_back(T value) {  
            Node<T>* newNode = new Node<T>(value);
            if (rootNode == nullptr) {
                rootNode = newNode;
                return;
            }
            Node<T>* currentNode = rootNode;
            while (currentNode->nextNode != nullptr) {
                currentNode = currentNode->nextNode;
            }
            currentNode->nextNode = newNode;
        };
        void insert_after(int index, T value) {
            int currentIndex = 0;
            Node<T>* currentNode = rootNode;
            while (currentNode != nullptr) {
                if (currentIndex == index) {
                    Node<T>* newNode = new Node<T>(value);
                    newNode->nextNode = currentNode->nextNode;
                    currentNode->nextNode = newNode;
                    return;
                } else {
                    currentNode = currentNode->nextNode;
                    currentIndex++;
                }
            }
        };
        // Deletion
        T pop_front() {
            if (rootNode == nullptr) {
                throw std::out_of_range("List is empty");
            }
            Node<T>* currentNode = rootNode;
            T value = currentNode->value;
            rootNode = currentNode->nextNode;
            currentNode->nextNode = nullptr; // Disconect the value
            delete currentNode; // Free memory
            return value;
        };
        T pop_back() {
            if (rootNode == nullptr) {
                throw std::out_of_range("List is empty");
            }
            Node<T>* currentNode = rootNode;
            Node<T>* previousNode = nullptr;

            while (currentNode->nextNode != nullptr) {
                previousNode = currentNode;
                currentNode = currentNode->nextNode;
            }

            T value = currentNode->value;

            if (previousNode == nullptr) { // Only one element in the list
                delete previousNode;
                rootNode = nullptr;
            } else {
                previousNode->nextNode = nullptr;
                delete currentNode;   
            }
            return value;
        };
        void remove(T value) {
            if (rootNode == nullptr) {
                throw std::out_of_range("List is empty");
            }

            Node<T>* currentNode = rootNode;
            Node<T>* previousNode = nullptr;

            while(currentNode->value != value) {
                previousNode = currentNode;
                currentNode = currentNode->nextNode;
            }

            if (previousNode == nullptr) { // Only one element in the list
                delete currentNode;
                rootNode = nullptr;
            } else {
                previousNode->nextNode = currentNode->nextNode;
                currentNode->nextNode = nullptr;
                delete currentNode;
            }
        };
        void remove_at(int index) {
            if (rootNode == nullptr) {
                throw std::out_of_range("List is empty");
            }

            int currentIndex = 0;
            Node<T>* currentNode = rootNode;
            Node<T>* previousNode = nullptr;

            while (currentIndex < index && currentNode->nextNode != nullptr) {
                previousNode = currentNode;
                currentNode = currentNode->nextNode;
                currentIndex++;
            }

            if (currentIndex != index) {
                throw std::out_of_range("Index is out of range");
            }

            if (previousNode == nullptr) { // Only one element in the list
                delete currentNode;
                rootNode = nullptr;
            } else {
                previousNode->nextNode = currentNode->nextNode;
                currentNode->nextNode = nullptr;
                delete currentNode;
            }
        };
        // Traversal and Access
        T get_front() {
            if (rootNode == nullptr) {
                throw std::out_of_range("List is empty");
            }
            return rootNode->value;
        };
         T get_back() {
            if (rootNode == nullptr) {
                throw std::out_of_range("List is empty");
            }
            Node<T>* currentNode = rootNode;

            while (currentNode->nextNode != nullptr) {
                currentNode = currentNode->nextNode;
            }

            return currentNode->value;
        };
        T get_at(int index) {
            if (index < 0) {
                throw std::out_of_range("Invalid index");
            }

            if (rootNode == nullptr) {
                throw std::out_of_range("List is empty");
            }

            int currentIndex = 0;
            Node<T>* currentNode = rootNode;

            while (currentIndex < index && currentNode->nextNode != nullptr) {
                currentNode = currentNode->nextNode;
                currentIndex++;
            }

            if (currentIndex != index) {
                throw std::out_of_range("Index is out of range");
            }

            return currentNode->value;
        };

        int size() {
            int size = 0;
            Node<T>* currentNode = rootNode;

            while (currentNode != nullptr) {
                currentNode = currentNode->nextNode;
                size++;
            }
            
            return size;
        };
        bool isEmpty() {
            return rootNode == nullptr;
        };
        // Print
        void print() {
            Node<T>* currentNode = rootNode;
            std::cout << "Linked List: ";
            while (currentNode != nullptr) {
                std::cout << currentNode->value << " ";
                currentNode = currentNode->nextNode;
            }
            std::cout << std::endl;
        };
};

int main() {
    // Create a SinglyLinkedList object
    SinglyLinkedList<int> myList;

    // Test push_front
    std::cout << "Testing push_front..." << std::endl;
    myList.push_front(10);
    myList.push_front(20);
    myList.push_front(30);
    // Print the list to check the order
    myList.print(); 

    // Test push_back
    std::cout << "Testing push_back..." << std::endl;
    myList.push_back(5);
    myList.push_back(15);
    myList.push_back(25);
    // Print the list to check the order
    myList.print();

    // Test insert_after
    std::cout << "Testing insert_after..." << std::endl;
    myList.insert_after(2, 20); // Insert value 20 after position 2
    myList.print();

    // Test pop_front
    std::cout << "Testing pop_front..." << std::endl;
    int frontValue = myList.pop_front();
    std::cout << "Popped front value: " << frontValue << std::endl;
    myList.print();

    // Test pop_back
    std::cout << "Testing pop_back..." << std::endl;
    int backValue = myList.pop_back();
    std::cout << "Popped back value: " << backValue << std::endl;
    myList.print();

    // Test remove value
    std::cout << "Testing remove value..." << std::endl;
    myList.remove(15);
    myList.print();

    // Test remove at index
    std::cout << "Testing remove at index..." << std::endl;
    myList.remove_at(2);
    myList.print();

    // Test get_front, get_back, get_at
    std::cout << "Testing get_front, get_back, get_at..." << std::endl;
    int front = myList.get_front();
    int back = myList.get_back();
    int atIndex = myList.get_at(1); // Change the index based on list size
    std::cout << "Front value: " << front << std::endl;
    std::cout << "Back value: " << back << std::endl;
    std::cout << "Value at index 2: " << atIndex << std::endl;

    // Test size and isEmpty
    std::cout << "Testing size and isEmpty..." << std::endl;
    std::cout << "List size: " << myList.size() << std::endl;
    std::cout << "Is the list empty? " << (myList.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}