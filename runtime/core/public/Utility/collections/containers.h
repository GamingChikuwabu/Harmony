#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <stack>
#include <queue>
#include <gc_cpp.h>
#include <gc_allocator.h>


// std::vector
template<class T>
using HMArray = std::vector<T, gc_allocator<T>>;

// std::list
template<class T>
using HMList = std::list<T, gc_allocator<T>>;

// std::map
template<class Key, class T>
using HMMap = std::map<Key, T, std::less<Key>, gc_allocator<std::pair<const Key, T>>>;

// std::set
template<class Key>
using HMSet = std::set<Key, std::less<Key>, gc_allocator<Key>>;

// std::unordered_map
template<class Key, class T>
using HMUnorderedMap = std::unordered_map<Key, T, std::hash<Key>, std::equal_to<Key>, gc_allocator<std::pair<const Key, T>>>;

// std::unordered_set
template<class Key>
using HMUnorderedSet = std::unordered_set<Key, std::hash<Key>, std::equal_to<Key>, gc_allocator<Key>>;

// std::deque
template<class T>
using HMDeque = std::deque<T, gc_allocator<T>>;

// std::stack
template<class T, class Container = HMDeque<T>>
using HMStack = std::stack<T, Container>;

// std::queue
template<class T, class Container = HMDeque<T>>
using HMQueue = std::queue<T, Container>;

// std::priority_queue
template<class T, class Container = HMDeque<T>, class Compare = std::less<typename Container::value_type>>
using HMPriorityQueue = std::priority_queue<T, Container, Compare>;