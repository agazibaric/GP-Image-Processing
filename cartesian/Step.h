#ifndef CARTESIAN_STEP_H
#define CARTESIAN_STEP_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Step : public Function<Container,Result> {
    public:
        Step();
        ~Step() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Step<Container,Result>::Step()
    {
        this->name_ = "step";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Step<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        if(*it > 0) {
            result = *it;
        }
        result = 0;
    }
}
#endif //CARTESIAN_STEP_H
