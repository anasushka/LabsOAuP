#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <forward_list>
#include <utility>
#include <sstream>
#include <functional>
#include <stdexcept>

// HashTable
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
private:
    std::vector<std::forward_list<std::pair<const Key, Value>>> buckets;
    size_t num_elements = 0;
    float max_load = 0.75f;
    Hash hashFunc;

    void rehashIfNeeded() {
        if (buckets.empty()) return;
        float lf = float(num_elements) / buckets.size();
        if (lf > max_load) rehash(buckets.size() * 2);
    }

public:
    HashTable(size_t bc=8, float ml=0.75f) : buckets(bc), max_load(ml) {
        if (buckets.empty()) buckets.resize(1);
    }

    bool contains(const Key& k) const {
        if (buckets.empty()) return false;
        auto idx = hashFunc(k) % buckets.size();
        for (auto& e : buckets[idx]) if (e.first == k) return true;
        return false;
    }

    Value& operator[](const Key& k) {
        if (buckets.empty()) buckets.resize(1);
        auto idx = hashFunc(k) % buckets.size();
        for (auto& e : buckets[idx]) if (e.first == k) return e.second;
        buckets[idx].push_front({k, Value()});
        ++num_elements;
        rehashIfNeeded();
        idx = hashFunc(k) % buckets.size();
        for (auto& e : buckets[idx]) if (e.first == k) return e.second;
        throw std::runtime_error("Insert error");
    }

    Value operator[](const Key& k) const {
        if (buckets.empty()) return {};
        auto idx = hashFunc(k) % buckets.size();
        for (auto& e : buckets[idx]) if (e.first == k) return e.second;
        return {};
    }

    void insert(const std::pair<const Key, Value>& p) {
        if (buckets.empty()) buckets.resize(1);
        auto idx = hashFunc(p.first) % buckets.size();
        for (auto& e : buckets[idx]) if (e.first == p.first) { e.second = p.second; return; }
        buckets[idx].push_front(p);
        ++num_elements;
        rehashIfNeeded();
    }

    bool erase(const Key& k) {
        if (buckets.empty()) return false;
        auto idx = hashFunc(k) % buckets.size();
        auto& chain = buckets[idx];
        auto prev = chain.before_begin();
        for (auto it = chain.begin(); it != chain.end(); ++it, ++prev) {
            if (it->first == k) { chain.erase_after(prev); --num_elements; return true; }
        }
        return false;
    }

    void clear() {
        for (auto& c : buckets) c.clear();
        num_elements = 0;
    }

    void rehash(size_t n) {
        if (n == 0) n = 1;
        std::vector<std::forward_list<std::pair<const Key, Value>>> nb(n);
        for (auto& c : buckets) for (auto& e : c) {
                auto idx = hashFunc(e.first) % nb.size();
                nb[idx].push_front(std::move(e));
            }
        buckets = std::move(nb);
    }

    size_t size() const { return num_elements; }
    bool empty() const { return num_elements == 0; }
    size_t bucket_count() const { return buckets.size(); }
    float load_factor() const { return buckets.empty() ? 0.0f : float(num_elements) / buckets.size(); }

    std::string debugString() const {
        std::ostringstream oss;
        for (size_t i = 0; i < buckets.size(); ++i) {
            oss << "Bucket " << i << ": ";
            for (auto& e : buckets[i]) oss << "[" << e.first << ":" << e.second.toStdString() << "] ";
            oss << "\n";
        }
        return oss.str();
    }
};

#endif // HASHTABLE_H
