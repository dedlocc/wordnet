#include "wordnet.h"

#include <fstream>
#include <sstream>

WordNet::WordNet(const std::string & synsets, const std::string & hypernyms)
    : graph(hypernyms)
{
    std::ifstream in(synsets);

    if (!in) {
        throw std::runtime_error("Synsets file not found");
    }

    std::size_t id;
    while (in >> id) {
        in.ignore();
        std::string synonyms;
        std::getline(in, synonyms, ',');
        std::stringstream ss(synonyms);
        while (ss >> synonyms) {
            wordMap[std::move(synonyms)].insert(id);
        }

        std::getline(in, glossary[id]);
    }
}

WordNet::iterator WordNet::begin()
{
    return iterator(wordMap.begin());
}

WordNet::iterator WordNet::end()
{
    return iterator(wordMap.end());
}

bool WordNet::is_noun(const std::string & word) const
{
    return wordMap.find(word) != wordMap.end();
}

std::string WordNet::lca(const std::string & noun1, const std::string & noun2) const
{
    return glossary.at(graph.ancestor(wordMap.at(noun2), wordMap.at(noun1)));
}

std::size_t WordNet::distance(const std::string & noun1, const std::string & noun2) const
{
    return graph.length(wordMap.at(noun1), wordMap.at(noun2));
}
