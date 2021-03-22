//  Priority Scheduling Algorithm
// Preemptive

#include<bits/stdc++.h>

using namespace std;

struct process{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
    int remaining_time = 0;
    int priority = 0;
    bool done = false;
};

bool stop(process *p, int n){
    int c = 0;
    for(int i = 0; i < n; i++){
        if(p[i].done){
            c++;
        }
    }
    if(c == n){
        return true;
    }
    return false;
}

void print_gantt_chart(queue<int> q){
    cout<<"\n Gannt Chart : ";
    while(!q.empty()){
        cout<<" P"<<q.front()<<" ";
        q.pop();
    }
}

void display(process *p,int n){
    for(int i = 0; i < n; i++){
        cout<<" Process ID : "<<p[i].id<<" Priority : "<<p[i].priority<<" Arrival Time : "<<p[i].arrival_time<<" Burst Time : "<<p[i].burst_time;
        cout<<" Completion Time : "<<p[i].completion_time<<" Turn Around Time : "<<p[i].turn_around_time;
        cout<<" Waiting Time : "<<p[i].waiting_time<<endl;
    }
}

int main(){

    queue<int> gantt_chart;
    
    int n;
    cout<<"\n Enter the number of Processes : ";
    cin>>n;
    
    cout<<"\n Priority Order (1) for Higher-Lower (-1) for Lower-Higher : ";
    int priority_order;
    cin>>priority_order; 

    process p[n];
    for(int i = 0; i < n; i++){
        p[i].id = i;
        cout<<" \n Enter Priority of Process "<<i<<" : ";
        int x;
        cin>>x;
        p[i].priority = x * priority_order;
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

    int curr = 0;
    int timer = 0 + p[curr].arrival_time;

    while(!stop(p,n)){
        if(timer >= p[curr].arrival_time){
            for(int i = 0; i < n; i++){
                if((p[i].id != curr) && (!p[i].done) && (timer >= p[i].arrival_time)){
                    if(p[i].priority > p[curr].priority){
                        curr = i;
                    }
                }
            }
            if(!p[curr].done){
                if(p[curr].remaining_time > 1){
                    p[curr].remaining_time--;
                    timer++;
                    gantt_chart.push(p[curr].id);
                    // timer_chart.push(timer);

                    // cout<<" "<<p[curr].id;
                }
                else{
                    p[curr].remaining_time--;
                    timer++;
                    p[curr].completion_time = timer;
                    p[curr].done = true;
                    p[curr].turn_around_time = p[curr].completion_time - p[curr].arrival_time;
                    p[curr].waiting_time = p[curr].turn_around_time - p[curr].burst_time;
                    gantt_chart.push(p[curr].id);
                    // timer_chart.push(timer);
                    // cout<<" "<<p[curr].id;
                }
            }
            else{
                for(int i = 0; i < n; i++){
                    if((timer >= p[i].arrival_time) && (!p[i].done)){
                        curr = i;
                        break;
                    }
                }
            }
        }
        else{
            timer++;
        }
        
    }



    cout<<" CPU Scheduled Using Priority Scheduling Algorithm : \n";     
    display(p,n);

    float avg_wait = 0;
    
    for(int i = 0; i < n; i++){
        avg_wait += p[i].waiting_time; 
    }

    cout<<"\n Average Waiting Time : "<<avg_wait/n<<endl;
    
    print_gantt_chart(gantt_chart);
    cout<<endl;

    return 0;
}
