#pragma once
#include "ICache.h"
#include <vector>
#include <unordered_map>

template<typename Key, typename Value>
class ClockCache : public ICache<Key, Value> {
private:
    struct Page {
        Key k;
        Value v;
        bool bit;
    };

    size_t _cap;
    size_t _ptr;
    std::vector<Page> _vec;
    std::unordered_map<Key, size_t> _map;

    long long _access_count = 0;

public:
    explicit ClockCache(size_t capacity) : _cap(capacity), _ptr(0) {
        if (_cap == 0) _cap = 1;
        _vec.reserve(_cap);
    }

    void set(const Key& key, const Value& value) override {
        if (_map.find(key) != _map.end()) {
            size_t idx = _map[key];
            _vec[idx].v = value;
            _vec[idx].bit = true;
            return;
        }

        if (_vec.size() < _cap) {
            _vec.push_back({ key, value, true });
            _map[key] = _vec.size() - 1;
            return;
        }

        for (;;) {
            if (_vec[_ptr].bit) {
                _vec[_ptr].bit = false;
                _ptr = (_ptr + 1) % _cap;
            }
            else {
                Key old_k = _vec[_ptr].k;
                _map.erase(old_k);

                _vec[_ptr].k = key;
                _vec[_ptr].v = value;
                _vec[_ptr].bit = true;
                _map[key] = _ptr;

                _ptr = (_ptr + 1) % _cap;
                return;
            }
        }
    }

    Value get(const Key& key) override {
        _access_count++;
        if (_map.find(key) != _map.end()) {
            size_t i = _map[key];
            _vec[i].bit = true;
            return _vec[i].v;
        }
        return Value();
    }

    bool contains(const Key& key) const override {
        return _map.find(key) != _map.end();
    }

    void clear() override {
        _vec.clear();
        _map.clear();
        _ptr = 0;
        _access_count = 0;
    }

    size_t size() const override {
        return _vec.size();
    }
};