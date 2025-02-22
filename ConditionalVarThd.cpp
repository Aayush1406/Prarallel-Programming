// Condition Variable used for
// 1. Notify other thds.
// 2. Waiting for some condition.
// It allows running thd to wait on some condition and once those condition are met the waiting thd is notified using
// - notify_one() or notify_all()
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

mutex m;
condition_variable cv;
int bal = 0;

void addMoney(int money){
    m.lock();
    bal = bal + money;
    m.unlock();
    cv.notify_one();
}

void withdrawMoney(int money){
    unique_lock<mutex> uniquelock(m);
    cv.wait(uniquelock, []{ return (bal==0)? false : true;}); // cv.wait(lock, (conditional lambda fun) []{if true than proceed below})
    if(bal>=money)
    bal = bal - money;
    else
    cout<<"Not enough money";
    uniquelock.unlock();
}


int main(){

    int addm  = 1000;
    int widm = 100;
    thread t1(addMoney, addm);

    thread t2 (withdrawMoney, widm);

    t1.join();

    t2.join();

    cout<<bal;
}