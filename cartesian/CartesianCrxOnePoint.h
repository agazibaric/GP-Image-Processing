#ifndef CARTESIAN_CARTESIANCRXONEPOINT_H
#define CARTESIAN_CARTESIANCRXONEPOINT_H
#include <ECF/ECF_base.h>
namespace cartesian {
    class CartesianCrxOnePoint: public CrossoverOp
    {
    public:
        void registerParameters(StateP state);
        bool initialize(StateP state);
        bool mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child);
    };
    using CartesianCrxOnePointP = boost::shared_ptr<CartesianCrxOnePoint>;
}
#endif //SEMINAR_CARTESIANCRXONEPOINT_H
