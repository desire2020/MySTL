#ifndef SUI_STLSTACK
#define SUI_STLSTACK
#include "STLDeque.hpp"
namespace mystl
{
	template<class T, class Tlist = deque<T> >
	class stack
	{
		protected:
			Tlist data;
		public:
			stack() { }
			inline void clear()
			{
				data.clear();
			}
			inline bool empty()
			{
				return data.empty();
			}
			inline void pop()
			{
				data.pop_back();
			}
			inline const T& top()
			{
				return data.back();
			}
			inline void push(const T& target)
			{
				data.push_back(target);
			}
			inline size_t size() const
			{
				return data.size();
			}
			virtual ~stack()
			{
			}
	};
};
#endif