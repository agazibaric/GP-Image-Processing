#ifndef CARTESIAN_MUTCONNECTION_H
#define CARTESIAN_MUTCONNECTION_H
#include "ecf/ECF_base.h"
#include "../utility/utilityrng.h"
namespace cartesian{
    class MutateConnection : public MutationOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mutate(GenotypeP gene);
    };
    using MutateConnectionP = boost::shared_ptr<MutateConnection>;
}
#endif //CARTESIAN_MUTCONNECTION_H
