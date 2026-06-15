#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int val = 0) : data(val), next(nullptr) {}
};
Node *creatList(int *arr, int len)
{
    if (len == 0)
        return nullptr;
    Node *head = new Node(arr[0]);
    Node *curr = head;
    for (int i = 1; i < len; i++)
    {
        curr->next = new Node(arr[i]);
        curr = curr->next;
    }
    return head;
}
bool insertNode(Node *head, int pos, int val)
{
    if (pos < 0)
        return false;
    Node *curr = head;
    for (int i = 0; i < pos - 1; i++)
    {
        if (curr == nullptr)
            return false;
        curr = curr->next;
    }
    Node *newNode = new Node(val);
    newNode->next = curr->next;
    curr->next = newNode;
    return true;
}
void traverseList(Node *head)
{
    Node *curr = head;
    while (curr)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}
void deleteList(Node *head)
{
    Node *curr = head;
    while (curr)
    {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    Node *head = creatList(arr, len);
    cout << "Original list: ";
    traverseList(head);
    int pos = 2;
    int val = 10;
    if (insertNode(head, pos, val))
    {
        cout << "After inserting " << val << " at position " << pos << ": ";
        traverseList(head);
    }
    else
    {
        cout << "Insertion failed at position " << pos << endl;
    }
    deleteList(head);
    return 0;
}
