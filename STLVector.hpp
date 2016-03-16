#ifndef SUI_STLVECTOR
#define SUI_STLVECTOR
#include "STLSequenceContainer.hpp"

namespace mystl
{
	template<class T>
	class vector : public SequenceContainer<T>
	{
		protected:
			long long value_capa, value_size, limit_capa;
			T* data;
			inline bool out_range(size_t p)
			{
				return limit_capa != -1 && p > limit_capa;
			}
			inline size_t maxc(size_t a, size_t b)
			{
				if (b == -1) return a;
				if (a == -1) return b;
				if (a < b) return b;
				return a;
			}
			inline size_t maxcd(size_t a, size_t b)
			{
				if (a == -1 || b == -1)
					return -1;
				if (a < b) return b;
				return a;
			}
		public:
			class const_iterator;
			class iterator {
				private:
					long long index;
					vector<T>* context;
				public:
					friend class vector<T> :: const_iterator;
					iterator(long long p = 0, const vector<T>* given_context = NULL) : index(p)
					{
						context = (vector<T>*)(given_context);
					}
					iterator(const vector<T> :: const_iterator& source) : index(source.index), context(source.context) {}
					
					iterator operator+(const int &n) {
						return (iterator(index + n, context));
					}
					iterator operator-(const int &n) {
						return (iterator(index - n, context));
					}
					int operator-(const iterator &rhs) {
						if (context != rhs.context)
							throw invalid_iterator;
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
					iterator operator++(int) {
						iterator orig(*this);
						index++;
						return orig;
					}
					iterator& operator++() {
						index++;
						return (*this);
					}
					inline const T* true_address() const
					{
						return (&(*(*this)));
					}
					iterator operator--(int) {
						iterator orig(*this);
						index--;
						return orig;
					}
					iterator& operator--() {
						index--;
						return (*this);
					}
					T& operator*() const {
						return (*context)[index];
					}
					inline long long idx() const {
						return index;
					}
					template<class Type>
					bool operator==(const Type &rhs) {
						if (context != rhs.context)
							return false;
						return index == rhs.index;
					}
					template<class Type>
					inline bool operator!=(const Type &rhs) {
						return !((*this) == rhs);
					}
			};
			class const_iterator {
				private:
					long long index;
					vector<T>* context;
				public:
					friend class vector<T> :: iterator;
					const_iterator(long long p = 0, const vector<T>* given_context = NULL) : index(p)
					{
						context = (vector<T>*)(given_context);
					}
					const_iterator(const vector<T> :: iterator& source) : index(source.index), context(source.context) {}
					
					const_iterator operator+(const int &n) {
						return (iterator(index + n, context));
					}
					const_iterator operator-(const int &n) {
						return (iterator(index - n, context));
					}
					int operator-(const const_iterator &rhs) {
						if (context != rhs.context)
							throw invalid_iterator;
						return (index - rhs.index);
					}
					const_iterator operator+=(const int &n) {
						index += n;
						return (*this);
					}
					const_iterator operator-=(const int &n) {
						index -= n;
						return (*this);
					}
					const_iterator operator++(int) {
						const_iterator orig(*this);
						index++;
						return orig;
					}
					const_iterator& operator++() {
						index++;
						return (*this);
					}
					inline const T* true_address() const
					{
						return (&(*(*this)));
					}
					const_iterator operator--(int) {
						iterator orig(*this);
						index--;
						return orig;
					}
					const_iterator& operator--() {
						index--;
						return (*this);
					}
					const T& operator*() const {
						return (*context)[index];
					}
					inline long long idx() const {
						return index;
					}
					template<class Type>
					bool operator==(const Type &rhs) {
						if (context != rhs.context)
							return false;
						return index == rhs.index;
					}
					template<class Type>
					inline bool operator!=(const Type &rhs) {
						return !((*this) == rhs);
					}
			};
			vector()
			{
				value_capa = 1;
				value_size = 0;
				limit_capa = -1;
				data = new T[value_capa];
			}
			vector(const T& target)
			{
				value_capa = 1;
				value_size = 1;
				limit_capa = -1;
				data = new T[value_capa];
				data[0] = target;
			}
			vector(const vector<T>& target) : value_capa(target.value_capa), value_size(target.value_size), limit_capa(target.limit_capa)
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
				limit_capa = other.limit_capa;
				delete[] data;
				data = new T[value_capa];
				for (int i = 0; i < value_size; i++)
				{
					data[i] = other.data[i];
				}
				return (*this);
			}	
			virtual ~vector()
			{
				delete[] data;
			}
			T & at(const size_t &pos) 
			{
				if (pos >= value_size || pos < 0)
					throw index_out_of_bound;
				return data[pos];
			}
			const T & at(const size_t &pos) const 
			{
				if (pos >= value_size || pos < 0)
					throw index_out_of_bound;
				return data[pos];
			}
			T & operator[](const size_t &pos)
			{
				if (pos >= value_size || pos < 0)
					throw index_out_of_bound;
				return data[pos];
			}
			const T & operator[](const size_t &pos) const
			{
				if (pos >= value_size || pos < 0)
					throw index_out_of_bound;
				return data[pos];
			}
			const T & front() const 
			{
				if (value_size == 0)
					throw container_is_empty;
				return data[0];
			}
			const T & back() const {
				if (value_size == 0)
					throw container_is_empty;
				return data[value_size - 1];
			}
			iterator begin() 
			{
				return iterator(0, this);
			}
			const_iterator cbegin() const 
			{
				return const_iterator(0, this);
			}
			iterator end() 
			{
				return iterator(value_size, this);
			}
			const_iterator cend() const 
			{
				return const_iterator(value_size, this);
			}
			inline bool empty() const
			{
				return value_size == 0;
			}
			inline bool full() const
			{
				return value_capa == value_size;
			}
			inline bool totally_full() const
			{
				return value_size == limit_capa;
			}
			inline size_t size() const
			{
				return value_size;
			}
			inline size_t capacity() const
			{
				return value_capa;
			}
			void clear()
			{
				delete[] data;
				vector();
			}
			iterator insert(iterator pos, const T &value) {
				iterator it;
				T tmpa(value), tmpb(value);
				for (it = pos; it != end(); it++)
				{
					tmpa = *it;
					*it = tmpb;
					tmpb = tmpa;
				}
				push_back(tmpb);
				return pos;
			}
			inline iterator insert(const size_t &ind, const T &value) {
				return insert(iterator(ind, this), value);
			}
			iterator erase(iterator pos) {
				iterator isp;
				for (iterator it = pos; it != end(); it++)
				{
					isp = it;
					isp++;
					if (isp == end()) break;
					(*it) = *isp;
				}
				value_size--;
				return pos;
			}
			iterator erase(const size_t &ind) {
				return erase(iterator(ind, this));
			}
			void space_doubles()
			{
				if (out_range(value_capa))
					return;
				value_capa <<= 1;
				value_capa = maxc(value_capa, limit_capa);
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
				if (out_range(value_size))
					throw index_out_of_bound;
				if (value_size > value_capa)
					space_doubles();
				data[value_size - 1] = target;
			}
			void pop_back()
			{
				if (empty())
					throw container_is_empty;
				value_size--;
			}
			inline void set_max_capa(size_t limit)
			{
				limit_capa = limit;
			}
			void reserve(long long new_capacity)
			{
				if (new_capacity < value_capa)
					throw std :: out_of_range("Vector space underestimated!");
				value_capa = new_capacity;
				limit_capa = maxcd(value_capa, limit_capa);
				T* new_place = new T[value_capa];
				for (int i = 0; i < value_size; i++)
				{
					new_place[i] = data[i];
				};
				delete[] data;
				data = new_place;
			}

	};
};
#endif