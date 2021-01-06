#include "expression_evaluation.h"
namespace utility{
    double evaluateExpression(const std::map<std::string,double>& variables, std::string expression)
    {
        std::stack<std::string> operators;
        std::stack<double> values;
        std::vector<std::string> splitsContainer;
        boost::split(splitsContainer,expression,boost::is_any_of(" "));
        for(const auto& elem : splitsContainer) {
            if(existingOperators.count(elem)) {
                operators.push(elem);
            }
            else if(variables.find(elem) != variables.cend()) {
                values.push(variables.at(elem));
            }
            else if(elem == "(") {
                continue;
            }
            else if(elem == ")") {
                if(operators.empty()) {
                    break;
                }
                std::string op = operators.top();
                operators.pop();
                double numericalV = values.top();
                values.pop();
                if(op == "+") {
                    numericalV = values.top() + numericalV;
                    values.pop();
                }
                else if(op == "-") {
                    numericalV = values.top() - numericalV;
                    values.pop();
                }
                else if(op == "*") {
                    numericalV = values.top() * numericalV;
                    values.pop();
                }
                else if(op == "/") {
                    numericalV = values.top() / numericalV;
                    values.pop();
                }
                else if(op == "^") {
                    numericalV = std::pow(values.top(), numericalV);
                    values.pop();
                }
                else if(op == "max") {
                    numericalV = std::max(values.top(),numericalV);
                    values.pop();
                }
                else if(op == "min") {
                    numericalV = std::min(values.top(),numericalV);
                    values.pop();
                }
                else if(op == "sin") {
                    numericalV = std::sin(numericalV);
                }
                else if(op == "cos") {
                    numericalV = std::cos(numericalV);
                }
                else if(op == "sqrt") {
                    numericalV = std::sqrt(numericalV);
                }
                else if(op == "ln") {
                    numericalV = std::log(numericalV);
                }
                values.push(numericalV);
            }
            else {
                double numericalV;
                try{
                    numericalV = std::stod(elem);
                    values.push(numericalV);
                }catch(std::exception& ex) {
                    std::cerr << "Nešto nije u redu. Nisam mogao obraditi: " << elem << '\n';
                }
            }
        }
        return values.top();
    }
}
