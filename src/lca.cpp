#include "wordnet.h"

#include <cassert>
#include <queue>

using LCA = LowestCommonAncestor;

LCA::LowestCommonAncestor(Digraph graph)
    : graph(std::move(graph))
{
}

std::size_t LCA::length(const std::size_t v, const std::size_t w) const
{
    return bfs({v}, {w}).length;
}

std::size_t LCA::ancestor(const std::size_t v, const std::size_t w) const
{
    return bfs({v}, {w}).ancestor;
}

std::size_t LCA::length(const std::set<std::size_t> & v, const std::set<std::size_t> & w) const
{
    return bfs(v, w).length;
}

std::size_t LCA::ancestor(const std::set<std::size_t> & v, const std::set<std::size_t> & w) const
{
    return bfs(v, w).ancestor;
}

LCA::Result LCA::bfs(const std::set<std::size_t> & v, const std::set<std::size_t> & w) const
{
    std::array<std::unordered_map<std::size_t, std::size_t>, 2> visited;
    std::queue<std::pair<std::size_t, std::size_t>> q;

    for (const auto & e : v) {
        visited[0].emplace(e, 0);
        q.emplace(e, 0);
    }

    for (const auto & e : w) {
        if (visited[0].find(e) != visited[0].end()) {
            return {e, 0};
        }
        visited[1].emplace(e, 0);
        q.emplace(e, 1);
    }

    Result result;

    while (!q.empty()) {
        const auto [cur, i] = q.front();
        q.pop();

        auto & current = visited[i];
        const auto & other = visited[1 - i];
        const auto length = current.at(cur) + 1;

        for (const auto edge : graph[cur]) {
            if (current.emplace(edge, length).second) {
                q.emplace(edge, i);
            }

            const auto it = other.find(edge);
            if (it != other.end()) {
                const auto newLength = length + it->second;
                if (newLength < result.length) {
                    result = {edge, newLength};
                }
            }
        }
    }

    assert(result);
    return result;
}
