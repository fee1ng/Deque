#include <iostream>
#include "Deque.h"

int main()
{
	Deque<int> deq;
	deq.pop_front();
	deq.pop_back();

	//push_back
	for(int i = 1; i < 10; i++)
		deq.push_back(i);
	
	//emplace_front
	/*deq.emplace_front(999);
	for (int i = 0; i < 14; i++)
		std::cout << deq[i] << " ";
	std::cout << std::endl;*/

	//push_front
	/*deq.push_front(100);
	for (auto t : deq)
	{
		std::cout << t << " ";
	}
	std::cout<<endl;
	std::cout<<deq.getSize()<<endl;*/

	//operator[] at()
	std::cout<<deq[1]<<std::endl;
	std::cout<<deq.at(1)<<std::endl;

	//pop_front() pop_back()
	//deq.pop_front();
	//deq.pop_back();
	for (auto t : deq)
	{
		std::cout << t << " ";
	}
	std::cout<<endl;

	//emplace_back
	deq.emplace_back(100);
	auto it=deq.end();
	it--;
	deq.erase(it);
	for (auto t : deq)
	{
		std::cout << t << " ";
	}
	std::cout<<endl;

	auto itr = deq.begin();

	//operator++ 
	/*for(int i=0;i<8;i++)
		itr++;
	cout<<*(++itr)<<endl;
	cout<<*itr<<endl;*/
	itr++;
	itr++;
	itr++;
	
	//insert
	deq.insert(itr,100);
	for(auto i:deq)
		cout<<i<<" ";
	cout<<endl;

	//emplace 
	deq.emplace(itr, 36);
	for(auto t:deq)
		cout<<t<<" ";
	cout<<endl;

	//erase
	deq.erase(itr);
	for (auto t : deq)
	{
		std::cout << t << " ";
	}
	cout<<endl;

	return 0;
}