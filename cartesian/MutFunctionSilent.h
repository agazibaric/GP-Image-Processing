#ifndef CARTESIAN_MUTFUNCTIONSILENT_H
#define CARTESIAN_MUTFUNCTIONSILENT_H
#include "ecf/ECF_base.h"
#include "../utility/utilityrng.h"
namespace cartesian{
    class MutateFunctionSilent : public MutationOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mutate(GenotypeP gene);
    };
    using MutateFunctionSilentP = boost::shared_ptr<MutateFunctionSilent>;
}
#endif //CARTESIAN_MUTFUNCTIONSILENT_H
