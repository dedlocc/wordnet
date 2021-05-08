#include "wordnet.h"

LowestCommonAncestor::LowestCommonAncestor(const Digraph &graph) : graph(graph) {}

std::size_t LowestCommonAncestor::length(std::size_t v, std::size_t w) const
{
    // TODO Implement
}

std::size_t LowestCommonAncestor::ancestor(std::size_t v, std::size_t w) const
{
    // TODO Implement
}

std::size_t LowestCommonAncestor::lengthSubset(
        const std::set<std::size_t> &a,
        const std::set<std::size_t> &b
) const
{
    // TODO Implement
}

std::size_t LowestCommonAncestor::ancestorSubset(
        const std::set<std::size_t> &a,
        const std::set<std::size_t> &b
) const
{
    // TODO Implement
}
