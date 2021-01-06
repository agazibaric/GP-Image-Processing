#ifndef CARTESIAN_RAMP_H
#define CARTESIAN_RAMP_H
#include "Function.h"
namespace cartesian {
    template <typename Container, typename Result>
    class Ramp : public Function<Container, Result> {
    public:
        Ramp();
        ~Ramp() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Ramp<Container, Result>::Ramp()
    {
        this->name_ = "ramp";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Ramp<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        if (*it < 0) {
            result = 0;
        }
        else {
            result = *it;
        }
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_RAMP_H
