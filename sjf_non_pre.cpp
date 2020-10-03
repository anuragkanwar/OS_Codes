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

pair<int, pair<int, int>> subroutine_sjf(vector<pair<int, pair<int, int>>> &v)
{
    pair<int, pair<int, int>> temp;
    int min = INT32_MAX;
    for (auto x : v)
    {
        if (min >= x.second.first)
        {
            min = x.second.first;
            temp = x;
        }
    }
    return temp;
}

pair<int, pair<int, int>> compute(vector<int> &wt, vector<int> &rt, vector<int> &tat, int &tt, vector<pair<int, pair<int, int>>> &v)
{
    pair<int, pair<int, int>> temp = subroutine_sjf(v);
    if (tt < temp.first)
    {
        tt = temp.first;
    }
    wt.push_back(tt - temp.first);
    rt.push_back(tt - temp.first);
    tt += temp.second.first;
    tat.push_back(tt - temp.first);
    return temp;
}

void find(vector<pair<int, pair<int, int>>> &data, pair<int, pair<int, int>> del)
{
    auto pos = data.begin();
    for (auto x : data)
    {
        if (x == del)
        {
            data.erase(pos);
            break;
        }
        pos++;
    }
    cout << endl;
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
    vector<int> wt, rt, tat;
    int tt = 0;
    for (int i = 0; i < p; i++)
    {
        if (i == 0)
        {
            tt = data[i].first;
        }
        vector<pair<int, pair<int, int>>> temp;
        for (auto x : data)
        {
            if (x.first <= tt)
            {
                temp.push_back(x);
            }
            else
            {
                break;
            }
        }

        pair<int, pair<int, int>> del = compute(wt, rt, tat, tt, temp);
        final_data.push_back(del);
        find(data, del);
    }

    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < p; i++)
    {
        sum1 += wt[i];
        sum2 += tat[i];
    }
    double avg_wt = sum1 / p;
    double avg_tat = sum2 / p;

    cout << left << setw(6) << "P" << setw(6) << "AT" << setw(6) << "CBT" << setw(6) << "WT" << setfill(' ') << setw(6) << "RT" << setfill(' ') << setw(6) << "TAT" << endl;
    for (int i = 0; i < p; i++)
    {
        cout << left << setw(6) << final_data[i].second.second << setw(6) << final_data[i].first << setw(6) << final_data[i].second.first << setw(6) << wt[i] << setfill(' ') << setw(6) << rt[i] << setfill(' ') << setw(6) << tat[i] << endl;
    }

    cout << endl;
    cout << "Average waiting time is : " << avg_wt << endl;
    cout << "Average turn around time is : " << avg_tat << endl;
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
*/
