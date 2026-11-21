#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

void printList(Node* head)
{
    Node* curr = head;
    while(curr != NULL)
    {
        cout << curr->data << "->";
        curr=curr->next;
    }
    cout << "NULL" << endl;
}

Node* reverseList(Node* head)
{   
    Node* curr = head;
    Node* prev = NULL;
    while(curr!=NULL){
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main()
{
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);
    cout << "Original List: " << endl;
    printList(head);
    cout << "Reversed List: " << endl;
    Node* result = reverseList(head);
    printList(result);
    return 0;
}

/*
Time Complexity: O(n)
Space Complexity: O(1)
*/