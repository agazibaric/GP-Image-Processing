#ifndef CARTESIAN_DIV_H
#define CARTESIAN_DIV_H
#include "Function.h"
namespace cartesian{
    constexpr double DIVISION_THRESHOLD = 10e-7;
    template <typename Container, typename Result>
    class Div : public Function<Container,Result> {
    public:
        Div();
        ~Div() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Div<Container,Result>::Div()
    {
        this->name_ = "/";
        this->numOfArgs_ = 2;
    }

    template <typename Container, typename Result>
    void Div<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = *(container.cbegin());
        for(auto it = container.cbegin() + 1; it != container.cbegin() + this->numOfArgs_; it++) {
            if(*it <= DIVISION_THRESHOLD) {
                continue;
            }
            result /= *it;
        }
    }
}
#endif //CARTESIAN_DIV_H
