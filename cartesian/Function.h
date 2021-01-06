#ifndef CARTESIAN_FUNCTION_H
#define CARTESIAN_FUNCTION_H
#include "Cartesian_genotype.h"
#include <cmath>
namespace cartesian{
    template <typename Container, typename Result>
    class Function
    {
    public:
        Function() {}
        Function(uint numArgs) {}
        virtual ~Function() {}

        /**
         * Evaluate function could be done in a better way.
         * What it does is it takes inputs to a function node as first argument and result as a second argument.
         *
         * Problem arises because of the following:
         * 1.) Passed input should support an operation which is performed(+, -, *, /). This
         * is not a problem for built-in types, but does create a problem for user-defined types or aggregate-types.
         *
         * 2.) Assuming that input is given as a collection or any stl container, strictly speaking
         * all support needed for first argument is to be able to iterate over it.
         *
         * For general usage, abstract function evaluate could be defined as:
         * virtual void evaluate(voidP inputs, void* result) = 0;
         *
         * However this would require that concrete functions (derived classes of Function) know
         * in what to cast voidP and void*. This could be achieved using class templates.
         * Still, user would have to know in what to cast inputs.
         *
         * I opted for a solution of making base-class a template class, and arguments
         * of evaluate function container and a result.
         *
         * Solution I like the most (once C++ 2020 is supported by compilers) is
         * to use concepts, and scrape inheritance completely.
         * */

        virtual void evaluate(const Container& container, Result& result) = 0;

        std::string getName()
        {
            return name_;
        }

        uint getNumOfArgs()
        {
            return numOfArgs_;
        }

    protected:
        std::string name_;
        uint numOfArgs_;
    };

    //FunctionP_basic, assumes that container is a std::vector<double>, and obviously result is a double.
    using FunctionP_basic = boost::shared_ptr<Function<std::vector<double>,double>>;
}
#endif //CARTESIAN_FUNCTION_H
