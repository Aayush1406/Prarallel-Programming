// 1. promise - used to send the value to the worker thd and set the values in worker thd.
// 2. future - used to get the values from the promise, wait for the promise / will get blocked until promise set the value in worker and returns it to the future.get().


#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
#include<future>
using namespace std;

typedef  unsigned long long ull;

void findOddSum(promise<ull>*xpromis,ull start, ull end){
    ull OddSum = 0;

    for(ull i=start;i<=end;i++){
        if((i&1)==1){
            OddSum+=i;
        }
    }
    xpromis->set_value(OddSum);
}

int main(){

    ull start = 0;
    ull end = 190000000;

    promise<ull> xpromise;
    future<ull> xfuture = xpromise.get_future();

    thread t1(findOddSum,&xpromise,start,end);

    cout<<"Waiting for the future";

    cout<<"Odd Sum = "<<xfuture.get()<<endl;
    this_thread::sleep_for(chrono::seconds(5));
    t1.join();

    return 0;
}