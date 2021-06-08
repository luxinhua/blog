---
title: 自己实现动态内存分配思路（有点伪）
date: 2021/6/8
categories: c
---

---
### 伪动态内存分配
---
~~~c
#include <stdio.h>
#include <stdlib.h>

#define MEMMAXSIZE 100
int mem[MEMMAXSIZE];

typedef struct datanode{
    int used;
    int index_baseaddr;
    int size;
    struct datanode *next;
};

struct datanode *HEAD;

int splitmem(int index, int allsize, int needsize){
    return  index+allsize-needsize;
}

struct datanode * spaceRequest(int size){
    struct datanode *p = HEAD;
    while (p->next != NULL){
        p = p->next; 
        if (p->used == 0){
            if (p->size >= size){
                struct datanode *newnode = malloc(sizeof(struct  datanode));
                newnode->index_baseaddr = splitmem(p->index_baseaddr,p->size,size);
                newnode->size = size;
                newnode->used = 1;
                p->size -= size;
                newnode->next = p->next;
                p->next = newnode;
                return newnode;
            }
        }
    }

}

int spaceFree(struct datanode* space){
    struct datanode *p = HEAD;
    struct datanode *q,*pp;
    while (p->next != NULL){
        q = p;
        p = p->next;
        pp = p->next;
        if (p->index_baseaddr == space->index_baseaddr && p->size == space->size){
            p->used = 0;
            if (q->used == 0){
                q->size += p->size;
                q->next = p->next;
            }
            if (pp != NULL) {
                if (pp->used==0){
                    p->size += pp->size;
                    p->next = pp->next;
                }
            }
        }
    }
}

void memPrint(){
    struct datanode *p = HEAD;
    int i;
    int count = 0;
    while(p->next != NULL){
        p = p->next;
        for(i=p->index_baseaddr;i<(p->index_baseaddr+p->size);i++){
            if(p->used == 0)
                printf("\e[0;32m%d  ",mem[i]);
            else
                printf("\e[0m%d  ",mem[i]);
            if(count++ > 20){
                printf("\n");
                count = 0;
            }
        }
    }
    printf("\n----------------------------------------------------------------\n");
}

void memInit(){
    struct datanode *p;
    struct datanode *firstnode;
    p = malloc(sizeof(struct datanode));
    firstnode = malloc(sizeof(struct datanode));
    p->next = NULL;
    p->index_baseaddr = 0;
    p->size = 0;
    p->used = 1;
    firstnode->next = NULL;
    firstnode->used = 0;
    firstnode->index_baseaddr = 0;
    firstnode->size = MEMMAXSIZE;
    p->next = firstnode;
    HEAD = p;
}

int main(){
    memInit();

    struct datanode * a = spaceRequest(10);
    memPrint();
    struct datanode * b = spaceRequest(2);
    memPrint();
    struct datanode * c = spaceRequest(4);
    memPrint();

    spaceFree(a);
    memPrint();
    spaceFree(b);
    memPrint();
    spaceFree(c);
    memPrint();        
}
~~~

---
### 结果效果（绿色是申请的内存)
---
![](mem.png)

