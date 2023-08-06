/*
    So, which of the favours
    of your Lord would you deny?
*/

#include <bits/stdc++.h>

using namespace std;

namespace myheap
{
    template<typename T>
    bool cmp(T x, T y)
    {
        return x < y; // max_heap
    }
    template<typename T>
    void heapify(int i, vector<T> &v, int heap_size)
    {
        int l = 2*i;
        int r = l+1, largest = i;
        if(l > heap_size) return;
        if(cmp(v[i], v[l])) largest = l;
        if(r <= heap_size and cmp(v[largest] ,v[r])) largest = r;
        swap(v[largest], v[i]);
        if(i != largest) heapify(largest, v, heap_size);
    }
    template<typename T>
    void build_heap(vector<T> &v, int heap_size)
    {
        for(int i = v.size()-1; i ; i--)
        {
            heapify(i,v,heap_size);
        }
    }
    template<typename T>
    void heap_sort(vector<T> &v, int heap_size)
    {
        build_heap(v, heap_size);
        int last = v.size()-1;
        while(heap_size)
        {
            swap(v[1], v[heap_size]);
            heapify(1,v,--heap_size);
        }
    }
    template<typename T>
    T heap_top(vector<T> &v, int heap_size)
    {
        return v[1];
    }

    template<typename T>
    T extract_top(vector<T> &v, int &heap_size)
    {
        T ret = v[1];
        swap(v[1],v[heap_size]);
        heap_size--;
        v.pop_back();
        if(heap_size)
        {
            heapify(1,v,heap_size);
        }
        return ret;
    }
    template<typename T>
    void insert(vector<T> &v, T val, int &heap_size)
    {
        v.push_back(val);
        heap_size++;
        int i = v.size()-1;
        while(i > 1)
        {
            if(cmp(v[i/2], v[i]))
            {
                swap(v[i], v[i/2]);
                i /= 2;
            }
            else break;
        }
    }
    template<typename T>
    void increase_key(vector<T> &v, int pos, int amount)
    {
        v[pos] += amount;
        heapify(pos, v, v.size()-1);
        while(pos > 1)
        {
            if(cmp(v[pos], v[pos]/2))
            {
                swap(v[pos], v[pos/2]);
                pos /= 2;
            }
            else break;
        }
    }
    template<typename T>
    void decrease_key(vector<T> &v, int pos, int amount)
    {
        increase_key(v,pos,-amount);
    }
}
