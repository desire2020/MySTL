#ifndef SUI_STLLIST
#define SUI_STLLIST
#include "STLSequenceContainer.hpp"
namespace mystl
{
	template<class T>
	class node
	{
		public:
			T* data;
			node* last;
			node* next;
			node(T* real_data = NULL, node* real_last = NULL, node* real_next = NULL) : last(real_last), next(real_next)
			{
				if (real_data == NULL)
				{
					data = real_data;
				} else {
					data = new T(*real_data);
				}
			}
			node(const T& real_data, node* real_last = NULL, node* real_next = NULL) :  last(real_last), next(real_next)
			{
				data = new T;
				(*data) = real_data;
			}
			~node()
			{
				delete data;
			}
	};
	template<class T>
	class list : public SequenceContainer<T>
	{
		long long value_size;
		node<T>* head;
		node<T>* tail;
		public:
			list()
			{
				value_size = 0;
				head = new node<T>();
				tail = new node<T>();
				tail -> last = head;
				head -> next = tail;
			}
			virtual ~list()
			{
				clear();
				delete head;
				delete tail;
			}
			size_t size() const
			{
				return value_size;
			}
			bool empty()
			{
				return value_size == 0;
			}
			class iterator;
			class const_iterator : public SequenceContainer<T> :: const_iterator
			{
				protected:
					node<T>* real_ptr;
				public:
					friend class list<T> :: iterator;
					const_iterator(node<T>* target_ptr = NULL) : real_ptr(target_ptr) {}
					const_iterator(const list<T> :: iterator& source) : real_ptr(source.real_ptr) {}
					const T& operator*() const
					{
						return *((*real_ptr).data);
					}
					const const_iterator& operator++(int n)
					{
						static const_iterator orig;
						orig = *this;
						real_ptr = real_ptr -> next;
						return orig;
					}
					const_iterator& operator++()
					{
						real_ptr = real_ptr -> next;
						return (*this);
					}
					const_iterator last() const
					{
						return const_iterator(real_ptr -> last);
					}
					const_iterator next() const
					{
						return const_iterator(real_ptr -> next);
					}
					const T* true_address() const
					{
						return real_ptr -> data;
					}
					const node<T>* node_address() const
					{
						return real_ptr;
					}
					friend bool operator==(const_iterator target1, const_iterator target2)
					{
						return (&(*target1)) == (&(*target2));
					}
					friend bool operator!=(const_iterator target1, const_iterator target2)
					{
						return !(target1 == target2);
					}
			};
			class iterator : public SequenceContainer<T> :: iterator
			{
				protected:
					node<T>* real_ptr;
				public:
					friend class list<T> :: const_iterator;
					iterator(node<T>* target_ptr = NULL) : real_ptr(target_ptr) {}
					iterator(const list<T> :: const_iterator& source) : real_ptr(source.real_ptr) {}
					T& operator*() const
					{
						return *(real_ptr -> data);
					}
					const iterator& operator++(int n)
					{
						static iterator orig;
						orig = *this;
						real_ptr = real_ptr -> next;
						return orig;
					}
					iterator& operator++()
					{
						real_ptr = real_ptr -> next;
						return (*this);
					}
					iterator last() const
					{
						return iterator(real_ptr -> last);
					}
					iterator next() const
					{
						return iterator(real_ptr -> next);
					}
					const T* true_address() const
					{
						return real_ptr -> data;
					}
					node<T>* node_address() const
					{
						return real_ptr;
					}
					friend bool operator==(iterator target1, iterator target2)
					{
						return (&(*target1)) == (&(*target2));
					}
					friend bool operator!=(iterator target1, iterator target2)
					{
						return !(target1 == target2);
					}
			};
			iterator begin() const
			{
				return iterator(head -> next);
			}
			iterator end() const
			{
				return iterator(tail);
			}
			iterator back_it() const
			{
				return iterator(tail -> last);
			}
			iterator insert(iterator target, const T& targ_data)
			{
				value_size++;
				node<T>* newbie = new node<T>;
				newbie -> data = new T;
				(*(newbie -> data)) = targ_data;
				newbie -> next = target.node_address();
				newbie -> last = target.node_address() -> last;
				target.node_address() -> last -> next = newbie;
				target.node_address() -> last = newbie;
				target = iterator(newbie);
				return target;
			}
			iterator erase(iterator target)
			{
				node<T>* poped(target.node_address());
				target++;
				poped -> last -> next = poped -> next;
				poped -> next -> last = poped -> last;
				delete poped;
				value_size--;
				return target;
			}
			iterator erase(iterator start, iterator targ)
			{
				while (start != targ)
				{
					start = erase(start);
					value_size--;
				}
				return targ;
			}
			
			void push_back(const T& target)
			{
				insert(end(), target);
			}

			void pop_back()
			{
				if (empty())
					throw std :: out_of_range("Invalid pop operation!");
				erase(iterator(end().node_address() -> last));
			}
			void push_front(const T& target)
			{
				insert(iterator(begin().node_address() -> next), target);
			}
			void pop_front()
			{
				if (empty())
					throw std :: out_of_range("Invalid pop operation!");
				erase(iterator(begin().node_address() -> next));
			}
			
			const T& back() const
			{
				return (*(end().node_address() -> last -> data));
			}
			T& back()
			{
				return (*(end().node_address() -> last -> data));
			}
			const T& front() const
			{
				return (*(begin().node_address() -> next -> data));
			}
			inline void clear()
			{
				if (empty()) return;
				iterator it = begin();
				erase(it, end());
			}
			list(const list<T> &other) : value_size(0) {
				head = new node<T>();
				tail = new node<T>();
				tail -> last = head;
				head -> next = tail;
				list<T> :: const_iterator it;
				for (it = other.begin(); it != const_iterator(other.end()); it++)
				{
					push_back(*it);
				}
			}

	};
};
#endif