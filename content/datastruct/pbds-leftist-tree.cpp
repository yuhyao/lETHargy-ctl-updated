#include<ext/pb_ds/priority_queue.hpp> 
using namespace __gnu_pbds;
template<class T>
using Heap = __gnu_pbds::priority_queue<T, greater<T>, binomial_heap_tag>; // smallest value at the top.
// Use $a.join(b)$ to merge heap $b$ to heap $a$. After merging, $b$ will be empty.
