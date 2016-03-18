#ifndef SUI_STLDEQUE
#define SUI_STLDEQUE
#include "STLVector.hpp"
#include "STLList.hpp"

namespace mystl
{
	template<class T, int node_size = 320>
	class deque : public SequenceContainer<T>
	{
		protected:
			list< vector<T> > inside;
			long long value_size;
		public:
			typedef typename list< vector<T> > :: iterator it_con;
			typedef typename vector<T> :: iterator it_idx;
			class const_iterator;
			class iterator : public SequenceContainer<T> :: iterator
			{
				protected:
					it_con context;
					it_idx index;
					deque<T, node_size> *title;
				public:
					friend class deque<T, node_size> :: const_iterator;
					iterator() {}
					iterator(const typename deque<T, node_size> :: const_iterator& target) : context(target.context), index(target.index), title(target.title) {}
					iterator(const it_con& tg_con, it_idx tg_idx, const deque<T, node_size>* tg_tit) : context(tg_con), index(tg_idx) {
						title = (deque<T, node_size>*)tg_tit; 
					}
					
					iterator operator+(const int &n)
					{
						iterator tmp(*this);
						int ncp(n);
						if (n < (*(tmp.context)).size() - tmp.index.idx())
						{
							tmp.index += n;
							return tmp;
						}
						ncp -= (*(tmp.context)).size() - index.idx() - 1;
						tmp.context++;
						if (tmp.context == tmp.title -> end_list())
						{
							throw index_out_of_bound;
						}
						while (ncp > (*tmp.context).size())
						{
							ncp -= (*(tmp.context)).size();
							tmp.context++;
							if (tmp.context == tmp.title -> end_list())
							{
								throw index_out_of_bound;
							}
						}
						tmp.index = (*tmp.context).begin() + (ncp - 1);
						return tmp;
					}
					iterator operator-(const int &n)
					{
						int ncp(n);
						iterator tmp(*this);
						if (n <= tmp.index.idx())
						{
							tmp.index -= n;
							return tmp;
						}
						ncp -= tmp.index.idx();
						while (ncp > (*tmp.context).size())
						{
							ncp -= (*(tmp.context)).size();
							if (tmp.context != tmp.title -> beg_list())
								tmp.context--;
						}
						tmp.index = (*tmp.context).end() - ncp;
						return tmp;
					}
					int operator-(const iterator &rhs) {
						if (title != rhs.title)
							throw invalid_iterator;
						if (context == rhs.context)
							return index - rhs.index;
						int ans = ((*(rhs.context)).size() - rhs.index.idx()) + index.idx();
						for (it_con it = context.last(); it != rhs.context.next(); it++)
						{
							if (it == NULL)
								throw runtime_error;
							ans += (*it).size();
						}
						return ans;
					} 
					inline iterator operator+=(const int &n)
					{
						(*this) = (*this) + n;
						return (*this);
					}
					inline iterator operator-=(const int &n)
					{
						(*this) = (*this) - n;
						return (*this);
					}
					iterator operator++(int n)
					{
						iterator backup(*this);
						index++;
						if (index == (*context).end())
						{
							context++;
							if (context == (*title).end_list())
							{
								(*this) = title -> end();
								return backup;
							}
							index = (*context).begin();
						}
						return backup;
					}
					iterator& operator++()
					{
						index++;
						if (index == (*context).end())
						{
							context++;
							if (context == (*title).end_list())
							{
								(*this) = title -> end();
								return (*this);
							}
							index = (*context).begin();
						}
						return (*this);
					}
					iterator operator--(int n)
					{
						iterator backup(*this);
						if (index == (*context).begin())
						{
							if (context == (*title).beg_list())
							{
								throw index_out_of_bound;
							}
							context--;
							index = (*context).end();
						}
						index--;
						return backup;
					}
					const T* true_address() const
					{
						return &(*(*this));
					}
					iterator& operator--()
					{
						if (index == (*context).begin())
						{
							if (context == (*title).beg_list())
							{
								throw index_out_of_bound;
							}
							context--;
							index = (*context).end();
						}
						index--;
						return (*this);
					}
					iterator last() {
						iterator tmp(*this);
						--tmp;
						return tmp;
					}
					iterator next() {
						iterator tmp(*this);
						++tmp;
						return tmp;
					}
					T& operator*() const {
						return (*index);
					}
					bool operator==(const iterator &rhs) {
						return (context == rhs.context && index == rhs.index && title == rhs.title);
					}
					bool operator==(const const_iterator &rhs) {
						return (context == rhs.context && index == rhs.index && title == rhs.title);
					}
					template<class Type>
					inline bool operator!=(const Type &rhs) {
						return !((*this) == rhs);
					}
					friend iterator deque<T, node_size> :: insert(iterator pos, const T& value);
					friend iterator deque<T, node_size> :: erase(iterator pos);
			};
			class const_iterator : public SequenceContainer<T> :: const_iterator
			{
				protected:
					it_con context;
					it_idx index;
					deque<T, node_size> *title;
				public:
					friend class deque<T, node_size> :: iterator;
					const_iterator() {}
					const_iterator(const it_con& tg_con, it_idx tg_idx, const deque<T, node_size>* tg_tit) : context(tg_con), index(tg_idx)
					{
						title = (deque<T, node_size>*)tg_tit; 
					}
					const_iterator(const typename deque<T, node_size> :: iterator& target) : context(target.context), index(target.index), title(target.title) {}
					const_iterator operator+(const int &n)
					{
						const_iterator tmp(*this);
						if (n < (*(tmp.context)).size() - tmp.index.idx())
						{
							tmp.index += n;
							return tmp;
						}
						n -= (*(tmp.context)).size() - index.idx() - 1;
						context++;
						if (tmp.context == tmp.title -> end_list())
						{
							throw index_out_of_bound;
						}
						while (n > (*context).size())
						{
							n -= (*(tmp.context)).size();
							tmp.context++;
							if (tmp.context == tmp.title -> end_list())
							{
								throw index_out_of_bound;
							}
						}
						tmp.index = (*context).begin() + (n - 1);
						return tmp;
					}
					const_iterator operator-(const int &n)
					{
						const_iterator tmp(*this);
						if (n <= tmp.index.idx())
						{
							tmp.index -= n;
							return tmp;
						}
						n -= tmp.index.idx();
						while (n > (*context).size())
						{
							n -= (*(tmp.context)).size();
							if (tmp.context != tmp.title -> beg_list())
								tmp.context--;
						}
						tmp.index = (*context).end() - n;
						return tmp;
					}
					int operator-(const iterator &rhs) {
						if (title != rhs.title)
							throw invalid_iterator;
						if (context == rhs.context)
							return index - rhs.index;
						int ans = ((*(rhs.context)).size() - rhs.index.idx()) + index.idx();
						for (it_con it = context.last(); it != rhs.context.next(); it++)
						{
							if (it == NULL)
								throw runtime_error;
							ans += (*it).size();
						}
						return ans;
					} 
					inline const_iterator operator+=(const int &n)
					{
						(*this) = (*this) + n;
						return (*this);
					}
					inline const_iterator operator-=(const int &n)
					{
						(*this) = (*this) - n;
						return (*this);
					}
					const_iterator operator++(int n)
					{
						const_iterator backup(*this);
						index++;
						if (index == (*context).end())
						{
							context++;
							if (context == (*title).end_list())
							{
								(*this) = end();
								return backup;
							}
							index = (*context).begin();
						}
						return backup;
					}
					const T* true_address() const
					{
						return &(*(*this));
					}
					const_iterator& operator++()
					{
						index++;
						if (index == (*context).end())
						{
							context++;
							if (context == (*title).end_list())
							{
								(*this) = (*title).cend();
								return (*this);
							}
							index = (*context).begin();
						}
						return (*this);
					}
					const_iterator operator--(int n)
					{
						iterator backup(*this);
						if (index == (*context).begin())
						{
							if (context == (*title).beg_list())
							{
								throw index_out_of_bound;
							}
							context--;
							index = (*context).end();
						}
						index--;
						return backup;
					}
					const_iterator& operator--()
					{
						if (index == (*context).begin())
						{
							if (context == (*title).beg_list())
							{
								throw index_out_of_bound;
							}
							context--;
							index = (*context).end();
						}
						index--;
						return (*this);
					}
					const_iterator last() {
						const_iterator tmp(*this);
						--tmp;
						return tmp;
					}
					const_iterator next() {
						const_iterator tmp(*this);
						++tmp;
						return tmp;
					}
					const T& operator*() const {
						return (*index);
					}
					bool operator==(const iterator &rhs) {
						return (context == rhs.context && index == rhs.index && title == rhs.title);
					}
					bool operator==(const const_iterator &rhs) {
						return (context == rhs.context && index == rhs.index && title == rhs.title);
					}
					inline bool operator!=(const iterator &rhs) {
						return !((*this) == rhs);
					}
					inline bool operator!=(const const_iterator &rhs) {
						return !((*this) == rhs);
					}
			};
			deque() {
				inside.push_back(vector<T>());
				(*inside.begin()).set_max_capa(node_size + 1);
				value_size = 0;
			}
			deque(const deque<T, node_size> &other) {
				inside = other.inside;
				value_size = other.value_size;
			}
			~deque() {
				inside.clear();
				value_size = 0;
			}
			T& at(const size_t &pos) {
				return (*(begin() + pos));
			}
			const T & at(const size_t &pos) const {
				return (*(begin() + pos));
			}
			T& operator[](const size_t &pos) {
				return at(pos);
			}
			const T& operator[](const size_t &pos) const {
				return at(pos);
			}
			inline const T& front() const {
				return (*begin());
			}
			inline const T& back() const {
				return (*(end() - 1));
			}
			inline iterator begin() const {
				return iterator(inside.begin(), (*(inside.begin())).begin(), this);
			}
			inline const_iterator cbegin() const {
				return const_iterator(inside.begin(), (*(inside.begin())).begin(), this);
			}
			iterator end() const {
				return iterator(inside.end().last(), (*(inside.end().last())).end(), this);
			}
			inline const_iterator cend() const {
				return const_iterator(end());
			}
			inline bool empty() const
			{
				return value_size == 0;
			}
			inline size_t size() const
			{
				return value_size;
			}
			inline void clear()
			{
				inside.clear();
				value_size = 0;
			}
			iterator insert(iterator pos, const T& value)
			{
				if (pos.title != this)
					throw invalid_iterator;
				vector<T>& into_plat = (*(pos.context));
				it_idx it = pos.index;
				it = into_plat.insert(it, value);
				if (into_plat.totally_full())
				{
					pos.context++;
					if (pos.context == inside.end() || (*(pos.context)).totally_full())
					{
						vector<T> tmp(into_plat[node_size]);
						tmp.set_max_capa(node_size + 1);
						inside.insert(pos.context, tmp);
					} else {
						vector<T>& after_plat = (*(pos.context));
						after_plat.insert(after_plat.begin(), into_plat[node_size]);
					}
					into_plat.pop_back();
				}
				value_size++;
				return iterator(pos.context, it, this);
			}
			iterator erase(iterator pos) 
			{
				if (pos.title != this)
					throw invalid_iterator;
				vector<T>& into_plat = (*(pos.context));
				it_idx it = pos.index;
				it = into_plat.erase(it);
				if (it == into_plat.end())
				{
					pos.context++;
					it = (*(pos.context)).begin();
				}
				value_size--;
				return iterator(pos.context, it, pos.title);
			}
			inline void push_back(const T& value)
			{
				insert(end(), value);
			}
			void pop_back()
			{
				if (empty())
				{
					throw container_is_empty;
				}
				while (inside.back().empty() && (inside.size() > 1))
					inside.pop_back();
				vector<T>& into_plat = inside.back();
				into_plat.pop_back();
				while (inside.back().empty() && (inside.size() > 1))
					inside.pop_back();
				value_size--;
			}
			void push_front(const T& value) {
				vector<T> tmp(value);
				inside.push_front(value);
				value_size++;
			}
			inline void pop_front()
			{/*
				if (empty())
				{
					throw container_is_empty;
				}
				vector<T>& into_plat = (*inside.begin());
				into_plat.erase(into_plat.begin());
				while ((*inside.begin()).empty())
					inside.pop_front();
				value_size--;*/
				erase(begin());
			}
			inline int block_size() const {
				return node_size;
			}
			inline it_con beg_list() const {
				return inside.begin();
			}
			inline it_con end_list() const {
				return inside.end();
			}

	};

};
#endif