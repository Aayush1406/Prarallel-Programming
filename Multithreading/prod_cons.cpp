#include<bits/stdc++.h>

using namespace std;

binary_semaphore prod_sem{1}, con_sem{0};
int arr[10];
void producer(){
    while(true){
        prod_sem.acquire();
        for(int i=0;i<10;i++){
            arr[i] = i*i;
            cout<<"Produced = "<<arr[i]<<endl;
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        con_sem.release();
    }
}

void consumer(){

    while(true){
        con_sem.acquire();
        for(int i=0;i<10;i++){
            cout<<"Consumed = "<<arr[i]<<endl;
            this_thread::sleep_for(chrono::milliseconds(200));
            

        }        
        prod_sem.release();
    }
}

int main(){

    thread p(producer);
    thread c(consumer);

    p.join();
    c.join();

    return 0;
}