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
		element el;
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
	void rescursiveInsert(cosnt T& el)
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
	T* search(const T& el) const
	{
		return search(root, el);
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

#endif