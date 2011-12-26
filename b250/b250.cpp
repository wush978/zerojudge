/*
 * b250.cpp
 *
 *  Created on: Dec 26, 2011
 *      Author: wush
 */

#include "b250.h"

typedef Node<Weight> WeightedNode;

void sum_child(WeightedNode& node)
{
	Weight left(0), right(0);
	WeightedNode *temp;
	if (node.get_left()) {
		temp = node.get_left();
		left = temp->get_content();
	}
	if (node.get_right()) {
		temp = node.get_right();
		right = temp->get_content();
	}
	node.set_content(left + right);
}

bool retval;
void check_child(WeightedNode& node)
{
	Weight left(0), right(0);
	WeightedNode *temp;
	if (node.get_left()) {
		temp = node.get_left();
		left = temp->get_content();
		temp = node.get_right();
		right = temp->get_content();
		retval &= (left == right);
	}
	return;
}

int main()
{
	Count quiz_size;
	std::cin >> quiz_size;
	std::vector< std::string > quiz;
	quiz.resize(quiz_size);
	for (Count i = 0;i < quiz_size;i++)
	{
		std::cin >> quiz[i];
	}

	for (Count i = 0;i < quiz_size;i++)
	{
		const std::string& current_quiz(quiz[i]);
		WeightedNode *root = new WeightedNode;
		WeightedNode *node = root;
		Weight weight(0);
		for (Count j = 0;j < current_quiz.size();j++)
		{
			if (current_quiz[j] == '(') {
				node->span();
				node = node->get_left();
				continue;
			}
			if (current_quiz[j] == ')') {
				node = node->get_parent();
				continue;
			}
			if (current_quiz[j] == ',') {
				node = node->get_parent();
				node = node->get_right();
				continue;
			}
			weight *= 10;
			weight += current_quiz[i] - '0';
			if (current_quiz[j+1] - '0' < 0) {
				node->set_content(weight);
				weight = 0;
			}
		}
		Node<Weight>::apply_tree(root, &sum_child);
		retval = true;
		Node<Weight>::apply_tree(root, &check_child);
		if (retval) {
			std::cout << "Yes" << std::endl;
		}
		else {
			std::cout << "No" << std::endl;
		}
	}
	return 0;
}
