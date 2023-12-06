#include <fstream>
#include <string>
#include <iostream>
#include <fileapi.h>
using namespace std;



#pragma region ListString

// Создание структуры элемента списка
struct Elem {
    string value = "";
    Elem* next = nullptr;
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
void AddElem(Elem*& head, string value)
{
    if (head == nullptr) // если список пустой
    {
        head = new Elem;
        head->value = value;
        head->next = nullptr;
        return;
    }
    Elem* H = head; // Для прохода по списку
    Elem* C; // Вспомогательная переменная для сохранения предыдущего элемента
    do
    {
        C = H; // Сохраняем ссылку на текущий элемент
        H = H->next; // Берем следующий
    } while (H != nullptr); // Пока не дойдем до конца
    Elem* NewNode = new Elem;
    NewNode->value = value;
    NewNode->next = nullptr;
    C->next = NewNode; // Добавляем ссылку на последний элемент
}

#pragma endregion

#pragma region ListInt

// Создание структуры элемента списка
struct ElemInt {
    int value = 0;
    ElemInt* next = nullptr;
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
void AddElemInt(ElemInt*& head, int value)
{
    if (head == nullptr) // если список пустой
    {
        head = new ElemInt;
        head->value = value;
        head->next = nullptr;
        return;
    }
    ElemInt* H = head; // Для прохода по списку
    ElemInt* C; // Вспомогательная переменная для сохранения предыдущего элемента
    do
    {
        C = H; // Сохраняем ссылку на текущий элемент
        H = H->next; // Берем следующий
    } while (H != nullptr); // Пока не дойдем до конца
    ElemInt* NewNode = new ElemInt;
    NewNode->value = value;
    NewNode->next = nullptr;
    C->next = NewNode; // Добавляем ссылку на последний элемент
}



#pragma endregion

struct Person {
    const char  * Name = "Ivan";
    int Age = 18;
    float BodyMassIndex = 23.1;
};

void CreateF(string FilePath) {
    ofstream ofile;
    ofile.open(FilePath);
    if (ofile.is_open())
        cout << "CREATED\n";
    else
        cout << "IS NOT OPENED\n";
    ofile.close();
}

void TruncFile(string FilePath) {
    ofstream ofile;
    ofile.open(FilePath, ios::trunc);
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
        
        cout << "Write a sentence: \n";
        string l; getline(cin, l);
        l = l + "\n";
        auto new_text = l.c_str();
        ofile.write(new_text, strlen(new_text));
        if (ofile.fail())
        {
            cout << "WRITE_ERROR\n";
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
        if (ofile.fail())
        {
            cout << "WRITE_ERROR\n";
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
    ofile.open(FilePath, ios::app | ios::binary);
    if (ofile.is_open())
    {
        ofile.write((char*)&p, sizeof(p));
        if (ofile.fail())
        {
            cout << "WRITE_ERROR\n";
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
        
        getline(ifile, text, separator);
        if (ifile.fail())
        {
            cout << "READ_ERROR\n";
            ifile.clear();
        }
        ifile.close();
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
        while (getline(ifile, text, separator)) {
            
            AddElem(head, text);
        }
        if (ifile.fail())
        {
            cout << "READ_ERROR\n";
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
        while (!ifile.eof()) {
            ifile >> num;
            AddElemInt(head, num);
            if (ifile.fail())
            {
                cout << "READ_ERROR\n";
                ifile.clear();
                break;
            }
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
    ifile.open(FilePath, ios::in | ios::binary);
    if (ifile.is_open())
    {
        ifile.seekg(sizeof(p) * pos);
        if (!ifile.eof())
            ifile.read((char*)&p, sizeof(p));
        if (ifile.fail())
        {
            cout << "READ_ERROR\n";
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
    string wrongPath = "C:\\Program Files\\example.txt";
    string path = "example.txt";
    string pathNumbers = "exampleNumbers.txt";
    string pathSum = "nums.txt";
    
    Elem* head;
    ElemInt* headInt;
    
    //Создание файла
    //CreateF(wrongPath);
    //CreateF(path);

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

    //Чтение чисел в список
    //headInt = ReadNumsAllFile(pathNumbers);
    //BrListFromFirstInt(headInt);
    //headInt = ReadNumsAllFile(pathSum);
    //cout << Sum(headInt) << endl;

    // Запись структуры и чтение из определенного места
    /*string pathPerson = "examplePerson.txt";
    Person* newP;

    TruncFile(pathPerson);

    Person* p = new Person();
    WritePersonToFile(pathPerson, p);

    p = new Person(); p->Age = 81; p->BodyMassIndex = 29;p->Name = "Alex";
    WritePersonToFile(pathPerson, p);

    p = new Person(); p->Age = 23; p->BodyMassIndex = 21.32412; p->Name = "NIkolay";
    WritePersonToFile(pathPerson, p);

    for (int i = 2; i >= 0; i--) {
        newP = ReadPersonFromFile(pathPerson, i);
        cout << newP->Name << " " << newP->Age << " " << newP->BodyMassIndex << endl;
    }*/

    //auto f = CreateFileA("example.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}
