#include<iostream>
#include<omp.h>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int d) : data(d), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* insert(Node* root, int data) {
        if (!root) return new Node(data);
        if (data < root->data) root->left = insert(root->left, data);
        else root->right = insert(root->right, data);
        return root;
    }

    void parallelDFS(Node* root) {
        if (!root) return;

        cout << root->data << "\t";

        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                if (root->left) {
                    #pragma omp task
                    parallelDFS(root->left);
                    #pragma omp taskwait
                }

                if (root->right) {
                    #pragma omp task
                    parallelDFS(root->right);
                    #pragma omp taskwait
                }
            }
        }
    }
};

int main() {
    Node* root = NULL;
    int data;
    char ans;
    BST bst;

    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = bst.insert(root, data);
        cout << "Insert more (y/n)? ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "Parallel DFS Traversal: ";
    bst.parallelDFS(root);

    return 0;
}
