#ifndef MAP_BPT_H
#define MAP_BPT_H
#include <cassert>
//#include "../../!includes/BTree/btree.h"
#include "../../!includes/B+Tree/bplustree.h"

#include "../../!includes/Pair/pair.h"
#include <iostream>
using namespace std;


template <typename K, typename V>
class Map_BPT
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;

    class Iterator{
    public:
        friend class Map_BPT;
        Iterator(typename map_base::Iterator it);
        Iterator operator ++(int unused){
            assert(_it != NULL);
            _it++;
        }
        Iterator operator ++(){
            assert(_it != NULL);
            _it++;
        }
        Pair<K, V> operator *(){
            assert(this != NULL);
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

    Map_BPT();
    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    V& operator[](const K& key);
    const V& operator[](const K& key) const;
    V& at(const K& key);
    const V& at(const K& key) const;


    //  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

    //  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target);
    bool contains(const Pair<K, V>& target) const;

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map_BPT<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }

private:
    int key_count;
    BPlusTree<Pair<K, V> > map;

};

template <typename K, typename V>
Map_BPT<K, V>::Map_BPT(): map(){
    key_count = 0;
}

//  Capacity
template <typename K, typename V>
int Map_BPT<K, V>::size() const{
    map.size();
}
template <typename K, typename V>
bool Map_BPT<K, V>::empty() const{
    map.empty();
}

//Iterators
template <typename K, typename V>
typename Map_BPT<K, V>::Iterator Map_BPT<K, V>::begin(){
    map.begin();
}
template <typename K, typename V>
typename Map_BPT<K, V>::Iterator Map_BPT<K, V>::end(){
    map.end();
}

//element access
template <typename K, typename V>
V& Map_BPT<K, V>::operator[](const K& key){
    Pair<K, V> temp(key, 0);

    if(!map.contains(temp)){
        map.insert(temp);
    }
    return map.get(temp).value;
}

template <typename K, typename V>
const V& Map_BPT<K, V>::operator[](const K& key) const{
    Pair<K, V> temp(key, 0);


    return map.get_existing(temp).value;
}
template <typename K, typename V>
V& Map_BPT<K, V>::at(const K& key){
    Pair<K, V> temp(key, 0);

    if(!map.contains(temp)){
        map.insert(temp);
    }
    return map.get(temp).value;
}
template <typename K, typename V>
const V& Map_BPT<K, V>::at(const K& key) const{
    Pair<K, V> temp(key, 0);

    return map.get_existing(temp).value;
}

//modifiers
template <typename K, typename V>
void Map_BPT<K, V>::insert(const K& k, const V& v){
    Pair<K, V> temp(k, v);
    map.insert(temp);
}
template <typename K, typename V>
void Map_BPT<K, V>::erase(const K& key){
    map.remove(key);
}
template <typename K, typename V>
void Map_BPT<K, V>::clear(){
    map.clear_tree();
}
template <typename K, typename V>
V Map_BPT<K, V>::get(const K& key){
    Pair<K, V> temp(key, 0);

    if(!map.contains(temp)){
        map.insert(temp);
    }
    return map.get(temp).value;
}

//  Operations:
template <typename K, typename V>
typename Map_BPT<K, V>::Iterator Map_BPT<K, V>::find(const K& key){
    map.find(key);
}
template <typename K, typename V>
bool Map_BPT<K, V>::contains(const Pair<K, V>& target){
    bool result = false;
    result = map.contains(target.key);
    return result;
}
template <typename K, typename V>
bool Map_BPT<K, V>::contains(const Pair<K, V>& target) const{
    bool result = false;
    result = map.contains(target.key);
    return result;
}


#endif // MAP_BPT_H
