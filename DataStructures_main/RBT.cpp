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
	while (currNode != nullptr) { // Протестить с && [TODO]
		if (currNode->key > key && currNode->right != nullptr) { currNode = currNode->left; }
		else if (currNode->key < key && currNode->left != nullptr) { currNode = currNode->right; }
	}
	return currNode == nullptr ? iterator(root) : iterator(currNode);
}

template <typename KeyT>
void DS::rbt<KeyT>::insert(const KeyT& key) {
	if (sz > 0) {
		Node<KeyT>* place = *find_placement(key);
		if (key > place->key) { place->right = new Node{ key, place, nullptr, nullptr, red }; }
		else if (key < place->key) { place->left = new Node{ key, place, nullptr, nullptr, red }; }
		fixInsert(place);
	}
	else {
		root = new Node{ key, nullptr, nullptr, nullptr, black };
	}
	++sz;	
}

