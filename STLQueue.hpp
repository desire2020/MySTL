#ifndef SUI_STLQUEUE
#define SUI_STLQUEUE
#include "STLDeque.hpp"
namespace mystl
{
	template<class T, class Tlist = deque<T> >
	class queue
	{
		protected:
			Tlist data;
		public:
			queue() { }
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
				data.pop_front();
			}
			inline const T& front()
			{
				return data.front();
			}
			inline void push(const T& target)
			{
				data.push_back(target);
			}
			inline size_t size() const
			{
				return data.size();
			}
			virtual ~queue()
			{
			}
	};
};
#endif