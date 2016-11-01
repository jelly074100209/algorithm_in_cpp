#ifndef BST_H
#define BST_H

#include <queue>
#include <stack>

//定义栈
template<class T>
class Stack : public stack<T>
{
public:
	T pop()
	{
		T tmp = top();
		stack<T>::pop();
		return tmp;
	}
};

//定义队列
template<class T>
class Queue : public queue<T>
{
public:
	T dequeue()
	{
		T tmp = front();
		queue<T>::pop();
		return tmp;
	}

	void enqueue(const T& el)
	{
		push(el);
	}
};

template<class T>
class BSTNode
{
public:
	BSTNode<T> *left, *right;
	T element;
	BSTNode()
	{
		left = right = 0;
	}
	BSTNode(const T& el, BSTNode<T>* l = 0, BSTNode<T>* r = 0)
	{
		element = el;
		left = l;
		right = r;
	}
};

template<class T>
class BST
{
public:
	BST()
	{
		root = 0;
	}
	~BST()
	{
		clear();
	}
	void clear()
	{
		clear(root);
		root = 0;
	}
	bool isEmpty() const
	{
		return root == 0;
	}

	void preorder()
	{
		preorder(root);
	}
	void inorder()
	{
		inorder(root);
	}
	void postorder()
	{
		postorder(root);
	}
	void insert(const T&);
	void rescursiveInsert(const T& el)
	{
		recuresiveInsert(root, el);
	}
	T* search(const T& el) const
	{
		return search(root, el);
	}
	T* recuresiveSearch()
	{
		return recuresiveSearch(root, el);
	}
	
	void deleteByCopying(BSTNode<T>* &);
	void findAndDeleteByCopying(const T&);
	void deleteByMerging(BSTNode<T>* &);
	void findAndDeleteByMerging(const T&);
	void iterativePreorder();
	void iterativeInorder();
	void iterativePostorder();
	void breadthFirst();
	void MorrisPreorder();
	void MorrisInorder();
	void MorrisPostorder();
	void balance(T*, int, int);

protected:
	BSTNode<T>* root;
	void clear(BSTNode<T>*);
	void recuresiveInsert(BSTNode<T>* &, const T&);
	T* search(BSTNode<T>*, const T&) const;
	T* recuresiveSearch(BSTNode<T>*, const T&) const;
	void preorder(BSTNode<T>*);
	void inorder(BSTNode<T>*);
	void postorder(BSTNode<T>*);
	virtual void visit(BSTNode<T>* p)
	{
		cout << p->element << ' ';
	}
};

//实现部分
template<class T>
void BST<T>::clear(BSTNode<T>* p)
{
	//使用递归删除节点
	if (p != 0)
	{
		clear(p->left);
		clear(p->right);
		delete p;
	}
}

template<class T>
void BST<T>::insert(const T& el)
{
	BSTNode<T> *p = root, *prev = 0;
	while (p != 0)//如果树非空，则找到一个合适的子节点
	{
		prev = p;
		if (el < p->element)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	if (root == 0)//如果树为空
	{
		root = new BSTNode<T>(el);
	}
	else if (el < prev->element)
	{
		prev->left = new BSTNode<T>(el);
	}
	else
	{
		prev->right = new BSTNode<T>(el);
	}
}

template<class T>
void BST<T>::recuresiveInsert(BSTNode<T>*& p, const T& el)
{
	if (p == 0)
	{
		p = new BSTNode<T>(el);
	}
	else if (el < p->element)
	{
		recuresiveInsert(p->left, el);
	}
	else
	{
		rescursiveInsert(p->right, el);
	}
}

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const
{
	while (p != 0)
	{
		if (el == p->element)
		{
			return &p->element;
		}
		else if (el < p->element)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	return 0;
}

template<class T>
T* BST<T>::recuresiveSearch(BSTNode<T>* p, const T& el) const
{
	if (p != 0)
	{
		if (el == p->element)
		{
			return &p->element;
		}
		else if (el < p->element)
		{
			return recuresiveSearch(p->left, el);
		}
		else
		{
			return recuresiveSearch(p->right, el);
		}
	}
	else
	{
		return 0;
	}
}

//中序
template<class T>
void BST<T>::inorder(BSTNode<T>* p)
{
	if (p != 0)
	{
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}

//前序
template<class T>
void BST<T>::preorder(BSTNode<T> *p)
{
	if (p != 0)
	{
		visit(p);
		preorder(p->left);
		preorder(p->right);
	}
}

//后序
template<class T>
void BST<T>::postorder(BSTNode<T>* p)
{
	if (p != 0)
	{
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>* &node)
{
	BSTNode<T>* previous, *tmp = node;
	if (node->right == 0)
	{
		node = node->left;
	}
	else if (node->left == 0)
	{
		node = node->right;
	}
	else
	{
		tmp = node->left;
		previous = node;
		while (tmp->right != 0)
		{
			previous = tmp;
			tmp = tmp->right;
		}
		node->element = tmp->element;
		if (previous == node)
		{
			previous->left = tmp->left;
		}
		else
		{
			previous->right = tmp->left;
		}
	}
	delete tmp;
}

template<class T>
void BST<T>::findAndDeleteByCopying(const T& el)
{
	BSTNode<T> *p = root, *prev = 0;
	while (p != 0 && !(p->el == el))
	{
		prev = p;
		if (el < p->element)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	if (p != 0 && p->element == el)
	{
		if (p == root)
		{
			deleteByCopying(root);
		}
		else if (prev->left == p)
		{
			deleteByCopying(prev->left);
		}
		else
		{
			deleteByCopying(prev->right);
		}
	}
	else if (root != 0)
	{
		cout << "el " << el << " is not in the tree" << endl;
	}
	else
	{
		cout << "the tree is empty!" << endl;
	}
}

template<class T>
void BST<T>::deleteByMerging(BSTNode<T>* &node)
{
	BSTNode<T> *tmp = node;
	if (node != 0)
	{
		if (!node->right)
		{
			node = node->left;
		}
		else if (node->left == 0)
		{
			node = node->right;
		}
		else
		{
			tmp = node->left;
			while (tmp->right != 0)
			{
				tmp = tmp->right;
			}
			tmp->right = node->right;
			tmp = node;
			node = node->left;
		}
		delete tmp;
	}
}

template<class T>
void BST<T>::findAndDeleteByMerging(const T& el)
{
	BSTNode<T> *node = root, *prev = 0;
	while (node != 0)
	{
		if (node->el == el)
		{
			break;
		}
		prev = node;
		if (el < node->element)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	if (node != 0 && node->el == el)
	{
		if (node == root)
		{
			deleteByMerging(root);
		}
		else if (prev->left == node)
		{
			deleteByMerging(prev->left);
		}
		else
		{
			deleteByMerging(prev->right);
		}
	}
	else if (root != 0)
	{
		cout << "el " << el << " is not in the tree!" << endl;
	}
	else
	{
		cout << "the tree is empty!" << endl;
	}
}

//先序 迭代实现，使用栈
template<class T>
void BST<T>::iterativePreorder()
{
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root;
	if (p != 0)
	{
		travStack.push(p);
		while (!travStack.empty())
		{
			p = travStack.pop();
			visit(p);
			if (p->right != 0)
			{
				travStack.push(p->right);
			}
			if (p->left != 0)
			{
				travStack.push(p->left);//后进先出
			}
		}
	}
}

template<class T>
void BST<T>::iterativeInorder()
{
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root;
	while (p != 0)
	{
		while (p != 0)
		{
			if (p->right)//stack push
			{
				travStack.push(p->right);
			}
			travStack.push(p);
			p = p->left;
		}
		p = travStack.pop();
		while (!travStack.empty() && p->right == 0)//stack pop
		{
			visit(p);
			p = travStack.pop();
		}
		visit(p);
		if (!travStack.empty())
		{
			p = travStack.pop();
		}
		else
		{
			p = 0;
		}
	}
}

template<class T>
void BST<T>::iterativePostorder()
{
	Stack<BSTNode<T>*> travStack;
	BSTNode<T>* p = root, *q = root;
	while (p != 0)
	{
		for (; p->left != 0; p = p->left)
		{
			travStack.push(p);
		}
		while (p->right == 0 || p->right == q)
		{
			visit(p);
			q = p;
			if (travStack.empty())
			{
				return;
			}
			p = travStack.pop();
		}
		travStack.push(p);
		p = p->right;
	}
}

//宽度优先 使用队列
template<class T>
void BST<T>::breadthFirst()
{
	Queue<BSTNode<T>*> queue;
	BSTNode<T> *p = root;
	if (p != 0)
	{
		queue.enqueue(p);
		while (!queue.empty())
		{
			p = queue.dequeue();
			visit(p);
			if (p->left != 0)
			{
				queue.enqueue(p->left);
			}
			if (p->right != 0)
			{
				queue.enqueue(p->right);
			}
		}
	}
}

template<class T>
void BST<T>::MorrisInorder()
{
	BSTNode<T> *p = root, *tmp;
	while (p != 0)
	{
		if (p->left == 0)
		{
			visit(p);
			p = p->right;
		}
		else
		{
			tmp = p->left;
			while (tmp->right != 0 && tmp->right != p)
			{
				tmp = tmp->right;
			}
			if (tmp->right == 0)
			{
				tmp->right = p;
				p = p->left;
			}
			else
			{
				visit(p);
				tmp->right = 0;
				p = p->right;
			}
		}
	}
}

template<class T>
void BST<T>::MorrisPreorder()
{
	BSTNode<T> *p = root, *tmp;
	while (p != 0)
	{
		if (p->left == 0)
		{
			visit(p);
			p = p->right;
		}
		else
		{
			tmp = p->left;
			while (tmp->right != 0 && tmp->right != p)
			{
				tmp = tmp->right;
			}
			if (tmp->right == 0)
			{
				visit(p);
				tmp->right = p;
				p = p->left;
			}
			else
			{
				tmp->right = p;
				p = p->right;
			}
		}
	}
}

template<class T>
void BST<T>::MorrisPostorder()
{
	BSTNode<T> *p = new BSTNode<T>(), *tmp, *q, *r, *s;
	p->left = root;
	while (p != 0)
	{
		if (p->left == 0)
		{
			p = p->right;
		}
		else
		{
			tmp = p->left;
			while (tmp->right != 0 && tmp->right != p)
			{
				tmp = tmp->right;
			}
			if (tmp->right == 0)
			{
				tmp->right = p;
				p = p->left;
			}
			else
			{
				for (q = p->left, r = q->right, s = r->right; r != p; q = r, r = s, s = s->right)
				{
					r->right = q;
				}
				for (s = q->right; q != p->left; q->right = r, r = q, q = s, s = s->right)
				{
					visit(q);
				}
				visit(p->left);
				tmp->right = 0;
				p = p->right;
			}
		}
	}
}

template<class T>
void BST<T>::balance(T* data, int first, int last)
{
	if (first <= last)
	{
		int middle = (first + last) / 2;
		insert(data[middle]);
		balance(data, first, middle - 1);
		balance(data, middle + 1, last);
	}
}

#endif