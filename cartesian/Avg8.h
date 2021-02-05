#ifndef CARTESIAN_AVG8_H
#define CARTESIAN_AVG8_H
#include "Function.h"
namespace cartesian {
    template <typename Container, typename Result>
    class Avg8 : public Function<Container, Result> {
    public:
        Avg8();
        ~Avg8() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Avg8<Container, Result>::Avg8()
    {
        this->name_ = "avg8";
        this->numOfArgs_ = 8;
    }

    template <typename Container, typename Result>
    void Avg8<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        for (auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            result += *it;
        }
        result /= this->numOfArgs_;
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_AVG8_H
