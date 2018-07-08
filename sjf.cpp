#include <bits/stdc++.h>
#define N 5

using namespace std;

void sjf(vector<char>& process, vector<int>& arrival_time, vector<int>& cpu_time, int size){

    int max = arrival_time[0]; // the minimum arrival time
    for (int i = 1; i < size; i++){
        if (arrival_time[i] <= max){
            max = arrival_time[i];
        }
    }

    while (1){

        int min = arrival_time[0], index = 0, cpu = cpu_time[0];
        for (int i = 1; i < size; i++){
            if (arrival_time[i] <= max && cpu_time[i] <= cpu){
                min = arrival_time[i];
                cpu = cpu_time[i];
                index = i;
            }
        }

        max += cpu_time[index];

        cout << " " << process[index] << " ";
        cout << "arrival time = " << arrival_time[index] << " ";
        cout << "max = " << max << " ";
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
    vector<int> arrival_time = {2, 4, 8, 10, 5};
    vector<int> cpu_time = {3, 6, 4, 3, 2};

    sjf(process, arrival_time, cpu_time, N);

    return 0;
}