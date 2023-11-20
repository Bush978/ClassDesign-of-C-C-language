#include "book.h"
#include <bits/stdc++.h>
using namespace std;
int main()
{
    List l;
    int key;
    string name;
    int place;
    printf("===== Books Management System =====\n");
    printf("1. Scan & Show Book Information\n");
    printf("2. Add the Number of Books\n");
    printf("3. Insert Information at a Specific Place\n");
    printf("4. Delete Book Information at a Specific Place\n");
    printf("5. Search for a Book by Place\n");
    printf("6. Search for a Book by Name\n");
    printf("7. Update & Increase Book Prices\n");
    printf("8. Sort Books in Ascending Order\n");
    printf("9. Sort Books in Descending Order\n");
    printf("10. Exit\n\n");
    printf("Please choose an option (1-10): ");
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
        case 3:cout << "please input the position: \n";
            cin >> place;
            l.insertion(place);
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 4:cout << "please input the position: \n";
            cin >> place;
            l.deletion(place);
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 5:cout << "please input the position: \n";
            cin >> place;
            l.search(place);
            printf("\nplease choose the next option: ");
            cin >> key;
            break;

        case 6: cout << "please input the Title: \n";
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

