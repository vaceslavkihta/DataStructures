#pragma once
#include <iostream>
#include <queue>
#include <initializer_list>
#include <Windows.h>
#include <string>

using std::cout, std::endl, std::cerr;
using std::queue;
using std::initializer_list;
using std::string;

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
		iterator find_placement(const KeyT& key) {
			Node<KeyT>* currNode = root;
			while (currNode != nullptr) {
				if (key > currNode->key && currNode->right != nullptr) { currNode = currNode->right; }
				else if (key < currNode->key && currNode->left != nullptr) { currNode = currNode->left; }
				else break;
			}
			return currNode == nullptr ? iterator(root) : iterator(currNode);
		}

		void fixInsert(Node<KeyT>* node) {
			bool isLeft = false;
			Node<KeyT>* g = node->parent ? node->parent : nullptr, * u;

			if (iAmRight(node, g)) { u = g->left; }
			else { u = g->right; isLeft = true; }

			if (isRed(node)) {
				if (isNode(u) && isRed(u)) {
					if (g != root) { reverseColour(g, node, u); }
					else { reverseColour(node, u); }
	
					if (isNode(g->parent) && isRed(g->parent)) { fixInsert(g->parent); }// какую ноду передавать?
				}
				else if (!isNode(u)) {
					if (isLeft) { RRB(node); }
					else { LRB(node); }
					reverseColour(g, node);
				}
				else if (isNode(u) && isBlack(u)) {
					Node<KeyT>* ch = (isNode(node->left) && isRed(node->left)) ? node->left : node->right;

					if (isLeft) {
						if (iAmLeft(ch, node)) { RRB(node); reverseColour(node, g); }
						else { LR(node); RRB(g->left); reverseColour(ch, g); } // попробовать else{ LR(...); fixInsert(node); } т.к. дублирование кода
					}
					else {
						if (iAmRight(ch, node)) { LRB(node); reverseColour(node, g); }
						else { RR(node); LRB(g->right); reverseColour(ch, g); }
					}	
				}
			}
		}
		void fixErase(Node<KeyT>* node) {
			Node<KeyT>* p = node->parent;

			if (node->colour == red && node->right == nullptr && node->left == nullptr) { delete node; return; } // V1
			else if (node->colour == black) { // V2
				bool isLeft = false;  // true: deletion node is p->right
				Node<KeyT>* ch;        // [Дублирующая проверка]

				if (node == p->right) { ch = p->right; isLeft = 1; }
				else { ch = p->left; }

				if (isRed(p)) { // V2.1
					if (isNode(ch)) {
						if (!isLeft && isLeftCh(ch)) { RR(ch); LRB(p->right); } // Дублирующия проверка
						else if (isLeft && isRightCh(ch)) { LR(ch); RRB(p->left); } // возможно условие избыточно
					}
					else { reverseColour(p, ch); }
					delete node;
				}
				else { // V2.2 
					if (isNode(ch) && isRed(ch)) {  // возможно условие избыточно
						Node<KeyT>* d = isLeft ? ch->right->left : ch->left->right;

						if (isNode(d) && isRed(d)) { // isRed возможно избыточно
							if (isLeft) { LR(ch); RRB(p); }
							else { RR(ch); LRB(p); }
						}
						else {
							if (isLeft) { RRB(ch); }
							else { LRB(ch); }
							reverseColour(d);
						}
						delete node;
					}
					else if (isNode(ch) && isBlack(ch)) {
						Node<KeyT>* c = isLeft ? ch->right : ch->left;
						if (isNode(c)) {
							if (isLeft) { RR(ch); LRB(c); }
							else { LR(ch); RRB(c); }
							reverseColour(c);
						}
						else { reverseColour(ch); }
						delete node;
					}
				}
			}
		}

		void LR(Node<KeyT>* node) {
			Node<KeyT>* x = node->right, * ch = node->left;
			x->parent = node->parent;
			node->parent->left = x;
			if (isNode(ch)) {
				node->parent = ch;
				ch->left = node;
			}
			else {
				node->parent = x;
				x->left = node;
			}
		}
		void RR(Node<KeyT>* node) {
			Node<KeyT>* x = node->left, * ch = node->right;
			x->parent = node->parent;
			node->parent->right = x;
			if (isNode(ch)) {
				node->parent = ch;
				ch->right = node;
			}
			else {
				node->parent = x;
				x->right = node;
			}
		}
		void RRB(Node<KeyT>* node) {
			Node<KeyT>* child = node->right,
				* ggf = node->parent->parent != 0 ? node->parent->parent : nullptr;
			node->right = node->parent;
			if (ggf != nullptr) {
				node->parent = ggf;
				node == ggf->left ? ggf->left = node : ggf->right = node;
			}
			else { root = node; node->parent = nullptr;	}
			node->right->parent = node;
		
			if (child != nullptr) {
				node->right->left = child;
				child->parent = node->right;
			}
			else{ node->right->left = nullptr; }
			
		}
		void LRB(Node<KeyT>* node) {
			Node<KeyT>* child = node->left,
				* ggf = node->parent->parent != 0 ? node->parent->parent : nullptr;
			node->left = node->parent;
			if (ggf != nullptr) {
				node->parent = ggf;
				node == ggf->left ? ggf->left = node : ggf->right = node;
			}
			else { root = node; node->parent = nullptr; }
			node->left->parent = node;
			
			if (child != nullptr) {
				node->left->right = child;
				child->parent = node->left;
			}
			else{ node->left->right = nullptr; }
		}

	public:
		struct iterator;

		rbt() :root(nullptr), sz(0) { ; }
		rbt(KeyT key) { insert(key); }
		rbt(initializer_list<KeyT> list) {
			for (auto&& key : list) {
				insert(key);
			}
		}
		rbt(const rbt&);
		rbt(rbt&& rhs) noexcept : root(rhs.root), sz(rhs.sz) {
			rhs.root = nullptr;
			rhs.sz = 0;
		}

		rbt& operator=(const rbt&);
		rbt& operator=(rbt&& rhs) noexcept {
			root = rhs.root; sz = rhs.sz;
			rhs.root = nullptr; rhs.sz = 0;
		}

		/*~rbt() {
			for (auto it = begin(), itNext = ++it, itEnd = end(); it != itEnd; ++it, ++itNext) {
				delete it.getNode();
				it = itNext;
			}
		}*/

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

			void increment() {
				if (node->right != nullptr) {
					node = node->right;
					while (node->left != nullptr) { node = node->left; }
				}
				else {
					Node<KeyT>* tmpParent = node->parent;
					while (node == tmpParent->right) {
						node = tmpParent;
						tmpParent = tmpParent->parent;
					}
					if (node->right != tmpParent) { node = tmpParent; }
				}
			}
			void decrement() {
				Node<KeyT>* tmpParent = node->parent;
				if (node->left == nullptr) {
					while (node == tmpParent->left) {
						node = tmpParent;
						tmpParent = node->parent;
					}
					node = tmpParent->right;
				}
				else { node = node->left; }
			}

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
			reference operator*() { return node->key; } // Сомнительно

			bool operator==(iterator rhs) { return node == rhs.node; }
			bool operator!=(iterator rhs) { return !(node == rhs.node); }

			Node<KeyT>* getNode() const { return node; }
		};

		size_t size() const { return sz; }
		bool empty() const { return sz == 0 ? 1 : 0; }

		void insert(const KeyT& key) {
			if (sz > 0) {
				Node<KeyT>* place = find_placement(key).getNode();
				if (key > place->key) { place->right = new Node<KeyT>{ key, place, nullptr, nullptr, red }; }
				else if (key < place->key) { place->left = new Node<KeyT>{ key, place, nullptr, nullptr, red }; }
				
				if(isRed(place)){ fixInsert(place); }
			}
			else {
				root = new Node<KeyT>{ key, nullptr, nullptr, nullptr, black };
			}
			++sz;
		}
		void erase(const KeyT& key) {
			auto deletionNode = find(key).getNode();
			fixErase(deletionNode);
			--sz;
		}
		
		void print() {
			queue<Node<KeyT>*> q;
			q.push(root);
			while (!q.empty()) {
				int levelSize = q.size();

				for (int i = 0; i < levelSize; ++i) {
					auto node = q.front();
					q.pop();

					if (isRed(node)) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); }
					else { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); }

					Node<KeyT>* p = node->parent ? node->parent : nullptr,
						* leftCh = node->left ? node->left : nullptr,
						* rightCh = node->right ? node->right : nullptr;
					bool isLeft = false;

					if (isNode(p) && iAmLeft(node, p)) { isLeft = true; }
					string dir = isLeft ? " (L)" : " (R)";
					if (node == root) { dir = ""; }					
					
					cout << node->key << " (P: " << getKey(p) << dir << "; L: " << getKey(leftCh)
						<< "; R: " << getKey(rightCh) << ")" << "\t";

					if (isNode(node->left)) { q.push(node->left); }
					if (isNode(node->right)) { q.push(node->right); }
				}
				cout << endl;
			}
		}

		void printList() {
			queue<Node<KeyT>*> q;
			q.push(root);
			while (!q.empty()) {
				int levelSize = q.size();

				auto node = q.front();
				q.pop();

				cout << node->key << " ";

				if (isNode(node->left)) { q.push(node->left); }
				if (isNode(node->right)) { q.push(node->right); }
			}
		}
		
		iterator find(const KeyT& key) { // замерить с проверкой left/right перед переходом и без нее
			Node<KeyT>* currNode = root;
			while (currNode->key != key) {
				if (currNode->key > key) { currNode = currNode->left; }
				else if (currNode->key < key) { currNode = currNode->right; }
			}
			return currNode == nullptr ? iterator(root) : iterator(currNode);
		}

		iterator begin() {
			auto currNode = root;
			while (isLeftCh(currNode)) {
				currNode = currNode->left;
			}
			return iterator(currNode);
		}
		iterator end() { return iterator(root); }
	};

	template <typename KeyT>
	void revCol(Node<KeyT>* node) {
		if (node->colour == black) { node->colour = red; }
		else { node->colour = black; }
	}

	template<typename... Args>
	void reverseColour(Args... args) {
		(revCol(args), ...);
	}

	template <typename KeyT>
	bool isNode(Node<KeyT>* node) { return node != nullptr ? true : false; }

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

	template <typename KeyT>
	string getKey(Node<KeyT>* node){
		if (isNode(node)) { return std::to_string(node->key); }
		else { return "nil"; }
	}
}