#include <fstream>
#include <string>
#include <iostream>
#include <bitset>
#include <intrin.h>
using namespace std;

void Check(unsigned int eflags) {
    bitset<12> binary(eflags);
    if (binary[0] || binary[11])
        throw overflow_error("OverFlow");
}

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

int Sum(ElemInt* head) {
    int sum = 0;
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return 0;
    }
    while (head != nullptr) {
        sum += head->value;
        Check(__readeflags());
        head = head->next;
    }
    return sum;
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
    string pathSum = "nums.txt";
    
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

    //Чтение чисел в список
    //headInt = ReadNumsAllFile(pathNumbers);
    //BrListFromFirstInt(headInt);
    //headInt = ReadNumsAllFile(pathSum);
    //cout << Sum(headInt) << endl;

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
