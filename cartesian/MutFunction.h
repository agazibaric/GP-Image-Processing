#ifndef CARTESIAN_MUTFUNCTION_H
#define CARTESIAN_MUTFUNCTION_H
#include <ECF/ECF_base.h>
#include "../utility/utilityrng.h"
namespace cartesian{
    class MutateFunction : public MutationOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mutate(GenotypeP gene);

    };
    using MutateFunctionNonSilentP = boost::shared_ptr<MutateFunction>;
}
#endif //CARTESIAN_MUTFUNCTION_H
