#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

/*
class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};
*/
        int height(node * root){
          if(!root)
          return 0;
          int left=height(root->left);
          int right=height(root->right);
          return (left>right) ? (left+1) :(right+1) ;
        }
        void level(node *root,int h){
          if(!root)
            return ;
          if(h==1)
            cout<<root->data<<" ";
          level(root->left,h-1);
          level(root->right,h-1);
        }
        void levelOrder(Node * root) {
          int n=height(root);
          for(int i=1;i<=n;i++)
            level(root,i);
          }

}; //End of Solution

int main() {

    Solution myTree;
    Node* root = NULL;

    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }

	myTree.levelOrder(root);
    return 0;
}
