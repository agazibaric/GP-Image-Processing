#ifndef CARTESIAN_MUTCONNECTIONSILENT_H
#define CARTESIAN_MUTCONNECTIONSILENT_H
#include "ecf/ECF_base.h"
#include "../utility/utilityrng.h"
namespace cartesian{
    class MutateConnectionSilent : public MutationOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mutate(GenotypeP gene);
    };
    using MutateConnectionSilentP = boost::shared_ptr<MutateConnectionSilent>;
}
#endif //CARTESIAN_MUTCONNECTIONSILENT_H