#ifndef CARTESIAN_MIN8_H
#define CARTESIAN_MIN8_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Min8 : public Function<Container,Result> {
    public:
        Min8();
        ~Min8() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Min8<Container,Result>::Min8()
    {
        this->name_ = "min8";
        this->numOfArgs_ = 8;
    }

    template <typename Container, typename Result>
    void Min8<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        for(auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            result = (*it) < result ? (*it) : result;
        }
    }
}
#endif //CARTESIAN_MIN8_H
