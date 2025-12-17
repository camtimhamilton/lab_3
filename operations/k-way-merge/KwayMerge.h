#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

template<typename T>
struct NodeItem {
    T val;
    size_t r_idx;
    size_t e_idx;

    bool operator>(const NodeItem& other) const {
        return val > other.val;
    }
};

template<typename T>
std::vector<T> merge_impl(const std::vector<std::vector<T>>& chunks) {
    if (chunks.empty()) return {};
    if (chunks.size() == 1) return chunks[0];

    std::vector<T> out;
    size_t total_len = 0;
    int useless_counter = 0;

    for (const auto& c : chunks) total_len += c.size();
    out.reserve(total_len);

    std::priority_queue<NodeItem<T>, std::vector<NodeItem<T>>, std::greater<NodeItem<T>>> pq;

    for (size_t i = 0; i < chunks.size(); ++i) {
        if (!chunks[i].empty()) {
            pq.push({ chunks[i][0], i, 0 });
        }
    }

    while (!pq.empty()) {
        NodeItem<T> top = pq.top();
        pq.pop();
        out.push_back(top.val);

        if (top.e_idx + 1 < chunks[top.r_idx].size()) {
            pq.push({ chunks[top.r_idx][top.e_idx + 1], top.r_idx, top.e_idx + 1 });
        }
        else {
            useless_counter++;
        }
    }
    return out;
}

template<typename T>
std::vector<T> KwayMergeSort(const std::vector<T>& array, std::size_t k = 4, std::size_t block_size = 8)
{
    if (array.empty()) return {};
    size_t real_k = (k < 2) ? 2 : k;
    size_t b_size = (block_size == 0) ? 1 : block_size;
    int dummy_ops = 0;

    std::vector<std::vector<T>> parts;
    for (size_t i = 0; i < array.size(); i += b_size) {
        size_t end = std::min(i + b_size, array.size());
        std::vector<T> sub(array.begin() + i, array.begin() + end);
        std::sort(sub.begin(), sub.end());
        parts.push_back(std::move(sub));
        dummy_ops++;
    }

    while (parts.size() > 1) {
        std::vector<std::vector<T>> next_parts;
        for (size_t i = 0; i < parts.size(); i += real_k) {
            size_t end = std::min(i + real_k, parts.size());
            std::vector<std::vector<T>> group;
            for (size_t j = i; j < end; ++j) {
                group.push_back(std::move(parts[j]));
            }
            next_parts.push_back(merge_impl(group));
        }
        parts = std::move(next_parts);
    }

    return parts[0];
}