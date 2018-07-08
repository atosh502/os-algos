#include <bits/stdc++.h>
#define N 5

using namespace std;

void fcfs(vector<char>& process, vector<int>& arrival_time, vector<int>& cpu_time, int size){
    
    while (1){

        int min = arrival_time[0], index = 0;
        for (int i = 1; i < size; i++){
            if (arrival_time[i] <= min){
                min = arrival_time[i];
                index = i;
            }
        }

        cout << " " << process[index] << " ";
        cout << "arrival time = " << arrival_time[index] << " ";
        cout << "cpu time = " << cpu_time[index] << endl;

        process.erase(process.begin() + index);
        cpu_time.erase(cpu_time.begin() + index);
        arrival_time.erase(arrival_time.begin() + index);
        size--;

        if (process.size() == 0)
            break;
    }

}

int main(){
    vector<char> process = {'A', 'B', 'C', 'D', 'E'};
    vector<int> arrival_time = {0, 2, 4, 3, 1};
    vector<int> cpu_time = {5, 2, 3, 4, 6};

    fcfs(process, arrival_time, cpu_time, N);

    return 0;
}
