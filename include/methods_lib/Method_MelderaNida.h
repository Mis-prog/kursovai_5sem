#include <algorithm>
#include "Methods.h"

const double len_a = 0.5;
const double alfa = 1;
const double gamma = 2;
const double betta = 0.5;
const double epsilon=0.0001;

double foo(VectorXd &x);

void method_Neldera_and_Mida(Function &function);

MatrixXd set_node_fill(Function &function);

void set_node_fill_coef(MatrixXd &node,Function &function);

VectorXd get_CentralGravied(MatrixXd &node, int n);

MatrixXd sort_Node(MatrixXd &node, int n);

VectorXd display(VectorXd &x_central, VectorXd &x_big);

VectorXd stretching(VectorXd &x_central, VectorXd &x_display);

VectorXd сompression(VectorXd &x_central, VectorXd &x_big);

MatrixXd reduction(MatrixXd &node, int n);

bool stopping(VectorXd& function,int n);