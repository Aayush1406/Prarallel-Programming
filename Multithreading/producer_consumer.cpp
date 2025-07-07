#include<bits/stdc++.h>

using namespace std;

mutex m;
deque<int> q;
condition_variable cv;
bool done = false;
int maxsize = 2;
void producer(){

    for(int i=0;i<10;i++){
        unique_lock<mutex> lock(m);
        cv.wait(lock,[](){if(q.size()<maxsize)return true; else return false;});
            cout<<"Produced = "<<i<<endl;
            chrono::seconds(1);
            q.push_back(i);
        lock.unlock();
        cv.notify_one();
    }
    unique_lock<mutex> lock(m);
    done = true;

}

void consumer(){

    while(true){
        unique_lock<mutex> lock(m);
        if(done==true) break;
        cv.wait(lock,[](){if(q.empty()==false)return true; else return false;});
        cout<<"Consumed = "<<q.back()<<endl;
        chrono::seconds(1);
        q.pop_back();
        lock.unlock();
        cv.notify_one();
    }
}

int main(){

    thread p(producer);
    thread c(consumer);

    p.join();
    c.join();

    return 0;
}