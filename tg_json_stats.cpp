/**
 * @file tg_json_stats.cpp
 * @author bao-eng
 * @brief 
 * 
 */

#include "tg_json_stats.h"

vector<string> SplitIntoWords(const string &line)
{
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

tg_json_stats::tg_json_stats(const string &path, const string &opc_path) // : dict_opc_(opc_path)
{
    ifstream i(path);
    json j;
    i >> j;
    for (json &c : j["chats"]["list"])
    {
        for (json &d : c["messages"])
        {
            if ((d["type"] == "message") && (d["from"].is_string()))
            {
                //UnicodeString ufrom = ((string)d["from"]).c_str();
                if (d["text"].type() == json::value_t::string)
                {
                    auto tmp = SplitIntoWords(d["text"]);
                    for (auto e : tmp)
                    {
                        add_word(e,d["from"]);
                    }
                }
                if (d["text"].type() == json::value_t::array)
                {
                    for (json &f : d["text"])
                    {
                        if (f.type() == json::value_t::string)
                        {
                            auto tmp = SplitIntoWords(f);
                            for (auto e : tmp)
                            {
                                add_word(e,d["from"]);
                            }
                        }
                    }
                }
            }
        }
    }
    //cout << "word_count_total_.size() " << word_count_total_.size() << endl;
    find_unique();
}

size_t tg_json_stats::get_dict_size() const
{
    return dict_.size();
}

size_t tg_json_stats::get_word_count(const UnicodeString &word) const
{
    UnicodeString wordlc = word;
    wordlc = wordlc.toLower();
    auto it = word_count_total_.find(wordlc);
    if (it != word_count_total_.end())
    {
        return it->second;
    }
    return 0;
}

size_t tg_json_stats::only_nouns()
{
    int count = 0;
    int count1 = 0;
    set<size_t> ids;
    for (auto it = dict_.cbegin(); it != dict_.cend();)
    {
        UnicodeString itstr = *it;
        //ids = dict_opc_.find_id(*it);

        // for (auto id : ids)
        // {
        //     vector<pair<UnicodeString, vector<string>>> tmpv = dict_opc_.find_lemm(id);
        //     for(auto j : tmpv){
        //         if(j.first == itstr){

        //         }
        //     }
        // }

        count++;
        if (ids.size() == 0)
        {
            it = dict_.erase(it);
            word_count_total_.erase(itstr);
        }
        else
        {
            ++it;
        }
    }
    return get_dict_size();
}

int tg_json_stats::find_unique()
{
    for (auto i : word_users_)
    {
        if ((i.second.size() == 1))
        {
            unique_[i.second.begin()->first].push_back({i.second.begin()->second, i.first});
        }
    }
    for (auto &i : unique_)
    {
        sort(i.second.rbegin(), i.second.rend());
    }
    // for (auto &i : top_)
    // {
    //     // sort(i.second.rbegin(), i.second.rend());
    // }
    return 0;
}

map<UnicodeString, vector<pair<size_t, UnicodeString>>> tg_json_stats::get_unique() const
{
    return unique_;
}
map<UnicodeString, vector<pair<size_t, UnicodeString>>> tg_json_stats::get_top()
{
    for (auto i : top_)
    {
        for (auto j : i.second)
        {
            topv_[i.first].push_back({j.second, j.first});
        }
        sort(topv_[i.first].rbegin(), topv_[i.first].rend());
    }
    return topv_;
}

void tg_json_stats::add_word(const string &word, const string &from)
{
    UnicodeString tmpstr = word.c_str();
    tmpstr = tmpstr.toLower();
    UnicodeString ufrom = ((string)from).c_str();
    // set<size_t> ids;
    // ids = dict_opc_.find_id(*it);
    // for (auto id : ids)
    // {
    //     vector<pair<UnicodeString, vector<string>>> tmpv = dict_opc_.find_lemm(id);
    //     for (auto j : tmpv)
    //     {
    //         if (j.first == itstr)
    //         {
    //         }
    //     }
    // }

    dict_.insert(tmpstr);
    word_count_total_[tmpstr]++;
    top_[ufrom][tmpstr]++;
    word_users_[tmpstr][ufrom]++;
    // word_users_[tmpstr].insert(ufrom);
}