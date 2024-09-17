#include <iostream>
#include <string>
using namespace std ; 

bool is_digit(const char& input_char){ 
    if(input_char - '0' >= 0 && input_char - '0' < 10){
        return true ;
    }
    return false ; 
}
bool is_small_alphabet(const char& input_char){ 
    if(input_char - 'a' >= 0 && input_char - 'a' < 26){
        return true ;
    }
    return false ; 
}

bool is_capital_alphabet(const char& input_char){ 
    if(input_char - 'A' >= 0 && input_char - 'Z' < 26){
        return true ;
    }
    return false ; 
}

bool is_underscore(const char& input_char){ 
    if(input_char == '_'){
        return true ;
    }
    return false ; 
}

bool is_aplha_numeric(const char& input_char){
    if(is_digit(input_char) || is_small_alphabet(input_char) || is_capital_alphabet(input_char) || is_underscore(input_char)){
        return true ;
    }
    return false ; 
}

bool match_pattern(const string& input_line, const string& pattern) {
    // identifly the pattern expected 
    int input_ctr = 0 ; 
    int pattern_ctr = 0 ;
    while(pattern_ctr < pattern.size()){
        if(pattern[pattern_ctr] == '\\'){
            if(pattern[pattern_ctr+1] == 'd'){
                if(!is_digit(input_line[input_ctr])){
                    return false ; 
                }else{
                    while(++input_ctr < input_line.size() && is_digit(input_line[input_ctr])){}
                }
            }
            else if(pattern[pattern_ctr+1] == 'w'){
                if(!is_aplha_numeric(input_line[input_ctr])){
                    return false ; 
                }else{
                    while(++input_ctr < input_line.size() && is_aplha_numeric(input_line[input_ctr])){
                    }
                }
            }
            pattern_ctr += 2 ; 
        }
        else{
            if(input_line[input_ctr] != pattern[pattern_ctr]){
                return false ;
            }
            input_ctr ++ ; 
            pattern_ctr ++ ; 
        }
    }
    return true ; 
}

int main(int argc, char* argv[]) {
    cout << unitbuf;
    cerr << unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    cout << "Logs from your program will appear here" << endl;

    if (argc != 3) {
        cerr << "Expected two arguments" << endl;
        return 1;
    }

    string flag = argv[1];
    string pattern = argv[2];

    if (flag != "-E") {
        cerr << "Expected first argument to be '-E'" << endl;
        return 1;
    }

    
    string input_line;
    getline(cin, input_line);
    
    try {
        if (match_pattern(input_line, pattern)) {
            cout << "pattern found" ; 
            return 0;
        } else {
            cout << "pattern NOT found" ; 
            return 1;
        }
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
}
