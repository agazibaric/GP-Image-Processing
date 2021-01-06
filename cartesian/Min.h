#ifndef CARTESIAN_MIN_H
#define CARTESIAN_MIN_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Min : public Function<Container,Result> {
    public:
        Min();
        ~Min() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Min<Container,Result>::Min()
    {
        this->name_ = "min";
        this->numOfArgs_ = 2;
    }

    template <typename Container, typename Result>
    void Min<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = *container.cbegin();
        for(auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            result = (*it) > result ? result : (*it);
        }
    }
}
#endif //CARTESIAN_MIN_H
