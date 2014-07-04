#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define DELETE_DATA 1
#define DELETE_AT_POSITION 2

using namespace std;

/*Linked List node*/
template <typename T>
struct LLNode
{
    int data;
    struct LLNode<T> *next;
};

/*Linked list head node with count*/
template <typename T>
struct LinkedList
{
        int count;
        LLNode<T> * header;
};


///////////////////////FUNCTIONS//////////////////////////

template <typename T>
LinkedList<T> * createSingleLL(LinkedList<T> *l)
{
    l = (LinkedList<T> *)malloc(sizeof(LinkedList<T>));
    l->count = 0;
    l->header = NULL;
    return l;
}


template <typename T>
LinkedList<T>* endInsertionLL(LinkedList<T> *list,int data)
{
    LLNode<T> *temp = (LLNode<T> *)malloc(sizeof(LLNode<T>));
    temp->next = NULL;
    temp->data = data;
    if(list->header == NULL)
        list->header = temp;
    else
    {
        LLNode<T> *cur = list->header;
        while(cur->next != NULL)
              cur = cur->next;
        cur->next = temp;
    }
    (list->count)++;
    return list;
}


template <typename T>
void displayLinkedList(LinkedList<T> * list)
{
    LLNode<T> *temp = list->header;
    cout<<"Number of nodes: "<<list->count<<endl;
    while(temp->next!= NULL)
    {
        cout<<temp->data<<"->";
        temp = temp->next;
    }
    cout<<temp->data<<endl;
}

template <typename T>
LinkedList<T> * startInsertionLL(LinkedList<T> *list,int data)
{
    LLNode<T> *temp = (LLNode<T> *)malloc(sizeof(LLNode<T>));
    temp->next = list->header;
    temp->data = data;
    list->header = temp;
    list->count++;
}

template <typename T>
LinkedList<T>* middleInsertionLL(LinkedList<T> *list,int data,int position)
{
    LLNode<T> *temp = (LLNode<T> *)malloc(sizeof(LLNode<T>));
    temp->next = NULL;
    temp->data = data;
    if(list->header == NULL)
        list->header = temp;
    else
    {
        LLNode<T> *cur = list->header;
        --position;
        while(cur->next != NULL && --position)
            cur = cur->next;
        temp->next = cur->next;
        cur->next = temp;
    }
    (list->count)++;
    return list;
}

template <typename T>
LinkedList<T> * deleteLLNode(LinkedList<T> * list, int flag, int dataorposition)
{
    LLNode<T> *cur = list->header;
    LLNode<T> *prev;
    if(flag == DELETE_DATA)
    {
        if(cur->data = dataorposition)
            list->header = cur->next;
        else
        {
           while(cur->next!= NULL && cur->data != dataorposition)
            {
                prev = cur;
                cur = cur->next;
            }
            prev->next = cur->next;
        }
        free(cur);
    }
    else if(flag == DELETE_AT_POSITION)
    {
        if(!dataorposition)
            list->header = cur->next;

        while(cur!= NULL && --dataorposition)
        {
            prev = cur;
            cur = cur->next;
        }
        prev = cur->next;
        free(cur);
    }
    else{
        cout<<"Wrong flag!"<<endl;
        return list;
    }
    list->count--;
    return list;
}

template <typename T>
void deleteNodes(LLNode<T> *cur)
{
    if(cur == NULL)
        return;
    deleteNodes(cur->next);
        free(cur);
}

template <typename T>
void deleteLinkedList(LinkedList<T> *list)
{
    deleteNodes(list->header);
    free(list);
}


template <typename T>
LinkedList<T>* reverseLL(LinkedList<T> *list)
{
    if(list->header == NULL || list->count < 2)
        return list;
    reverseUtil(list->header, list->header->next, list);
    return list;
}

template <typename T>
void reverseUtil(LLNode<T> * prev, LLNode<T> * cur, LinkedList<T> *list)
{
    if(prev == list->header)
        prev->next = NULL;

    if(cur->next == NULL)
    {
        cur->next = prev;
        list->header = cur;
        return;
    }
    LLNode<T> *temp = cur->next;
    cur->next = prev;
    reverseUtil(cur, temp, list);
}