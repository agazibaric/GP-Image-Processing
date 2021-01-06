#ifndef CARTESIAN_RSQRT_H
#define CARTESIAN_RSQRT_H
#include "Function.h"
namespace cartesian {

    template <typename Container, typename Result>
    class RSqrt : public Function<Container, Result> {
    public:
        RSqrt();
        ~RSqrt() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    RSqrt<Container, Result>::RSqrt()
    {
        this->name_ = "rsqrt";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void RSqrt<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = *(container.cbegin());
        auto it = container.cbegin();
        if (std::isnan(*it) || std::isinf(*it)) {
            result = 1;
        }
        else if (*it < 0) {
            result = 1. / std::sqrt(std::abs(*it));
        }
        else {
            result = 1. / std::sqrt(*it);
        }
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_RSQRT_H
