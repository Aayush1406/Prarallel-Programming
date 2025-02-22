//async : launch::async -> runs in a new thread (Eager running) . Will create a separate thread from main and run the function given in the arg
//async : launch::deferred -> the func is not executed immediately in separate thd. Insted, it is called lazily by the main thd when .get() / .wait() is invoked.
// async - usage
// 1. async - clean way to return the value from the fun.
// 2. No need to manually write join. Provides automatic thd management
#include<iostream>
#include<thread>
#include<future>

using namespace std;

typedef unsigned long long ull;

ull findOddSum(ull start, ull end){
    ull sum = 0;
    for(ull i=start;i<=end;i++){
        if((i&1)==1){
            sum = sum + i;
        }
    }

    cout<<"Async function thread id = "<<this_thread::get_id()<<endl;
    return sum;
}

int main(){

    ull start = 0;
    ull end = 1900000000;

    cout<<"Main thread function id = "<<this_thread::get_id()<<endl;
    future<ull> fut = async(launch::deferred,findOddSum,start,end);

    cout<<"Result = "<<fut.get()<<endl;
    return 0;
}