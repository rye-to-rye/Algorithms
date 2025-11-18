#include <vector>
#include <climits>
#include <iostream>
using namespace std;

void dijkstras(int start, const vector<vector<int>>& matrix){
    int n = matrix.size();                  //The number of vertices

    vector<bool> selected(n, false);        //The array that tracks the vertices that have been selected
    vector<int> lowDist(n, INT_MAX);        //The array that stores the lowest distance of every vertice
    vector<int> prevVert(n, -1);            //The array stores the vertice previous to itself

    /////////  INITIALIZE  /////////

    int currStartSelected = start;          //The vertice we start with

    selected[start] = true;                 //Setting all arrays indexs' of [start] to initiazlied values
    lowDist[start] = 0;
    prevVert[start] = -1;

    int startMinVertice = INT_MAX;          //Tells me where to move selected for next iteration in initialize phase
    int startMinCost = INT_MAX;             //Tells me what the next vertice's lowDist value is going to be

    for(int i = 0; i < n; i++){             //Two things: 1, it finds the vertice with the smallest edge
                                            //            2, it sets lowDist[adjacent vertex] and prevDist[adjacent vertex] to its default edge values from the matrix and the previous vertex (start), to both, respectively
        if(matrix[start][i] == 0 || selected[i] == true) continue;

        if(matrix[start][i] < startMinCost){
            startMinCost = matrix[start][i];
            startMinVertice = i;
        }

        lowDist[i] = matrix[start][i];
        prevVert[i] = currStartSelected;
    }

    /////////  ITERATION  /////////

    int currSelected = startMinVertice;     //sets the new starting vertex as the vertex found from initialization

    while (true) {

        selected[currSelected] = true;      //in currSelected, that vertex is now selected, so it won't be traveresable in the future

        for(int j = 0; j < n; j++){         //going thru the row of the selected vertex, in the matrix
            if(matrix[currSelected][j] == 0 || selected[j] == true) continue;   //if it finds a 0 or it is already selected, skip this entry

            if(matrix[currSelected][j] + lowDist[currSelected] < lowDist[j]){   //if the the new calculated lowest distance is less than the current lowest distance, update that vertex's lowest distance
                lowDist[j] = matrix[currSelected][j] + lowDist[currSelected];   //<<<^
                prevVert[j] = currSelected;                                     //also update the previous vertex for that vertex
            }
        }

        int minNextVert = INT_MAX;          //Store the next vertice to move to

        for(int k = 0; k < n; k++){
            if(matrix[currSelected][k] == 0 || selected[k] == true) continue;   //if it finds a 0 or it is already selected, skip this entry

            if(minNextVert == INT_MAX){     //if minNextVert is maxed out, just set it to the first adjacent vertex
                minNextVert = k;
                continue;
            }

            if(lowDist[k] < lowDist[minNextVert]){      //however, if the adjacent vertex's lowDist is less than our least, update it
                minNextVert = k;
            }
        }
        if (minNextVert == INT_MAX) break;  // no more reachable nodes

        currSelected = minNextVert;         //our next vertex to travel to has been set!
    }

    //Print out information !!
    cout << "Selected: ";
    for(int x : selected){
        cout << x << " ";
    }
    cout << endl;

    cout << "Low distance: ";
    for(int y : lowDist){
        cout << y << " ";
    }
    cout << endl;

    cout << "Prev Node: ";
    for(int z : prevVert){
        cout << z << " ";
    }
    cout << endl;
}

int main(){

    vector<vector<int>> adj = {
        {0, 4, 0, 0, 0, 10, 0, 0, 0, 0},  // 0
        {0, 0, 3, 0, 0, 0, 0, 5, 0, 0},   // 1
        {0, 0, 0, 4, 0, 0, 8, 0, 0, 0},   // 2
        {0, 0, 0, 0, 2, 0, 0, 0, 7, 0},   // 3
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 9},   // 4
        {0, 0, 0, 0, 0, 0, 2, 0, 0, 0},   // 5
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 6},   // 6
        {0, 0, 0, 0, 3, 0, 0, 0, 0, 2},   // 7
        {0, 0, 5, 0, 0, 0, 0, 0, 0, 1},   // 8
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}    // 9
    };



    dijkstras(0, adj);

    return 0;
}
