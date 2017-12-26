#include "main.h"

void flush_adj_mat() {
    size_t i, j;
    for (i = 0; i < MAX_SIZE_RANGE; i++) 
        for (j = 0; j < MAX_SIZE_RANGE; j++) {
            adj_mat[i][j] = 0;
            match[i][j] = 0;
            path[i][j] = 0;
        }
}

inline void flush_deg_x() {
    size_t i;
    for (i = 0; i < MAX_SIZE_RANGE; i++) deg_x[i] = 0;
}

inline void flush_deg_y() {
    size_t i;
    for (i = 0; i < MAX_SIZE_RANGE; i++) deg_y[i] = 0;
}

inline void flush() {
    flush_adj_mat();
    flush_deg_x();
    flush_deg_y();
}

void tests() {
    size_t res, temp, temp2;
    
    flush();
    adj_mat[2][0] = 1;    
    deg_x[2] = 1;
    deg_y[0] = 1;
    res = get_min_count(3, 3);
    cout << "Test #1: " << (res == 1 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][2] = 1; adj_mat[2][0] = 1;    
    deg_x[0] = 1; deg_x[2] = 1;
    deg_y[0] = 1; deg_y[2] = 1;
    res = get_min_count(3, 3);
    cout << "Test #2: " << (res == 2 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][2] = 1; adj_mat[1][1] = 1; adj_mat[2][0] = 1;    
    deg_x[0] = 1; deg_x[1] = 1; deg_x[2] = 1;
    deg_y[0] = 1; deg_y[1] = 1; deg_y[2] = 1;
    res = get_min_count(3, 3);
    cout << "Test #3: " << (res == 3 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[1][0] = 1; adj_mat[1][2] = 1;
    deg_x[1] = 2;
    deg_y[0] = 1; deg_y[2] = 1;
    res = get_min_count(3, 3);
    cout << "Test #4: " << (res == 1 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][0] = 1; adj_mat[1][0] = 1; adj_mat[1][2] = 1; adj_mat[2][2] = 1;
    deg_x[0] = 1; deg_x[1] = 2;  deg_x[2] = 1;
    deg_y[0] = 2; deg_y[2] = 2;
    res = get_min_count(3, 3);
    cout << "Test #5: " << (res == 2 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[1][0] = 1; adj_mat[1][1] = 1; adj_mat[2][1] = 1;
    deg_x[1] = 2; deg_x[2] = 1;
    deg_y[0] = 1; deg_y[1] = 2;
    res = get_min_count(3, 3);
    cout << "Test #6: " << (res == 2 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][0] = 1; adj_mat[0][2] = 1;
    adj_mat[1][1] = 1;
    adj_mat[0][2] = 1; adj_mat[2][2] = 1;
    deg_x[0] = 2; deg_x[1] = 1; deg_x[2] = 2;
    deg_y[0] = 2; deg_y[1] = 1; deg_y[2] = 2;
    res = get_min_count(3, 3);
    cout << "Test #7: " << (res == 3 ? "Ok" : "False") << endl;
    
    flush();
    res = get_min_count(3, 3);
    cout << "Test #8: " << (res == 0 ? "Ok" : "False") << endl;
    
    flush();
    res = get_min_count(MAX_SIZE_RANGE, MAX_SIZE_RANGE);
    cout << "Test #9: " << (res == 0 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[99][99] = 1;
    deg_x[99] = 1;
    deg_y[99] = 1;
    res = get_min_count(MAX_SIZE_RANGE, MAX_SIZE_RANGE);
    cout << "Test #10: " << (res == 1 ? "Ok" : "False") << endl;
    
    flush();
    for (temp = 0; temp < MAX_SIZE_RANGE; temp++) adj_mat[temp][temp] = 1;
    for (temp = 0; temp < MAX_SIZE_RANGE; temp++) deg_x[temp] = 1;
    for (temp = 0; temp < MAX_SIZE_RANGE; temp++) deg_y[temp] = 1;
    res = get_min_count(MAX_SIZE_RANGE, MAX_SIZE_RANGE);
    cout << "Test #11: " << (res == MAX_SIZE_RANGE ? "Ok" : "False") << endl;
    
    flush();
    for (temp = 0; temp < (MAX_SIZE_RANGE - 2) / 2; temp++) {
        adj_mat[2 * temp + 1][2 * temp] = 1;
        adj_mat[2 * temp + 1][2 * temp + 2] = 1;
    }
    adj_mat[MAX_SIZE_RANGE - 1][MAX_SIZE_RANGE - 2] = 1;
    deg_x[MAX_SIZE_RANGE - 1] = 1;
    deg_y[0] = 1;
    for (temp = 1; temp < MAX_SIZE_RANGE - 2; temp += 2) deg_x[temp] = 2;
    for (temp = 2; temp < MAX_SIZE_RANGE - 1; temp += 2) deg_y[temp] = 2;
    res = get_min_count(MAX_SIZE_RANGE, MAX_SIZE_RANGE);
    cout << "Test #12: " << (res == MAX_SIZE_RANGE / 2 ? "Ok" : "False") << endl;
    
    flush();
    for (temp = 0; temp < (6 - 2) / 2; temp++) {
        adj_mat[2 * temp + 1][2 * temp] = 1;
        adj_mat[2 * temp + 1][2 * temp + 2] = 1;
    }
    adj_mat[5][4] = 1;
    deg_x[5] = 1;
    deg_y[0] = 1;
    for (temp = 1; temp < 6 - 2; temp += 2) deg_x[temp] = 2;
    for (temp = 2; temp < 6 - 1; temp += 2) deg_y[temp] = 2;
    res = get_min_count(6, 6);
    cout << "Test #13: " << (res == 3 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[1][0] = 1; adj_mat[1][2] = 1;
    adj_mat[3][2] = 1; adj_mat[3][4] = 1;
    adj_mat[5][4] = 1;
    deg_x[1] = 2; deg_x[3] = 2; deg_x[5] = 1;
    deg_y[0] = 1; deg_y[2] = 2; deg_y[4] = 2;
    res = get_min_count(6, 6);
    cout << "Test #14: " << (res == 3 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[1][0] = 1; adj_mat[1][2] = 1;
    adj_mat[3][2] = 1; adj_mat[3][4] = 1;
    adj_mat[5][4] = 1;
    deg_x[1] = 2; deg_x[3] = 2; deg_x[5] = 1;
    deg_y[0] = 1; deg_y[2] = 2; deg_y[4] = 2;
    res = get_min_count(6, 6);
    cout << "Test #14: " << (res == 3 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][0] = 1; adj_mat[0][2] = 1;
    adj_mat[1][0] = 1; adj_mat[1][3] = 1;
    adj_mat[2][2] = 1;
    deg_x[0] = 2; deg_x[1] = 2; deg_x[2] = 1;
    deg_y[0] = 2; deg_y[2] = 2; deg_y[3] = 1;
    res = get_min_count(3, 4);
    cout << "Test #15: " << (res == 3 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[1][0] = 1; adj_mat[1][1] = 1; adj_mat[1][2] = 1;
    adj_mat[3][4] = 1; adj_mat[4][4] = 1; adj_mat[5][4] = 1;
    adj_mat[7][6] = 1; adj_mat[7][7] = 1; adj_mat[7][8] = 1;
    deg_x[1] = 3; deg_x[3] = 1; deg_x[4] = 1; deg_x[5] = 1; deg_x[7] = 3;
    deg_y[0] = 1; deg_y[1] = 1; deg_y[2] = 1; deg_y[4] = 3; deg_y[6] = 1; deg_y[7] = 1; deg_y[8] = 1;
    res = get_min_count(8, 9);
    cout << "Test #16: " << (res == 3 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][0] = 1; adj_mat[0][1] = 1; adj_mat[0][2] = 1; adj_mat[0][3] = 1;
    adj_mat[1][0] = 1; adj_mat[1][1] = 1;
    adj_mat[2][0] = 1; adj_mat[2][2] = 1;
    adj_mat[3][2] = 1; adj_mat[3][3] = 1;
    adj_mat[4][1] = 1; adj_mat[4][3] = 1;
    deg_x[0] = 4; deg_x[1] = 2; deg_x[2] = 2; deg_x[3] = 2; deg_x[4] = 2;
    deg_y[0] = 3; deg_y[1] = 3; deg_y[2] = 3; deg_y[3] = 3;
    res = get_min_count(5, 4);
    cout << "Test #17: " << (res == 4 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][0] = 1;
    adj_mat[1][0] = 1; adj_mat[1][1] = 1;
    adj_mat[2][0] = 1; adj_mat[2][1] = 1; adj_mat[2][2] = 1;
    adj_mat[3][0] = 1; adj_mat[3][1] = 1; adj_mat[3][2] = 1; adj_mat[3][3] = 1;
    adj_mat[4][0] = 1; adj_mat[4][1] = 1; adj_mat[4][2] = 1; adj_mat[4][3] = 1; adj_mat[4][4] = 1;
    deg_x[0] = 1; deg_x[1] = 2; deg_x[2] = 3; deg_x[3] = 4; deg_x[4] = 5;
    deg_y[0] = 5; deg_y[1] = 4; deg_y[2] = 3; deg_y[3] = 2;
    res = get_min_count(5, 4);
    cout << "Test #18: " << (res == 4 ? "Ok" : "False") << endl;
    
//    flush();
//    for (temp = 0; temp < MAX_SIZE_RANGE; temp++) {
//        for (temp2 = 0; temp2 <= temp; temp2++) adj_mat[temp][temp2] = 1;
//        deg_x[temp] = temp + 1;
//        if (temp + 1 < MAX_SIZE_RANGE) deg_y[temp] = MAX_SIZE_RANGE - temp;
//    }
//    res = get_min_count(MAX_SIZE_RANGE, MAX_SIZE_RANGE - 1);
//    cout << "Test #19: " << (res == MAX_SIZE_RANGE - 1 ? "Ok" : "False") << endl;
    
    flush();
    adj_mat[0][0] = 1; adj_mat[0][1] = 1; adj_mat[0][2] = 1;
    adj_mat[1][0] = 1; adj_mat[1][1] = 1; adj_mat[1][2] = 1;
    adj_mat[2][0] = 1; adj_mat[2][1] = 1; adj_mat[2][2] = 1;
    deg_x[0] = 3; deg_x[1] = 3; deg_x[2] = 3;
    deg_y[0] = 3; deg_y[1] = 3; deg_y[2] = 3;
    res = get_min_count(3, 3);
    cout << "Test #20: " << (res == 3 ? "Ok" : "False") << endl;
    
//    flush();
//    for (temp = 0; temp < MAX_SIZE_RANGE; temp++) {
//        for (temp2 = 0; temp2 < MAX_SIZE_RANGE; temp2++) adj_mat[temp][temp2] = 1;
//        deg_x[temp] = MAX_SIZE_RANGE;
//        deg_y[temp] = MAX_SIZE_RANGE;
//    }
//    res = get_min_count(MAX_SIZE_RANGE, MAX_SIZE_RANGE);
//    cout << "Test #21: " << (res == MAX_SIZE_RANGE ? "Ok" : "False") << endl;
}
