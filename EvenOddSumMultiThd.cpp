// Task : Declare 2 threads executing 2 fun OddSum and EvenSum independently.
// give threads their local variables oddSum and evenSum and pass them as a ref to the above fun.
// any odd number will have 1st bit as 1 so num&1==1 will be odd and num&1==0 will be even.

#include<iostream>
#include<chrono>
#include<thread>

using namespace std;
using namespace chrono;



 void findOdd(unsigned long long start, unsigned long long end, unsigned long long *sumodd){

    for(unsigned long long i = start; i<=end;i++){
        if((i&1)==1){
            *sumodd+=i;
        }
    }

    
}

 void findEven(unsigned long long start, unsigned long long end, unsigned long long *sumeven){
    
    for(unsigned long long i=start; i<=end;i++){
        if((i&1)==0){
            *sumeven+=i;
        }
    }

}

int main(){

    unsigned long long start = 0;
    unsigned long long end = 190000000;

    unsigned long long sumodd = 0;
    unsigned long long sumeven = 0;

    auto startTime = high_resolution_clock::now();

    thread t1(findOdd,start,end,&sumodd);

    thread t2(findEven, start, end,&sumeven);

    // make the parent thread wait until the child threads finishes
    t1.join();

    t2.join();

    auto endTime = high_resolution_clock::now();


    auto duration = duration_cast<milliseconds>(endTime - startTime);

    cout<<duration.count()<<endl;
    cout<<sumodd<<endl;
    cout<<sumeven<<endl;

}