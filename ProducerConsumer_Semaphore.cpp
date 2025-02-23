#include<iostream>
#include<thread>
#include<vector>
using namespace std;

class CircularBuffer{
    private:
    int in, out, itemcnt, buffsize;
    vector<int> buffer;

    public:
    CircularBuffer(int itc, int bsize){
        in = 0;
        out = 0;
        itemcnt = itc;
        buffsize = bsize;
        buffer.resize(buffsize);
    }

    int getIn(){
        return in;
    }
    int getOut(){
        return out;

    }
    void setIn(int in){
        this->in=in;
    }

    void setOut(int out){
        this->out = out;
    }
    
    vector<int>& getBuffer(){
        return buffer;
    }

    int getItemCnt(){
        return this->itemcnt;
    }

    int getBuffSize(){
        return buffsize;
    }
};

counting_semaphore emptycnt(10), fullcnt(0);
mutex mtx;

void producer(CircularBuffer *c){
    vector<int>& buffer = c->getBuffer();
    int itemCnt = c->getItemCnt();
    int in = c->getIn();
    int out = c->getOut();
    int buffsize = c->getBuffSize();

    for(int i=0;i<=itemCnt;i++){
        emptycnt.acquire();
        mtx.lock();
        cout<<"Producing = "<<i<<endl;
        this_thread::sleep_for(chrono::seconds(1));
        buffer[in] = i;
        in = (in+1)%buffsize;
        c->setIn(in);
        mtx.unlock();
        fullcnt.release();
    }
}

void consumer(CircularBuffer* c){
    vector<int>& buffer = c->getBuffer();
    int itemCnt = c->getItemCnt();
    int in = c->getIn();
    int out = c->getOut();
    int buffsize = c->getBuffSize();

    for(int i=0;i<=itemCnt;i++){
        fullcnt.acquire();
        mtx.lock();
        this_thread::sleep_for(chrono::seconds(1));

        cout<<"Consuming = "<<buffer[out]<<endl;
        out = (out+1)%buffsize;
        c->setOut(out);
        mtx.unlock();
        emptycnt.release();
    }
}
int main(){

    CircularBuffer c(100,10);
    thread t1(producer, &c);
    thread t2(consumer, &c);

    t1.join();
    t2.join();

}