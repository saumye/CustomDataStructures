#include <iostream>
#include <stdlib.h>
#include <vector>
#define MAX 26
using namespace std;

typedef struct TrieNode
{
    char data;
    TrieNode *links[MAX];
    int endOfString;
}TrieNode;

typedef struct Trie
{
    int count;
    TrieNode *root;
}Trie;

bool insertSuccessful = false;


void printStack(vector<char>&);
TrieNode* createNode();
TrieNode* createNode(char );
Trie* insertInTrie(Trie *, char *);
void insertUtil(TrieNode *, char *,int);
bool searchTrie(Trie *, char *);
bool searchUtil(TrieNode *, char *,int);
Trie* createTrie();
void printTrie(Trie *);
void printTrieUtil(TrieNode*,vector<char> &);



Trie* createTrie()
{
    Trie *node = (Trie *)malloc(sizeof(Trie));
    node->count = 0;
    node->root = NULL;
    TrieNode *root = createNode();
    node->root = root;
    return node;
}

TrieNode* createNode(char data)
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->data = data;
    node->endOfString = 0;
    for(int i=0;i<MAX;i++)
        node->links[i] = NULL;
    return node;
}

TrieNode* createNode()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->endOfString = 0;
    for(int i=0;i<MAX;i++)
        node->links[i] = NULL;
    return node;
}

Trie* insertInTrie(Trie *t, char word[])
{
    insertUtil(t->root,word,0);
    if(insertSuccessful)
        t->count++;
    insertSuccessful = false;
    return t;
}

void insertUtil(TrieNode *root, char word[], int i)
{
    if(word[i] == '\0')
    {   
        root->endOfString = 1;
        return;
    }

    if(!root->links[((int)(word[i]))-97])
        root->links[((int)(word[i]))-97] = createNode(word[i]);
    root = root->links[((int)(word[i]))-97];
    i++;
    insertUtil(root,word,i);
    return;
}

bool searchTrie(Trie *t, char *word)
{
    if(t->root == NULL)
    return false;
    return searchUtil(t->root,word,0);
}

bool searchUtil(TrieNode *root, char word[], int i)
{
    if(!root)
        return false;
    if(word[i] == '\0')
        return true;

    if(root->links[((int)(word[i]))-97])
        root = root->links[((int)(word[i]))-97];
    else
        return false;
    i++;
    return searchUtil(root,word,i);

}
void printTrieUtil(TrieNode *node,vector<char> &v)
{
    if(node->endOfString)
    {
        printStack(v);
        cout<<endl;
    }
    for( int i = 0; i < MAX; i++)
    {
        if(node->links[i])
        {
            v.push_back(node->links[i]->data);
            printTrieUtil(node->links[i],v);
        }
    }
    v.pop_back();
}

void printStack(vector<char>& v)
{
    for(vector<char>::iterator i = v.begin(); i!= v.end(); i++ )
        cout<<*i;
}
void printTrie(Trie *t)
{
    vector <char> v;
    if(t->root)
        printTrieUtil(t->root,v);
}

