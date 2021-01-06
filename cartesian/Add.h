#ifndef CARTESIAN_ADD_H
#define CARTESIAN_ADD_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Add : public Function<Container,Result> {
    public:
        Add();
        ~Add() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Add<Container,Result>::Add()
    {
        this->name_ = "+";
        this->numOfArgs_ = 2;
    }

    template <typename Container, typename Result>
    void Add<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        for(auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            result += *it;
        }
    }
}
#endif //CARTESIAN_ADD_H
