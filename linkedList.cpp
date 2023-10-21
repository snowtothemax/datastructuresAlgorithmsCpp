#include <iostream>
#include <string>
#include <array>

class Node{
    public:
        Node* previous;
        Node* next;
        int val;
        Node(){
            
        }
};

class LinkedList{
    public:
        Node* head;
        Node* tail;
        LinkedList()
        {

        }

        void add(Node* node)
        {
            if (!head)
            {
                head=node;
                return;
            }
            if (!tail)
            {
                tail = node;
                head->next=tail;
                return;
            }

            Node* curr = tail;
            tail->next = node;
            tail=node;
            tail->previous=curr;
        }

        void remove(Node* node)
        {
            if (!head)
            {
                return;
            }
            if (head == node)
            {
                Node* temp = head->next;
                if (!temp)
                {
                    head = nullptr;
                    return;
                }
                temp->previous=nullptr;
                head=temp;
                return;
            }
            if (tail == node)
            {
                Node* temp = tail->previous;
                temp->next = nullptr;
                tail = temp;
                return;
            }
            Node* curr = head;
            while(curr->next)
            {
                if (curr->next == node)
                {
                    Node* temp = curr->next;
                    curr->next=temp->next;
                    curr->next->previous=curr;
                    return;
                }
            }
        }

        Node* find(int val)
        {
            if (!head)
            {
                return nullptr;
            }
            if (head->val == val)
            {
                return head;
            }
            if (tail->val == val)
            {
                return tail;
            }
            Node* curr = head;
            while(curr->next)
            {
                if (curr->next->val == val)
                {
                    return curr->next;
                }
            }
            return nullptr;
        }
};

int main()
{
    LinkedList *list = new LinkedList();
    Node* curr = new Node();
    Node* curr2 = new Node();
    curr->val=3;
    std::cout << curr->val;
    list->add(curr);
    curr2 = list->find(3);
    std::cout << curr2->val;
    list->remove(curr);
    if (!list->head)
    {
        std::cout << "YAY!";
    }
}
