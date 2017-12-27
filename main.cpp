#include "main.h"
#include "print.h"
#include "test.h"
/*
 * Координаты матрицы смежности (кмс)
 * Последовательные коориданты вершин в графах X и Y (пкв)
 */

size_t adj_mat[MAX_SIZE_RANGE][MAX_SIZE_RANGE]; // Матрица смежности (кмс)
size_t match[MAX_SIZE_RANGE][MAX_SIZE_RANGE]; // Итоговое паросочетание [Matching (graph theory)] (пкв)
size_t path[MAX_SIZE_RANGE][MAX_SIZE_RANGE]; // Текущий путь поиска паросочетания (Path) (пкв)
size_t deg_x[MAX_SIZE_RANGE]; // Степерь графа X [Degree (graph theory)]
size_t deg_y[MAX_SIZE_RANGE]; // Степерь графа Y [Degree (graph theory)]
size_t ind_matr_x[MAX_SIZE_RANGE]; // Массив для матрицы смежности графа X, (пкв) -> (кмс)
size_t ind_matr_y[MAX_SIZE_RANGE]; // Массив для матрицы смежности графа Y, (пкв) -> (кмс)
size_t satur_matr_x[MAX_SIZE_RANGE]; // Массив вершин графа X, прошедших проверку на поиск паросочетания (помеченые)(пкв)
size_t satur_matr_y[MAX_SIZE_RANGE]; // Массив вершин графа Y, прошедших проверку на поиск паросочетания (помеченые)(пкв)

size_t stop;

void flush_adj_mat(const int size) {
    size_t i, j;
    for (i = 0; i < size; i++) 
        for (j = 0; j < size; j++) {
            adj_mat[i][j] = 0;
            match[i][j] = 0;
            path[i][j] = 0;
        }
}

inline void flush_deg_x(const int size) {
    size_t i;
    for (i = 0; i < size; i++) deg_x[i] = 0;
}

inline void flush_deg_y(const int size) {
    size_t i;
    for (i = 0; i < size; i++) deg_y[i] = 0;
}

void flush(const int size) {
    flush_adj_mat(size);
    flush_deg_x(size);
    flush_deg_y(size);
}

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

size_t init_match(const size_t nx, const size_t ny) {
    size_t c = 0;
    for (size_t x = 0; x < nx; x++) {
        for (size_t y = 0; y < ny; y++) {
            if (get_adj_numb(x, y) != 1) continue;
            if (match[x][y] == 1) continue;
            if (satur_matr_y[y] == 1) continue;
            
//            cout << " init match x " << x << endl;
//            cout << " init match y " << y << endl;

            match[x][y] = 1;
            c++;
            satur_matr_x[x] = 1;
            satur_matr_y[y] = 1;
            break;
        }
    }
    return c;
}

void swap_adj_mat(size_t nx0, size_t ny0) {
    size_t adj_mat_res[MAX_SIZE_RANGE][MAX_SIZE_RANGE];        
    for (size_t x = 0; x < nx0; x++) {
        for (size_t y = 0; y < ny0; y++) {
            adj_mat_res[x][y] = adj_mat[x][y];
        }
    }
    std::swap(adj_mat, adj_mat_res);
}

// Поиск чередующей цепи
bool try_find_chain(size_t x, size_t nx, size_t ny) {
    if (stop > STOP_COUNT) return false;
    stop++;
            
    size_t y, xx;
    for (y = 0; y < ny; y++) {
//        cout << "try_find_chain for y get_adj_numb(" << x << ", " << y << "): " << get_adj_numb(x, y) << endl;
        if (get_adj_numb(x, y) != 1) continue;  // Пропускаем, если нет ребра в матрице смежности
        if (match[x][y] == 1) continue;         // Пропускаем, если ребро уже в паросочетании
        if (path[x][y] == 1) return false;      // Текущий путь в поиске паросочетаний не должен хранить повторные ребра
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
    size_t nx, ny, i, temp, x;
            
    if (nx0 > ny0) {
        swap_adj_mat(nx0, ny0);        

        temp = nx0;
        nx0 = ny0;
        ny0 = temp;
    }
    
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
    
    size_t count = init_match(nx, ny);
//    cout << " init count " << count << endl;
    stop = 0;
    for (x = 0; x < nx; x++) {
        if (satur_matr_x[x] == 1) continue;
        
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

int process() {
    int t, n1, n2, num_test = 1, i, j;
    int s1[MAX_SIZE_RANGE] = {0}, s2[MAX_SIZE_RANGE] = {0};
    
    size_t res;
    
    flush(MAX_SIZE_RANGE);
    
    scanf("%d",&t);
    while (t > 0) {
        scanf("%d",&n1);
        for (i = 0; i < n1; i++) scanf("%d",s1[i]);
        
        scanf("%d",&n2);
        for (i = 0; i < n2; i++) scanf("%d",s2[i]);
        
        for (i = 0; i < n1; i++) {
            for (j = 0; j < n2; j++) {
                if (s2[j] % s1[i] == 0) {
                    adj_mat[i][j] = 1;
                    deg_x[i]++;
                    deg_y[j]++;
                }
            }
            s1[i] = 0;
        }
        
        res = get_min_count(n1, n2);
        
        printf("Case %d: %u\n", num_test++, res);
        t--;
        
        if (t > 0) {
//            for (i = 0; i < n1; i++) s1[i] = 0;
            for (i = 0; i < n2; i++) s2[i] = 0;
            flush(n1 > n2 ? n1 : n2);
        }
    }
    
    return 0;
}

int main() {
    return process();
}

