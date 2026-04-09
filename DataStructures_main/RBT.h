#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>

using std::cout, std::endl, std::cerr;
using std::unique_ptr, std::make_unique;
using std::initializer_list;

/* 
==================================================



==================================================
*/

namespace DataStructures {
	template <typename KeyT>
	class rbt {
		Node<KeyT>* root = nullptr;
		std::size_t size = 0;
		
	public:
		rbt();
		rbt(KeyT);
		rbt(initializer_list<KeyT>);
		rbt(const rbt<KeyT>&);
		rbt(rbt<KeyT>&&);

		rbt& operator=(const rbt<KeyT>&);
		rbt& operator=(rbt<KeyT>&&);

		~rbt();
		

	};	

	template <typename KeyT>
	void leftRotate(Node<KeyT>*);

	template <typename KeyT>
	void rightRotate(Node<KeyT>*);

	template <typename KeyT>
	void leftRotateBig(Node<KeyT>*);

	template <typename KeyT>
	void rightRotateBig(Node<KeyT>*);

	template<typename KeyT>
	void balancing(Node<KeyT>*);

	template<typename KeyT>
	void find(const KeyT&);
}