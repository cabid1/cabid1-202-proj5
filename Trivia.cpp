/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};


//**********Implement Trivia Class Here***********
// Name: Default Constructor
// Desc: Displays the title, Loads Questions and calls menu
// Indicates if the file was not loaded.
// Precondition: None
// Postcondition: User is prompted with assignment menus
template <class T>
Trivia<T>::Trivia(string filename){
    if(LoadQuestions(filename)){//checks that loadfile works
        DisplayTitle();
        MainMenu();
    }else{
        cout<<"the file was not loaded"<< endl;
    }
}
// Name: Destructor
// Desc: Deallocates memory allocated for the Questions and
// resets all variables.
// Precondition: A Trivia exists.
// Postcondition: All dynamically allocated memory in Trivia is deleted.
template <class T>
Trivia<T>::~Trivia(){
    for (int i = 0; i < m_questions->GetSize(); i++){
        delete m_questions->At(i);
    }
    delete m_questions;
}
// Name: LoadQuestions
// Desc: Each input file will be for a specific type of question (int, double, string)
//       Reads in Questions from a file and stores them in anLqueue.
//       An input file will be for exactly one type of question (int, double, string)
// Precondition: None.
// Postcondition: Returns true if file was read. Otherwise, it returns false.
template <class T>
bool Trivia<T>::LoadQuestions(string filename){
    string subject;
    string question;
    string datatype;
    string diff;
    int diffInt;
    T ans;
    string newLine;
    ifstream myFile;
    myFile.open(filename);
    if (myFile.is_open()) {
        m_questions = new Lqueue <Question<T>*>();
        while (myFile.good()) {
            getline(myFile, subject, DELIMITER);//gets subject from line
            getline(myFile, question, DELIMITER);//gets the question
            getline(myFile, datatype, DELIMITER); // gets datatype
            getline(myFile, diff, DELIMITER); // gets difficulty
            myFile >> ans;
            getline(myFile,newLine); // gets difficulty
            diffInt = stoi(diff);
            AddSubject(subject);
            m_questions->Push(new Question<T>(subject,question,datatype,diffInt,ans));
        }
        myFile.close();
        return true;
    }else{
        return false;
    }
}
// Name: MainMenu
// Desc: Presents user with menu options for showing subjects and allowing
// user to work on a subject.
// Precondition: None.
// Postcondition: The main menu is presented.
template <class T>
void Trivia<T>::MainMenu() {
    int num;
    cout << "Choose an option.\n"
            "1. Display Subjects \n"
            "2. Start Subject \n"
            "3. Quit" << endl;
    cin >> num;
    while (num != 3) {//keeps program running
        if (num >= 1 && num < 3) {
            if (num == 1) {
                DisplaySubjects();
            } else if (num == 2) {
                StartSubject();
            }
        }else if (num < 1 || num > 3) { // validates input
            cout << "option out of range" << endl;
        }
        cout << "Choose an option.\n"
                "1. Display Subjects \n"
                "2. Start Subject \n"
                "3. Quit" << endl;
        cin >> num;

        }

    cout << "Thank you trying UMBC Trivia!" << endl;
}
// Name: DisplaySubjects
// Desc: Presents all Subjects with corresponding numerical identifiers.
// Precondition: Subjects have been added.
// Postcondition: All assignments are printed to the screen.
template <class T>
void Trivia<T>::DisplaySubjects(){
    cout << "Possible Subjects:"<<endl;
    int count = 1;
    for(int i = 0; i < int(m_subjects.size()-1);i++ ){//goes through m_subjects and displays
        cout << count << ". " << m_subjects[i] << endl;
        ++count;
    }
}
// Name: StartSubject
// Desc: Starts working on a selected Subject.
// Displays the number of questions in subject.
// Starts at beginning and goes through each question.
// After all questions have been answered:
//       displays total correct, incorrect, and percentage correct
// Precondition: m_questions has been populated
// Postcondition: Returns to main menu
template <class T>
void Trivia<T>::StartSubject(){
    int count = 1;
    double correct = 0;
    double wrong = 0;
    string answer;
    T finalAnswer;
    int choice =ChooseSubject();
    int total = QuestionsPerSubject(m_subjects[choice]);
    cout << "There are " << total  << " questions in this subject." << endl;
    for(int i = 0; i < m_questions->GetSize(); i++){
        if(m_questions->At(i)->m_subject == m_subjects.at(choice)) {
            cout << count << ". Question: " << m_questions->At(i)->m_question << endl;
            cout << "Please answer with a(n) string." << endl;
            cin >> finalAnswer;
            if (m_questions->At(i)->CheckAnswer(finalAnswer)){
                cout << "correct" << endl;
                correct++;
            }else if(!m_questions->At(i)->CheckAnswer(finalAnswer)){
                cout << "incorrect" << endl;
                wrong++;
            }
        count++;
        }
    }
    cout << "You got " << correct << " answers correct" << endl;
    cout << "You got " << wrong<< " answers incorrect" << endl;
    cout << "which is a " << ((correct/total)*100) << "%." << endl;//look at this

}
// Name: AddSubject
// Desc: Checks to see if a subject exists in m_subjects.
//       If not, inserts subject into m_subjects.
// Precondition: A Subject exists.
// Postcondition: Add subject to m_subjects if new subject.
template <class T>
void Trivia<T>::AddSubject(string subject){
    bool inVector = false;
    if(int(m_subjects.size())== 0){
        m_subjects.push_back(subject);
    }else {
        for (int i = 0; i <int(m_subjects.size());i++) {
            if(m_subjects[i]==subject){
                inVector = true;
            }
        }
        if(!inVector){
            m_subjects.push_back(subject);
        }
    }
}
// Name: ChooseSubject
// Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
// in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
// Precondition: A Subject exists.
// Postcondition: Returns value entered minus one
template <class T>
int Trivia<T>::ChooseSubject(){
    int count;
    cout << "What subject would you like to attempt?" << endl;
    DisplaySubjects();
    cin >> count;
    while(count < 0 || count >int(m_subjects.size())){
        cout << "please enter a valid number" << endl;
        cout << "What subject would you like to attempt?" << endl;
        DisplaySubjects();
        cin >> count;
    }
    --count;
    return count;
}
// Name: QuestionsPerSubject
// Desc: Iterates over m_questions and counts how many questions match the subject
// passed into function
// Precondition: A Subject exists.
// Postcondition: Returns number of questions of a particular subject
template <class T>
int Trivia<T>::QuestionsPerSubject(string subject){
    int count = 0;
    for(int i = 0; i < m_questions->GetSize(); i++){
        if(m_questions->At(i)->m_subject == subject){
            ++count;
        }
    }
    return count;

}
// Name: DisplayTitle
// Desc: Displays opening Welcome message
// Precondition: None.
// Postcondition: Title is displayed.
template <class T>
void Trivia<T>:: DisplayTitle(){
    cout << "Welcome to UMBC Trivia!" << endl;
}

#endif
