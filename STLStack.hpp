#ifndef SUI_STLSTACK
#define SUI_STLSTACK
#include "STLVector.hpp"
#include "STLList.hpp"
namespace mystl
{
	template<class T, class Tlist = vector<T> >
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
			T pop()
			{
				static T tmp;
				tmp = data.back();
				data.pop_back();
				return tmp;
			}
			inline T top()
			{
				return data.back();
			}
			inline void push(const T& target)
			{
				data.push_back(target);
			}
			inline long long size() const
			{
				return data.size();
			}
			virtual ~stack()
			{
			}
	};
};
#endif