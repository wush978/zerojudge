/*
 * BinaryTreeNode.hpp
 *
 *  Created on: 2012/1/25
 *      Author: wush
 */

#ifndef BINARYTREENODE_HPP_
#define BINARYTREENODE_HPP_

#ifndef NULL
#define NULL 0
#endif

template<class Content>
class BTreeNode
{
	typedef BTreeNode* pBTreeNode;
	pBTreeNode _parent;
	pBTreeNode _left;
	pBTreeNode _right;
	Content _content;
public:
	BTreeNode() : _parent(NULL), _left(NULL), _right(NULL) { }
	BTreeNode(const Content& content) : _parent(NULL), _left(NULL), _right(NULL), _content(content) { }
	~BTreeNode() {
		if (_left) {
			delete _left;
		}
		if (_right) {
			delete _right;
		}
	}

	pBTreeNode get_left_new(const Content& content)
	{
		if (!_left) {
			_left = new BTreeNode<Content>(content);
			_left->set_parent(this);
		}
		return _left;
	}

	pBTreeNode get_right_new(const Content& content)
	{
		if (!_right) {
			_right = new BTreeNode<Content>(content);
			_right->set_parent(this);
		}
		return _right;
	}

    pBTreeNode get_left() const
    {
        return _left;
    }

    pBTreeNode get_parent() const
    {
        return _parent;
    }

    pBTreeNode get_right() const
    {
        return _right;
    }

    void set_left(pBTreeNode left)
    {
        _left = left;
    }

    void set_parent(pBTreeNode parent)
    {
        _parent = parent;
    }

    void set_right(pBTreeNode right)
    {
        _right = right;
    }

    Content get_content() const
    {
        return _content;
    }

    void set_content(Content content)
    {
        _content = content;
    }
	
};


#endif /* BINARYTREENODE_HPP_ */
