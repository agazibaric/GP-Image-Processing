#ifndef CARTESIAN_CARTESIANCRXUNIFORM_H
#define CARTESIAN_CARTESIANCRXUNIFORM_H
#include <ECF/ECF_base.h>
namespace cartesian {
    class CartesianCrxUniform: public CrossoverOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child);
    };
    using CartesianCrxUniformP = boost::shared_ptr<CartesianCrxUniform>;
}
#endif //CARTESIAN_CARTESIANCRXUNIFORM_H
