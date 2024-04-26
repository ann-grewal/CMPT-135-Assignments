// a2.cpp

// student information
    // name: Anureet Grewwal
    // student id #: 301554326
    // sfu email: anureet_grewal@sfu.ca

// statement of originality 
    // All the code and comments below are my own original work. For any non-
    // original work, I have provided citations in the comments with enough detail
    // so that someone can see the exact source and extent of the borrowed work.
    // In addition, I have not shared this work with anyone else, and I have not
    // seen solutions from other students, tutors, websites, books, etc. 

// additional notes 
    // visiual studios code, windows linux, ubuntu, windows laptop 

// a2.cpp

#include "cmpt_error.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

class str_vec {

  // named with arr, not be confused with methods 
  int arr_size; 
  int arr_capacity; 
  string* arr; 

  public: 

  // constructer initializer list, create array on free store 
  str_vec (int given_size, int given_capacity) 
  : arr_size(given_size), arr_capacity(given_capacity)
  {
    arr = new string[given_capacity]; 
  }

  // question 1 - default constructor
  str_vec () 
  : str_vec (0, 10) 
  {}

  // question 2 - destructor
  ~str_vec() {
    delete[] arr; 
  }

  // question 3 - constructer that fills array
  str_vec (int n, string s) {

    // check input size is 1 or more 
    if (n < 1 ) {
      cmpt::error("cannot set capacity to 0"); 
    }

    // initalize everything from regular constructor 
    arr = new string[n]; 
    arr_size = n; 
    arr_capacity = n; 

    // fill array 
    for (int i = 0; i < n; i++) {
      arr[i] = s; 
    }
  }

  // question 4 - copy constructor 
  str_vec (const str_vec& other)
  : str_vec(other.arr_size, other.arr_size)  
  { 
    // copy elements 
    for (int i = 0; i < other.arr_size; i++) {
      arr[i] = other.get(i); 
    }
  }

  // question 5 - constructor that reads from an array 
  str_vec (const char* array[], int n)
  : str_vec (n, n)
  {
    for (int i = 0; i < n; i++) {
      arr[i] = array[i]; 
    }
  }

  // question 6 - constant getters 
  int size() const {
    return arr_size; 
  }

  int length() const {
    return arr_size; 
  }

  int capacity() const {
    return arr_capacity; 
  }

  double pct_used() const {
    return (static_cast <double> (arr_size)) / (static_cast <double> (arr_capacity)); 
  }

  // question 7 - more constant methods
  string to_str() const {

    string arr_string;
    arr_string = "{" ; 
    
    if (arr_size > 0) {
      arr_string += "\"" + arr[0] + "\"";

      for (int i = 1; i < arr_size; i++) {
        arr_string += ", \"" + arr[i] + "\""; 
      }
    }

    arr_string += "}"; 
    return arr_string; 
  }

  void print () const {
    cout << to_str(); 
  }

  void println () const {
    cout << to_str() << "\n"; 
  }

  // question 8 - getters and setters 
  string get (int i) const {
    if (i < 0 && i > (arr_size-1))  {
      cmpt::error("accessing an index outside of array bounds, bounds 0 to size - 1"); 
    }
    return arr [i]; 
  }

  void set (int i, string s) {
    if (i < 0 && i > (arr_size-1))  {
      cmpt::error("accessing an index outside of array bounds, bounds 0 to size - 1"); 
    } else {
      arr [i] = s; 
    }
  }

  // question 9 - add string or another str_vec 
  void append (string add_string) {

    if (arr_capacity <= arr_size) {

      // make new array
      arr_capacity *= 2; 
      string* arr_new = new string [arr_capacity]; 

      // copy elements 
      for (int i = 0; i < arr_size; i++) {
        arr_new[i] = arr[i]; 
      }
      
      // move pointer after deallocation 
      delete[] arr; 
      arr = arr_new; 
    }

    arr[arr_size] = add_string; 
    arr_size++; 
  }

  void append (str_vec add_arr) {

    // add each element from array seperately 
    for (int i = 0; i < add_arr.arr_size; i++) {
      append(add_arr.get(i)); 
    }
  }

  // question 10 - capitilize method 
  void capitalize_all() {
    for (int i = 0; i < arr_size; i++) {
     
      // checking using ascii table relations, lowercase 96 through 123
      if (arr[i][0] > 96 && arr[i][0] < 123 ) {

        // manipulating by minusing the 31 difference between lowercase and uppercase 
        arr[i][0] -= 32; 
      }
    }
  }

  // question 11 - find and remove method mutation 
  void remove_first(const string& s) {

    // find in array 
    for (int i = 0; i < arr_size; i++) {

      // if found overwrite and break loop 
      if (arr[i] == s) {
        arr_size--; 
        for (int j = i; j < arr_size; j++) {
          arr[j] = arr[j+1]; 
        }
        break; 
      }
    }  
  }

  // question 12 - keep only those that start with c (using question 11) 
  void keep_all_starts_with (char c) {
    for (int i = 0; i < arr_size; i++) {

      // remove anything that does not start with c 
      if (arr[i][0] != c ) {
        remove_first (arr[i]); 

        // loop back to the element that is going to fill removed
        i--;
      }
    }
  }

  // question 13 - clear / squish by making a new arrys 
  void clear() {
    delete[] arr; 
    arr = new string[arr_capacity]; 
    arr_size = 0; 
  }

  void squish() {

    // handle size 0 case 
    if (arr_size == 0) {
      cmpt::error("cannot set capacity to 0"); 
    }

    // make new array
    arr_capacity = arr_size; 
    string* arr_new = new string [arr_capacity];    
    
    for (int i = 0; i < arr_size; i++) {
      arr_new[i] = arr[i]; 
    }

    delete[] arr; 
    arr = arr_new; 
  }

  // question 15 - sort into alphabetical order
  // using the built in std::sort function from algorithms that alphabetizes vectors or arrays from cmpt 130 
  void sort() {
    std::sort (arr, arr + arr_size); 
  }
}; 

// question 14 - overload operators
bool operator == (const str_vec a, const str_vec b) {
  if (a.size() != b.size()) return false; 

  for (int i = 0; i < a.size(); i++) {
    if (a.get(i) != b.get(i)) return false; 
  }

  // if not yet returned 
  return true; 
}

// negated ==
bool operator != (const str_vec a, const str_vec b) {
  return !(a == b); 
}

// question 6 tests
void test_size (){
  str_vec structure1; 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, "goodbye"); 
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  assert(structure1.size() == 0); 
  assert(structure2.size() == 10); 
  assert(structure3.size() == 10); 
  assert(structure4.size() == 11); 
  assert(structure5.size() == 1); 
  assert(structure6.size() == 3); 
  assert(structure1.length() == 0); 
  assert(structure2.length() == 10); 
  assert(structure3.length() == 10); 
  assert(structure4.length() == 11); 
  assert(structure5.length() == 1); 
  assert(structure6.length() == 3); 
  cout << "test_size completed \n";  
}
void test_capacity (){
  str_vec structure1; 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, "goodbye"); 
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  assert(structure1.capacity() == 10); 
  assert(structure2.capacity() == 10); 
  assert(structure3.capacity() == 10); 
  assert(structure4.capacity() == 11); 
  assert(structure5.capacity() == 1); 
  assert(structure6.capacity() == 3); 
  cout << "test_capacity completed \n"; 
}
void test_pct (){
  str_vec structure1; 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (10, 20); 
  str_vec structure5 (5, 20); 
  str_vec structure6 (1, "greeting"); 
  const char* array7[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure7 (array7, 3); 
  assert(structure1.pct_used() == 0); 
  assert(structure2.pct_used() == 1); 
  assert(structure3.pct_used() == 1); 
  assert(structure4.pct_used() == 0.5); 
  assert(structure5.pct_used() == 0.25); 
  assert(structure6.pct_used()  == 1); 
  assert(structure7.pct_used()  == 1); 
  cout << "test_pct completed \n"; 
}

// question 7 tests
void test_to_str () {
  str_vec structure1; 
  str_vec structure2 (3, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (5, "goodbye"); 
  str_vec structure5 (1, "greeting");
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  assert(structure1.to_str() == "{}"); 
  assert(structure2.to_str() == "{\"hello\", \"hello\", \"hello\"}"); 
  assert(structure3.to_str() == "{\"hello\", \"hello\", \"hello\"}"); 
  assert(structure4.to_str() == "{\"goodbye\", \"goodbye\", \"goodbye\", \"goodbye\", \"goodbye\"}"); 
  assert(structure5.to_str() == "{\"greeting\"}"); 
  assert(structure6.to_str() == "{\"good morning\", \"good afternoon\", \"good evening\"}"); 
  cout << "test_to_str completed \n"; 
}

// question 8 tests 
void test_get ()  {
  str_vec structure1; 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, "goodbye");
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  assert(structure1.get(0) == ""); 
  assert(structure2.get(0) == "hello"); 
  assert(structure3.get(1) == "hello"); 
  assert(structure4.get(10) == "goodbye"); 
  assert(structure5.get(0) == "greeting"); 
  assert(structure6.get(1) == "good afternoon"); 
  cout << "test_get completed \n"; 
}
void test_set ()  {
  str_vec structure1; 
  str_vec structure2 (3, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (5, "goodbye"); 
  str_vec structure5 (1, "greeting");
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure1.set(0, "hello"); 
  structure2.set(1, "goodbye"); 
  structure3.set(2, ""); 
  structure4.set(4, "hello"); 
  structure5.set(0, " "); 
  structure6.set(1, "goodnight"); 
  assert(structure1.get(0) == "hello"); 
  assert(structure2.get(1) == "goodbye"); 
  assert(structure3.get(2) == ""); 
  assert(structure4.get(4) == "hello"); 
  assert(structure5.get(0) == " "); 
  assert(structure6.get(1) == "goodnight"); 
  cout << "test_get completed \n"; 
}

// question 9 tests 
void test_append_string() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, "goodbye");
  str_vec structure5 (1, "greeting");
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure1.append ("hello"); 
  structure2.append ("another hello"); 
  structure3.append ("another hello");  
  structure4.append ("another goodbye"); 
  structure5.append ("");
  structure6.append ("goodnight"); 
  assert(structure1.get(0) == "hello"); 
  assert(structure2.get(10) == "another hello"); 
  assert(structure3.get(10) == "another hello"); 
  assert(structure4.get(11) == "another goodbye"); 
  assert(structure5.get(1) == "");
  assert(structure6.get(3) == "goodnight"); 
  cout << "test_append_string completed \n"; 
}
void test_append_arr() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, "goodbye");
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure1.append (structure2); 
  structure2.append (structure2); 
  structure3.append (structure4);  
  structure4.append (structure2); 
  structure5.append (structure5); 
  structure6.append (structure1); 
  assert ((structure1.get(9) == "hello") && (structure1.capacity() == 16)); 
  assert ((structure2.get(19) == "hello") && (structure2.capacity() == 20)); 
  assert ((structure3.get(20) == "goodbye") && (structure3.capacity() == 40)); 
  assert ((structure4.get(20) == "hello") && (structure4.capacity() == 44)); 
  assert ((structure5.get(1) == "greeting") && (structure5.capacity() == 2)); 
  assert ((structure6.get(12) == "hello") && (structure6.capacity() == 24));
  cout << "test_append_arr completed \n"; 
}

// question 10 tests 
void test_capitalize_all() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (3, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (1, "goodbye");
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure3.append ("another hello"); 
  structure4.append ("another goodbye");
  structure1.capitalize_all(); 
  structure2.capitalize_all(); 
  structure3.capitalize_all(); 
  structure4.capitalize_all(); 
  structure5.capitalize_all(); 
  structure6.capitalize_all(); 
  assert (structure1.to_str() == "{}"); 
  assert (structure2.to_str() == "{\"Hello\", \"Hello\", \"Hello\"}"); 
  assert (structure3.to_str() == "{\"Hello\", \"Hello\", \"Hello\", \"Another hello\"}"); 
  assert (structure4.to_str() == "{\"Goodbye\", \"Another goodbye\"}"); 
  assert (structure5.to_str() == "{\"Greeting\"}"); 
  assert (structure6.to_str() == "{\"Good morning\", \"Good afternoon\", \"Good evening\"}"); 
  cout << "test_capitalize_all completed \n"; 
}

// question 11 tests 
void test_remove_first() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (3, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (1, "goodbye");
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure3.append ("another hello"); 
  structure4.append ("another goodbye");
  structure1.remove_first(structure1.get(0));  
  structure2.remove_first(structure2.get(0)); 
  structure3.remove_first(structure3.get(0)); 
  structure3.remove_first(structure3.get(0)); 
  structure3.remove_first(structure3.get(0)); 
  structure4.remove_first(" "); 
  structure5.remove_first("greeting"); 
  structure6.remove_first("good evening"); 
  assert (structure1.to_str() == "{}"); 
  assert (structure2.to_str() == "{\"hello\", \"hello\"}"); 
  assert (structure3.to_str() == "{\"another hello\"}"); 
  assert (structure4.to_str() == "{\"goodbye\", \"another goodbye\"}"); 
  assert (structure5.to_str() == "{}"); 
  assert (structure6.to_str() == "{\"good morning\", \"good afternoon\"}"); 
  cout << "test_remove_first completed \n"; 
}

// question 12 tests
void test_keep_all_starts_with() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (3, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (1, "goodbye");
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure4.append ("another goodbye");
  structure5.append (structure2); 
  structure5.append (structure4); 
  structure6.append(structure2); 
  structure1.keep_all_starts_with('h'); 
  structure2.keep_all_starts_with('g'); 
  structure3.keep_all_starts_with('h'); 
  structure4.keep_all_starts_with('a');
  structure5.keep_all_starts_with('g'); 
  structure6.keep_all_starts_with('g');
  assert (structure1.to_str() == "{}"); 
  assert (structure2.to_str() == "{}"); 
  assert (structure3.to_str() == "{\"hello\", \"hello\", \"hello\"}"); 
  assert (structure4.to_str() == "{\"another goodbye\"}"); 
  assert (structure5.to_str() == "{\"greeting\", \"goodbye\"}"); 
  assert (structure6.to_str() == "{\"good morning\", \"good afternoon\", \"good evening\"}"); 
  cout << "test_keep_all_starts_with completed \n"; 
}

// question 13 tests 
void test_clear() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, "goodbye");
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure1.append ("hello"); 
  structure1.clear(); 
  structure2.clear(); 
  structure3.clear(); 
  structure4.clear(); 
  structure5.clear();
  structure6.clear();  
  assert((structure1.to_str() == "{}") && (structure1.size() == 0)); 
  assert((structure2.to_str() == "{}") && (structure2.size() == 0)); 
  assert((structure3.to_str() == "{}") && (structure3.size() == 0)); 
  assert((structure4.to_str() == "{}") && (structure4.size() == 0)); 
  assert((structure5.to_str() == "{}") && (structure4.size() == 0)); 
  assert((structure6.to_str() == "{}") && (structure6.size() == 0)); 
  cout << "test_clear completed \n"; 
}
void test_squish() {
  str_vec structure1 (1, 1); 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, 20);
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure3.append(structure2); 
  structure1.squish(); 
  structure2.squish(); 
  structure3.squish(); 
  structure4.squish(); 
  structure5.squish(); 
  structure6.squish(); 
  assert (structure1.capacity() == structure1.size()); 
  assert (structure2.capacity() == structure2.size()); 
  assert (structure3.capacity() == structure3.size());
  assert (structure4.capacity() == structure4.size());
  assert (structure5.capacity() == structure5.size()); 
  assert (structure6.capacity() == structure6.size()); 
  cout << "test_squish completed \n"; 
}

// question 14 tests 
void test_equal_operator(){
  str_vec structure1 (0, 1); 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, "goodbye");
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure1.append(structure2); 
  structure4.clear();
  structure4.append(structure2); 
  structure5.clear(); 
  structure5.append(structure4); 
  assert (structure1 == structure2); 
  assert (structure2 == structure3); 
  assert (structure3 == structure4);
  assert (structure4 == structure5);
  assert (structure5 == structure1); 
  assert (structure6 == structure6); 
  cout << "test_equal_operator completed \n";
}
void test_not_equal_operator() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (10, "hello"); 
  str_vec structure3 (structure2); 
  str_vec structure4 (11, 20);
  str_vec structure5 (1, "greeting"); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  assert (structure1 != structure2); 
  assert (!(structure2 != structure3)); 
  assert (structure3 != structure4);
  assert (structure4 != structure5);
  assert (structure5 != structure1); 
  assert (!(structure6 != structure6)); 
  cout << "test_not_equal_operator completed \n";
}

// question 15 tests
void test_sort() {
  str_vec structure1 (0, 1); 
  str_vec structure2 (3, "hello"); 
  str_vec structure3 (0, 1); 
  str_vec structure4 (1, "goodbye"); 
  str_vec structure5 (0, 1); 
  const char* array6[] = {"good morning", "good afternoon", "good evening"};
  str_vec structure6 (array6, 3); 
  structure3.append("hello"); 
  structure3.append("goodbye"); 
  structure3.append("greeting"); 
  structure4.append("another goodbye"); 
  structure5.append(" "); 
  structure5.append(structure4); 
  structure1.sort(); 
  structure2.sort(); 
  structure3.sort(); 
  structure4.sort(); 
  structure5.sort(); 
  structure6.sort(); 
  assert (structure1.to_str() == "{}"); 
  assert (structure2.to_str() == "{\"hello\", \"hello\", \"hello\"}"); 
  assert (structure3.to_str() == "{\"goodbye\", \"greeting\", \"hello\"}"); 
  assert (structure4.to_str() == "{\"another goodbye\", \"goodbye\"}"); 
  assert (structure5.to_str() == "{\" \", \"another goodbye\", \"goodbye\"}"); 
  assert (structure6.to_str() == "{\"good afternoon\", \"good evening\", \"good morning\"}"); 
  cout << "test_sort completed \n";
}

int main() {
  cout << "assignment 2..."; 
}