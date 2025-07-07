// TOPIC: Mutex In C++ Threading | Why Use Mutex | What Is Race Condition And How To Solve It? | What Is Critical Section

// Mutex: Mutual Exclusion

// RACE CONDITION:
// 0. Race condition: multiple threads try to read / write shared data at same time.
// 1. Critical section: a shared piece of code where race cond is possible

// MUTEX: A lock that makes sure only 1 thread can enter critical section at a time.
// 0. Mutex is used to avoid race condition.
// 1. We use lock() , unlock() on mutex to avoid race condition.
// 2. m.lock() is a blocking call, meaning until thread gets the lock it will be waiting.
#include<bits/stdc++.h>

using namespace std;


int amt = 100;
mutex m;

void f(){
    m.lock();
    amt++; // Critical Section
    m.unlock();
}

int main(){

    thread t1(f);
    thread t2(f);

    t1.join();
    t2.join();

    cout<<amt;
    return 0;
}