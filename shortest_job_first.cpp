// Shortest Job First 

#include<bits/stdc++.h>

using namespace std;

struct process{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
    bool done = false;
};

void display(process *p,int n){
    for(int i = 0; i < n; i++){
        cout<<" Process ID : "<<p[i].id<<" Arrival Time : "<<p[i].arrival_time<<" Burst Time : "<<p[i].burst_time;
        cout<<" Completion Time : "<<p[i].completion_time<<" Turn Around Time : "<<p[i].turn_around_time;
        cout<<" Waiting Time : "<<p[i].waiting_time<<endl;
    }
}

void print_gantt_chart(queue<int> q){
    cout<<"\n Gannt Chart : ";
    while(!q.empty()){
        cout<<" P"<<q.front()<<" ";
        q.pop();
    }
}

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

int main(){

    int n;
    cout<<"\n Enter the number of Processes : ";
    cin>>n;
    
    queue<int> gantt_chart;
    // queue<int> timer_chart;
    process p[n];
    for(int i = 0; i < n; i++){
        p[i].id = i;
        cout<<" \n Enter Arrival Time of Process "<<i<<" : ";
        cin>>p[i].arrival_time;
        cout<<" \n Enter Burst Time of Process "<<i<<" : ";
        cin>>p[i].burst_time;
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

    int curr = 0;
    int timer = 0;
    timer = timer + p[curr].arrival_time;

    while(!stop(p,n)){
        if(timer >= p[curr].arrival_time){
            for(int i = 0; i < n; i++){
                if((p[i].id != curr) && (!p[i].done) && (timer >= p[i].arrival_time)){
                    if(p[i].burst_time < p[curr].burst_time){
                        curr = i;
                    }
                }
            }
            if(!p[curr].done){
                timer += p[curr].burst_time;
                p[curr].completion_time = timer;
                p[curr].done = true;
                p[curr].turn_around_time = p[curr].completion_time - p[curr].arrival_time;
                p[curr].waiting_time = p[curr].turn_around_time - p[curr].burst_time;
                gantt_chart.push(p[curr].id);
                    
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

    cout<<" CPU Scheduled Using Shortest Job First Algorithm : \n";     
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
