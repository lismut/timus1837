#include<iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

struct rateSet {
    size_t rate = 500;
    std::set<std::string> friends;
};

void addPerson(const std::string& one, const std::string& two, const std::string& three, std::map<std::string, rateSet>& all) {
    all[one].friends.insert(two);
    all[one].friends.insert(three);
}

void recursiveWalk(std::set<std::string>& layer, size_t newRate, std::map<std::string, rateSet>& all) {
    for(const auto& i : layer) {
        if (all[i].rate > newRate) {
            all[i].rate = newRate;
            recursiveWalk(all[i].friends, newRate+1, all);
        }
    }
}

int main() {
    std::string IsenKey = "Isenbaev";
    size_t sz;
    std::cin >> sz;
    std::map<std::string, rateSet> all;
    for (size_t i = 0; i < sz; ++i) {
        std::string family1, family2, family3;
        std::cin >> family1;
        std::cin >> family2;
        std::cin >> family3;
        addPerson(family1, family2, family3, all);
        addPerson(family2, family1, family3, all);
        addPerson(family3, family2, family1, all);
    }
    if (all.find(IsenKey) != all.end()) {
        all[IsenKey].rate = 0;
        recursiveWalk(all[IsenKey].friends, all[IsenKey].rate + 1, all);
    }
    for (const auto& i : all) {
        auto res = i.second.rate == 500 ? std::string("undefined") : std::to_string(i.second.rate);
        std::cout << i.first << ' ' << res << std::endl;
    }
}
