#include <mutex>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Digraph
{
public:
    explicit Digraph(const std::string & filename);

    // returns set of nodes adjacent to the given one
    const std::unordered_set<std::size_t> & operator[](std::size_t v) const;

    // prints adjacency lists to out
    friend std::ostream & operator<<(std::ostream & out, const Digraph & graph);

private:
    std::unordered_map<std::size_t, std::unordered_set<std::size_t>> edges;
};

class LowestCommonAncestor
{
public:
    LowestCommonAncestor(Digraph);

    // calculates length of LCA path between nodes
    std::size_t length(std::size_t, std::size_t) const;

    // returns node id of LCA of nodes
    std::size_t ancestor(std::size_t, std::size_t) const;

    // calculates length of LCA path between node subsets
    std::size_t length(const std::set<std::size_t> &, const std::set<std::size_t> &) const;

    // returns node id of LCA of node subsets
    std::size_t ancestor(const std::set<std::size_t> &, const std::set<std::size_t> &) const;

private:
    const Digraph graph;

    struct Result
    {
        static constexpr std::size_t INVALID = std::numeric_limits<std::size_t>::max();

        std::size_t ancestor = 0;
        std::size_t length = INVALID;

        operator bool() const
        {
            return length != INVALID;
        }
    };

    Result bfs(const std::set<std::size_t> &, const std::set<std::size_t> &) const;
};

class WordNet
{
    using WordMap = std::unordered_map<std::string, std::set<std::size_t>>;

public:
    WordNet(const std::string & synsets, const std::string & hypernyms);

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = WordMap::key_type;
        using difference_type = typename WordMap::iterator::difference_type;
        using pointer = const value_type *;
        using reference = const value_type &;

        iterator() = default;
        iterator(const WordMap::iterator & it)
            : it(it)
        {
        }

        reference operator*() const
        {
            return it->first;
        }

        pointer operator->() const
        {
            return &it->first;
        }

        iterator & operator++()
        {
            ++it;
            return *this;
        }

        iterator operator++(int)
        {
            auto tmp = *this;
            ++it;
            return tmp;
        }

        friend bool operator==(const iterator & lhs, const iterator & rhs)
        {
            return lhs.it == rhs.it;
        }

        friend bool operator!=(const iterator & lhs, const iterator & rhs)
        {
            return lhs.it != rhs.it;
        }

    private:
        WordMap::iterator it;
    };

    // get iterator to list all nouns stored in WordNet
    iterator begin();
    iterator end();

    // returns 'true' iff word is stored in WordNet
    bool is_noun(const std::string &) const;

    // returns gloss of LCA of nouns
    std::string lca(const std::string &, const std::string &) const;

    // calculates distance between nouns
    std::size_t distance(const std::string &, const std::string &) const;

private:
    LowestCommonAncestor graph;
    WordMap wordMap;
    std::unordered_map<std::size_t, std::string> glossary;
};

class Outcast
{
public:
    Outcast(const WordNet &);

    // returns outcast word
    std::string outcast(const std::vector<std::string> &);

private:
    const WordNet & wordnet;
};
