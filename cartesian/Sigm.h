#ifndef CARTESIAN_SIGM_H
#define CARTESIAN_SIGM_H
#include "Function.h"
namespace cartesian {
    template <typename Container, typename Result>
    class Sigm : public Function<Container, Result> {
    public:
        Sigm();
        ~Sigm() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Sigm<Container, Result>::Sigm()
    {
        this->name_ = "sigm";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Sigm<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        auto it = container.cbegin();
        result = 1. / (1. + std::exp(-(*it)));
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_SIGM_H
