#ifndef CartesianMutSilent_h
#define CartesianMutSilent_h

#include "ecf/ECF_base.h"


namespace CGP {
	/**
	 * \brief Cartesian genotype: one point mutation operator
	 */
	class CartesianMutSilent : public MutationOp
	{
	protected:
		double mutProb_;

	public:
		/**
		Silent mutation chooses one silent node (if there is one) and mutates its inputs.
		When silent mutation is performed silent node that is mutated remains silent.
		*/
		bool mutate(GenotypeP gene);
		bool initialize(StateP);
		void registerParameters(StateP);
	};
	typedef boost::shared_ptr<CartesianMutSilent> CartesianMutSilentP;

}

#endif /* CartesianMutSilent_h */