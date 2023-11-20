#include <iostream>
#include "book.h"
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;
int main()
{
    List l;
    int key;
    string name;
    int place;
    printf("---Books management stystem---\n");
    printf("1.scan&show the info of the book\n");
    printf("2.addition the number of the book\n");
    printf("3.insert the information into the certain place\n");
    printf("4.delete the information of the book in the certain place\n");
    printf("5.search the book by place\n");
    printf("6.search the book by name\n");
    printf("7.update&grow the prices of the books \n");
    printf("8.sort the books in ascend order\n");
    printf("9.sort the books in inverted sequence\n");
    printf("10.exit\n\n");
    printf("\nplease choose the option(1-10): ");
    cin >> key;
    do {
        switch (key)
        {
        case 1:l.scan();
            printf("\nplease choose the next option: ");
            cin >> key;
            break;
        case 2:l.shownumber();
            printf("\nplease choose the next option: ");
            cin >> key;
            break;
        case 3:cout << "please input the place: \n";
            cin >> place;
            l.insertion(place);
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 4:cout << "please input the place: \n";
            cin >> place;
            l.deletion(place);
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 5:cout << "please input the place: \n";
            cin >> place;
            l.search(place);
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 6: cout << "please input the name: \n";
            cin>> name;
            l.search(name);
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 7:l.update();
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 8:l.mergesort();
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 9:l.invertion();
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 10:
            break;
        }
    } while (key != 10);
    return 0;
}

