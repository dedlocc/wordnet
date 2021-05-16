#include "wordnet.h"

#include <cassert>
#include <queue>

using LCA = LowestCommonAncestor;

std::size_t LCA::Cache::Hash::operator()(const Key key) const noexcept
{
    return (key.first + 1) ^ key.second;
}

LCA::Result & LCA::Cache::get(std::size_t a, std::size_t b)
{
    if (a > b) {
        std::swap(a, b);
    }
    std::lock_guard<std::mutex> lock(mutex);
    return data.try_emplace({a, b}).first->second;
}

LCA::LowestCommonAncestor(const Digraph & graph)
    : graph(graph)
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
    auto & cached = cache.get(*v.begin(), *w.begin());

    if (cached) {
        return cached;
    }

    Result result;

    std::unordered_map<std::size_t, std::pair<std::size_t, bool>> visited;
    std::queue<std::size_t> q;

    for (const auto & e : v) {
        visited[e] = {0, false};
        q.push(e);
    }

    for (const auto & e : w) {
        if (!visited.emplace(e, std::make_pair(0, true)).second) {
            return result = {e, 0};
        }
        q.push(e);
    }

    while (!q.empty()) {
        const auto cur = q.front();
        q.pop();

        const auto [length, isFirst] = visited.find(cur)->second;

        for (const auto edge : graph[cur]) {
            const auto & it = visited.find(edge);
            if (visited.end() == it) {
                visited[edge] = {length + 1, isFirst};
                q.push(edge);
            }
            else if (isFirst != it->second.second) {
                const auto newLength = length + it->second.first + 1;
                if (newLength < result.length) {
                    result = {edge, newLength};
                }
            }
        }
    }

    assert(result);
    return cached = result;
}
