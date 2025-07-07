// Recursive mutex
// 0. Same thread can lock same mutex multiple times using recursive mutex.
// 1. if thread t1 acquires same mutex 10 times recursively than it will also unlock the same mutex 10 times to release all the locks



#include<bits/stdc++.h>
using namespace std;

recursive_mutex m;


void f(int& n1, int& cnt){
    if(cnt==0) return;
    m.lock();
        cout<<"thread"<<n1<<" cnt = "<<cnt<<endl;
        cnt--;
        f(n1, cnt);
    m.unlock();
}

int main(){
    int n1 = 1, n2 = 2, cnt1 = 10, cnt2 = 10;
    thread t1(f, ref(n1), ref(cnt1));
    thread t2(f, ref(n2), ref(cnt2));

    t1.join();
    t2.join();

    return 0;
}