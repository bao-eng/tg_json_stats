#pragma once

#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <string>

#include <nlohmann/json.hpp>

#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/locid.h>

#include "dict_opc.h"

using namespace std;
using namespace icu;
using json = nlohmann::json;

/**
 * @brief split input string itno separate words
 * 
 * @param line input string
 * @return vector<string> output vestor of words
 */
vector<string> SplitIntoWords(const string &line);

/**
 * @brief 
 * 
 */
class tg_json_stats
{
public:
    /**
     * @brief Construct a new tg json stats object and import messages and dictionary
     * 
     * @param path path to the input json with telegram messages
     * @param opc_path path to the opencorpora plain-text dictionary
     */
    tg_json_stats(const string &path, const string &opc_path);
    void add_word(const string &word, const string &from);
    size_t get_dict_size() const;
    size_t get_word_count(const UnicodeString &) const;
    size_t only_nouns();
    int find_unique();
    map<UnicodeString, vector<pair<size_t, UnicodeString>>> get_unique() const;
    map<UnicodeString, vector<pair<size_t, UnicodeString>>> get_top();

    // private:
    set<UnicodeString> dict_;
    map<UnicodeString, size_t> word_count_total_;
    //map<UnicodeString, vector<pair<UnicodeString, size_t>>> index_;
    map<UnicodeString, map<UnicodeString, size_t>> top_;
    map<UnicodeString, vector<pair<size_t, UnicodeString>>> topv_;
    // map<UnicodeString, set<UnicodeString>> word_users_;
    map<UnicodeString, map<UnicodeString, size_t>> word_users_;
    map<UnicodeString, vector<pair<size_t, UnicodeString>>> unique_;
    // dict_opc dict_opc_;
};