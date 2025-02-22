//Deadlock - when 2 or more processes are waiting for the resouces occupied by each other than deadlock occurs.
// std::lock() in c++11
// It is used to lock multiple mutex at the same time.

// Important:
//syntax---> std::lock(m1,m2,m3,m4.....);
// 1. All the mutexes are locked via seq of calls to lock().
// 2. Order of locking is not defined (it will try to lock provided mutex in any order and ensure that there is no deadlock) 
// 3. It is a blocking call

 I
// [Example:0] -- No deadlock.
//     Thread 1                    Thread 2
//     std::lock(m1,m2);           std::lock(m1,m2);

//So basically it works atomically. If thd1 will occupy m1 and m2 at same time. If m2 is locked by T2 than T1 will wait and let T2 proceed first
// [Example:1] -- No deadlock. 

//     Thread 1                    Thread 2
//     std::lock(m1, m2);          std::lock(m2, m1);

// [Example:2] -- No deadlock. 

//     Thread 1                    Thread 2
//     std::lock(m1, m2, m3, m4);  std::lock(m3, m4);
//                                 std::lock(m1, m2);

// [Example:3] -- Yes, the below can deadlock. 

//     Thread 1                    Thread 2
//     std::lock(m1,m2);           std::lock(m3,m4);
//     std::lock(m3,m4);           std::lock(m1,m2);
#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
using namespace chrono;
using namespace this_thread;
mutex m1;
mutex m2;
int cnt = 0;

void fun1(){
    lock(m1,m2);
    sleep_for(seconds(1));

    cout<<"Critical section of 1"<<endl;
    m1.unlock();
    m2.unlock();
}

void fun2(){
    lock(m2,m1);
    sleep_for(seconds(1));
    cout<<"Critical section of 2"<<endl;
    m2.unlock();
    m1.unlock();
}

int main(){

    thread t1(fun1);

    thread t2(fun2);

    t1.join();

    t2.join();

    cout<<"Here"<<endl;
    // cout<<cnt;
    return 0;

}