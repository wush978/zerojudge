/*
 * b250.cpp
 *
 *  Created on: Dec 26, 2011
 *      Author: wush
 */
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned int Count;
typedef unsigned short Weight;

enum NodeType
{
	Branch = 0,
	Leaf,
};

struct Node
{
	NodeType _type;
	Weight _weight;
	Node* _parent;
	Node* _left;
	Node* _right;
	Node() : _type(Leaf), _weight(0), _parent(NULL), _left(NULL), _right(NULL) { }
	Node(Node* parent) : _type(Leaf), _weight(0), _parent(parent), _left(NULL), _right(NULL) { }
	~Node()
	{
		if (_type == Branch)
		{
			delete _left;
			delete _right;
			return;
		}
		assert(!_left);
		assert(!_right);
	}
	static Node* TravelToRight(const Node& src)
	{
		assert(src._parent);
		Node* current_place = src._parent;
		current_place->sum();
		while (current_place->_right)
		{
			current_place = current_place->_parent;
			current_place->sum();
		}
		current_place->_right = new Node(current_place);
		return current_place->_right;
	}
	void sum()
	{
		if ( this->_left && this->_right )
		{
			this->_weight = this->_left->_weight + this->_right->_weight;
		}
	}
	Node* get_root()
	{
		if (!this->_parent)
			return this;
		Node* retval = this->_parent;
		while(retval->_parent)
		{
			retval = retval->_parent;
		}
		return retval;
	}
	bool is_valid()
	{
		if (_type == Branch)
		{
			return _left->_weight == _right->_weight;
		}
		return true;
	}
};


int main()
{
	Count quiz_size;
	std::vector<std::string> quiz;
	std::cin >> quiz_size;
	quiz.resize(quiz_size);
	for (Count i = 0;i < quiz_size;i++)
	{
		std::cin >> quiz[i];
	}

	for (Count i = 0;i < quiz_size;i++)
	{
		Node* node = new Node();
		const std::string& chime(quiz[i]);
		Weight weight = 0;
		for (Count j = 0;j < chime.size();j++)
		{
			if (chime[j] == '(')
			{
				node->_type = Branch;
				node->_left = new Node(node);
				node = node->_left;
				continue;
			}
			if (chime[j] == ',')
			{
				node = Node::TravelToRight(*node);
				continue;
			}
			if (chime[j] == ')')
			{
				continue;
			}
			weight *= 10;
			weight += chime[j] - '0';
			if (chime[j+1] - '0' < 0)
			{
				node->_weight = weight;
				weight = 0;
			}
		}
		Node *prev = NULL, *current = node->get_root(), *next = NULL;
		while (current)
		{
			if (prev == current->_parent)
			{
				prev = current;
				next = current->_left;
			}
			if (!next || prev == current->_left)
			{
				if (!current->is_valid())
				{
					std::cout << "No" << std::endl;
					break;
				}
				prev = current;
				next = current->_right;
			}
			if (!next || prev == current->_right)
			{
				prev = current;
				next = current->_parent;
			}
			current = next;
		}
		node = node->get_root();
		delete node;
	}
}


