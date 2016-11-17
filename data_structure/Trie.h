#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Trie;

class TrieNonLeafNode
{
public:
    TrieNonLeafNode()
    {

    }
    TrieNonLeafNode(char);
private:
    bool leaf, endOfWord;
    char *letters;
    TrieNonLeafNode **ptrs;
    friend class Trie;
};

class TrieLeafNode
{
public:
    TrieLeafNode()
    {

    }
    TrieLeafNode(char*);
private:
    bool leaf;
    char *word;
    friend class Trie;
};

class Trie
{
public:
    Trie() : notFound(-1)
    {

    }
    Trie(char*);
    void printTrie()
    {
        *prefix = '\0';
        printTrie(0, root, prefix);
    }
    void insert(char*);
    bool wordFound(char*);
private:
    TrieNonLeafNode *root;
    const int notFound;
    char prefix[80];
    int position(TrieNonLeafNode*, char);
    void addCell(char, TrieNonLeafNode*, int);
    void printTrie(int, TrieNonLeafNode*, char*);
};

TrieLeafNode::TrieLeafNode(char* suffix)
{
    leaf = true;
    word = new char[strlen(suffix) + 1];
    if (word == 0)
    {
        cerr << "Out of memory2.\n";
        exit(-1);
    }
    strcpy(word, suffix);
}

TrieNonLeafNode::TrieNonLeafNode(char ch)
{
    ptrs = new TrieNonLeafNode*;
    letters = new char[2];
    if (ptrs == 0 || letters == 0)
    {
        cerr << "Out of memory3.\n";
        exit(1);
    }
    leaf = false;
    endOfWord = false;
    *ptrs = 0;
    *letters = ch;
    *(letters + 1) = '\0';
}

Trie::Trie(char* word) : nonFound(-1)
{
    root = new TrieNonLeafNode(*word);
    createLeaf(*word, word + 1, root);
}

void Trie::printTrie(int depth, TrieNonLeafNode* p, char *prefix)
{
    register int i;
    if (p->leaf)
    {
        TrieLeafNode *lf = (TrieLeafNode*)p;
        for (i = 1; i <= depth; i++)
        {
            cout << " ";
        }
        cout << " >>" << prefix << "|" << lf->word << endl;
    }
    else
    {
        for (i = strlen(p->letters) - 1; i >= 0; i--)
        {
            if (p->ptrs[i] != 0)
            {
                prefix[depth] = p->letters[i];
                prefix[depth + 1] = '\0';
                printTrie(depth + 1, p->ptrs[i], prefix);
            }
        }
        if (p->endOfWord)
        {
            prefix[depth] = '\0';
            for (i = 1; i <= depth + 1; i++)
            {
                cout << " ";
            }
            cout << ">>>" << prefix << "\n";
        }
    }
}

if Trie::position(TrieNonLeafNode p, char ch)
{
    int i;
    for (i = 0; i < strlen(p->letters) && p->letters[i] != ch; i++);
    if (i < strlen(p->letters))
    {
        return i;
    }
    else return notFound;
}

bool Trie::wordFound((char *word)
{
    TrieNonLeafNode *p = root;
    TrieLeafNode *lf;
    int pos;
    while (true)
    {
        if (p->leaf)
        {
            lf = (TrieLeafNode*)p;
            if (strcmp(word, lf->word) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (*word == '\0')
        {
            if (p->endOfWord)
            {
                return true;
            }
            else return false;
        }
        else if ((pos = position(p, *word)) != notFound && p->ptrs[pos] != 0)
        {
            p = p->ptrs[pos];
            word++;
        }
        else return false;
    }
}

#endif