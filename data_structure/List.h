#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include <iostream>
using namespace std;

template<class T>
class List
{
private:
	ListNode<T>* head;
	ListNode<T>* tail;
public:
	List()
	{
		head = tail = 0;
	}
	virtual ~List();
	bool isEmpty()
	{
		return head == 0;
	}

	void addToHead(T);
	void addToTail(T);
	bool deleteFromHead();
	bool deleteFromTail();
	bool deleteListNode(T);
	bool isInList(T) const;
	void printAll() const;
};

template<class T>
List<T>::~List()
{
}

template<class T>
void List<T>::addToHead(T el)
{
	head = new ListNode<T>(el, head);
	if (tail == 0)
	{
		tail = head;
	}
}

template<class T>
void List<T>::addToTail(T el)
{
	if (tail == 0)
	{
		head = tail = new ListNode<T>(el);
	}
	else
	{
		tail->next = new ListNode<T>(el);
		tail = tail->next;//总是把tail置于链表末尾
	}
}

template<class T>
bool List<T>::deleteFromHead()
{
	if (head == 0)
	{
		return false;
	}
	else
	{
		if (head != tail)
		{
			ListNode<T>* tmp = head; //指针可以完美释放head
			head = head->next;
			delete tmp;
		}
		else
		{
			head = tail = 0;
		}
		return true;
	}
}

template<class T>
bool List<T>::deleteFromTail()
{
	if (head == 0)
	{
		return false;
	}
	else
	{
		if (head == tail)
		{
			delete head;
			head = tail = 0;
		}
		else
		{
			ListNode<T>* tmp = head;
			while (tmp->next != tail) //指针是否相等?
			{
				tmp = tmp->next;
			}
			delete tail;
			tail = tmp;
			tail->next = 0;
		}
		return true;
	}
}

template<class T>
bool List<T>::deleteListNode(T el)
{
	if (head == 0)
	{
		return false;
	}
	else
	{
		if (head == tail && tail->element == el)
		{
			delete head;
			head = tail = 0;
			return true;
		}
		else
		{
			if (el == head->element)//如果刚好是头结点
			{
				this->deleteFromHead();
				return true;
			}
			else
			{
				ListNode<T> *pred, *tmp;
				for (pred = head, tmp = head->next; // and a non-head node
					tmp != 0 && !(tmp->element == el);// is deleted;
					pred = pred->next, tmp = tmp->next);
				if (tmp != 0)
				{
					pred->next = tmp->next;
					if (tmp == tail)
						tail = pred;
					delete tmp;
					return true;
				}
				return false;
			}
			return false;
		}
	}
}

template<class T>
bool List<T>::isInList(T el) const
{
	if (head == 0)
	{
		return false;
	}
	else
	{
		ListNode<T>* tmp;
		for (tmp = head; tmp != 0; tmp = tmp->next)
		{
			if (tmp->element == el)
			{
				return true;
			}
		}
		return false;
	}
}

template<class T>
void List<T>::printAll() const
{
	if (head == 0)
	{
		cout << "List is empty" << endl;
	}
	else
	{
		ListNode<T>* tmp;
		for (tmp = head; tmp != 0; tmp = tmp->next)
		{
			cout << tmp->element << " ";
		}
		cout << endl;
		delete tmp;
	}
}

#endif