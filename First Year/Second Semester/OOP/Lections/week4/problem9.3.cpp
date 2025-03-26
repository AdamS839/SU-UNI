#include <iostream>
#include <cstring>
#include <algorithm>

const int max_words = 500;

struct Entry{
    char word[100];
    char meaning[500];
};

class Dictionary{
    Entry entries[max_words];
    int count;
public:
    Dictionary() : count(0) {}

    void printAllEntries(){
        for (int i = 0; i < count; ++i)
        {
            std::cout << entries->word[i] << " - " << entries->meaning[i] << std::endl;
        }
    }

    void addNewEntry(const char* a_word, const char* a_meaning){
        if(count >= max_words){
            std::cout << "Full dictionary" << std::endl;
            return;
        }
        std::strncpy(entries[count].word, a_word, 100);
        entries[count].word[99] = '\0';
        std::strncpy(entries[count].meaning, a_meaning, 500);
        entries[count].meaning[499] = '\0';
        ++count;
        
    }

    void removeEntry(const char* r_word){
        int id = -1;
        int i = 0;

        while (id == -1 && i < count)
        {
            if(std::strcmp(entries[i].word, r_word) == 0){
                id = i;
            }
            ++i;
        }
        
        if(id == -1) std::cout << "Cant remove that word" << std::endl; return;

        for (int i = id; i < count - 1; ++i)
        {
            entries[i] = entries[i+1];
        }
        --count;
        std::cout << "Removed" << std::endl;
    }

    void giveMeaning(const char* f_word){
        int id = -1;
        int i = 0;

        while (id == -1 && i < count)
        {
            if(std::strcmp(entries[i].word, f_word) == 0){
                id = i;
            }
            ++i;
        }

        if(id == -1) {
            std::cout << "No word found" << std::endl;
             return;
        }
        else std::cout << entries[id].meaning << std::endl;
    }

    static bool compareEntries(const Entry& e1, const Entry& e2){
        return std::strcmp(e1.word, e2.word) < 0;
    }

    void printAsc(){
        if(count == 0){
            std::cout << "Dictionary is empty" << std::endl;
            return;
        }

        for (int i = 0; i < count; ++i){
            for (int j = i + 1; j < count - i - 1; ++j){
                if(std::strcmp(entries[j].word, entries[j+1].word) > 0){
                    std::swap(entries[j], entries[j+1]);
                }
            }
        }
        
        for (int i = 0; i < count; ++i)
        {
            std::cout << entries[i].word << " - " << entries[i].meaning << std::endl;
        }
    }
};

int main() {

    return 0;
}