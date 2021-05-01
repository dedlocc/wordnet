#pragma once

#include "digraph.h"

#include <set>

class LowestCommonAncestor
{
public:
    LowestCommonAncestor(const Digraph &);

    // calculates length of LCA path between nodes
    std::size_t length(std::size_t, std::size_t) const;

    // returns node id of LCA of nodes
    std::size_t ancestor(std::size_t, std::size_t) const;

    // calculates length of LCA path between node subsets
    std::size_t lengthSubset(const std::set<std::size_t> &, const std::set<std::size_t> &) const;

    // returns node id of LCA of node subsets
    std::size_t ancestorSubset(const std::set<std::size_t> &, const std::set<std::size_t> &) const;
};
