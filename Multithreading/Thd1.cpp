// TOPIC: Introduction to thread in c++ (c++11)

// QUESTIONS
// 1. What do you understand by thread and give one example in C++?

// ANSWER
// Threads are smallest unit of execution in a process / Threads are created within a process within a single address space.
// 
// 0. In evey application there is a default thread which is main(), in side this we create other threads.
// 1. A thread is also known as lightweight process. Idea is achieve parallelism by dividing a process into multiple threads. 
//    For example:
//    (a) The browser has multiple tabs that can be different threads. 
//    (b) MS Word must be using multiple threads, one thread to format the text, another thread to process inputs (spell checker)
//    (c) Visual Studio code editor would be using threading for auto completing the code. (Intellicence)

// Task - REQUIREMENT
// Find the addition of all odd and even number from 1 to 10 

// Key Takeaway
// - Thread copies all the arg by def. Generally passing to thread as ptr, val is recommended. But if passing as ref. (t2 in below code) than wrap the var. in ref(n).
// - thread.join() makes the main thd wait for a child thread to finish work. This is to make sure main prog. doesn't end while thread is running.


#include<bits/stdc++.h>
using namespace std;

void oddsum(int* sodd, int n){
    for(int i=1;i<=n;i++){
        if((i&1)==1){
            *sodd+=i;
        }
    }
}

void evensum(int* seven, int& n){
    for(int i=1;i<=n;i++){
        if((i&1)==0){
            *seven+=i;
        }
    }
}

int main(){

    int n = 10;
    int sodd = 0;
    int seven = 0;
    thread t1(oddsum, &sodd, n);
    thread t2(evensum, &seven, ref(n));

    t1.join(); // main thd stops here 
    cout<<sodd<<endl;
    t2.join(); // main thd stops here
    cout<<seven<<endl;

    return 0;
}

// Thread calling function with a return type inside a lambda
#include<bits/stdc++.h>
using namespace std;

int s1 = 0, s2 = 0;

int oddsum(int n){

    for(int i=1;i<=n;i++){
        if(i%2==1){
            s1+=i;
        }
    }

    return s1;

}

int evensum(int n){

    for(int i=1;i<=n;i++){
        if(i%2==0){
            s2+=i;
        }
    }

    return s2;
}

int main(){

    int oddans, evenans, n = 10;
    thread t1([&oddans,n](){ oddans = oddsum(n);});
    thread t2([&evenans,n](){evenans = evensum(n);});

    t1.join();
    t2.join();

    cout<<oddans<<endl;
    cout<<evenans<<endl;

    return 0;
}
