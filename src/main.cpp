#include "wordnet.h"

#include <iostream>

// For debug purposes
int main()
{
    WordNet wordnet("tests/etc/synsets.txt", "tests/etc/hypernyms.txt");
    Outcast outcast(wordnet);

    while (true) {
        std::string action;
        std::cin >> action;

        if (action == "is" || action == "has" || action == "noun") {
            std::string w;
            std::cin >> w;
            std::cout << (wordnet.is_noun(w) ? "Yes" : "No") << '\n';
        }
        else if (action == "lca" || action == "sca") {
            std::string w1, w2;
            std::cin >> w1 >> w2;
            std::cout << wordnet.lca(w1, w2) << '\n';
        }
        else if (action == "distance" || action == "dist" || action == "d") {
            std::string w1, w2;
            std::cin >> w1 >> w2;
            std::cout << wordnet.distance(w1, w2) << '\n';
        }
        else if (action == "outcast" || action == "oc") {
            std::string w;
            std::vector<std::string> words;
            while (std::cin >> w && w != "$") {
                words.push_back(w);
            }
            std::cout << outcast.outcast(words) << '\n';
        }
    }
}
