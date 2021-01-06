#ifndef CARTESIAN_CEIL_H
#define CARTESIAN_CEIL_H
#include "Function.h"
namespace cartesian {

    template <typename Container, typename Result>
    class Ceil : public Function<Container, Result> {
    public:
        Ceil();
        ~Ceil() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Ceil<Container, Result>::Ceil()
    {
        this->name_ = "ceil";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Ceil<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = *(container.cbegin());
        auto it = container.cbegin();
        result = std::ceil(*it);
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_CEIL_H
