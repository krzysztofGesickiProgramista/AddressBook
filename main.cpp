#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

using namespace std;

string fileName = "addressBook.txt";

struct Contact {
    int id;
    string name, surname, phoneNumber, email, address;
};

void showContacts(int _contactsNumber, vector <Contact> _contacts) {
    cout << "Lista zapisanych kontaktow: " << endl << endl;

    for (int i = 0; i < _contactsNumber; i++) {
        cout << "ID kontaktu: " << _contacts[i].id << endl;
        cout << "Imie: " << _contacts[i].name << endl;
        cout << "Nazwisko: " << _contacts[i].surname << endl;
        cout << "Numer telefonu: " << _contacts[i].phoneNumber << endl;
        cout << "Adres e-mail: " << _contacts[i].email << endl;
        cout << "Adres: " << _contacts[i].address << endl;
        cout << endl;
    }
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
}

int addNewContact(int _contactsNumber, vector <Contact> & _contacts) {
    //dodanie nowego kontaktu do tablicy
    cin.ignore();
    _contacts.push_back(Contact());
    if (_contactsNumber == 0) _contacts[_contactsNumber].id = _contactsNumber+1;
    else _contacts[_contactsNumber].id = (_contacts[_contactsNumber-1].id+1);
    cout << "Podaj imie: ";
    getline(cin, _contacts[_contactsNumber].name);
    cout << endl << "Podaj nazwisko: ";
    getline(cin, _contacts[_contactsNumber].surname);
    cout << endl << "Podaj numer telefonu: ";
    getline(cin, _contacts[_contactsNumber].phoneNumber);
    cout << endl << "Podaj adres e-mail: ";
    getline(cin, _contacts[_contactsNumber].email);
    cout << endl << "Podaj adres: ";
    getline(cin, _contacts[_contactsNumber].address);

    //dodanie nowego kontaktu do pliku
    fstream textFile;
    textFile.open(fileName.c_str(), ios::out|ios::app);
    if (textFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    textFile << _contacts[_contactsNumber].id << endl;
    textFile << _contacts[_contactsNumber].name << endl;
    textFile << _contacts[_contactsNumber].surname << endl;
    textFile << _contacts[_contactsNumber].phoneNumber << endl;
    textFile << _contacts[_contactsNumber].email << endl;
    textFile << _contacts[_contactsNumber].address << endl;
    textFile.close();

    cout << "Kontakt dodany! ";
    system("pause");

    return _contactsNumber+1;
}

void searchContactByName(int _contactsNumber, vector <Contact> _contacts) {
    string searchFor;
    cout << "Podaj szukana fraze (imie): ";
    cin.ignore();
    getline(cin, searchFor);
    for (int i = 0; i < _contactsNumber; i++) {
        if (searchFor == _contacts[i].name) {
            cout << "ID kontaktu: " << _contacts[i].id << endl;
            cout << "Imie: " << _contacts[i].name << endl;
            cout << "Nazwisko: " << _contacts[i].surname << endl;
            cout << "Numer telefonu: " << _contacts[i].phoneNumber << endl;
            cout << "Adres e-mail: " << _contacts[i].email << endl;
            cout << "Adres: " << _contacts[i].address << endl;
            cout << endl;
        }
    }
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
}

void searchContactBySurname(int _contactsNumber, vector <Contact> _contacts) {
    string searchFor;
    cout << "Podaj szukana fraze (nazwisko): ";
    cin.ignore();
    getline(cin, searchFor);
    for (int i = 0; i < _contactsNumber; i++) {
        if (searchFor == _contacts[i].surname) {
            cout << "ID kontaktu: " << _contacts[i].id << endl;
            cout << "Imie: " << _contacts[i].name << endl;
            cout << "Nazwisko: " << _contacts[i].surname << endl;
            cout << "Numer telefonu: " << _contacts[i].phoneNumber << endl;
            cout << "Adres e-mail: " << _contacts[i].email << endl;
            cout << "Adres: " << _contacts[i].address << endl;
            cout << endl;
        }
    }
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
}

int loadTextFile(vector <Contact> & _contacts) {
    fstream textFile;
    string textLine;
    textFile.open(fileName.c_str(), ios::in);
    if (textFile.good() == false) {
        ofstream temp (fileName.c_str());
    }
    textFile.open(fileName.c_str(), ios::in);
    if (textFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    Contact temporaryContact;
    int contactsNumber = 0;
    int numberOfLine = 1;
    //teraz wczytujemy z pliku do tablicy
    while (getline(textFile,textLine)) {
        switch (numberOfLine) {
        case 1:
            temporaryContact.id = atoi(textLine.c_str());
            break;
        case 2:
            temporaryContact.name = textLine;
            break;
        case 3:
            temporaryContact.surname = textLine;
            break;
        case 4:
            temporaryContact.phoneNumber = textLine;
            break;
        case 5:
            temporaryContact.email = textLine;
            break;
        case 6:
            temporaryContact.address = textLine;
            break;
        }
        if (numberOfLine == 6) {
            numberOfLine = 0;
            contactsNumber++;
            _contacts.push_back(temporaryContact);
        }
        numberOfLine++;
    }
    textFile.close();
    return contactsNumber;
}

void showMenu () {
    system("cls");
    cout << "1. Dodaj adresata"  <<  endl;
    cout << "2. Wyszukaj po imieniu"  <<  endl;
    cout << "3. Wyszukaj po nazwisku"  <<  endl;
    cout << "4. Wyswietl wszystkich adresatow"  <<  endl;
    cout << "5. Usun adresata"  <<  endl;
    cout << "6. Edytuj adresata"  <<  endl;
    cout << "9. Zakoncz program"  <<  endl;
    cout << endl;
}

int main() {
    char selection;
    vector <Contact> contacts;
    int contactsNumber = loadTextFile(contacts);

    //MENU GLOWNE
    while (true) {

        showMenu();
        cin >> selection;

        if (selection == '1') {
            system("cls");
            contactsNumber = addNewContact(contactsNumber, contacts);
        }

        else if (selection == '2') {
            system("cls");
            searchContactByName(contactsNumber, contacts);
        }

        else if (selection == '3') {
            system("cls");
            searchContactBySurname(contactsNumber, contacts);
        }

        else if (selection == '4') {
            system("cls");
            showContacts(contactsNumber, contacts);
        }

        else if (selection == '5') {
            system("cls");
            //deleteContact();
        }

        else if (selection == '6') {
            system("cls");
            //editContact();
        }

        else if (selection == '9') {
            exit(0);
        }

        else {
            cout << "Wybrano niepoprawna opcje! Sprobuj ponownie ";
            system("pause");
        }
    }

    return 0;
}
