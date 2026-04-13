#include "RBT.h"

template <typename KeyT>
using rbt = DataStructures::rbt<KeyT>;

template <typename KeyT>
using iterator = DataStructures::rbt<KeyT>::iterator;

template <typename KeyT>
rbt<KeyT>::rbt(KeyT root) : root(root) { ; }


template<typename KeyT>
void DataStructures::rbt<KeyT>::iterator::increment() {
	if (node->right != nullptr) {
		node = node->right;
		while (node->left != nullptr) { node = node->left; }
	}
	else {
		Node<KeyT>* tmpParent = node->parent;
		while (node == node->right) {
			node = tmpParent;
			tmpParent = tmpParent->parent;
		}
		if (node->right != tmpParent) { node = tmpParent; }
	}
}






#ifdef FIND
template<typename KeyT>
iterator<KeyT> rbt<KeyT>::find(const KeyT& key) {
	Node<KeyT>* currNode = root;
	while (currNode != nullptr) {
		if (currNode->key > key) { currNode = currNode->right; }
		else if (currNode->key < key) { currNode = currNode->left; }
	}
	return iterator<KeyT>(currNode);
}
#endif