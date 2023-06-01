#include "Header.h"

template<typename T>
MultiSet<T>::MultiSet() : head(nullptr) {}

template<typename T>
void MultiSet<T>::insert(const T& element) {
    Node* newNode = new Node(element);

    if (head == nullptr)
        head = newNode;
    else if (element <= head->value) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr && element > current->next->value)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }
}

template<typename T>
bool MultiSet<T>::contains(const T& element) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == element)
            return true;
        current = current->next;
    }
    return false;
}

template<typename T>
void MultiSet<T>::merge(const MultiSet<T>& otherSet) {
    Node* current = otherSet.head;
    while (current != nullptr) {
        insert(current->value);
        current = current->next;
    }
}

template<typename T>
void MultiSet<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

template<typename T>
MultiSet<T>::Iterator::Iterator(const MultiSet<T>& set) : multiSet(set), current(set.head) {}

template<typename T>
void MultiSet<T>::Iterator::begin() {
    current = multiSet.head;
}

template<typename T>
bool MultiSet<T>::Iterator::end() {
    return current == nullptr;
}

template<typename T>
const T& MultiSet<T>::Iterator::value() {
    return current->value;
}

template<typename T>
void MultiSet<T>::Iterator::next() {
    current = current->next;
}

template<typename T>
typename MultiSet<T>::Iterator MultiSet<T>::getIterator() const {
    return Iterator(*this);
}

void menu() {
    int chosen_type = 0;

    cout << "Enter 1 for creating a multiset of int numbers, 2 for double, or 3 for char: ";
    cin >> chosen_type;

    if (chosen_type == 1) {

        MultiSet<int> mySet;
        program(mySet);

    }

    else if (chosen_type == 2) {

        MultiSet<double> mySet;
        program(mySet);

    }

    else {

        MultiSet<char> mySet;
        program(mySet);

    }

}

template<typename T>
void program(MultiSet<T>& mySet) {

    int choose = 0, multiset_size = 0;

    T insert;
    MultiSet<T> otherSet;

    do {

        cout << "-------------------------------------" << endl;
        cout << "Menu:" << endl;
        cout << "1. Insert an element" << endl;
        cout << "2. Check if an element exists" << endl;
        cout << "3. Merge with another multiset" << endl;
        cout << "4. Print all elements" << endl;
        cout << "5. Clear the multiset" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choose;
        cout << "-------------------------------------" << endl;

        if (choose == 1) {
            cout << "Enter an element to insert: ";
            cin >> insert;
            mySet.insert(insert);
            cout << "Successfully inserted!" << endl;
        }

        else if (choose == 2) {
            cout << "Enter an element to check: ";
            cin >> insert;
            if (mySet.contains(insert))
                cout << "The multiset contains the element!" << endl;
            else
                cout << "The multiset does not contain the element." << endl;
        }

        else if (choose == 3) {

            cout << "Enter the size of the second multiset: ";
            cin >> multiset_size;
            cout << "Enter numbers you want to add: ";

            for (int i = 0; i < multiset_size; i++) {

                cin >> insert;
                otherSet.insert(insert);

            }

            mySet.merge(otherSet);

            cout << "Multisets were merged!" << endl;

            otherSet.clear();

        }

        else if (choose == 4) {

            typename MultiSet<T>::Iterator iterator = mySet.getIterator();
            iterator.begin();

            cout << "-------------------------------------" << endl;

            while (!iterator.end()) {
                cout << iterator.value() << " ";
                iterator.next();
            }

            cout << endl << "-------------------------------------" << endl;

        }

        else if (choose == 5) {

            mySet.clear();
            cout << "Successfully cleared!" << endl;

        }

        else
            break;

        

    } while (true);

}
