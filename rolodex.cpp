#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Contact {
    std::string name;
    std::string phone;
};

class Rolodex {
private:
    std::vector<Contact> contacts;
    std::vector<Contact>::iterator current;

public:
    Rolodex() : current(contacts.end()) {} // Start with no valid contact

    void addContact(const std::string& name, const std::string& phone) {
        contacts.push_back({name, phone});
        sortContacts();
        if (contacts.size() == 1) {
            current = contacts.begin();
        }
    }

    void removeCurrent() {
        if (!contacts.empty() && current != contacts.end()) {
            current = contacts.erase(current);
            if (current == contacts.end() && !contacts.empty()) {
                current = contacts.begin(); // wrap around if needed
            }
        }
    }

    void next() {
        if (!contacts.empty() && current != contacts.end()) {
            ++current;
            if (current == contacts.end()) {
                current = contacts.begin();
            }
        }
    }

    void previous() {
        if (!contacts.empty() && current != contacts.end()) {
            if (current == contacts.begin()) {
                current = contacts.end();
            }
            --current;
        }
    }

    void showCurrent() const {
        if (contacts.empty() || current == contacts.end()) {
            std::cout << "No contacts.\n";
        } else {
            std::cout << "\n=====================\n";
            std::cout << "   Current Contact   \n";
            std::cout << "=====================\n";
            std::cout << "Name : " << current->name << "\n";
            std::cout << "Phone: " << current->phone << "\n";
            std::cout << "=====================\n";
        }
    }

private:
    void sortContacts() {
        std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.name < b.name;
        });
        if (!contacts.empty()) {
            current = contacts.begin();
        }
    }
};

void showMenu() {
    std::cout << "\n--- Rolodex ---\n";
    std::cout << "[A]dd Contact\n";
    std::cout << "[N]ext Contact\n";
    std::cout << "[P]revious Contact\n";
    std::cout << "[R]emove Current Contact\n";
    std::cout << "[S]how Current Contact\n";
    std::cout << "[Q]uit\n";
    std::cout << "Enter choice: ";
}

int main() {
    Rolodex r;
    char choice;

    do {
        showMenu();
        std::cin >> choice;
        choice = std::toupper(choice);

        switch(choice) {
            case 'A': {
                std::cin.ignore();
                std::string name, phone;
                std::cout << "Enter name: ";
                std::getline(std::cin, name);
                std::cout << "Enter phone: ";
                std::getline(std::cin, phone);
                r.addContact(name, phone);
                break;
            }
            case 'N':
                r.next();
                r.showCurrent();
                break;
            case 'P':
                r.previous();
                r.showCurrent();
                break;
            case 'R':
                r.removeCurrent();
                break;
            case 'S':
                r.showCurrent();
                break;
            case 'Q':
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }

    } while(choice != 'Q');

    return 0;
}
