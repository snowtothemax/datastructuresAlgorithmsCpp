#include <iostream>
#include <string>
#include <array>

// In this implementation, I should have used utility functions in order to simplify my needs

class Node{
    public:
        /// @brief The left child node
        Node* left;

        /// @brief The right child node
        Node* right;

        /// @brief The parent node
        Node* parent;

        /// @brief The nodes value
        int value;

        /// @brief The nodes (subtree's) height
        int height;

        bool isRoot;

        /// @brief 
        /// @param val 
        /// @param newParent 
        Node(int val, Node* newParent){
            left=nullptr;
            right=nullptr;
            parent=newParent;
            isRoot=false;
            height=1;
            value=val;
        }

        /// @brief 
        /// @param isRoot 
        Node(bool isRoot){
            left=nullptr;
            right=nullptr;
            parent=nullptr;
            isRoot=isRoot;
            height=0;
            value=INT_MAX;
        }

        /// @brief 
        /// @param val 
        /// @param child 
        /// @param grandChild 
        /// @return 
        bool add(int val,Node* child,Node* grandChild)
        {
            bool success=false;
            if (value==val)
            {
                return false;
            }
            if (val>value)
            {
                if (!right)
                {
                    right=new Node(val,this);
                    grandChild=right;
                    child=this;
                    return true;
                }
                else success = right->add(val,child,grandChild);
            }
            else
            {
                if (!left)
                {
                    left=new Node(val,this);
                    grandChild=left;
                    child=this;
                    return true;
                }
                else success = left->add(val,child,grandChild);
            }
            
            if (success && !isRoot)
            {
                int heightDifference = right->maxDepth()-left->maxDepth();
                if (heightDifference <= 1 && heightDifference>=-1)
                {
                    return true;
                }
                // Height Balance
                // LeftLeft
                Node* oldParent = parent;
                Node* T1 = nullptr;
                Node* T2 = nullptr;
                Node* T3 = nullptr;
                Node* T4 = nullptr;
                if (child==left&&grandChild==left->left)
                {
                    T1 = grandChild->left;
                    T2 = grandChild->right;
                    T3 = child->right;
                    T4 = right;

                    setLeftChild(T3);
                    setRightChild(T4);
                    child->setLeftChild(grandChild);
                    child->setRightChild(this);
                    child->parent=oldParent;
                }
                // LeftRight
                else if (left==child&&left->right==grandChild)
                {
                    T1 = child->left;
                    T2 = grandChild->left;
                    T3 = grandChild->right;
                    T4 = right;

                    child->setRightChild(T2);
                    setLeftChild(T3);
                    grandChild->setLeftChild(child);
                    grandChild->setRightChild(this);
                    grandChild->parent=oldParent;
                }
                //RightRight
                else if(right==child&&right->right==grandChild)
                {
                    T1 = left;
                    T2 = child->left;
                    T3 = grandChild->left;
                    T4 = grandChild->right;

                    setLeftChild(T1);
                    setRightChild(T2);
                    grandChild->setLeftChild(T3);
                    grandChild->setRightChild(T4);
                    child->setLeftChild(this);
                    child->setRightChild(grandChild);
                    child->parent=oldParent;
                }
                //rightLeft
                else
                {
                    T1 = left;
                    T2 = grandChild->left;
                    T3 = grandChild->right;
                    T4 = child->right;

                    setLeftChild(T1);
                    setRightChild(T2);
                    child->setLeftChild(T3);
                    child->setRightChild(T4);
                    grandChild->setLeftChild(this);
                    grandChild->setRightChild(child);
                    grandChild->parent=oldParent;
                }
            }
            grandChild=child;
            child=this;
            return success;
        }
        /// @brief 
        /// @return 
        int maxDepth()
        {
            if (isLeafNode())
            {
                return 1;
            }
            int leftHeight=0;
            int rightHeight=0;
            if (left)
            {
                leftHeight=left->height;
            }
            if (right)
            {
                rightHeight=right->height;
            }
            if (leftHeight>rightHeight) height=leftHeight+1;
            height=rightHeight+1;
            return height;
        }
        /// @brief Sets the right child of this node to child
        /// @param child The node to set to the right child
        void setRightChild(Node* child)
        {
            right=child;
            child->parent=this;
        }
        /// @brief 
        /// @param child 
        void setLeftChild(Node* child)
        {
            left=child;
            child->parent=this;
        }
        /// @brief 
        /// @return 
        bool isRightChild() {
            return parent->right==this;
        }
        /// @brief 
        /// @param child 
        /// @param newParent 
        void setParentChild(Node *child, Node* newParent)
        {
            child->parent = parent;
            if (isRightChild())
            {
                parent->right=child;
            }
            else parent->left=child;

            parent=newParent;
        }
        /// @brief 
        /// @return 
        bool isLeafNode()
        {
            return !left && !right;
        }
        Node* get(int value)
        {
            if (isLeafNode())
            {
                return nullptr;
            }
            if (value==this->value)
            {
                return this;
            }
            else if (value>this->value && right)
            {
                return right->get(value);
            }
            else if (value<this->value && left)
            {
                return left->get(value);
            }
            else return nullptr;
        }
};

class BalancedBinaryTree{
    public:
        Node* root;
        BalancedBinaryTree(){
            root=new Node(true);
        }
        ~BalancedBinaryTree(){
            delete root;
        }
        bool add(int val)
        {
            return root->add(val,nullptr,nullptr);
        }
        Node* get(int value)
        {
            return root->get(value);
        }
};

int main()
{
    BalancedBinaryTree *tree = new BalancedBinaryTree();
    std::cout << tree->add(1);
    std::cout << tree->add(2);
    std::cout << tree->add(3);
    std::cout << tree->add(4);
    std::cout << tree->add(5);
    std::cout << tree->add(6);
    std::cout << tree->add(7);
    std::cout << tree->add(8);
    std::cout << tree->add(9);
}
