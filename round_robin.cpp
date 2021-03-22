#include<bits/stdc++.h>
using namespace std;
queue<int> ready_queue;

void print_gantt_chart(queue<int> q){
    cout<<"\n Gannt Chart : ";
    while(!q.empty()){
        cout<<" P"<<q.front()<<" ";
        q.pop();
    }
}

struct process{
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
    queue<int> gantt_chart;
    
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
    int curr = 0;
    timer = timer + p[0].arrival_time;
    // cout<<time<<id;

    
    ready_queue.push(p[curr].id);
    // cout<<ready_queue.size();
  //  cout<<id<<"\npushed\n";
    // int id = p[curr].id;
	cout<<endl;
    while(!ready_queue.empty()){
        // ready_queue.pop();
        
        curr = ready_queue.front();
        if(timer >= p[curr].arrival_time){
            if(!p[curr].done){
                if(p[curr].remaining_time > time_quantum){
                    timer = timer + time_quantum;
                    p[curr].remaining_time = p[curr].remaining_time - time_quantum;
                    gantt_chart.push(p[curr].id);
                    //cout<<" "<<id;
                    for(int i = 0; i < n; i++){
                        if((timer >= p[i].arrival_time) && (p[i].id != p[curr].id)){
                            // cout<<" Found : "<<found(p[i].id)<<endl;
                            if((!p[i].done) && (!found(p[i].id))){
                                ready_queue.push(i);
                                // cout<<p[i].id<<" pushed at "<<timer<<endl;
                            }
                        }
                        
                    }
                    ready_queue.push(curr);
                    // cout<<id<<" pushed at "<<timer<<endl;
                }
                else{
                    p[curr].done = true;
                    //cout<<id<<"completed"<<endl;
                    //cout<<" "<<id;
                    timer = timer + p[curr].remaining_time;
                    p[curr].remaining_time = 0;
                    p[curr].completion_time = timer;
                    p[curr].turn_around_time = p[curr].completion_time - p[curr].arrival_time;
                    p[curr].waiting_time = p[curr].turn_around_time - p[curr].burst_time;
                    gantt_chart.push(p[curr].id);
                    for(int i = 0; i < n; i++){
                        if((timer >= p[i].arrival_time) && (p[i].id != p[curr].id)){
                            // cout<<" Found : "<<found(p[i].id)<<endl;
                            if((!p[i].done) && (!found(p[i].id))){
                                ready_queue.push(i);
                                // cout<<p[i].id<<" pushed at "<<timer<<endl;
                            }
                        }
                        
                    }
                }
            }
            ready_queue.pop();
        }
        else{
            timer++;
        }
           
    }

    float avg_wait = 0;
    
    cout<<" CPU Scheduled Using Round Robin Algorithm : \n";
    display(p,n);
    for(int i = 0; i < n; i++){
        avg_wait += p[i].waiting_time; 
    }
    cout<<"\n Average Waiting Time : "<<avg_wait/n<<endl;

    print_gantt_chart(gantt_chart);
    cout<<endl;
    
    return 0;
}
