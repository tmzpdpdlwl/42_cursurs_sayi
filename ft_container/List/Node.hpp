#ifndef NODE_HPP
# define NODE_HPP

# include <cstring>
# include <iostream>
namespace ft
{
template<typename value_type>
class Node
{
private:
	Node<value_type> *m_previous;
	value_type m_value;
	Node<value_type> *m_next;
public:
	Node(): m_previous(this), m_value(), m_next(this) {}
	Node(value_type const &val):
		m_previous(this), m_value(val), m_next(this) {}
	Node(Node *previous, value_type const &val, Node *next=NULL):
		m_previous(previous), m_value(val), m_next(next) {}
	Node(Node const &other):
		m_previous(other.m_previous), m_value(other.val), m_next(other.m_next) {}
	virtual ~Node() {}

	void insert_node(Node *node) {
		node->m_next = this;
		node->m_previous = this->m_previous;
		this->m_previous->m_next = node;
		this->m_previous = node;
	}

	void disconnect(void) {
		this->m_previous->m_next = this->m_next;
		this->m_next->m_previous = this->m_previous;
	}

	void swap(Node *node) {
		if (this->m_next == node) {
			this->m_previous->m_next = node;
			node->m_previous = this->m_previous;
			this->m_previous = node;
			node->m_next->m_previous = this;
			this->m_next = node->m_next;
			node->m_next = this;
		} else if (this->m_previous == node) {
			node->m_previous->m_next = this;
			this->m_previous = node->m_previous;
			node->m_previous = this;
			this->m_next->m_previous = node;
			node->m_next = this->m_next;
			this->m_next = node;
		} else {
			Node<value_type> *previous = this->m_previous;
			Node<value_type> *next = this->m_next;

			this->m_previous->m_next = node;
			this->m_next->m_previous = node;
			this->m_previous = node->m_previous;
			this->m_next = node->m_next;
			node->m_previous->m_next = this;
			node->m_next->m_previous = this;
			node->m_previous = previous;
			node->m_next = next;
		}
	}

	void reverse(void) {
		Node<value_type> *tmp = this->m_previous;
		this->m_previous = this->m_next;
		this->m_next = tmp;
	}

	void swap_values(Node *node) {
		value_type tmp;
		std::memmove(static_cast<void*>(&tmp), static_cast<void*>(&node->m_value), 1);
		std::memmove(static_cast<void*>(&node->m_value), static_cast<void*>(&this->m_value), 1);
		std::memmove(static_cast<void*>(&this->m_value), static_cast<void*>(&tmp), 1);
	}

	value_type &value(void) {
		return (this->m_value);
	}
	value_type const &value(void) const {
		return (this->m_value);
	}

	Node *&previous(void) {
		return (this->m_previous);
	}
	Node const *previous(void) const {
		return (this->m_previous);
	}

	Node *&next(void) {
		return (this->m_next);
	}
	Node const *next(void) const {
		return (this->m_next);
	}
};
}

#endif
