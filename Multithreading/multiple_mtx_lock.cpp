// Task - increment values of x and y in incrementXY() and than consume that incremented value by consumerXY()
// use 2 mutexes m1 and m2
// try_lock(m1, m2) returns -1 when both the mutexes are available.

#include<bits/stdc++.h>

using namespace std;

mutex m1;
mutex m2;
int x = 0, y = 0;

void doSomeWorkForSeconds(int seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds)); }
void incrementXY(int&n , mutex& m){
    
    for(int i=1;i<=5;i++){
        m.lock();
            n++;
        m.unlock();
    doSomeWorkForSeconds(10);

    }
}

void consumeXY(){

    int cnt = 5;
    int sum = 0;

    while(true){

        if(try_lock(m1,m2)==-1){
            if(x!=0 && y!=0){
                sum+= x+y;
                x = 0;
                y = 0;
                cout<<sum<<endl;
                cnt--;
            }
            m1.unlock();
            m2.unlock();
            if(cnt==0) break;
        }

    }


}

int main(){

    thread t1(incrementXY, ref(x), ref(m1));
    thread t2(incrementXY, ref(y), ref(m2));
    thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
