#pragma once

#include "lca.h"

#include <string>
#include <vector>

class WordNet
{
public:
    WordNet(const std::string &synsetsFile, const std::string &hypernymsFile);

    class iterator
    {
        using iterator_category = std::forward_iterator_tag;

        // TODO Design interface
    };

    // get iterator to list all nouns stored in WordNet
    iterator nouns();
    iterator end();

    // returns 'true' iff 'word' is stored in WordNet
    bool isNoun(const std::string &) const;

    // returns gloss of LCA of nouns
    std::string lca(const std::string &, const std::string &) const;

    // calculates distance between nouns
    std::size_t distance(const std::string &, const std::string &) const;
};

class Outcast
{
public:
    Outcast(WordNet &);

    // returns outcast word
    std::string outcast(const std::vector<std::string> &);
};
