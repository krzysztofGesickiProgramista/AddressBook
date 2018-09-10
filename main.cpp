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
    textFile << _contacts[_contactsNumber].id << "|";
    textFile << _contacts[_contactsNumber].name << "|";
    textFile << _contacts[_contactsNumber].surname << "|";
    textFile << _contacts[_contactsNumber].phoneNumber << "|";
    textFile << _contacts[_contactsNumber].email << "|";
    textFile << _contacts[_contactsNumber].address << "|" << endl;
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

string explodeStringLine (int position, string _textLine)
{
    string singleObject = "";
    int countPosition = 1;
    int stringSize = _textLine.size();
    for (int i = 0; i < stringSize; i++)
    {
        if (_textLine[i] == '|')
        {
            if (countPosition == position)
            {
                return singleObject;
            }
            else
            {
                countPosition++;
                singleObject = "";
            }
        }
        else singleObject += _textLine[i];
    }
}

int loadTextFile(vector <Contact> & _contacts) {
    fstream textFile;
    string textLine;
    string idToConvert;
    textFile.open(fileName.c_str(), ios::in);
    if (textFile.good() == false) {
        ofstream temp (fileName.c_str());
        textFile.open(fileName.c_str(), ios::in);
        if (textFile.good() == false) {
            cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
            Sleep(2000);
            exit(0);
        }
    }
    Contact temporaryContact;
    int contactsNumber = 0;
    while (getline(textFile,textLine)) {
        idToConvert = explodeStringLine(1, textLine);
        temporaryContact.id = atoi(idToConvert.c_str());
        temporaryContact.name = explodeStringLine(2, textLine);
        temporaryContact.surname = explodeStringLine(3, textLine);
        temporaryContact.phoneNumber = explodeStringLine(4, textLine);
        temporaryContact.email = explodeStringLine(5, textLine);
        temporaryContact.address = explodeStringLine(6, textLine);
        contactsNumber++;
        _contacts.push_back(temporaryContact);
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
    cout << "Twoj wybor: ";
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
