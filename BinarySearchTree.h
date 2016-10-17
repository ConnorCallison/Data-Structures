#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "TreeNode.h"
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
/*
Incomplete BST.  We will fill this out more in future lectures.
*/
using namespace std;
template <typename T>
class BinarySearchTree
{
private:
    TreeNode<T> *_root = nullptr;
    int _tree_size = 0;

protected:

	virtual TreeNode<T> *findLargestRec(TreeNode<T> *root)
	{
		//base case: root has no right child or root is null
		if (root == nullptr || root->getRightChild() == nullptr)
		{
			return root;
		}
		return findLargestRec(root->getRightChild());
	}

	//iterative version of find largest
	virtual TreeNode<T> *findLargestIter(TreeNode<T> *root)
	{
		while (root != nullptr || root->getRightChild() != nullptr)
		{
			root = root->getRightChild();
		}
		return root;
	}

	//iterative version of find smallest
	virtual TreeNode<T> *findSmallestIter(TreeNode<T> *root)
	{
		while (root != nullptr || root->getLeftChild() != nullptr)
		{
			root = root->getLeftChild();
		}
		return root;
	}

    virtual TreeNode<T> * addItemHelper(TreeNode<T> *root, T item)
	{
		//BASE CASE: null root
		if (root == nullptr)
		{
			//allocate new space, store value, then return.
			root = new TreeNode<T>{};
			root->setValue(item);
			return root;
		}

		//RECURSIVE CASE: root is not null
		if (item >= root->getValue())
		{
			//CASE 1: belongs on the right side of root
			TreeNode<T> *right = addItemHelper(
                                         root->getRightChild(),
                                         item
                                         );

			//update right side with reconfigured state
			root->setRightChild(right);
		}
		else
		{
			//CASE 2: belongs on the left side of root
			TreeNode<T> *left = addItemHelper(
                                        root->getLeftChild(),
                                        item
                                        );
			root->setLeftChild(left);
		}

		return root;
	}

	TreeNode<T> * removeItemHelper(TreeNode<T> *root, T value)
	{
		//assumption: root is not null
		if (root == nullptr)
		{
			return root;
		}

		//Three possibilities
		//base case: we found our value:
		if(root->getValue() == value)
		{
			//for now, we will find replacement from the left subtree
			if (root->getLeftChild() != nullptr)
			{
				//find the largest on the left to replace our value
				TreeNode<T> *largest = findLargestIter(root->getLeftChild());

				//make largest node's value our value
				root->setValue(largest->getValue());

				//mark largest node for removal
				//two cases: largest has no children
				//           largest has one left
				if (largest->getLeftChild() == nullptr)
				{
					delete largest;

					//TODO: laragest's parent now has a dangling NULL ptr
				}
			}
			else
			{
				//else, draw replacement from our sole right child
			}
		}
	}

    bool isAvlHelper(TreeNode<T> *root)
    {
        //Always guard against nullptr

        if(root == nullptr)
        {
            return true;
        }

        int left_Height = getHeightHelper(root->getLeftChild());
        int right_Height = getHeightHelper(root->getRightChild());

        if(abs(left_Height - right_Height) > 1)
        {
            return false;
        }
        else
        {
            return isAvlHelper(root->getLeftChild()) && isAvlHelper(root->getRightChild());
        }
    }

	int getHeightHelper(TreeNode<T> *root)
	{
	    // Base case null
	    if(root == nullptr)
        {
            return -1;
        }

        //capture left and right sides
        int left_height = getHeightHelper(root->getLeftChild());
        int right_height = getHeightHelper(root->getRightChild());

        if(left_height > right_height)
        {
            return left_height + 1;
        }
        else
        {
            return right_height + 1;
        }
	}

    bool IsFullHelper (TreeNode<T> *root)
    {
        //Base Case Root is null
        if(root == nullptr)
        {
            return true;
        }

        if(root->getLeftChild() != nullptr && root->getRightChild() != nullptr)
        {
            return IsFullHelper(root->getLeftChild()) && IsFullHelper(root->getRightChild());
        }

        else if(root->getLeftChild() == nullptr && root->getRightChild() == nullptr)
        {
            return true;
        }

        {
            return false;
        }
    }

public:
    virtual void addItem(T value)
    {
        _root = addItemHelper(_root, value);
        _tree_size++;
    }

	virtual void removeItem(T value)
	{
		_root = removeItemHelper(_root, value);
		_tree_size--;
	}

    bool isAvl()
    {
        return isAvlHelper(_root);
    }

    bool isFull()
    {

        return IsFullHelper(_root);
    }

	void preOrderTraversalHelper(TreeNode<T> *root, vector<TreeNode<T> *> &list)
	{
		//Base Case: root is null
		if (root == nullptr)
		{
			return;
		}

		//Invariant: root must not be null
		list.push_back(root);

		//do left
		preOrderTraversalHelper(root->getLeftChild(), list);

		//do right
		preOrderTraversalHelper(root->getRightChild(), list);

		////Possibility 2: root has no children
		//if (root->getLeftChild() == nullptr && root->getRightChild() == nullptr)
		//{
		//	list.push_back(root);
		//	return;
		//}
		//if (root->getLeftChild() != nullptr)
		//{
		//	//call ourselves
		//}
		//if (root->getRightChild() != nullptr)
		//{
		//	//call ourselves
		//}
	}

	//returns all nodes in tree using pre-order traversal pattern
	vector<TreeNode<T> *> preOrderTraversal()
	{
		vector<TreeNode<T> *>result{};
		preOrderTraversalHelper(_root, result);
		return result;
		//pattern:
		//U L R

		//step 1: look at us (put us in the vector)
		//step 2: put left into vector (recursive)
		//preOrderTraversal(); //this won't work because we need to remember
							 //what we've done
		//we need to track the "root" (relative defn, not necessairly actual root of
		                             //tree)
		//we also need to track the "mast vector" that we're adding to

		//step 3: put right into vector (recursive)
	}

	//iterative traversal using explicit stack
	vector<TreeNode<T> *> inOrderTraversal()
	{
		stack<TreeNode<T> *> nodes_to_visit{};
		vector<TreeNode<T> *> result{};

		//"prime" our loop by pushing _root into our nodes to visit
		nodes_to_visit.push(_root->getRightChild());
		nodes_to_visit.push(_root);
		nodes_to_visit.push(_root->getLeftChild());
		_root->setVisited(true);


		//keep going as long as there are more nodes to visit
		while (nodes_to_visit.empty() == false)
		{
			//L U R
			TreeNode<T> *next = nodes_to_visit.top();

			//can't use STL pop to get item, must use top() then pop() to remove
			nodes_to_visit.pop();
			if (next != nullptr)
			{
				if (next->isVisited() == false)
				{
					next->setVisited(true);

					//Right
					nodes_to_visit.push(next->getRightChild());

					//Us
					nodes_to_visit.push(next);

					//Left
					nodes_to_visit.push(next->getLeftChild());
				}
				else
				{
					result.push_back(next);
				}
			}
		}

		return result;
	}

};

#endif // BINARY_SEARCH_TREE_H
