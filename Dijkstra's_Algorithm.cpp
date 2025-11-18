#include <vector>
#include <climits>
#include <iostream>
using namespace std;

void dijkstras(int start, const vector<vector<int>>& matrix){
    int n = matrix.size();      //The number of vertices

    vector<bool> selected(n, false);        //Tracks visited vertices
    vector<int> lowDist(n, INT_MAX);        //Stores shortest known distances
    vector<int> prevVert(n, -1);            //Stores parent of each vertex

    /////////  INITIALIZE  /////////

    selected[start] = true;
    lowDist[start] = 0;
    prevVert[start] = -1;

    // set initial neighbors of start
    for(int i = 0; i < n; i++){
        if(matrix[start][i] != 0){
            lowDist[i] = matrix[start][i];
            prevVert[i] = start;
        }
    }

    /////////  ITERATION  /////////

    int currSelected = -1;
    for(int i = 0; i < n; i++){
        int best = -1;
        int bestDist = INT_MAX;

        // pick global unselected min-distance vertex
        for(int v = 0; v < n; v++){
            if(!selected[v] && lowDist[v] < bestDist){
                bestDist = lowDist[v];
                best = v;
            }
        }

        if(best == -1) break; // no reachable vertices left

        currSelected = best;
        selected[currSelected] = true;

        // relax neighbors of currSelected
        for(int j = 0; j < n; j++){
            if(matrix[currSelected][j] == 0) continue;
            if(selected[j]) continue;

            if(lowDist[currSelected] + matrix[currSelected][j] < lowDist[j]){
                lowDist[j] = lowDist[currSelected] + matrix[currSelected][j];
                prevVert[j] = currSelected;
            }
        }
    }

    /////////  PRINT RESULTS  /////////

    cout << "Selected: ";
    for(bool x : selected) cout << x << " ";
    cout << endl;

    cout << "Low distance: ";
    for(int y : lowDist) cout << y << " ";
    cout << endl;

    cout << "Prev Node: ";
    for(int z : prevVert) cout << z << " ";
    cout << endl;
}

int main(){

    vector<vector<int>> adj = {
        {0,6,0,9,0,0,0,0,0,0},
        {0,0,5,0,3,0,0,0,0,0},
        {0,0,0,2,0,7,0,0,0,0},
        {0,0,0,0,4,0,0,0,8,0},
        {0,0,0,0,0,1,0,0,0,6},
        {0,0,0,0,0,0,3,0,0,0},
        {0,0,0,0,0,0,0,2,0,9},
        {0,0,0,0,0,0,0,0,4,0},
        {0,0,0,0,0,0,0,0,0,2},
        {0,0,0,0,0,0,0,0,0,0}
    };





    dijkstras(0, adj);

    return 0;
}
