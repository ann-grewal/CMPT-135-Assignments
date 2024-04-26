// a4.cpp

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

// a4.cpp

#include "a4.h"  
using namespace std;

// no main in file, only implmentations of a4.h 

int sum_of_squares(int n) {
    // edge cases 
    assert (n >= 0); 
    if (n == 0) return 0; 
    // base case 
    if (n == 1) return 1; 
    // recursive case 
    return n*n + (sum_of_squares (n - 1)); 
}
void sum_of_squares_test() {
    assert (sum_of_squares(0) == 0); 
    assert (sum_of_squares(1) == 1); 
    assert (sum_of_squares(2) == 5); 
    assert (sum_of_squares(3) == 14); 
    assert (sum_of_squares(4) == 30); 
    assert (sum_of_squares(5) == 55); 
    cout << "sum_of_squares_test() complete" << "\n"; 
}

int strange_seq(int n) {
    // edge case
    assert (n > 0); 
    // base case
    if (n == 1) return 3; 
    // recursive case
    return 2*(strange_seq(n - 1)) + 1; 
}
void strange_seq_test() {
    assert (strange_seq(1) == 3); 
    assert (strange_seq(2) == 7); 
    assert (strange_seq(3) == 15); 
    assert (strange_seq(4) == 31); 
    assert (strange_seq(5) == 63); 
    assert (strange_seq(6) == 127); 
    cout << "strange_seq_test() complete" << "\n"; 
}

bool is_ternary(const string& s) {
    // edge case
    if (s.empty()) return true; 
    // condition 
    bool ternary_condition = (s[0] == '0' || s[0] == '1' || s[0] == '2'); 
    // base case
    if (s.size() == 1 && ternary_condition) return true; 
    // recursive case 
    if (ternary_condition) return is_ternary(s.substr(1, s.size()-1)); 
    return false;
}
void is_ternary_test() {
    assert (is_ternary("")); 
    assert (is_ternary("0"));
    assert (is_ternary("1")); 
    assert (is_ternary("2011120")); 
    assert (is_ternary("00002222")); 
    assert (!is_ternary(" ")); 
    assert (!is_ternary("o"));
    assert (!is_ternary(" 2"));
    assert (!is_ternary("x"));
    assert (!is_ternary("2011 120"));
    assert (!is_ternary("2 1 0")); 
    cout << "is_ternary_test() complete" << "\n"; 
}

// check string backwards so (-) is in base case 
bool is_int(const string& s) {
    // edge case
    if (s.empty()) return false;
    // condition 
    bool is_digit = 
    (  s[s.size()-1] == '0' || s[s.size()-1] == '1' || s[s.size()-1] == '2' || s[s.size()-1] == '3' || s[s.size()-1] == '4' 
    || s[s.size()-1] == '5' || s[s.size()-1] == '6' || s[s.size()-1] == '7' || s[s.size()-1] == '8' || s[s.size()-1] == '9'  ); 
    // base cases
    if (s.size() == 2 && is_digit && s[0] == '-') return true; 
    if (s.size() == 1 && is_digit) return true; 
    // recursive case 
    if (is_digit) return is_int(s.substr(0, s.size()-1)); 
    return false;
}
void is_int_test() {
    assert (is_int("911"));
    assert (is_int("-23"));
    assert (is_int("0"));
    assert (is_int("-007"));
    assert (is_int("19346"));
    assert (is_int("3212"));
    assert (is_int("-3212")); 
    assert (!is_int(""));
    assert (!is_int("-"));
    assert (!is_int("--"));
    assert (!is_int("0 "));
    assert (!is_int(" 911"));
    assert (!is_int(" 24e5"));
    assert (!is_int("782 2"));
    assert (!is_int("+32"));
    assert (!is_int("3.14"));
    cout << "is_int() complete" << "\n"; 
}

string strip(const string& s) {
    // edge case
    if (s.size() == 0) return ""; 
    if (s.size() == 1 && s[0] == ' ') return ""; 
    // recursive cases 
    if (s[0] == ' ') return strip(s.substr(1, s.size()-1)); 
    if (s[s.size() - 1 ] == ' ') return strip(s.substr(0, s.size()-1)); 
    // base case
    return s; 
}
void strip_test() {
    assert (strip("  ab c  d ") == "ab c  d");
    assert (strip(" abcd") == "abcd");
    assert (strip("abcd " ) == "abcd");
    assert (strip("abc d") == "abc d");  
    assert (strip(" a b c d ") == "a b c d"); 
    assert (strip(" ab ") == "ab");
    assert (strip("") == ""); 
    assert (strip(" ") == ""); 
    assert (strip("      ") == ""); 
    cout << "strip_test() complete" << "\n";
}

int sum_neg(const vector<int> &v) {
    // edge case
    if (v.empty()) return 0; 
    // condition to save negetive values 
    int neg = 0; 
    if (v[v.size()-1] < 0) neg = v[v.size()-1]; 
    // base case
    if (v.size() == 1) return neg; 
    // recursive case
    vector<int> copy_v = v; 
    copy_v.pop_back(); 
    return neg + sum_neg(copy_v); 
}
void sum_neg_test() {
    vector<int> vec_1; 
    vector<int> vec_2 = {1, 2, 3, 4, 5, 6, 7, 8,9};
    vector<int> vec_3 = {-1, -2, -3, -4, -5};
    vector<int> vec_4 = {1, -2, -3, 4, 5,};
    vector<int> vec_5 = {-1, 1};
    vector<int> vec_6 = {-9}; 
    vector<int> vec_7 = {-10, -11, -12}; 
    assert (sum_neg(vec_1) == 0); 
    assert (sum_neg(vec_2) == 0); 
    assert (sum_neg(vec_3) == -15); 
    assert (sum_neg(vec_4) == -5); 
    assert (sum_neg(vec_5) == -1); 
    assert (sum_neg(vec_6) == -9); 
    assert (sum_neg(vec_7) == -33);
    cout << "sum_neg_test() complete" << "\n"; 
}
vector<int> max_vec(const vector<int>& a, const vector<int>& b) {
    // conditions to start 
    int size = a.size(); 
    assert (size == b.size() && size > 0); 
    vector <int> max; 
    // recursive case, remove last element 
    if (a.size() != 1) {
        vector<int> copy_a = a; 
        copy_a.pop_back(); 
        vector<int> copy_b = b;
        copy_b.pop_back(); 
        max = max_vec(copy_a, copy_b);
    }
    // in all cases, add max last element to vector 
    if (a[size-1] > b[size-1]) max.push_back(a[size-1]);
    else max.push_back(b[size-1]);
    return max; 
}
void max_vec_test() {
    vector<int> vec_1 = {3, 4, 1}; 
    vector<int> vec_2 = {2, 5, 2}; 
    vector<int> vec_3 = vec_2; 
    vector<int> vec_4 = {10, 1, 2};
    vector<int> vec_5 = {1}; 
    vector<int> vec_6 = {2}; 
    vector<int> vec_7 = {10, 11, 12, 13, 14, 15}; 
    vector<int> vec_8 = {0, 1, 2, 3, 4, 5}; 
    vector<int> answer1 = {3, 5, 2}; 
    vector<int> answer2 = {2, 5, 2}; 
    vector<int> answer3 = {10, 4, 2}; 
    vector<int> answer4 = {10, 5, 2}; 
    vector<int> answer5 = {2}; 
    vector<int> answer6 = vec_7; 
    assert (max_vec(vec_1, vec_2) == answer1); 
    assert (max_vec(vec_2, vec_3) == answer2); 
    assert (max_vec(vec_1, vec_4) == answer3); 
    assert (max_vec(vec_2, vec_4) == answer4); 
    assert (max_vec(vec_5, vec_6) == answer5);
    assert (max_vec(vec_7, vec_8) == answer6); 
    cout << "max_vec_test() complete" << "\n"; 
}

int count(const vector<string>& v, const string& s) {
    // base case 
    if (v.empty()) return 0; 
    // recursive case
    vector<string> copy_v = v; 
    copy_v.pop_back(); 
    int count_s = count(copy_v, s); 
    if (v[v.size()-1] == s) count_s++;
    return count_s;    
}
void count_test() {
    vector<string> vec_1 = {}; 
    vector<string> vec_2 = {""}; 
    vector<string> vec_3 = {"a", "a", "a", "a"}; 
    vector<string> vec_4 = {"a", "a", "b"}; 
    vector<string> vec_5 = {"b", "b", "a", "b"}; 
    vector<string> vec_6 = {"b", "b"}; 
    vector<string> vec_7 = {" ", "", "", "a", "", "a", " ", " "};  
    assert (count(vec_1, "a") == 0); 
    assert (count(vec_2, "a") == 0); 
    assert (count (vec_2, "") == 1); 
    assert (count(vec_3, "a") == 4); 
    assert (count(vec_3, "b") == 0); 
    assert (count(vec_3, "") == 0); 
    assert (count(vec_4, "a") == 2); 
    assert (count(vec_4, "b") == 1); 
    assert (count(vec_5, " ") == 0); 
    assert (count(vec_5, "a") == 1); 
    assert (count(vec_5, "b") == 3); 
    assert (count(vec_6, "a") == 0);
    assert (count(vec_6, "b") == 2); 
    assert (count(vec_7, "a") == 2);
    assert (count(vec_7, "") == 3); 
    assert (count(vec_7, " ") == 3);  
    cout << "count_test() complete" << "\n";
}
 
vector<string> zip(const string& s, const string& t){
    // condition to start 
    int size = s.size(); 
    assert (size == t.size());
    vector<string> zip_vec;  
    // edge case
    if (s.empty()) return zip_vec; 
    // recurisive case 
    if (size != 1) zip_vec = zip (s.substr(0, size-1), t.substr(0, size-1)); 
    // all cases 
    zip_vec.push_back(s.substr(size-1, 1)+ t.substr(size-1, 1)); 
    return zip_vec; 
}

void zip_test(){
    string string_1 = "abc"; 
    string string_2 = "def"; 
    string string_3 = ""; 
    string string_4 = string_3; 
    string string_5 = "---"; 
    string string_6 = "123456";  
    vector<string> answer_1 = {"ad", "be", "cf"}; 
    vector<string> answer_2 = {"ad", "be", "cf", "da", "eb", "fc"}; 
    vector<string> answer_3 = {}; 
    vector<string> answer_4 = {"a-", "b-", "c-"}; 
    vector<string> answer_5 = {"--", "--", "--"}; 
    vector<string> answer_6 = {"1a", "2b", "3c", "4d", "5e", "6f"}; 
    assert (zip(string_1, string_2) == answer_1); 
    assert (zip(string_1 + string_2, string_2 + string_1) == answer_2); 
    assert (zip(string_3, string_4) == answer_3); 
    assert (zip(string_1, string_5) == answer_4); 
    assert (zip(string_5, string_5) == answer_5); 
    assert (zip(string_6, string_1 + string_2) == answer_6); 
    cout << "zip_test() complete" << "\n"; 
}

string join(const vector<string>& v, const string& sep) {
    // edge case
    if (v.empty()) return ""; 
    // base case
    if (v.size() == 1) return v[v.size()-1]; 
    // recursive case 
    vector<string> copy_v = v; 
    copy_v.pop_back(); 
    string joined = join(copy_v, sep) + sep;
    joined += v[v.size()-1]; 
    return joined; 
}
void join_test(){
    vector<string> vec_1 = {"hello"}; 
    vector<string> vec_2 = {"hello", "world"}; 
    vector<string> vec_3 = {"", "hello", "world"}; 
    vector<string> vec_4 = {"hello", "world", "!"};
    assert (join(vec_1, ", ") == "hello"); 
    assert (join(vec_2, ", ") == "hello, world");
    assert (join(vec_2, "--seperated--") == "hello--seperated--world"); 
    assert (join(vec_3, "-") == "-hello-world"); 
    assert (join(vec_3, "") == "helloworld"); 
    assert (join(vec_4, ", ") == "hello, world, !");
    assert (join(vec_4, " ") == "hello world !"); 
    assert (join(vec_4, vec_3[0]) == "helloworld!");  
    cout << "join_test() complete" << "\n"; 
}