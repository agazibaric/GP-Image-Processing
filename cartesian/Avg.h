#ifndef CARTESIAN_AVG_H
#define CARTESIAN_AVG_H
#include "Function.h"
namespace cartesian {
    template <typename Container, typename Result>
    class Avg : public Function<Container, Result> {
    public:
        Avg();
        ~Avg() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Avg<Container, Result>::Avg()
    {
        this->name_ = "avg";
        this->numOfArgs_ = 2;
    }

    template <typename Container, typename Result>
    void Avg<Container, Result>::evaluate(const Container& container, Result& result)
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
#endif //CARTESIAN_AVG_H
