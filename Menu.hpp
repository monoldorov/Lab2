#ifndef MOSQUITO_MORON_MENU_HPP
#define MOSQUITO_MORON_MENU_HPP

#include <iostream>

using namespace std;

#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

#define EMPTY if (seq == nullptr) {\
                cout << "Sequence is empty.\n";\
                break;}

#define DELETE delete seq;\
                seq = nullptr;

#define PRINT cout << "Sequence:\n" << seq << endl;

void talker() {
    cout << "\nSelect an option:\n"
            "1. Create a new array sequence\n"
            "2. Create a new linked list sequence\n"
            "3. Print the sequence\n"
            "4. Get the first element\n"
            "5. Get the last element\n"
            "6. Get an element by index\n"
            "7. Get the length of the sequence\n"
            "8. Append an element\n"
            "9. Prepend an element\n"
            "10. Insert an element at an index\n"
            "0. Finish program\n"
            ">";
}

void menu() {
    int flag = 1, choice, index;
    float value;
    Sequence<float> *seq = nullptr;
    while (flag) {
        talker();
        cin >> choice;

        switch (choice) {
            case 1:     // New array sequence
                if (seq != nullptr) { DELETE }
                seq = new ArraySequence<float>();
                break;

            case 2:     // New linked list sequence
                if (seq != nullptr) { DELETE }
                seq = new ListSequence<float>();
                break;

            case 3:     // Print the sequence
                EMPTY
                cout << "Sequence:\n" << seq << endl;
                break;

            case 4:     // First element
                EMPTY
                PRINT
                cout << "First element: " << seq->GetFirst() << endl;
                break;

            case 5:     // Last element
                EMPTY
                PRINT
                cout << "Last element: " << seq->GetLast() << endl;
                break;

            case 6:     // Element by index
                EMPTY
                PRINT
                cout << "Enter index of element: ";
                cin >> index;
                if (index < 0 || index >= seq->Size()) {
                    cout << "Error. Index out of range.\n";
                    break;
                }
                cout << "Element at index " << index << ": " << seq->Get(index) << endl;
                break;

            case 7:     // Length of the sequence
                EMPTY
                PRINT
                cout << "Sequence length: " << seq->Size() << endl;
                break;

            case 8:     // Append
                PRINT
                cout << "Enter value to Append: ";
                cin >> value;
                seq->Append(value);
                PRINT
                break;

            case 9:     // Prepend an element
                PRINT
                cout << "Enter the element to Prepend: ";
                cin >> value;
                seq->Prepend(value);
                PRINT
                break;

            case 10:    // Insert an element at an index
                PRINT
                cout << "Enter the index Where you want to Insert the element: ";
                cin >> index;
                if (index < 0 || index > seq->Size()) {
                    cout << "Error. Please enter a valid index between 0 and " << seq->Size() << "." << endl;
                    break;
                }
                cout << "Enter the value of the element: ";
                cin >> value;
                seq->Insert(value, index);
                PRINT
                break;
            case 0:     // Finish
                flag = 0;
                DELETE
                break;
            default:
                break;
        }

    }
}

#endif //MOSQUITO_MORON_MENU_HPP
