#ifndef THREADED_TREE_H
#define THREADED_TREE_H

template<class T>
class ThreadedNode
{
public:
	ThreadedNode()
	{
		left = right = 0;
	}
	ThreadedNode(const T& el, ThreadedNode *l = 0, ThreadedNode *r = 0)
	{
		key = el; left = l; right = r; successor = 0;
	}
	ThreadedNode *left, *right;
	T key;
	unsigned int successor : 1; //表示只占一bit，0表示后继，1表示前驱
};

template<class T>
class ThreadedTree
{
public:
	ThreadedTree()
	{
		root = 0;
	}
	~ThreadedTree()
	{
		clear();
	}
	void clear()
	{
		clear(root); root = 0;
	}
	void virtual visit(ThreadedNode<T>* p)
	{
		cout << p->key << " ";
	}
	void preorder();
	void inorder();
	void postorder();
	void insert(const T&);
protected:
	ThreadedNode<T>* root;
	void clear(ThreadedNode<T>*);
};

template<class T>
void ThreadedTree<T>::clear(ThreadedNode<T> *p)
{
	if (p != 0)
	{
		clear(p->left);
		if (p->successor == 0) //go to the right only if it is a descendant
		{
			clear(p->right);
		}
		delete p;
	}
}

template<class T>
void ThreadedTree<T>::insert(const T& el)
{
	ThreadedNode<T> *p, *prev = 0, *newNode;
	newNode = new ThreadedNode<T>(el);
	if (root == 0)//如果是空树则直接插入
	{
		root = newNode;
		return;
	}
	p = root;
	while (p != 0)//找到一个合适的节点准备插入
	{
		prev = p;//赋值给当前节点的前驱
		if (p->key > el)
		{
			p = p->left;
		}
		else if (p->successor == 0)
		{
			p = p->right;
		}
		else break;
	}
	if (prev->key > el)//左子树
	{
		prev->left = newNode;
		newNode->successor = 1;
		newNode->right = prev;//构造前驱线索
	}
	else if (prev->successor == 1)//如果是右子树并且父节点有前驱，则取消父节点前驱
	{
		newNode->successor = 1;
		prev->successor = 0;
		newNode->right = prev->right;
		prev->right = newNode;//将新节点放到右子树
	}
	else
	{
		prev->right = newNode;
	}
}

template<class T>
void ThreadedTree<T>::inorder()
{
	ThreadedNode<T> *prev, *p = root;
	if (p != 0)
	{
		while (p->left != 0)
		{
			p = p->left;//先到最左子树
		}
		while (p != 0)
		{
			visit(p);//访问最左子树节点
			prev = p;
			p = p->right;
			if (p != 0 && prev->successor == 0)
			{
				while (p->left != 0)
				{
					p = p->left;
				}
			}
		}
	}
}

template<class T>
void ThreadedTree<T>::preorder()
{
	ThreadedNode<T> *p = root;
	while (p != 0)
	{
		visit(p);
		if (p->left != 0)
		{
			p = p->left;
		}
		else if (p->right != 0 && p->successor == 0)
		{
			p = p->right;
		}
		else
		{
			while (p->successor == 1)
			{
				p = p->right;
			}
			p = p->right;
		}
	}
}

template<class T>
void ThreadedTree<T>::postorder()
{
	ThreadedNode<T> *q, *r, *s, *p = new ThreadedNode<T>, *rightmost, *dummy = p;
	p->left = root;
	for (rightmost = root; rightmost->right != 0; rightmost = rightmost->right);
	rightmost->successor = 1;
	rightmost->right = p;
	enum direction
	{
		goLeft, goRight, visiting
	} dir = goLeft;
	while (p != 0)
	{
		if (dir == goLeft)
		{
			if (p->left != 0)
			{
				p = p->left;
			}
			else
			{
				dir = goRight;
			}
		}
		else if (dir == goRight)
		{
			if (p->right != 0 && p->successor == 0)
			{
				p = p->right;
				dir = goLeft;
			}
			else
			{
				dir = visiting;
			}
		}
		else
		{
			if (p == dummy)
			{
				rightmost->right = 0;
				rightmost->successor = 0;
				delete dummy;
				return;
			}
			visit(p);
			if (p->right != 0 && p->right->left == p)
			{
				p = p->right;
				dir = goRight;
			}
			else
			{
				for (q = p->right->left, r = q->right, s = r->right; r != p; q = r, r = s, s = s->right)
				{
					r->right = q;
				}
				for (s = q->right; q != p->right->left; q->right = r, r = q, q = s, s = s->right)
				{
					visit(q);
				}
				visit(q);
				p = p->right;
				dir = goRight;
			}
		}
	}
}

#endif