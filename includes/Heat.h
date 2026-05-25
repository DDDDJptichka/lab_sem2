#pragma once

#include <cmath>
#include <algorithm>

#include "Exception.h"
#include "DynamicArray.h"
#include "DiagonalMatrix.h"

template <typename Container> size_t get_size(const Container &container){

    if constexpr (requires {container.get_size();}){

        return container.get_size();

    }
    else if constexpr (requires {container.get_length();}){

        return container.get_length();

    }

}

template <template <typename> class Container> DiagonalMatrix<Container, double> make_heat_matrix(size_t matrix_size, double sigma){

    Container<double> buffer;

    for (size_t i = 0; i < 3 * matrix_size - 2; ++i){

        buffer.append(0.0);

    }

    DiagonalMatrix<Container, double> matrix(buffer, 3 * matrix_size - 2, 3);

    for (size_t i = 0; i < matrix_size; ++i){

        matrix.set(i, i, 1 + 2 * sigma);

        if (i > 0){

            matrix.set(i, i - 1, -sigma);

        }

        if (i + 1 < matrix_size){

            matrix.set(i, i + 1, -sigma);

        }

    }

    return matrix;

}

template <template <typename> class Container> Container<double> thomas_algorithm(const DiagonalMatrix<Container, double> &matrix, const Container<double> &d){

    size_t matrix_size = matrix.get_matrix_size();

    if (get_size(d) != matrix_size){

        throw different_matrix_size("There is not enough information about the temperature");

    }

    Container<double> al;
    Container<double> bt;
    Container<double> x;

    for (size_t i = 0; i < matrix_size; ++i){

        al.append(0);
        bt.append(0);
        x.append(0);

    }

    double b0 = matrix.get(0, 0);
    double c0 = 0.0;

    if (abs(b0) < 1e-12){

        throw zero_determinant("Zero division(b0 = 0)");

    }
    
    if (matrix_size > 1){

        c0 = matrix.get(0, 1);

    }

    al[0] = -c0 / b0;
    bt[0] = d[0] / b0;

    for (size_t i = 1; i < matrix_size; ++i){

        double a = matrix.get(i, i - 1);
        double b = matrix.get(i, i);
        double c = 0;

        if (i + 1 < matrix_size){

            c = matrix.get(i, i + 1);

        }

        double denominator = b + a * al[i - 1];

        if (abs(denominator) < 1e-12){

            throw zero_determinant("Zero division");

        }

        al[i] = -c / denominator;
        bt[i] = (d[i] - a * bt[i - 1]) / denominator;

    }
     
    x[matrix_size - 1] = bt[matrix_size - 1];

    for (int i = matrix_size - 2; i >= 0; --i){

        x[i] = al[i] * x[i + 1] + bt[i];

    }

    return x;

}

template <template <typename> class Container> Container<double> heat_step(const Container<double> &old_u, double left_t, double right_t, double sigma){

    size_t full_size = get_size(old_u);

    if (full_size < 3){

        throw index_out_of_range("Too small heat layer");

    }

    size_t index = full_size - 1;
    size_t count_unknown = index - 1;

    auto matrix = make_heat_matrix<Container>(count_unknown, sigma);
    Container<double> d;

    for (size_t i = 1; i < index; ++i){

        d.append(old_u[i]);

    }

    d[0] = d[0] + sigma * left_t;
    d[count_unknown - 1] = d[count_unknown - 1] + sigma * right_t;

    Container<double> inner_solution = thomas_algorithm(matrix, d);
    Container<double> new_u;

    new_u.append(left_t);

    for (size_t i = 0; i < count_unknown; ++i){

        new_u.append(inner_solution[i]);

    }

    new_u.append(right_t);

    return new_u;

}

template <template <typename> class Container> DynamicArray<Container<double>> solve_heat_equation(const Container<double> &start_layer, size_t steps, double left_t, double right_t, double sigma){

    DynamicArray<Container<double>> layers(0);
    Container<double> current = start_layer;

    layers.append(start_layer);

    for (size_t step = 0; step < steps; ++step){

        current = heat_step<Container>(current, left_t, right_t, sigma);
        layers.append(current);

    }

    return layers;

}