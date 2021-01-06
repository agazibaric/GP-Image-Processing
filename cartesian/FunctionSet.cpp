#include "FunctionSet.h"
namespace cartesian{
    FunctionSet::FunctionSet()
    {

    }

    bool FunctionSet::initialize(StateP state)
    {
        this->state_ = std::move(state);
        //+,-,*,/,ln,sqrt,sin,cos,step,neg,max,min,nop,avg

        FunctionP_basic function = (FunctionP_basic) (new Add<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Sub<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Mul<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Div<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Nlog<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Sqrt<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Step<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Neg<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Sin<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Cos<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Max<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Min<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic) (new Sq_exp<std::vector<double>,double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Nop<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Avg<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Abs<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Ceil<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Floor<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Frac<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Rec<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new RSqrt<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Sigm<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));

        function = (FunctionP_basic)(new Ramp<std::vector<double>, double>);
        mAllFunctions_.insert(std::make_pair(function->getName(), function));
        return true;
    }

    bool FunctionSet::addFunction(const std::string &name)
    {
        auto result = mAllFunctions_.find(name);
        if(result == mAllFunctions_.end()) {
            return false;
        }
        vActiveFunctions_.push_back(result->second);
        mActiveFunctions_.insert(std::make_pair(name,result->second));
        return true;
    }
}
