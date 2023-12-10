
#include "Method_MelderaNida.h"

double foo(VectorXd x) {
    return 2.8 * x(1) * x(1) + 1.9 * x(0) + 2.7 * x(0) * x(0) + 1.6 - 1.9 * x(1);
}

void nodeFillCoef(const VectorXd &x0, int n, MatrixXd &node);

MatrixXd set_NodeFill(VectorXd x0) {
    int n = x0.size();
    MatrixXd node(n, n);
    node.setZero();
    node.row(0) = x0.transpose();
    nodeFillCoef(x0, n - 1, node);
    return node;
}

void nodeFillCoef(const VectorXd &x0, int n, MatrixXd &node) {
    double a = ((sqrt(n + 1) - 1) / (n * sqrt(2))) * len_a;
    double b = ((sqrt(n + 1) + n - 1) / (n * sqrt(2))) * len_a;
//    cout << "a=" << a << " b=" << b << endl;
    for (int i = 0; i < n; i++) {
        VectorXd x_cur(n + 1);
        x_cur.setZero();
        for (int j = 0; j < n; j++) {
            if (i == j) {
                x_cur(j) = x0(j) + a;
            } else {
                x_cur(j) = x0(j) + b;
            }
        }
        x_cur(n) = foo(x_cur);
        node.row(i + 1) = x_cur.transpose();
    }
}

VectorXd setInitial_x0(int n);

int set_n();

void print_node(const MatrixXd &node_x);

void print_point(VectorXd &x_central);

void methodNelderaMida() {
    int n = set_n();
    VectorXd x0 = setInitial_x0(n);
    MatrixXd node_x = set_NodeFill(x0);
    while(1) {
        node_x = sort_Node(node_x, n);
        VectorXd x_central = get_CentralGravied(node_x, n);
        VectorXd x_big = node_x.row(n);
        VectorXd x_new = display(x_central, x_big);
        if (x_new(n) < x_big(n)) {
            node_x.row(n) = x_new.transpose();
            x_central = get_CentralGravied(node_x, n);
            VectorXd x_stretching = stretching(x_central, x_new);
            if (x_stretching(n) < x_new(n)) {
                node_x.row(n) = x_stretching.transpose();
                node_x = sort_Node(node_x, n);
            } else {
                node_x = sort_Node(node_x, n);
            }
            x_big.setZero();
            x_new.setZero();
            x_stretching.setZero();
            x_central.setZero();
        } else {
            if (x_new(n) < node_x(n - 1, n)) {
                node_x.row(n) = x_new.transpose();
                node_x = sort_Node(node_x, n);
            } else {
                VectorXd x_compression = сompression(x_central, x_big);
                if (x_compression(n) < x_big(n)) {
                    node_x.row(n) = x_compression.transpose();
                    node_x = sort_Node(node_x, n);
                } else {
                    node_x = reduction(node_x, n);
                }
            }
            x_big.setZero();
            x_new.setZero();
            x_central.setZero();
        }
        print_node(node_x);
    }
}

void print_point(VectorXd &x_central) { cout << "Точка:\n" << x_central.transpose() << endl; }

void print_node(const MatrixXd &node_x) { cout << "Симплекс:\n" << node_x << endl; }

int set_n() {
    int n;
    cout << "Введите размерность пространства:";
    cin >> n;
    return n;
}

VectorXd get_CentralGravied(MatrixXd &node, int n) {
    VectorXd cent_grav(n + 1);
    cent_grav.setZero();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cent_grav(i) += node(j, i);
        }
        cent_grav(i) = cent_grav(i) / n;
    }
    cent_grav(n) = foo(cent_grav);
    return cent_grav;
}

MatrixXd sort_Node(MatrixXd &node, int n) {
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

VectorXd display(VectorXd &x_central, VectorXd &x_big) {
    VectorXd new_point = x_central + alfa * (x_central - x_big);
    new_point(x_central.size() - 1) = foo(new_point);
    return new_point;
}

VectorXd stretching(VectorXd &x_central, VectorXd &x_display) {
    VectorXd new_point = x_central + gamma * (x_display - x_central);
    new_point(x_central.size() - 1) = foo(new_point);
    return new_point;
}

VectorXd сompression(VectorXd &x_central, VectorXd &x_big) {
    VectorXd new_point = x_central + betta * (x_big - x_central);
    new_point(x_central.size() - 1) = foo(new_point);
    return new_point;
}

MatrixXd reduction(MatrixXd &node, int n) {
    MatrixXd new_node(n + 1, n + 1);
    new_node.setZero();
    for (int i = 0; i <= n; i++) {
        new_node.row(i) = node.row(i) + 0.5 * (node.row(i) - node.row(0));
        VectorXd new_point = new_node.row(i);
        new_node(i, n) = foo(new_point);
    }
    return new_node;
}

bool stopping(VectorXd &function, int n) {
    double value_foo = function.sum() / (n + 1);
    double sigma = 0;
    for (int i = 0; i <= n; i++) {
        sigma = (function(i) - value_foo);
    }
    sigma = sqrt(sigma / (n + 1));
    if (sigma < epsilon) {
        return 1;
    } else {
        return 0;
    }
}

VectorXd setInitial_x0(int n) {
    VectorXd x0(n + 1);
    x0.setZero();
    cout << "Введите координаты начальной точки:";
    for (int i = 0; i < n; i++) {
        cin >> x0(i);
    }
    x0(n) = foo(x0);
    return x0;
}