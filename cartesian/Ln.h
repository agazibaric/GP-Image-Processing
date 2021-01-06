#ifndef CARTESIAN_LN_H
#define CARTESIAN_LN_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Nlog : public Function<Container,Result> {
    public:
        Nlog();
        ~Nlog() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Nlog<Container,Result>::Nlog()
    {
        this->name_ = "ln";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Nlog<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        if(std::isnan(*it) || std::isinf(*it) || *it == 0) {
            result = 1.0;
        }
        else if(*it < 0.0) {
            result = std::log(std::abs(*it));
        }
        else {
            result = std::log(*it);
        }
    }
}
#endif //CARTESIAN_LN_H
