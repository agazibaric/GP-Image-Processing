#ifndef CARTESIAN_CARTESIANCRXHALFUNIFORM_H
#define CARTESIAN_CARTESIANCRXHALFUNIFORM_H
#include <ECF/ECF_base.h>

namespace cartesian {
    class CartesianCrxHalfUniform: public CrossoverOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state) ;
        bool mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child);
    };
    using CartesianCrxHalfUniformP = boost::shared_ptr<CartesianCrxHalfUniform>;
}
#endif //CARTESIAN_CARTESIANCRXHALFUNIFORM_H
