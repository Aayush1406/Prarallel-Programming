// TOPIC: std::mutex::try_lock() On Mutex In C++11 Threading

// 0. try_lock() Tries to lock the mutex, on successful lock acquisition returns true otherwise returns false.
// 1. If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking.

// key takeaway - the f(), m, and ans are global things but inside f() the var i is private in each thread stack
// - If t1 is accessing CS and t2 comes than it might not able to access CS and does not wait while i counter keeps incrementing.
// - That is why we do not get 2x the ans everytime
// - if we use lock instead than t2 will wait until it gets the lock. In that case we get 2x the ans.
#include<bits/stdc++.h>

using namespace std;

mutex m;

int ans = 0;
void f(){
    for(int i=1;i<=10000;i++){
        if(m.try_lock()){
            ans++;
            m.unlock();
        }
    }
}
int main(){

    // int ans = 0;
    thread t1(f);
    thread t2(f);

    t1.join();
    t2.join();

    cout<<ans;
    return 0;
}
