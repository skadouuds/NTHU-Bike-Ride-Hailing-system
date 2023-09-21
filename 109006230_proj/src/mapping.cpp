#include "mapping.h"

#define INTERGER_MAX 2147483647 //int_maX

void map::graph(string selectedCase) {//Constructor initialize Matrix Adjacency with 0

    data = new int*[V];
    for (int i = 0; i < V; i++) {
        data[i] = new int[V];
        for (int j = 0; j < V; j++) {
            data[i][j] = 0;
        }
    } 

    shortest = new int *[V];
    for (int i = 0; i < V; ++i) {
        shortest[i] = new int[V];
    }

}

void map::addEdge(string selectedCase) {//Undirected graph with weighted distance
    ifstream myfile("./testcases/"+selectedCase+"/map.txt", ios::in); //Open the map file
    string station1_string, station2_string;
    int station1, station2;
    int vertices;
    int distance;
    while(!myfile.eof()) {
        myfile >> station1_string >> station2_string >> distance;
        station1 = stoi(station1_string.substr(1));
        station2 = stoi(station2_string.substr(1));
        data[station1][station2] = distance;
        data[station2][station1] = distance;
    }
    myfile.close();
}

int map::minDistance(int dist[], bool checked[]) {//Find the minimum distance from the source
    int min = INTERGER_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (checked[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void map::djikstra_algo(string selectedCase) {//Djikstra Algorithm
    int dist[V];
    bool checked[V];

    this->graph(selectedCase);
    this->addEdge(selectedCase);

    for(int s = 0; s < V; s++) {
        for(int i = 0; i<V; i++) {
            dist[i] = INTERGER_MAX;
            checked[i] = false;
        }
            dist[s] = 0;

            for(int j = 0; j < V-1; j++) {
                int minimum = minDistance(dist, checked);
                checked[minimum] = true;

                for(int k = 0; k < V; k++) {
                    if(checked[k] == false  && data[minimum][k] && dist[minimum] != INTERGER_MAX && dist[minimum] + data[minimum][k] < dist[k]) {
                        dist[k] = dist[minimum] + data[minimum][k];
                    }
                }
            }
        for(int d = s+1; d < V; d++) {
                shortest[s][d] = dist[d];
                shortest[d][s] = shortest[s][d];
        }
    }
}

int map::findVertices(string selectedCase){
    ifstream myfile("./testcases/"+selectedCase+"/map.txt", ios::in); //Open the map file
    string line;
    string station1_string, station2_string;
    int station1, station2;
    int vertices;
    int distance; 
    int max = 0;  
    if(myfile.is_open()){
        while(!myfile.eof()){
            myfile >> station1_string >> station2_string >> distance;
            station1 = stoi(station1_string.substr(1));
            station2 = stoi(station2_string.substr(1));
            if(station1 > max) max = station1;
            if(station2 > max) max = station2;
        }
        myfile.close();
        V = max + 1;
        return V;
    } else {
        cout << "Unable to open the file of Map.txt";
        return 0;
    }
}

map::~map() {
    for (int i=0; i< V; i++) {
        delete[] data[i];
    }
    delete [] data;


    for (int i=0; i< V; i++) {
        delete[] shortest[i];
    }
    delete [] shortest;
};
