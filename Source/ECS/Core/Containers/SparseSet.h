#pragma once
#include <cassert>
#include <memory>
#include <type_traits>
#include <vector>

template <typename T, size_t PageSize, typename = std::enable_if<std::is_integral_v<T>>>
class SparseSet final
{
public:
    void insert(T t)
    {
        density.emplace_back(t);
        assure(t);
        index(t) = density.size() - 1;
    }

    void remove(T t)
    {
        if(!contains(t)) return;
        auto &idx = index(t);
        if(idx == density.size() - 1) {
            idx = null;
            density.pop_back();
        }
        else {
            auto last   = density.back();
            index(last) = null;
            std::swap(density[idx], density.back());
            idx = null;
            density.pop_back();
        }
    }

    bool contains(T t) const
    {
        assert(t != null);
        auto p = page(t);
        auto o = offset(t);
        return p < sparse.size() && sparse[p][o] != null;
    }

    void clear()
    {
        density.clear();
        sparse.clear();
    }

    auto begin() const { return density.begin(); }

    auto end() const { return density.end(); }

    auto size() const { return density.size(); }

private:
    std::vector<T> density;
    std::vector<std::array<T, PageSize>> sparse;
    // 数组默认初始化为INF
    static constexpr T null = std::numeric_limits<T>::max();

    size_t page(T t) const { return t / PageSize; }

    size_t offset(T t) const { return t % PageSize; }

    T index(T t) const { return sparse[page(t)][offset(t)]; }

    T &index(T t) { return sparse[page(t)][offset(t)]; }

    // 分配内存
    void assure(T t)
    {
        auto p = page(t);
        if(p >= sparse.size()) {
            sparse.resize(p + 1);
            sparse[p].fill(null);
        }
    }
};
