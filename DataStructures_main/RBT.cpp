#include "RBT.h"

namespace DS = DataStructures;

template<typename KeyT>
void DataStructures::rbt<KeyT>::iterator::increment() {
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

template <typename KeyT>
void DataStructures::rbt<KeyT>::iterator::decrement() {
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

template <typename KeyT>
void DataStructures::LR(Node<KeyT>* node) {
	Node<KeyT>* child = node->right;
	child->parent = node->parent;
	node->parent->left = child;
	node->parent = child;
	child->left = node;
}

template <typename KeyT>
void DataStructures::RR(Node<KeyT>* node) { 
	Node<KeyT>* child = node->right;
	child->parent = node->parent;
	node->parent->right = child;
	node->parent = child;
	child->right = node;
}

template <typename KeyT>
void DataStructures::RRB(Node<KeyT>* node) {
	Node<KeyT>* child = node->right, 
		* ggf = node->parent->parent != 0 ? node->parent->parent : nullptr;
	node->right = node->parent;
	if (ggf != nullptr){
		node->parent = ggf;
		node == ggf->left ? ggf->left = node : ggf->right = node;
	}
	node->right->parent = node;
	node->right->left = child;
	child->parent = node->right;
}

template <typename KeyT>
void DataStructures::LRB(Node<KeyT>* node) {
	Node<KeyT>* child = node->left,
		* ggf = node->parent->parent != 0 ? node->parent->parent : nullptr;
	node->left = node->parent;
	if (ggf != nullptr) {
		node->parent = ggf;
		node == ggf->left ? ggf->left = node : ggf->right = node;
	}
	node->left->parent = node;
	node->right->left = child;
	child->parent = node->right;
}

template <typename KeyT>
DS::rbt<KeyT>::iterator DS::rbt<KeyT>::find(const KeyT& key) { // замерить с проверкой left/right перед переходом и без нее
	Node<KeyT>* currNode = root;
	while (currNode->key != key) {
		if (currNode->key > key) { currNode = currNode->left; }
		else if (currNode->key < key) { currNode = currNode->right; }
	}
	return currNode == nullptr ? iterator(root) : iterator(currNode);
}

template <typename KeyT>
DS::rbt<KeyT>::iterator DS::rbt<KeyT>::find_placement(const KeyT& key) {
	Node<KeyT>* currNode = root;
	while (currNode->left != nullptr || currNode->right != nullptr) { // Протестить с && [TODO]
		if (currNode->key > key) { currNode = currNode->left; }
		else if (currNode->key < key) { currNode = currNode->right; }
	}
	return currNode == nullptr ? iterator(root) : iterator(currNode);
}

template <typename KeyT>
void DS::rbt<KeyT>::insert(const KeyT& key) {
	if (sz > 0) {
		Node<KeyT>* place = *find_placement(key);
		if (key > place->key) { place->right = new Node{ key, place, nullptr, nullptr, red }; }
		else if (key < place->key) { place->left = new Node{ key, place, nullptr, nullptr, red }; }
	}
	else {
		root = new Node{ key, nullptr, nullptr, nullptr, black };
	}
	++sz;	
}



template <typename KeyT>
void DS::fixInsert(Node<KeyT>* node) {
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
			if (isLeft && node->right->colour == red) { LRB(node); }
			else if (!isLeft && node->left->colour == red) { RRB(node); }
		}
	}
}