#ifndef CARTESIAN_ABS_H
#define CARTESIAN_ABS_H
#include "Function.h"
namespace cartesian {
    template <typename Container, typename Result>
    class Abs : public Function<Container, Result> {
    public:
        Abs();
        ~Abs() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Abs<Container, Result>::Abs()
    {
        this->name_ = "abs";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Abs<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        result = std::abs(*it);
    }
}
#endif //CARTESIAN_ABS_H
