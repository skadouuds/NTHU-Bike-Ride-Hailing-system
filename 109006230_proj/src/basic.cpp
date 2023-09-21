#include "./nthu_bike.h"
#include "./mapping.h" 
#include "./usercheck.h"


void basic(string selectedCase){
    map maps1;
    my_user userdata;
    my_station stat1;

    const int totalrequest = userdata.read_user(selectedCase); //All starts from Num 0
    const int total_stations = maps1.findVertices(selectedCase);
    const int total_biketype = userdata.get_num_biketype(selectedCase);

    int** rent_data = new int *[totalrequest];
    int** cantik = new int *[totalrequest];
    for (int i = 0; i < totalrequest; ++i) {
        rent_data[i] = new int[5];
        cantik[i] = new int[5];
    }
    
    int** user_result = new int *[100000]; 
    int** transfer = new int *[100000];
    for (int i = 0; i < 100000 ; ++i) {
        transfer[i] = new int[6];
        user_result[i] = new int[6];
    }
    for(int c = 0; c < 100000; c++) {
        for(int k =0 ; k < 6; k++) {
            transfer[c][k] = -1;
            user_result[c][k] = -1;
        }
    }
    


    int time[totalrequest]; //time[totalreq] = -1;
    for (int i = 0; i < totalrequest; i++) {
        time[i] = -1;
    }

    string multipletype[totalrequest]; //Buat biketype dalam bentuk string [User id]
    // int user_result[totalrequest][6]; //userid, accept / reject, bike id, starttime, endtime, revenur
    // int rent_data[totalrequest][4]; //userid >> bike_type >> timestart >> timeend >> startpoint >> endpoint >> FLAG if multiple type bike

    int is = 0; //Total Request
    int coy = 0; //Counter Buat di Ending

    ///Part1
    ifstream myfile("./testcases/"+selectedCase+"/user.txt", ios::in);
    if(!myfile.is_open()) {
        cout << "File Users Cannot be opened" << endl;
        exit;
    } else {
        string userid;
        int timestart;
        int timeend;
        int total_rent;
        string bike_type;
        string startpoint;
        string endpoint;
        
        while (!myfile.eof()) {
            myfile >> userid >> bike_type >> timestart >> timeend >> startpoint >> endpoint;
            rent_data[is][0] = stoi(userid.substr(1)); 
            rent_data[is][1] = timestart;
            rent_data[is][2] = timeend;
            rent_data[is][3] = stoi(startpoint.substr(1));
            rent_data[is][4] = stoi(endpoint.substr(1));

            time[is] = timestart;
            multipletype[rent_data[is][0]] = bike_type; //Multiple[userid] = string bike typenya

            is++;
            if(is == totalrequest) {
                break;
            }
        }
        myfile.close(); 
    }
    stat1.station_ready(selectedCase); //IMPORTING ALL THE BIKES INTO THE STATION ( With Counter < Limit)
    userdata.mergesort(time,rent_data, 0,is-1);
    maps1.djikstra_algo(selectedCase);

    int soi = 0;
    int test = 0;
    while(soi < is) { //JANGGAL GA SIH SOI > IS DOANK ?
         if(time[test] == rent_data[soi][1]) {
            cantik[test][0] = rent_data[soi][0]; //User Id
            cantik[test][1] = rent_data[soi][1]; //Time start
            cantik[test][2] = rent_data[soi][2]; //Time end
            cantik[test][3] = rent_data[soi][3]; //Station Awal
            cantik[test][4] = rent_data[soi][4]; //Station Akhir
            rent_data[soi][1] = -1;
            test++;
            soi = 0;
        } else {
            soi++;
        }
    }
    
    while (coy < is) { // 17 Ganti IS
        const int temp_station = cantik[coy][3];
        int temp_ave = cantik[coy][2]-cantik[coy][1]; //Time end - Time start
        int shortest = maps1.shortest[temp_station][cantik[coy][4]]; //First station and end station
        int total_end = shortest + cantik[coy][1]; //Shortest + starttime = New End time

        if(stat1.bike_ready(temp_station, multipletype[cantik[coy][0]], cantik[coy][1])) { 
            int high_id = stat1.max_bikeid;
            int revenue = stat1.bike_rent[high_id] * shortest; //Rental Fee

            if(cantik[coy][1] >= 0 && cantik[coy][2] <= 1440 && (temp_ave <= 1440)) { //When The Time start above >= 0 and endd time <= 1440
                if(total_end < cantik[coy][2]) { //Arrival time Less than End time[...]
                    user_result[cantik[coy][0]][0] = cantik[coy][0]; //User_result [bike id]
                    user_result[cantik[coy][0]][1] = 1;
                    user_result[cantik[coy][0]][2] = high_id;
                    user_result[cantik[coy][0]][3] = cantik[coy][1];
                    user_result[cantik[coy][0]][4] = total_end;
                    user_result[cantik[coy][0]][5] = revenue ;
                    userdata.transfer_log(transfer,cantik, coy, high_id, cantik[coy][1], total_end);
                    stat1.update(cantik[coy][3], cantik[coy][4], high_id, total_end); //UPDet nya harus bentuk double array pointer keknya gaboleh terima int karna mau ubah hasilny ake main
                } else {
                    //Arrival time > End time
                    userdata.rejected(cantik[coy][0], user_result);
                }
            } else {
                //Time start < 0 or Time end > 1440
                userdata.rejected(cantik[coy][0], user_result);
            }
        } else {
            //Bike is not ready at the station
            userdata.rejected(cantik[coy][0], user_result);
        }
        stat1.flag = 0; //Reset FLag buat bike_ready()
        stat1.max = -1; // Reset MAX buat di BOOL 
        coy++;  
    }
    userdata.output_trf(selectedCase, transfer,user_result, is);
    stat1.station_status(selectedCase, total_stations);


    //destructor
    for (int i=0; i< totalrequest; i++) {
        delete[] rent_data[i];
        delete[] cantik[i];
    }
    delete [] rent_data;
    delete [] cantik;

    for (int i=0; i< 100000; i++) {
        delete[] user_result[i];
        delete[] transfer[i];
    }
    delete [] user_result;
    delete [] transfer;

}

