/**
 * @file        LinkedList.c
 * @brief       連結リスト管理
 * @author      Keitetsu
 * @date        2013/09/21
 * @copyright   Copyright (c) 2013 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"


LIST_ELEMENT_T *LinkedList_createList(
        void *object)
{
    return LinkedList_createElement(object);
}


LIST_ELEMENT_T *LinkedList_createElement(
        void *object)
{
    LIST_ELEMENT_T *tmp;

    tmp = (LIST_ELEMENT_T *)malloc(sizeof(LIST_ELEMENT_T));
    if (tmp != NULL) {
        tmp->object = object;
        tmp->prev = tmp;
        tmp->next = tmp;
    }

    return tmp;
}


LIST_ELEMENT_T *LinkedList_addElementTail(
        LIST_ELEMENT_T *head,
        void *object)
{
    LIST_ELEMENT_T *tmp;
    LIST_ELEMENT_T *tail;

    if (head == NULL) {
        tmp = LinkedList_createList(object);
    }
    else {
        tail = head->prev;
        tmp = LinkedList_createElement(object);
        tmp->prev = tail;
        tmp->next = head;
        head->prev = tmp;
        tail->next = tmp;
    }

    return tmp;
}


void LinkedList_showList(
        LIST_ELEMENT_T *head,
        void (*show)(void *))
{
    LIST_ELEMENT_T *tmp;
    LIST_ELEMENT_T *tail;

    tail = head->prev;
    tmp = head;
    while (1) {
        (*show)(tmp->object);

        if (tmp == tail) {
            break;
        }
        else {
            tmp = tmp->next;
        }
    }

    return;
}


LIST_ELEMENT_T *LinkedList_eraseList(
        LIST_ELEMENT_T *head)
{
    LIST_ELEMENT_T *tmp;

    (head->prev)->next = NULL;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }

    return head;
}

