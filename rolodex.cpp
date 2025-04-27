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
    int current = 0; // Index of currently selected contact
public:
    void addContact(const std::string& name, const std::string& phone) {
        contacts.push_back({name, phone});
        sortContacts();
    }

    void removeCurrent() {
        if (!contacts.empty()) {
            contacts.erase(contacts.begin() + current);
            if (current >= contacts.size()) {
                current = contacts.size() - 1;
            }
        }
    }

    void next() {
        if (!contacts.empty()) {
            current = (current + 1) % contacts.size();
        }
    }

    void previous() {
        if (!contacts.empty()) {
            current = (current - 1 + contacts.size()) % contacts.size();
        }
    }

    void showCurrent() const {
        if (contacts.empty()) {
            std::cout << "No contacts.\n";
        } else {
        const auto& c = contacts[current];
        std::cout << "\n=====================\n";
        std::cout << "   Current Contact   \n";
        std::cout << "=====================\n";
        std::cout << "Name : " << c.name << "\n";
        std::cout << "Phone: " << c.phone << "\n";
        std::cout << "=====================\n";
        }
    }

private:
    void sortContacts() {
        std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.name < b.name;
        });
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
                std::cin.ignore(); // Clear the newline character
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
