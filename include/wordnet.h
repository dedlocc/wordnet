#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Digraph
{
public:
    template <class InputStream>
    Digraph(InputStream && in)
    {
        // fixme simplify
        while (in)
        {
            auto & hypernyms = edges.emplace_back();
            std::size_t next;
            in >> next;
            while ('\n' != in.peek())
            {
                in.ignore();
                in >> next;
                hypernyms.push_back(next);
            }
            in.ignore();
        }
    }
private:
    std::vector<std::vector<std::size_t>> edges;
};

class LowestCommonAncestor
{
public:
    LowestCommonAncestor(const Digraph &);

    // calculates length of LCA path between nodes
    std::size_t length(std::size_t, std::size_t) const;

    // returns node id of LCA of nodes
    std::size_t ancestor(std::size_t, std::size_t) const;

    // calculates length of LCA path between node subsets
    std::size_t length(const std::set<std::size_t> &, const std::set<std::size_t> &) const;

    // returns node id of LCA of node subsets
    std::size_t ancestor(const std::set<std::size_t> &, const std::set<std::size_t> &) const;

private:
    Digraph graph;
};

class WordNet
{
public:
    WordNet(const std::string & synsetsFile, const std::string & hypernymsFile);

    class iterator
    {
        using iterator_category = std::forward_iterator_tag;
        // To do
    };

    // get iterator to list all nouns stored in WordNet
    iterator nouns();
    iterator end();

    // returns 'true' iff word is stored in WordNet
    bool isNoun(const std::string &) const;

    // returns gloss of LCA of nouns
    std::string lca(const std::string &, const std::string &) const;

    // calculates distance between nouns
    std::size_t distance(const std::string &, const std::string &) const;

private:
    LowestCommonAncestor graph;
    std::unordered_map<std::string, std::set<std::size_t>> wordMap;
    std::vector<std::string> glossary;
};

class Outcast
{
public:
    Outcast(WordNet &);

    // returns outcast word
    std::string outcast(const std::vector<std::string> &);

private:
    WordNet wordnet;
};
