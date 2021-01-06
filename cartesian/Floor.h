#ifndef CARTESIAN_FLOOR_H
#define CARTESIAN_FLOOR_H
#include "Function.h"
namespace cartesian {

    template <typename Container, typename Result>
    class Floor : public Function<Container, Result> {
    public:
        Floor();
        ~Floor() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Floor<Container, Result>::Floor()
    {
        this->name_ = "floor";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Floor<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = *(container.cbegin());
        auto it = container.cbegin();
        result = std::floor(*it);
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_FLOOR_H
