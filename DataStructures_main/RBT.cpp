#include "RBT.h"

template <typename KeyT>
using rbt = DataStructures::rbt<KeyT>;

template <typename KeyT>
using iterator = DataStructures::rbt<KeyT>::iterator;

template <typename KeyT>
rbt<KeyT>::rbt(KeyT root) : root(root) { ; }












template<typename KeyT>
iterator<KeyT> rbt<KeyT>::find(const KeyT& key) {
	Node<KeyT>* currNode = root;
	while (currNode != nullptr) {
		if (currNode->key > key) { currNode = currNode->right; }
		else if (currNode->key < key) { currNode = currNode->left; }
	}
	return iterator<KeyT>(currNode);
}