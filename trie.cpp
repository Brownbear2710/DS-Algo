/*
    So, which of the favours
    of your Lord would you deny?
*/

#include <iostream>
#include <string>
#include <vector>

#ifdef ADIB_PC
#include "dbg.h"
#else
#define dbg(...){}
#endif

using namespace std;
using LL = long long;

template<size_t _alphabet_size, char _first_alphabet>
class trie
{
public:
    struct node
    {
        bool end_point = false;
        int cnt = 0;
        vector<node *> next;
        node() {next.resize(_alphabet_size, nullptr);}
        ~node(){next.clear();}
    };
    node * root = nullptr;
    ~trie(){clear(root);}
private:
    void delete_string(string &s, node * &curr, int i = 0)
    {
        if(i == s.size()+1) return;
        if(i < s.size())
        {
            delete_string(s, curr->next[s[i] - _first_alphabet], i+1);
            curr->cnt--;
        }
        if(curr->cnt == 0)
        {
            delete curr;
            curr = nullptr;
        }
        else if(i == s.size()) curr->end_point = false;
    }
    void display_with_prefix(node * curr, string &str, string &pref)
    {
        if(curr == nullptr) return;
        if(curr->end_point == true and pref.size() <= str.size()) cout << str << '\n';
        if(str.size() >= pref.size())
        {
            for(int i = 0; i < _alphabet_size; i++)
            {
                str += (char)(i+_first_alphabet);
                display_with_prefix(curr->next[i] , str, pref);
                str.pop_back();
            }
        }
        else
        {
            str += pref[str.size()];
            display_with_prefix(curr->next[str.back() - _first_alphabet], str, pref);
            str.pop_back();
        }
    }
    // void display_with_prefix(node * curr, string &str, string &pref, int &printed)
    // {
    //     if(curr == nullptr) return;
    //     if(printed == 3) return;
    //     if(curr->end_point == true and pref.size() <= str.size())
    //     {
    //         cout << str << '\n';
    //         printed++;
    //     }
    //     if(str.size() >= pref.size())
    //     {
    //         for(int i = 0; i < _alphabet_size; i++)
    //         {
    //             str += (char)(i+_first_alphabet);
    //             display_with_prefix(curr->next[i] , str, pref, printed);
    //             str.pop_back();
    //         }
    //     }
    //     else
    //     {
    //         str += pref[str.size()];
    //         display_with_prefix(curr->next[str.back() - _first_alphabet], str, pref, printed);
    //         str.pop_back();
    //     }
    // }
public:
    void insert(string s)
    {
        if(root == NULL) root =  new node();
        node * curr = root;
        int i = 0;
        while(i < s.size())
        {
            curr->cnt++;
            if(curr->next[s[i] - _first_alphabet] == nullptr) curr->next[s[i] - _first_alphabet] = new node();
            curr = curr->next[s[i] - _first_alphabet];
            i++;
        }
        curr->end_point = true;
    }
    bool search(string s)
    {
        if(s == "") return true;
        if(root == NULL) return false;
        node * curr = root;
        int i = 0;
        while(i < s.size())
        {
            if(curr->next[s[i] - _first_alphabet] == nullptr) return false;
            curr = curr->next[s[i] - _first_alphabet];
            i++;
        }
        return curr->end_point;
    }
    void display(string pref = "")
    {
        string temp;
        display_with_prefix(root, temp, pref);
        // int printed = 0;
        // display_with_prefix(root, temp, pref, printed);
    }
    int how_many(string s = "")
    {
        node * curr = root;
        int i = 0;
        while(i < s.size())
        {
            if(curr->next[s[i] - _first_alphabet] == nullptr) return 0;
            curr = curr->next[s[i] - _first_alphabet];
            i++;
        }
        return curr->cnt;
    }
    void remove(string s)
    {
        if(search(s) == false) return;
        delete_string(s, root);
    }
    void clear(node * &curr)
    {
        if(curr == nullptr) return;
        for(int i = 0; i < _alphabet_size; i++)
            clear(curr->next[i]);
        delete curr;
        curr = nullptr;
    }
};

int main()
{
    trie<26,'a'> t;
    t.insert("algorithm");
    t.insert("algo");
    t.insert("algo");
    t.insert("also");
    t.insert("next");
    // t.display("hello");
    cout << t.how_many() << '\n';
    t.display();
    cout << "-------------------------------\n";
    cout << t.how_many("n") << '\n';
    t.remove("algo");
    t.display();
    cout << "-------------------------------\n";
    t.display("algo");
    t.display("n");
    cout << t.how_many() << '\n';
    return 0;
}