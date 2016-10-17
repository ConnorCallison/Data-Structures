#ifndef STACK_H
#define STACK_H

#include "LinkedListNode.h"

template <typename T>
class Stack
{
private:
    LinkedListNode<T> *_top = nullptr;
    int _size = 0;

public:
    Stack()
    {

    }

    //Adds a new item onto our stack
    void push(T value)
    {
        LinkedListNode<T> *next = new LinkedListNode<T>{value};
        next->setNext(_top);
        _top = next;
        _size++;
    }

    //removes an item from the stack
    T pop()
    {
        LinkedListNode<T> *first = _top;
		if(getSize() > 1)
		{
			_top = _top->getNext();
		}
        T value = first->getValue();
        delete first;
		_size--;
        return value;
    }

    //returns size of stack
    int getSize()
    {
        return _size;
    }

    //returns whether or not stack is empty
    bool isEmpty()
    {
        return _size == 0;
    }
};

#endif // STACK_H
