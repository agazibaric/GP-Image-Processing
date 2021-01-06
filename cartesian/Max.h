#ifndef CARTESIAN_MAX_H
#define CARTESIAN_MAX_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Max : public Function<Container,Result> {
    public:
        Max();
        ~Max() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Max<Container,Result>::Max()
    {
        this->name_ = "max";
        this->numOfArgs_ = 2;
    }

    template <typename Container, typename Result>
    void Max<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        for(auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            result = (*it) > result ? (*it) : result;
        }
    }
}
#endif //CARTESIAN_MAX_H
