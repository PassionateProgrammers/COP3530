// copied from prof code

//DFS is the same as used in BinaryTree.cpp as it is the standard way of
//traversing through a BST to find a node

//BFS is used for finding shortest path and 
//for visiting nodes at specific levels

#include <iostream>
#include <queue>
struct BinaryTreeNode
{
    char key;
    int value;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode(char key, int value)
    {
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
    }
};
// Prints out the keys in the tree in pre-order.
void PreOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    std::cout << node->key << " ";
    PreOrderTraversal(node->left);
    PreOrderTraversal(node->right);
}
// Prints out the keys in the tree in order.
void InOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    InOrderTraversal(node->left);
    std::cout << node->key << " ";
    InOrderTraversal(node->right);
}
// Prints out the keys in the tree in post-order.
void PostOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    PostOrderTraversal(node->left);
    PostOrderTraversal(node->right);
    std::cout << node->key << " ";
}

// Searches and returns the node with the target key using DFS. We assume it is
// unique in the tree.
BinaryTreeNode *DFS(BinaryTreeNode *node, char target)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->key == target)
    {
        return node;
    }
    BinaryTreeNode *left_res = DFS(node->left, target);
    if (left_res != NULL)
    {
        return left_res;
    }
    return DFS(node->right, target);
}
// Searches and returns the node with the target key using BFS. We assume it is
// unique in the tree.
BinaryTreeNode *BFS(BinaryTreeNode *node, char target)
{
    if (node == NULL)
    {
        return NULL;
    }
    std::queue<BinaryTreeNode *> open_queue;
    open_queue.push(node);
    while (!open_queue.empty())
    {
        BinaryTreeNode *current_node = open_queue.front();
        if (current_node->key == target)
        {
            return current_node;
        }
        if (current_node->left != NULL)
        {
            open_queue.push(current_node->left);
        }
        if (current_node->right != NULL)
        {
            open_queue.push(current_node->right);
        }
        open_queue.pop();
    }
    return NULL;
}
// Searches and returns the node with the target key using BFS. We assume it is
// unique in the tree.
// Do the search layer by layer so that we know the depth of the target.
BinaryTreeNode *BFS_layer_by_layer(BinaryTreeNode *node, char target) {
    if (node == NULL) {
        return NULL;
    }

    std::queue<BinaryTreeNode *> current_layer;
    current_layer.push(node);

    int layer = 0; // Counter to track the layer/height

    while (!current_layer.empty()) {
        int nodes_in_current_layer = current_layer.size();
        for (int i = 0; i < nodes_in_current_layer; ++i) {
            BinaryTreeNode *current_node = current_layer.front();
            current_layer.pop();

            if (current_node->key == target) {
                return current_node;
            }

            if (current_node->left != NULL) {
                current_layer.push(current_node->left);
            }
            if (current_node->right != NULL) {
                current_layer.push(current_node->right);
            }
        }

        // Increment the layer/height counter after processing a layer
        layer++;
    }

    return NULL;
}

int main()
{
    // Create a binary tree as follows.
    /*
    A
    / \
    B D
    / \ \
    E F J
    / /
    K M
    */
    BinaryTreeNode root('A', 1); // BinaryTreeNode* root = new BinaryTreeNode('A');
    BinaryTreeNode node_b('B', 2);
    BinaryTreeNode node_d('D', 3);
    BinaryTreeNode node_e('E', 4);
    BinaryTreeNode node_f('F', 5);
    BinaryTreeNode node_j('J', 6);
    BinaryTreeNode node_k('K', 7);
    BinaryTreeNode node_m('M', 8);
    root.left = &node_b;
    root.right = &node_d;
    node_b.left = &node_e;
    node_b.right = &node_f;
    node_d.right = &node_j;
    node_e.left = &node_k;
    node_f.left = &node_m;
    // print out the keys of nodes in in-order traversal
    std::cout << "Pre-order traversal of the tree: ";
    InOrderTraversal(&root);
    std::cout << std::endl;
    // Search for the key 'F' using DFS;
    BinaryTreeNode *dfs_res = DFS(&root, 'F');
    std::cout << "DFS result: ";
    if (dfs_res == NULL)
    {
        std::cout << "node not found." << std::endl;
    }
    else
    {
        std::cout << "The value of the node is: " << dfs_res->value << std::endl;
    }
    // Search for the key 'F' using BFS;
    BinaryTreeNode *bfs_res = BFS(&root, 'F');
    std::cout << "BFS result: ";
    if (bfs_res == NULL)
    {
        std::cout << "node not found." << std::endl;
    }
    else
    {
        std::cout << "The value of the node is: " << bfs_res->value << std::endl;
    }
    return 1;
}
