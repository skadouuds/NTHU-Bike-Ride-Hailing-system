#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>



using namespace std;

class my_user {
    public:
        int get_num_biketype(string selectedCase);
        int read_user(string selectedCase);
        
        int user_num = 0; // User total
        int num_biketype = 0; //Bike type total

        void mergesort(int *time, int **rentdata, int const begin, int const end);
        void merge(int *time, int **rentdata, int const left, int const mid, int const right);


        void splitIt(int **cantik, int coy, string selectedCase);
        void transfer_log(int** transfer,int **cantik, int coy, int bikeid, int start_t, int end_t);
        void transfer_notsort(int** transfer,int **cantik, int coy, int bikeid, int start_t, int end_t, string selectedCase);
        void rejected(int userid, int** user_result);

        void output_trf(string selectedCase, int** transfer, int** user_result, int is);

};

class my_station {
    public :

    int **station = new int*[1000];
    my_station() {
        for(int i = 0; i < 1000; ++i) {
            station[i] = new int[10000];
        }
        for(int c = 0; c < 1000; c++) {
            for(int k =0 ; k <10000; k++) {
                station[c][k] = -1;
            }
        }
        for(int i = 0; i < 10000; i++) {
            time[i] = -1;
            bike_rent[i] = -1.0;
            rent_count[i] = -1;
            initial_price[i] = -1.0;
        }
    }
    //Total Bike <= 10000, Bike type <= 10000 , All assign to -1
    int time[10000] ; //Time[Bikeid]
    float bike_rent[10000]; //bike_rent[bikeid] = current rental price
    int rent_count[10000] ; //bike_used[bikeid] = rental couuter
    float initial_price[10000];//initial_price[bike_type] = initial price




    //Station ready()
    float discount; // Discount depreciation
    int rentlimit;  // Limit rent
    int counterkontol;

    int biketype = 0;
    string biketype_str1;
    int type;
    int bikeid;
    string station_id;
    int num_stat;
    float price; //Price
    int counter; //Maksudnya Counter rent speda

    int max_type;
    int max_bikeid;
    int flag;
    float max = 0;

    ~my_station();


    void station_ready(string selectedCase); //Import dulu semua data bike ke dalam 2d arr
    bool bike_ready(int first_stat, string multipletypes, int starttime); // Cek bike type itu ada ga di station tersebut
    int max_venue(int stat, int tipe,int starttime); // stat = station awal , tipe = bike type to getting the Highest price id
    void update(int startstation, int endstation, int ids, int totalend);
    void searching( int firststat, int sub, int starttime);
    void station_status(string selectedCase, int numstat);

};

