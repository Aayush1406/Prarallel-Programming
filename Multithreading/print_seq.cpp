#include<bits/stdc++.h>

using namespace std;

int cnt = 1;
int step = 1;
mutex m;
condition_variable cv;
void f1(int n){
    while(true){
    unique_lock<mutex> lock(m);

    cv.wait(lock,[](){
        return (step==1||(cnt>10));
    });
    if(cnt>10){
        cv.notify_all();
        lock.unlock();
        break;
    }
    cout<<"T"<<n<<" "<<cnt<<endl;
    cnt++;
    step=2;
    cv.notify_all();
}
}

void f2(int n){
    while(true){
    unique_lock<mutex> lock(m);
    cv.wait(lock,[](){
        return (step==2||(cnt>10));
    });
    if(cnt>10){
        cv.notify_all();
        lock.unlock();
        break;
    }
    cout<<"T"<<n<<" "<<cnt<<endl;
    cnt++;
    step=3;
    cv.notify_all();
}
}

void f3(int n){
    while(true){
    unique_lock<mutex> lock(m);
    cv.wait(lock,[](){
        return (step==3||cnt>10);
    });

    if(cnt>10){
        cv.notify_all();
        lock.unlock();
        break;
    }
    cout<<"T"<<n<<" "<<cnt<<endl;
    cnt++;
    step=1;
    cv.notify_all();
}
}

int main(){

    thread t1(f1, 1);
    thread t2(f2, 2);
    thread t3(f3, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}