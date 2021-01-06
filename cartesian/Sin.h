#ifndef CARTESIAN_SIN_H
#define CARTESIAN_SIN_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Sin : public Function<Container,Result> {
    public:
        Sin();
        ~Sin() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Sin<Container,Result>::Sin()
    {
        this->name_ = "sin";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Sin<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        result = std::sin(*it);
    }
}
#endif //CARTESIAN_SIN_H
