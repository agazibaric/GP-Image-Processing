#ifndef CARTESIAN_MUL_H
#define CARTESIAN_MUL_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Mul : public Function<Container,Result> {
    public:
        Mul();
        ~Mul() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Mul<Container,Result>::Mul()
    {
        this->name_ = "*";
        this->numOfArgs_ = 2;
    }

    template <typename Container, typename Result>
    void Mul<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        for(auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            result *= *it;
        }
    }
}
#endif //CARTESIAN_MUL_H
