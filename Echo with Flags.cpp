// myecho.cpp

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

// myecho.cpp

#include <iostream>   
#include <vector>     
#include <string>      
#include <algorithm>   
#include <cassert>     
using namespace std;

string quote (string inputed_string); 
void test_quote(); 
string to_string (const vector <string> &v); 
void test_to_string(); 
void help_flag_function();  
void unknown_flag_function (const string &unknown_flag); 
void runtest_flag_function (bool other_flags); 

int main(int argc, char *argv[]) { 

    int argument_current = 1; 

    // handle possible flag argument (after name)
    if (argv[argument_current]) {
        
        string flag_argument = argv[1]; 
        bool help_flag = false; 
        bool quote_flag = false; 
        bool space_flag = false; 
        bool reverse_flag = false; 
        bool other_character = false; 

        if (flag_argument[0] == '-') { 

            argument_current++; 

            // check for runtest flag
            string runtests_name = "runtests"; 

            // .find function from string library finds specified substring in string
            // from cmpt 130 with dr. brian fraser @ simon fraser university 
            int runtests_location = flag_argument.find (runtests_name);

            // question 9 - handle multiple single flags 
            for (int i = 1; i < flag_argument.length(); i++) {

                // ensure that the 'r' and 's' characters are not those belonging to "runtests"
                // get i to skip over anything in "runtest"
                if (runtests_location == i) {
                    i += runtests_name.length(); 
                }

                if (flag_argument[i] == 'h') help_flag = true;
                else if (flag_argument[i] == 'q') quote_flag = true; 
                else if (flag_argument[i] == 's') space_flag = true;
                else if (flag_argument[i] == 'r') reverse_flag = true;
                else other_character = true; 
            }
        
            bool single_flags = help_flag || quote_flag || space_flag || reverse_flag; 
            
            // checkpoint that some valid flag exits and is not muddled with additional characters 
            // fatal error checking problem missed one bracket 
            if (other_character ||(!single_flags && runtests_location == -1)) unknown_flag_function(flag_argument);

            // handle runtest function 
            if (runtests_location != -1) runtest_flag_function (single_flags); 

            // handle help flag if called 
            if (help_flag) help_flag_function(); 
        }   
    
        // handle how other single flags change argument output 
        string arguments_output; 

        // question 7 - add spacing 
        string spacing = " "; 
        if (space_flag) spacing = "";

        // question 8 - add reversing 
        // ensure some argument exists after flag 
        if (argv[argument_current]) {

            // load output according to reverse flag 
            // add first argument string seperately so no extra spaces 
            if (reverse_flag) {
                arguments_output += argv[argc-1]; 
                for (int i = argc-2; i >= argument_current; i--) {
                    arguments_output += spacing; 
                    arguments_output += argv[i]; 
                }
            } else {
                arguments_output += argv[argument_current]; 
                for (int i = argument_current+1; i < argc; i++) {
                    arguments_output += spacing; 
                    arguments_output += argv[i]; 
                }
            } 
        }
        // question 6 - add quotes 
        if (quote_flag) arguments_output = "\"" + arguments_output + "\""; 

        // question 3 - print arguments 
        cout << arguments_output;
    }
    // just for spacing output 
    cout << "\n\n"; 
}

// question 1 - function 
string quote (string inputed_string) {

    // handle strings with only one character (no space for double quotes)
    if (inputed_string.length() == 1) {
        return "\"" + inputed_string + "\""; 
    }

    // handle strings that do not start and end with quotes  
    else if (inputed_string [0] != '\"' || inputed_string [inputed_string.length()-1] != '\"') { 
        return "\"" + inputed_string + "\""; 
    }

    // if quotes in correct place 
    else {
        return inputed_string; 
    } 
}

// question 1 - test 
void test_quote () {
    
    cout << "testing quote ... ";
    assert(quote("quote1") == "\"quote1\"");
    assert(quote("\"quote2") == "\"\"quote2\"");
    assert(quote("\"\"quote3\"") == "\"\"quote3\""   );
    assert(quote("\"quote4\"") == "\"quote4\"");
    assert(quote("quote5\"quote5") == "\"quote5\"quote5\"");
    assert(quote("\"quote6") == "\"\"quote6\"");
    assert(quote("quote7\"") == "\"quote7\"\"");
    assert(quote("") == "\"\"");
    assert(quote("\"") == "\"\"\"");
    cout << "all tests passed\n";
}

// question 2 - function 
string to_string (const vector <string> &v){

    string vector_string  = "{"; 

    if (!v.empty()) {
        for (int i = 0; i < v.size()- 1; i++) {
            vector_string += "\"" + v[i] + "\"" + ", ";
        }
        vector_string += "\"" + v[v.size()-1] + "\""; 
    }

    vector_string += "}"; 
    return vector_string; 
}

// question 2 - test 
void test_to_string () {

    cout << "testing to string ... " ; 
    vector <string> vector1 = {"string1.1", "string1.2", "string1.3"}; 
    assert (to_string (vector1) == "{\"string1.1\", \"string1.2\", \"string1.3\"}"); 
    vector <string> vector2 = {}; 
    assert (to_string (vector2) == "{}"); 
    vector <string> vector3 = {"string3.1"};
    assert (to_string(vector3) == "{\"string3.1\"}"); 
    vector <string> vector4 = {"\""}; 
    assert (to_string(vector4) == "{\"\"\"}"); 
    cout << "all tests passed \n"; 
}

// question 4 - help flag function 
// can be called from wrong flag input or -h flag 
void help_flag_function() {

    cout << "\nUsage: ./myecho [-runtests|-(hrs)] [string ...]"; 
    cout << "\n -runtests: run the tests"; 
    cout << "\n            over-rides single-character flags"; 
    cout << "\n        -h: print this help message"; 
    cout << "\n           over-rides other single-character flags";
    cout << "\n        -r: print the strings in reverse order"; 
    cout << "\n        -s: no space between arguments"; 
    cout << "\n        -q: quote the printed results"; 
    cout << "\n  -rs, -sr: no space between arguments, in reverse order";
    cout << "\n"; 
    cout << "\n Repeated single-character flags are allowed (and are ignored)."; 
    cout << "\n Unknown flags cause an error."; 
    cout << "\n\n"; 
    cout << "\nExamples:";
    cout << "\n  >./myecho -q"; 
    cout << "\n  \"\""; 
    cout << "\n  >./myecho x y z"; 
    cout << "\n  x y z"; 
    cout << "\n  >./myecho -q x y z"; 
    cout << "\n  \"x y z\""; 
    cout << "\n  >./myecho -sr x y z";
    cout << "\n  zyx"; 
    cout << "\n  ./myecho -h"; 
    cout << "\n\n"; 

    // crashes program and sends exit failure to operating system
    // from cmpt 130 with dr. brian fraser @ simon fraser university 
    exit (EXIT_FAILURE); 
}

// if unknown flag
void unknown_flag_function (const string &unknown_flag) {

    cout << "Error, unknown flag: " << unknown_flag << "\n"; 
    help_flag_function(); 
}

// question 5 - runtest function 
void runtest_flag_function (bool other_flags) { 

    if (other_flags) {
        cout << "Error, invalid flag: u \n"; 
        help_flag_function(); 
     
    } else {
        test_quote(); 
        test_to_string();
    }
}
