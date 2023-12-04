#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#pragma region ListString

// Создание структуры элемента списка
struct Elem {
    string value;
    Elem* next;
    Elem* prev; // Ссылка на предыдущий элемент
};

// Процедура просмотра элементов списка от головы к хвосту
void BrListFromFirst(Elem* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

// Добавление элемента
void AddElem(Elem*& head, string value) {
    Elem* NewNode = new Elem; // Создание нового
    NewNode->value = value;
    NewNode->next = nullptr;
    NewNode->prev = nullptr;
    if (head == nullptr) // Список пустой
    {
        head = NewNode;
        return;
    }
    Elem* H = head;
    if (head->value > value) { // Элемент встает на первое место
        head = NewNode;
        head->next = H;
        return;
    }
    Elem* C;
    do
    {
        C = H;
        H = H->next;
    } while (H != nullptr && value > H->value); // Доходим до места вставки
    if (H == nullptr) { // Элемент встает на последнее место
        C->next = NewNode;
        NewNode->prev = C;
    }
    else {
        NewNode->next = H;
        H->prev = NewNode; // Элемент встает в середину, добавляем ссылку на следующий элемент, а у следующего меняем на новый предыдущий
    }
}

#pragma endregion

#pragma region ListInt

// Создание структуры элемента списка
struct ElemInt {
    int value;
    ElemInt* next;
    ElemInt* prev; // Ссылка на предыдущий элемент
};

// Процедура просмотра элементов списка от головы к хвосту
void BrListFromFirstInt(ElemInt* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

// Добавление элемента
void AddElemInt(ElemInt*& head, int value) {
    ElemInt* NewNode = new ElemInt; // Создание нового
    NewNode->value = value;
    NewNode->next = nullptr;
    NewNode->prev = nullptr;
    if (head == nullptr) // Список пустой
    {
        head = NewNode;
        return;
    }
    ElemInt* H = head;
    if (head->value > value) { // Элемент встает на первое место
        head = NewNode;
        head->next = H;
        return;
    }
    ElemInt* C;
    do
    {
        C = H;
        H = H->next;
    } while (H != nullptr && value > H->value); // Доходим до места вставки
    if (H == nullptr) { // Элемент встает на последнее место
        C->next = NewNode;
        NewNode->prev = C;
    }
    else {
        C->next = NewNode;
        NewNode->prev = C;
        NewNode->next = H;
        H->prev = NewNode; // Элемент встает в середину, добавляем ссылку на следующий элемент, а у следующего меняем на новый предыдущий
    }
}

#pragma endregion

struct Person {
    const char * Name = "Ivan";
    int Age = 18;
    float BodyMassIndex = 23.1;
};

void CreateFile(string FilePath) {
    ofstream ofile;
    ofile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ofile.open(FilePath);
        cout << "CREATED\n";
        ofile.close();
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ofile.clear();
    }
}

void WriteLineToFile(string FilePath) {
    ofstream ofile;
    ofile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ofile.open(FilePath);
        cout << "Write a sentence: \n";
        string l; getline(cin, l);
        l = l + "\n";
        auto new_text = l.c_str();
        ofile.write(new_text, strlen(new_text));
        ofile.close();
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ofile.clear();
    }
}

void AddSeveralNotesToFile(string FilePath) {
    ofstream ofile;
    ofile.exceptions(ofstream::badbit | ofstream::failbit);
    try {
        ofile.open(FilePath, ios::app);
        cout << "Write sentences. Write 'stop' to stop writing sentences\n";
        string l; getline(cin, l);
        l = l + "\n";
        auto new_text = l.c_str();
        do
        {
            ofile.write(new_text, strlen(new_text));
            getline(cin, l);
            l = l + "\n";
            new_text = l.c_str();
        } while (l != "\n" && l != "stop\n");
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ofile.clear();
    }
    ofile.close();
}

string ReadLineFromFile(string FilePath) {
    ifstream ifile;
    string text = "";
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open(FilePath);
        getline(ifile, text);
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ifile.clear();
    }
    return text;
}

Elem* ReadAllFile(string FilePath, char separator) {
    Elem* head = nullptr;
    ifstream ifile;
    string text;
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open(FilePath);
        while (!ifile.eof()) {
            getline(ifile, text, separator);
            AddElem(head, text);
        }
    }
    catch (...) {
        cout << "CATCHED\n";
        ifile.clear();
    }
    ifile.close();
    return head;
}

ElemInt* ReadNumsAllFile(string FilePath) {
    ElemInt* head = nullptr;
    ifstream ifile;
    int num;
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open(FilePath);
        while (!ifile.eof()) {
            ifile >> num;
            AddElemInt(head, num);
        }
    }
    catch (...) {
        cout << "CATCHED\n";
        ifile.clear();
    }
    ifile.close();
    return head;
}

void WriteNoteToFile(string FilePath, Person* p) {
    ofstream ofile;
    ofile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ofile.open(FilePath, ios::app);
        ofile.write((char*)&p, sizeof(p));
        ofile.close();
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ofile.clear();
    }
}

Person* ReadNotesFromFile(string FilePath, int pos) {
    Person* p = nullptr;
    ifstream ifile;
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open(FilePath);
        ifile.seekg(sizeof(p)*pos);
        if (!ifile.eof())
            ifile.read((char*) &p, sizeof(p));
    }
    catch (...) {
        cout << "CATCHED\n";
        ifile.clear();
    }
    ifile.close();
    return p;
}

int main()
{
    string wrongPath = "C:/Program Files/example.txt";
    string path = "example.txt";
    
    Elem* head;
    ElemInt* headInt;
    


    //CreateFile(wrongPath);
    //CreateFile(path);


    //WriteLineToFile(path);


    //cout << ReadLineFromFile(path) << endl;

    //AddSeveralNotesToFile(path);
    
    //head = ReadAllFile(path, '\n');
    //BrListFromFirst(head);

    //headInt = ReadNumsAllFile(path);
    //BrListFromFirstInt(headInt);

    // Запись структуры и чтение из определенного места
    string pathPerson = "examplePerson.txt";
    Person* p = new Person();
    Person* newP;

    CreateFile(pathPerson);
    WriteNoteToFile(pathPerson, p);
    p = new Person();
    p->Age = 81;
    p->BodyMassIndex = 29;
    p->Name = "Alex";
    WriteNoteToFile(pathPerson, p);
    p = new Person();
    p->Age = 23;
    p->BodyMassIndex = 21.32412;
    p->Name = "Nikolayllll";
    WriteNoteToFile(pathPerson, p);
    newP = ReadNotesFromFile(pathPerson, 0);
    cout << newP->Name << " " << newP->Age << " " << newP->BodyMassIndex << endl;
    newP = ReadNotesFromFile(pathPerson, 1);
    cout << newP->Name << " " << newP->Age << " " << newP->BodyMassIndex << endl;
    newP = ReadNotesFromFile(pathPerson, 2);
    cout << newP->Name << " " << newP->Age << " " << newP->BodyMassIndex << endl;
}
