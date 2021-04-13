

/**

  This Contains all the cpu Scheduling Algorithms.
  Considering only CPU Burst. I/O Burst with be updated soon.

**/















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

class cpu_scheduler{
    private:
        process p[1000];
        int n;
        queue<int> gantt_chart;
        queue<int> ready_queue;
        int timer = 0;
        int time_quantum;
        int curr;        
        float avg_wait = 0;
    public:
        void process_details(bool,int);
        void process_sorting();
        void process_display();
        void gantt_chart_display();
        bool stop();
        bool found(int);
        void driver_code();
        void fcfs();
        void sjf();
        void srtf();
        void round_robin();
        void priority();
        void average_waiting_time();
};



void cpu_scheduler::process_details(bool ispriority,int priority_order){
    cout<<"\n Enter the number of Processes : ";
    cin>>n;

    for(int i = 0; i < n; i++){
        p[i].id = i;
        if(ispriority){
            cout<<" \n Enter Priority of Process "<<i<<" : ";
            int x;
            cin>>x;
            p[i].priority = x * priority_order;
        }
        cout<<" \n Enter Arrival Time of Process "<<i<<" : ";
        cin>>p[i].arrival_time;
        cout<<" \n Enter Burst Time of Process "<<i<<" : ";
        cin>>p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
    }

    process_sorting();
    
}

void cpu_scheduler::process_sorting(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            if(p[j].arrival_time > p[j+1].arrival_time){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void cpu_scheduler::process_display(){
 
    cout<<"\n Process Table : \n";

    for(int i = 0; i < n; i++){
        cout<<" Process ID : "<<p[i].id<<" Priority : "<<p[i].priority<<" Arrival Time : "<<p[i].arrival_time;
        cout<<" Burst Time : "<<p[i].burst_time<<" Completion Time : "<<p[i].completion_time;
        cout<<" Turn Around Time : "<<p[i].turn_around_time<<" Waiting Time : "<<p[i].waiting_time<<endl;
    }
}

void cpu_scheduler::gantt_chart_display(){
    cout<<"\n Gantt Chart : ";
    while(!gantt_chart.empty()){
        cout<<" P"<<gantt_chart.front()<<" ";
        gantt_chart.pop();
    }
}

bool cpu_scheduler::stop(){
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

bool cpu_scheduler::found(int n){
    bool f = false;
    queue<int> temp = ready_queue;
    while (!temp.empty()){
        if(temp.front() == n)return true;
        temp.pop();
    }
    
    return f;
}

void cpu_scheduler::fcfs(){

    process_details(0,0);

    curr = 0;
    timer = timer + p[curr].arrival_time;

    while(!stop()){
        if(timer >= p[curr].arrival_time){
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

}

void cpu_scheduler::sjf(){
    
    process_details(0,0);
    
    curr = 0;
    timer = 0;
    timer = timer + p[curr].arrival_time;

    while(!stop()){
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
}

void cpu_scheduler::srtf(){
    process_details(0,0);

    curr = 0;
    timer = 0 + p[curr].arrival_time;
    while(!stop()){
        if(timer >= p[curr].arrival_time){
            for(int i = 0; i < n; i++){
                if((p[i].id != curr) && (!p[i].done) && (timer >= p[i].arrival_time)){
                    if(p[i].remaining_time < p[curr].remaining_time){
                        curr = i;
                    }
                }
            }
            if(!p[curr].done){
                if(p[curr].remaining_time > 1){
                    p[curr].remaining_time--;
                    timer++;
                    gantt_chart.push(p[curr].id);
                }
                else{
                    p[curr].remaining_time--;
                    timer++;
                    p[curr].completion_time = timer;
                    p[curr].done = true;
                    p[curr].turn_around_time = p[curr].completion_time - p[curr].arrival_time;
                    p[curr].waiting_time = p[curr].turn_around_time - p[curr].burst_time;
                    gantt_chart.push(p[curr].id);
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
}

void cpu_scheduler::round_robin(){

    process_details(0,0);
    cout<<"\n Enter the Time Quantum : ";
    cin>>time_quantum;
    
    timer = 0;
    curr = 0;
    timer = timer + p[0].arrival_time;
    
    ready_queue.push(p[curr].id);
    
    cout<<endl;
    while(!ready_queue.empty()){
        
        curr = ready_queue.front();
        if(timer >= p[curr].arrival_time){
            if(!p[curr].done){
                if(p[curr].remaining_time > time_quantum){
                    timer = timer + time_quantum;
                    p[curr].remaining_time = p[curr].remaining_time - time_quantum;
                    gantt_chart.push(p[curr].id);
                    for(int i = 0; i < n; i++){
                        if((timer >= p[i].arrival_time) && (p[i].id != p[curr].id)){
                            if((!p[i].done) && (!found(p[i].id))){
                                ready_queue.push(i);
                            }
                        }
                        
                    }
                    ready_queue.push(curr);
                }
                else{
                    p[curr].done = true;
                    timer = timer + p[curr].remaining_time;
                    p[curr].remaining_time = 0;
                    p[curr].completion_time = timer;
                    p[curr].turn_around_time = p[curr].completion_time - p[curr].arrival_time;
                    p[curr].waiting_time = p[curr].turn_around_time - p[curr].burst_time;
                    gantt_chart.push(p[curr].id);
                    for(int i = 0; i < n; i++){
                        if((timer >= p[i].arrival_time) && (p[i].id != p[curr].id)){
                            if((!p[i].done) && (!found(p[i].id))){
                                ready_queue.push(i);
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
}

void cpu_scheduler::priority(){

    cout<<"\n Priority Order (1) for Higher-Lower (-1) for Lower-Higher : ";
    int priority_order;
    cin>>priority_order; 
    process_details(1,priority_order);

    curr = 0;
    timer = 0 + p[curr].arrival_time;

    while(!stop()){
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
                }
                else{
                    p[curr].remaining_time--;
                    timer++;
                    p[curr].completion_time = timer;
                    p[curr].done = true;
                    p[curr].turn_around_time = p[curr].completion_time - p[curr].arrival_time;
                    p[curr].waiting_time = p[curr].turn_around_time - p[curr].burst_time;
                    gantt_chart.push(p[curr].id);
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
}

void cpu_scheduler::average_waiting_time(){
    
    for(int i = 0; i < n; i++){
        avg_wait += p[i].waiting_time; 
    }

    cout<<"\n Average Waiting Time : "<<avg_wait/n<<endl;
}

void cpu_scheduler::driver_code(){
    cout<<" \n\t\t =========================================== CPU SCHEDULING ALGORITHMS =========================================== \n";
    cout<<" \n\t\t\t 1. First Come First Serve CPU Scheduling Algorithm  ";
    cout<<" \n\t\t\t 2. Shortest Job First CPU Scheduling Algorithm  ";
    cout<<" \n\t\t\t 3. Shortest Remaining Time First CPU Scheduling Algorithm  ";
    cout<<" \n\t\t\t 4. Round Robin CPU Scheduling Algorithm  ";
    cout<<" \n\t\t\t 5. Priority CPU Scheduling Algorithm  \n";
    int ch;
    cout<<" Enter The Algorithm you want to Implement : ";
    cin>>ch;
    switch(ch){
        case 1:            
            fcfs();
            break;
        case 2:
            sjf();
            break;
        case 3:
            srtf();
            break;
        case 4:
            round_robin();
            break;
        case 5:
            priority();
            break;
    }
        
    process_display();
    gantt_chart_display();
    average_waiting_time();

}

int main(){
    cpu_scheduler cpu;
    cpu.driver_code();
    return 0;
}
