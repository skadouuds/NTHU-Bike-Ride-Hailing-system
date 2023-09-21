#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


class map {

    public :
        int V;
        int **data;
        int flag;
        int **shortest;

        ~map();
    
        void graph(string selectedCase);
        int findVertices(string selectedCase);
        void addEdge(string selectedCase);
        int minDistance(int dist[], bool checked[]);
        int djikstra_LAMA(string selectedCase,int source, int destination);

        void djikstra_algo(string selectedCase);

        string station_start;
        string station_end;
        int distance;
};
