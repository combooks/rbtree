#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

struct data_struct {
	int data_val;
	struct rb_node data_rb;
};

static struct rb_root data_rbtree = RB_ROOT;

static struct data_struct *search(struct rb_root *root, int value) {
	struct data_struct *data;
	struct rb_node *node = root->rb_node;

	while (node) {
		data = rb_entry(node, struct data_struct, data_rb);

		if (value < data->data_val)
			node = node->rb_left;
		else if (data->data_val < value)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}

static int __insert(struct rb_root *root, struct data_struct *new_data) {
	struct data_struct *data;
	struct rb_node **node = &root->rb_node, *parent = NULL;

	while (*node) {
		data = rb_entry(*node, struct data_struct, data_rb);
		parent = *node;

		if (new_data->data_val < data->data_val)
			node = &((*node)->rb_left);
		else if (data->data_val < new_data->data_val)
			node = &((*node)->rb_right);
		else
			return -1;
	}
	rb_link_node(&new_data->data_rb, parent, node);
	rb_insert_color(&new_data->data_rb, root);

	return 0;
}

static int insert(int value) {
	struct data_struct *new_data;

	new_data = (struct data_struct *)malloc(sizeof(struct data_struct));
	new_data->data_val = value;
	return __insert(&data_rbtree, new_data);
}

static int delete(int value) {
	struct data_struct *data = search(&data_rbtree, value);

	if (data) {
		rb_erase(&data->data_rb, &data_rbtree);
		free(data);
		return 0;
	}
	return -1;
}

static void __print_inorder(struct rb_node *node) {
	struct data_struct *data;

	if (node == NULL)
		return;

	__print_inorder(node->rb_left);

	data = rb_entry(node, struct data_struct, data_rb);
	printf("%d ", data->data_val);

	__print_inorder(node->rb_right);
}

static void print_inorder(void) {
	printf("Inorder: ");
	__print_inorder(data_rbtree.rb_node);
	printf("\n");
}

int main(void) {
	insert(7);
	insert(6);
	insert(5);
	insert(4);
	insert(3);
	insert(2);
	insert(1);

	print_inorder();

	delete(3);
	delete(6);
	delete(9);

	print_inorder();

	return 0;
}
