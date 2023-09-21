#include "./usercheck.h" //Initialize all the users

int my_user::read_user(string selectedCase) {
    ifstream ifs("./testcases/"+selectedCase+"/user.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to opened the file." <<endl;
        return 0;
    } else {
        string s;
        while (getline(ifs, s)){
            user_num ++;
        }
    }
    ifs.close();
    return user_num;
};

int my_user::get_num_biketype(string selectedCase) {
    ifstream ifs("./testcases/"+selectedCase+"/bike_info.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to opened the file." <<endl;
        return 0;
    } else {
        string s;
        while (getline(ifs, s)){
             num_biketype++;
        }
    }
    ifs.close();
    return num_biketype - 2;
};

void my_station::station_ready(string selectedCase) {
    //Input Bike_info.txt
    ifstream info("./testcases/"+selectedCase+"/bike_info.txt", ios::in);
    if(info.is_open()) {
        string disc_str;
        string limit_str;
        getline(info, disc_str);
        getline(info, limit_str);
        discount = stof(disc_str); //Discount Depreciacion
        rentlimit = stoi(limit_str); //Limit 
        while (!info.eof()) { 
            string biketype_str;
            int init_price;  
            info >> biketype_str >> initial_price[biketype]; //initial_price[bike_type] = harganya
            biketype++;
        }
        info.close();
    } else {
        cout << "Bike_info.txt cannot be opened" << endl;
        return;
    }
   
    //Opening Bike info in each station inputiing all.
    ifstream filekas("./testcases/"+selectedCase+"/bike.txt", ios::in);
    if(filekas.is_open()) {
        while(!filekas.eof()) {
            filekas >> biketype_str1 >> bikeid >> station_id >> price >> counter;
            type = stoi(biketype_str1.substr(1));
            num_stat = stoi(station_id.substr(1));
            station[num_stat][bikeid] = type; //station[stat id][bikeid] = bike type
            bike_rent[bikeid] = price; //bike_rent[bikeid] = current rental price FLOAT yak
            rent_count[bikeid] = counter; //bike_used[bikeid] = rental couuter 
            counterkontol = bikeid;
        }
        filekas.close();
    } else {
        cout << "Bike.txt cannot be opened" << endl;
    }

};

void my_station::update(int startstation, int endstation, int ids, int totalend) {
    rent_count[ids] = rent_count[ids] + 1;
    time[ids] = totalend;
    bike_rent[ids] = initial_price[max_type] - (discount * rent_count[ids]); //initial price [biketype] , Actual Rent Price
    station[endstation][ids] = station[startstation][ids];
    station[startstation][ids] = -1; //Cari solusi update stasiun sepeda nya yg bener , Keknya pake List [stats][biketype] ={id id didalam apa aja}
};

bool my_station::bike_ready(int first_stat, string multipletype, int starttime) {
    stringstream sstr(multipletype);
    while(sstr.good()) {
        string kata;
        int sub;
        getline(sstr, kata, ',');
        sub = stoi(kata.substr(1));
        for (int i = 0 ; i < (counterkontol+1) ; i++) {
            if(station[first_stat][i] == sub && time[i] <= starttime && (rent_count[i] < rentlimit) ) {
                if(max < bike_rent[i]) {
                    max = bike_rent[i];
                    max_bikeid = i;
                    max_type = sub;
                    flag = 1;
                }
                if(max == bike_rent[i]) { //If Has the same price, Check for The lowest Bike Id
                    if(i < max_bikeid) {
                        max = bike_rent[i];
                        max_bikeid = i;
                        max_type = sub;
                        flag = 1;
                    }
                }
            } 
        }
    }
    if(flag == 1) {
        return true;
    } else {
        return false;
    }
};

void my_user::transfer_log(int** transfer,int **cantik, int coy, int bikeid, int start_t, int end_t) {
    // Bike Id , Start point, End Point, Start time, End time , User ID
    transfer[cantik[coy][0]][0] = bikeid;
    transfer[cantik[coy][0]][1] = cantik[coy][3];
    transfer[cantik[coy][0]][2] = cantik[coy][4];
    transfer[cantik[coy][0]][3] = start_t;
    transfer[cantik[coy][0]][4] = end_t;
    transfer[cantik[coy][0]][5] = cantik[coy][0];
};

void my_user::rejected(int userid, int** user_result) {
    user_result[userid][0] = userid;
    user_result[userid][1] = 0;
    user_result[userid][2] = 0;
    user_result[userid][3] = 0;
    user_result[userid][4] = 0;
    user_result[userid][5] = 0;
};

void my_user::output_trf(string selectedCase, int** transfer, int **user_result, int is) {
    ofstream out_transfer;
    ofstream out_user;
    out_transfer.open("./result/"+selectedCase+"/transfer_log.txt", ios::out); //Transfernya not sort ya bisa diganti
    out_user.open("./result/"+selectedCase+"/user_result.txt", ios::out);
    if(!out_transfer.is_open() && !out_user.is_open()) {
        cout << "Error: file to write could not be opened either Transfer log or User Result" << endl;
        exit(1);
    } else {
        for (int i = 0 ; i < 100000 ; i++) {
            if(transfer[i][0] != -1) {
                out_transfer << transfer[i][0] << " S";
                out_transfer << transfer[i][1] << " S";
                out_transfer << transfer[i][2] << " ";
                out_transfer << transfer[i][3] << " ";
                out_transfer << transfer[i][4] << " U";
                out_transfer << transfer[i][5] << endl;
            }
            if(user_result[i][0] != -1) {
                out_user << "U" << user_result[i][0] << " ";
                out_user << user_result[i][1] << " ";
                out_user << user_result[i][2] << " ";
                out_user << user_result[i][3] << " ";
                out_user << user_result[i][4] << " ";
                out_user << user_result[i][5] << endl;
            }
        }
        out_user.close();
        out_transfer.close();
    }
};

void my_station::station_status(string selectedCase, int numstat) {
    ofstream station_stat;
    station_stat.open("./result/"+selectedCase+"/station_status.txt", ios::out); //Transfernya not sort ya bisa diganti
    if(!station_stat.is_open()) {
        cout << "Error: file to write could not be opened" << endl;
        exit(1);
    } else {
        for(int c = 0; c < numstat; c++) {
            for(int i = 0; i < 10000; i++) {
                if(station[c][i] != -1) {
                    float kintil = round(bike_rent[i]*10)/10;
                    station_stat << "S" << c << " " << i << " B" << station[c][i] << " " << kintil << " " << rent_count[i] << endl;
                }
            }
        }
    }
};

void my_user::mergesort(int *time, int **rentdata, int const begin, int const end) {
    if (begin >= end)
        return; 
    auto mid = begin + (end - begin) / 2;
    mergesort(time, rentdata, begin, mid);
    mergesort(time, rentdata, mid + 1, end);
    merge(time, rentdata, begin, mid, end);
};

void my_user::merge(int *time, int **rentdata, int const left, int const mid, int const right) {
    auto const subOne = mid - left + 1;
    auto const subTwo = right - mid;
 
    auto *leftArr = new int[subOne], *rightArr = new int[subTwo];
 
    for (auto i = 0; i < subOne; i++) {
        leftArr[i] = time[left + i];
    }
    for (auto j = 0; j < subTwo; j++) {
        rightArr[j] = time[mid + 1 + j];
    }
 
    auto idx1 = 0, idx2 = 0; 
    int idxMerged = left; 

    while (idx1 < subOne && idx2 < subTwo) {
        if (leftArr[idx1] <= rightArr[idx2]) {
            time[idxMerged] = leftArr[idx1];
            idx1++;
        } else {
            time[idxMerged]= rightArr[idx2];
            idx2++;
        }
        idxMerged++;
    }
    while (idx1 < subOne) {
        time[idxMerged]= leftArr[idx1];
        idx1++;
        idxMerged++;
    }
    while (idx2 < subTwo) {
        time[idxMerged]= rightArr[idx2];
        idx2++;
        idxMerged++;
    }
    delete[] leftArr;
    delete[] rightArr;
};

my_station::~my_station() {
    for (int i=0; i< 1000; i++) {
        delete[] station[i];
    }
    delete [] station;

};


