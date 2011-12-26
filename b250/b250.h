/*
 * b250.h
 *
 *  Created on: Dec 27, 2011
 *      Author: wush
 */

#ifndef B250_H_
#define B250_H_
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned int Count;
typedef unsigned short Weight;

template <class Content>
class Node
{
typedef void NodeOperation(Node&);
	Content _content;
	Node* _parent;
	Node* _left;
	Node* _right;

	static void delete_node(Node& node)
	{
		delete &node;
	}

	void delete_child()
	{
		if (_left) {
			_left->delete_child();
			delete _left;
		}
		if (_right) {
			_right->delete_child();
			delete _right;
		}
		return;
	}

public:
	Node() : _parent(NULL), _left(NULL), _right(NULL) { }
	Node(Content content) : _content(content), _parent(NULL), _left(NULL), _right(NULL) { }

	void span()
	{
		set_left(new Node());
		get_left()->set_parent(this);
		set_right(new Node());
		get_right()->set_parent(this);
	}

	Node *get_root()
	{
		Node *retval = this;
		while (retval->get_parent())
		{
			retval = retval->get_parent();
		}
		return retval;
	}

	void static apply_tree(Node* node, NodeOperation* node_operation)
	{
		Node
			*prev = NULL,
			*current = node->get_root(),
			*next = NULL;
		while (current)
		{
			if (prev == current->get_parent()) {
				prev = current;
				next = current->get_left();
			}
			if (!next || prev == current->get_left()) {
				(*node_operation)(*current);
				prev = current;
				next = current->get_right();
			}
			if (!next || prev == current->get_right()) {
				prev = current;
				next = current->get_parent();
			}
			current = next;
		}

	}

	static void delete_tree(Node* node)
	{
		Node *root = node->get_root();
		root->delete_child();
		delete root;
	}

    Content get_content() const
    {
        return _content;
    }

    Node *get_left() const
    {
        return _left;
    }

    Node *get_parent() const
    {
        return _parent;
    }

    Node *get_right() const
    {
        return _right;
    }

    void set_content(Content content)
    {
        _content = content;
    }

    void set_left(Node *left)
    {
        _left = left;
    }

    void set_parent(Node *parent)
    {
        _parent = parent;
    }

    void set_right(Node *right)
    {
        _right = right;}

};




#endif /* B250_H_ */
