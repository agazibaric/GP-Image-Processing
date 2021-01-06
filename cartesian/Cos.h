#ifndef CARTESIAN_COS_H
#define CARTESIAN_COS_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Cos : public Function<Container,Result> {
    public:
        Cos();
        ~Cos() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Cos<Container,Result>::Cos()
    {
        this->name_ = "cos";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Cos<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        result = std::cos(*it);
    }
}
#endif //CARTESIAN_COS_H
