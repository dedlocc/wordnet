#include "wordnet.h"

#include <fstream>
#include <iterator>

Digraph::Digraph(const std::string & filename)
{
    std::ifstream in(filename);

    if (!in) {
        throw std::runtime_error("Hypernyms file not found");
    }

    std::size_t id;
    while (in >> id) {
        auto & adj = edges[id];
        while (in.peek() != '\n') {
            in.ignore();
            std::size_t next;
            in >> next;
            adj.insert(next);
        }
        in >> std::ws;
    }
}

const std::unordered_set<std::size_t> & Digraph::operator[](const std::size_t v) const
{
    return edges.at(v);
}

std::ostream & operator<<(std::ostream & out, const Digraph & graph)
{
    std::ostream_iterator<std::size_t> outIt(out, " ");
    for (const auto & adj : graph.edges) {
        out << adj.first << ": ";
        std::copy(adj.second.begin(), adj.second.end(), outIt);
        out << '\n';
    }
    return out;
}
