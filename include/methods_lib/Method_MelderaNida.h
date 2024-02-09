#include <algorithm>
#include "Methods.h"

const double len_a = 0.5;
const double alfa = 1;
const double gamma = 2;
const double betta = 0.5;
const double epsilon=0.0001;


void method_Neldera_and_Mida(Function &function);

MatrixXd set_node_fill(Function &function);

void set_node_fill_coef(MatrixXd &node,Function &function);

VectorXd get_central_gravied(MatrixXd &node, int n, Function &function);

MatrixXd sort_node(MatrixXd &node, int n);

VectorXd display(VectorXd &x_central, VectorXd &x_big, Function &function);

VectorXd stretching(VectorXd &x_central, VectorXd &x_display, Function &function);

VectorXd сompression(VectorXd &x_central, VectorXd &x_big, Function &function);

MatrixXd reduction(MatrixXd &node, int n, Function &function);

bool stopping(VectorXd &x, int n, Function &function);