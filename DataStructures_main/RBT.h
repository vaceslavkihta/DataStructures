#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>

using std::cout, std::endl, std::cerr;
using std::unique_ptr, std::make_unique;
using std::initializer_list;

namespace DataStructures {
	enum Colours { black, red };

	template <typename KeyT>
	struct Node;

	template <typename KeyT>
	class rbt {
		Node<KeyT>* root = nullptr;
		std::size_t sz = 0;
		
	public:
		struct iterator;

		rbt(KeyT);
		rbt(initializer_list<KeyT>);
		rbt(const rbt&);
		rbt(rbt&&);

		rbt& operator=(const rbt&);
		rbt& operator=(rbt&&);

		~rbt();

		size_t size() const;
		bool empty() const;

		void insert(const KeyT&);
		void erase(const KeyT&);
		iterator find(const KeyT&);

		iterator begin();
		iterator end();

		struct iterator {
			Node<KeyT>* node;

			iterator();
			iterator(Node<KeyT>*);
			iterator(const iterator&);

			void increment(); /* must be private/protected
			void decrement();    must be private/protected */
			
			using difference_type = std::ptrdiff_t;
			using value_type = Node<KeyT>;
			using pointer = Node<KeyT>*;
			using reference = Node<KeyT>&;
			using iterator_category = std::bidirectional_iterator_tag;

			void operator++();
			void operator--();
			void operator*();
		};
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


}