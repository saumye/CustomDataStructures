#include <iostream>
#include <stdlib.h>
#include <vector>
#define MAX 26
using namespace std;

/*
Insertion: O(log n)
Deletion:  O(log n)
Query: O(log n)

n: Length of word
*/

/*
The Trie node containing array of pointers to each link for each alphabet and data i.e the letter
*/
typedef struct TrieNode
{
    char data;
    TrieNode *links[MAX];
    int endOfString;
}TrieNode;


/*
Wrapper for the actual Trie containing header node and number of words in the Trie
*/
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


/*
Initializes Trie data structure using malloc
*/
Trie* createTrie()
{
    Trie *node = (Trie *)malloc(sizeof(Trie));
    node->count = 0;
    node->root = NULL;
    TrieNode *root = createNode();
    node->root = root;
    return node;
}

/*
Initializes An individual Trie node if not present for the alphabet
*/
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

/*
Calls insertUtil function sending the trie pointer and the word to be inserted
*/
Trie* insertInTrie(Trie *t, char word[])
{
    insertUtil(t->root,word,0);
    if(insertSuccessful)
        t->count++;
    insertSuccessful = false;
    return t;
}

/*
function to insert a word, checks letter by letter
*/
void insertUtil(TrieNode *root, char word[], int i)
{
    //check if end of string reached
    if(word[i] == '\0')
    {   
        root->endOfString = 1;
        return;
    }
    //if pointer is not null, letter exists then go to the node else create the node
    if(!root->links[((int)(word[i]))-97])
        root->links[((int)(word[i]))-97] = createNode(word[i]);
    root = root->links[((int)(word[i]))-97];
    i++;
    insertUtil(root,word,i);
    return;
}

/*
Function to search if Trie contains the word by calling searchUtil
*/
bool searchTrie(Trie *t, char *word)
{
    if(t->root == NULL)
    return false;
    return searchUtil(t->root,word,0);
}

/*
Function to search going by checking each letter in word with the present TrieNode->data
*/
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

/*
DFS on the Data Structure, printing all words
*/
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



