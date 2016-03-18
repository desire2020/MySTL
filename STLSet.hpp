#ifndef SUI_STLSET
#define SUI_STLSET
template <class T>
struct node
{
	T data;
	node<T>* left;
	node<T>* right;
	node(T create) : data(create), left(NULL), right(NULL) {}
};

template <class T>
class naive_set
{
	node<T>* inner_struct;
	public:
		naive_set()
		{
			inner_struct = NULL;
		}
		typedef node<T>* node_ptr;
		void create(node_ptr &target, const T& value)
		{
			if (target == NULL)
			{
				target = new node<T>(value);
				return;
			}
			if (value < target -> data)
				create(target -> left, value);
			if (value > target -> data)
				create(target -> right, value);
		}
		inline void insert(const T& value)
		{
			create(inner_struct, value);
		}
		bool seekfor(node_ptr &target, const T& value)
		{
			if (target == NULL)
				return false;
			if (value < target -> data)
				return seekfor(target -> left, value);
			if (value > target -> data)
				return seekfor(target -> right, value);
		}
		inline bool exist(const T& value)
		{
			return seekfor(inner_struct, value);
		}
		void deletenode(node_ptr &target, const T& value)
		{
			if (target == NULL)
				return;
			if (value < target -> data)
				deletenode(target -> left, value);
			if (value > target -> data)
				deletenode(target -> right, value);
			if (value == target -> data)
			{
				node_ptr tmp;
				if (target -> left == NULL)
				{
					tmp = target;
					target = target -> right;
					delete tmp;
					return;
				} else {
					if (target -> right == NULL)
					{
						tmp = target;
						target = target -> left;
						delete tmp;
						return;
					} else {
						tmp = target -> right;
						while (tmp -> left != NULL)
							tmp = tmp -> left;
						target -> data = tmp -> data;
						deletenode(target -> data, target -> right);
					}
				}
				target == NULL;
			}
		}
		inline void erase(const T& value)
		{
			deletenode(inner_struct, value);
		}
};
#endif