#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>

// https://github.com/triffon/sdp-2024-25-midterm-2/blob/main/G_2_F.cpp

using hist = std::unordered_map<std::string, unsigned>;

bool isWhitespace(char c){
    return c == ' ' || c == '\n' || c == '\t';
}

std::vector<std::string> words(std::string const &str){
    std::vector<std::string> result;
    std::string acc;

    for (char c : str){
        if(isWhitespace(c)){
            if(!acc.empty()){
                result.push_back(acc);
                acc.clear();
            }
        }
        else{
            acc += c;
        }
    }
    if (!acc.empty()){
        result.push_back(acc);
    }

    return result;
}

hist makeHis(std::vector<std::string> const &s){
    hist h;

    for (std::string const &w : s){
        if (h.find(w) == h.end()){
            h.insert({w, 1});
        }
        else {
            h[w]++;
        }
    }
    return h;
}

bool areAnagrams(hist const &h1, hist const &h2){
    if (h1.size() != h2.size()) return false;

    for (auto const &[key, val] : h1){
        if (h2.find(key) == h2.end()) return false;

        if (h2.at(key) != val) return false;
    }

    return true;
}

bool permuteOrCommon(std::string const &s1, std::string const &s2, std::ostream &os){
    hist h1(makeHis(words(s1))), h2(makeHis(words(s2)));

    if (areAnagrams(h1, h2)) return true;
    else {
        for (auto const &[key, _] : h1){
            if (h2.find(key) != h2.end()){
                os << key << ' ';
            }
        }
    }

    return false;
}

int main() {
    std::cout << std::boolalpha;

    std::cout << permuteOrCommon("Merry Christmas and Happy New Year", "Happy New Year and Merry Christmas", std::cout) << '\n';
    //→ true 
    
    std::cout << permuteOrCommon("Jingle bells jingle bells", "bells jingle all the way", std::cout) << '\n';
    // → jingle bells

    return 0;
}