#include <iostream>
#include <iomanip> 

template <class T>
class Node {
public:
    T* data;            // Указатель на данные, хранящиеся в узле
    Node<T>* left;      // Указатель на левую ветвь
    Node<T>* right;     // Указатель на правую ветвь

    // Конструктор
    Node(T* value) : data(value), left(nullptr), right(nullptr) {}

    // Деструктор
    ~Node() {
        delete data; 
    }

    // Метод для добавления левого дочернего узла
    void setLeft(Node<T>* leftNode) {
        left = leftNode;
    }

    // Метод для добавления правого дочернего узла
    void setRight(Node<T>* rightNode) {
        right = rightNode;
    }

    // Метод для обхода дерева в порядке (in-order)
    void inOrderTraversal() {
        if (left) left->inOrderTraversal(); // Обход левой ветви
        std::cout << *data << " ";          // Посещение узла
        if (right) right->inOrderTraversal(); // Обход правой ветви
    }

    // Метод для отображения дерева сверху-вниз
    void display(int space = 0) {
        space += 10;

        if (right) {
            right->display(space);
        }

        std::cout << std::endl;
        std::cout << std::setw(space) << *data << std::endl;

        if (left) {
            left->display(space);
        }
    }
};

int main() {
    int* rootData = new int(20);
    Node<int> root(rootData);

    int* leftData = new int(10);
    Node<int> leftChild(leftData);
    root.setLeft(&leftChild);

    int* rightData = new int(30);
    Node<int> rightChild(rightData);
    root.setRight(&rightChild);

    int* leftLeftData = new int(5);
    Node<int> leftLeftChild(leftLeftData);
    leftChild.setLeft(&leftLeftChild);

    int* leftRightData = new int(15);
    Node<int> leftRightChild(leftRightData);
    leftChild.setRight(&leftRightChild);

    int* rightLeftData = new int(25);
    Node<int> rightLeftChild(rightLeftData);
    rightChild.setLeft(&rightLeftChild);

    int* rightRightData = new int(35);
    Node<int> rightRightChild(rightRightData);
    rightChild.setRight(&rightRightChild);

    // Добавляем еще больше узлов
    int* leftLeftLeftData = new int(3);
    Node<int> leftLeftLeftChild(leftLeftLeftData);
    leftLeftChild.setLeft(&leftLeftLeftChild);

    int* leftLeftRightData = new int(7);
    Node<int> leftLeftRightChild(leftLeftRightData);
    leftLeftChild.setRight(&leftLeftRightChild);

    int* leftRightLeftData = new int(12);
    Node<int> leftRightLeftChild(leftRightLeftData);
    leftRightChild.setLeft(&leftRightLeftChild);

    int* leftRightRightData = new int(17);
    Node<int> leftRightRightChild(leftRightRightData);
    leftRightChild.setRight(&leftRightRightChild);

    int* rightLeftLeftData = new int(22);
    Node<int> rightLeftLeftChild(rightLeftLeftData);
    rightLeftChild.setLeft(&rightLeftLeftChild);

    int* rightLeftRightData = new int(27);
    Node<int> rightLeftRightChild(rightLeftRightData);
    rightLeftChild.setRight(&rightLeftRightChild);

    int* rightRightLeftData = new int(32);
    Node<int> rightRightLeftChild(rightRightLeftData);
    rightRightChild.setLeft(&rightRightLeftChild);

    int* rightRightRightData = new int(37);
    Node<int> rightRightRightChild(rightRightRightData);
    rightRightChild.setRight(&rightRightRightChild);

    std::cout << "In-order traversal: ";
    root.inOrderTraversal(); // 3 5 7 10 12 15 17 20 22 25 27 30 32 35 37
    std::cout << std::endl;

    std::cout << "Tree structure:" << std::endl;
    root.display(); 

    return 0;
}
