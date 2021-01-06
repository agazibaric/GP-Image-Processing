#include "CartesianCrxHalfUniform.h"
#include "Cartesian_genotype.h"
namespace cartesian{

    void CartesianCrxHalfUniform::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "crx.halfuniform", (voidP) new double(0), ECF::DOUBLE);
    }

    bool CartesianCrxHalfUniform::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "crx.halfuniform");
        probability_ = *((double*)sptr.get());
        return true;
    }

    bool CartesianCrxHalfUniform::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
    {
        auto p1 = (Cartesian*) gen1.get();
        auto p2 = (Cartesian*) gen2.get();
        auto ch = (Cartesian*) child.get();

        uint parent1Size = p1->size() - p1->nOutputs;
        uint parent2Size = p2->size() - p2->nOutputs;
        uint minimumSize = parent1Size > parent2Size ? parent1Size : parent2Size;
        bool parent1IsLonger = parent1Size > parent2Size;
        ch->clear();

        std::uniform_real_distribution<double> distribution(0,1.0);
        double whichParent = rng::get_uniform_random_double(distribution);
        double whichPart = rng::get_uniform_random_double(distribution);
        uint crossoverStart = 0;
        uint crossoverEnd = minimumSize/2;
        uint start = crossoverEnd;
        uint end = minimumSize;
        bool keepFirst = false;
        if(whichPart >= 0.5) {
            start = 0;
            end = minimumSize/2;
            crossoverStart = end;
            crossoverEnd = minimumSize;
            keepFirst = true;
        }
        if(whichParent < 0.5) {
            if(keepFirst) {
                for(uint i = start; i < end; i++){
                    ch->push_back(p1->operator[](i));
                }
                for(uint i = crossoverStart; i < crossoverEnd; i++) {
                    double randomResult = rng::get_uniform_random_double(distribution);
                    if(randomResult < 0.5) {
                        ch->push_back(p1->operator[](i));
                    }
                    else {
                        ch->push_back(p2->operator[](i));
                    }
                }
            }
            else {
                for(uint i = crossoverStart; i < crossoverEnd; i++) {
                    double randomResult = rng::get_uniform_random_double(distribution);
                    if(randomResult < 0.5) {
                        ch->push_back(p1->operator[](i));
                    }
                    else {
                        ch->push_back(p2->operator[](i));
                    }
                }
                for(uint i = start; i < end; i++){
                    ch->push_back(p1->operator[](i));
                }
            }
        }
        else {
           if(keepFirst) {
               for(uint i = start; i < end; i++){
                   ch->push_back(p2->operator[](i));
               }
               for(uint i = crossoverStart; i < crossoverEnd; i++) {
                   double randomResult = rng::get_uniform_random_double(distribution);
                   if(randomResult < 0.5) {
                       ch->push_back(p1->operator[](i));
                   }
                   else {
                       ch->push_back(p2->operator[](i));
                   }
               }
           }
           else {
               for(uint i = crossoverStart; i < crossoverEnd; i++) {
                   double randomResult = rng::get_uniform_random_double(distribution);
                   if(randomResult < 0.5) {
                       ch->push_back(p1->operator[](i));
                   }
                   else {
                       ch->push_back(p2->operator[](i));
                   }
               }
               for(uint i = start; i < end; i++){
                   ch->push_back(p2->operator[](i));
               }
           }
        }
        if(parent1IsLonger) {
            for(uint i = parent2Size; i < parent1Size; i++) {
                ch->push_back(p1->operator[](i));
            }
        }
        else{
            for(uint i = parent1Size; i < parent2Size; i++) {
                ch->push_back(p1->operator[](i));
            }
        }
        //Resolve outputs.
        for(uint i = 0; i < p1->nOutputs; i++) {
            if(whichParent < 0.5) {
                ch->push_back(p1->operator[](parent1Size + i));
            }
            else {
                ch->push_back(p1->operator[](parent2Size + i));
            }
        }
        return true;
    }
}