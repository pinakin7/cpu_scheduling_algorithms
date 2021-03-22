#include<bits/stdc++.h>

using namespace std;

void print_gantt_chart(queue<int> q){
    cout<<"\n Gannt Chart : ";
    while(!q.empty()){
        cout<<" P"<<q.front()<<" ";
        q.pop();
    }
}

int main(){
    queue<int> gantt_chart;
    set< pair<int,pair<int,int> > > process_de;
    
    int n,id,at,bt;
    cout<<" Enter The number of process : ";
    cin>>n;
    
    int waiting_time[n];
    int x = n;
    
    while(x--){
        cout<<" Enter The Process Id : ";
        cin>>id;
        cout<<" Enter The Arrival Time : ";
        cin>>at;
        cout<<" Enter The Burst Time : ";
        cin>>bt;
        process_de.insert(make_pair(at,make_pair(id,bt)));
    }
    // int wait = 0;

    cout<<" CPU Scheduled Using First Come First Serve Algorithm : \n";
    int timer = 0;
     for(auto p:process_de){
         int arrival_time = p.first;
         auto q = p.second;
         int p_id = q.first;
         int burst_time = q.second;
         
         if(timer < arrival_time){
             timer = arrival_time;
         }
         waiting_time[p_id] = timer - arrival_time;
         timer = timer + burst_time;
         cout<<" Process Id : "<<p_id<<" Arrival Time : "<<arrival_time;
         cout<<" Burst Time : "<<burst_time<<" Waiting Time : "<<waiting_time[p_id]<<endl;
        gantt_chart.push(p_id);
    }
    float avg_wait = 0;
    for(int i=1;i<=n;i++){
        avg_wait += waiting_time[i];
    }
    avg_wait = (float)avg_wait/(float)n;
    cout<<" Average Waiting Time : "<<avg_wait<<endl;


    print_gantt_chart(gantt_chart);
    cout<<endl;

    return 0;
}
