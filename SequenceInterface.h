#pragma once\

#include "Sequence.h"

double input_double();

int input_int();

Sequence<double> *choose_seq();

void print_seq(Sequence<double> *seq);

void do_operations(Sequence<double> *&seq);