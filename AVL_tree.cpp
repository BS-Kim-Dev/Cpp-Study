#include <iostream>

typedef struct Node {
    int data;
    int height;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

int getMax(int a, int b){
    if (a > b){return a;}
    else {return b;}
}

int getHeight(Node *node){
    if (node == NULL){return 0;}
    return node->height;
}

void setHeight(Node *node){
    node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

int getDifference(Node *node){
    if (node == NULL){return 0;}
    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

Node* insertNode (Node *root, int data){
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root->leftChild = root->rightChild = NULL;
        root->data = data;
        return root;
    }
    else {
        if (root->data > data) {
            root->leftChild = insertNode(root->leftChild, data);
        }
        else {
            root->rightChild = insertNode(root->rightChild, data);
        }
    }
    return root;
}

Node* searchNode(Node *root, int data){
    if (root == NULL) {return NULL;}
    if (root->data == data) {return root;}
    else if (root->data > data) {return searchNode(root->leftChild, data);}
    else {return searchNode(root->rightChild, data);}
}

void preorder(Node *root){
    if (root == NULL) {return;}
    std::cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void inorder(Node *root){
    if (root == NULL) {return;}
    inorder(root->leftChild);
    std::cout << root->data << " ";
    inorder(root->rightChild);
}

Node* findMinNode(Node *root){
    Node *node = root;
    while (node->leftChild != NULL){
        node = node->leftChild;
    }
    return node;
}

Node* deleteNode(Node *root, int data){
    Node* node = NULL;
    if (root == NULL){return NULL;}
    if (root->data > data){root->leftChild = deleteNode(root->leftChild, data);}
    else if (root->data < data){root->rightChild = deleteNode(root->rightChild, data);}
    else{
        if ((root->leftChild != NULL) && (root->rightChild != NULL)){
            node = findMinNode(root->rightChild);
            root->data = node ->data;
            root->rightChild = deleteNode(root->rightChild, node->data);
        }
        else {
            node = (root->leftChild != NULL) ? root->leftChild : root->rightChild;
            free(root);
            return node;
        }
    }
    return root;
}

Node* rotateLL(Node* node){
    Node *leftChild = node->leftChild;
    node->leftChild = leftChild->rightChild;
    leftChild->rightChild = node;
    setHeight(node);
    return leftChild;
}

Node* rotateRR(Node* node){
    Node *rightChild = node->rightChild;
    node->rightChild = rightChild->leftChild;
    rightChild->leftChild = node;
    setHeight(node);
    return rightChild;
}

Node* rotateLR(Node* node){
    Node *leftChild = node->leftChild;
    node->leftChild = rotateRR(leftChild);
    setHeight(node->leftChild);
    return rotateLL(node);
}

Node* rotateRL(Node* node){
    Node *rightChild = node->rightChild;
    node->rightChild = rotateLL(rightChild);
    setHeight(node->rightChild);
    return rotateRR(node);
}

int main(void){
    Node *root = NULL;
    root = insertNode(root, 30);
    root = insertNode(root, 17);
    root = insertNode(root, 48);
    root = insertNode(root,  5);
    root = insertNode(root, 23);
    root = insertNode(root, 37);
    root = insertNode(root, 50);
    preorder(root);
    std::cout << std::endl;
    inorder(root);
    std::cout << std::endl;
    root = deleteNode(root, 48);
    inorder(root);


}