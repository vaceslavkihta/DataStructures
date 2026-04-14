#include "RBT.h"

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