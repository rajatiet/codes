// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v, Node* next = NULL) {
        val =v;
        next=NULL;
    }
};

//1->2->3->4->5->6->7->8
//k=2
//2->1->3->4->6_.5->7->8

void print_list(Node* head) {
    cout << "###List###" << endl;
    while (head) {
        cout << " " << head->val;
        head = head->next;
    }
    cout << endl;
}

Node* alternate_reverse(Node* head, int k) {
    if (!head)
        return head;
    if (k<=1)
        return head;
    Node* tmp=head;
    int nrev;
    int nskip;
    bool is_new_head_set = false;
    
//1->2->3->4->5->6->7->8
//k=2
//2->1->3->4->5->6->7->8

//2->1->3->4-> 5->6->7->8
//6->5->NULL;
//prev=6
//prev1=4

    Node* prev=NULL;
    Node* curr=tmp;
    Node* prev1= NULL;
    while (curr) {
        nrev=0;
        Node* next=NULL;
        tmp = curr;
        while (nrev <k && curr) {
            if (curr->next)
                next = curr->next;
            curr->next = prev;
            prev=curr;
            curr = next;
            nrev++;
        }
        if (prev1)
            prev1->next = prev;
        tmp->next = curr;
        if (!is_new_head_set) {
            head = prev;
            is_new_head_set = true;
        }
        nskip=0;
        while (nskip<k && curr) {
            prev = curr;
            curr=curr->next;
            nskip++;
        }
        prev1 = prev;
    }
    return head;    
}

int main() {
    // Write C++ code here
    //1->2->3->4->5->6->7->8
    Node* head= new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);
    head->next->next->next->next->next->next = new Node(7);
    head->next->next->next->next->next->next->next = new Node(8);
    //Node* n= new Node(1, new Node(2, new Node(3, new Node(4, new Node(5, new Node(6, new Node(7, new Node(8))))))));
    print_list(head);
    int k = 2;
    head = alternate_reverse(head, k);
    cout << "after reverse" << endl;
    print_list(head);
    cout << "finished" << endl;
    return 0;
}
