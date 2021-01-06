#ifndef CARTESIAN_FUNCTIONSET_H
#define CARTESIAN_FUNCTIONSET_H
#include "Function.h"
#include "Add.h"
#include "Sub.h"
#include "Mul.h"
#include "Div.h"
#include "Ln.h"
#include "Neg.h"
#include "Sin.h"
#include "Sqrt.h"
#include "Step.h"
#include "Cos.h"
#include "Max.h"
#include "Min.h"
#include "Sq_exp.h"
#include "Nop.h"
#include "Avg.h"
#include "Abs.h"
#include "Ceil.h"
#include "Floor.h"
#include "Frac.h"
#include "Ramp.h"
#include "Reciprical.h"
#include "RSqrt.h"
#include "Sigm.h"

namespace cartesian{
    class FunctionSet{
    public:
        FunctionSet();
        ~FunctionSet() = default;
        bool initialize(StateP state);
        bool addFunction(const std::string& name);

        std::map<std::string,FunctionP_basic> mAllFunctions_;
        std::vector<FunctionP_basic> vActiveFunctions_;
        std::map<std::string,FunctionP_basic> mActiveFunctions_;
        StateP state_;
    };
    using FunctionSetP = boost::shared_ptr<FunctionSet>;
}
#endif //SEMINAR_FUNCTIONSET_H
