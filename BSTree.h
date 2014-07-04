#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>

/////////////////
#define tr(c,i) for(typeof((c).begin() i = (c).begin(); i != (c).end(); i++)        //Traverse a container
#define present(c,x) ((c).find(x) != (c).end())
////////////////

using namespace std;

/** SINGLE NODE WITH DATA  **/

template<typename T>
struct TreeNode
{
    T data;
    TreeNode *left;
    TreeNode *right;
};

/** TREE DATA STRUCTURE **/
template<typename T>
struct BSTree
{
    TreeNode<T> *root;
    int count;
};


/**
    BSTREE FUNCTIONS

        -   createTreeNode(T data)

        -   insertInBST(BSTree<T>*)

        -   inorderBSTTraversal(BSTree<T>*)

        -   levelorderBSTTraversal(BSTree<T>*)

        -   preorderBSTTraversal(BSTree<T>*)

        -   postorderBSTTraversal(BSTree<T>*)

        -   mergeBSTrees(BSTree <T> *, BSTree <T> *)
**/



///////////////////////FUNCTIONS//////////////////////////


template<typename T>
TreeNode<T>* createTreeNode(T data)
{
    TreeNode<T> *node = (TreeNode<T>*)malloc(sizeof(TreeNode<T>));
    if(!node)
    {
        cout<<"Error in creation of node"<<endl;
        return NULL;
    }
    node->left = node->right = NULL;
    node->data = data;
    return node;
}

template<typename T>
BSTree<T>* insertInBST(BSTree<T> *tree, T data )
{
    if(!tree->root)
        tree->root = createTreeNode(data);
    else
        tree->root = insertUtil(tree->root,data);
    return tree;
}

template<typename T>
TreeNode <T>* insertUtil(TreeNode<T> *root, T data)
{
    if(root == NULL)
        root = createTreeNode(data);
    else
    {
        if(root->data > data)
            root->left = insertUtil(root->left,data);
        else if(root->data < data)
            root->right = insertUtil(root->right, data);
    }
    return root;

}

template <typename T>
void inorderBSTTraversal(BSTree<T> *tree)
{
    TreeNode<T> *root = tree->root;
    inorderBSTUtil(root);
    return;
}

template <typename T>
void inorderBSTUtil(TreeNode<T> *root)
{
    vector< TreeNode<T>* > nodes;
    while(1)
    {
        while(root)
        {
                nodes.push_back(root);
                root = root->left;
        }
        if(nodes.empty())
            return;
        root = nodes.back();
        nodes.pop_back();
        cout<<root->data<<endl;
        root = root->right;
    }
    return;
}


template <typename T>
void preorderBSTTraversal(BSTree<T> *tree)
{
    TreeNode<T> *root = tree->root;
    vector< TreeNode<T>* > nodes;
    while(1)
    {
        while(root)
        {
                cout<<root->data<<endl;
                nodes.push_back(root);
                root = root->left;
        }
        if(nodes.empty())
            return;
        root = nodes.back();
        nodes.pop_back();
        root = root->right;
    }
    return;
}

template <typename T>
void postorderBSTTraversal(BSTree<T> *tree)
{
    TreeNode<T> *root = tree->root;
    vector< TreeNode<T> * > nodes;

    do
    {
        while(root)
        {
            if(root->right)
                nodes.push_back(root->right);

            nodes.push_back(root);
            root = root->left;
        }

        root = nodes.back();
        nodes.pop_back();

        if(root->right && nodes.back() == root->right)
        {
            nodes.pop_back();
            nodes.push_back(root);
            root = root->right;
        }
        else
        {
            cout<<root->data<<endl;
            root = NULL;
        }
    }while(!nodes.empty());
}

template<typename T>
T minBST(BSTree<T> *tree)
{
    TreeNode<T> *root = tree->root;
    while(root->left != NULL)
        root = root->left;
    retun root->data;
}


template<typename T>
void levelorderBSTTraversal(BSTree<T> *tree)
{
    TreeNode<T> *root = tree->root;
    queue< TreeNode<T> * > nodes;
    nodes.push(root);
    while(!nodes.empty())
    {
        root = nodes.front();
        nodes.pop();
        cout<<root->data<<endl;
        if(root->left)
        nodes.push(root->left);
        if(root->right)
        nodes.push(root->right);
    }
}

template<typename T>
bool searchBST(BSTree<T> *tree, T element)
{
    TreeNode<T> *root = tree->root;
    while(root)
    {
        if(element == root->data)
            return true;
        if(element < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}


template<typename T>
TreeNode<T>* convertBSTToDLL(BSTree<T> *t)
{
    if(!t->root)
        return t->root;
    t->root = convertBSTToDLLUtil(t->root);
    TreeNode<T> *node = t->root;
    while(node->left != NULL)
        node = node->left;
    return node;
}

template<typename T>
TreeNode<T> * convertBSTToDLLUtil(TreeNode<T> *root)
{
    if(!root)
        return root;
    if(root->left)
    {
        TreeNode<T> *left = convertBSTToDLLUtil(root->left);            //left node , division and creation
        while(left->right!= NULL)
            left = left->right;                 //inorder successor
        left->right = root;
        root->left = left;
    }
    if(root->right)
    {
        TreeNode<T> *right = convertBSTToDLLUtil(root->right);            //left node , division and creation
        while(right->left!= NULL)
            right = right->left;                 //inorder successor
        right->left = root;
        root->right = right;
    }
    return root;
}

template<typename T>
void mergeBSTrees(BSTree<T> *t1, BSTree<T> *t2)
{
    if(!t1->root)
        inorderBSTTraversal(t2);
    if(!t2->root)
        inorderBSTTraversal(t1);

    TreeNode<T> *cur1 = t1->root;
    TreeNode<T> *cur2 = t2->root;


    vector < TreeNode<T> * > stack1;
    vector < TreeNode<T> * > stack2;

    while(cur1 || cur2)
    {

        if(cur1)
        {
            stack1.push_back(cur1);
            cur1 = cur1->left;     
        }       

        else if(cur2)
        {
            stack2.push_back(cur2);
            cur2 = cur2->left;
        }

        else
        {
            cur1 = stack1.back();
            cur2 = stack2.back();

            if(cur1->data < cur2->data)
            {
                cout<<cur1->data<<"->";
                stack1.pop_back();
                cur1 = cur1->right;
            }

            else
            {
                cout<<cur2->data<<"->";
                cur2 = stack2.back();
                stack2.pop_back();
                cur2 = cur2->right;

            }
        }

        if(stack1.empty())
            {
                while(!stack2.empty())
                {
                    cur2 = stack2.back();
                    stack2.pop_back();
                    inorderBSTUtil(cur2);
                }
                return;
            }
        if(stack2.empty())
            {
                while(!stack1.empty())
                {
                    cur2 = stack1.back();
                    stack1.pop_back();
                    inorderBSTUtil(cur1);
                }
                return;
            }
    }

}

template <typename T>
int diameterUtil(TreeNode<T> *root)
{
    if(!root)
        return 0;
    int left = heightUtil(root->left);
    int right = heightUtil(root->right);

    return max((1+left+right), max(diameterUtil(root->left),diameterUtil(root->right)));
}

template <typename T>
int diameter(BSTree<T> *t)
{
    return diameterUtil(t->root);
}

template <typename T>
int heightUtil(TreeNode<T> *root)
{
    if(root == NULL)
        return 0;

    int x = heightUtil(root->left);
    int y = heightUtil(root->right);

    return (1+(x>y?x:y));
}

template <typename T>
int height(BSTree<T> *t)
{
    return heightUtil(t->root);
}
