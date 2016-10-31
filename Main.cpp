#include <iostream>
#include <string>
#include <assert.h>
#include <time.h>

#include "data_structure/List.h"
#include "data_structure/DLList.h"
#include "data_structure/SkipList.h"

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
	/*跳跃链表 主要用于快速查找链表*/

	SkipList<int> skiplist;
	skiplist.choosePowers();
	for (int i = 0; i < 20; i++)
	{
		skiplist.skipListInsert(i);
	}
	cout<<*skiplist.skipListSearch(18)<<endl;

	/*二叉树*/

	const time_t t2 = time(NULL);
	cout << "time is: " << t2-t1 << endl;

}