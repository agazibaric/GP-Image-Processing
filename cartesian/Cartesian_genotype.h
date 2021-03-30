#ifndef CARTESIAN_GENOTYPE_H
#define CARTESIAN_GENOTYPE_H
#include <vector>
#include <set>
#include <ECF/ECF_base.h>
#include <ECF/Genotype.h>
#include "CartesianGene.h"
#include "../utility/utilityrng.h"
namespace cartesian
{
    //Forward declare function set.
    class FunctionSet;
    using FunctionSetP = boost::shared_ptr<FunctionSet>;
    class Cartesian : public std::vector<CartesianGene>, public Genotype
    {
    public:
        Cartesian(void);
        ~Cartesian(void) = default;

        /**
         * Initialize a genotype object (read parameters, perform sanity check, build data)
         */
        bool initialize(StateP state);
        /**
	    * Create an identical copy of the genotype object
	    */
        Cartesian* copy();

        /**
         * Create and return a vector of crossover operators
         */
        vector<CrossoverOpP> getCrossoverOp();

        /**
         * Create and return a vector of mutation operators
         */
        vector<MutationOpP> getMutationOp();

        /**
         * Register genotype's parameters (called before Genotype::initialize)
         */
        void registerParameters(StateP state);

        /**
         * Read genotype data from XMLNode
         */
        void read(XMLNode &xCart);

        /**
         * Write genotype data to XMLNode
         */
        void write(XMLNode &xCart);

        uint getRowNumber(uint index);

        uint getGenomeSize();

        uint randomConnectionGenerator(uint rowNumber);

        uint randomOutput();

        std::set<uint> allPossibleConnection(uint rowNumber);

        /**
        Build random genotype choosing input connections, outputs and functions
        */
        void buildRandomGenome();

        /**
       * Returns a vector of integers which contain indexes of elements of genotype.
         * These indexes are those operators which make connection from
         * and output (specified with output_number) to inputs.
       */
        std::vector<uint> getActiveTrail(uint output_number);

        /**
         * Returns all trails.
         */
        std::vector<std::vector<uint>> getActiveTrails();

        /**
        Return result for required inputs (optional: from node with index funcNum)
        */
        void evaluate(const vector<double>& inputData, vector<double>& results);

        std::string toStringActiveNodes(uint output_number);
        std::string toStringAllActiveNodes();

    public:
        StateP state_;					//!< local copy of state

        // user defined parameters
        uint nVariables;				//!< number of input variables
        uint nConstants;				//!< number of input constants
        uint nOutputs;					//!< number of final outputs
        uint nRows;						//!< number of rows
        uint nCols;						//!< number of columns
        uint nLevelsBack;				//!< levels back parameter
        uint nFunctions;				//!< number of functions

        // derived parameters
        uint nInputs;					//!< total number of inputs (including constants)
        uint maxArity;					//!< max number of inputs for all function nodes (gates)

        FunctionSetP functionSet_;
        vector<double> constantSet;
    };
}
using CartesianP = boost::shared_ptr<cartesian::Cartesian>;
#endif //CARTESIAN_GENOTYPE_H
