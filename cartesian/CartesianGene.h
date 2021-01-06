#ifndef SEMINAR_CARTESIANGENE_H
#define SEMINAR_CARTESIANGENE_H
#include <vector>
#include <iostream>
namespace cartesian{
    struct CartesianGene{
        CartesianGene() = default;
        CartesianGene(uint value_, std::vector<uint> inputConnections_, bool isOutput_ = false) :
                value{value_}, inputConnections{std::move(inputConnections_)}, isOutput{isOutput_} {};
        //value is ID of a function if CartesianGene is not an output node
        //If it is, value is index of a node (inside Cartesian) whose output
        //is forwarded to value.
        //Suggestion: Replace with union;
        uint value;
        std::vector<uint> inputConnections;
        bool isOutput;
        friend std::ostream& operator<<(std::ostream& out, const CartesianGene& cg) {
            out << cg.value << ' ';
            if(!cg.isOutput) {
                for(const auto& elem : cg.inputConnections) {
                    out << elem << ' ';
                }
            }
            return out;
        }
    };
}
#endif //SEMINAR_CARTESIANGENE_H
