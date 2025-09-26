#include <iostream>

using namespace std;

struct ListNode
{
    int data;
    ListNode* next;
    
    explicit ListNode(int val) : data(val), next(nullptr) {}
};

void printList(ListNode* head)
{
    while(head)
    {
        cout << head->data << ' ';
        head = head->next;
    }
    cout << endl;
}

size_t listLenght(ListNode* head)
{
    size_t count = 0;
    
    while(head)
    {
        count++;
        head = head->next;
    }
    return count;
}

bool findNode(ListNode* head, int value)
{
    while(head)
    {
        if(head->data == value)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

ListNode* deleteValue(ListNode* head, int value)
{
    while(head && head->data == value)
    {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    
    ListNode* current = head;
    while(current && current->next)
    {
        if(current->next->data == value)
        {
            ListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
        {
            current = current->next;
        }
    }
    return head;
}

template<typename... Args>
ListNode* createList(Args&&... args)
{
    ListNode* head = nullptr;
    ListNode** curr = &head;
    
    ((*curr = new ListNode(args), curr = &((*curr)->next)), ...);
    
    return head;
}

int binaryToDecimal(ListNode* head)
{
    int decVal = 0;
    
    while(head)
    {
        decVal = decVal * 2 + head->data;
        head = head->next;
    }
    return decVal;
}

ListNode* findMiddle(ListNode* head)
{
    if(!head) return nullptr;
    
    ListNode* jmpOne = head;
    ListNode* jmpTwice = head;
    
    while(jmpTwice && jmpTwice->next)
    {
        jmpOne = jmpOne->next;
        jmpTwice = jmpTwice->next->next;
    }
    return jmpOne;    
}

bool hasCycle(ListNode* head)
{
    if(!head) return false;
    
    ListNode* jmpOne = head;
    ListNode* jmpTwice = head;
    
    while(jmpTwice && jmpTwice->next)
    {
        jmpOne = jmpOne->next;
        jmpTwice = jmpTwice->next->next;
        
        if(jmpOne == jmpTwice) return true;
    }
    return false;
}

ListNode* deleteDublicate(ListNode* head)
{
    ListNode* current = head;
    
    while(current && current->next)
    {
        if(current->data == current->next->data)
        {
            ListNode* temp = current->next;
            current->next = temp->next;
            delete temp;
        }       
        else
        {
            current = current->next;
        }
    }
    return head;
}

ListNode* reverseList(ListNode* head)
{
    ListNode* prev = nullptr;
    ListNode* curr = head;
    
    while(curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool isPalindrome(ListNode* head)
{
    if(!head || !head->next)
    {
        return true;
    }
    
    ListNode* jmpOne = head;
    ListNode* jmpTwice = head;
    
    while(jmpTwice->next && jmpTwice->next->next)
    {
        jmpOne = jmpOne->next;
        jmpTwice = jmpTwice->next->next;
    }
    
    ListNode* second = reverseList(jmpOne->next);
    
    ListNode* p1 = head;
    ListNode* p2 = second;
    bool pal = true;
    
    while(p2)
    {
        if(p1->data != p2->data)
        {
            pal = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    jmpOne->next = reverseList(second);
    
    return pal;
}

int main()
{
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    printList(n1);
    
    cout << listLenght(n1) << endl;
    
    cout << findNode(n1, 5) << endl;
    
    ListNode* deletedList = deleteValue(n1, 3);
    printList(deletedList);
    
    ListNode* createdList = createList(1, 0, 1, 1);
    printList(createdList);
    
    cout << binaryToDecimal(createdList) << endl;
    
    ListNode* middle = findMiddle(n1);
    if(middle) cout << middle->data << endl;
    
    ListNode* c1 = new ListNode(10);
    ListNode* c2 = new ListNode(20);
    ListNode* c3 = new ListNode(30);
    c1->next = c2;
    c2->next = c3;
    c3->next = c2;
    cout << hasCycle(c1) << endl;
    c3->next = nullptr;

    ListNode* dubList = createList(1, 1, 2, 3, 3);
    printList(dubList);
    dubList = deleteDublicate(dubList);
    printList(dubList);

    ListNode* revList = createList(1, 2, 3);
    printList(revList);
    revList = reverseList(revList);
    printList(revList);
    revList = reverseList(revList);

    ListNode* pal1 = createList(1, 2, 2, 1);
    cout << isPalindrome(pal1) << endl;
    ListNode* pal2 = createList(1, 2);
    cout << isPalindrome(pal2) << endl;
    
    return 0;
}