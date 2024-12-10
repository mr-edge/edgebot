#ifndef EDGEBOTQUEUE_H
#define EDGEBOTQUEUE_H

#include "animations.h"

struct AnimationQueueNode {
    Animation* item;
    struct AnimationQueueNode* next;
};


void enqueue(AnimationQueueNode **head, Animation* val) {
    AnimationQueueNode *new_node = (AnimationQueueNode*)malloc(sizeof(AnimationQueueNode));
    if (!new_node) return;

    new_node->item = val;
    new_node->next = *head;

    *head = new_node;
}

Animation* dequeue(AnimationQueueNode **head) {
    AnimationQueueNode *current, *prev = NULL;
    Animation* retval = NULL;

    if (*head == NULL) return NULL;

    current = *head;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    retval = current->item;
    free(current);
    
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;

    return retval;
}

#endif