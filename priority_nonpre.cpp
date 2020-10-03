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

// {
//     for (auto x : data)
//     {
//         cout << x.first.first << " " << x.first.second << " " << x.second.first << " " << x.second.first << " " << endl;
//     }
// }

void recreate_data(vector<pair<pair<int, int>, pair<int, int>>> &rq, vector<pair<pair<int, int>, pair<int, int>>> &data)
{
    for (auto x : rq)
    {
        auto it = find(data.begin(), data.end(), x);
        if (it != data.end())
        {
            data.erase(it);
        }
    }
}

void ready_q(vector<pair<pair<int, int>, pair<int, int>>> &rq, vector<pair<pair<int, int>, pair<int, int>>> &data, int &tt)
{
    if (data.size() == 0)
    {
        return;
    }
    for (auto x : data)
    {
        if (tt >= x.first.first)
        {
            rq.push_back(x);
        }
    }
    if (rq.size() == 0)
    {
        tt = data.front().first.first;
        for (auto x : data)
        {
            if (tt >= x.first.first)
            {
                rq.push_back(x);
            }
        }
    }

    recreate_data(rq, data);
}

bool Compare(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
    return (a.second.first < b.second.first);
}

bool Compare_data(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
    return (a.second.second < b.second.second);
}

void execute_pro(vector<pair<pair<int, int>, pair<int, int>>> &rq, vector<pair<pair<int, int>, pair<int, int>>> &data, int &tt, map<string, int> &tat, map<string, int> &rt)
{
    auto found = min_element(rq.begin(), rq.end(), Compare);
    rt[to_string(found->second.second)] = tt - found->first.first;
    tt += found->first.second;
    tat[to_string(found->second.second)] = tt - found->first.first;
    rq.erase(found);
}

void waiting_time(map<string, int> &wt, map<string, int> &tat, vector<pair<pair<int, int>, pair<int, int>>> &final_data)
{
    for (auto x : final_data)
    {
        wt[to_string(x.second.second)] = tat[to_string(x.second.second)] - x.first.second;
    }
}

float avg(map<string, int> &t)
{
    float sum = 0;
    for (auto x : t)
    {
        sum += x.second;
    }
    return (sum / t.size());
}

int main()
{
    cout << "Enter the number of process : ";
    int p;
    cin >> p;
    vector<pair<pair<int, int>, pair<int, int>>> data, final_data;
    cout << "Enter in the order of arrival time, cpu burst time, priority: " << endl;
    for (int i = 0; i < p; i++)
    {
        int at, cbt, pr;
        cin >> at >> cbt >> pr;
        data.push_back(make_pair(make_pair(at, cbt), make_pair(pr, i + 1)));
    }
    final_data = data;
    sort(data.begin(), data.end());
    map<string, int> wt, rt, tat;
    vector<pair<pair<int, int>, pair<int, int>>> rq;
    int i = 0;
    int tt = 0;
    while (data.size() || rq.size())
    {
        if (i == 0)
        {
            tt += data[i].first.first;
            i++;
        }
        ready_q(rq, data, tt);
        execute_pro(rq, data, tt, tat, rt);
        ready_q(rq, data, tt);
    }
    waiting_time(wt, tat, final_data);

    cout << left << setw(6) << "P" << setw(6) << "AT" << setw(6) << "CBT" << setw(6) << "Prio" << setw(6) << "WT" << setfill(' ') << setw(6) << "RT" << setfill(' ') << setw(6) << "TAT" << endl;

    auto it1 = wt.begin();
    auto it2 = rt.begin();
    auto it3 = tat.begin();
    sort(final_data.begin(), final_data.end(), Compare_data);

    for (int i = 0; i < p; i++)
    {
        cout << left << setw(6) << final_data[i].second.second << setw(6) << final_data[i].first.first << setw(6) << final_data[i].first.second << setw(6) << final_data[i].second.first << setfill(' ') << setw(6) << it1->second << setfill(' ') << setw(6) << it2->second << setfill(' ') << setw(6) << it3->second << endl;
        it1++;
        it2++;
        it3++;
    }
    cout << endl;
    cout << "Average waiting time is : " << avg(wt) << endl;
    cout << "Average turn around time is : " << avg(tat) << endl;
    cout << "Total up time of machine is : " << tt << endl;
}

/*
5
0 4 2
1 3 3
2 1 4
3 5 5
4 2 5

5
0 4 2
1 3 3
2 1 2
3 5 1
4 2 1


4
0 7 2
2 2 1
4 1 3
6 5 4

*/