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
	struct Node {
		KeyT val;
		Node* parent, * left, * right;
		Colours colour;
	};

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
			using difference_type = std::ptrdiff_t;
			using value_type = KeyT;
			using pointer = KeyT*;
			using reference = KeyT&;
			using iterator_category = std::bidirectional_iterator_tag;

			Node<KeyT>* node;

			iterator() : node(nullptr) { ; }
			iterator(Node<KeyT>* src) : node(src) { ; }
			iterator(const iterator& rhs) : node(rhs.node) { ; }

			void increment();
			void decrement();
			
			iterator& operator++() { increment(); return *this; }
			iterator& operator++(int) {
				iterator tmp = *this;
				increment();
				return tmp;
			}
			iterator& operator--() { decrement(); return *this; }
			iterator& operator--(int) {
				iterator tmp = *this;
				decrement();
				return tmp;
			}
			reference operator*() { return node->value; }
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