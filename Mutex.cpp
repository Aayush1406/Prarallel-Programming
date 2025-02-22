// Race condition: when two or more processes or thds try to change the same data / shared resource at a same time.

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;


int counter = 0;
mutex m;
void run(){
    for(int i=0;i<5;i++){
        m.lock();
        counter = counter + 1; //This is a Critical Section (shared res) that all the threads are accessing and modifying here.
        m.unlock();
    }
}
int main(){

    thread t1(run);
    thread t2(run);
    thread t3(run);
    thread t4(run);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout<<counter;
    return 0;
}