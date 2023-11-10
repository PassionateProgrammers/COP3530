#include <iostream>
#include <vector>

struct Node {
    //properties of a node in a binary tree
    char key;
    int value;
    int height;
    int size;
    Node* left;
    Node* right;
    Node* parent;
    //constructor to set the values and keys based on arguments. Also sets defaults
    Node(char key, int value) {
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 0;
        size = 1;
    }
};
//function to create a balanced binary tree using recursion
//LEFT AND RIGHT ARE INDICES AT THIS POINT
//We need to map the vectors to nodes with keys and values
Node* BuildTree(std::vector<std::pair<char, int> >& key_value_pairs, int left, int right) {
    //base case for recursion. Initially Left is starting index and right is ending index.
    //Left will never be bigger than the right because left is smaller
    if (left > right) return NULL;

    //for inputs of even size a simple integer division will find the middle
    int mid = (left + right) / 2;
    //adjust the input for odd ranges so the tree is more balanced
    if ((left + right) % 2 == 1) {
        mid = (left + right) / 2 + 1;
    }
    //creates a node called root with the key and value of the middle vector
    //this is where the constructor comes into play
    Node* root = new Node(key_value_pairs[mid].first, key_value_pairs[mid].second);
    //recursively call the function again for left bound to middle -1
    //this will run logarithmically cutting the left in half each time
    /*The way this will work is it will create root nodes and point left nodes
    to each middle point on the left side. It will do this until left and right are 0
    causing to return NULL and making the 0 index the furthest left node
    */
    root->left = BuildTree(key_value_pairs, left, mid - 1);
    //if there exists a left node, make this node it's parent
    //first or furthest left is a leaf so theres no left but on the second recursive callback
    //and all of the following callbacks, it points the left nodes parent to the root
    //this is how we keep track of each nodes children by conncecting them
    if (root->left != NULL) {
        root->left->parent = root;
    }
    //once the furthest left node is reached it will build right nodes
    /*NOTICE THAT THE ROOT->LEFT FUNCTION CALL COMES BEFORE THIS MEANING
    EVERY LINE OF CODE IS RUN BEFORE THIS FUNCTION EVERY TIME ITS CALLED
    MEANING LEFT SUBTREES WILL BE MADE ON THE RIGHT BRANCH*/ 
    root->right = BuildTree(key_value_pairs, mid + 1, right);
    if (root->right != NULL) {
        root->right->parent = root;
    }
    //returns the root of the tree after it is constructed this ensures
    //that after all the nodes are created the root will be returned
    return root;
}
//takes root as input and stores the size and height
void InitHeightAndSize(Node* inputNode) {
    if (inputNode == NULL) {
        return;
    }
    int left_height = 0, left_size = 0, right_height = 0, right_size = 0;
    if (inputNode->left != NULL) {
        InitHeightAndSize(inputNode->left);
        left_height = inputNode->left->height;
        left_size += inputNode->left->size;
    }
    if (inputNode->right != NULL) {
        InitHeightAndSize(inputNode->right);
        right_height = inputNode->right->height;
        right_size += inputNode->right->size;
    }
    inputNode->height = 1 + std::max(left_height, right_height);
    inputNode->size = 1 + left_size + right_size;
}

int GetSize(Node* inputNode) {
    if (inputNode == NULL) {
        return 0;
    }
    return inputNode->size;
}

int GetHeight(Node* inputNode) {
    if (inputNode == NULL) {
        return 0;
    }
    return inputNode->height;
}

void UpdateNumberOfNodeAndHeight(Node* inputNode) {
    if (inputNode == NULL) return;

    int left_h = GetHeight(inputNode->left);
    int right_h = GetHeight(inputNode->right);

    inputNode->height = 1 + std::max(left_h, right_h);

    int left_s = GetSize(inputNode->left);
    int right_s = GetSize(inputNode->right);

    inputNode->size = left_s + right_s + 1;

    UpdateNumberOfNodeAndHeight(inputNode->parent);
}
//Depth First Search function
Node* Get(Node* root, int i) {
    int n_left = GetSize(root->left);
    if (n_left == i) {
        return root;
    }
    if (n_left < i) {
        return Get(root->right, i - n_left - 1);
    }
    return Get(root->left, i);
}
//Adds node to tree as the ith node
void Add(Node* root, int i, int key, int value) {
    Node* current_ith_node = Get(root, i);
    Node* node_to_add = new Node(key, value);

    Node* current_left = current_ith_node->left;
    if (current_left == NULL) {
        current_ith_node->left = node_to_add;
        node_to_add->parent = current_ith_node;
        return;
    }
    Node* rightmost_node = current_left;
    while (rightmost_node != NULL && rightmost_node->right != NULL) {
        rightmost_node = rightmost_node->right;
    }
    rightmost_node->right = node_to_add;
    node_to_add->parent = rightmost_node;
    
    UpdateNumberOfNodeAndHeight(node_to_add->parent);
}

bool IsLeft(Node* inputNode) {
    if (inputNode->parent == NULL) {
        return true;
    }
    return inputNode->parent->left == inputNode;
}

void ConnectChildWithParent(Node* child, Node* grandparent, bool is_left) {
    if(is_left) {
        grandparent->left = child;
    }
    else{
        grandparent->right = child;
    }
    if (child == NULL) {
        return;
    }
    child->parent = grandparent;
}

Node* Delete(Node* root, int i) {
    Node* node_to_delete = Get(root, i);
    std::cout << "found" << node_to_delete->key << std::endl;
    if (node_to_delete->left == NULL && node_to_delete->right == NULL) {
        //update node_to_deletes ancestor
        Node* parent = node_to_delete->parent;
        delete node_to_delete;
        if (parent != NULL) {
            if (IsLeft(node_to_delete)) {
                parent->left = NULL;
            }
            else{
                parent->right = NULL;
            }
        }
        UpdateNumberOfNodeAndHeight(parent);
        return root;
    }
    if (node_to_delete->left == NULL) {
        Node* right_child = node_to_delete->right;
        Node* grandparent = node_to_delete->parent;
        if (grandparent == NULL) {
            return right_child;
        }
        delete node_to_delete;
        ConnectChildWithParent(right_child, grandparent, IsLeft(node_to_delete));
        UpdateNumberOfNodeAndHeight(grandparent);
        return root;
    }
    if (node_to_delete->right == NULL) {
        Node* left_child = node_to_delete->left;
        Node* grandparent = node_to_delete->parent;
        if (grandparent == NULL) {
            return left_child;
        }
        delete node_to_delete;
        ConnectChildWithParent(left_child, grandparent, IsLeft(node_to_delete));
        UpdateNumberOfNodeAndHeight(grandparent);
        return root;
    }
    Node* predecessor = node_to_delete->left;
    if (predecessor->right == NULL) {
        node_to_delete->value = predecessor->value;
        node_to_delete->key = predecessor->key;
        
        node_to_delete->left = predecessor->left;
        if (predecessor->left != NULL) {
            predecessor->left->parent = node_to_delete;
        }
        delete predecessor;
        UpdateNumberOfNodeAndHeight(node_to_delete);
        return root;
    }
    while(predecessor != NULL && predecessor->right != NULL) {
        predecessor = predecessor->right;
    }
    node_to_delete->value = predecessor->value;
    node_to_delete->key = predecessor->key;

    Node* parent_of_predecessor = predecessor->parent;
    parent_of_predecessor->right = predecessor->left;
    if (predecessor->left != NULL) {
        predecessor->left->parent = parent_of_predecessor;
    }
    delete predecessor;
    UpdateNumberOfNodeAndHeight(parent_of_predecessor);
    return root;
}

void PrintBT(const std::string &prefix, Node* parent, bool isLeft, bool isRoot) {
    if (parent == NULL) {
        return;
    }
    if (isRoot) {
        std::cout << "------";
    }
    else {
        std::cout << prefix << (isLeft ? "L-----" : "R-----");
    }
    std::cout << parent->key << ", " << "N=" << parent->size << std::endl;
    PrintBT(prefix + (isLeft ? " |  " : "    "), parent->left, true, false);
    PrintBT(prefix + (isLeft ? " |  " : "    "), parent->right, false, false);  
}

int main() {
    std::vector<std::pair<char, int> > key_value_pairs;
    key_value_pairs.push_back(std::make_pair('A', 1));
    key_value_pairs.push_back(std::make_pair('B', 2));
    key_value_pairs.push_back(std::make_pair('C', 3));
    key_value_pairs.push_back(std::make_pair('D', 4));
    key_value_pairs.push_back(std::make_pair('E', 5));
    key_value_pairs.push_back(std::make_pair('F', 6));
    key_value_pairs.push_back(std::make_pair('G', 7));

    // Building a balanced binary tree
    Node* root = BuildTree(key_value_pairs, 0, key_value_pairs.size() - 1);
    InitHeightAndSize(root);

    std::cout << "Initial Binary Tree:" << std::endl;
    PrintBT("", root, false, true);
    std::cout << "---------------------" << std::endl;

    // Adding a node at the 3rd position
    Add(root, 3, 'H', 8);

    std::cout << "Binary Tree after adding a node at position 3:" << std::endl;
    PrintBT("", root, false, true);
    std::cout << "---------------------" << std::endl;

    // Deleting the node at the 2nd position
    root = Delete(root, 2);

    std::cout << "Binary Tree after deleting a node at position 2:" << std::endl;
    PrintBT("", root, false, true);
    std::cout << "---------------------" << std::endl;

    // Perform more operations or tests here...

    return 0;
}
