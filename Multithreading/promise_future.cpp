#include<bits/stdc++.h>

using namespace std;


void fun(promise<int>&& p){

    int sum = 0;
    for(int i=1;i<=10;i++){
        sum+=i;
    }

    p.set_value(sum);
}

int main(){


    promise<int> p;
    future<int> f = p.get_future();
    thread t1(fun,move(p));

    cout<<f.get()<<endl;
    t1.join();
    return 0;
}