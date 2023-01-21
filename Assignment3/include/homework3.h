//BLG 335E ANALYSIS OF ALGORITHMS 1 HOMEWORK 3
//Leminur Çelik
//150190085
#ifndef _H
#define _H

#include <string>

using namespace std;

//Node Class creates the node with the following properties
class Node {
	public:
		string name; //Hold the name of the node
		int vruntime; //Hold the virtual run time
		int bursttime; //Hold the burst time
		Node *parent; //Pointer to the parent
		Node *left; //Pointer to left child
		Node *right; //Pointer to right child
		int color; //0-Black, 1-Red
};

//RBTree Class implements the operations in Red Black Tree
class RBTree {
	private:
		Node* root; //Pointer to root
		Node* TNULL; //Pointer to NILL node

		//Fix the red-black tree modified by insert operation
		void fixupInsert(Node* x){
			Node* uncle; //Create a node for uncle
			while (x->parent->color == 1){ //While parent's color is red
				if(x->parent == x->parent->parent->right){//If grandparent's right is parent 
					uncle = x->parent->parent->left; //Set uncle to grandparent's left child
					if(uncle->color == 1){//If uncle's color is red, then this is the case 1
						uncle->color = 0; //Change uncle's color to black
						x->parent->color = 0; //Change parent's color to black
						x->parent->parent->color = 1; //Change grandparent's color to red
						x = x->parent->parent; //Put grandparent to x
					} 
					else{
						if(x == x->parent->left){ //If x's uncle's color is black and x is a left child, then this is the case 2
							x = x->parent; //Put parent to x
							rightRotate(x); //Rotate right at node x
						}
						//If x's uncle is black and x is a right child, then this is the case 3
						x->parent->color = 0; //Change parent's color to black
						x->parent->parent->color = 1; //Change grandparent's color to red
						leftRotate(x->parent->parent); //Rotate left at x's grandparent
					}
				} 
				else{
					uncle = x->parent->parent->right; //Set uncle to grandparent's right child

					if(uncle->color == 1){ //If uncle's color is red, then this is the case 1
						uncle->color = 0; //Change uncle's color to black
						x->parent->color = 0; //Change parent's color to black
						x->parent->parent->color = 1; //Change grandparent's color to red
						x = x->parent->parent; //Put grandparent to x
					} 
					else{
						if(x == x->parent->right){ //If x's uncle's color is black and x is a right child, then this is the case 2
							x = x->parent; //Put parent to x
							leftRotate(x); //Rotate left at node x
						}
						//If x's uncle is black and x is a left child, then this is the case 3
						x->parent->color = 0; //Change parent's color to black
						x->parent->parent->color = 1; //Change grandparent's color to red
						rightRotate(x->parent->parent); //Rotate right at x's grandparent
					}
				}
				if(x == root){ //If the node is root, then break while loop
					break;
				}
			}
			root->color = 0; //Set root color to black
		}

		//Fix the red black tree modified by the delete operation
		void fixupDelete(Node* x) {
			Node* s; //Create a node
			while (x != root && x->color == 0) { //While x is not root and x's color is black
				if(x == x->parent->left){ //If x is x's parent's left, then this is the case 1
					s = x->parent->right; //Assign x's sibling to created node
					if(s->color == 1){ //If x's sibling s's color is red, then this is the case 1
						s->color = 0; //Change x's sibling's color to black
						x->parent->color = 1; //Change parent's color to red
						leftRotate(x->parent); //Rotate left at point parent
						s = x->parent->right; //Assign parent's right to created node
					}

					if(s->left->color == 0 && s->right->color == 0){ //If x's sibling's color, and its children's color are black, then this is the case 2
						s->color = 1; //Change x's sibling's color to red
						x = x->parent; //Set x's parent to x
					} 
					else{
						if(s->right->color == 0){ //If x's sibling's color and its right child's color are black and its left child's color is red, then this is the case 3
							s->left->color = 0; //Change x's siblings left's color to black
							s->color = 1; //Change x's sibling's color to red
							rightRotate(s); //Rotate right at point x's sibling
							s = x->parent->right; //Set parent's right to x's sibling
						}
						//If x's sibling's color is black and its right child's color is red, then this is the case 4
						s->color = x->parent->color; //Assign parent's color to x's sibling
						x->parent->color = 0; //Change parent's color to black
						s->right->color = 0; //Change x's sibling's right child's color to black
						leftRotate(x->parent); //Rotate left at point parent
						x = root; //Set root to x
					}
				} 
				else{
					s = x->parent->left; //Assign x's sibling to created node
					if (s->color == 1) { //If x's sibling s's color is red, then this is the case 1
						s->color = 0; //Change x's sibling's color to black
						x->parent->color = 1; //Change parent's color to red
						rightRotate(x->parent); //Rotate right at point parent
						s = x->parent->left; //Assign parent's left to created node
					}

					if(s->right->color == 0 && s->left->color == 0){ //If x's sibling's color, and its children's color are black, then this is the case 2
						s->color = 1; //Change x's sibling's color to red
						x = x->parent; //Set x's parent to x
					} 
					else{
						if(s->left->color == 0){ //If x's sibling's color and its left child's color are black and its right child's color is red, then this is the case 3
							s->right->color = 0; //Change x's siblings right's color to black
							s->color = 1; //Change x's sibling's color to red
							leftRotate(s); //Rotate left at point x's sibling
							s = x->parent->left; //Set parent's right to x's sibling
						} 
						//If x's sibling's color is black and its left child's color is red, then this is the case 4
						s->color = x->parent->color; //Assign parent's color to created node
						x->parent->color = 0; //Change parent's color to black
						s->left->color = 0; //Change x's sibling's left child's color to black
						rightRotate(x->parent); //Rotate right at point parent
						x = root; //Set root to x
					}
				} 
			}
			x->color = 0; //Set root's color to black
		}

		//Replace two nodes with each other
		void rbTransplant(Node* u, Node* v){
			if(u->parent == nullptr){
				root = v;
			} 
			else if(u == u->parent->left){
				u->parent->left = v;
			} 
			else{
				u->parent->right = v;
			}
			v->parent = u->parent; //Updates parents
		}

	
	public:
		//Constructor of RBTree
		RBTree(){
			TNULL = new Node; //Create NILL node
			TNULL->color = 0; //Assign NILL node's color to black
			TNULL->left = nullptr; //Assign NILL node's left to NULL
			TNULL->right = nullptr; //Assign NILL node's right to NULL
			root = TNULL; //Assign root to NILL
		}
		
		//Get the root of the tree
		Node* getRoot(){
			return this->root; //Return root
		}

		//Find the node with the minimum run time
		Node* minimum(Node* node){
			while (node->left != TNULL){ //While the left of this node is not NILL, this node is updated with the one to the left
				node = node->left;
			}
			return node; //Return the minimum run time of node in tree
		}

		//Check if there are nodes smaller than or equal to the vruntime of the minimum node
		bool exist_minimum(Node* min){
			if(min != root){ //If the node is not root, then compare parent node's vruntime value
				if(min->parent->vruntime <= min->vruntime){ //If node's vruntime value is bigger than its parent node's vruntime value, then return true
					return true;
				}
			}
			else{ //If the node is root, then compare right node's vruntime value
				if(min->right->name != ""){
					if(min->right->vruntime == min->vruntime){ //If node's vruntime value is equal to its right node's vruntime value, then return true
						return true;
					}
				}
			}
			return false; //Return false if the top two comparisons are not provided
		}
	
		//Rotate left at node x
		void leftRotate(Node* x){
			Node* y = x->right; //Set y
			x->right = y->left; //Turn y's left subtree into x's right subtree
			if(y->left != TNULL){ //If y's left is not NILL, then assign x to the y's left's parent
				y->left->parent = x;
			}
			y->parent = x->parent; //Assign x's parent to y's parent
			if(x->parent == nullptr){ //If x's parent is NULL, then assign y to the root of tree 
				this->root = y;
			} 
			else if(x == x->parent->left){ //If x is equal to x's parent's left then assign y to the x's parent's left
				x->parent->left = y;
			} 
			else{ //Else assign y to the x's parent's right
				x->parent->right = y;
			}
			y->left = x; //Put x on y's left
			x->parent = y; //Put y to the x's parent
		}

		//Rotate right at node x
		void rightRotate(Node* x){
			Node* y = x->left; //Set y
			x->left = y->right; //Turn y's right subtree into x's left subtree
			if(y->right != TNULL){ //If y's right is not NILL, then assign x to the y's right's parent
				y->right->parent = x;
			}
			y->parent = x->parent; //Assign x's parent to y's parent
			if(x->parent == nullptr){ //If x's parent is NULL, then assign y to the root of tree 
				this->root = y;
			} 
			else if(x == x->parent->right){ //If x is equal to x's parent's left then assign y to the x's parent's right
				x->parent->right = y;
			} 
			else{ //Else assign y to the x's parent's right
				x->parent->left = y;
			}
			y->right = x; //Put x on y's right
			x->parent = y; //Put y to the x's parent
		}

		//Insert the node with its the name, run time and burst time to the tree in its appropriate position and fix the tree
		void insert(string name, int vruntime, int burst_time){
			Node* node = new Node; //Create a new Node
			node->parent = nullptr; //Assign NULL to node's parent
			node->vruntime = vruntime; //Assign run time which takes as an input to node's vruntime 
			node->name = name; //Assign name which takes as an input to node's name
			node->bursttime = burst_time; //Assign burst time which takes as an input to node's burst time 
			node->left = TNULL; //Assign NILL to node's left
			node->right = TNULL; //Assign NILL to node's right
			node->color = 1; //Assign red to node's color because new node must be red

			Node* y = nullptr; //Assign NULL to node y
			Node* x = this->root; //Assign root to node x

			while(x != TNULL){ //While x is not NILL
				y = x; //Assign x to y
				if(node->vruntime < x->vruntime){ //If node's vruntime is smaller than x's vruntime, then assign x's left to x
					x = x->left;
				} 
				else{ //Else, then assign x's right to x
					x = x->right;
				}
			}
			node->parent = y; //y is parent of node
			if (y == nullptr) { //If y is NULL
				root = node; //Assign node to root
			} 
			else if (node->vruntime < y->vruntime){ //If node's vruntime is smaller than y's vruntime
				y->left = node; //Assign node to y's left
			} 
			else { //Else assign node to y's right
				y->right = node;
			}
			//If new node is a root node, change node's color to black and simply return
			if (node->parent == nullptr){
				node->color = 0;
				return;
			}
			//If the grandparent is null, simply return
			if (node->parent->parent == nullptr) {
				return;
			}
			// Fix the tree
			fixupInsert(node);
		}

		//Delete the node from the tree which takes root node, run time and name of the node to be deleted as inputs
		void deleteNode(Node* node, int vrun_time, string name) {
			Node* z = TNULL;
			Node* x;
			Node* y;
			while(node != TNULL){
				if(node->vruntime == vrun_time && node->name == name){
					z = node;
				}

				if(node->vruntime <= vrun_time && node->name == name){
					node = node->right;
				}
				else{
					node = node->left;
				}
			}
			if (z == TNULL) {
				cout<<"Couldn't find vrun_time in the tree"<<endl;
				return;
			} 
			y = z; //Set y to z
			int y_original_color = y->color; //original color of y stores y’s color before any changes occur
			if(z->left == TNULL){
				x = z->right; //Set x to y's only child
				rbTransplant(z, z->right);
			} 
			else if(z->right == TNULL){
				x = z->left; //Set x to y's only child
				rbTransplant(z, z->left);
			} 
			else{
				y = minimum(z->right); //Sets y to z's successor
				y_original_color = y->color; //y original color stores y’s color before any changes occur
				x = y->right; //If y has no children, set x to TNULL
				if(y->parent == z){
					x->parent = y; //Set x's parent to original position of y's parent
				} 
				else{
					rbTransplant(y, y->right);
					y->right = z->right; 
					y->right->parent = y; 
				}

				rbTransplant(z, y);
				y->left = z->left; 
				y->left->parent = y; 
				y->color = z->color; //Give y as the same color as z
			}
			delete z;
			if (y_original_color == 0){ //If y's color was black, then removing or moving y cause violations of the red black properties
				fixupDelete(x); //Call this function to restore red black properties
			}
		}
		
		//Print the tree using inorder traversal
		void print_inorder(Node* node){ 
			if(node != TNULL){
				print_inorder(node->left); //Print left of node
				string color_name;
				if(node->color == 0){ //If node's color id is 0 that means color name is black
					color_name = "Black";
				}
				else{ //If node's color id is 1 that means color name is red
					color_name = "Red";
				}
				cout << node->name << ":" << node->vruntime << "-" << color_name << ";"; //Print the name, virtual run time and color of this node
				print_inorder(node->right); //Print right of node
			} 
		}
};
#endif