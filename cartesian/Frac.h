#ifndef CARTESIAN_FRAC_H
#define CARTESIAN_FRAC_H
#include "Function.h"
namespace cartesian {

    template <typename Container, typename Result>
    class Frac : public Function<Container, Result> {
    public:
        Frac();
        ~Frac() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Frac<Container, Result>::Frac()
    {
        this->name_ = "frac";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Frac<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = *(container.cbegin());
        auto it = container.cbegin();
        result = (*it) - std::floor(*it);
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_FRAC_H
