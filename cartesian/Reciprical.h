#ifndef CARTESIAN_REC_H
#define CARTESIAN_REC_H
#include "Function.h"
namespace cartesian {

    template <typename Container, typename Result>
    class Rec : public Function<Container, Result> {
    public:
        Rec();
        ~Rec() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Rec<Container, Result>::Rec()
    {
        this->name_ = "rec";
        this->numOfArgs_ = 1;
    }

    template <typename Container, typename Result>
    void Rec<Container, Result>::evaluate(const Container& container, Result& result)
    {
        result = *(container.cbegin());
        auto it = container.cbegin();
        result = 1. / *it;
        if (std::isnan(result) || std::isinf(result)) {
            result = 1;
        }
    }
}
#endif //CARTESIAN_REC_H
