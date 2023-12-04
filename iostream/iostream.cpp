#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#pragma region List

// Создание структуры элемента списка
struct Elem {
    string value;
    Elem* next;
    Elem* prev; // Ссылка на предыдущий элемент
};

string GetElemValue(Elem* elem) {
    return elem->value;
}

Elem* GetElemNext(Elem* elem) {
    if (elem->next != nullptr) {
        return elem->next;
    }
    else
        throw out_of_range("Out of range");
}

Elem* GetElemPrev(Elem* elem) {
    if (elem->prev != nullptr) {
        return elem->prev;
    }
    else
        throw out_of_range("Out of range");
}

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

// Процедура просмотра элементов списка от хвоста к голове (итерационно)
void BrListFromEnd(Elem* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    Elem* C;
    while (head->next != nullptr) { // Доходим до последнего элемента
        head = head->next;
    }
    while (head != nullptr) { // Выводим в обратном порядке
        cout << head->value << " ";
        head = head->prev; // Берем предыдущий элемент
    }
}

// Удаление элемента
void DeleteElems(Elem*& head, string EV)
{
    bool isDeleted = false;
    Elem* H = head;
    Elem* C = nullptr;
    while (H != nullptr)
    { // Список не пуст - ищем в нём элемент для удаления:
        if (H->value == EV) // Элемент найден
        {
            if (H == head) // Удаляется элемент из головы списка
            {
                head = H->next;
                delete H;
                H = head;
            }
            else // Удаляется элемент из хвоста списка
            {
                C->next = H->next;
                if (H->next != nullptr) //Если следующий элемент существует, 
                    H->next->prev = C; // присваиваем к его ссылке на предыдущий элемент новый
                delete H;
                H = C->next;
            }
            isDeleted = true;
            cout << "Элемент удалён!" << endl;
            continue;
        }
        C = H;
        H = H->next;
    }
    if (!isDeleted)
        cout << "Нет элемента для удаления!" << endl;
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

// Поиск
void Find(Elem* head, string value) {
    int count = 0;
    for (int index = 0; head != nullptr; index++) {
        if (head->value == value) {
            cout << "Номер: " << index + 1 << endl;
            count++;
        }
        head = head->next;
    }
    if (count)
        cout << "Количество совпадений: " << count << endl;
    else
        cout << "Не найдено." << endl;
}

string Get(Elem* list, int index) {
    /*if (list == nullptr)
        RaiseException(EXCEPTION_ACCESS_VIOLATION, EXCEPTION_NONCONTINUABLE, NULL, NULL);*/
    while (list->prev != nullptr) {
        list = list->prev;
    }
    int counter = 0;
    while (list->next != nullptr) {
        if (counter++ == index)
            return list->value;
        list = list->next;
    }
    if (counter == index) {
        return list->value;
    }
    throw out_of_range("Out of range");
}

void Put(Elem* list, int index, string value) {
    /*if (list == nullptr)
        RaiseException(EXCEPTION_ACCESS_VIOLATION, EXCEPTION_NONCONTINUABLE, NULL, NULL);*/
    while (list->prev != nullptr) {
        list = list->prev;
    }
    int counter = 0;
    while (list->next != nullptr) {
        if (counter++ == index)
            list->value = value;
        list = list->next;
    }
    if (counter == index)
        list->value = value;
    throw out_of_range("Out of range");
}

#pragma endregion

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

Elem* ReadAllFile(string FilePath) {
    Elem* head = nullptr;
    ifstream ifile;
    string text;
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open(FilePath);
        while (!ifile.eof()) {
            getline(ifile, text, '\n');
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

string ReadFragmentFromFile(string FilePath, int firstPos, int lastPos) {
    ifstream ifile;
    string text = "";
    char sym;
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open(FilePath);
        ifile.seekg(streampos(firstPos));
        while (ifile.tellg() != streampos(lastPos) && !ifile.eof()) {
            if(ifile.get(sym))
                text += sym;
        }
    }
    catch (std::ios_base::failure& e) {
        cout << "Out of range\n";
        ifile.clear();
    }
    return text;
}

int main()
{
    string wrongPath = "C:/Program Files/example.txt";
    string path = "example.txt";
    Elem* head;

    //CreateFile(wrongPath);
    //CreateFile(path);

    //WriteLineToFile(wrongPath);
    //WriteLineToFile(path);

    //ReadLineFromFile(wrongPath);
    //cout << ReadLineFromFile(path) << endl;

    //AddSeveralNotesToFile(path);
    
    //head = ReadAllFile(path);
    //BrListFromFirst(head);

    //cout << ReadFragmentFromFile(path, 5, 40) << endl;
}
