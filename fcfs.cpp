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
#define pob pop_back
#define mp make_pair

#define ll long long
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pll> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

#define printvec(v)       \
    for (auto x : v)      \
        cout << x << " "; \
    cout << endl

template <typename... T>
void read(T &... args)
{
    ((cin >> args), ...);
}

template <typename... T>
void write(T &&... args)
{
    ((cout << args << " "), ...);
}

int main()
{

    int n;
    cout << "enter number of process : ";
    cin >> n;
    vector<pair<pair<int, int>, int>> v;
    for (int i = 0; i < n; i++)
    {
        int temp1, temp2;
        cout << "Enter start time and burst time for process " << i + 1 << " spearated by space :";
        cin >> temp1 >> temp2;
        v.pb(mp(mp(temp1, temp2), i + 1));
    }

    sort(v.begin(), v.end());

    vi ans;
    int tt = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            ans.pb(0);
            tt += v[i].first.first;
        }
        else
        {
            if (tt >= v[i].first.first)
            {
                ans.pb(tt - v[i].first.first);
            }
            else
            {
                tt = v[i].first.first;
                ans.pb(0);
            }
        }

        tt += v[i].first.second;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "For P" << v[i].second << " wait time is : " << ans[i] << endl;
    }
    cout << "Total time elapsed by System : " << tt << endl;
}

// Roll No : 102083041
//  Name : Anurag Kanwar
// batch : 2COE18