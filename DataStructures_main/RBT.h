#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>
#include <exception>

using std::cout, std::endl, std::cerr;
using std::unique_ptr, std::make_unique;
using std::initializer_list;

namespace DataStructures {
	enum Colours { black, red };

	template <typename KeyT>
	struct Node {
		KeyT key;
		Node* parent, * left, * right;
		Colours colour;
	};

	template <typename KeyT>
	class rbt {
		Node<KeyT>* root = nullptr;
		std::size_t sz = 0;

		struct iterator;
		iterator find_placement(const KeyT&);
		
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
	void LR(Node<KeyT>*);

	template <typename KeyT>
	void RR(Node<KeyT>*);

	template <typename KeyT>
	void LRB(Node<KeyT>*);

	template <typename KeyT>
	void RRB(Node<KeyT>*);

	template <typename KeyT>
	void fixInsert(Node<KeyT>* node) {
		bool isLeft = false;
		Node<KeyT>* g = node->parent ? node->parent : nullptr,
			* u = g != nullptr ? g->right == node ? g->left, isLeft = true : g->right : nullptr;

		if (node->colour == red) {
			if (u != nullptr && u->colour == red) {
				g->colour = red;
				node->colour = black;
				u->colour = black;
				if (g->parent->colour == red) { fixInsert(g->parent); }// какую ноду передавать?
			}
			else if (u != nullptr && u->colour == black) {
				if (isLeft && node->left->colour == red) {
					LR(node), RRB(node->parent);
				}
				else if (!isLeft && node->right->colour) {
					RR(node), LRB(node->parent);
				}

				if (isLeft && node->right->colour == red) { LRB(node); reverseColour(g, node->right); }
				else if (!isLeft && node->left->colour == red) { RRB(node); reverseColour(g, node->left); }
			}
		}
	}

	template <typename KeyT>
	void fixErase(Node<KeyT>* node) {
		Node<KeyT>* p = node->parent;

		if (node->colour == red && node->right == nullptr && node->left == nullptr) { delete node; return; } // V1
		else if (node->colour == black) { // V2
			Node<KeyT>* ch = node == p->left ? p->right : p->left; // [ƒублирующа€ проверка]

			if (p->colour == red) { // V2.1
				if (isChild(ch)) {
					if (iAmRight(ch, p) && isLeftCh(ch)) { RR(ch); LRB(p->right); } // ƒублирующи€ проверка
					else if (iAmLeft(ch, p) && isRightCh(ch)) { LR(ch); RRB(p->left); } // возможно условие избыточно
				}
				else { reverseColour(p, ch); }
				delete node;
			}	

			else { // V2.2 
				if (isChild(ch) && isRed(ch)) {  // возможно условие избыточно
					if (iAmRight(ch, p) && isChild(ch->left->right)) {
						if (isRed(ch->left->right)) {

						}
						else {
							RRB(ch); reverseColour(ch, ch->right); // ch->right проверить
						}
					}


					if (ch->left != nullptr && ch->left->colour == black) {
						if (ch->left->right != nullptr && ch->left->right->colour == red){
							// ћалый (ch) + большой (p->right); d -> black
						}
						else {
							// Ѕольшой (ch), C -> красный, B -> черный
						}
					}
				}
				else if (ch != nullptr && ch->colour == black) {
					if (ch->left != nullptr) {

					}
					else {

					}
				}
			}
		}
	}

	template<typename KeyT>
	void balancing(Node<KeyT>*);	

	template <typename KeyT>
	void revCol(Node<KeyT>* node) {
		if (node->colour == black) node->colour = red;
		else node->colour = black;
	}

	template<typename... Args>
	void reverseColour(Args... args) {
		(revCol(args), ...);
	}

	template <typename KeyT>
	bool isChild(Node<KeyT>* node) { return node != nullptr ? true : false; }

	template <typename KeyT>
	bool isLeftCh(Node<KeyT>* node) { return node->left != nullptr ? true : false; }

	template <typename KeyT>
	bool isRightCh(Node<KeyT>* node) { return node->right != nullptr ? true : false; }

	template <typename KeyT>
	bool iAmRight(Node<KeyT>* node, Node<KeyT>* parent) { return parent->right == node ? true : false; }

	template <typename KeyT>
	bool iAmLeft(Node<KeyT>* node, Node<KeyT>* parent) { return parent->left == node ? true : false; }

	template <typename KeyT>
	bool isRed(Node<KeyT>* node) { return node->colour == red ? true : false; }

	template <typename KeyT>
	bool isBlack(Node<KeyT>* node) { return node->colour == black ? true : false; }

}