/* 
 * File:   main.h
 * Author: Paul
 *
 * Created on 25 декабря 2017 г., 20:13
 */

#ifndef MAIN_H
#define	MAIN_H

#include <iostream>
#define MAX_SIZE_RANGE 100
#define STOP_COUNT 100000001

using std::cout;
using std::cin;
using std::endl;

extern size_t adj_mat[MAX_SIZE_RANGE][MAX_SIZE_RANGE];
extern size_t match[MAX_SIZE_RANGE][MAX_SIZE_RANGE];
extern size_t path[MAX_SIZE_RANGE][MAX_SIZE_RANGE];
extern size_t deg_x[MAX_SIZE_RANGE];
extern size_t deg_y[MAX_SIZE_RANGE];
extern size_t ind_matr_x[MAX_SIZE_RANGE];
extern size_t ind_matr_y[MAX_SIZE_RANGE];
extern size_t satur_matr_x[MAX_SIZE_RANGE];
extern size_t satur_matr_y[MAX_SIZE_RANGE];

size_t get_min_count(size_t, size_t);

#endif	/* MAIN_H */

