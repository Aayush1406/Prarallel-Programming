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

// Bounded buffer with fixed cap in queue
#include<bits/stdc++.h>
using namespace std;

class Test{
    
    private:
        mutex m;
        int cap;
        queue<int> q;
        int n;
        condition_variable cv;

    public:
    Test(int cap = 5,int n = 30){
        this->cap = cap;
        this->n = n;
    }

    void producer(){

        while(true){
            
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this](){if(q.size()<cap||(n==0))return true; else return false;});
            if(n==0){
                cv.notify_all();
                break;
            }
            int num = rand();
            q.push(num);
            cout<<"Produced = "<<num<<endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            n--;
            cv.notify_all();
        }
    }

    void consumer(){

        while(true){
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this](){if(q.size()!=0||n==0)return true; else return false;});
            if(n==0){
                cv.notify_all();
                break;
            }
            int num = q.front();
            cout<<"Consumed = "<<num<<endl;
            this_thread::sleep_for(std::chrono::seconds(1));

            q.pop();
            n--;
            cv.notify_all();

        }

    }
};


int main(){

    Test o;
    thread t1([&o](){o.producer();});
    thread t2([&o](){o.consumer();});

    t1.join();
    t2.join();

    return 0;
}
