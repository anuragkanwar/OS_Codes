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

vi need_matrix(vi &allocated, vi &max)
{
    vi temp;
    auto it1 = allocated.begin();
    auto it2 = max.begin();

    while (it1 != allocated.end())
    {
        temp.pb(abs(*it1 - *it2));
        it1++;
        it2++;
    }
    return temp;
}

bool check_req(vi &v1, vi &v2)
{
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    int flag = 1;
    while (it1 != v1.end())
    {
        if (*it1 > *it2)
        {
            flag = 0;
            break;
        }
        it1++;
        it2++;
    }
    return flag;
}

void extend_avl(vi &avl, vi &allocated)
{
    auto it1 = avl.begin();
    auto it2 = allocated.begin();
    while (it1 != avl.end())
    {
        *it1 += *it2;
        it1++;
        it2++;
    }
}

bool safe_seq(vector<pair<pair<int, vi>, pair<vi, vi>>> &data, vi &avl, vi &seq)
{
    while (data.size())
    {
        int flag = 0;
        pair<pair<int, vi>, pair<vi, vi>> temp;
        for (auto x : data)
        {
            temp = x;
            if (check_req(x.second.second, avl))
            {
                seq.pb(x.first.first);
                extend_avl(avl, x.first.second);
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
    cout << "Enter number of processes : ";
    cin >> n;
    cout << "Enter number of resource type : ";
    cin >> m;

    vector<pair<pair<int, vi>, pair<vi, vi>>> Data, Org_data;
    for (int i = 0; i < n; i++)
    {
        vi temp1, temp2, temp5;
        cout << "enter allocated process " << i + 1 << " in space seperated format : ";
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
        temp5 = need_matrix(temp1, temp2);
        Data.push_back(mp(mp(i, temp1), mp(temp2, temp5)));
    }

    Org_data = Data;
    vi avl, seq;
    cout << "Enter availabel resources in space seperated format : ";
    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        avl.pb(temp);
    }
    int flag = safe_seq(Data, avl, seq);
    if (flag)
    {
        for (auto x : seq)
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
4
3
0 1 2
2 2 2
6 0 0
8 4 1
4 4 5
5 5 5
3 3 2
5 4 2
1 1 0






*/