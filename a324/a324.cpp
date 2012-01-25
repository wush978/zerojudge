
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "BinaryTreeNode.hpp"

const char* CODE[] = { "---.","--....",".-..-","-----",".--","..-.-","--..--","-...","-.--","..-..-.--","..-..--","----.","..---","-.-.","--.-","--...-","..-..-..-",".-.-","-..-","...",".-...","..-...","..--.","..-..-.-.","--..-.","..-..-..." };

typedef unsigned int Count;

int main()
{
	BTreeNode<char> root('\0');
	for (char alphabet = 'A'; alphabet != 'Z' + 1; alphabet++)
	{
		const char* code = CODE[alphabet - 'A'];
		BTreeNode<char> *current = &root;
		while (current->get_content() == '\0')
		{
			switch(*code++)
			{
			case '.' :
				current = current->get_left_new('\0');
				break;
			case '-':
				current = current->get_right_new('\0');
				break;
			case '\0':
				current->set_content(alphabet);
				break;
			default:
				assert(false);
			}
		}
	}

	Count question_count;
	std::cin >> question_count;
	std::vector<std::string> question;
	for (Count i = 0;i < question_count;i++)
	{
		question.push_back(std::string());
		std::getline(std::cin, question[i]);
		if (!question[i].size()) {
			question[i].clear();
			std::getline(std::cin, question[i]);
		}
	}
	for (Count question_label = 0; question_label < question_count;question_label++)
	{
		std::string retval;
		const std::string& code_string(question[question_label]);
		BTreeNode<char>* current = &root;
		for (Count code_label = 0;code_label < code_string.size();code_label++)
		{
			switch(code_string[code_label])
			{
			case '.' :
				current = current->get_left();
				assert(current);
				if (current->get_content() != '\0') {
					retval.push_back(current->get_content());
					current = &root;
				}
				break;
			case '-' :
				current = current->get_right();
				assert(current);
				if (current->get_content() != '\0') {
					retval.push_back(current->get_content());
					current = &root;
				}
				break;
			case ' ' :
				assert(current == &root);
				retval.push_back(' ');
				break;
			default:
				assert(false);
			}
		}
		std::cout << retval << std::endl;
	}
	return 0;
}
