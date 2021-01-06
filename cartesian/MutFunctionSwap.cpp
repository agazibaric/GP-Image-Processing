#include "MutFunctionSwap.h"
#include "Cartesian_genotype.h"
#include "FunctionSet.h"
namespace cartesian{

    void MutateFunctionSwap::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "mut.funcswap", (voidP) new double(0), ECF::DOUBLE);
    }

    bool MutateFunctionSwap::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "mut.funcswap");
        probability_ = *((double*)sptr.get());
        return true;
    }

    bool MutateFunctionSwap::mutate(GenotypeP gene)
    {
        auto cartesian = (Cartesian*) gene.get();
        const auto& vRef = cartesian->functionSet_->vActiveFunctions_;
        //Generate two indexes of functions which will be swapped. Functions must have same number of operands.
        std::uniform_int_distribution<uint> distribution(0, cartesian->size() - 1 - cartesian->nOutputs);
        uint firstIndex = rng::get_unifrom_random_uint(distribution);
        uint secondIndex = rng::get_unifrom_random_uint(distribution);
        uint firstFunction = cartesian->operator[](firstIndex).value;
        uint secondFunction = cartesian->operator[](secondIndex).value;
        uint firstNoOfArgs = vRef[firstFunction]->getNumOfArgs();
        uint secondNoOfArgs = vRef[secondFunction]->getNumOfArgs();
        while(firstNoOfArgs != secondNoOfArgs) {
//            std::cout << "Mut func swap zapeo.\n";
            secondIndex = rng::get_unifrom_random_uint(distribution);
            secondFunction = cartesian->operator[](secondIndex).value;
            secondNoOfArgs = vRef[secondFunction]->getNumOfArgs();
        }
        cartesian->operator[](firstIndex).value = secondFunction;
        cartesian->operator[](secondIndex).value = firstFunction;
        return true;
    }
}
