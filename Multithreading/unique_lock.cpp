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