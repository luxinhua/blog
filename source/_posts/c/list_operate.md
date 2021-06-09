---
title: list operate
date: 2021/6/9
categories: c
---

---
### list 操作
---
~~~c 
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node * head;

void listInit(){
    struct node *p, *firstnode;
    p = malloc(sizeof(struct node));
    p->data = 0;
    p->next = NULL;
    firstnode = malloc(sizeof(struct node));
    firstnode->data = 0;
    firstnode->next = NULL;
    p->next = firstnode;
    head = p;
}

struct node * listAdd(int data){
    struct node *newnode;
    newnode = malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;

    struct node *p = head;
    while(p->next != NULL)
        p = p->next;
    
    p->next = newnode;
    return newnode;
}

void listDel(struct node * node){
    struct node *p = head;
    struct node *q;
    while(p->next != NULL){
        q = p;
        p = p->next;
        if (p->next != NULL){
            if (p->data == node->data)
                q->next = p->next;
        }
    }
}

void listPrint(){
    struct node *p = head;
    while(p->next != NULL){
        p = p->next;
        printf("%d  ",p->data);
    }
    printf("\n");
}

int main(){
    listInit();
    struct node *a = listAdd(1);
    struct node *b = listAdd(2);
    struct node *c = listAdd(3);
    struct node *d = listAdd(4);
    struct node *e = listAdd(5);
    listPrint();

    listDel(a);
    listDel(b);
    listPrint();

}
~~~

---
### 结果
---
~~~bash
    $ ./a.exe
    0  1  2  3  4  5
    0  3  4  5
~~~