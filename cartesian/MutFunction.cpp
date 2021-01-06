#include "MutFunction.h"
#include "Cartesian_genotype.h"
#include "FunctionSet.h"
namespace cartesian{

    void MutateFunction::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "mut.func", (voidP) new double(0), ECF::DOUBLE);
    }

    bool MutateFunction::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "mut.func");
        probability_ = *((double*)sptr.get());
        return true;
    }

    bool MutateFunction::mutate(GenotypeP gene)
    {
        auto cartesian = (Cartesian*) gene.get();
        const auto& vRef = cartesian->functionSet_->vActiveFunctions_;

        //First a random output is chosen. A function that affects this output will be mutated.
        uint whichOutput = rng::get_unifrom_random_uint(0, cartesian->nOutputs - 1);
        auto trail = cartesian->getActiveTrail(whichOutput);
        uint whoIsMutated = trail[rng::get_unifrom_random_uint(0, trail.size() - 1)];
        uint oldFunctionId = cartesian->operator[](whoIsMutated).value;
        uint oldNumOfArgs = vRef[oldFunctionId]->getNumOfArgs();

        std::uniform_int_distribution<uint> allFunctions(0, vRef.size() - 1);
        uint newFunctionId = rng::get_unifrom_random_uint(allFunctions);
        while(newFunctionId == oldFunctionId) {
            newFunctionId = rng::get_unifrom_random_uint(allFunctions);
        }
        uint newNumOfArgs = vRef[newFunctionId]->getNumOfArgs();

        //Assign a new function to the node.
        cartesian->operator[](whoIsMutated).value = newFunctionId;

        //old and new function may not have the same amount of operators.
        if(oldNumOfArgs < newNumOfArgs){
            uint rowNumber = cartesian->getRowNumber(whoIsMutated);
            while(oldNumOfArgs < newNumOfArgs) {
//                std::cout << "MUTFUNC while if zapeo.\n";
                uint connection = cartesian->randomConnectionGenerator(rowNumber);
                cartesian->operator[](whoIsMutated).inputConnections.push_back(connection);
                oldNumOfArgs++;
            }
        }
        else if(oldNumOfArgs > newNumOfArgs) {
            while(oldNumOfArgs > newNumOfArgs) {
//                std::cout << "MUTFUNC while else if zapeo.\n";
                uint connection = rng::get_unifrom_random_uint(0, oldNumOfArgs - 1);
                cartesian->operator[](whoIsMutated).inputConnections.erase(cartesian->operator[](whoIsMutated).inputConnections.cbegin() + connection);
                oldNumOfArgs--;
            }
        }
        return true;
    }
}
