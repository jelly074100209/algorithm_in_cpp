#ifndef MULTISET_H
#define MULTISET_H
#define _DEFINE_DEPRECATED_HASH_CLASSES 0

#include <iterator>
#include <iostream>
#include <string.h>
#include <set>

using namespace std;

class Person
{
    //friend class lersserAge;
public:
    Person(char *n = "", int a = 0)
    {
        name = _strdup(n);
        age = a;
    }
    bool operator<(const Person& p) const
    {
        return strcmp(name, p.name) < 0;
    }
    bool operator==(const Person& p) const
    {
        return strcmp(name, p.name) == 0 && age == p.age;
    }
private:
    char *name;
    int age;
    friend ostream& operator<< (ostream& out, const Person& p)
    {
        out << "(" << p.name << ", " << p.age << ")";
        return out;
    }
    
};

//class lesserAge
//{
//public:
//    int operator() (const Person& p1, const Person& p2) const
//    {
//        return (p1.age < p2.age);
//    }
//};

void printSet(const set<int>& s, char *c)
{
    cout << c << ": ";
    for (set<int>::const_iterator i = s.begin(); i != s.end(); i++)
    {
        cout << *i << ' ';
        cout << endl;
    }
}

void printMSet(const multiset<int>& s, char *c)
{
    cout << c << ": ";
    for (multiset<int>::const_iterator i = s.begin(); i != s.end(); i++)
    {
        cout << *i << ' ';
    }
    cout << endl;
}

template<class T>
void Union(const set<T>& st1, const set<T>& st2, set<T>& st3)
{
    set<T> tmp(st2);
    if (&st != &st2)
    {
        for (typename set<T>::const_iterator i = st1.begin(); i != st1.end(); i++)
        {
            tmp.insert(*i);
        }
    }
    tmp.swap(st3);
}

#endif