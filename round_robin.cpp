#include<bits/stdc++.h>
using namespace std;
queue<int> ready_queue;

struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
    int remaining_time = 0;
    bool done = false;
};

bool found(int n){
    bool f = false;
    queue<int> temp = ready_queue;
    while (!temp.empty()){
        if(temp.front() == n)return true;
        temp.pop();
    }
    
    return f;
}

void display(process *p,int n){
    for(int i = 0; i < n; i++){
        cout<<" Process ID : "<<p[i].id<<" Arrival Time : "<<p[i].arrival_time<<" Burst Time : "<<p[i].burst_time;
        cout<<" Completion Time : "<<p[i].completion_time<<" Turn Around Time : "<<p[i].turn_around_time;
        cout<<" Waiting Time : "<<p[i].waiting_time<<endl;
    }
}

int main(){
    int n;
    cout<<" \n Enter the number of processes : ";
    cin>>n;

    process p[n];

    for(int i = 0; i < n; i++){
        p[i].id = i;
        cout<<" \n Enter Arrival Time of Process "<<i<<" : ";
        cin>>p[i].arrival_time;
        cout<<" \n Enter Burst Time of Process "<<i<<" : ";
        cin>>p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            if(p[j].arrival_time > p[j+1].arrival_time){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    
    // display(p,n);

    int time_quantum = 2;
    int timer = 0;
    int id = p[0].id;
    timer = timer + p[0].arrival_time;
    // cout<<time<<id;

    
    ready_queue.push(id);
    // cout<<ready_queue.size();
  //  cout<<id<<"\npushed\n";

	cout<<endl;
    while(!ready_queue.empty()){
        // ready_queue.pop();
        
        id = ready_queue.front();
        if(!p[id].done){
            if(p[id].remaining_time > time_quantum){
                timer = timer + time_quantum;
                p[id].remaining_time = p[id].remaining_time - time_quantum;
                //cout<<" "<<id;
		for(int i = 0; i < n; i++){
                    if((timer >= p[i].arrival_time) && (p[i].id != id)){
                        // cout<<" Found : "<<found(p[i].id)<<endl;
                        if((!p[i].done) && (!found(p[i].id))){
                            ready_queue.push(p[i].id);
                            // cout<<p[i].id<<" pushed at "<<timer<<endl;
                        }
                    }
                    
                }
                ready_queue.push(id);
                // cout<<id<<" pushed at "<<timer<<endl;
            }
            else{
                p[id].done = true;
                //cout<<id<<"completed"<<endl;
                //cout<<" "<<id;
		        timer = timer + p[id].remaining_time;
                p[id].remaining_time = 0;
                p[id].completion_time = timer;
                p[id].turn_around_time = p[id].completion_time - p[id].arrival_time;
                p[id].waiting_time = p[id].turn_around_time - p[id].burst_time;
                for(int i = 0; i < n; i++){
                    if((timer >= p[i].arrival_time) && (p[i].id != id)){
                        // cout<<" Found : "<<found(p[i].id)<<endl;
                        if((!p[i].done) && (!found(p[i].id))){
                            ready_queue.push(p[i].id);
                            // cout<<p[i].id<<" pushed at "<<timer<<endl;
                        }
                    }
                    
                }
            }
        //	ready_queue.pop();
	}
	// else{
	// 	ready_queue.pop();
	// }
         
        ready_queue.pop();   
    }
    float avg_wait = 0;
    display(p,n);
    for(int i = 0; i < n; i++){
        avg_wait += p[i].waiting_time; 
    }
    cout<<"\n Average Waiting Time : "<<avg_wait/n<<endl;
    return 0;
}
