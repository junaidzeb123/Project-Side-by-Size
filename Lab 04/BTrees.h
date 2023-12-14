#include "Vector.h"
#include "File.h"
#include <queue>
#include <cmath>
struct BNode {
	Vector<File*> key;
	Vector<BNode*> children;
	bool leaf;
	const int order;
	BNode* parent;
	BNode(int order, bool l = false) : key(order + 1), children(order + 2), order(order) {
		leaf = l;
		parent = nullptr;
	}
	void TraverseList(File* file) {
		File* curr = file;
		while (curr) {
			std::cout << *curr;
			curr = curr->next;
		}
		std::cout << ' ';
	}
	void displayNode() {
		for (int i = 0; i < key.size; ++i) {
			TraverseList(key[i]);
		}
		std::cout << "| ";
	}
	int getSize() { return key.size; }
};
class BTree {
	BNode* root;
	const int order;



	void printKey(int key, int level) {
		std::cout << "Level " << level << ": " << key << std::endl;
	}


	void merge(BNode*& node, int idx, int nextIdx) {
		BNode* childNode = node->children[idx];

		BNode* newNode = nullptr;
		if (nextIdx > idx) {
			BNode* rightNode = node->children[nextIdx];
			childNode->key.push_back(node->key[idx]);

			for (int i = 0; i < rightNode->key.size; ++i) {
				childNode->key.push_back(rightNode->key[i]);
				if (rightNode->children.size > 0)
					childNode->children.push_back(rightNode->children[i]);
			}

			if (rightNode->children.size > 0) {
				childNode->children.push_back(rightNode->children.peek());
				rightNode->children.pop();
			}
			newNode = childNode;
			node->children[idx] = newNode;
			node->key.remove(idx);
			node->children.remove(nextIdx);
		}
		else {
			BNode* leftNode = node->children[nextIdx];
			leftNode->key.push_back(node->key[nextIdx]);
			for (int i = 0; i < childNode->key.size; ++i) {
				leftNode->key.push_back(childNode->key[i]);
				if (leftNode->children.size > 0)
					leftNode->children.push_back(childNode->children[idx]);
			}
			if (leftNode->children.size > 0) {
				leftNode->children.push_back(childNode->children.peek());
				childNode->children.pop();
			}
			newNode = leftNode;
			node->children[idx] = newNode;
			node->key.remove(nextIdx);
			node->children.remove(idx);
		}

		if (node == root && node->key.size == 0)
			root = newNode;


	}
	void removeSibling(BNode* node, int idx, int nextIdx) {

		BNode* childNode = node->children[idx];
		if (idx < nextIdx) {
			BNode* rightNode = node->children[nextIdx];
			childNode->key.push_back(node->key[idx]);
			node->key[idx] = rightNode->key[0];
			if (rightNode->children.size > 0) {
				childNode->children.push_back(rightNode->children[0]);
				rightNode->children.remove(0);
			}
			rightNode->key.remove(0);
		}
		else {
			BNode* leftNode = node->children[nextIdx];
			childNode->key.insert(node->key[idx - 1], 0);
			node->key[idx - 1] = leftNode->key.peek();
			leftNode->key.pop();
			if (leftNode->children.size > 0)
			{
				childNode->children.insert(leftNode->children.peek(), 0);
				childNode->children.pop();
			}
		}

	}

	void adjustTree(BNode*& node, int idx) {

		if (idx > 0 && idx + 1 < node->getSize() + 1) {
			if (node->children[idx + 1]->getSize() >= ceil(order / 2.0))
				removeSibling(node, idx, idx + 1);
			else if (node->children[idx - 1]->getSize() >= ceil(order / 2.0))
				removeSibling(node, idx, idx - 1);
			else
				merge(node, idx, idx + 1);
		}
		else if (idx == 0) {
			if (node->children[idx + 1]->getSize() >= ceil(order / 2.0))
				removeSibling(node, idx, idx + 1);
			else
				merge(node, idx, idx + 1);


		}
		else if (idx + 1 == node->getSize() + 1) {
			if (node->children[idx - 1]->getSize() >= ceil(order / 2.0))
				removeSibling(node, idx, idx - 1);
			else
				merge(node, idx, idx - 1);
		}

	}
	void deleteListNode(File* node) {
		File* curr = node, * prev = nullptr;
		int count = 1;
		std::cout << "These are the results that we have found in our DataBase: \n";
		while (curr) {
			std::cout << "Press " << count << " for " << *curr << '\n';
			curr = curr->next;
			++count;

		}
		curr = node;
		int input;
		std::cin >> input;
		count = 1;
		while (count < input) {
			prev = curr;
			curr = curr->next;
			++count;
		}

		if (prev)
			prev->next = curr->next;
		else {
			curr = node;
			node = node->next;
		}
		delete curr;


	}
	std::string getLeastValInSubtree(BNode* node) {

		BNode* curr = node;
		while (!curr->leaf)
			curr = curr->children[0];

		return curr->key[0]->Hash;
	}
	void removeInternalNode(BNode*& node, std::string value, int idx) {
		std::string least = getLeastValInSubtree(node->children[idx + 1]);
		node->key[idx]->Hash = least;
		removeRecur(least, node->children[idx + 1]);
	}

	void removeRecur(std::string value, BNode*& node) {
		int idx = 0;
		while (idx < node->key.size && *node->key[idx] < value) ++idx;
		if (!node->leaf && idx < node->key.size && *node->key[idx] == value) {

			if (node->key[idx]->next)
			{
				deleteListNode(node->key[idx]);
				return;
			}
			removeInternalNode(node, value, idx);
			++idx;
		}
		else if (idx < node->key.size && *node->key[idx] == value) {
			if (node->key[idx]->next)
			{
				deleteListNode(node->key[idx]);
				return;
			}
			node->key.remove(idx);

			return;
		}
		else
			removeRecur(value, node->children[idx]);

		if (node->children[idx]->getSize() < ceil(order / 2.0) - 1)
			adjustTree(node, idx);

	}

	void splitRoot() {
		BNode* newRoot = new BNode(order);
		newRoot->children.push_back(root);
		splitChild(newRoot, 0);
		root = newRoot;
	}
	void insertLinkedList(File*& fileNode, File*& value) {
		File* curr = fileNode;
		while (curr->next) curr = curr->next;
		curr->next = value;
	}
	void insertRecur(BNode*& node, File*& value, BNode* parent = nullptr, int childIdx = -1) {

		if (node == nullptr) return;
		int repeat = node->key.includes(value);
		if (repeat != -1) {
			insertLinkedList(node->key[repeat], value);
			return;
		}
		if (node->leaf) {

			node->parent = parent;
			node->key.addInOrder(value);

			if (node->getSize() >= order) {
				if (parent == nullptr)
					splitRoot();
				else
					splitChild(parent, childIdx);
			}
			return;
		}
		int idx = 0;
		int keySize = node->getSize();

		while (idx < keySize && value > node->key[idx]) ++idx;

		insertRecur(node->children[idx], value, node, idx);

		if (node->getSize() >= order) {
			if (parent == nullptr)
				splitRoot();
			else
				splitChild(parent, childIdx);
		}

	}
	void splitChild(BNode*& node, int idx) {

		BNode* fullChild = node->children[idx];

		BNode* newChild = new BNode(order, fullChild->leaf);

		if (node->children[idx] != this->root)
			node->children.insert(newChild, idx + 1);
		else node->children.push_back(newChild);

		int medianKey = ceil(order / 2.0);
		node->key.insert(fullChild->key[medianKey - 1], idx);


		for (int idx = medianKey; idx < order; ++idx)
			newChild->key.push_back(fullChild->key[idx]);



		fullChild->key.pop(order - medianKey + 1);

		if (!fullChild->leaf) {
			for (int idx = medianKey; idx < order + 1; ++idx)
				newChild->children.push_back(fullChild->children[idx]);


			fullChild->children.pop(order - medianKey + 1);
		}

	}
	File* traverseListAndSearch(File* file) {
		File* curr = file;
		int count = 1;
		std::cout << "These are the results that we have found in our DataBase: \n";
		while (curr) {
			std::cout << "Press " << count << " for " << *curr << '\n';
			curr = curr->next;
			++count;

		}
		curr = file;
		int input;
		std::cin >> input;
		count = 1;
		while (count < input) {
			curr = curr->next;
			++count;
		}
		if (count == input) std::cout << "FOUND IT" << std::endl;
		return curr;
	}
public:
	BTree(int order) : order(order) {
		root = new BNode(order, true);
	}
	File* search(std::string key, BNode* node = nullptr) {
		node = node == nullptr ? root : node;
		if (!node) return nullptr;
		int idx = 0;
		while (idx < node->key.size && key > node->key[idx]->Hash)
			++idx;

		if (idx < node->key.size && key == node->key[idx]->Hash) {

			return traverseListAndSearch(node->key[idx]);
		}
		else
			search(key, node->children[idx]);
	}

	void insert(std::string Name, std::string Hash) {
		File* value = new File({ Name, Hash });
		insertRecur(root, value);
	}
	void search(File*& key, BNode* node = nullptr) {
		node = node == nullptr ? root : node;
		if (!node) return;
		int idx = 0;
		while (idx < node->key.size && key > node->key[idx])
			++idx;

		if (idx < node->key.size && key == node->key[idx]) {
			std::cout << "found " << node->key[idx];
			return;
		}
		else if (node->leaf) return;
		else
			search(key, node->children[idx]);
	}


	void remove(std::string value) {
		removeRecur(value, root);
	}
	void display() {
		if (root == nullptr) return;

		std::queue<BNode*> q;
		q.push(root);


		while (!q.empty()) {
			int nodeCount = q.size();
			std::cout << "{";
			while (nodeCount > 0) {
				BNode* current = q.front();
				q.pop();
				if (!current) {
					std::cout << "}\t{";
					nodeCount--;
					continue;
				}
				// Process the current node (e.g., print keys)

				current->displayNode();
				std::cout << "|";
				if (!current->leaf) {
					// Enqueue children if not a leaf node
					for (int i = 0; i <= current->getSize(); ++i)
						q.push(current->children[i]);
				}
				q.push(nullptr);

				nodeCount--;
			}
			std::cout << "}";
			std::cout << "\n";
		}
	}

};