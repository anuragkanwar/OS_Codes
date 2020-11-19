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

bool find_safe_seq(vector<pair<pair<int, int>, pair<int, int>>> &data, vi &safe, int &m)
{
    while (data.size())
    {
        int flag = 0;
        pair<pii, pii> temp;
        for (auto x : data)
        {
            temp = x;
            if (x.second.second <= m)
            {
                safe.pb(x.first.first);
                m += x.second.first;
                auto it = find(data.begin(), data.end(), temp);
                data.erase(it);
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            return flag;
        }
    }
    return 1;
}

int main()
{
    int n, m;
    cout << "enter number of prcoess : ";
    cin >> n;
    cout << "enter number of availabel resources : ";
    cin >> m;
    cout << "enter max need and allocated resources to process  : ";
    vector<pair<pair<int, int>, pair<int, int>>> data, final_data;
    for (int i = 0; i < n; i++)
    {
        int temp1, temp2;
        cin >> temp1;
        cin >> temp2;
        data.pb(mp(mp(i + 1, temp1), mp(temp2, temp1 - temp2)));
    }
    vi safe;
    int flag = find_safe_seq(data, safe, m);
    if (flag)
    {

        for (auto x : safe)
        {
            cout << "P" << x << "  ";
        }
        cout << endl;
    }
    else
    {
        cout << "safe sequence not possible";
    }
}

/*
5
4
4 1
7 2
3 1
5 0
4 3



5
4
10 4
12 3
4 0
6 3
20 9


5
4
10 3
12 3
4 0
6 3
20 9




*/
