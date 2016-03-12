#ifndef SUI_STLCONTAINER
#define SUI_STLCONTAINER
#include<stdexcept>
namespace mystl
{
	template<class T>
	class Container
	{
		public:
			class iterator;
			class const_iterator;
			class iterator_base
			{
				public:
					virtual const T* true_address() const = 0;
			};
			class const_iterator : public iterator_base
			{
				public:
					virtual const_iterator& operator++() = 0;
					//virtual const_iterator operator++(int n) = 0;
					virtual const T& operator*() const = 0;
			};
			class iterator : public iterator_base
			{
				public:
					virtual iterator& operator++() = 0;
					//virtual iterator operator++(int n) = 0;
					virtual T& operator*() const = 0;
			};
			virtual bool empty() = 0;
			virtual size_t size() const = 0;
			virtual void clear() = 0;
			virtual ~Container() {}
	};

};
#endif 