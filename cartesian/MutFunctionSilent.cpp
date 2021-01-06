#include <set>
#include "MutFunctionSilent.h"
#include "Cartesian_genotype.h"
#include "FunctionSet.h"
namespace cartesian{

    void MutateFunctionSilent::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "mut.funcsilent", (voidP) new double(0), ECF::DOUBLE);
    }

    bool MutateFunctionSilent::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "mut.funcsilent");
        probability_ = *((double*)sptr.get());
        return true;
    }

    bool MutateFunctionSilent::mutate(GenotypeP gene)
    {
        auto cartesian = (Cartesian*) gene.get();
        const auto& vRef = cartesian->functionSet_->vActiveFunctions_;
        std::set<uint> allActiveIndexes;
        auto allTrails = cartesian->getActiveTrails();
        for(const auto& trail : allTrails) {
            for(const auto& elem : trail) {
                allActiveIndexes.insert(elem);
            }
        }
        std::uniform_int_distribution<uint> distribution(0, cartesian->size() - 1 -cartesian->nOutputs);
        uint toBeMutated = rng::get_unifrom_random_uint(distribution);
        if(allActiveIndexes.size() == cartesian->size() - cartesian->nOutputs) {
            return true;
        }
        while(allActiveIndexes.count(toBeMutated)) {
//            std::cout << "MutFuncSilent 1 while zapeo.\n";
            toBeMutated = rng::get_unifrom_random_uint(distribution);
        }
        uint oldFunctionId = cartesian->operator[](toBeMutated).value;
        uint oldNumOfArgs = vRef[oldFunctionId]->getNumOfArgs();
        std::uniform_int_distribution<uint> allFunctions(0, vRef.size() - 1);
        uint newFunctionId = rng::get_unifrom_random_uint(allFunctions);
        while(newFunctionId == oldFunctionId) {
//            std::cout << "MutFuncSilent 2 while zapeo.\n";
            newFunctionId = rng::get_unifrom_random_uint(allFunctions);
        }
        uint newNumOfArgs = vRef[newFunctionId]->getNumOfArgs();
        //Assign a new function to the node.
        cartesian->operator[](toBeMutated).value = newFunctionId;

        //old and new function may not have the same amount of operators.
        if(oldNumOfArgs < newNumOfArgs){
            uint rowNumber = cartesian->getRowNumber(toBeMutated);
            while(oldNumOfArgs < newNumOfArgs) {
//                std::cout << "MutFuncSilent 3 while zapeo.\n";
                uint connection = cartesian->randomConnectionGenerator(rowNumber);
                cartesian->operator[](toBeMutated).inputConnections.push_back(connection);
                oldNumOfArgs++;
            }
        }
        else if(oldNumOfArgs > newNumOfArgs) {
            while(oldNumOfArgs > newNumOfArgs) {
//                std::cout << "MutFuncSilent 4 while zapeo.\n";
                uint connection = rng::get_unifrom_random_uint(0, oldNumOfArgs - 1);
                cartesian->operator[](toBeMutated).inputConnections.erase(cartesian->operator[](toBeMutated).inputConnections.cbegin() + connection);
                oldNumOfArgs--;
            }
        }
        return true;
    }
}
