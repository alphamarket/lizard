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
        mutable std::ostringstream lizard_std_buffer;
        mutable std::streambuf* lizard_stdout = nullptr;

        void flush_buffer() const;
        void clear_buffer(void) const;
        void change_stdout(bool change2buffer) const;

        inline std::string buffer() const { return lizard_std_buffer.str(); }

    protected:
        Base(const std::string& name)
            : _name(name)
        {
            lizard_stdout = std::cout.rdbuf();
            Tester::instance()->signup(name, this);
        }

        inline const auto& name() const noexcept
        { return _name; }

        inline const auto& executioner(const std::string& label) const noexcept
        { return _executioners.at(label); }

        inline const auto& conditioner(const std::string& label) const noexcept
        { return _conditioners.at(label); }


        template<typename Collection, typename Callback>
        void registery(Collection& collection, const std::string& label, const Callback& callback) {
            if(std::accumulate(collection.begin(), collection.end(), false, [&label](auto prev, auto item) { return prev || item.first == label; }))
                throw LizardRuntimeError("Duplicate `" + label + "`, cannot register it!");
            collection.emplace_back(label, callback);
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

        template<typename Callback>
        inline void prespec(const Callback& callback) { prespec("", callback); }

        template<typename Callback>
        inline void postspec(const Callback& callback) { postspec("", callback); }

        template<typename Callback>
        inline void onstart(const Callback& callback) { onstart("", callback); }

        template<typename Callback>
        inline void onterminate(const Callback& callback) { onterminate("", callback); }

        virtual void setup() = 0;

    public:
        TestUnitResult run() const;
    };

private:
    static std::shared_ptr<Tester> _instance;
    static std::vector<std::shared_ptr<Base>> _test_units;

    std::vector<std::tuple<std::string, const Base*, bool>> _manifest;

public:
    Tester() { }

    static std::shared_ptr<Tester>& instance() noexcept {
        if(_instance == nullptr)
            _instance = std::make_shared<Tester>();
        return _instance;
    }

    TestUnitResult run() const;
    void signup(const std::string& name, const Base* tester);

    template<typename T>
    static void register_it() { _test_units.push_back(std::make_shared<T>()); }
};

}
