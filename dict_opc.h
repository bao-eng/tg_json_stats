#pragma once

#include <fstream>
#include <string>
#include <sstream>

#include <map>
#include <vector>
#include <set>

#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/locid.h>

using namespace std;
using namespace icu;

class dict_opc
{
public:
    dict_opc(const string &path);
    set<size_t> find_id(const UnicodeString &string);
    vector<pair<UnicodeString, vector<string>>> find_lemm(size_t id);

private:
    map<UnicodeString, set<size_t>> dict_lookup_;
    //map<UnicodeString, map<size_t,>> dict_lookup_;
    map<size_t, vector<pair<UnicodeString, vector<string>>>> dict_;
    //map<UnicodeString, vector<pair<size_t, vector<string>>>> dict_;
};