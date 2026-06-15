#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int val = 0) : data(val), next(nullptr) {}
};
Node *creatList(int *arr, int n)
{
    if (n == 0)
        return nullptr;
    Node *head = new Node(arr[0]);
    Node *curr = head;
    for (int i = 1; i < n; i++)
    {
        curr->next = new Node(arr[i]);
        curr = curr->next;
    }
    return head;
}
void traverseList(Node *head)
{
    if (!head)
        return;
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
    int n = sizeof(arr) / sizeof(arr[0]);
    Node *head = creatList(arr, n);
    traverseList(head);
    deleteList(head);
    return 0;
}