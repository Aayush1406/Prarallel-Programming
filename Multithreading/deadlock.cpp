#include<bits/stdc++.h>

using namespace std;

mutex m1;
mutex m2;

void f1(){
    
    m1.lock();
    m2.lock();
    cout<<"Thread 1"<<endl;
    m2.unlock();
    m1.unlock();
}

void f2(){

    m2.lock();
    m1.lock();
    cout<<"Thread 2"<<endl;
    m1.unlock();
    m2.unlock();
}

int main(){

    thread t1(f1);
    thread t2(f2);

    t1.join();
    t2.join();

    return 0;

}