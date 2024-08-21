#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "listHandling.h"

char heap[MAX_HEAP_SIZE];
char *programBreak = heap;

node *head = NULL;


void printList() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    node *current = head;
    do {
       printf("Node at %p: sz = %zu, Next = %p, Pre = %p\n",
               (void*)current, current->sz, (void*)current->Next, (void*)current->Pre);
        current = current->Next;
    } while (current != head);
}


void createNode(node *nodePlace, size_t nodeSize)
{
    node *newNode = (node*)nodePlace;
    newNode->sz = nodeSize;

    // If the list is empty
    if (head == NULL)
    {
        newNode->Next = newNode;
        newNode->Pre = newNode;
        head = newNode;
    }
    else
    {
        node *temp = head;

        // Find the correct insertion point
        // Iterate through the list to find where to insert the new node
        do
        {
            if (newNode < temp)
            {
                // Insert the new node between temp and temp->Next
                newNode->Next = temp;
                newNode->Pre = temp->Pre;
                temp->Pre->Next = newNode;
                temp->Pre = newNode;

                // If the new node is inserted at the head, update the head pointer
                if (temp == head)
                {
                    head = newNode;
                }

                return;
            }
            temp = temp->Next;
        } while (temp != head);
        newNode->Next = head;
        newNode->Pre = head->Pre;
        head->Pre->Next = newNode;
        head->Pre = newNode;
    }
}


int deleteNode(node * nodePlace)
{
    if (nodePlace == NULL || head == NULL) return 0; // If the nodePlace is NULL, return 0

    // If the list only contains one node
    if (nodePlace->Next == nodePlace && nodePlace->Pre == nodePlace) {
        nodePlace->Next = nodePlace->Pre = NULL; // Mark the node as deleted
        head = NULL;
        return 1; // Return 1 to indicate successful deletion
    }

    // If the node to delete is the head node
    if (nodePlace == head) {
        head = head->Next; // Move head to the next node
    }

  // Update the links of the neighboring nodes
    nodePlace->Pre->Next = nodePlace->Next;
    nodePlace->Next->Pre = nodePlace->Pre;

    // Mark the node as deleted by setting its Next and Pre pointers to NULL
    nodePlace->Next = nodePlace->Pre = NULL;

    return 1; // Return 1 to indicate successful deletion

}

