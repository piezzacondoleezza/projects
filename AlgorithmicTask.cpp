#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <cassert>

int maxKarma(int k, std::vector<std::pair<int, bool>> contests) {
    int ptrImportant = 0;
    for (size_t i = 0; i < contests.size(); ++i) {
        if (contests[i].second) {
            std::swap(contests[ptrImportant], contests[i]);
            ++ptrImportant;
        }
    }
    int lastLost = std::min(std::max(ptrImportant - k, 0), ptrImportant);
    std::nth_element(contests.begin(), contests.begin() + lastLost, contests.begin() + ptrImportant);
    int result = 0;
    for (int i = 0; i < lastLost; ++i) {
        result -= contests[i].first;
    }
    for (int i = lastLost; i < contests.size(); ++i) {
        result += contests[i].first;
    }
    return result;
}

namespace UnitTests {
    template<class T>
    void AssertEqual(T a, T b) {
        assert(a == b);
    }
    
    void TestKarma() {
        AssertEqual(maxKarma(6, {{9, 1}, {5, 1}, {8, 1}, {10, 1}, {6, 1}, {7, 1}, {2, 1}, {4, 1}, {3, 1}, {1, 1}}), 35);
        AssertEqual(maxKarma(0, {{2, 1}, {3, 1}, {4, 1}}), -9);
        AssertEqual(maxKarma(2, {{4, 1}, {3, 1}, {2, 1}, {1, 0}}), 6);
        AssertEqual(maxKarma(4, {{3, 1}, {1, 0}, {2, 1}, {4, 1}}), 10);
        AssertEqual(maxKarma(2, {{10000, 1}, {1, 1}, {1, 0}, {10000, 1}}), 20000);
    }
};




int main() {
    UnitTests::TestKarma();
    int n, k;
    std::cin >> n >> k;
    std::vector<std::pair<int, bool>> contests(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> contests[i].first >> contests[i].second;
    }
    std::cout << maxKarma(k, contests) << std::endl;
    return 0;
}
