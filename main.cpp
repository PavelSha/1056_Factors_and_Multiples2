#include "main.h"
#include "print.h"
#include "test.h"

size_t adj_mat[MAX_SIZE_RANGE][MAX_SIZE_RANGE];
size_t match[MAX_SIZE_RANGE][MAX_SIZE_RANGE];
size_t path[MAX_SIZE_RANGE][MAX_SIZE_RANGE];
size_t deg_x[MAX_SIZE_RANGE];
size_t deg_y[MAX_SIZE_RANGE];
size_t ind_matr_x[MAX_SIZE_RANGE];
size_t ind_matr_y[MAX_SIZE_RANGE];
size_t satur_matr_x[MAX_SIZE_RANGE];
size_t satur_matr_y[MAX_SIZE_RANGE];

size_t stop;

inline void init_matr(const size_t n, size_t ind[], size_t satur[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        ind[i] = i; satur[i] = 0;
    }
}

int get_size_new_adj(const size_t n1, const size_t n0, size_t deg[], size_t ind[]) {
    size_t n = n1, i;
    for (i = n0 - 1; i >= 0 && i < MAX_SIZE_RANGE; i--) {
//        cout << " i " << i << endl;
//        cout << " n " << n << endl;
//        cout << " deg[i] " << deg[i] << endl;
        if (deg[i] == 0 && i == n - 1) n--;
        if (deg[i] == 0 && i < n - 1) {
            ind[i] = ind[n - 1];
            n--;
        }
        if (n > MAX_SIZE_RANGE) n = 0;
    }
    return n;
}

inline int get_adj_numb(const size_t x, const size_t y) {
    return adj_mat[ind_matr_x[x]][ind_matr_y[y]];
}

bool try_find_chain(size_t x, size_t nx, size_t ny) {
    if (stop > STOP_COUNT) return false;
    stop++;
            
    size_t y, xx;
    for (y = 0; y < ny; y++) {
//        cout << "try_find_chain for y get_adj_numb(" << x << ", " << y << "): " << get_adj_numb(x, y) << endl;
        if (get_adj_numb(x, y) != 1) continue;
        if (match[x][y] == 1) continue;
        if (path[x][y] == 1) return false;
//        cout << "try_find_chain old y: " << ind_matr_y[y] << endl;
        if (satur_matr_y[y] == 0) {
//        cout << "try_find_chain satur y: " << y << endl;
//            cout << "try_find_chain find (x,y): " << ind_matr_x[x] << " " << ind_matr_y[y] << endl;
            satur_matr_y[y] = 1;
            match[x][y] = 1;
//            cout << "try_find_chain find init match[xx][y] = 1 for old x " << ind_matr_x[x] << endl;
//            cout << "try_find_chain find init match[xx][y] = 1 for old y " << ind_matr_y[y] << endl;
            return true;
        }
        path[x][y] = 1;
        for (xx = 0; xx < nx; xx++) {
//            cout << "try_find_chain bef 1 old xx: " << ind_matr_x[xx] << endl;
            if (get_adj_numb(xx, y) != 1) continue;
//            cout << "try_find_chain bef 2 old xx: " << ind_matr_x[xx] << endl;
//            cout << "try_find_chain bef 2 xx: " << xx << endl;
//            cout << "try_find_chain bef 2 satur_matr_x[xx]: " << satur_matr_x[xx] << endl;
            if (satur_matr_x[xx] != 1) continue;
//            cout << "try_find_chain bef 3 old xx: " << ind_matr_x[xx] << endl;
//            cout << "try_find_chain bef 3 old y: " << ind_matr_y[y] << endl;
//            cout << "try_find_chain bef 3 match[xx][y]: " << match[xx][y] << endl;
            if (match[xx][y] == 0) continue;
//            cout << "try_find_chain !! old xx: " << ind_matr_x[xx] << endl;
//            cout << "try_find_chain !! old y: " << ind_matr_y[y] << endl;
            path[xx][y] = 1;
            bool res = try_find_chain(xx, nx, ny);
            path[xx][y] = 0;
            if (res) {
                match[xx][y] = 0;
                match[x][y] = 1;
                path[x][y] = 0;
                return true;
            }
        }
        path[x][y] = 0;
    }
    return false;
}

size_t get_min_count(size_t nx0, size_t ny0) {
    size_t nx, ny, i, temp, x, count;
    
    init_matr(nx0, ind_matr_x, satur_matr_x);
    init_matr(ny0, ind_matr_y, satur_matr_y);
    
    nx = nx0; ny = ny0;
    nx = get_size_new_adj(nx, nx0, deg_x, ind_matr_x);
//    cout << "nx: " << nx << endl;
    ny = get_size_new_adj(ny, ny0, deg_y, ind_matr_y);
//    cout << "ny: " << ny << endl;
    
//    print_ind_matr_x(nx);
//    cout << " ---- " << endl;
//    print_ind_matr_y(ny);
//    print_satur_matr_x(nx);
//    print_satur_matr_y(ny);
    
    count = 0;
    stop = 0;
    for (x = 0; x < nx; x++) {
//        cout << " begin x : " << ind_matr_x[x] << endl;
        bool res = try_find_chain(x, nx, ny);
        if (res) {
//            cout << "increm x : " << ind_matr_x[x] << endl;
            count++;
        }
        satur_matr_x[x] = 1;
//        if (res) {
//            print_satur_matr_x(nx);
//            print_satur_matr_y(ny);
//        }
    }
    if (stop > STOP_COUNT) cout << " S T O P !!!!" << endl;
    
//    cout << "Count: " << count << endl;
    
    return count;
}


int main() {
    // Write ....
    
    // Transformation
    tests();
}

