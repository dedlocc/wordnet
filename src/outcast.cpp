#include "wordnet.h"

Outcast::Outcast(WordNet & wordnet)
    : wordnet(wordnet)
{
}

std::string Outcast::outcast(const std::vector<std::string> & nouns)
{
    if (nouns.size() <= 2) {
        return "";
    }

    std::vector<std::size_t> dist(nouns.size(), 0);
    std::size_t maxIndex = 0;
    bool multiple = false;

    for (std::size_t i = 0; i < nouns.size(); ++i) {
        for (std::size_t j = i + 1; j < nouns.size(); ++j) {
            const auto t = wordnet.distance(nouns[i], nouns[j]);
            dist[i] += t;
            dist[j] += t;
        }

        if (dist[i] > dist[maxIndex]) {
            maxIndex = i;
            multiple = false;
        }
        else if (dist[i] == dist[maxIndex] && i != 0) {
            multiple = true;
        }
    }

    return multiple ? "" : nouns[maxIndex];
}
