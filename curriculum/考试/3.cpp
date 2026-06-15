#include <array>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

struct Card
{
    int rk;
    int col;
};

static constexpr array<const char *, 13> kRanks{
    "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
static constexpr array<const char *, 4> kSuits{
    "Hearts", "Diamonds", "Clubs", "Spades"};

ostream &operator<<(ostream &os, const Card &c)
{
    os << kRanks[c.rk] << " of " << kSuits[c.col];
    return os;
}

bool operator<(const Card &a, const Card &b)
{
    return (a.rk == b.rk) ? (a.col < b.col) : (a.rk < b.rk);
}

int main()
{
    random_device rd;
    mt19937 gen(rd());

    vector<Card> deck;
    deck.reserve(52);
    for (int col = 0; col < 4; ++col)
    {
        for (int rk = 0; rk < 13; ++rk)
        {
            deck.push_back({rk, col});
        }
    }

    shuffle(deck.begin(), deck.end(), gen);

    vector<Card> cards(deck.begin(), deck.begin() + 5);

    for (const auto &c : cards)
    {
        cout << c << '\n';
    }

    sort(cards.begin(), cards.end(), less<Card>());

    cout << '\n';
    for (const auto &c : cards)
    {
        cout << c << '\n';
    }
    return 0;
}
