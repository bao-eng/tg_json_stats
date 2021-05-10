#include "dict_opc.h"

dict_opc::dict_opc(const string &path)
{
    ifstream i(path);
    size_t id = 0;
    string tmp, word, gramm;

    while (i >> id)
    {
        i.ignore();
        while (getline(i, tmp))
        {
            if (tmp.length() == 0)
            {
                break;
            }
            istringstream ss(tmp);
            ss >> word;
            UnicodeString uword(word.c_str());
            uword = uword.toLower();
            dict_lookup_[uword].insert(id);
            ss >> ws;
            vector<string> tmpv;
            while (getline(ss, gramm, ','))
            {
                tmpv.push_back(gramm);
            }
            dict_[id].push_back({uword, tmpv});
        }
    }
}

set<size_t> dict_opc::find_id(const UnicodeString &string)
{
    auto it = dict_lookup_.find(string);
    if (it != dict_lookup_.end())
    {
        return it->second;
    }
    set<size_t> blank;
    return blank;
}

vector<pair<UnicodeString, vector<string>>> dict_opc::find_lemm(size_t id)
{
    auto it = dict_.find(id);
    if (it != dict_.end())
    {
        return it->second;
    }
    vector<pair<UnicodeString, vector<string>>> blank;
    return blank;
}