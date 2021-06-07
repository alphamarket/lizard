#pragma once

#include <mutex>
#include <vector>
#include <memory>
#include <cstring>
#include <sstream>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

#include "defines.hpp"

namespace lizard {
class Tester {
public:
    struct TestUnitResult {
        size_t
            number_of_success = 0,
            number_of_errors = 0,
            number_of_skips = 0,
            total = 0;
    };

    class Base {
        std::string _name;
        std::unordered_map<std::string, std::vector<std::pair<std::string, std::function<void(void)>>>> _executioners = {
            { "specs", { } },
            { "onstarts", { } },
            { "onternimates", { } }
        };
        std::unordered_map<std::string, std::vector<std::pair<std::string, std::function<void(const std::string&)>>>> _conditioners = {
            { "prespecs", { } },
            { "postspecs", { } },
        };

        // make a backup from current stdout
        mutable std::ostringstream stdout_buffer;
        mutable std::streambuf* stdout_handler = nullptr;

        void flush_buffer() const;
        void clear_buffer(void) const;

        inline std::string buffer() const {
            return stdout_buffer.str();
        }

    protected:
        Base(const std::string& name)
            : _name(name)
        { clear_buffer(); stdout_handler = std::cout.rdbuf(); }

        virtual ~Base() { }

        inline const auto& name() const noexcept
        { return _name; }

        inline const auto& executioner(const std::string& label) const noexcept
        { return _executioners.at(label); }

        inline const auto& conditioner(const std::string& label) const noexcept
        { return _conditioners.at(label); }

        inline void clear_stdout_buffer() const { clear_buffer(); }

        template<typename Collection, typename Callback>
        void registery(Collection& collection, const std::string& label, const Callback& callback) {
#if 0
            if(std::accumulate(collection.begin(), collection.end(), false, [&label](auto prev, auto item) { return prev || item.first == label; }))
                throw LizardRuntimeError("Duplicate `" + label + "`, cannot register it!");
#endif
            collection.push_back({ label, callback });
        }

        template<typename Callback>
        inline void spec(const std::string& label, const Callback& callback) { registery(_executioners["specs"], label, callback); }

        template<typename Callback>
        inline void prespec(const std::string& label, const Callback& callback) { registery(_conditioners["prespecs"], label, callback); }

        template<typename Callback>
        inline void postspec(const std::string& label, const Callback& callback) { registery(_conditioners["postspecs"], label, callback); }

        template<typename Callback>
        inline void onstart(const std::string& label, const Callback& callback) { registery(_executioners["onstarts"], label, callback); }

        template<typename Callback>
        inline void onterminate(const std::string& label, const Callback& callback) { registery(_executioners["onternimates"], label, callback); }

        virtual void setup() = 0;

        void change_stdout(bool change2buffer) const;

    public:
        TestUnitResult run() const;
    };

    std::vector<std::shared_ptr<Base>> _test_units;

public:
    Tester() { }

    TestUnitResult run() const;

    template<typename T>
    void register_it() { _test_units.push_back(std::make_shared<T>()); }
};

}
