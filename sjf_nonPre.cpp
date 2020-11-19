#include <bits/stdc++.h>
#include <iomanip>
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define test(x) cout << "---------------------" << x << endl;
#define chk(x) cout << x.first << " " << x.second.first << " " << x.second.second << endl;

using namespace std;
#define pd(v)                                                                       \
    for (auto x : v)                                                                \
    {                                                                               \
        cout << x.first << " " << x.second.first << " " << x.second.second << endl; \
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

    recreate_data(rq, data);
}

bool Compare(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
    return (a.second.first < b.second.first);
}

bool Compare_data(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
    return (a.second.second < b.second.second);
}

void response_time(vector<pair<int, pair<int, int>>> &rq, vector<pair<int, pair<int, int>>> &final_data, int &tt, map<string, int> &rt)
{
    pair<int, pair<int, int>> it;
    auto found = min_element(rq.begin(), rq.end(), Compare);
    for (auto x : final_data)
    {
        if (x.second.second == found->second.second)
        {
            it = x;
            break;
        }
    }

    if (found->second.first == it.second.first)
    {
        rt[to_string(found->second.second)] = tt - found->first;
    }
    return;
}

void execute_pro(vector<pair<int, pair<int, int>>> &rq, vector<pair<int, pair<int, int>>> &data, int &tt, map<string, int> &tat)
{
    auto found = min_element(rq.begin(), rq.end(), Compare);
    tt += found->second.first;
    tat[to_string(found->second.second)] = tt - found->first;
    rq.erase(found);
}

void waiting_time(map<string, int> &wt, map<string, int> &tat, vector<pair<int, pair<int, int>>> &final_data)
{
    for (auto x : final_data)
    {
        wt[to_string(x.second.second)] = tat[to_string(x.second.second)] - x.second.first;
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
    vector<pair<int, pair<int, int>>> data, final_data;
    cout << "Enter the arrival time  and cpu burst time: " << endl;
    for (int i = 0; i < p; i++)
    {
        int at, cbt;
        cin >> at >> cbt;
        data.push_back(make_pair(at, make_pair(cbt, i + 1)));
    }
    sort(data.begin(), data.end());
    final_data = data;
    map<string, int> wt, rt, tat;
    vector<pair<int, pair<int, int>>> rq;
    int tt = 0;
    int i = 0;
    while (data.size() || rq.size())
    {
        if (i == 0)
        {
            tt += data[i].first;
            ready_q(rq, data, tt);
            i++;
        }
        response_time(rq, final_data, tt, rt);
        execute_pro(rq, data, tt, tat);
        ready_q(rq, data, tt);
        if (rq.size() == 0)
        {
            tt = data[0].first;
            ready_q(rq, data, tt);
        }
    }

    waiting_time(wt, tat, final_data);
    cout << left << setw(6) << "P" << setw(6) << "AT" << setw(6) << "CBT" << setw(6) << "WT" << setfill(' ') << setw(6) << "RT" << setfill(' ') << setw(6) << "TAT" << endl;

    auto it1 = wt.begin();
    auto it2 = rt.begin();
    auto it3 = tat.begin();
    sort(final_data.begin(), final_data.end(), Compare_data);

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
5
2 6
5 3
1 8
0 3
4 4
*/

/*
4
3 2
2 4
0 6
1 4

5
0 5
7 4
8 3
9 1
10 2

*/
