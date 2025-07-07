//1. if launch is async than a separate thread will be created and will work asynchronously
//2. if launch is deferred than when the future.get() exe. the f() is executed. So there is no 2 threads created here !
#include<bits/stdc++.h>

using namespace std;

int f(){

    cout<<this_thread::get_id()<<endl;

    int sum = 0;

    for(int i=0;i<=10;i++){
        sum+=i;
    }

    return sum;
}


int main(){

    future<int> ans = async(launch::async, f);

    cout<<this_thread::get_id()<<endl;

    cout<<ans.get();

    return 0;
}