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
        C->next = NewNode;
        NewNode->prev = C;
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
    ofile.open(FilePath);
    if (ofile.is_open())
        cout << "CREATED\n";
    else
        cout << "IS NOT OPENED\n";
    ofile.close();
}

#pragma region WRITE

void WriteToFile(string FilePath) {
    ofstream ofile;
    ofile.open(FilePath);
    if (ofile.is_open()) {
        ofile.exceptions(ofstream::badbit | ofstream::failbit);
        try
        {
            cout << "Write a sentence: \n";
            string l; getline(cin, l);
            l = l + "\n";
            auto new_text = l.c_str();
            ofile.write(new_text, strlen(new_text));
        }
        catch (std::ios_base::failure& e) {
            cout << e.what() << "\nWRITE_ERROR\n";
            ofile.clear();
        }
        ofile.close();
    }
    else {
        cout << "IS NOT OPENED\n";
    }
}

void AddSeveralNotesToFile(string FilePath, string type = "out") {
    ofstream ofile;
    auto flag = ios::out;
    if (type == "app")
        flag = ios::app;
    ofile.open(FilePath, flag);
    if (ofile.is_open())
    {
        ofile.exceptions(ofstream::badbit | ofstream::failbit);
        try {
            cout << "Write sentences. Write 'stop' to stop writing sentences\n";
            string l; 
            getline(cin, l);
            l += "\n";
            auto new_text = l.c_str();
            do
            {
                ofile.write(new_text, strlen(new_text));
                getline(cin, l);
                l += "\n";
                new_text = l.c_str();
            } while (l != "\n" && l != "stop\n");
        }
        catch (std::ios_base::failure& e) {
            cout << e.what() << "\nWRITE_ERROR\n";
            ofile.clear();
        }
        ofile.close();
    }
    else {
        cout << "IS NOT OPENED\n";
    }
}

void WritePersonToFile(string FilePath, Person* p) {
    ofstream ofile;
    ofile.open(FilePath, ios::app);
    if (ofile.is_open())
    {
        ofile.exceptions(ofstream::badbit | ofstream::failbit);
        try
        {
            ofile.write((char*)&p, sizeof(p));
        }
        catch (std::ios_base::failure& e) {
            cout << e.what() << "\nWRITE_ERROR\n";
            ofile.clear();
        }
        ofile.close();
    }
    else {
        cout << "IS NOT OPENED\n";
    }
}

#pragma endregion

#pragma region READ

string ReadFromFile(string FilePath, char separator = '\n') {
    ifstream ifile;
    string text = "";
    ifile.open(FilePath);
    if (ifile.is_open())
    {
        ifile.exceptions(ofstream::badbit | ofstream::failbit);
        try
        {
            getline(ifile, text, separator);
        }
        catch (std::ios_base::failure& e) {
            cout << e.what() << "\nREAD_ERROR\n";
            ifile.clear();
        }
    }
    else {
        cout << "IS NOT OPENED\n";
    }
    return text;
}

Elem* ReadAllFile(string FilePath, char separator = '\n') {
    Elem* head = nullptr;
    ifstream ifile;
    string text;
    ifile.open(FilePath);
    if(ifile.is_open())
    {
        ifile.exceptions(ofstream::badbit | ofstream::failbit);
        try
        {
            while (!ifile.eof()) {
                getline(ifile, text, separator);
                AddElem(head, text);
            }
        }
        catch (std::ios_base::failure& e) {
            cout << e.what() << "\nREAD_ERROR\n";
            ifile.clear();
        }
        ifile.close();
    }
    else {
        cout << "IS NOT OPENED\n";
    }
    return head;
}

ElemInt* ReadNumsAllFile(string FilePath) {
    ElemInt* head = nullptr;
    ifstream ifile;
    int num;
    ifile.open(FilePath);
    if (ifile.is_open())
    {
        ifile.exceptions(ofstream::badbit | ofstream::failbit);
        try
        {
            while (!ifile.eof()) {
                ifile >> num;
                AddElemInt(head, num);
            }
        }
        catch (std::ios_base::failure& e) {
            cout << e.what() << "\nREAD_ERROR\n";
            ifile.clear();
        }
        ifile.close();
    }
    else {
        cout << "IS NOT OPENED\n";
    }
    return head;
}

Person* ReadPersonFromFile(string FilePath, int pos) {
    Person* p = nullptr;
    ifstream ifile;
    ifile.open(FilePath);
    if (ifile.is_open())
    {
        ifile.exceptions(ofstream::badbit | ofstream::failbit);
        try
        {
            ifile.seekg(sizeof(p) * pos);
            if (!ifile.eof())
                ifile.read((char*)&p, sizeof(p));
        }
        catch (std::ios_base::failure& e) {
            cout << e.what() << "\nREAD_ERROR\n";
            ifile.clear();
        }
        ifile.close();
    }
    else {
        cout << "IS NOT OPENED\n";
    }
    return p;
}

#pragma endregion

int main()
{
    string wrongPath = "C:/Program Files/example.txt";
    string path = "example.txt";
    string pathNumbers = "exampleNumbers.txt";
    
    Elem* head;
    ElemInt* headInt;
    
    //Создание файла
    //CreateFile(wrongPath);
    //CreateFile(path);

    //Запись в файл
    //WriteToFile(path);

    //Добавление записей в файл
    //AddSeveralNotesToFile(path, "app");

    //Чтение записи из файла
    //cout << ReadFromFile(path) << endl;
    
    //Чтение записей в список
    //head = ReadAllFile(path, '\n');
    //BrListFromFirst(head);

    //Добавление записей в файл c числами
    //AddSeveralNotesToFile(pathNumbers, "out");
    
    //Чтение чисел в список
    //headInt = ReadNumsAllFile(pathNumbers);
    //BrListFromFirstInt(headInt);

    // Запись структуры и чтение из определенного места
    /*string pathPerson = "examplePerson.txt";
    Person* newP;

    CreateFile(pathPerson);

    Person* p = new Person();
    WritePersonToFile(pathPerson, p);

    p = new Person(); p->Age = 81; p->BodyMassIndex = 29;p->Name = "Alex";
    WritePersonToFile(pathPerson, p);

    p = new Person(); p->Age = 23; p->BodyMassIndex = 21.32412; p->Name = "Nikolayllll";
    WritePersonToFile(pathPerson, p);

    for (int i = 2; i >= 0; i--) {
        newP = ReadPersonFromFile(pathPerson, i);
        cout << newP->Name << " " << newP->Age << " " << newP->BodyMassIndex << endl;
    }*/
}
