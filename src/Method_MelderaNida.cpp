#include "../include/methods_lib/Methods.h"


MatrixXd set_node_fill(Function &function) {
    int n = function.x0.size();

    MatrixXd node(n, n);
    node.setZero();
    node.row(0) = function.x0.transpose();
    set_node_fill_coef(node, function);
    return node;
}

void set_node_fill_coef(MatrixXd &node, Function &function) {
    int n = function.x0.size() - 1;
    double a = ((sqrt(n + 1) - 1) / (n * sqrt(2))) * len_a;
    double b = ((sqrt(n + 1) + n - 1) / (n * sqrt(2))) * len_a;
//    cout << "a=" << a << " b=" << b << endl;
    for (int i = 0; i < n; i++) {
        VectorXd x_cur(n + 1);
        x_cur.setZero();
        for (int j = 0; j < n; j++) {
            if (i == j) {
                x_cur(j) = function.x0(j) + a;
            } else {
                x_cur(j) = function.x0(j) + b;
            }
        }
        x_cur(n) = function.mnk(x_cur);
        node.row(i + 1) = x_cur.transpose();
    }
}


void print_node(const MatrixXd &node_x);

void print_point(VectorXd &x_central);

void method_Neldera_and_Mida(Function &function) {
    clock_t start = clock();

    function.x0.conservativeResize(function.x0.size() + 1);

    int n = function.x0.size() - 1;
    MatrixXd node_x = set_node_fill(function);

    VectorXd funk = node_x.col(n);

    while (stopping(funk, n, function)) {
        node_x = sort_node(node_x, n);
        VectorXd x_central = get_central_gravied(node_x, n, function);
        VectorXd x_big = node_x.row(n);
        VectorXd x_new = display(x_central, x_big, function);
        if (x_new(n) < x_big(n)) {
            node_x.row(n) = x_new.transpose();
            VectorXd x_stretching = stretching(x_central, x_new, function);
            if (x_stretching(n) < x_new(n)) {
                node_x.row(n) = x_stretching.transpose();
                node_x = sort_node(node_x, n);
            } else {
                node_x = sort_node(node_x, n);
            }
        } else {
            if (x_new(n) < node_x(n - 1, n)) {
                node_x.row(n) = x_new.transpose();
                node_x = sort_node(node_x, n);
            } else {
                VectorXd x_compression = сompression(x_central, x_big, function);
                if (x_compression(n) < x_big(n)) {
                    node_x.row(n) = x_compression.transpose();
                    node_x = sort_node(node_x, n);
                } else {
                    node_x = reduction(node_x, n, function);
                }
            }
        }
        funk = node_x.col(n);
        function.count_iter++;
    }
    node_x = sort_node(node_x, n);
    funk = node_x.row(1);
    function.x0 = funk;
    function.x0.conservativeResize(function.x0.size() - 1);

    clock_t end = clock();
    function._time = double(end - start) / CLOCKS_PER_SEC;
}

void print_point(VectorXd &x_central) { cout << "Точка:\n" << x_central.transpose() << endl; }

void print_node(const MatrixXd &node_x) { cout << "Матрица:\n" << node_x << endl; }


VectorXd get_central_gravied(MatrixXd &node, int n, Function &function) {
    VectorXd cent_grav(n + 1);
    cent_grav.setZero();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cent_grav(i) += node(j, i);
        }
        cent_grav(i) = cent_grav(i) / n;
    }
    cent_grav(n) = function.mnk(cent_grav);
    return cent_grav;
}

MatrixXd sort_node(MatrixXd &node, int n) {
    int sortingRow = n;
    VectorXi indices(node.rows());
    for (int i = 0; i < node.rows(); ++i) {
        indices(i) = i;
    }

    sort(indices.data(), indices.data() + indices.size(),
         [&node, sortingRow](int i, int j) {
             return node(i, sortingRow) < node(j, sortingRow);
         });

    MatrixXd sortedMatrix(node.rows(), node.cols());
    for (int i = 0; i < node.rows(); ++i) {
        sortedMatrix.row(i) = node.row(indices(i));
    }
    return sortedMatrix;
}

VectorXd display(VectorXd &x_central, VectorXd &x_big, Function &function) {
    VectorXd new_point = x_central + alfa * (x_central - x_big);
    new_point(x_central.size() - 1) = function.mnk(new_point);
    return new_point;
}

VectorXd stretching(VectorXd &x_central, VectorXd &x_display, Function &function) {
    VectorXd new_point = x_central + gamma * (x_display - x_central);
    new_point(x_central.size() - 1) = function.mnk(new_point);
    return new_point;
}

VectorXd сompression(VectorXd &x_central, VectorXd &x_big, Function &function) {
    VectorXd new_point = x_central + betta * (x_big - x_central);
    new_point(x_central.size() - 1) = function.mnk(new_point);
    return new_point;
}

MatrixXd reduction(MatrixXd &node, int n, Function &function) {
    MatrixXd new_node(n + 1, n + 1);
    new_node.setZero();
    for (int i = 0; i <= n; i++) {
        new_node.row(i) = node.row(i) + 0.5 * (node.row(i) - node.row(0));
        VectorXd new_point = new_node.row(i);
        new_node(i, n) = function.mnk(new_point);
    }
    return new_node;
}

bool stopping(VectorXd &x, int n, Function &function) {
    double value_foo = x.sum() / (n + 1);
    double sigma = 0;
    for (int i = 0; i <= n; i++) {
        sigma = (x(i) - value_foo);
    }
    sigma = sqrt(sigma / (n + 1));
    if (sigma < function.epsilon) {
        return 0;
    } else {
        return 1;
    }
}