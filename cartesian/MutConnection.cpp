#include "MutConnection.h"
#include "Cartesian_genotype.h"
#include "FunctionSet.h"
namespace cartesian{
    void MutateConnection::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "mut.connection", (voidP) new double(0), ECF::DOUBLE);
    }

    bool MutateConnection::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "mut.connection");
        probability_ = *((double*)sptr.get());
        return true;
    }

    bool MutateConnection::mutate(GenotypeP gene)
    {
        auto cartesian = (Cartesian*) gene.get();
        const auto& vRef = cartesian->functionSet_->vActiveFunctions_;
        //Connection of which output will be mutated?
        uint whichOutput = rng::get_unifrom_random_uint(0, cartesian->nOutputs - 1);
        auto trail = cartesian->getActiveTrail(whichOutput);
        uint whoIsMutated = trail[rng::get_unifrom_random_uint(0, trail.size() - 1)];
        uint rowNumber = cartesian->getRowNumber(whoIsMutated);
        uint whichConnection = rng::get_unifrom_random_uint(0, vRef[cartesian->operator[](whoIsMutated).value]->getNumOfArgs() - 1);
        uint newConnection = cartesian->randomConnectionGenerator(rowNumber);
        cartesian->operator[](whoIsMutated).inputConnections[whichConnection] = newConnection;
        
        //std::uniform_real_distribution<double> dist(0, 1);
        //std::uniform_int_distribution<uint> functionDist(0, vRef.size() - 1);
        //for (int i = 0, n = cartesian->size() - cartesian->nOutputs; i < n; i++) {
        //    double toMutate = utility::RandomGenerator::get_uniform_random_double(dist);
        //    
        //    if (toMutate < 0.01) {
        //        CartesianGene gene = cartesian->operator[](i);
        //        int geneIndexToMutate = rng::get_unifrom_random_uint(0, gene.inputConnections.size());
        //        if (geneIndexToMutate == gene.inputConnections.size()) {
        //            // Mutate function
        //            uint oldFunctionId = cartesian->operator[](i).value;
        //            uint oldNumOfArgs = vRef[oldFunctionId]->getNumOfArgs();

        //            uint newFunctionId = rng::get_unifrom_random_uint(functionDist);
        //            uint newNumOfArgs = vRef[newFunctionId]->getNumOfArgs();
        //            cartesian->operator[](i).value = newFunctionId;

        //            if (oldNumOfArgs < newNumOfArgs) {
        //                uint rowNumber = cartesian->getRowNumber(i);
        //                while (oldNumOfArgs < newNumOfArgs) {
        //                    //                std::cout << "MUTFUNC while if zapeo.\n";
        //                    uint connection = cartesian->randomConnectionGenerator(rowNumber);
        //                    cartesian->operator[](i).inputConnections.push_back(connection);
        //                    oldNumOfArgs++;
        //                }
        //            }
        //            else if (oldNumOfArgs > newNumOfArgs) {
        //                while (oldNumOfArgs > newNumOfArgs) {
        //                    //                std::cout << "MUTFUNC while else if zapeo.\n";
        //                    uint connection = rng::get_unifrom_random_uint(0, oldNumOfArgs - 1);
        //                    cartesian->operator[](i).inputConnections.erase(cartesian->operator[](i).inputConnections.cbegin() + connection);
        //                    oldNumOfArgs--;
        //                }
        //            }
        //        }
        //        else {
        //            // Mutate input connection
        //            uint rowNumber = cartesian->getRowNumber(i);
        //            uint newConnection = cartesian->randomConnectionGenerator(rowNumber);
        //            cartesian->operator[](i).inputConnections[geneIndexToMutate] = newConnection;
        //        }
        //        
        //    }
        //}
        return true;
    }
}
