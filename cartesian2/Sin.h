#ifndef Sin_h
#define Sin_h
#include "Function.h"

namespace CGP
{
    template <class T>
    class SinT: public Function
    {
    public:
        SinT();
        ~SinT();

        void evaluate(std::vector<T>& inputs, T& result);
    };

    typedef SinT<double> Sin;
    template <class T>
    SinT<T>::SinT()
    {
        name_ = "sin";
        nArguments_ = 1;
    }

    template <class T>
    SinT<T>::~SinT()
    {}

    template <class T>
    void SinT<T>::evaluate(vector<T> &inputs, T &result)
    {
        result = sin(inputs[0]);
    }
}
#endif //Sin_h
