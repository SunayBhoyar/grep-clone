#include <iostream>
#include <string>
#include <set>
#include <vector>

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
    bool case_failed = false ; 

    while(pattern_ctr < pattern.size()){
        if(input_ctr  == input_line.size()){
            if(pattern[pattern_ctr] == '$'){
                return true ;
            }
            return false ;
        }
        if(pattern[pattern_ctr] == '\\'){
            if(pattern[pattern_ctr+1] == 'd'){
                if(!is_digit(input_line[input_ctr])){
                    if(pattern_ctr != 0){ 
                        case_failed = true ; 
                    }
                    pattern_ctr = -2 ;
                }
            }
            else if(pattern[pattern_ctr+1] == 'w'){
                if(!is_aplha_numeric(input_line[input_ctr])){
                    if(pattern_ctr != 0){ 
                        case_failed = true ; 
                    }
                    pattern_ctr = -2 ; 
                }
            }
            pattern_ctr += 2 ; 
        }
        else if(pattern[pattern_ctr] == '['){
            pattern_ctr ++ ; 
            set<char> given_set ; 
            bool posative = true ; 
            int times_inc_pattern_ctr = 2 ; 
            while(pattern[pattern_ctr] != ']' && pattern_ctr < pattern.size()){
                if(pattern[pattern_ctr] == '^'){
                    posative = false ;
                }else{
                    given_set.insert(pattern[pattern_ctr]) ; 
                }
                pattern_ctr ++ ;
                times_inc_pattern_ctr ++ ; 
            }
            if(posative){
                if(given_set.find(input_line[input_ctr]) == given_set.end()){
                    if(pattern_ctr > times_inc_pattern_ctr){ 
                        case_failed = true ; 
                    }
                    pattern_ctr -= times_inc_pattern_ctr ; 
                }
            }else{
                if(given_set.find(input_line[input_ctr]) != given_set.end()){
                    if(pattern_ctr > times_inc_pattern_ctr){ 
                        case_failed = true ; 
                    }
                    pattern_ctr -= times_inc_pattern_ctr  ; 
                }
            }
            pattern_ctr ++ ; 
        }
        else if(pattern[pattern_ctr] == '('){
            pattern_ctr ++ ;
            vector<string> option_of_patterns ; 
            option_of_patterns.push_back("");
            int option_of_patterns_ctr = 0 ;
            while(pattern[pattern_ctr]!= ')' && pattern_ctr < pattern.size()){
                if(pattern[pattern_ctr] != '|'){
                    option_of_patterns[option_of_patterns_ctr] += pattern[pattern_ctr] ; 
                }else{
                    option_of_patterns.push_back("");
                    option_of_patterns_ctr ++ ;
                }
                pattern_ctr ++ ; 
            }
            string given_word = "" ; 
            while(input_ctr < input_line.size() && input_line[input_ctr] != ' ' ){
                given_word += input_line[input_ctr] ;
                input_ctr ++ ;
            }
            input_ctr -- ;
            pattern_ctr ++ ; 
            bool pattern_matched = false ; 
            for (int i = 0 ; i < option_of_patterns.size() ;i ++){
                if(option_of_patterns[i] == given_word){
                    pattern_matched = true ; 
                }
            }
            if(!pattern_matched){
                return false ; 
            }
        }
        else if (pattern[pattern_ctr] == '^'){
            if(input_line[input_ctr] != pattern[pattern_ctr+1]){
                return false ; 
            }
            pattern_ctr += 2 ; 
        }
        else if (pattern[pattern_ctr] == '$'){
            if(input_line[input_ctr+1] == ' '){
                return true ; 
            } else{
                pattern_ctr = 0 ; 
            }
        }
        else if (pattern[pattern_ctr] == '+' || pattern[pattern_ctr] == '?'){
            char last_char = pattern[pattern_ctr-1] ;
            while(1){
                if(input_line[input_ctr] == last_char){
                    input_ctr ++ ; 
                }else{ 
                    input_ctr -- ;
                    break ; 
                }
            }
            pattern_ctr ++ ; 
        }
        else if (pattern[pattern_ctr] == '.' ){
            pattern_ctr ++ ; 
        }
        else{
            if(input_line[input_ctr] != pattern[pattern_ctr]){
                if(pattern[pattern_ctr+1] == '?'){
                    input_ctr -- ; 
                }else{
                    if(pattern_ctr != 0){ 
                        case_failed = true ; 
                    }
                    pattern_ctr = -1 ; 
                }
            }
            pattern_ctr ++ ; 
        }
        if(!case_failed){
            input_ctr ++ ; 
        }
        case_failed = false ; 
        
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
