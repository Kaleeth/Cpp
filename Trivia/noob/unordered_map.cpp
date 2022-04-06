#include <string>
#include <unordered_map>

const std::string &
more_frequent(const std::unordered_map<std::string, int> &word_counts,
                const std::string &word1, const std::string &word2) {
    // counts[word1] creates new entry with value 0 in case if doesn't already exist!
    return word_counts.at(word1) > word_counts.at(word2) ? word1 : word2;
}

// on the side note, string literals like "string" are guaranteed to live for the entire life of a program
// so return "string" for function returning const char * is fine