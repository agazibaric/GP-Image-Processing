#ifndef CARTESIAN_MED8_H
#define CARTESIAN_MED8_H
#include "Function.h"
namespace cartesian{
    template <typename Container, typename Result>
    class Med8 : public Function<Container,Result> {
    public:
        Med8();
        ~Med8() = default;
        void evaluate(const Container& container, Result& result) override;
    };

    template <typename Container, typename Result>
    Med8<Container,Result>::Med8()
    {
        this->name_ = "med8";
        this->numOfArgs_ = 8;
    }

    template <typename Container, typename Result>
    void Med8<Container,Result>::evaluate(const Container& container, Result& result)
    {
        result = Result{};
        std::vector<double> v;
        for(auto it = container.cbegin(); it != container.cbegin() + this->numOfArgs_; it++) {
            v.push_back(*it);
        }
        
        size_t n = v.size() / 2;
        std::nth_element(v.begin(), v.begin()+n, v.end());
        result =  v[n];
    }
}
#endif //CARTESIAN_MED8_H
