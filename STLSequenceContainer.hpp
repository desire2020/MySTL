#ifndef SUI_STLSEQCONTAINER
#define SUI_STLSEQCONTAINER
#include "STLContainer.hpp"
namespace mystl
{
	template<class T>
	class SequenceContainer : public Container<T>
	{
		public:
			virtual void push_back(const T& target) = 0;
			virtual void pop_back() = 0;
			virtual const T& back() const = 0;
			virtual const T& front() const = 0;
			class iterator : public Container<T> :: iterator
			{};
			virtual ~SequenceContainer() {}
	};
};
#endif