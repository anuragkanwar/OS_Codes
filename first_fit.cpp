#include <bits/stdc++.h>
using namespace std;

#define deb(x) cout << #x << " = " << x << endl

#define deb2(x, y) cout << #x << " = " << x << "\n" \
                        << #y << "=" << y << endl

#define debwe(x) cout << #x << " = " << x
#define check(x) cout << "--------" << x << endl

#define fo(i, n) for (int i = 0; i < n; i++)
#define Fo(i, k, n) for (int i = k; i < n; i++)

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pll> vpl;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

#define printvec(v)       \
    for (auto x : v)      \
        cout << x << " "; \
    cout << endl

// template <typename... T>
// void read(T &... args)
// {
//     ((cin >> args), ...);
// }

// template <typename... T>
// void write(T &&... args)
// {
//     ((cout << args << " "), ...);
// }

vi block_size, process_size;
unordered_map<int, int> mapping;

void best_fit()
{
    cout << "best Fit : " << endl;

    for (auto it2 = process_size.begin(); it2 != process_size.end(); it2++)
    {
        int flag = 1;
        int ind = INT32_MAX;
        auto it3 = block_size.begin();
        for (auto it1 = block_size.begin(); it1 != block_size.end(); it1++)
        {
            if (*it1 >= *it2)
            {
                flag = 0;
                if ((*(block_size.begin() + ind) - *it2) >= (*it1 - *it2))
                {
                    ind = it1 - block_size.begin();
                    it3 = it1;
                }
            }
        }
        if (flag)
        {
            mapping[*it2] = -1;
        }
        else
        {
            mapping[*it2] = ind;
            *it3 = *it3 - *it2;
        }
    }

    for (auto x : mapping)
    {
        cout << x.first << " --> " << x.second << endl;
    }
    cout << endl;
    /*
    5
    100 500 200 300 600
    4
    212 417 112 426
    */
}
void worst_fit()
{
    cout << "Worst Fit : " << endl;

    for (auto it2 = process_size.begin(); it2 != process_size.end(); it2++)
    {
        int flag = 1;
        int ind = INT32_MIN;
        auto it3 = block_size.begin();
        for (auto it1 = block_size.begin(); it1 != block_size.end(); it1++)
        {
            if (*it1 >= *it2)
            {
                flag = 0;
                if ((*(block_size.begin() + ind) - *it2) <= (*it1 - *it2))
                {
                    ind = it1 - block_size.begin();
                    it3 = it1;
                }
            }
        }
        if (flag)
        {
            mapping[*it2] = -1;
        }
        else
        {
            mapping[*it2] = ind;
            *it3 = *it3 - *it2;
        }
    }

    for (auto x : mapping)
    {
        cout << x.first << " --> " << x.second << endl;
    }
    cout << endl;
    /*
    5
    100 500 200 300 600
    4
    212 417 112 426
    */
}
void first_fit()
{
    cout << "First Fit : " << endl;
    for (auto it2 = process_size.begin(); it2 != process_size.end(); it2++)
    {
        int flag = 1;
        for (auto it1 = block_size.begin(); it1 != block_size.end(); it1++)
        {
            if (*it1 >= *it2)
            {
                flag = 0;
                mapping[*it2] = it1 - block_size.begin();
                *it1 = *it1 - *it2;
                break;
            }
        }
        if (flag)
        {
            mapping[*it2] = -1;
        }
    }

    for (auto x : mapping)
    {
        cout << x.first << " --> " << x.second << endl;
    }

    /*
    5
    100 500 200 300 600
    4
    212 417 112 426

    */
    cout << endl;
}

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    int n, m;
    cout << "enter the number of blocks : ";
    cin >> n;
    cout << "enter the block sizes : " << endl;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        block_size.pb(temp);
    }

    cout << "enter the number of processes : ";
    cin >> m;
    cout << "enter the process sizes : " << endl;
    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        process_size.pb(temp);
    }

    /*
    first_fit();
    best_fit();
    worst_fit();
    */
}