#include <bits/stdc++.h>
#define N 5 // number of processes
#define R 4 // number of resources
using namespace std;

int safeProcess(vector<vector<int>>& need, vector<int>& available, int size){

    bool safe, safeRow = false;
    int processId;
    for (int i = 0; i < size; i++){
        safe = true;
        for (int j = 0; j < R; j++){
            safe = safe && (need[i][j] <= available[j]);
        }
        if (safe)
            processId = i;
        safeRow = safeRow || safe;
    }
    if (safeRow){
        return processId;
    } else {
        return -1;
    }
}

bool check(vector<vector<int>>& need, vector<int>& available, int size){

    bool safe, safeRow = false;
    for (int i = 0; i < size; i++){
        safe = true;
        for (int j = 0; j < R; j++){
            safe = safe && (need[i][j] <= available[j]);
        }
        safeRow = safeRow || safe;
    }
    return safeRow;
}

void allocate_resources(vector<char>& process, int pid, vector<vector<int>>& allocation, 
            vector<vector<int>>& need,vector<int>& existing, vector<int>& possessed, 
            vector<int>& available){
        
    for (int i = 0; i < R; i++){
        allocation[pid][i] += need[pid][i];
        possessed[i] += need[pid][i];
        available[i] -= need[pid][i];
        need[pid][i] -= need[pid][i];
    }
}

bool isComplete(vector<vector<int>>& need, int pid){
    for (int i = 0; i < R; i++){
        if (need[pid][i] != 0){
            return false;
        }
    }
    return true;
}

void free_resources(vector<char>& process, int pid, vector<vector<int>>& allocation, 
            vector<vector<int>>& need,vector<int>& existing, vector<int>& possessed, 
            vector<int>& available){
    cout << "Resources of process " << process[pid] << " are being freed." << endl;

    for (int i = 0; i < R; i++){
        possessed[i] -= allocation[pid][i];
        available[i] += allocation[pid][i];
        allocation[pid][i] -= allocation[pid][i];
    }
}

void banker(vector<char>& process, vector<vector<int>>& allocation, vector<vector<int>>& need,
            vector<int>& existing, vector<int>& possessed, vector<int>& available, int size){

    while (1){
        // check if need <= available for all processes
        int pid = safeProcess(need, available, size);
        if (pid != -1){
            cout << "The process " << process[pid] << " can proceed " << endl;
            allocate_resources(process, pid, allocation, need, existing, possessed, available);

            if (isComplete(need, pid)){
                cout << "Process " << process[pid] << " is complete" << endl;

                free_resources(process, pid, allocation, need, existing, possessed, available);

                // remove process D
                char p = process[pid];
                process.erase(process.begin() + pid);
                allocation.erase(allocation.begin() + pid);
                need.erase(need.begin() + pid);
                cout << "Deleted process " << p << endl;
            }
            // decrease the number of processes;
            size--;
            cout << endl;
        } else {
            cout << "Deadlock" << endl;
            break;
        }
        if (process.size() == 0){
            break;
        }
    }
}

int main(){
    //vector<char> process = {'A', 'B', 'C', 'D', 'E'};    
    vector<char> process = {'A', 'B', 'C'};    
    // vector<vector<int>> allocation = {
    //     {3, 0, 1, 1},
    //     {0, 1, 0, 0},
    //     {1, 1, 1, 0},
    //     {1, 1, 0, 1},
    //     {0, 0, 0, 0}
    // };
    vector<vector<int>> allocation = {
        {0, 0, 1, 0},
        {2, 0, 0, 1},
        {0, 1, 2, 0}
    };

    // vector<vector<int>> need = {
    //     {1, 1, 0, 0}, 
    //     {0, 1, 1, 2}, 
    //     {3, 1, 0, 0}, 
    //     {0, 0, 1, 0}, 
    //     {2, 1, 1, 0}
    // };
    vector<vector<int>> need = {
        {2, 0, 0, 1}, 
        {1, 0, 1, 0}, 
        {2, 1, 0, 0}
    };

    // vector<int> existing = {6, 3, 4, 2};
    // vector<int> possessed = {5, 3, 2, 2};
    // vector<int> available = {1, 0, 2, 0};
    vector<int> existing = {4, 2, 3, 1};
    vector<int> possessed = {2, 1, 3, 1};
    vector<int> available = {2, 1, 0, 0};

    banker(process, allocation, need, existing, possessed, available, process.size());
    return 0;
}