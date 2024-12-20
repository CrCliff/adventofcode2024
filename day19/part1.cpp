#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <cassert>
#include <queue>
#include <vector>
#include <memory>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

constexpr int ALPH = 26;
constexpr int END = -2;
constexpr int FAIL = -1;

struct trie
{
    trie *children[ALPH];
    bool term = false;
    bool visited = false;
};

void reset(trie *T)
{
    T->visited = false;
    for (int i = 0; i < ALPH; i++)
    {
        if (T->children[i] != nullptr)
            reset(T->children[i]);
    }
}

void add(trie *T, std::string s)
{
    DEBUG(std::cout << s << std::endl);
    trie *curr = T;
    for (auto &c : s)
    {
        if (c == ' ')
            continue;

        const int idx = c - 'a';

        if (curr->children[idx] == nullptr)
            curr->children[idx] = new trie();

        curr = curr->children[idx];
    }

    // Mark the node as a terminal
    curr->term = true;
}

int check(trie *T, std::string s, int i)
{
    trie *curr = T;
    const int start = i;
    for (; i < s.size(); i++)
    {
        const char &c = s.at(i);
        const int idx = c - 'a';

        if (c == ' ')
            continue;

        DEBUG(std::printf("('%c' terminal: %d visited: %d) ", c, curr->term, curr->visited))

        if (curr->children[idx]->visited && curr->children[idx] != nullptr)
        {
            ;
            // curr = curr->children[idx];
        }
        else if (curr->children[idx] == nullptr)
        {
            curr->visited = true;
            DEBUG(std::cout << "ERR" << std::endl);
            if (start == 0)
                return END;
            else
                return FAIL;
        }
        else if (!curr->visited && curr->children[idx]->term)
        {
            // curr->visited = true;
            break;
        }

        curr = curr->children[idx];
    }
    DEBUG(std::cout << std::endl);
    return i + 1;
}

int main()
{
    long sum = 0;
    auto T = new trie();

    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    constexpr char del = ',';
    std::string ptrn;
    while (std::getline(ss, ptrn, del))
    {
        // DEBUG(std::cout << ptrn.substr(1, ptrn.length()) << std::endl);

        add(T, ptrn);
        for (auto &c : ptrn)
        {
            if (c == ' ')
                continue;
            // DEBUG(std::cout << c);
        }
        // DEBUG(std::cout << std::endl);
    }

    std::string chk;

    std::getline(std::cin, chk);
    for (; std::getline(std::cin, chk) && chk.size() > 0;)
    {
        reset(T);
        // DEBUG(std::cout << chk << std::endl);
        int i = 0;
        while (i != chk.size() && i != END)
        {
            i = 0;
            while (i < chk.size() && i >= 0)
            {
                i = check(T, chk, i);
                DEBUG(std::cout << i << std::endl);
            }
        }

        if (i == chk.size())
        {
            std::printf("%s -> GOOD\n", chk.c_str());
        }
        else if (i == END)
        {
            std::printf("%s -> BAD\n", chk.c_str());
        }
    }

    // 1485257
    std::cout << sum << std::endl;

    return 0;
}
