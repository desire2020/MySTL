#ifndef SUI_PRIORITY_QUEUE
#define SUI_PRIORITY_QUEUE
#include <cstddef>
#include <functional>
#include "STLVector.hpp"
namespace mystl {

	/**
	 * a container like std::priority_queue which is a heap internal.
	 */
	template<typename T, class Compare = std::less<T> >
	class HeapBase
	{
		protected:
			Compare less_than;
			bool equal_to(const T& target1, const T& target2) const
			{
				return !(this -> less_than(target1, target2) || this -> less_than(target2, target1));
			}
		public:
			virtual void heapify() = 0;
			virtual const T& top() const = 0;
			virtual void insert(const T& target) = 0;
			virtual size_t size() const = 0;
			virtual bool empty() const = 0;
			virtual void pop() = 0;
			virtual bool exist(const T& target) const = 0;
			virtual ~HeapBase() {}
	};
	template<typename T, class Compare = std::less<T> >
	class BinaryHeap : public HeapBase<T, Compare>
	{
		protected:
			vector<T> inside;
			inline int left(int ps)
			{
				return ((ps + 1) << 1) - 1;
			}
			inline int right(int ps)
			{
				return (ps + 1) << 1;
			}
			inline bool inrange(int ps)
			{
				return ps < size();
			}
		public:
			void heapify_bottom2top()
			{
				int p = inside.size();
				p -= 1;
				if (p <= 0) return;
				while (this -> less_than(inside[p], inside[(p - 1) >> 1]))
				{
					std :: swap(inside[p], inside[(p - 1) >> 1]);
					p = (p - 1) >> 1;
					if (p <= 0) return;
				}
			}
			void heapify_top2bottom()
			{
				int p = 0;
				while (inrange(left(p)))
				{
					if (!inrange(right(p)) || this -> less_than(inside[left(p)], inside[right(p)]))
					{
						if (this -> less_than(inside[left(p)], inside[p]))
						{
							std :: swap(inside[left(p)], inside[p]);
							p = left(p);
						} else {
							return;
						}
					} else {
						if (this -> less_than(inside[right(p)], inside[p]))
						{
							std :: swap(inside[right(p)], inside[p]);
							p = right(p);
						} else {
							return;
						}
					}
				}
			}
			inline void heapify()
			{
				heapify_bottom2top();
				heapify_top2bottom();
			}
			inline const T& top() const
			{
				return inside[0];
			}
			inline void insert(const T& target)
			{
				inside.push_back(target);
				heapify_bottom2top();
			}
			inline size_t size() const
			{
				return inside.size();
			}
			void pop()
			{
				std :: swap(inside[0], inside[size() - 1]);
				inside.pop_back();
				heapify_top2bottom();
			}
			inline bool empty() const 
			{
				return size() == 0;
			}
			bool exist(const T& target) const
			{
				for (int i = 0; i < size(); i++)
				{
					if (this -> equal_to(inside[i], target))
						return true;
				}
				return false;
			}
			BinaryHeap& merge(const BinaryHeap& target)
			{
				for (int i = 0; i < target.size(); i++)
				{
					insert(target.inside[i]);
				}
				return *this;
			}
			virtual ~BinaryHeap() {}
	};
	
	template<typename T, class Compare = std::less<T>, class THeap = BinaryHeap<T, Compare> >
	class priority_queue {
	protected:
		THeap data;
	public:
		inline const T & top() const 
		{
			return data.top();
		}

		inline void push(const T &e) 
		{
			data.insert(e);
		}
		inline void pop() 
		{
			data.pop();
		}
		inline size_t size() const 
		{
			return data.size();
		}
		inline bool empty() const 
		{
			return data.empty();
		}
	};

}

#endif