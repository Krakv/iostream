#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void CreateFile() {
    ofstream ofile;
    ofile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ofile.open("C:/Program Files/example.txt", ios::out);
        ofile.close();
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ofile.clear();

    }

    try {
        ofile.open("example.txt", ios::out);
        ofile.close();
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHEDx2\n";
        ofile.clear();
    }
}

void WriteFile() {
    ofstream ofile;
    ofile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ofile.open("C:/Program Files/example.txt", ios::out);
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
    try {
        ofile.open("example.txt", ios::out);
        string l; getline(cin, l);
        l = l + "\n";
        auto new_text = l.c_str();
        ofile.write(new_text, strlen(new_text));
        ofile.close();
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHEDx2\n";
        ofile.clear();
    }
}

void WriteSeveralNotesToFile() {
    ofstream ofile;
    ofile.exceptions(ofstream::badbit | ofstream::failbit);
    try {
        ofile.open("example.txt", ios::app);
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

void ReadFile() {
    ifstream ifile;
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open("C:/Program Files/example.txt");
        string text;
        getline(ifile, text);
        cout << text << endl;
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ifile.clear();
    }
    try {
        ifile.open("example.txt");
        string text;
        getline(ifile, text);
        cout << text << endl;
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHEDx2\n";
        ifile.clear();
    }
}

void ReadSeveralNotesFromFile() {
    ifstream ifile;
    string text, temp;
    ifile.exceptions(ofstream::badbit | ofstream::failbit);
    try
    {
        ifile.open("example.txt");
        while (!ifile.eof()) {
            getline(ifile, temp, '\n');
            text += temp + '\n';
        }
    }
    catch (std::ios_base::failure& e) {
        cout << e.what() << " CATCHED\n";
        ifile.clear();
    }
    ifile.close();
    cout << text << endl;
}

int main()
{
    //CreateFile();
    //WriteFile();
    //ReadFile();
    //WriteSeveralNotesToFile();
    ReadSeveralNotesFromFile();
}
