#ifndef SEMINAR_MUTFUNCTIONSWAP_H
#define SEMINAR_MUTFUNCTIONSWAP_H
#include <ECF/ECF_base.h>
#include "../utility/utilityrng.h"
namespace cartesian{
    class MutateFunctionSwap : public MutationOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mutate(GenotypeP gene);
    };
    using MutateFunctionSwapP = boost::shared_ptr<MutateFunctionSwap>;
}
#endif //SEMINAR_MUTFUNCTIONSWAP_H
