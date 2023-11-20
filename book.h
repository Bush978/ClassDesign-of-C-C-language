#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
#define MAXSIZE 10000 
#define MAX_LINE 1024 

typedef struct Book
{
    string no;
    string name;
    double price;
}Book;

typedef struct Node {
    Book data;
    Node* before;
    Node* next;
}Node;

class List {
public:
    List() {
        head = new Node;
        head->next = NULL;
        head->before = NULL;
        head->data.price = 0.0;
        number = 0;
    }
    void scan();
    void show();
    void shownumber();
    void insertion(int place);
    void deletion(const string& name);
    void deletion(const int& place);
    void invertion();
    void mergesort();
    void division(Node* first1, Node*& first2);
    void recmergesort(Node*& firsthead);
    void search(const int place);
    void search(const string name);
    void update();
    void fileprint();
    Node* merge(Node* first1, Node* first2);
private:
    Node* head;
    int number;
};

void List::insertion(int place) {
    Node* newnode = new Node;
    Node* current = head;
    int i = 1;
    double price;
    string no, name;
    cout << "please input the book's no, book's name and book's price in order. \n";
    cin >> no >> name >> price;
    newnode->data.no = no;
    newnode->data.name = name;
    newnode->data.price = price;

    while (current->next != NULL && i != place) {
        current = current->next;
        i++;
    }
    newnode->next = current->next;
    current->next = newnode;
    number++;
    fileprint();
}

void List::scan() {
    Node* current = head;
    FILE* fp;
    errno_t err = fopen_s(&fp, "book.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Can't open file\n");
        exit(1);
    }

    char no[32], name[64];
    double price;
    char buffer[MAX_LINE];
    for (int i = 0; i < 2; i++) {
        if (fgets(buffer, MAX_LINE, fp) == NULL) {
            fprintf(stderr, "unseccessful");
            exit(1);
        }
        printf("%s", buffer);
    }

    while (fgets(buffer, MAX_LINE, fp)) {
        Node* newnode = new Node;
        if (sscanf_s(buffer, "%s %s %lf", no, 32, name, 64, &price) == 3) {
            for (int i = 0; i < strlen(no); i++) newnode->data.no += no[i];
            for (int j = 0; j < strlen(name); j++) newnode->data.name += name[j];
            newnode->data.price = price;
            newnode->next = current->next;
            current->next = newnode;
            current = current->next;
            number++;
        }
        else {
            fprintf(stderr, "unseccessful %s\n", buffer);
        }
    }
    fclose(fp);
    show();
}

void List::deletion(const string& name) {
    Node* auxpointer = head, * pointer = head->next;
    int i = 1;
    while (pointer != NULL) {
        if (pointer->data.name == name && auxpointer != head && i <= number) {
            auxpointer->next = pointer->next;
            pointer->next->before = auxpointer;
            delete pointer;
            number--;
        }
        else if (pointer->data.name == name && auxpointer == head && i <= number) {
            auxpointer->next = pointer->next;
            pointer->next->before = auxpointer;
            delete pointer;
            number--;
        }
        else if (i > number) break;
        pointer = pointer->next;
        auxpointer = auxpointer->next;
    }
    fileprint();
}

void List::deletion(const int& place) {
    Node* auxpointer = head, * pointer = head->next;
    //cout << auxpointer->data.price << " " << pointer->data.price;
    int i = 1;
    if (pointer == NULL)
        return;
    else {
        while (pointer != NULL) {
            if (i == place && auxpointer != head && i <= number) {
                auxpointer->next = pointer->next;
                pointer->next->before = auxpointer;
                delete pointer;
                number--;
                break;
            }
            else if (i == place && auxpointer == head && i <= number) {
                auxpointer->next = pointer->next;
                pointer->next->before = auxpointer;
                number--;
                break;
            }
            else if (i > number) break;
            i++;
            pointer = pointer->next;
            auxpointer = auxpointer->next;
        }
    }
    fileprint();
}

void List::invertion() {
    Node* auxpointer = head, * pointer = head->next;
    if (pointer == NULL)
        auxpointer->before = pointer->before;
    else {
        while (pointer != NULL) {
            pointer->before = auxpointer;
            //cout << auxpointer->before << " " << pointer << endl;
            pointer = pointer->next;
            auxpointer = auxpointer->next;
        }
    }

    ofstream fout("book-newinverse.txt");
    if (!fout) {
        cerr << "无法打开文件" << endl;
        return;
    }
    fout << "北京林业大学图书馆计算机类图书采购列表" << endl;
    fout << "ISBN	  书名	    定价" << endl;
    Node* curr = head;

    while (auxpointer->before != NULL) {
        fout << auxpointer->data.no << " " << auxpointer->data.name << " " << auxpointer->data.price << endl;
        cout << auxpointer->data.no << " " << auxpointer->data.name << " " << auxpointer->data.price << endl;
        auxpointer = auxpointer->before;
    }

    fout.close();

}

void List::show() {
    Node* current = head->next;
    while (current != NULL) {
        cout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
        current = current->next;
    }
}

void List::shownumber() {
    cout << number << endl;
}

void List::mergesort() {
    recmergesort(head);
    show();
    ofstream fout("book-newsort.txt");
    if (!fout) {
        cerr << "无法打开文件" << endl;
        return;
    }
    fout << "北京林业大学图书馆计算机类图书采购列表" << endl;
    fout << "ISBN	  书名	    定价" << endl;
    Node* curr = head->next;
    while (curr) {
        fout << curr->data.no << " " << curr->data.name << " " << curr->data.price << endl;
        curr = curr->next;
    }
    fout.close();
}

void List::recmergesort(Node*& firsthead) {

    Node* otherhead = head;
    if (firsthead != NULL)
        if (firsthead->next != NULL) {
            division(firsthead, otherhead);
            //cout <<" recusion in recmergesort"<<endl<<firsthead<< " " << otherhead->data.price << " " << otherhead->data.name << endl << endl;
            recmergesort(firsthead);
            recmergesort(otherhead);
            firsthead = merge(firsthead, otherhead);
        }

}

void List::division(Node* first1, Node*& first2) {
    Node* middle, * current;
    //cout << first2->data.price;
    if (first1 == NULL) {
        first2 = NULL;
        //cout << "1";
        return;
    }
    else if (first1->next == NULL) {
        first2 = NULL;
        return;
    }
    else {
        middle = first1;
        current = first1->next;

        if (current != NULL)
            current = current->next;

        while (current != NULL)
        {
            middle = middle->next;
            current = current->next;
            if (current != NULL)
                current = current->next;
        }

        first2 = middle->next;
        //cout << "loop in division" << endl<< first2->data.name << endl<<endl;
        middle->next = NULL;
    }
}

Node* List::merge(Node* first1, Node* first2) {
    Node* auxpointer, * newhead;
    if (first1 == NULL) return first2;
    else if (first2 == NULL) return first1;
    else {
        if (first1->data.price > first2->data.price)
        {
            newhead = first2;
            first2 = first2->next;
        }
        else
        {
            newhead = first1;
            first1 = first1->next;
        }

        auxpointer = newhead;

        while (first1 != NULL && first2 != NULL) {
            if (first1->data.price > first2->data.price)
            {
                auxpointer->next = first2;
                auxpointer = auxpointer->next;
                first2 = first2->next;
            }
            else
            {
                auxpointer->next = first1;
                auxpointer = auxpointer->next;
                first1 = first1->next;
            }
        }

        if (first1 == NULL)
            auxpointer->next = first2;
        else
            auxpointer->next = first1;
        return newhead;
    }
}

void List::search(const int place) {
    int i = 0;
    Node* current = head;
    while (current != NULL)
    {
        if (i == place)
            cout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
        i++;
        current = current->next;
    }

}

void List::search(const string name) {
    Node* current = head;
    while (current != NULL)
    {
        if (name == current->data.name)
            cout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
        current = current->next;
    }
}

void List::update() {
    Node* current = head;
    while (current != NULL)
    {
        if (current->data.price >= 45)
            current->data.price *= 1.1;
        else
            current->data.price *= 1.2;
        current = current->next;
    }
    ofstream fout("book-newprice.txt");
    if (!fout) {
        cerr << "无法打开文件" << endl;
        return;
    }
    fout << "北京林业大学图书馆计算机类图书采购列表" << endl;
    fout << "ISBN	  书名	    定价" << endl;
    Node* curr = head->next;
    while (curr) {
        fout << curr->data.no << " " << curr->data.name << " " << curr->data.price << endl;
        curr = curr->next;
    }
    fout.close();
}

void List::fileprint() {
    ofstream fout("book.txt");
    fout << "北京林业大学图书馆计算机类图书采购列表" << endl;
    fout << "ISBN	  书名	    定价" << endl;
    Node* current = head;
    while (current) {
        fout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
        current = current->next;
    }
    fout.close();
}