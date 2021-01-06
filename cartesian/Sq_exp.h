#ifndef CARTESIAN_SQ_EXP_H
#define CARTESIAN_SQ_EXP_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Sq_exp : public Function<Container,Result> {
    public:
        Sq_exp();
        ~Sq_exp() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Sq_exp<Container,Result>::Sq_exp()
    {
        this->name_ = "sq_exp";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Sq_exp<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        result = std::pow(*it,2);
    }
}
#endif //CARTESIAN_SQ_EXP_H
