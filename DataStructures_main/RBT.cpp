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
template <typename Compare>
DS::rbt<KeyT>::iterator DS::rbt<KeyT>::find(const KeyT&, Compare compare) {
	Node<KeyT>* currNode = root;
	while (compare() )
}