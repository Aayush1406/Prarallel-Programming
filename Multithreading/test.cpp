#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>
#include <vector>
using namespace std;

class ZeroEvenOdd {
private:
    int n;
    int ind_cnt;
    int num_cnt;
    mutex m;
    condition_variable cv;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        num_cnt = 1;
        ind_cnt = 1;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(true){
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this](){
                if(ind_cnt%2==1||num_cnt>n)return true;
                else return false;
            });
            if(num_cnt>n){
                cv.notify_all();
                break;
            }
            printNumber(0);
            ind_cnt++;
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while(true){
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this](){
                if((ind_cnt%2==0 && ind_cnt%4==0)||num_cnt>n) return true;
                else return false;
            });
            if(num_cnt>n){
                cv.notify_all();
                break;
            }
            printNumber(num_cnt);
            num_cnt++;
            ind_cnt++;
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while(true){
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this](){
                if(ind_cnt%2==0||num_cnt>n) return true;
                else return false;
            });
            if(num_cnt>n){
                cv.notify_all();
                break;
            }
            printNumber(num_cnt);
            num_cnt++;
            ind_cnt++;
            cv.notify_all();
        }  
    }
};

// Test function
int main() {
    ZeroEvenOdd zeo(5);
    
    auto printNumber = [](int x) {
        cout << x << " ";
    };
    
    vector<thread> threads;
    threads.emplace_back(&ZeroEvenOdd::zero, &zeo, printNumber);
    threads.emplace_back(&ZeroEvenOdd::even, &zeo, printNumber);
    threads.emplace_back(&ZeroEvenOdd::odd, &zeo, printNumber);
    
    for(auto& t : threads) {
        t.join();
    }
    
    cout << endl;
    return 0;
}