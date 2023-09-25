//Implementation of a singly linked list in C++
//James Kirk

#include <iostream>

//First create a struct called Node. Define a value and a pointer to the next node
struct Node {
    int value;
    Node* next;
};

//create a function that makes a new linked list with 1 node
Node* Initialize(int value) {
    //define a head and set it to a new node struct
    Node* head = new Node();
    //set the heads value to the value provided upon call
    head->value = value;
    //set the next to NULL so theres only 1 Node
    head->next = NULL;
    //return the head Node we just created
    return head;
};

//create a function to make more nodes and insert them at any index
Node* InsertAt(Node* head, int index, int value) {
    //When inserting to front
    if (index == 0) {
        //create the node
        Node* nodeToInsert = new Node();
        //set the value of the node
        nodeToInsert->value = value;
        //link to the previous head
        nodeToInsert->next = head;
        //return the new head
        return nodeToInsert;
    }
    //start at the head and traverse the list
    Node* currentNode = head;
    for (int i=0; i < index-1; ++i) {
        //check if theres a list and that it has enough Nodes
        if (currentNode = NULL) {
            std::cout << "The input index is not valid" << std::endl;
            //always return to the head of the list
            return head;
        }
        //goes to next Node until index-1 is reached
        Node* currentNode = currentNode->next;
    }
    //checks if the index-1 node is Null
    if (currentNode == NULL){
        std::cout << "The input index is not valid" << std::endl;
        return head;
    }
    //create a node variable with the old index node
    //Note this already has a value, we are storing its memory address
    Node* nextNode = currentNode->next;
    //create the Node that is to be inserted
    Node* nodeToInsert = new Node();
    //set Nodes value as provided by user
    nodeToInsert->value = value;
    //links the index-1 node to the new node
    currentNode->next = nodeToInsert;
    //links the new node to the next node (index node prior)
    nodeToInsert->next = nextNode;
    //always return to the head
    return head;
}
//function to create a node at start
Node* InsertAtStart(Node* head, int value) {
    return InsertAt(head, 0, value);
}

//function to delete Node anywhere in the list
Node* DeleteAt(Node* head, int index) {
    //when deleting first node
    if (index == 0) {
        //handles empty list
        if (head == NULL) {
            std::cout << "The input index is not valid" << std::endl;
            return head;
        }
        //set the current node to the head
        Node* currentNode = head;
        //set the head to the next node. If Null the list will be empty
        head = head->next;
        //delete the previous head
        delete currentNode;
        //return to the new head
        return head;
    }
    //start at the head
    Node* currentNode = head;
    //traverse until reaching index-1 node
    for (int i=0; i < index-1; ++i) {
        //if any nodes are NULL then return not valid
        if (currentNode == NULL) {
            std::cout << "The input index is not valid" << std::endl;
            //always return to the head of the list
            return head;
        }
    //traversing by setting current node to the next
    currentNode = currentNode->next;
    }
    //check if index-1 is NULL
    if (currentNode == NULL){
        std::cout << "The input index is not valid" << std::endl;
        return head;
    }
    //sets index-1 -> next to index node
    Node* indexNode = currentNode->next;
    //sets index -> next to next node
    Node* nextNode = indexNode->next;
    //links the index-1 to the next node
    currentNode->next = nextNode;
    //deletes the index node
    delete indexNode;
    //goes back to the start of the list
    return head;
}

Node* DeleteAtStart(Node* head) {
    return DeleteAt(head, 0);
}

int GetAt(Node* head, int index) {
    Node* currentNode = head;
    for (int i=0; i < index; ++i) {
        if (currentNode == NULL) {
            std::cout << "The input index is not valid" << std::endl;
            return -1;
        }
    }
    return currentNode-> value;
}

int SetAt(Node* head, int index, int value) {
    Node* currentNode = head;
    for (int i=0; i < index; ++i) {
        if (currentNode == NULL) {
            std::cout << "The input index is not valid" << std::endl;
            return -1;
        }
        currentNode = currentNode->next;
    }
    if (currentNode == NULL) {
            std::cout << "The input index is not valid" << std::endl;
            return -1;
        }
    currentNode->value = value;
    return 0;
}


void PrintAll(Node* head) {
    Node* currentNode = head;
    int listSize = 0;
    std::cout << "List Elements: " << std::endl;
    while (currentNode != NULL) {
        std::cout << currentNode->value << std::endl;
        currentNode = currentNode->next;
        ++listSize;
    }
}