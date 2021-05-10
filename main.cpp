#include <iostream>

#include "tg_json_stats.h"

using namespace std;
using namespace icu;

int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     cout << "Please provide path to input file." << endl;
    //     return 0;
    // }

    //ifstream i(argv[1]);
    // ifstream i("../example_1.json");
    // ifstream i("/home/toor/Downloads/Telegram Desktop/DataExport_2021-05-06/result.json");

    // if (i.fail())
    // {
    //     throw runtime_error("Unable to open file "); // + file_path);
    // }

    tg_json_stats stats("result.json", "dict.opcorpora.txt");
    cout << "dict_size " << stats.get_dict_size() << endl;
    cout << "Привет " << stats.get_word_count("Привет") << endl;
    //cout << "only_nouns " << stats.only_nouns() << endl;

    vector<pair<UnicodeString, size_t>> words_sorted;

    for (auto i : stats.word_count_total_)
    {
        words_sorted.push_back({i.first, i.second});
    }
    sort(words_sorted.begin(), words_sorted.end(), [](pair<UnicodeString, size_t> a, pair<UnicodeString, size_t> b) {
        return a.second > b.second;
    });

    for (auto i : stats.top_["Andrey Basov"])
    {
        if (i.second > 10)
        {
            cout << i.first << " " << i.second << endl;
        }
    }

    auto unique = stats.get_unique();
    for (auto &i : unique)
    {
        cout << i.first << endl;
        for (auto j = i.second.begin(); ((j != i.second.begin() + 10) && (j != i.second.end())); j++)
        {
            cout << j->second << " " << j->first << endl;
        }
        cout << endl;
    }

    // auto top = stats.get_top();
    // for (auto &i : top)
    // {
    //     cout << i.first << endl;
    //     for (auto j = i.second.begin(); ((j != i.second.begin() + 10) && (j != i.second.end())); j++)
    //     {
    //         cout << j->second << " " << j->first << endl;
    //     }
    //     cout << endl;
    // }
}
