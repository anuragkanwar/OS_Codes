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
//**********************************************************************************************************//

vi Type;
void Format(int m)
{
    Type.resize(m);
}

int main()
{

    int n, m;
    cout << "Enter number of processes : ";
    cin >> n;
    cout << "Enter number of resource type : ";
    cin >> m;

    vector<pair<int, pair<vi, vi>>> Data, Org_data;
    for (int i = 0; i < n; i++)
    {
        vi temp1, temp2;
        cout << "enter allocation for process " << i + 1 << " in space seperated format : ";
        for (int j = 0; j < m; j++)
        {
            int temp3;
            cin >> temp3;
            temp1.pb(temp3);
        }
        cout << "enter Max for process " << i + 1 << " in space seperated format : ";
        for (int j = 0; j < m; j++)
        {
            int temp3;
            cin >> temp3;
            temp2.pb(temp3);
        }

        Data.push_back(mp(i, mp(temp1, temp2)));
    }
    Org_data = Data;
    vi avl;
    cout << "Enter availabel resources in space seperated format : ";
    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        avl.pb(temp);
    }

    vvi Need;
    for (auto x : Data)
    {
        vi temp;
        auto it1 = x.second.first.begin();
        auto it2 = x.second.second.begin();

        while (it1 != x.second.first.end())
        {
            temp.pb(*it2 - *it1);
            it1++;
            it2++;
        }
        Need.pb(temp);
    }

    vi seq;
    while (Data.size() != 0)
    {
        int count = -1;
        for (auto x : Need)
        {
            count++;
            auto it1 = x.begin();
            auto it2 = avl.begin();
            int flag = 1;
            while (it2 != avl.end())
            {
                if (*it1 > *it2)
                {
                    flag = 0;
                    break;
                }
            }

            if (flag)
            {
                it1 = x.begin();
                it2 = avl.begin();
                while (it2 != avl.end())
                {
                    *it2 = *it2 + *it1;
                }
                Data.erase(Data.begin() + count);
                Need.erase(Need.begin() + count);
            }
        }
    }
}