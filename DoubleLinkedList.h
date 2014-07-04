#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define DELETE_DATA 1
#define DELETE_AT_POSITION 2

using namespace std;

/*Linked List node*/
template <typename T>
struct DLLNode
{
    T data;
    struct DLLNode<T> *next;
    struct DLLNode<T> *prev;
};
/*Linked list head node with count*/
template <typename T>
struct DoubleLinkedList
{
        int count;
        DLLNode<T> * header;
};



///////////////////////FUNCTIONS//////////////////////////

template <typename T>
DoubleLinkedList<T> * createDLL(DoubleLinkedList<T> *l)
{
    l = (DoubleLinkedList<T> *)malloc(sizeof(DoubleLinkedList<T>));
    l->count = 0;
    l->header = NULL;
    return l;
}


template <typename T>
DoubleLinkedList<T>* endInsertionDLL(DoubleLinkedList<T> *list,T data)
{
    DLLNode<T> *temp = (DLLNode<T> *)malloc(sizeof(DLLNode<T>));
    temp->next = NULL;
    temp->data = data;
    temp->prev = NULL;
    if(list->header == NULL)
        list->header = temp;
    else
    {
        DLLNode<T> *cur = list->header;
        while(cur->next != NULL)
              cur = cur->next;
        cur->next = temp;
        temp->prev = cur;
    }
    (list->count)++;
    return list;
}


template <typename T>
void displayDoubleLinkedList(DoubleLinkedList<T> * list)
{
    DLLNode<T> *temp = list->header;
    cout<<"Number of nodes: "<<list->count<<endl;
    while(temp->next!= NULL)
    {
        cout<<temp->data<<"->";
        temp = temp->next;
    }
    cout<<temp->data<<endl;
}

template <typename T>
DoubleLinkedList<T> * startInsertionDLL(DoubleLinkedList<T> *list,T data)
{
    DLLNode<T> *temp = (DLLNode<T> *)malloc(sizeof(DLLNode<T>));
    temp->prev = temp;
    temp->next = list->header;
    temp->data = data;
    list->header = temp;
    list->count++;
    return list;
}

template <typename T>
DoubleLinkedList<T>* middleInsertionDLL(DoubleLinkedList<T> *list,T data,int position)
{
    if(position > list->count)
        return list;
    DLLNode<T> *temp = (DLLNode<T> *)malloc(sizeof(DLLNode<T>));
    temp->next = NULL;
    temp->prev = NULL;
    temp->data = data;
    if(list->header == NULL)
            list->header = temp;

    else
    {
        DLLNode<T> *cur = list->header;
        --position;
        while(cur->next != NULL && --position)
            cur = cur->next;
        temp->next = cur->next;
        cur->next->prev = temp;
        cur->next = temp;
        temp->prev = cur;
    }
    (list->count)++;
    return list;
}


template <typename T>
DoubleLinkedList<T> *deleteDataFromDLL(DoubleLinkedList<T> *list, T data)
{
    DLLNode<T> *cur = list->header;
    DLLNode<T> *prev;
    if(cur->data = data)
        list->header = cur->next;
    else
    {
        while(cur->next!= NULL && cur->data != data)
        {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        cur->next->prev = prev;
    }
    free(cur);
    list->count--;
    return list;
}

template <typename T>
DoubleLinkedList<T> * deleteDLLNodeAt(DoubleLinkedList<T> * list, int position)
{
    DLLNode<T> *cur = list->header;
    DLLNode<T> *prev;
    
    if(!position)
        list->header = cur->next;

    while(cur!= NULL && --position)
    {
        prev = cur;
        cur = cur->next;
    }
    prev = cur->next;
    cur->next->prev = prev;
    free(cur);
    list->count--;
    return list;
}

template <typename T>
void deleteNodes(DLLNode<T> *cur)
{
    if(cur == NULL)
        return;
    deleteNodes(cur->next);
        free(cur);
}

template <typename T>
void deleteLinkedList(DoubleLinkedList<T> *list)
{
    deleteNodes(list->header);
    free(list);
}

template <typename T>
T* searchDoubleLinkedList(DoubleLinkedList<T> *list, T data)
{
    DLLNode<T> *node = list->header;
    while(node->data != data || node!= NULL)
        node = node->next;
    return node;
}