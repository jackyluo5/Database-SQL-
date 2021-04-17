#ifndef PAIR_H
#define PAIR_H
#include <iostream>
#include <string>
using namespace std;

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){
        key = k;
        value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
        outs<<print_me.key<<"|"<<print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key == rhs.key){
            return true;
        }
        return false;
    }
    friend bool operator != (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key != rhs.key){
            return true;
        }
        return false;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key < rhs.key){
            return true;
        }
        return false;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key > rhs.key){
            return true;
        }
        return false;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key <= rhs.key){
            return true;
        }
        return false;
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key >= rhs.key){
            return true;
        }
        return false;
    }
    Pair<K, V> operator += (const Pair<K, V>& rhs){
        assert(key == rhs.key);
        value = rhs.value;
        return *this;
    }
};


#endif // PAIR_H
