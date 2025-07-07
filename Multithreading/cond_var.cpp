#include<bits/stdc++.h>

using namespace std;

condition_variable cv;
mutex m;
long bal = 0;

void addMoney(int amt){

    unique_lock<mutex> lock(m);
    bal+= amt;
    cv.notify_one();
}

void withdrawMoney(int amt){
    unique_lock<mutex> lock(m);
    cv.wait(lock, []{if(bal==0)return false; else return true;});
    if(amt>bal){
        cout<<"Not enough bal"<<endl;
    }else{
        bal-= amt;
    }
}

int main(){

    thread t1(withdrawMoney, 100);
    thread t2(addMoney, 500);

    t1.join();
    t2.join();

    cout<<"final bal = "<<bal<<endl;

    return 0;
}

// example - Semaphore based sol

#include<bits/stdc++.h>
using namespace std;


binary_semaphore add_sem{1};
binary_semaphore with_sem{0};
long bal = 0;

void addMoney(int amt){

    add_sem.acquire();
    bal+=amt;
    cout<<"Amt deposited = "<<amt<<" Total bal = "<<bal<<endl;
    with_sem.release();
}

void withdrawMoney(int amt){

    with_sem.acquire();
    bal-=amt;
    cout<<"Amt withdrawn = "<<amt<<" Total bal = "<<bal<<endl;
    add_sem.release();
}

int main(){

    return 0;
}
