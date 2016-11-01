#ifndef ListNode_H
#define	ListNode_H

template <class T>
class ListNode
{
public:
	T element;
	ListNode<T>* next;
	
	ListNode()
	{
		next = 0;
	}

	ListNode(T el, ListNode<T> *ptr = 0)
	{
		element = el;
		next = ptr;
	}
};

#endif