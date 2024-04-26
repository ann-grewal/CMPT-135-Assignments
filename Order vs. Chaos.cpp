// a5.cpp
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
// a5.cpp

#include <iostream>
#include <vector> 
#include <string>
#include <cstdlib>
using namespace std; 

const int WIN_STREAK = 5; 

struct space {

    // 0 x 0 to size-1 x size-1 
    int x; 
    int y; 
    char occupied_by = ' '; 

    space(int input_x, int input_y)
    : x(input_x), y(input_y)
    {}
    space(int input_x, int input_y, char character)
    : x(input_x), y(input_y), occupied_by (character)
    {}
    space()
    : x(-1), y(-1)
    {}

    char opposite() {
        if (occupied_by == 'X') return 'O'; 
        if (occupied_by == 'O') return 'X';
        return (' '); 
    }
}; 

struct board {

    int size; 
    int turns = 0; 
    int closest_streak1 = 0; 
    int closest_streak2 = 0; 
    space best_move1 = space(); 
    space best_move2 = space(); 
    vector<space> all_spaces;

    board (int s) 
    : size(s)
    {
        // arbitrarly set best moves to space in middle with character X 
        best_move1 = space (WIN_STREAK, WIN_STREAK, 'X'); 
        best_move2 = space (size-WIN_STREAK, size-WIN_STREAK, 'X');

        // set up all spaces in grid row by row, bottom to top 
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                // positions in vector corresponding to their x and y value 
                all_spaces.push_back(space(j, i));
            }
        }
    }
    int check_streak (int streak, int x, int y, char space_char, char chosen_char) {

        // continued streak
        if (chosen_char == space_char) return streak+1; 

        // broken streak, check if beat best streaks
        else if (space_char == ' ') {
            if (streak > closest_streak1) {    
                closest_streak2 = closest_streak1; 
                best_move2 = best_move1; 
                closest_streak1 = streak;  
                best_move1 = space (x, y, chosen_char); 
            }
            else if (streak > closest_streak2 && (best_move1.x != x || best_move1.y != y)) {
                closest_streak2 = streak;  
                best_move2 = space (x, y, chosen_char); 
            }
        }
        return 0; 
    }
    bool check_board (int x, int y, int chosen_char) {

        // check x column 
        int streak = 0;
        for (int i = 0; i < size; i++) {
            if (WIN_STREAK - streak > size - i) break; 
            char space_char = (all_spaces[x + i*size].occupied_by); 
            streak = check_streak (streak, x, i, space_char, chosen_char); 
            if (streak == 5) return true;
        }
        streak = 0; 
        for (int i = size-1; i >= 0; i--) {
            if ((WIN_STREAK - streak) > i) break;
            char space_char = (all_spaces[x + i*size].occupied_by); 
            streak = check_streak (streak, x, i, space_char, chosen_char);
            if (streak == 5) return true;
        } 

        // check y row 
        streak = 0; 
        for (int i = 0; i < size; i++) {
            if (WIN_STREAK - streak > size - i) break; 
            char space_char = (all_spaces[i + y*size].occupied_by); 
            streak = check_streak (streak, i, y, space_char, chosen_char);
            if (streak == 5) return true;
        }
        streak = 0; 
        for (int i = size-1; i >= 0; i--) {
            if ((WIN_STREAK - streak) > i) break;
            char space_char = (all_spaces[i + y*size].occupied_by); 
            streak = check_streak (streak, i, y, space_char, chosen_char);
            if (streak == 5) return true;
        }

        // check positive diagnol line through (x, y)
        if (WIN_STREAK - size <= (y-x) && (y-x) <= size-WIN_STREAK ){
            streak = 0; 
            for (int i = 0; i < size; i++) {
                if (WIN_STREAK - streak > size - i) break; 
                int diagnol = i + (y - x); 
                if (diagnol < 0) continue; 
                if (diagnol > size) break; 
                char space_char (all_spaces[i + diagnol*size].occupied_by); 
                streak = check_streak (streak, i, diagnol, space_char, chosen_char);
                if (streak == 5) return true;
            }
            streak = 0; 
            for (int i = size-1; i >= 0; i--) {
                if ((WIN_STREAK - streak) > i) break;
                int diagnol = i + (y - x); 
                if (diagnol > size) continue; 
                if (diagnol < 0) break; 
                char space_char (all_spaces[i + diagnol*size].occupied_by); 
                streak = check_streak (streak, i, diagnol, space_char, chosen_char);
                if (streak == 5) return true;
            }
        }

        // check negetive diagnol line through (x, y)
        if (2*size-WIN_STREAK >= (y+x) && (y+x) >= WIN_STREAK)  {
            streak = 0; 
            for (int i = 0; i < size; i++) {
                if (WIN_STREAK - streak > size - i) break; 
                int diagnol = (y + x) - i; 
                if (diagnol > size) continue; 
                if (diagnol < 0) break; 
                char space_char (all_spaces[i + diagnol*size].occupied_by); 
                streak = check_streak (streak, i, diagnol, space_char, chosen_char);
                if (streak == 5) return true;
            }
            streak = 0; 
            for (int i = size-1; i >= 0; i--) {
                if ((WIN_STREAK - streak) > i) break;
                int diagnol = (y + x) - i; 
                if (diagnol < 0) continue; 
                if (diagnol > size) break; 
                char space_char (all_spaces[i + diagnol*size].occupied_by); 
                streak = check_streak (streak, i, diagnol, space_char, chosen_char);
                if (streak == 5) return true;
            }
        }
        return false; 
    }
    int occupy_space (int x, int y, char chosen_char) {

        space* chosen_space = &(all_spaces[x + y*size]); 

        // if previously occupied space 
        if (chosen_space -> occupied_by != ' ') return -1;

        // if empty space 
        if (chosen_space -> occupied_by == ' ') {
            chosen_space -> occupied_by = chosen_char; 

            // reset if best move chosen and not at end of game 
            if (best_move1.x == x && best_move1.y == y && turns < (size*size-1)) {
                closest_streak1 = closest_streak2;
                best_move1 = best_move2; 

                closest_streak2 = -1; 
                best_move2 = space(); 
            }
            if (best_move2.x == x && best_move2.y == y && turns < (size*size-2)) {
               closest_streak2 = -1; 
               best_move2 = space(); 
            }

            // check how close to winning 
            bool win_check = check_board(x, y, chosen_char); 

            // best_move1 must have a valid value until one move before chaos wins 
            while (best_move1.x == -1 && turns < (size*size-1) ) {
                
                // set to next empty space 
                for (space s: all_spaces) {
                    if (s.occupied_by == ' ') {
                        best_move1 = s; 
                        best_move1.occupied_by = chosen_char; 
                        break; 
                    }
                }
                closest_streak1 = -1; 
                break; 
            }

            // best_move1 must have a valid valud until two moves before chaos wins 
            while (best_move2.x == -1 && turns < (size*size-2) ) {

                // set to next empty space
                for (space s: all_spaces) {
                    if (s.occupied_by == ' ' && (s.x != best_move1.x) && (s.y != best_move1.y)) {
                        best_move2 = s; 
                        best_move2.occupied_by = chosen_char; 
                        break; 
                    }
                }
                closest_streak2 = -1; 
                break; 
            }

            // best_moves cannot end up with the same x and y coordinates
            bool same_moves = (best_move1.x == best_move2.x && best_move1.y == best_move2.y);
            if (same_moves && turns < (size*size-2) ) {

                // set to next empty space
                for (space s: all_spaces) {
                    if (s.occupied_by == ' ' && (s.x != best_move1.x) && (s.y != best_move1.y)) {
                        best_move2 = s; 
                        best_move2.occupied_by = chosen_char; 
                        break; 
                    }
                }
            }   

            // display round results 
            draw_board(); 
            if (win_check) return 1;  
        }
        return 0; 
    }
    int play_best(string team) {

        // play best move
        int result = -1; 
        if (team == "order") {
            result =  occupy_space (best_move1.x, best_move1.y, best_move1.occupied_by);
        } else {
            result = occupy_space (best_move1.x, best_move1.y, best_move1.opposite()); 
        }

        // fail safe so computer always has a move 
        if (result == -1) {
            for (space s: all_spaces) {
                if (s.occupied_by == ' ') {
                    result = occupy_space(s.x, s.y, 'X'); 
                    break; 
                }
            }
        }
        return result; 
    }
    void draw_board () {

        cout << "\n"; 
        for (int i = size-1; i >= 0; i--) {
            
            // y axis labels
            char y_letter = 97 + i; 
            cout << y_letter << "   ";

            // board
            for (int j = 0; j < size; j++) {
                cout << all_spaces[j + i*size].occupied_by << " "; 
            }
            cout << "\n"; 
        }

        // x axis labels 
        cout << "\n    "; 
        for (int i = 0; i < size; i++) {
            cout << i+1 << " "; 
        }
        cout << "\n\n"; 
    }
}; 

int user_setup(); 
string user_input(string message); 
bool computer_play (board* game_board, string team); 
bool user_play (board* game_board); 
bool user_end (string game_action); 

int main() {
    bool game_play = true;
    srand(time(nullptr));

    while (game_play) {

        // set up board 
        int size = user_setup(); 
        board game_board = board(size); 
        game_board.draw_board(); 

        // set up round 
        int version = rand() % 3;
        bool order_win = false; 

        if (version <= 1 ) {
            
            // user order 
            cout << "user is Order, computer is Chaos, ";  

            // user starts 
            if (version == 0) {
                cout << "user starts \n\n"; 
                while (true) {
                    game_play = user_end("game round");
                    if (!game_play) break;  
                    order_win = user_play(&game_board); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                    order_win = computer_play(&game_board, "chaos"); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                }
            }
            
            // computer starts 
            if (version == 1) {
                cout << "computer starts \n\n"; 
                while (true) {
                    game_play = user_end("game round");
                    if (!game_play) break; 
                    order_win = computer_play(&game_board, "chaos"); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                    order_win = user_play(&game_board); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                }
            }

            // game result 
            if (order_win) cout << "user won as Order, computer lost!\n\n"; 
            if (game_board.turns >= size*size) cout << "computer won as Chaos, user lost!\n\n"; 
            if (!game_play) cout << "computer won as Chaos, user lost!\n\n";
            game_play = user_end("game"); 
        }
        else {

            // computer is chaos
            cout << "computer is Order, user is Chaos, ";  

            // user starts 
            if (version == 2) {
                cout << "user starts\n\n"; 
                while (true) {
                    game_play = user_end("game round");
                    if (!game_play) break; 
                    order_win = user_play(&game_board); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                    order_win = computer_play(&game_board, "order"); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                }
            }

            // computer starts 
            if (version ==3) {
                cout << "computer starts\n\n"; 
                while (true) {
                    game_play = user_end("game round"); 
                    if (!game_play) break; 
                    order_win = computer_play(&game_board, "order"); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                    order_win = user_play(&game_board); 
                    if (order_win) break; 
                    game_board.turns++; 
                    if (game_board.turns == size*size) break; 
                }
            }
            
            // game result 
            if (order_win) cout << "computer won as Order, user lost!\n\n"; 
            if (game_board.turns >= size*size) cout << "user won as Chaos, computer lost!\n\n";
            if (!game_play) cout << "computer won as Order, user lost!\n\n"; 
            game_play = user_end("game"); ; 
        }
    }
}
string user_input(string message) {

    // collect user input as string to avoid errors 
    string input; 
    cout << message; 
    cin >> input; 
    return input; 
}
int user_setup() {
    
    // instructions 
    cout << "ORDER VERSUS CHAOS \n"
        << "starting move randomly assigned to player or computer \n" 
        << "Order or Chaos randomly assigned to player or computer \n\n"
        << "if Order try to insert Xs or Os in a row of 5 on grid \n" 
        << "if Chaos try to insert Xs or Os to block Order on grid \n \n"; 
    
    // set grid 
    int size = 0;   
    string size_string; 
    string message = "enter size of perfect square grid to play on (valid sizes 6, 7, 8, 9): ";
    while (size_string != "6" && size_string != "7"&& size_string != "8" && size_string != "9"){
        size_string = user_input (message);
    }
    size = stoi(size_string); 
    return size; 
}
bool user_end(string game_action) {

    // check for valid data by string
    int end = -1; 
    string end_string; 
    string first_message = "enter 0 to exit " + game_action; 
    string second_message = " completely, enter 1 to continue to next " + game_action + ": ";
    while (end_string != "0" && end_string != "1") {
        end_string = user_input (first_message + second_message);
    }
    
    // convert to integer once verified 
    end = stoi(end_string); 
    cout << "\n"; 
    return end; 
}
bool user_play(board* game_board) {
    
    cout << "user move \n"; 
    int move = -1; 

    // repeatedly ask for move until valid move inputed 
    while (move == -1) {

        string y_string; 
        char y_char = ' '; 
        int y = -1; 
        while (y < 0 || y > (game_board->size-1)){
            y_string = user_input ("enter row (letter): ");
            if (y_string.size() == 1) y_char = y_string[0];  
            y = y_char-97;
        }
       
        string x_string; 
        char x_char = ' '; 
        int x = -1; 
        while (x < 0 || x > (game_board -> size-1)) {
            x_string = user_input ("enter column (number): ");
            if (x_string.size() == 1) x_char = x_string[0]; 
            x = x_char-49;  
        }
 
        string character_string; 
        char character = ' ';
        while (character != 'X' && character != 'O') {
            character_string = user_input("enter X or O character: "); 
            if (character_string.size() == 1) character = character_string[0];   
        }
        move = game_board->occupy_space(x, y, character); 
    }
    
    // result
    if (move == 1) return true; 
    return false; 
}
bool computer_play (board* game_board, string team) {

    // computer always plays best move 
    cout << "computer move \n"; 
    int move = game_board-> play_best(team); 

    // result 
    if (move == 1) return true; 
    return false; 
}

// report  
/*    
    computer strategy: 
        Each time a player makes a move (user or computer), its horizontal, verticle, and 
        diagnol lines are checked for a win and to track the two longest streaks (continuous 
        lines of Xs or Os) thus far. The spaces to extend those longest streaks become the 
        positions for the next best moves. If the computer is Order, it plays the best move. 
        If the computer is Chaos, it blocks the best move with the opposite symbol. When the 
        game progresses to a point where there are no obvious best moves, then the first open
        space (from left row a) is assigned to the best move so the computer can still take its 
        turn. The comptuer plays better than random moves.

    extra features: 
        All of the user input is collected into a string variable and then checked for 
        valid values, so the program does not loop infinetly or crash when the wrong variable 
        type is inputed by the user. 

    limitations:
        The computer plays the best move compared to the last saved best_moves and the last 
        played move. Since it does not recheck every line in every direction, it may not play 
        the best overall move possible but it is still a logical next move (better than random). 

    citations: 
        Desmos graphing calculator was used to model the lines needed to be checked for a space. 
        
*/