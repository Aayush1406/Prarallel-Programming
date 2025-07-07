#include<bits/stdc++.h>

using namespace std;
// 1. it is a wrapper.
mutex m;

int buffer = 0;

void task(int num){

    unique_lock<mutex> lock(m);
    for(int i=1;i<=num;i++){
        buffer++;
    }

}


void task2(int n){
    unique_lock<mutex> lock(m, defer_lock); // does not call lock on the mutex, because of the defer_lock !
    /*
    
    Some Code part

    */

    lock.lock();
    for(int i=0;i<n;i++){
        buffer++;
    }
}


int main(){

    thread t1(task2, 10);
    thread t2(task2, 10);

    t1.join();
    t2.join();

    cout<<buffer<<endl;

    return 0;

}

// example: 2

#include<bits/stdc++.h>
using namespace std;

int cnt = 0;
mutex m;
void f(){

    for(int i=0;i<100;i++){
    unique_lock<mutex> lock;
        cnt++;
    } // lock gets unlocked here !
}

int main(){

    thread t1([](){f();});
    thread t2([](){f();});
    thread t3([](){f();});
    thread t4([](){f();});
    thread t5([](){f();});

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    cout<<cnt;

    return 0;
}
