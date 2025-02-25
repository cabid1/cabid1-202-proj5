/*****************************************************************************
 ** File: Question.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Question class. Includes both class definition and
 class function definitions.
*****************************************************************************/

#ifndef QUESTION_CPP
#define QUESTION_CPP
#include <iostream>
#include <string>
using namespace std;

// Global constants for number of types
const int NUM_TYPES = 6;
const string KNOWN_TYPES[NUM_TYPES] = { "int", "double", "bool", "char", "string"};

template <class T>
struct Question {
public:
  // Name: Overloaded Constructor
  // Desc: Constructs a question object given all fields.
  // Precondition: Question must be templated by the data type passed in as an argument.
  // Postcondition: A new Question object is created for use.
  Question(string subject, string question, string datatype, int difficulty, T answer);
  // Name: Copy Constructor
  // Desc: Makes a copy of an existing Question object
  // Precondition: A Question object exists.
  // Postcondtion: A new populated Question exists
  Question(const Question&);
  // Name: Destructor
  // Desc: Resets variables and deallocates dynamically allocated memory
  // Precondition: A Question object exists.
  // Postcondtion: All dynamically allocated memory is destroyed.
  ~Question();
  // Name: CheckAnswer
  // Desc: Compares passed value with m_answer
  // Precondition: A Question object exists.
  // Postcondtion: Returns true if value passed matches m_answer else false.
  bool CheckAnswer(T submission);
  // Name: Overloaded insertion operator
  // Desc: Returns ostream object for the question prompt. Presents
  // question and answer data type.
  // Precondition: Question object exists
  // Postcondition: Returns ostream of question prompt.
  template<class Y> //As friend function, has to use different templated variable
  friend ostream& operator<< (ostream& output, Question<Y>&);

  //Member variables (all public)
  string m_subject; //Subject for question
  string m_question; // Question
  string m_datatype; // What type of data used for answer
  int m_difficulty; // Difficulty Rating (1 - 5)
  T m_answer; // Answer to question
  bool m_isAnswered; // True once question is answered. Otherwise, false.
};

//**********Implement Question Class Here***********
// Name: Overloaded Constructor
// Desc: Constructs a question object given all fields.
// Precondition: Question must be templated by the data type passed in as an argument.
// Postcondition: A new Question object is created for use.
template <class T>
Question<T> :: Question(string subject, string question, string datatype, int difficulty, T answer){
    m_subject = subject;
    m_question= question; // Question
    m_datatype= datatype; // What type of data used for answer
    m_difficulty =difficulty; // Difficulty Rating (1 - 5)
    m_answer=answer; // Answer to question
    m_isAnswered= false;

}
// Name: Copy Constructor
// Desc: Makes a copy of an existing Question object
// Precondition: A Question object exists.
// Postcondtion: A new populated Question exists
template <class T>
Question<T> ::Question(const Question& question){
    m_subject = question.m_subject;
    m_question= question.m_question; // Question
    m_datatype= question.m_datatype; // What type of data used for answer
    m_difficulty =question.m_difficulty; // Difficulty Rating (1 - 5)
    m_answer=question.m_answer; // Answer to question
    m_isAnswered= question.m_isAnswered;
}
// Name: Destructor
// Desc: Resets variables and deallocates dynamically allocated memory
// Precondition: A Question object exists.
// Postcondtion: All dynamically allocated memory is destroyed.
template <class T>
Question<T> :: ~Question(){}
// Name: CheckAnswer
// Desc: Compares passed value with m_answer
// Precondition: A Question object exists.
// Postcondtion: Returns true if value passed matches m_answer else false.
template <class T>
bool Question<T> ::CheckAnswer(T submission){
    m_isAnswered = true;
    if(submission == m_answer){
        return true;
    }else{
        return false;
    }
}
// Name: Overloaded insertion operator
// Desc: Returns ostream object for the question prompt. Presents
// question and answer data type.
// Precondition: Question object exists
// Postcondition: Returns ostream of question prompt.
template<class Y> //As friend function, has to use different templated variable
ostream& operator<< (ostream& output, Question<Y>&y){
    output <<  y.m_question << " " << y.m_answer<< endl;
    return output;
}






#endif
