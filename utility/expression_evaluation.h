#ifndef CARTESIAN_EXPRESSION_EVALUATION_H
#define CARTESIAN_EXPRESSION_EVALUATION_H
#include <string>
#include <map>
#include <set>
#include <stack>
#include <iostream>
#include <cmath>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace utility{
    static std::set<std::string> existingOperators{"+","-","*","/","^","sqrt","sin","max","min","cos","ln"};
    double evaluateExpression(const std::map<std::string,double>& variables, std::string expression);
}
#endif //CARTESIAN_EXPRESSION_EVALUATION_H
