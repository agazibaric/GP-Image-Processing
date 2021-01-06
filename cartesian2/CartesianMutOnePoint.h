#ifndef CartesianMutOnePoint_h
#define CartesianMutOnePoint_h

#include "ecf/ECF_base.h"


namespace CGP {
/**
 * \brief Cartesian genotype: one point mutation operator
 */
class CartesianMutOnePoint: public MutationOp 
{
protected:
	double mutProb_;

public:
	/**
	Mutation point is randomly chosen among all integer values in genotype.
	Chosen mutation point might be input connection, function or output. 
	Predetermined rules are applied in order to obtain valid genotype by mutation.
	*/
	bool mutate(GenotypeP gene);
	bool initialize(StateP);
	void registerParameters(StateP);
};
typedef boost::shared_ptr<CartesianMutOnePoint> CartesianMutOnePointP;

}

#endif /* CartesianMutOnePoint_h */