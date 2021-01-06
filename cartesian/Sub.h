#ifndef CARTESIAN_SUB_H
#define CARTESIAN_SUB_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Sub : public Function<Container,Result> {
    public:
        Sub();
        ~Sub() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Sub<Container,Result>::Sub()
    {
        this->name_ = "-";
        this->numOfArgs_ = 2;
    }

    template <typename Container, typename Result>
    void Sub<Container,Result>::evaluate(const Container& container, Result& result) {
        result = *container.cbegin();
        for(auto it = container.cbegin() + 1; it != container.cbegin() + this->numOfArgs_; it++)
        {
            result -= *it;
        }
    }
}
#endif //CARTESIAN_SUB_H
