#include <set>
#include <string>
#include <vector>

class Digraph
{
    // Please implement...
};

class ShortestCommonAncestor
{
    ShortestCommonAncestor(Digraph & dg);

    // calculates length of shortest common ancestor path from node with id 'v' to node with id 'w'
    int length(int v, int w);

    // returns node id of shortest common ancestor of nodes v and w
    int ancestor(int v, int w);

    // calculates length of shortest common ancestor path from node subset 'subset_a' to node subset 'subset_b'
    int length_subset(const std::set<int> & subset_a, const std::set<int> & subset_b);

    // returns node id of shortest common ancestor of node subset 'subset_a' and node subset 'subset_b'
    int ancestor_subset(const std::set<int> & subset_a, const std::set<int> & subset_b);
};

class WordNet
{
public:
    WordNet(const std::string & synsets_fn, const std::string & hypernyms_fn);

    class iterator
    {
        using iterator_category = std::forward_iterator_tag;
        // To do
    };

    // get iterator to list all nouns stored in WordNet
    iterator nouns();
    iterator end();

    // returns 'true' iff 'word' is stored in WordNet
    bool is_noun(const std::string & word) const;

    // returns gloss of "shortest common ancestor" of noun1 and noun2
    std::string sca(const std::string & noun1, const std::string & noun2);

    // calculates distance between noun1 and noun2
    int distance(const std::string & noun1, const std::string & noun2);
};

class Outcast
{
public:
    Outcast(WordNet & wordnet);

    // returns outcast word
    std::string outcast(const std::vector<std::string> & nouns);
};
