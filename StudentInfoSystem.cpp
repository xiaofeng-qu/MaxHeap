#include "StudentInfoSystem.hpp"

StudentInfoSystem::StudentInfoSystem(){
    filePath = "316p2.txt";
    byId = true;
    menu();
}

void StudentInfoSystem::menu(){
    cout << "(1) Read data from external text file." << endl; /* Prompt the user to enter an external input file name or use default file name. */
    cout << "(2) Build a max heap in terms of ID or LastName." << endl; /* prompt for selection */
    cout << "(3) Add a new record to max heap." << endl; /* prompt for entering new record */
    cout << "(4) Delete a record from the max heap." << endl; /* Prompt for ID or LastName*/
    cout << "(5) Print sorted list from max heap in ascending order based on ID or LastName." << endl;
    cout << "(6) Save a sorted list to a binary file named as 316p2.rec." << endl;
    cout << "(7) Load 316p2.rec and print it." << endl;
    cout << "(8) Quit." << endl;

    int menuItem;
    cin >> menuItem;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(menuItem){
        case 1:
                getFilePath();
                cout << endl;
                menu();
                break;
        case 2:
                readFile();
                cout << endl;
                menu();
                break;
        case 3:
                addRecord();
                cout << endl;
                menu();
                break;
        case 4:
                deleteRecord();
                cout << endl;
                menu();
                break;
        case 5:
                printRecords();
                cout << endl;
                menu();
                break;
        case 6:
                saveRecords();
                cout << endl;
                menu();
                break;
        case 7:
                loadBinary();
                cout << endl;
                menu();
                break;
        case 8:
                exit(0);
        default:
                cout << "No such option. Please choose from 1-8.\n" << endl;
                menu();
                break;
    }
}

void StudentInfoSystem::getFilePath(){
    cout << "Please input your text file path: ";
    getline(cin, filePath);
}

void StudentInfoSystem::readFile(){
    cout << "(1) Sort by ID" << endl;
    cout << "(2) Sort by last name" << endl;
    int option;
    cin >> option;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(option){
        case 1:
                orderById();
                StudentHeapById.clearHeap();
                StudentHeapByLastName.clearHeap();
                buildById();
                buildByLastName();
                break;
        case 2:
                orderByLastName();
                StudentHeapById.clearHeap();
                StudentHeapByLastName.clearHeap();
                buildById();
                buildByLastName();
                break;
        default:
                cout << "No such option. Please choose from 1-2.\n" << endl;
                readFile();
                break;
    }
}

void StudentInfoSystem::buildById(){
    StudentById students[100];
    int index=0;
    ifstream infile(filePath);
    while(infile >> students[index].firstname >> students[index].lastname >> students[index].id >> students[index].gpa && index < 100){
        StudentHeapById.insertKey(students[index]);
    }
    infile.close();
    // StudentHeapById.ascPrint();
}

void StudentInfoSystem::buildByLastName(){
    StudentByLastName students[100];
    int index=0;
    ifstream infile(filePath);
    while(infile >> students[index].firstname >> students[index].lastname >> students[index].id >> students[index].gpa && index < 100){
        StudentHeapByLastName.insertKey(students[index]);
    }
    infile.close();
    // StudentHeapById.ascPrint();
}

void StudentInfoSystem::addRecord(){
    string firstname, lastname;
    int id;
    float gpa;
    cout << "(1) Add by ID" << endl;
    cout << "(2) Add by Last Name" << endl;
    int option;
    cin >> option;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(option){
    case 1:
        orderById();
        break;
    case 2:
        orderByLastName();
        break;
    default:
        cout << "No such option. Please choose from 1-2.\n" << endl;
        addRecord();
        break;
    }
    cout << "Input the First Name, Last Name, ID, and GPA, separate by space: (First and Last Name should be less than 20 characters.)";
    while(true){
        if(cin >> firstname >> lastname >> id >> gpa){
            if(firstname.length() > 20){
                cout << "The First Name is longer than 20 characters, please input the First Name, Last Name, ID, and GPA, separate by space: (First and Last Name should be less than 20 characters.)";
            } else if(lastname.length() > 20) {
                cout << "The Last Name is longer than 20 characters, please input the First Name, Last Name, ID, and GPA, separate by space: (First and Last Name should be less than 20 characters.)";
            } else break;
        } else {
            cout << "There is something wrong with your input. please input the First Name, Last Name, ID, and GPA, separate by space: (First and Last Name should be less than 20 characters.)";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    StudentById studentById(firstname, lastname, id, gpa);
    StudentByLastName studentByLastName(firstname, lastname, id, gpa);
    StudentHeapById.insertKey(studentById);
    StudentHeapByLastName.insertKey(studentByLastName);
}

void StudentInfoSystem::deleteRecord(){
    string firstname = "", lastname = "";
    int id = 0;
    float gpa = 0.0;
    cout << "(1) Delete by ID" << endl;
    cout << "(2) Delete by Last Name" << endl;
    int option;
    cin >> option;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    StudentById studentById;
    StudentByLastName studentByLastName;
    switch(option){
    case 1:
        orderById();
        cout << "Please enter the id you want to delete: ";
        cin >> id;
        studentById = StudentById(firstname, lastname, id, gpa);
        studentById = StudentHeapById.deleteKey(studentById);
        studentByLastName = StudentByLastName(firstname, studentById.lastname, id, gpa);
        StudentHeapByLastName.deleteKey(studentByLastName);
        break;
    case 2:
        orderByLastName();
        cout << "Please enter the last name you want to delete: ";
        cin >> lastname;
        studentByLastName = StudentByLastName(firstname, lastname, id, gpa);
        studentByLastName = StudentHeapByLastName.deleteKey(studentByLastName);
        studentById = StudentById(firstname, lastname, studentByLastName.id, gpa);
        StudentHeapById.deleteKey(studentById);
        break;
    default:
        cout << "No such option. Please choose from 1-2.\n" << endl;
        deleteRecord();
        break;
    }
}

void StudentInfoSystem::printRecords(){
    cout << "(1) Print by ID" << endl;
    cout << "(2) Print by Last Name" << endl;
    int option;
    cin >> option;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(option){
    case 1:
        orderById();
        StudentHeapById.ascPrint();
        break;
    case 2:
        orderByLastName();
        StudentHeapByLastName.ascPrint();
        break;
    default:
        cout << "No such option. Please choose from 1-2.\n" << endl;
        printRecords();
        break;
    }
}

void StudentInfoSystem::saveRecords(){
    if(isById()){
        MaxHeap<StudentById> StudentHeapId(StudentHeapById);
        stack<StudentById> StudentStackId;
        while(!StudentHeapId.isEmpty()){
            StudentStackId.push(StudentHeapId.removeMax());
        }
        StudentById studentId;
        ofstream outfile("316p2.rec", ios::out | ios::binary | ios::trunc);
        while(!StudentStackId.empty()){
            studentId = StudentStackId.top();
            StudentStackId.pop();
            size_t str_size = studentId.firstname.size();
            outfile.write(reinterpret_cast<char *>(&str_size), sizeof(str_size));
            outfile.write(studentId.firstname.c_str(), str_size*sizeof(char));
            str_size = studentId.lastname.size();
            outfile.write(reinterpret_cast<char *>(&str_size), sizeof(str_size));
            outfile.write(studentId.lastname.c_str(), str_size*sizeof(char));
            outfile.write(reinterpret_cast<char *>(&studentId.id), sizeof(studentId.id));
            outfile.write(reinterpret_cast<char *>(&studentId.gpa), sizeof(studentId.gpa));
        }
        outfile.close();
    } else {
        MaxHeap<StudentByLastName> StudentHeapLastName(StudentHeapByLastName);
        stack<StudentByLastName> StudentStackLastName;
        while(!StudentHeapLastName.isEmpty()){
            StudentStackLastName.push(StudentHeapLastName.removeMax());
        }
        StudentByLastName studentLastName;
        ofstream outfile("316p2.rec", ios::out | ios::binary | ios::trunc);
        while(!StudentStackLastName.empty()){
            studentLastName = StudentStackLastName.top();
            StudentStackLastName.pop();
            size_t str_size = studentLastName.firstname.size();
            outfile.write(reinterpret_cast<char *>(&str_size), sizeof(str_size));
            outfile.write(studentLastName.firstname.c_str(), str_size*sizeof(char));
            str_size = studentLastName.lastname.size();
            outfile.write(reinterpret_cast<char *>(&str_size), sizeof(str_size));
            outfile.write(studentLastName.lastname.c_str(), str_size*sizeof(char));
            outfile.write(reinterpret_cast<char *>(&studentLastName.id), sizeof(studentLastName.id));
            outfile.write(reinterpret_cast<char *>(&studentLastName.gpa), sizeof(studentLastName.gpa));
        }
        outfile.close();
    }
}

void StudentInfoSystem::loadBinary(){
    ifstream infile("316p2.rec", ios::in | ios::binary);
    while(true){
        int str_size;
        infile.read(reinterpret_cast<char *>(&str_size), sizeof(str_size));
        vector<char> fn(str_size);
        infile.read(reinterpret_cast<char *>(&fn[0]), str_size*sizeof(char));
        string firstname(fn.begin(), fn.end());
        infile.read(reinterpret_cast<char *>(&str_size), sizeof(str_size));
        vector<char> ln(str_size);
        infile.read(reinterpret_cast<char *>(&ln[0]), str_size*sizeof(char));
        string lastname(ln.begin(), ln.end());
        int id;
        infile.read(reinterpret_cast<char *>(&id), sizeof(int));
        float gpa;
        infile.read(reinterpret_cast<char *>(&gpa), sizeof(float));
        if( infile.eof() ) break;
        cout << firstname << "\t" << lastname << "\t" << id << "\t" << gpa << endl;
    }
    infile.close();
}
