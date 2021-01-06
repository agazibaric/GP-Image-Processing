#include <set>
#include "MutConnectionSilent.h"
#include "Cartesian_genotype.h"
#include "FunctionSet.h"
namespace cartesian{
    void MutateConnectionSilent::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "mut.connectionsilent", (voidP) new double(0), ECF::DOUBLE);
    }

    bool MutateConnectionSilent::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "mut.connectionsilent");
        probability_ = *((double*)sptr.get());
        return true;
    }

    bool MutateConnectionSilent::mutate(GenotypeP gene)
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
//            std::cout << "MUTCONSILENT while zapeo.\n";
            toBeMutated = rng::get_unifrom_random_uint(distribution);
        }
        uint oldFunctionId = cartesian->operator[](toBeMutated).value;
        uint rowNumber = cartesian->getRowNumber(toBeMutated);
        uint oldConnection = rng::get_unifrom_random_uint(0, vRef[oldFunctionId]->getNumOfArgs() - 1);
        uint newConnection = cartesian->randomConnectionGenerator(rowNumber);
        cartesian->operator[](toBeMutated).inputConnections[oldConnection] = newConnection;
        return true;
    }
}
