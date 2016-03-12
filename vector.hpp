#ifndef MYSTL_VECTOR
#define MYSTL_VECTOR
#include <stdexcept>
namespace std {
template <class T> class vector {
	public:
		class iterator {
			T* real_ptr;
			public:
				iterator(T* ptr = NULL) : real_ptr(ptr) {}
				T& operator*() { return *real_ptr; }
				
		}
		int assign(iterator beg, iterator ed);
		int assign(int n, T target);
		int capacity();
		int reserve(int target_size);
		int size();
		
	private:
		int num_size = 0;
		int num_capa = 0;
		T* data;
}
}

template <class T> int vector<T> :: assign(int n, T target)
{
	if (size < n)
		reserve(n);
	for (int i = 0; i < n; i++)
	{
		data[i] = T;
	}
	return 0;
}

template <class T> int reserve
#endif