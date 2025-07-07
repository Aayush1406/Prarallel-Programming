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

#include<bits/stdc++.h>
using namespace std;

class Test{

    public:
        bool fun(){
            cout<<"Hello Aayush !";

            return true;
        }

};


int main(){

    Test t;
    bool ans;
    
    thread t1([&t, &ans](){ans = t.fun();}); //imp to pass t as ref else pass by val is treated as const in lambda so t will also be const so fun() has to be const also !
    t1.join();
    cout<<ans<<endl;

    return 0;
}
