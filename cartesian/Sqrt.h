#ifndef CARTESIAN_SQRT_H
#define CARTESIAN_SQRT_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Sqrt : public Function<Container,Result> {
    public:
        Sqrt();
        ~Sqrt() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Sqrt<Container,Result>::Sqrt()
    {
        this->name_ = "sqrt";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Sqrt<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        if(std::isnan(*it) || std::isinf(*it)) {
            result = 0.;
        }
        else if(*it < 0.0) {
            result = std::sqrt(std::abs(*it));
        }
        else {
            result = std::sqrt(*it);
        }
        if (std::isnan(result) || std::isinf(result)) {
            result = 0.;
        }
    }
}
#endif //CARTESIAN_SQRT_H
