#ifndef MMAP_H
#define MMAP_H

#include <cassert>
#include "../../!includes/B+Tree/bplustree.h"
#include "../../!includes/MPair/mpair.h"
#include <iostream>

using namespace std;


template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = NULL): _it(it){}
        Iterator operator ++(int unused){
            assert(_it != NULL);
            _it++;
            return _it;
        }
        Iterator operator ++(){
            assert(_it != NULL);
            ++_it;
            return _it;
        }
        MPair<K, V> operator *(){
            assert(_it != NULL);
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return (lhs._it == rhs._it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return (lhs._it != rhs._it);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

    //  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

    //  Operations:
    bool contains(const K& key);
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;

};
template <typename K, typename V>
MMap<K, V>::MMap(): mmap()
{
}

//  Iterators
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin(){
    //return iterator at beginning
    return mmap.begin();
}
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end(){
    //return iterator at end
    return mmap.end();
}


//  Capacity
template <typename K, typename V>
int MMap<K, V>::size() const{
    mmap.size();
}
template <typename K, typename V>
bool MMap<K, V>::empty() const{
    mmap.empty();
}


//  Element Access
template <typename K, typename V>
const vector<V>& MMap<K, V>::operator[](const K& key) const{
    MPair<K, V> temp(key, 0);

    return mmap.get_existing(temp).value_list;
}
template <typename K, typename V>
vector<V>& MMap<K, V>::operator[](const K& key){
    MPair<K, V> temp(key);

    if(!mmap.contains(temp)){
        mmap.insert(temp);
    }
    return mmap.get(temp).value_list;
}

//  Modifiers
template <typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v){
    MPair<K, V> temp(k,v);
    mmap.insert(temp);
}
template <typename K, typename V>
void MMap<K, V>::erase(const K& key){
    mmap.remove(key);
}
template <typename K, typename V>
void MMap<K, V>::clear(){
    mmap.clear_tree();
}

//  Operations:
template <typename K, typename V>
bool MMap<K, V>::contains(const K& key){
    MPair<K, V> temp(key);
    bool result;
    result = mmap.contains(temp.key);
    return result;
}
template <typename K, typename V>
bool MMap<K, V>::contains(const K& key) const {
    MPair<K, V> temp(key);
    bool result;
    result = mmap.contains(temp.key);
    return result;
}
template <typename K, typename V>
vector<V> &MMap<K, V>::get(const K& key){
    MPair<K,V> temp(key);

    if(!mmap.contains(temp)){
        mmap.insert(temp);
    }
    mmap.get(temp).value_list;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key){
    //returns Iterator at Key
    mmap.find(key);
}


#endif // MMAP_H
