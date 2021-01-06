#ifndef Add_h
#define Add_h
#include "Function.h"

namespace CGP
{
	template <class T>
	class AddT : public Function
	{
	public:
		AddT();
		~AddT();

		void evaluate(std::vector<T>& inputs, T& result);
	};

	typedef AddT<double> Add;

	template <class T>
	AddT<T>::AddT()
	{
		name_ = "+";
		nArguments_ = 2;
	}


	template <class T>
	AddT<T>::~AddT()
	{}

	template <class T>
	void AddT<T>::evaluate(std::vector<T>& inputs, T& result)
	{
		double sum = 0;
		for (uint i = 0; i < nArguments_; i++) {
			sum += inputs[i];
		}
		result = sum;
	}

}

#endif /* Add_h */