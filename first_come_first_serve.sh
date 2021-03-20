# First Come First Serve

declare -a arrival_time
declare -a burst_time
declare -a waiting_time
declare -a completion_time
declare -a process_id

# echo " First Come First Serve Algorithm "

echo " Enter the Number of Processes : "
read n 

for ((i = 1 ; i <= n ; i++))
do
    echo " Enter the Arrival Time of Process $i : "
    read at 
    arrival_time[i]=$at
    
    echo " Enter the Burst Time of Process $i : "
    read bt 
    burst_time[i]=$bt

    process_id[i]=$i
done

# echo ${arrival_time[*]}
# echo ${burst_time[*]}
# echo ${process_id[*]}

for ((i = 1 ; i <= n ; i++))
do
    for ((j = i ; i<= n ; i++))
    do
        if [ ${arrival_time[j]} -gt ${arrival_time[j+1]} ]
        then
            index=$j
            temp=${arrival_time[j]}
            arrival_time[j]=${arrival_time[j+1]}
            arrival_time[j+1]=$temp
            
            temp=${burst_time[j]}
            burst_time[j]=${burst_time[j+1]}
            burst_time[j+1]=$temp
            
            temp=${process_id[j]}
            process_id[j]=${process_id[j+1]}
            process_id[j+1]=$temp
            

        fi    
    done
done

# echo ${arrival_time[*]}
# echo ${burst_time[*]}
# echo ${process_id[*]}

timer=0
avgwait=0
echo -e "\e[1;42m CPU Scheduled based on FCFS \e[0m"

for ((i = 1 ; i <= n ; i++))
do
    if [ $timer -le ${arrival_time[i]} ]
    then 
        timer=${arrival_time[i]}
    fi
    
    waiting_time[i]=$((timer - arrival_time[i]))
    timer=$((timer + burst_time[i]))
    completion_time=$timer
    avgwait=$((avgwait + waiting_time[i]))

    echo " Process ID : ${process_id[i]} Arrival Time : ${arrival_time[i]} Burst Time : ${burst_time[i]} Completion Time : ${completion_time[i]} Waiting Time : ${waiting_time[i]}"
done

printf "%s" " Average Waiting Time : "
printf %.10f\\n "$((avgwait / n))"
