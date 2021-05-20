#pragma once
#include <vector>
using namespace std;

template <typename T, int max_size = 10>
class Deque
{
private:
	struct Node;
	Node *last_node;
	Node *first_node;
	
	int size;

public:
	struct iterator;
	struct r_iterator;
	friend class iterator;
	Deque();
	~Deque();

	T &front();
	T &back();

	typename Deque<T, max_size>::iterator begin();
	typename Deque<T, max_size>::iterator end();
	const typename Deque<T, max_size>::iterator cbegin();
	const typename Deque<T, max_size>::iterator cend();

	T &operator[](int pos);
	T &at(int pos);

	void push_back(T elem);
	void help_push_front(int size,T elem);
	void push_front(T elem);
	void insert(Deque<T, max_size>::iterator pos, T elem);
	int getSize();

	template <typename ...Args>
	void emplace_front(Args && ...args);
	template <typename ...Args>
	void emplace(Deque<T, max_size>::iterator pos, Args && ...args);
	template <typename... Args>
	void emplace_back(Args && ...args);

	void pop_front();
	void pop_back();
	void erase(Deque<T, max_size>::iterator pos);

};

template <typename T, int max_size>
struct Deque<T, max_size>::Node
{
	vector<T> elements;
	Node *next_node;
	Node *prev_node;

	Node();
	~Node();
	Node(Node *_next_node, Node *_prev_node);
};

//带尾节点双向链表控制器map
template <typename T, int max_size>
Deque<T, max_size>::Deque()
{
	first_node = new Node();
	last_node = new Node();
	first_node->next_node = last_node;
	last_node->prev_node = first_node;
	size=0;
}

template <typename T, int max_size>
Deque<T, max_size>::~Deque()
{
	delete this->first_node;
}

template <typename T, int max_size>
T &Deque<T, max_size>::front()
{
	return first_node->elements.front();
}

template <typename T, int max_size>
T &Deque<T, max_size>::back()
{
	return last_node->prev_node->elements.back();
}

template <typename T, int max_size>
T &Deque<T, max_size>::operator[](int pos)
{
	Node *curr_node = first_node;
	while (pos >= curr_node->elements.size())
	{
		pos -= curr_node->elements.size();
		curr_node = curr_node->next_node;
	}
	return curr_node->elements[pos];
}

template <typename T, int max_size>
T &Deque<T, max_size>::at(int pos)
{	
	Node *curr_node = first_node;
	while (pos >= curr_node->elements.size())
	{
		pos -= curr_node->elements.size();
		curr_node = curr_node->next_node;
	}
	return curr_node->elements[pos];
}

template<typename T,int max_size>
int Deque<T,max_size>::getSize()
{
	return size;
}

template <typename T, int max_size>
void Deque<T, max_size>::push_back(T elem)
{
	if (last_node->prev_node->elements.size() == max_size)
	{
		last_node->prev_node->next_node = new Node(last_node, last_node->prev_node);
		last_node->prev_node = last_node->prev_node->next_node;
		last_node->prev_node->elements.push_back(elem);
	}
	else
	{
		last_node->prev_node->elements.push_back(elem);
	}
	++size;
}

template <typename T,int max_size>
void Deque<T,max_size>::help_push_front(int size,T elem)
{	
	first_node->elements.resize(size+1);
	for(int i=size;i>0;i--)
	{
		first_node->elements[i]=first_node->elements[i-1];
	}
	first_node->elements[0]=elem;
}

template <typename T, int max_size>
void Deque<T, max_size>::push_front(T elem)
{
	
	if (first_node->elements.size()==max_size)
	{
		first_node->prev_node = new Node(first_node, nullptr);
		first_node = first_node->prev_node;
		help_push_front(0,elem);
	}
	else
	{
		help_push_front(first_node->elements.size(),elem);
	}
	++size;
}

template <typename T, int max_size>
void Deque<T, max_size>::insert(Deque<T, max_size>::iterator pos, T elem)
{	
	if(pos.this_node==last_node)
	{
		throw std::exception();
		return;
	}
	if (pos.this_node->elements.size() == max_size || pos.this_node->next_node == last_node)
	{
		T last_elem = pos.this_node->elements.back();
		if (pos.this_node->next_node->elements.size() == max_size)
		{
			Node *temp_node = new Node(pos.this_node->next_node, pos.this_node);
			pos.this_node->next_node->prev_node = temp_node;
			pos.this_node->next_node = temp_node;

			auto it = pos.this_node->elements.begin() + pos.index;
			auto remove_it=pos.this_node->elements.end()-1;
			temp_node->elements.insert(temp_node->elements.begin(), last_elem);
			pos.this_node->elements.erase(remove_it);
			pos.this_node->elements.insert(it, elem);
		}
		else if(pos.this_node->next_node!=last_node)
		{
			auto it = pos.this_node->elements.begin() + pos.index;
			auto remove_it=pos.this_node->elements.end()-1;
			pos.this_node->next_node->elements.insert(pos.this_node->next_node->elements.begin(), last_elem);
			pos.this_node->elements.erase(remove_it);
			pos.this_node->elements.insert(it,elem);
		}
		else if(pos.this_node->elements.size() == max_size && pos.this_node->next_node == last_node)
		{
			Node *temp_node = new Node(pos.this_node->next_node, pos.this_node);
			pos.this_node->next_node->prev_node = temp_node;
			pos.this_node->next_node = temp_node;

			auto it = pos.this_node->elements.begin() + pos.index;
			auto remove_it=pos.this_node->elements.end()-1;
			temp_node->elements.insert(temp_node->elements.begin(), last_elem);
			pos.this_node->elements.erase(remove_it);
			pos.this_node->elements.insert(it,elem);
		}
		else
		{
			auto it = pos.this_node->elements.begin() + pos.index;
			pos.this_node->elements.insert(it, elem);
		}
	}
	else
	{
		auto it = pos.this_node->elements.begin() + pos.index;
		pos.this_node->elements.insert(it, elem);
	}
	++size;
}

template <typename T, int max_size>
void Deque<T, max_size>::pop_front()
{
	if(first_node->elements.size()==0)
	{
		std::cout<<"pop_front() error"<<std::endl;
		return;
	}
	else
	{
		first_node->elements.erase(first_node->elements.begin());
		if(first_node->elements.size()==0)
		{
			Node *temp_ptr = first_node;
			first_node = first_node->next_node;
			temp_ptr->next_node = nullptr;
			delete temp_ptr;
		}
	}
	--size;
}

template <typename T, int max_size>
void Deque<T, max_size>::pop_back()
{
	if(last_node->prev_node->elements.size()==0)
	{
		std::cout<<"pop_back() error"<<std::endl;
		return;
	}
	else
	{	
		auto it=last_node->prev_node->elements.end()-1;
		//cout<<*it<<endl;
		last_node->prev_node->elements.erase(it);
		if(last_node->prev_node->elements.size()==0)
		{
			Node *temp_node = last_node->prev_node;
			temp_node->prev_node->next_node = last_node;
			last_node->prev_node = temp_node->prev_node;
			temp_node->next_node = nullptr;
			delete temp_node;
		}
	}
	--size;
}

template <typename T, int max_size>
void Deque<T, max_size>::erase(Deque<T, max_size>::iterator pos)
{
	int remove_index=pos.index;
	auto remove_it=pos.this_node->elements.begin()+remove_index;
	pos.this_node->elements.erase(remove_it);

	if(pos.this_node->elements.size()==0)
	{
		Node *temp_node = pos.this_node;
		temp_node->next_node->prev_node = temp_node->prev_node;
		if (temp_node->prev_node)
			temp_node->prev_node->next_node = temp_node->next_node;
		else
			this->first_node = temp_node->next_node;
		temp_node->next_node = nullptr;
		delete temp_node;
	}
	--size;
}

template <typename T, int max_size>
Deque<T, max_size>::Node::Node()
{
	next_node = nullptr;
	prev_node = nullptr;
}

template <typename T, int max_size>
Deque<T, max_size>::Node::~Node()
{
	delete this->next_node;
}

template <typename T, int max_size>
Deque<T, max_size>::Node::Node(Node *_next_node, Node *_prev_node)
{
	next_node = _next_node;
	prev_node = _prev_node;
}

template <typename T, int max_size>
struct Deque<T, max_size>::iterator
{	
	Node *this_node;
	int index; //在buffer中的位置

	//++iterator
	Deque<T, max_size>::iterator &operator++();
	//iterator++
	Deque<T, max_size>::iterator operator++(int);

	Deque<T, max_size>::iterator &operator--();
	Deque<T, max_size>::iterator operator--(int);

	bool operator==(const Deque<T, max_size>::iterator &itr);
	bool operator!=(const Deque<T, max_size>::iterator &itr);

	T &operator*();

	iterator();
	iterator(Node *new_node, int _index = 0);
	~iterator();
};

//当只有一块时且index+1==size，++会导致iterator指向last_node,只能修改插入函数了
template <typename T, int max_size>
typename Deque<T, max_size>::iterator Deque<T, max_size>::iterator::operator++(int)
{	
	auto tmp = *this;
	if (this->index + 1 == this->this_node->elements.size())
	{	
		this->index = 0;
		this->this_node = this->this_node->next_node;
		return tmp;
		
	}
	this->index++;
	return tmp;
}

template <typename T, int max_size>
typename Deque<T, max_size>::iterator &Deque<T, max_size>::iterator::operator++()
{
	if (this->index + 1 == this->this_node->elements.size())
	{
		this->index = 0;
		this->this_node = this->this_node->next_node;
	}
	else
	{
		this->index++;
	}
	return *this;
}

template <typename T, int max_size>
typename Deque<T, max_size>::iterator &Deque<T, max_size>::iterator::operator--()
{
	if (this->index == 0)
	{
		this->this_node = this->this_node->prev_node;
		index = this->this_node->elements.size() - 1;
	}
	else
	{
		this->index--;
	}
	return *this;
}

template <typename T, int max_size>
typename Deque<T, max_size>::iterator Deque<T, max_size>::iterator::operator--(int)
{	
	auto tmp = *this;
	if (this->index == 0)
	{
		this->this_node = this->this_node->prev_node;
		index = this->this_node->elements.size() - 1;
		return tmp;
	}

	this->index--;
	return tmp;
}

template <typename T, int max_size>
bool Deque<T, max_size>::iterator::operator==(const Deque<T, max_size>::iterator &itr)
{
	return (this->this_node == itr.this_node) && (this->index == itr.index);
}

template <typename T, int max_size>
bool Deque<T, max_size>::iterator::operator!=(const Deque<T, max_size>::iterator &itr)
{
	return (this->this_node != itr.this_node) || (this->index != itr.index);
}

template <typename T, int max_size>
T &Deque<T, max_size>::iterator::operator*()
{
	return this_node->elements[index];
}

template <typename T, int max_size>
Deque<T, max_size>::iterator::iterator()
{
	this_node = nullptr;
	index = 0;
}

template <typename T, int max_size>
Deque<T, max_size>::iterator::iterator(Node *new_node, int _index)
{
	this_node = new_node;
	index = _index;
}

template <typename T, int max_size>
Deque<T, max_size>::iterator::~iterator(){};

template <typename T, int max_size>
typename Deque<T, max_size>::iterator Deque<T, max_size>::begin()
{
	return typename Deque<T, max_size>::iterator(this->first_node, 0);
}

template <typename T, int max_size>
typename Deque<T, max_size>::iterator Deque<T, max_size>::end()
{
	return Deque<T, max_size>::iterator(this->last_node, 0);
}

template <typename T, int max_size>
const typename Deque<T, max_size>::iterator Deque<T, max_size>::cbegin()
{
	return Deque<T, max_size>::iterator(this->first_node, 0);
}

template <typename T, int max_size>
const typename Deque<T, max_size>::iterator Deque<T, max_size>::cend()
{
	return Deque<T, max_size>::iterator(this->last_node, 0);
}

template <typename T, int max_size>
template <typename ...Args>
void Deque<T, max_size>::emplace_back(Args && ...args)
{
	if (last_node->prev_node->elements.size() == max_size)
	{
		last_node->prev_node->next_node = new Node(last_node, last_node->prev_node);
		last_node->prev_node = last_node->prev_node->next_node;
		last_node->prev_node->elements.emplace_back(std::forward<T>(args)...);
	}
	else
	{
		last_node->prev_node->elements.emplace_back(std::forward<T>(args)...);
	}
	++size;
}

template <typename T, int max_size>
template <typename ...Args>
void Deque<T, max_size>::emplace_front(Args && ...args)
{
	if (first_node->elements.size() == max_size)
	{
		first_node->prev_node = new Node(first_node, nullptr);
		first_node = first_node->prev_node;
		first_node->elements.emplace(first_node->elements.begin(), std::forward<Args>(args)...);
	}
	else
	{
		first_node->elements.emplace(first_node->elements.begin(), std::forward<Args>(args)...);
	}
	++size;
}

template <typename T, int max_size>
template <typename ...Args>
void Deque<T, max_size>::emplace(Deque<T, max_size>::iterator pos, Args && ...args)
{	
	if(pos.this_node==last_node)
	{
		throw std::exception();
		return;
	}
	if (pos.this_node->elements.size() == max_size || pos.this_node->next_node == last_node)
	{
		T last_elem = pos.this_node->elements.back();
		if (pos.this_node->next_node->elements.size() == max_size)
		{
			Node *temp_node = new Node(pos.this_node->next_node, pos.this_node);
			pos.this_node->next_node->prev_node = temp_node;
			pos.this_node->next_node = temp_node;

			auto it = pos.this_node->elements.begin() + pos.index;
			auto remove_it=pos.this_node->elements.end()-1;
			temp_node->elements.emplace(temp_node->elements.begin(), last_elem);
			pos.this_node->elements.erase(remove_it);
			pos.this_node->elements.emplace(it,std::forward<Args>(args)...);
		}
		else if(pos.this_node->next_node!=last_node)
		{
			auto it = pos.this_node->elements.begin() + pos.index;
			auto remove_it=pos.this_node->elements.end()-1;
			pos.this_node->next_node->elements.emplace(pos.this_node->next_node->elements.begin(), last_elem);
			pos.this_node->elements.erase(remove_it);
			pos.this_node->elements.emplace(it, std::forward<Args>(args)...);
		}
		else if(pos.this_node->elements.size() == max_size && pos.this_node->next_node == last_node)
		{
			Node *temp_node = new Node(pos.this_node->next_node, pos.this_node);
			pos.this_node->next_node->prev_node = temp_node;
			pos.this_node->next_node = temp_node;

			auto it = pos.this_node->elements.begin() + pos.index;
			auto remove_it=pos.this_node->elements.end()-1;
			temp_node->elements.emplace(temp_node->elements.begin(), last_elem);
			pos.this_node->elements.erase(remove_it);
			pos.this_node->elements.emplace(it,std::forward<Args>(args)...);
		}
		else
		{
			auto it = pos.this_node->elements.begin() + pos.index;
			pos.this_node->elements.emplace(it, std::forward<Args>(args)...);
		}
	}
	else
	{
		auto it = pos.this_node->elements.begin() + pos.index;
		pos.this_node->elements.emplace(it, std::forward<Args>(args)...);
	}
}