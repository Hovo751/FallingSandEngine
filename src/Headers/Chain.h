#pragma once
#include <iostream>
#include "IdCreator.h"

struct Node {
    int value;
    Node* next;
    Node* prev;
    int id;
    Node(int v) : value(v), next(nullptr), prev(nullptr) {}
};

class IntChain {
    int count = 0;
    unsigned int id = getId();

public:
    Node* start = nullptr;
    Node* end = nullptr;

    Node* add(int val, unsigned int num) {
        num = (num <= count) ? num : 0;
        Node* newNode = new Node(val);
        newNode->id = id;

        if (count == 0)
        {
            start = newNode;
            end = newNode;
        }
        else
        {
            if (num == 0)
            {
                newNode->next = start;
                start->prev = newNode;
                start = newNode;
            }
            else if (num == count)
            {
                newNode->prev = end;
                end->next = newNode;
                end = newNode;
            }
            else if (num < count / 2)
            {
                Node* crt = start;
                for (int i = 1; i < num; i++)
                {
                    crt = crt->next;
                }
                newNode->prev = crt;
                newNode->next = crt->next;
                newNode->next->prev = newNode;
                newNode->prev->next = newNode;
            }
            else
            {
                Node* crt = end;
                for (int i = count - 1 - num; i > 0; i--)
                {
                    crt = crt->prev;
                }
                newNode->next = crt;
                newNode->prev = crt->prev;
                newNode->next->prev = newNode;
                newNode->prev->next = newNode;
            }
        }
        count++;
        return newNode;
    }

    void deleteByAdr(Node* node) {
        if (node->id == id)
        {
            if (node->next)
            {
                node->next->prev = node->prev;
                if (!node->prev) {
                    start = node->next;
                }
            }

            if (node->prev)
            {
                node->prev->next = node->next;
                if (!node->next) {
                    end = node->prev;
                }
            }

            delete node;
            count--;
        }
        if (count == 0) {
            start = nullptr;
            end = nullptr;
        }
    }

    void print()
    {
        Node* crt = start;
        for (int i = 0; i < count; i++)
        {
            std::cout << crt->value << ' ';
            crt = crt->next;
        }
    }


    int size() const {
        return count;
    }
};
