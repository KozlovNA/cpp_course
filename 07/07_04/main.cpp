#include <algorithm>
#include <vector>
#include <random>
#include <gtest/gtest.h>

struct Player {
    std::size_t eff = 0;
    std::size_t num = 0;
    
    bool operator==(const Player& other) const {
        return eff == other.eff && num == other.num;
    }
};

bool operator<(Player const& lhs, Player const& rhs) {
    return lhs.eff < rhs.eff;
}

template<typename T>
void order(std::vector<T> &vector, std::size_t left, std::size_t right) {
    for (auto i = left + 1; i <= right; ++i) {
        for (auto j = i; j > left; --j) {
            if (vector[j] < vector[j - 1]) {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

static std::random_device rd;
static std::mt19937 gen(rd());

int generateRandomPivot(int low, int high) {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

template<typename T>
void quick_sort(std::vector<T> &arr, int low, int high) {
    if (low < high) {
        if (high - low + 1 <= 16) {
            order(arr, low, high);
            return;
        }
        
        int pivotIndex = generateRandomPivot(low, high);
        T pivotValue = arr[pivotIndex];

        std::swap(arr[pivotIndex], arr[high]);

        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivotValue) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);

        quick_sort(arr, low, i);
        quick_sort(arr, i + 2, high);
    }
}

template<typename T>
void sort_players(std::vector<T>& vec) {
    if (vec.empty()) return;
    quick_sort(vec, 0, static_cast<int>(vec.size() - 1));
}


TEST(HybridSortTest, HandlesSmallVector) {
    std::vector<Player> players = { {10, 1}, {5, 2}, {8, 3}, {1, 4}, {5, 5} };
    
    sort_players(players);
    
    EXPECT_TRUE(std::is_sorted(players.begin(), players.end()));
    EXPECT_EQ(players.size(), 5);
    EXPECT_EQ(players[0].eff, 1);
    EXPECT_EQ(players[4].eff, 10);
}

TEST(HybridSortTest, HandlesLargeVector) {
    const size_t size = 1000;
    std::vector<Player> players(size);
    
    std::uniform_int_distribution<> dist(0, 10000);
    for (size_t i = 0; i < size; ++i) {
        players[i].num = i;
        players[i].eff = dist(gen);
    }

    sort_players(players);

    EXPECT_TRUE(std::is_sorted(players.begin(), players.end()));
    EXPECT_EQ(players.size(), size);
}

TEST(HybridSortTest, HandlesEmptyVector) {
    std::vector<Player> players;
    sort_players(players);
    EXPECT_TRUE(players.empty());
}

TEST(HybridSortTest, HandlesSingleElement) {
    std::vector<Player> players = { {42, 1} };
    sort_players(players);
    EXPECT_EQ(players.size(), 1);
    EXPECT_EQ(players[0].eff, 42);
}

TEST(HybridSortTest, HandlesSortedVector) {
    std::vector<Player> players = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
    sort_players(players);
    EXPECT_TRUE(std::is_sorted(players.begin(), players.end()));
    EXPECT_EQ(players[0].eff, 1);
    EXPECT_EQ(players[4].eff, 5);
}

TEST(HybridSortTest, HandlesReverseSortedVector) {
    std::vector<Player> players = { {5, 1}, {4, 2}, {3, 3}, {2, 4}, {1, 5} };
    sort_players(players);
    EXPECT_TRUE(std::is_sorted(players.begin(), players.end()));
    EXPECT_EQ(players[0].eff, 1);
    EXPECT_EQ(players[4].eff, 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
