#ifndef DL_LIST_H
#define DL_LIST_H

//节点类
template<class T>
class DLLNode
{
public:
	DLLNode()
	{
		next = prev = 0;
	}
	DLLNode(const T& el, DLLNode<T> *n = 0, DLLNode<T> *p = 0)
	{
		next = n;
		prev = p;
		element = el;
	}

	DLLNode<T> *next, *prev;
	T element;
};

template<class T>
class DLList
{
public:
	DLList()
	{
		head = tail = 0;
	}
	~DLList()
	{
		clear();
	}
	void addToTail(const T&);
	T deleteFromTail();
	bool isEmpty() const
	{
		return head == 0;
	}

	void clear();
	void setToNull()
	{
		head = tail = 0;
	}

	void addToHead(const T&);
	T deleteFromHead();
	T firstEl();
	T* find(const T&) const;

protected:
	DLLNode<T> *head, *tail;

	//重载<<
	friend ostream& operator<<(ostream& out, const DLList<T>& dll)
	{
		for (DLLNode<T>* tmp = dll.head; tmp != 0; tmp = tmp->next)
		{
			out << tmp->element << ' ';
		}
		return out;
	}
};

template<class T>
void DLList<T>::addToHead(const T& el)
{
	if (head != 0)
	{
		head = new DLLNode<T>(el, head, 0);
		head->next->prev = head;//注意双向连接，连接新的head
	}
	else
	{
		head = tail = new DLLNode<T>(el);
	}
}

template<class T>
void DLList<T>::addToTail(const T& el)
{
	if (tail != 0)
	{
		tail = new DLLNode<T>(el, 0, tail);//加到tail后面
		tail->prev->next = tail;//连接新的tail
	}
	else
	{
		head = tail = new DLLNode<T>(el);
	}
}

template<class T>
T DLList<T>::deleteFromHead()
{
	T el = head->element;
	if (head == tail)//只有一个节点
	{
		delete head;
		head = tail = 0;
	}
	else
	{
		head = head->next;
		delete head->prev;
		head->prev = 0;
	}
	return el;
}

template<class T>
T DLList<T>::deleteFromTail()
{
	T el = tail->element;
	if (head == tail)
	{
		delete tail;
		delete head;
		head = tail = 0;
	}
	else
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = 0;
	}

	return el;
}

template<class T>
T* DLList<T>::find(const T& el) const
{
	DLLNode<T>* tmp = head;
	for (; tmp != 0 !(tmp->element == el); tmp = tmp->next);
	if (tmp == 0)
	{
		return 0;
	}
	else
	{
		return &tmp->element;
	}
}

template<class T>
T DLList<T>::firstEl()
{
	if (head != 0)
	{
		return head->element;
	}
	else
	{
		return 0;
	}
}

template<class T>
void DLList<T>::clear()
{
	for (DLLNode<T>* tmp; head != 0;)
	{
		tmp = head;
		head = head->next;
		delete tmp;//逐个删除节点
	}
}

#endif // !DL_LIST_H
