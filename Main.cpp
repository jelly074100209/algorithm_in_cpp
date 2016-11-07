#include <iostream>
#include <string>
#include <assert.h>
#include <time.h>

#include "data_structure/List.h"
#include "data_structure/DLList.h"
#include "data_structure/SkipList.h"
#include "data_structure/BST.h"
#include "algorithm/sorting.h"

using namespace std;

int main() {
	const time_t t1 = time(NULL);

	/* 单向链表 */
	List<int> list;
	for (int i = 0; i < 10; i++)
	{
		list.addToHead(i);
	}
	cout << list.isInList(999999) << endl;
	cout << list.isEmpty() << endl;
	list.deleteListNode(7);
	list.deleteFromTail();
	list.deleteFromHead();
	list.printAll();

	/*双向链表*/
	DLList<int> dllist;
	for (int i = 0; i < 5; i++)
	{
		dllist.addToHead(i);
	}
	for (int i = 10; i > 5; i--)
	{
		dllist.addToTail(i);
	}
	dllist.deleteFromHead();
	dllist.deleteFromTail();
	cout<<dllist.firstEl()<<endl;
	cout << dllist;
	cout << endl;

	/*跳跃链表 主要用于快速查找链表 代替平衡树*/

	SkipList<int> skiplist;
	skiplist.choosePowers();
	for (int i = 0; i < 20; i++)
	{
		skiplist.skipListInsert(i);
	}
	cout<<*skiplist.skipListSearch(18)<<endl;

	/*二叉树*/
	BST<int> tree;
	int balance_list[10];
	for (int i = 10, j=0; i < 20; i++, j++)
	{
		//tree.insert(i);
		balance_list[j] = i;
	}
	tree.balance(balance_list, 0, 9);
	tree.breadthFirst();
	cout << endl;
	tree.preorder();
	cout << endl;
	tree.inorder();
	cout << endl;
	tree.postorder();
	cout << endl;
	tree.iterativePreorder();
	cout << endl;
	tree.iterativeInorder();
	cout << endl;
	tree.iterativePostorder();
	cout << endl;
	tree.MorrisPreorder();
	cout << endl;
	tree.MorrisInorder();//TODO:需要重新改写
	cout << endl;
	tree.MorrisPostorder();
	cout << endl;

	/*排序*/
	int data[10] = { 15, 9, 23, 7, 8, 43, 12, 5, 19, 10 };
	display(data, 10);
	quicksort(data, 10);
	display(data, 10);

	const time_t t2 = time(NULL);
	cout << "time is: " << t2-t1 << endl;

}