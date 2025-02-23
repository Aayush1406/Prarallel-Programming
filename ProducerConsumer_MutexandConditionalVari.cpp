#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<condition_variable>
using namespace std;

typedef unsigned long long ull;
class CircularBuffer{
  
    private:
        vector<ull> buffer; 
        ull in;
        ull out;
        ull itemcnt;
        ull bufsize;


    public:
    CircularBuffer(int size, int itmcnt){
        bufsize = size;
        buffer.resize(bufsize);
        itemcnt = itmcnt;
        in = 0;
        out = 0;
    }

    ull getItemCnt(){
        return itemcnt;
    }
    ull getIn(){
        return in;
    }
    ull getOut(){
        return out;
    }
    ull getBuffSize(){
        return bufsize;
    }
    void setIn(ull in){
        this->in = in;
    }
    void setOut(ull out){
        this->out = out;
    }
    vector<ull>& getVector(){
        return buffer;
    }
};
mutex mtx;
condition_variable cv_prod, cv_cons;

void producer(CircularBuffer* cb){
    int itemcnt = cb->getItemCnt();
    int in = cb->getIn();
    int out = cb->getOut();
    int buffsize = cb->getBuffSize();
    vector<ull>& buffer = cb->getVector();
    
    for(int i=0;i<=itemcnt;i++){
        unique_lock uniquelock(mtx);
        cv_prod.wait(uniquelock,[cb,buffsize](){return ((cb->getIn()+1)%buffsize==cb->getOut())?false:true;});
        buffer[in] = i;
        cout<<"Producer = "<<i<<endl;
        in = (in + 1)%buffsize;
        cb->setIn(in);
        uniquelock.unlock();
        cv_cons.notify_one();
    }
}

void consumer(CircularBuffer* cb){
    int itemcnt = cb->getItemCnt();
    int in = cb->getIn();
    int out = cb->getOut();
    int buffsize = cb->getBuffSize();
    vector<ull>& buffer = cb->getVector();
    
    for(int i=0;i<=itemcnt;i++){
        unique_lock uniquelock(mtx);
        cv_cons.wait(uniquelock, [cb](){return (cb->getIn()==cb->getOut())? false : true;});
        cout<<"Consumer = "<<buffer[out]<<endl;
        out = (out + 1)%buffsize;
        cb->setOut(out);
        uniquelock.unlock();
        cv_prod.notify_one();
    }
}

int main(){

    CircularBuffer cb(10,100);
    thread prod(producer, &cb);
    thread cons(consumer, &cb);

    prod.join();
    cons.join();

    return 0;
}