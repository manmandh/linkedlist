// Problem 1. We want to manage a list of students. Information of each student consists
// of the following fields: name, date of birth (day, month, year), math mark, physic mark,
// language mark. Write a program solving the following requirements using singly linked
// list:
// 1) Input n students’ information.
// 2) Print out the student list.
// 3) Add a new student to the list.
// 4) Count the number of students in a given year of birth.
// 5) Check if a student name x exists in the list or not.
// 6) Delete a student from the list by a given name x.
// 7) Find the student(s) having the biggest average of math, physic and language marks.
// 8) Print the list of students whose math mark is less than 5.
// 9) Write the student list to a file named StudentList.txt.

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

struct BirthDay
{
    int day;
    int month;
    int year;
};

struct Student
{
    string name;
    BirthDay birthDay;
    float mathMark, physicMark, languageMark;
};

struct Node
{
    Student data;
    Node *next;
};

struct LinkedList
{
    Node *head;
    Node *tail;
};

/* Linked list */
// Khoi tao list
void initList(LinkedList &list)
{
    list.head = NULL;
    list.tail = NULL;
}

bool isEmptyList(LinkedList &list)
{
    return list.head == NULL;
}

// Tim kiem ten hoc sinh co ton tai trong danh sach khong
bool isStudentNameExistList(LinkedList &list, string &name)
{
    if (!isEmptyList(list))
    {
        Node *node = list.head;
        while (node != NULL)
        {
            if (node->data.name == name)
            {
                return true;
            }

            node = node->next;
        }
    }
    return false;
}

// Tao node moi
Node *createNode(Student &s)
{
    Node *node = new Node();
    node->data = s;
    node->next = NULL;
    return node;
}

// Them dau
void addHead(LinkedList &list, Node *node)
{
    if (list.head == NULL)
    {
        list.head = node;
        list.tail = node;
    }
    else
    {
        node->next = list.head;
        list.head = node;
    }
}

// Them cuoi
void addTail(LinkedList &list, Node *node)
{
    if (list.head == NULL)
    {
        list.head = node;
        list.tail = node;
    }
    else
    {
        list.tail->next = node;
        list.tail = node;
    }
}

// Xoa dau danh sach
bool deleteHead(LinkedList &list)
{
    if (list.head == NULL)
    {
        return false;
    }

    Node *p = list.head->next;
    if (list.head->next == NULL)
    {
        delete list.head;
        initList(list);
    }
    else
    {
        delete list.head;
        list.head = p;
    }
    return true;
}

// Xoa cuoi danh sach
bool deleteTail(LinkedList &list)
{
    if (list.head != NULL)
    {
        if (list.head->next == NULL)
        {
            delete list.tail;
            initList(list);
            return true;
        }

        for (Node *p = list.head; p != NULL; p = p->next)
        {
            if (p->next == list.tail)
            {
                delete list.tail;
                p->next = NULL;
                list.tail = p;
                return true;
            }
        }
    }
    return false;
}

// Xoa node phia sau node duoc nhap vao
bool deleteAfterNode(LinkedList &list, Node *node)
{
    if (node == NULL)
    {
        return false;
    }

    Node *p = node->next;
    node->next = p->next;
    if (p == list.tail)
    {
        list.tail = node;
    }

    delete p;
    return true;
}

// Xoa hoc sinh bang ten
bool deleteStudentByName(LinkedList &list, string &name)
{
    if (list.head == NULL)
    {
        return false;
    }

    Node *node = NULL;
    Node *pre = NULL;

    for (Node *p = list.head; p != NULL; p = p->next)
    {
        if (p->data.name == name)
        {
            node = p;
            break;
        }
        pre = p;
    }

    if (node != NULL)
    {
        if (node == list.head)
        {
            deleteHead(list);
        }
        else
        {
            deleteAfterNode(list, pre);
        }
        return true;
    }
    return false;
}

/// @brief Dem so hoc sinh co nam sinh duoc nhap vao
/// @param list Danh sach hoc sinh
/// @param year Nam sinh dieu kien
/// @return So hoc sinh co nam sinh trung voi year
int countStudentInYearOfBirth(LinkedList &list, int &year)
{
    int count = 0;
    if (list.head != NULL)
    {
        Node *node = list.head;
        while (node != NULL)
        {
            if (node->data.birthDay.year == year)
            {
                ++count;
            }

            node = node->next;
        }
    }

    return count;
}

// Tinh diem trung binh toan ly van cua sinh vien
float calcAvgMark(Student s)
{
    return (s.mathMark + s.physicMark + s.languageMark) / 3;
}
// Tim kiem danh sach hoc sinh co diem trung binh lon nhat
vector<Student> findStudentByMaxAvg(LinkedList &list)
{
    vector<Student> listAvgMax = {};
    if (list.head == NULL)
    {
        return listAvgMax;
    }

    Node *nodeMax = list.head;
    for (Node *p = list.head->next; p != NULL; p = p->next)
    {
        if (calcAvgMark(p->data) > calcAvgMark(nodeMax->data))
        {
            nodeMax = p;
        }
    }
    for (Node *p = list.head; p != NULL; p = p->next)
    {
        if (calcAvgMark(p->data) == calcAvgMark(nodeMax->data))
        {
            listAvgMax.push_back(p->data);
        }
    }
    return listAvgMax;
}

/* input & output */
void inputStudent(Student &s)
{
    cout << "\nEnter name: ";
    getline(cin, s.name);
    cout << "Day of birth\n";
    cout << setw(2) << "";
    cout << "Enter day: ";    
    cin >> s.birthDay.day;
    cout << setw(2) << "";
    cout << "Enter month: ";
    cin >> s.birthDay.month;
    cout << setw(2) << "";
    cout << "Enter year: ";
    cin >> s.birthDay.year;
    cout << "Enter Math Mark: ";
    cin >> s.mathMark;
    cout << "Enter Physic Mark: ";
    cin >> s.physicMark;
    cout << "Enter language Mark: ";
    cin >> s.languageMark;
    cin.ignore();
}

void inputListStudent(LinkedList &list, int &n)
{
    Student s = {};
    for (int i = 0; i < n; i++)
    {
        cout << "\nStudent " << i + 1;
        inputStudent(s);
        addHead(list, createNode(s));
    }
}

void outputHeader(int tableCell = 20, int marginLeft = 2, int countCol = 5)
{
    cout
        << endl
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << "Name"
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << "Date of birth"
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << "Math mark"
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << "Physic mark"
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << "Language mark"
        << setw(marginLeft) << left << "|";
    cout
        << endl
        << setw((tableCell * countCol + marginLeft * countCol) + 1)
        << setfill('=') << "" << setfill(' ');
}

/// @brief Xuat mot hoc sinh
/// @param s du lieu mot hoc sinh
/// @param tableCell Do rong khoang trong tung o trong bang
/// @param marginLeft Canh le trai tung o trong bang
/// @param countCol So cot cua bang
void outputStudent(Student &s, int tableCell = 20, int marginLeft = 2, int countCol = 5)
{
    string birtday = to_string(s.birthDay.day) + "/" + to_string(s.birthDay.month) + "/" + to_string(s.birthDay.year);
    cout
        << endl
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << s.name
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << birtday
        << setw(marginLeft) << left << "|";
    cout
        << setw(tableCell) << left << s.mathMark
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << s.physicMark
        << setw(marginLeft) << left << "|"
        << setw(tableCell) << left << s.languageMark
        << setw(marginLeft) << left << "|";
}

void printList(LinkedList &list)
{
    if (isEmptyList(list))
    {
        cout << "\nList is empty!";
        return;
    }

    outputHeader();
    for (Node *p = list.head; p != NULL; p = p->next)
    {
        outputStudent(p->data);
    }
}

//In danh sach sinh vien co diem toan nho hon 5
void printListMathMarkLessFive(LinkedList &list)
{
    if (isEmptyList(list))
    {
        cout << "\nList is empty!";
        return;
    }

    outputHeader();
    for (Node *p = list.head; p != NULL; p = p->next)
    {
        if (p->data.mathMark < 5)
        {
            outputStudent(p->data);
        }
    }
}

//Xuat danh sach sinh vien ra file
bool exportFile(LinkedList &list)
{
    if (isEmptyList(list))
    {
        return false;
    }
    
    int marginLeft = 2;
    int tableCell = 20;
    int countCol = 5;
    string birtday = "";

    fstream fo;
    //Mo file de ghi, truong hop khong co file se tao moi file
    fo.open("StudentList.txt", ios::out);
    
        fo  << setw(45) << setfill('=') << "" << setfill(' ')
            << " "
            << "MANAGE STUDENT LIST"
            << " "
            << setw(45) << setfill('=') << "" << setfill(' ');

        fo  << endl
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << "Name"
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << "Date of birth"
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << "Math mark"
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << "Physic mark"
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << "Language mark"
            << setw(marginLeft) << left << "|";
    fo
        << endl
        << setw((tableCell * countCol + marginLeft * countCol) + 1)
        << setfill('=') << "" << setfill(' ');
    for (Node* p = list.head; p != NULL; p = p->next)
    {
        birtday = to_string(p->data.birthDay.day) + "/" + to_string(p->data.birthDay.month) + "/" + to_string(p->data.birthDay.year);
        fo << endl
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << p->data.name
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << birtday
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << p->data.mathMark
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << p->data.physicMark
            << setw(marginLeft) << left << "|"
            << setw(tableCell) << left << p->data.languageMark
            << setw(marginLeft) << left << "|";
    }
    fo.close();
    return true;
}

/* Menu */
//Tao tieu de cho chuong trinh
void titleMenu(string title = "MANAGE STUDENT LIST", int length = 41)
{
    cout
        << setw(length) << setfill('=') << "" << setfill(' ')
        << " "
        << title
        << " "
        << setw(length) << setfill('=') << "" << setfill(' ');
}

//Danh sach chuc nang cua chuong trinh
void menu(char &choose)
{
    titleMenu();
    cout << "\n1) Input n students information";
    cout << "\n2) Print out the student list";
    cout << "\n3) Add a new student to the list";
    cout << "\n4) Count the number of students in a given year of birth";
    cout << "\n5) Check if a student name x exists in the list or not";
    cout << "\n6) Delete a student from the list by a given name x";
    cout << "\n7) Find the student(s) having the biggest average of math, physic and language marks";
    cout << "\n8) Print the list of students whose math mark is less than 5";
    cout << "\n9) Write the student list to a file named StudentList.txt";
    cout << "\n0) Exit";
    cout << "\nChoose: ";
    cin >> choose;
    cin.ignore();
}

//Menu nay thay cho lenh dung mang hinh
void menuContinue()
{
    cout << "\nPress enter key to continue...";
    cin.get();
}

void logic(LinkedList &list)
{
    string name = "";
    vector<Student> ls = {};
    Student s = {};
    int year = 0;
    int n = 0;
    char choose = ' ';
    do
    {
        system("cls");
        menu(choose);
        switch (choose)
        {
        case '1': // Input n students’ information
            system("cls");
            titleMenu("Input n students information");
            cout << "\nEnter student number: ";
            cin >> n;
            cin.ignore();
            inputListStudent(list, n);
            cout << "\nAdded " << n << " student to the list";
            menuContinue();
            break;
        case '2': // Print out the student list
            system("cls");
            titleMenu("Print out the student list");
            printList(list);
            menuContinue();
            break;
        case '3': // Add a new student to the list
            system("cls");
            titleMenu("Add a new student to the list");
            inputStudent(s);
            addTail(list, createNode(s));
            cout << "\nAdded a student to the list";
            menuContinue();
            break;
        case '4': // Count the number of students in a given year of birth
            system("cls");
            titleMenu("Count the number of students in a given year of birth");
            cout << "\nEnter year of birth: ";
            cin >> year;
            cin.ignore();
            cout << "There is " << countStudentInYearOfBirth(list, year) << " student";
            menuContinue();
            break;
        case '5': // Check if a student name x exists in the list or not
            system("cls");
            titleMenu("Check if a student name x exists in the list or not");
            cout << "\nEnter student name: ";
            getline(cin, name);
            if (isStudentNameExistList(list, name))
            {
                cout << "\nExist name";
            }
            else
            {
                cout << "\nNot exist!";
            }
            menuContinue();
            break;
        case '6': // Delete a student from the list by a given name x
            system("cls");
            titleMenu("Delete a student from the list by a given name x");
            cout << "\nEnter student name: ";
            getline(cin, name);

            if (deleteStudentByName(list, name))
            {
                cout << "\nDeleted student name " << name;
            }
            else
            {
                cout << "\nNot found " << name << "!";
            }

            menuContinue();
            break;
        case '7': // Find the student(s) having the biggest average of math, physic and language marks
            system("cls");
            titleMenu("Find the student(s) having the biggest average of math, physic and language marks", 14);
            ls = findStudentByMaxAvg(list);
            if (ls.size() != 0)
            {
                outputHeader();
                for (int i = 0, l = ls.size(); i < l; i++)
                {
                    outputStudent(ls[i]);
                    cout << endl;
                }
            }
            else
            {
                cout << "\nList is empty!";
            }

            menuContinue();
            break;
        case '8': // Print the list of students whose math mark is less than 5
            system("cls");
            titleMenu("Print the list of students whose math mark is less than 5", 26);
            printListMathMarkLessFive(list);
            menuContinue();
            break;
        case '9': // Write the student list to a file named StudentList.txt
            system("cls");
            titleMenu("Write the student list to a file named StudentList.txt", 26);
            if (exportFile(list))
            {
                cout << "\nExported file StudentList.txt";
            } else
            {
                cout << "\nList is empty!";
            }
            menuContinue();
            break;
        case '0':
            cout << "\nExit";
            break;
        default:
            system("cls");
            cout << "\nPlease choose from 0 to 9!";
            menuContinue();
            break;
        }
    } while (choose != '0');
}

int main()
{
    LinkedList list;
    initList(list);
    logic(list);
    return 0;
}