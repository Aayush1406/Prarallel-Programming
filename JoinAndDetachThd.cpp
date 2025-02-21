#include<iostream>
#include<thread>
#include<chrono>

using namespace std;
using namespace this_thread;

void run(int *count){
    while(*count>0){
        (*count)--; // imp to keep the *count in the ()!
        cout<<"Aayush"<<endl;
    }

}


int main(){
    int count = 10;
    cout<<"Before main"<<endl;
    thread t1 (run,&count);
    // t1.join();
    t1.detach(); // used to detach newly created thd from the parent thd.
    // if(t1.joinable()){ //if your code is too big and you are not sure whether you should write join or not than you can check it using joinable() fun.
    //     t1.join();
    // }
    // sleep_for(chrono::seconds(0)); // here the detached main / parent thd will wait before exec next line.

    cout<<"After main"<<endl;

    return 0;
}