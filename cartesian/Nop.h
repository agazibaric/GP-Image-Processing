#ifndef CARTESIAN_NOP_H
#define CARTESIAN_NOP_H
#include "Function.h"
namespace cartesian {
    template <typename Container, typename Result>
    class Nop : public Function<Container, Result> {
    public:
        Nop();
        ~Nop() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Nop<Container, Result>::Nop()
    {
        this->name_ = "nop";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Nop<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        result = *it;
    }
}
#endif //CARTESIAN_NOP_H
