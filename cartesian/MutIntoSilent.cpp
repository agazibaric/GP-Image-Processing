#include <set>
#include "MutIntoSilent.h"
#include "Cartesian_genotype.h"
#include "FunctionSet.h"
namespace cartesian{
    void MutateIntoSilent::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "mut.tosilent", (voidP) new double(0), ECF::DOUBLE);
    }

    bool MutateIntoSilent::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "mut.tosilent");
        probability_ = *((double*)sptr.get());
        return true;
    }

    bool MutateIntoSilent::mutate(GenotypeP gene)
    {
        auto cartesian = (Cartesian*) gene.get();
        //First random output is chosen. Trail which decides the output will be mutated.
        uint whichOutput = rng::get_unifrom_random_uint(0, cartesian->nOutputs - 1);
        auto activeTrail = cartesian->getActiveTrail(whichOutput);
    //    std::cout << "Mut into silent CP 1.\n";
        uint whoIsMutated = activeTrail[rng::get_unifrom_random_uint(0, activeTrail.size() - 1)];
        //Now, indexes of silent nodes are needed. Only silent nodes before whoIsMutated are needed.
        std::set<uint> allActiveIndexes;
     //   std::cout << "Započeo Mut into silent.\n";
        auto allTrails = cartesian->getActiveTrails();
     //   std::cout << "Mut into silent CP 2.\n";
        for(const auto& trail : allTrails) {
            for(const auto& elem : trail) {
                if(elem < whoIsMutated) {
                    allActiveIndexes.insert(elem);
                }
            }
        }
        if(allTrails.empty()){
            return true;
        }
        if(allActiveIndexes.size() == cartesian->size() - cartesian->nOutputs) {
            return true;
        }
        uint rowNumber = cartesian->getRowNumber(whoIsMutated);
        uint newConnection = cartesian->randomConnectionGenerator(rowNumber);
        auto allPossibleConnections = cartesian->allPossibleConnection(rowNumber);
     //   std::cout << "Mut into silent CP 3.\n";
        for(const auto& activeIndex : allActiveIndexes) {
            allPossibleConnections.erase(activeIndex);
        }
        if(allPossibleConnections.empty()) {
            return true;
        }
        while(allActiveIndexes.count(newConnection)) {
           // std::cout << "Mut into silent zapeo.\n";
            newConnection = cartesian->randomConnectionGenerator(rowNumber);
        }
        for(const auto& element : activeTrail) {
            auto& cg = cartesian->operator[](element);
            if(element + cartesian->nInputs > newConnection) {
                for(unsigned int & inputConnection : cg.inputConnections) {
                    if(inputConnection == whoIsMutated) {
                        inputConnection = newConnection;
                    }
                }
            }
        }
        return true;
    }
}
