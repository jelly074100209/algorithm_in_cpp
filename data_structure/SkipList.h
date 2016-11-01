#ifndef SKIP_LIST_H
#define SKIP_LIST_H

const int SKIP_LIST_MAX_LEVEL = 4;

template<class T>
class SkipListNode
{
public:
	SkipListNode()
	{
	}
	T key;
	SkipListNode<T> **next;
};

template<class T>
class SkipList
{
public:
	SkipList();
	bool isEmpty() const;
	void choosePowers();
	int chooseLevel();
	T* skipListSearch(const T&);
	void skipListInsert(const T&);

private:
	SkipListNode<T>* root[SKIP_LIST_MAX_LEVEL];//最大层数
	int powers[SKIP_LIST_MAX_LEVEL];
};

template<class T>
SkipList<T>::SkipList()
{
	for (int i = 0; i < SKIP_LIST_MAX_LEVEL; i++)
	{
		root[i] = 0;
	}
}

template<class T>
bool SkipList<T>::isEmpty() const
{
	return root[0] == 0;
}

template<class T>
void SkipList<T>::choosePowers()
{
	powers[SKIP_LIST_MAX_LEVEL - 1] = (2 << (SKIP_LIST_MAX_LEVEL)) - 1; // 2^maxLevel - 1;
	for (int i = SKIP_LIST_MAX_LEVEL - 2, j = 0; i >= 0; i--, j++)
	{
		powers[i] = powers[i + 1] - (2 << j);
	}
}

template<class T>
int SkipList<T>::chooseLevel()
{
	int i, r = (rand() % powers[SKIP_LIST_MAX_LEVEL - 1]) + 1;//随机选取
	//cout << "r is: " << r << endl;
	for (i = 1; i < SKIP_LIST_MAX_LEVEL; i++)
	{
		if (r < powers[i])
		{
			return i - 1; //返回一个小于最高层的level
		}
	}
	return i - 1; //返回最高层
}

template<class T>
void SkipList<T>::skipListInsert(const T& key)
{
	SkipListNode<T> *curr[SKIP_LIST_MAX_LEVEL], *prev[SKIP_LIST_MAX_LEVEL], *newNode;
	int lvl, i;
	curr[SKIP_LIST_MAX_LEVEL - 1] = root[SKIP_LIST_MAX_LEVEL - 1];
	prev[SKIP_LIST_MAX_LEVEL - 1] = 0;
	for (lvl = SKIP_LIST_MAX_LEVEL - 1; lvl >= 0; lvl--)
	{
		while (curr[lvl] && curr[lvl]->key < key)//go to next if smaller
		{
			prev[lvl] = curr[lvl];
			curr[lvl] = *(curr[lvl]->next + lvl);
		}
		if (curr[lvl] && curr[lvl]->key == key)//don't include duplicates
		{
			return;
		}
		if (lvl > 0) //go one level down if not the lowest level, using a link either from the root or from the predecessor
		{
			if (prev[lvl] == 0)
			{
				curr[lvl - 1] = root[lvl - 1];
				prev[lvl - 1] = 0;
			}
			else
			{
				curr[lvl - 1] = *(prev[lvl]->next + lvl - 1);
				prev[lvl - 1] = prev[lvl];
			}
		}
	}
	lvl = chooseLevel(); //随机选取层
	//cout << "lvl is: " << lvl << endl;
	newNode = new SkipListNode<T>;
	newNode->next = new SkipListNode<T>*[sizeof(SkipListNode<T>*) * (lvl + 1)];
	newNode->key = key;
	for (i = 0; i <= lvl; i++) //initialize next fields of newNode and reset to newNode either fields of the root or next fields of newNode's predecessors;
	{
		*(newNode->next + i) = curr[i];
		if (prev[i] == 0)
		{
			root[i] = newNode;
		}
		else
		{
			*(prev[i]->next + i) = newNode;
		}
	}
}

template<class T>
T* SkipList<T>::skipListSearch(const T& key)
{
	if (isEmpty())
	{
		return 0;
	}
	SkipListNode<T> *prev, *curr;
	int lvl;
	for (lvl = SKIP_LIST_MAX_LEVEL - 1; lvl >= 0 && !root[lvl]; lvl--);
	prev = curr = root[lvl];
	while (1)
	{
		if (key == curr->key) //如果相等则返回
		{
			return &curr->key;
		}
		else if (key < curr->key) //if smaller, go down if possible by one level starting from the predecessor which can be the root
		{
			if (lvl == 0)
			{
				return 0;
			}
			else if (curr == root[lvl])
			{
				curr = root[--lvl];
			}
			else
			{
				curr = *(prev->next + --lvl);
			}
		}
		else //if greater, go to the next non-null node on the same level or to a list on a lower level;
		{
			prev = curr;
			if (*(curr->next + lvl) != 0)
			{
				curr = *(curr->next + lvl);
			}
			else
			{
				for (lvl--; lvl >= 0 && *(curr->next + lvl) == 0; lvl--);
				if (lvl >= 0)
				{
					curr = *(curr->next + lvl);
				}
				else
				{
					return 0;
				}
			}
		}
	}
}

#endif // SKIP_LIST_H
