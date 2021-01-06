#ifndef CARTESIAN_MUTINTOSILENT_H
#define CARTESIAN_MUTINTOSILENT_H
#include "ecf/ECF_base.h"
#include "../utility/utilityrng.h"
namespace cartesian{
    class MutateIntoSilent : public MutationOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mutate(GenotypeP gene);
    };
    using MutateIntoSilentP = boost::shared_ptr<MutateIntoSilent>;
}
#endif //CARTESIAN_MUTINTOSILENT_H