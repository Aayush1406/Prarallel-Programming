// TOPIC: Different Types Of Thread Creation And Calling.
// There are 5 different types of creating threads and calling callable in threads.

// Key Takeaway
// lambda function - auto fun = [](int x){/* Body */}; thread t1(fun, 10);
// syntax for calling a fun in class from a thread - Test obj; thread t1(&Test::fun, &obj, 10);

#include<bits/stdc++.h>

using namespace std;

// 1. func ptr
void f(int* n){
    while(*n>0){
        cout<<*n<<endl;
        *n = *n-1;
    }
}

int main(){
    int n = 10;
    thread t(f, &n);
    t.join();
    return 0;
}

// 2. Lambda function

int main(){

    auto fun = [](int x){
        while(x>0){
            cout<<x<<endl;
            x--;
        }
    };

    thread t(fun, 5);

    t.join();

    return 0;
}

// 3. non static member function

class Test{

    public:
        void f(int x){
            cout<<"f is running = "<<x<<endl;
        }

};

int main(){

    Test t;

    thread t1(&Test::f, &t, 10);
    t1.join();

    return 0;
}