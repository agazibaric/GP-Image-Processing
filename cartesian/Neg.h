#ifndef CARTESIAN_NEG_H
#define CARTESIAN_NEG_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Neg : public Function<Container,Result> {
    public:
        Neg();
        ~Neg() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Neg<Container,Result>::Neg()
    {
        this->name_ = "neg";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Neg<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        result = -1 * (*it);
    }
}
#endif //CARTESIAN_NEG_H
