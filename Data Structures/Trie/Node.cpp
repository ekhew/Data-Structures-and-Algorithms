/*
Title: Trie Node
Author: Edwin Khew
Description: Trie node class implementation.
Date Created: 7/4/2021
*/

Node::Node():character_('\0'), end_of_word_(false) { }

Node::Node(char c):character_(c), end_of_word_(false) { }

void Node::setChar(char c)
{
    character_ = c;
}

void Node::setEndOfWord(bool end_of_word)
{
    end_of_word_ = end_of_word;
}

char Node::getChar()
{
    return character_;
}

bool Node::getEndOfWord()
{
    return end_of_word_;
}

bool Node::hasChildren()
{
    for(int i = 0; i < CHILDREN_; i++) //traverse through the entire array of pointers
    {
        if(children_[i] != nullptr) //if a child is found, return true
        {
            return true;
        }
    }

    return false;
}
