#ifndef CartesianMutNonSilent_h
#define CartesianMutNonSilent_h

#include "ecf/ECF_base.h"


namespace CGP {
	/**
	 * \brief Cartesian genotype: one point mutation operator
	 */
	class CartesianMutNonSilent : public MutationOp
	{
	protected:
		double mutProb_;

	public:
		/**
		Non silent mutation transforms silent node (if there is one) into active by
		connecting silentNode to the one of the inputs of the active node 
		(column(activeNode) > column(silentNode)) or by connecting silentNode to the output.
		*/
		bool mutate(GenotypeP gene);
		bool initialize(StateP);
		void registerParameters(StateP);
	};
	typedef boost::shared_ptr<CartesianMutNonSilent> CartesianMutNonSilentP;

}

#endif /* CartesianMutNonSilent_h */