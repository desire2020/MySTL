#ifndef SUI_STLVECTOR
#define SUI_STLVECTOR
#include "STLSequenceContainer.hpp"
namespace mystl
{
	template<class T>
	class vector : public SequenceContainer<T>
	{
		protected:
			long long value_capa, value_size;
			T* data;
		public:
			vector()
			{
				value_capa = 1;
				value_size = 0;
				data = new T[value_capa];
			}
			vector(const T& target)
			{
				value_capa = 1;
				value_size = 1;
				data = new T[value_capa];
				data[0] = target;
			}
			vector(const vector<T>& target) : value_capa(target.value_capa), value_size(target.value_size)
			{
				data = new T[value_capa];
				for (int i = 0; i < value_size; i++)
				{
					data[i] = target.data[i];
				}
			}
			vector<T>& operator=(const vector<T> &other){
				value_capa = other.value_capa;
				value_size = other.value_size;
				delete[] data;
				data = new T[value_capa];
				for (int i = 0; i < value_size; i++)
				{
					data[i] = other.data[i];
				}
				return (*this);
			}	
			size_t size() const
			{
				return value_size;
			}
			bool full() const
			{
				return value_capa == value_size;
			}
			void clear()
			{
				delete[] data;
				vector();
			}
			bool empty()
			{
				return value_size == 0;
			}
			void space_doubles()
			{
				value_capa <<= 1;
				//std :: cerr << value_capa << " blocks at this run." << std :: endl;
				T* new_place = new T[value_capa];
				for (int i = 0; i < value_size - 1; i++)
				{
					new_place[i] = data[i];
				};
				delete[] data;
				data = new_place;
			}
			void push_back(const T& target)
			{
				value_size++;
				if (value_size > value_capa)
					space_doubles();
				data[value_size - 1] = target;
			}
			void pop_back()
			{
				value_size--;
			}
			const T& back() const
			{
				return data[value_size - 1];
			}
			const T& front() const
			{
				return data[0];
			}
			T& operator[](long long n)
			{
				return data[n];
			}
			T& at(long long n)
			{
				if (n >= value_size)
					throw std :: out_of_range("Vector index range error!");
				return data[n];
			}
			long long capacity() const
			{
				return value_capa;
			}
			void reserve(long long new_capacity)
			{
				if (new_capacity < value_capa)
					throw std :: out_of_range("Vector space underestimated!");
				value_capa = new_capacity;
				T* new_place = new T[value_capa];
				for (int i = 0; i < value_size; i++)
				{
					new_place[i] = data[i];
				};
				delete[] data;
				data = new_place;
			}
			class iterator;
			class const_iterator : public SequenceContainer<T> :: const_iterator
			{
				protected:
					long long index;
					vector<T>* context;
				public:
					friend class vector<T> :: iterator;
					const_iterator(long long p = 0, const vector<T>* given_context = NULL) : index(p)
					{
						context = (vector<T>*)(given_context);
					}
					const_iterator(const vector<T> :: iterator& source) : index(source.index), context(source.context) {}
					const T& operator*() const
					{
						return (*context)[index];
					}
					const const_iterator& operator++(int n)
					{
						const_iterator orig(*this);
						index++;
						return orig;
					}
					const_iterator& operator++()
					{
						index++;
						return (*this);
					}
					const T* true_address() const
					{
						return (&(*(*this)));
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
				long long index;
				vector<T>* context;
				public:
					friend class vector<T> :: const_iterator;
					iterator(long long p = 0, const vector<T>* given_context = NULL) : index(p)
					{
						context = (vector<T>*)(given_context);
					}
					iterator(const vector<T> :: const_iterator& source) : index(source.index), context(source.context) {}
					T& operator*() const
					{
						return (*context)[index];
					}
					const iterator& operator++(int n)
					{
						static iterator orig(*this);
						index++;
						return orig;
					}
					iterator operator+(const int &n) {
						return (iterator(index + n, context));
					}
					iterator operator-(const int &n) {
						return (iterator(index - n, context));
					}
					// return th distance between two iterator,
					// if these two iterators points to different vectors, throw invaild_iterator.
					int operator-(const iterator &rhs) {
						if (context != rhs.context)
							throw std :: out_of_range("invalid iterator");
						return (index - rhs.index);
					}
					iterator operator+=(const int &n) {
						index += n;
						return (*this);
					}
					iterator operator-=(const int &n) {
						index -= n;
						return (*this);
					}
					iterator& operator++()
					{
						index++;
						return (*this);
					}
					const T* true_address() const
					{
						return (&(*(*this)));
					}
					inline long long idx() const
					{
						return index;
					}
					friend bool operator==(iterator target1, iterator target2)
					{
						return (&(*target1)) == (&(*target2));
					}
					friend bool operator!=(iterator target1, iterator target2)
					{
						return !(target1 == target2);
					}
					friend vector<T> :: iterator vector<T> :: erase(const iterator& start, const iterator& targ);
			};
			iterator begin() const
			{
				return iterator(0, this);
			}
			iterator end() const
			{
				return iterator(value_size, this);
			}
			iterator insert(iterator target, const T& newbie)
			{
				iterator it;
				T tmpa(newbie), tmpb(newbie);
				for (it = target; it != end(); it++)
				{
					tmpa = *it;
					*it = tmpb;
					tmpb = tmpa;
				}
				push_back(tmpb);
				return target;
			}
			iterator erase(const iterator& target)
			{
				iterator isp;
				for (iterator it = target; it != end(); it++)
				{
					isp = it;
					isp++;
					if (isp == end()) break;
					(*it) = *isp;
				}
				value_size--;
				return target;
			}
			iterator erase(const iterator& start, const iterator& targ)
			{
				iterator des(start), src(targ);
				while (src != end())
				{
					*des = *targ;
					des++;
					targ++;
				}
				value_size -= targ.index - start.index;
			}
			virtual ~vector()
			{
				delete[] data;
			}
	};
};
#endif