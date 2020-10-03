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

void print_time(map<string, int> &t)
{
    for (auto x : t)
    {
        cout << x.first << "-->" << x.second << endl;
    }
    cout << endl;
}

void recreate_data(vector<pair<int, pair<int, int>>> &rq, vector<pair<int, pair<int, int>>> &data)
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

void ready_q(vector<pair<int, pair<int, int>>> &rq, vector<pair<int, pair<int, int>>> &data, int &tt)
{
    if (data.size() == 0)
    {
        return;
    }
    for (auto x : data)
    {
        if (tt >= x.first)
        {
            rq.push_back(x);
        }
    }
    if (rq.size() == 0)
    {
        tt = data.front().first;
        for (auto x : data)
        {
            if (tt >= x.first)
            {
                rq.push_back(x);
            }
        }
    }

    recreate_data(rq, data);
}

void waiting_time(map<string, int> &wt, map<string, int> &tat, vector<pair<int, pair<int, int>>> &final_data)
{
    for (auto x : final_data)
    {
        wt[to_string(x.second.second)] = tat[to_string(x.second.second)] - x.second.first;
    }
}

void response_time(vector<pair<int, pair<int, int>>> &rq, vector<pair<int, pair<int, int>>> &final_data, int &tt, map<string, int> &rt)
{
    // auto it = find(final_data.begin(), final_data.end(), x);
    pair<int, pair<int, int>> it;

    for (auto x : final_data)
    {

        if (x.second.second == rq.front().second.second)
        {
            it = x;
            break;
        }
    }

    if (rq.front().second.first == it.second.first)
    {
        rt[to_string(rq.begin()->second.second)] = tt - rq.front().first;
    }

    return;
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
    int p, tq;
    cin >> p;
    vector<pair<int, pair<int, int>>> data, final_data;
    map<string, int> wt, rt, tat;
    cout << "Enter the arrival time  and cpu burst time: " << endl;
    for (int i = 0; i < p; i++)
    {
        int at, cbt;
        cin >> at >> cbt;
        data.push_back(make_pair(at, make_pair(cbt, i + 1)));
    }

    final_data = data;
    cout << "Enter time quantam : ";
    cin >> tq;

    sort(data.begin(), data.end());
    vector<pair<int, pair<int, int>>> rq;
    int sum = 1;
    int tt = 0;
    int i = 0;
    while (data.size() || rq.size())
    {
        if (i == 0)
        {
            tt = data[i].first;
            i++;
        }
        ready_q(rq, data, tt);
        response_time(rq, final_data, tt, rt);
        tt += min(tq, (rq.front()).second.first);
        ready_q(rq, data, tt);
        if (rq.front().second.first - tq > 0)
        {
            pair<int, pair<int, int>> temp = rq.front();
            temp.second.first -= tq;
            rq.erase(rq.begin());
            rq.push_back(temp);
        }
        else
        {
            tat[to_string(rq.begin()->second.second)] = tt - rq.begin()->first;
            rq.erase(rq.begin());
        }
    }
    waiting_time(wt, tat, final_data);

    cout << left << setw(6) << "P" << setw(6) << "AT" << setw(6) << "CBT" << setw(6) << "WT" << setfill(' ') << setw(6) << "RT" << setfill(' ') << setw(6) << "TAT" << endl;

    auto it1 = wt.begin();
    auto it2 = rt.begin();
    auto it3 = tat.begin();

    for (int i = 0; i < p; i++)
    {
        cout << left << setw(6) << final_data[i].second.second << setw(6) << final_data[i].first << setw(6) << final_data[i].second.first << setw(6) << it1->second << setfill(' ') << setw(6) << it2->second << setfill(' ') << setw(6) << it3->second << endl;
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
6
0 250
50 170
130 75
190 100
210 130
350 50
100


5
0 5
1 3
2 1
3 2
4 3
2

4
0 5
7 10
8 2
9 4
2

*/
