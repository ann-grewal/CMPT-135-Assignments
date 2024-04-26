// a3.cpp

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

// a3.cpp
#include "cmpt_error.h"
#include <iostream>
#include <cassert>
#include <vector> 
#include <fstream> 
#include <algorithm>
#include "Date_base.h"
#include "Todo_item_base.h"
#include "Todo_list_base.h"
using namespace std;

class Date : public Date_base {
private:
    int day;
    int month;
    int year;  

public:
    // general constructor 
    Date (int d, int m, int y) 
    : day(d), month(m), year(y)
    {}

    // copy contructor
    Date (const Date &other)
    : day (other.day), month(other.month), year (other.year)
    {} 

    // string constructor based only on positions of "dd/mm/yyyy"
    // convert string integer using stoi function
    // extracting part of the string using the substr(start, length) method 
    Date (const string &Date_string) 
    : day (stoi(Date_string.substr(0, 2))), 
      month (stoi(Date_string.substr(3, 2))), 
      year (stoi(Date_string.substr(6, 4))) 
    {}

    // body of getters/setters
    int get_day() const {return day;}
	int get_month() const {return month;}
	int get_year() const {return year;}
	void set_day(int new_day) {day = new_day;}
    void set_month(int new_month) {month = new_month;}
    void set_year(int new_year) {year = new_year;}

    // body of = operator 
    Date &operator = (const Date &other) {

        // check for self assignment using address 
        if (this == &other) return *this; 

        // else assign 
        day = other.day; 
        month = other.month; 
        year = other.year; 
        return *this; 
	}

    // body of to_string function, returns "dd/mm/yyyy"
    // convert integer using standerd to_string function 
    string to_string() const {
        string day_string; 
        string month_string; 
        string year_string; 

        if (day < 10) day_string = "0"; 
        day_string += std::to_string(day); 
        
        if (month < 10) month_string = "0"; 
        month_string += std::to_string(month);
        
        if (year < 10) year_string = "0";
        if (year < 100) year_string += "0"; 
        if (year < 1000) year_string += "0"; 
        year_string += std::to_string(year); 

        return (day_string + "/" + month_string + "/" + year_string); 
    }
}; 

// body of < operator for Date, true if d1 earlier than d2 (opposite of bigger)
bool operator < (const Date& d1, const Date& d2) {
    if (d1.get_year() < d2.get_year()) return true; 
    if (d1.get_year() > d2.get_year()) return false; 
    if (d1.get_month() < d2.get_month()) return true; 
    if (d1.get_month() > d2.get_month()) return false; 
    if (d1.get_day() < d2.get_day()) return true; 
    return false; // greater day or equal dates 
}

class Todo_item : public Todo_item_base {
private:
    string description;
    Date due_date; 
    bool done; 
    bool not_done; 

public:
    // general constructor 
    Todo_item (string s, Date d) 
    : description(s), due_date(d), done(0), not_done(1)
    {}

    // string constructor based only on "dd/mm/yyyy! message" 
    // extracting part of the string using the substr(start, length) method 
    Todo_item (const string &Todo_string) 
    : description (Todo_string.substr (12, Todo_string.length() - 12)), 
      due_date (Todo_string.substr(0, 10))
    {
        if (Todo_string[10] == '@') {
            done = 1; 
            not_done = 0; 
        } 
        else {
            done = 0; 
            not_done = 1; 
        }
    }
    
    // body of getters and setters 
    string get_description() const {return description;}; 
    Date get_due_date() const {return due_date;}; 
	bool is_done() const {return done;}
    void set_description(const string& new_description) {
        description = new_description; 
    }
	void set_due_date(const Date& new_due_date) {
        due_date = new_due_date; 
    }
    void set_done() {
        done = 1; 
        not_done = 0; 
    }
	void set_not_done() {
        done = 0; 
        not_done = 1; 
    }

    // body of to_string functions
    string to_string() const {
        string done_symbol = "!"; 
        if (done) done_symbol = "@"; 
        return (due_date.to_string() + done_symbol + " " + description);
    }

    // body of html item function 
    string to_html_item() const {
        if (done) return "<li><del>" + due_date.to_string() + " " + description + "</del></li>"; 
        else return "<li>" + due_date.to_string() + " " + description + "</li>"; 
    }
};

// body of < operator for Todo, no description or done condition 
// defer to < operator for Date
bool operator < (const Todo_item& t1, const Todo_item& t2) {
    return (t1.get_due_date() < t2.get_due_date()); 
}

class Todo_list : public Todo_list_base {
private:
    vector <Todo_item> Todo_item_list;

public:
    // default constructor, vector constructs itself to empty 
    Todo_list() 
    {}

    // body of getters and setters, implemented using common vector methods (from cmpt 130)
    int size() const { return Todo_item_list.size();}
	Todo_item get_item(int i) const {return Todo_item_list[i];}
    void add_item (const Todo_item& item) {Todo_item_list.push_back(item);}
	void remove_item (int i) {Todo_item_list.erase(Todo_item_list.begin()+i);}

    // body of read from file, using basic c read from file procedure (from cmpt 130)
    void read_from_file(const string& filename) {

        // open file and handle faliure 
        ifstream list_file (filename);
        if (list_file.fail()) return; 

        // read in all data
        while (true) {
            // assign to string then Todo_item object then Todo_list vector
            string Todo_item_string; 
	        getline (list_file, Todo_item_string); 
            if (!Todo_item_string.empty()) Todo_item_list.push_back(Todo_item(Todo_item_string)); 

	        // check for data, already know file is open so ran out of data 
	        if (list_file.fail()) break; 
        }
        list_file.close(); 
    }
    // body of write to file, using basic c read from file procedure (from cmpt 130)
    void write_to_file(const string& filename) {

        // open file and handle failure, ofstream overwites existing 
        ofstream list_file (filename);
        if (list_file.fail()) return; 

        // sort vector using standard sort 
        sort(Todo_item_list.begin(), Todo_item_list.end()); 

        // print vector elements to file 
        for (int i = 0; i < Todo_item_list.size(); i++) {
            if (i == 0) list_file << Todo_item_list[i].to_string(); 
            else list_file << "\n" << Todo_item_list[i].to_string(); 
        } 
        list_file.close();
    }
    // body of write to html file 
    void write_to_html_file(const string& filename) {

        // open file and handle failure, ofstream overwites existing 
        ofstream list_file (filename);
        if (list_file.fail()) return; 

        // sort vector using standard sort 
        sort(Todo_item_list.begin(), Todo_item_list.end()); 

        // print vector elements to file with html formatting 
        list_file << "<ul>" << "\n"; 
        for (int i = 0; i < Todo_item_list.size(); i++) {
            if (i == 0) list_file << Todo_item_list[i].to_html_item(); 
            else list_file << "\n" << Todo_item_list[i].to_html_item(); 
        } 
        list_file << "\n" << "</ul>"; 
        list_file.close();
    }
};

void part5(string filename)  {

    // make object and its corresponding files 
    Todo_list part5; 
    part5.read_from_file(filename); 
    part5.write_to_file("final_output.txt"); 
    part5.write_to_html_file("final_output.html");  

    // count done/not done 
    int done = 0;
    int not_done = 0;
    for (int i = 0; i < part5.size(); i++) {
        if ((part5.get_item(i)).is_done()) done++; 
        else not_done++; 
    }
    cout << "done: " << done << "\n"; 
    cout << "not done: " << not_done << "\n"; 

    // print first and last, already sorted 
    cout << "oldest: "<< (part5.get_item(0)).to_string() << "\n"; 
    cout << "newest: " << (part5.get_item(part5.size() - 1)).to_string() << "\n"; 
}

// Date class tests
void step_2_1_test(){
    Date xmas(25, 12, 2018);
    cout << xmas.get_day() << " " << xmas.get_month() << " " << xmas.get_year() << "\n";
    assert(xmas.get_day() == 25);
    assert(xmas.get_month() == 12);
    assert(xmas.get_year() == 2018);
    xmas.set_year(2020);
    assert(xmas.get_day() == 25);
    assert(xmas.get_month() == 12);
    assert(xmas.get_year() == 2020);
    cout << "All step_2_1 tests passed!\n";
}
void step_2_2_test() {
    Date a(25, 12, 2018);
    Date b = a;
    assert(a.get_day() == 25);
    assert(a.get_month() == 12);
    assert(a.get_year() == 2018);
    assert(a.get_day() == b.get_day());
    assert(a.get_month() == b.get_month());
    assert(a.get_year() == b.get_year());
    b = Date(1, 1, 2019);
    a = b;
    assert(a.get_day() == 1);
    assert(a.get_month() == 1);
    assert(a.get_year() == 2019);
    assert(a.get_day() == b.get_day());
    assert(a.get_month() == b.get_month());
    assert(a.get_year() == b.get_year());
    cout << "All step_2_2 tests passed!\n";
}
void step_2_3_test() {
    Date a(25, 12, 2018);
    Date b(4, 19, 1999);
    Date c(1, 1, 0);
    assert(a.to_string() == "25/12/2018");
    assert(b.to_string() == "04/19/1999");
    assert(c.to_string() == "01/01/0000");
    cout << "All step_2_3 tests passed!\n";
}
void step_2_4_test() {
    Date a("25/12/2018");
    Date b("04/19/1999");
    Date c("01/01/0000");
    assert(a.get_day() == 25);
    assert(a.get_month() == 12);
    assert(a.get_year() == 2018);
    assert(b.get_day() == 4);
    assert(b.get_month() == 19);
    assert(b.get_year() == 1999);
    assert(c.get_day() == 1);
    assert(c.get_month() == 1);
    assert(c.get_year() == 0);
    cout << "All step_2_4 tests passed!\n";
}
void step_2_5_test() {
    Date a("01/01/0000");
    Date b("01/01/2018");
    Date c("02/01/2018");
    Date d("01/02/2018");
    assert(a < b);
    assert(a < c);
    assert(a < d);
    assert(b < c);
    assert(b < d);
    assert(c < d);
    assert(!(a < a));
    assert(!(b < a));
    cout << "All step_2_5 tests passed!\n";
}

// Todo_item class tests
void step_3_1_test() {
    Date xmas(25, 12, 2018);
    Todo_item buy_gifts("Buy gifts", xmas);
    assert(buy_gifts.get_description() == "Buy gifts");
    assert(buy_gifts.get_due_date().get_day() == xmas.get_day());
    assert(buy_gifts.get_due_date().get_month() == xmas.get_month());
    assert(buy_gifts.get_due_date().get_year() == xmas.get_year());
    assert(!buy_gifts.is_done());
    buy_gifts.set_done();
    assert(buy_gifts.is_done());
    buy_gifts.set_not_done();
    assert(!buy_gifts.is_done());
    Date earlier(20, 12, 2018);
    buy_gifts.set_due_date(earlier);
    assert(buy_gifts.get_due_date().get_day() == earlier.get_day());
    assert(buy_gifts.get_due_date().get_month() == earlier.get_month());
    assert(buy_gifts.get_due_date().get_year() == earlier.get_year());
    buy_gifts.set_description("Buy gifts for family");
    assert(buy_gifts.get_description() == "Buy gifts for family");
    cout << "All step_3_1 tests passed!\n";
}
void step_3_2_test() {
    Date xmas(25, 12, 2018);
    Todo_item buy_gifts("Buy gifts", xmas);
    assert(buy_gifts.to_string() == "25/12/2018! Buy gifts");
    buy_gifts.set_done();
    assert(buy_gifts.to_string() == "25/12/2018@ Buy gifts");
    cout << "All step_3_2 tests passed!\n";
}
void step_3_3_test() {
    Date xmas(25, 12, 2018);
    Todo_item buy_gifts("Buy gifts", xmas);
    assert(buy_gifts.to_html_item() == "<li>25/12/2018 Buy gifts</li>");
    buy_gifts.set_done();
    assert(buy_gifts.to_html_item() == "<li><del>25/12/2018 Buy gifts</del></li>");
    Date easter(21, 4, 2019);
    Todo_item weave_basket("Weave basket", easter);
    assert(weave_basket.to_html_item() == "<li>21/04/2019 Weave basket</li>");
    weave_basket.set_done();
    assert(weave_basket.to_html_item() == "<li><del>21/04/2019 Weave basket</del></li>");
    cout << "All step_3_3 tests passed!\n";
}
void step_3_4_test(){
    Date halloween(31, 10, 2018);
    Date xmas(25, 12, 2018);
    Date easter(21, 4, 2019);
    Todo_item carve_pumpkin("Carve pumpkin", halloween);
    Todo_item buy_gifts("Buy gifts", xmas);
    Todo_item weave_basket("Weave basket", easter);
    assert(carve_pumpkin < buy_gifts);
    assert(buy_gifts < weave_basket);
    assert(carve_pumpkin < weave_basket);
    assert(!(carve_pumpkin < carve_pumpkin));
    assert(!(buy_gifts < carve_pumpkin));
    assert(!(weave_basket < buy_gifts));
    assert(!(weave_basket < carve_pumpkin));
    cout << "All step_3_4 tests passed!\n";
}

void step_3_5_test() {
    Todo_item a("01/01/0000@ buy a hamster");
    assert(a.get_description() == "buy a hamster");
    assert(a.get_due_date().get_day() == 1);
    assert(a.get_due_date().get_month() == 1);
    assert(a.get_due_date().get_year() == 0);
    assert(a.is_done());
    Todo_item b("01/01/2018! sell hamster");
    assert(b.get_description() == "sell hamster");
    assert(b.get_due_date().get_day() == 1);
    assert(b.get_due_date().get_month() == 1);
    assert(b.get_due_date().get_year() == 2018);
    assert(!b.is_done());
    assert(a < b);
    assert(!(b < a));
    cout << "All step_3_5 tests passed!\n";
}

// Todo_list class tests 
void step_4_1_test() {
    Date easter(21, 4, 2018);
    Date halloween(31, 10, 2018);
    Todo_item weave_basket("Weave basket", easter);
    Todo_item carve_pumpkin("Carve pumpkin", halloween);
    Todo_list list;
    assert(list.size() == 0);
    list.add_item(weave_basket);
    assert(list.size() == 1);
    Todo_item item = list.get_item(0);
    Date date = item.get_due_date();
    assert(item.get_description() == weave_basket.get_description());
    assert(date.get_day() == weave_basket.get_due_date().get_day());
    assert(date.get_month() == weave_basket.get_due_date().get_month());
    assert(date.get_year() == weave_basket.get_due_date().get_year());
    list.add_item(carve_pumpkin);
    assert(list.size() == 2);
    list.remove_item(0);
    assert(list.size() == 1);
    item = list.get_item(0);
    date = item.get_due_date();
    assert(item.get_description() == carve_pumpkin.get_description());
    assert(date.get_day() == carve_pumpkin.get_due_date().get_day());
    assert(date.get_month() == carve_pumpkin.get_due_date().get_month());
    assert(date.get_year() == carve_pumpkin.get_due_date().get_year());
    list.remove_item(0);
    assert(list.size() == 0);
    cout << "All step_4_1 tests passed!\n";
}
void step_4_2_test() {
    Todo_list list;
    list.read_from_file("todo_example.txt");
    assert(list.size() == 11);
    // 13/02/2023! optometrist in afternoon
    Todo_item eyes("optometrist in afternoon", Date(13, 2, 2023));
    Todo_item item = list.get_item(0);
    Date date = item.get_due_date();
    assert(item.get_description() == eyes.get_description());
    assert(date.get_day() == eyes.get_due_date().get_day());
    assert(date.get_month() == eyes.get_due_date().get_month());
    assert(date.get_year() == eyes.get_due_date().get_year());
    cout << "All step_4_2 tests passed!\n";
}
void step_4_3_test() {
    Todo_list list;
    list.add_item(Todo_item("Buy tinsel", Date(20, 12, 2018)));
    list.add_item(Todo_item("21/04/2018@ Weave basket"));
    list.add_item(Todo_item("Carve pumpkin", Date(31, 10, 2018)));
    list.write_to_file("step_4_3_output.txt");
    list.write_to_html_file("step_4_3_output.html");

    // read step_4_3_output.txt back in and compare to list
    Todo_list list2;
    list2.read_from_file("step_4_3_output.txt");
    assert(list2.size() == 3);
    assert(list2.get_item(0).get_description() == "Weave basket");
    assert(list2.get_item(1).get_description() == "Carve pumpkin");
    assert(list2.get_item(2).get_description() == "Buy tinsel");
    assert(list2.get_item(0).get_due_date().get_day() == 21);
    assert(list2.get_item(0).get_due_date().get_month() == 4);
    assert(list2.get_item(0).get_due_date().get_year() == 2018);
    assert(list2.get_item(1).get_due_date().get_day() == 31);
    assert(list2.get_item(1).get_due_date().get_month() == 10);
    assert(list2.get_item(1).get_due_date().get_year() == 2018);
    assert(list2.get_item(2).get_due_date().get_day() == 20);
    assert(list2.get_item(2).get_due_date().get_month() == 12);
    assert(list2.get_item(2).get_due_date().get_year() == 2018);
    assert(list2.get_item(0).is_done() == true);
    assert(list2.get_item(1).is_done() == false);
    assert(list2.get_item(2).is_done() == false);
    cout << "All step_4_3 tests run: check the HTML results by hand!\n";
}

int main() {
    cout << "Hello from assignment 3!\n";
    step_2_1_test(); 
    step_2_2_test(); 
    step_2_3_test();
    step_2_4_test(); 
    step_2_5_test(); 
    step_3_1_test(); 
    step_3_2_test(); 
    step_3_3_test();
    step_3_4_test(); 
    step_3_5_test(); 
    step_4_1_test(); 
    step_4_2_test(); 
    step_4_3_test(); 
    part5("part5_todos.txt"); 
}