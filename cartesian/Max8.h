#ifndef CARTESIAN_MAX8_H
#define CARTESIAN_MAX8_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Max8 : public Function<Container,Result> {
    public:
        Max8();
        ~Max8() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Max8<Container,Result>::Max8()
    {
        this->name_ = "max8";
        this->numOfArgs_ = 8;
    }

    template <typename Container, typename Result>
    void Max8<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        for(auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            result = (*it) > result ? (*it) : result;
        }
    }
}
#endif //CARTESIAN_MAX8_H
