#include <bits/stdc++.h>
#define N 5
#define T 3 // time slice is 3
using namespace std;

void round_robin(vector<char>& process, vector<int>& arrival_time, vector<int>& cpu_time, int size){
    
    int max = 0, temp;
    while (1){

        int index = 0;
        int min = arrival_time[0];
        for (int i = 1; i < size; i++){
            if (arrival_time[i] <= min){
                min = arrival_time[i];
                index = i;
            }
        }

        cout << " " << process[index] << " ";
        
        if (cpu_time[index] >= 3){
            temp = T;
        } else {
            temp = cpu_time[index];
        }
        arrival_time[index] = temp + max;
        max = arrival_time[index];
        cout << " arrival time = " << arrival_time[index] << " ";
        cpu_time[index] -= temp;
        cout << "cpu time = " << cpu_time[index] << endl;

        if (cpu_time[index] == 0){
            process.erase(process.begin() + index);
            cpu_time.erase(cpu_time.begin() + index);
            arrival_time.erase(arrival_time.begin() + index);
            size--;
        }

        if (process.size() == 0){
            break;
        }
    }
    cout << endl;
}

int main(){
    vector<char> process = {'A', 'B', 'C', 'D', 'E'};
    vector<int> arrival_time = {0, 2, 3, 4, 5};
    vector<int> cpu_time = {8, 6, 7, 5, 4};

    round_robin(process, arrival_time, cpu_time, N);

    return 0;
}