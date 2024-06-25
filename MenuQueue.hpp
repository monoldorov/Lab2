#ifndef MOSQUITO_MORON_MENUQUEUE_HPP
#define MOSQUITO_MORON_MENUQUEUE_HPP

#include <iostream>
#include "Queue.hpp"
#include "Pair.hpp"
#include "QueueWithPriority.hpp"

using namespace std;

#define PRINT cout << "Queue:\t" << queue << endl;

void talker() {
    cout << "\nSelect an option:\n"
            "1. Print the queue\n"
            "2. Append an element in queue\n"
            "3. Get an element by index from queue\n"
            "4. Get the length of the queue\n"
            "5. Map()\n"
            "6. Where()\n"
            "7. Reduce()\n"
            "8. Concatenation with priority\n"
            "0. Finish program\n"
            ">";
}

void menu() {
    int flag = 1, choice, value;
    int array[] = {1, 2, 3, 4};
    auto makeDouble = [](int &val) { return val * 2; };
    auto isOdd = [](int &val) { return val % 2 == 1; };
    auto sum = [](int &val1, int &val2) { return val1 + val2; };
    Pair<int, int> pair1(5, 10);
    Pair<int, int> pair2(6, 15);
    Pair<int, int> pair3(10, 100);
    Pair<int, int> pair4(7, 1);
    Pair<int, int> pair5(-5, 17);
    Pair<int, int> pair6(-6, 20);
    Pair<int, int> array1[] = {pair1, pair2, pair3};
    Pair<int, int> array2[] = {pair4, pair5, pair6};

    PriorityQueue<int, int> priorityQueue1(array1, 3);
    PriorityQueue<int, int> priorityQueue2(array2, 3);
    PriorityQueue<int, int> priorityQueue3 = priorityQueue1.concatWithPriority(priorityQueue2);

    Queue<int> queue(array, 4);
    Queue<int> where = queue.Where(isOdd);
    Queue<int> map = queue.Map(makeDouble);
    Queue<int> reduce = queue.Reduce(sum, 0);
    while (flag) {
        talker();
        cin >> choice;

        switch (choice) {
            case 1:     // Print
                PRINT
                break;

            case 2:     // Append
                cout << "Enter new element: ";
                cin >> value;
                queue.Append(value);
                PRINT
                break;

            case 3:     // Get element by index
                PRINT
                cout << "Enter index: ";
                cin >> value;
                cout << queue.Peek(value) << endl;
                break;

            case 4:     // Length of the queue
                PRINT
                cout << "size: " << queue.Size() << endl;
                break;

            case 5:     // Map()
                PRINT
                cout << "Queue:\t" << map << endl;
                break;

            case 6:     // Where()
                PRINT
                cout << "Queue:\t" << where << endl;
                break;

            case 7:     // Reduce()
                PRINT
                cout << "Queue:\t" << reduce << endl;
                break;

            case 8:     // ConcatWithPriority
                cout << "First priorityQueue:\t" << priorityQueue1 << endl;
                cout << "Second priorityQueue:\t" << priorityQueue2 << endl;
                cout << "Queue concatenation with priority:\t" << priorityQueue3 << endl;
                break;

            case 0:     // Finish
                flag = 0;
                break;

            default:
                break;
        }
    }
}


#endif //MOSQUITO_MORON_MENUQUEUE_HPP
