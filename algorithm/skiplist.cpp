#ifndef SkiplistList_H_
#define SkiplistList_H_

/*
参考：
    http://ifeve.com/cas-skiplist/
    open data structures(in C++)
    redis
    leveldb
*/

#include <cstdlib>
#include <cstring>

template<class T>
class SkiplistList {
protected:
    const int max_sheight = 32;
    T null;
    struct Node {
        T x;
        int heigth;//随机生成的高度, 作为下面两位数据成员的长度
        int *length;//同层内，当前节点到下一个节点之间有多少个节点<如果next指针不为空, 则该层length最少为1, 要理解这个>
        Node **next;
    };
    Node *sentinel;
    int sheight;
    int nNode;

    Node* newNode (T x, int h) {
        Node* u = new Node();
        u->x = x;
        u->height = h;
        u->length = new int[h+1];
        u->next = new Node*[h+1];
        return u;
    }

    void delNode (Node* u) {
        delete[] u->length;
        delete[] u->next;
        delete u;
    }

    Node* findPreNode (int i) {
        Node* u = sentinel;
        int r = sheight;
        int j = -1;
        while (r >= 0) {
            //不降层的循环
            while (u->next[r] != NULL && j + u->length[r] < i) {
                j += u->length[r];
                u = u->next[r];
            }
            r--;
        }
        return u;
    }

    Node* addNode(int i, Node* w) {
        Node* u = sentinel;
        int k = w->height;
        int r = sheight;
        int j = -1;
        while (r >= 0) {
            while (u->next[r] != NULL && j + u->length[r] < i) {
                j += u->length[r];
                u = u->next[r];
            }
            u->length[r]++;
            if (r <= k) {
                w->next[r] = u->next[r];
                u->next[r] = w;
                w->length[r] = u->length[r] - (i - j);
                u->length[r] = i - j;
            }
            r--;
        }
        nNode++;
        return u;
    }

public:
    SkiplistList() {};
    virtual ~SkiplistList() {};

    T get(int i) {
        return findPreNode(i)->next[0]->x;
    }

    T set(int i, T x) {
        Node* u = findPreNode(i)->next[0];
        T y = u->x;
        u->x = x;
        return y;
    }

    void add(int i, T x) {
        Node* u = new Node(x, pickHeight());
        if (u->heigth > sheight) {
            sheight = u->heigth;
        }
        addNode(i, u);
    }

    T remove(int i) {
        T x = null;
        Node* u = sentinel, *del;
        int r = sheight;
        int j = -1;
        while (r >= 0) {
            while (u->next[r] != NULL && j + u->length[r] < i) {
                j += u->length[r];
                u = u->next[r];
            }
            u->length[r]--;
            if (j + u->length[r] + 1 == i && u->next[r] != NULL) {
                x = u->next[r]->x;
                u->length[r] += u->next[r]->length[r];
                del = u->next[r];
                u->next[r] = u->next[r]->next[r];
                if (u == sentinel && u->next[r] == NULL) {
                    sheight--;
                }
            }
            r--;
        }
        delNode(del);
        nNode--;
        return x;
    }

    int pickHeight() {
        int z = rand();
        int k = 0;
        int m = 1;
        while ((z & m) != 0) {
            k++;
            m <<= 1;
        }
        return k;
    }

    void clear() {
        Node* u = sentinel->next[0];
        while (u != NULL) {
            Node* next = u->next[0];
            delNode(u);
            u = next;
        }
        memset(sentinel->next, '\0', sizeof(Node)*max_sheight);
        memset(sentinel->length, 0, sizeof(Node)*max_sheight);
        sheight = 0;
        nNode = 0;
    }

    int size() {
        return nNode;
    }
};


template<class T>
SkiplistList<T>::SkiplistList() {
    null = (T)NULL;
    n = 0;
    sentinel = newNode(null, max_sheight);
    memset(sentinel->next, '\0', sizeof(Node*)*sentinel->height);
    memset(sentinel->length, 0, sizeof(Node*)*sentinel->height);
    h = 0;
}

template<class T>
SkiplistList<T>::~SkiplistList() {
    clear();
    deleteNode(sentinel);
}
#endif