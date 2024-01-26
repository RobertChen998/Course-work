#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
void find(int i, int j, const vector<int> &chord, vector<vector<int>> &DP, vector<int> &chord_ans)
{
    // cout<<"i = "<<i<<endl;
    // cout<<"j = "<<j<<endl;
    // Base case 1
    //  Check if DP[i][j] has been computed before
    if (i >= j)
    {
        return;
    }
    // case 1
    if (chord[j] > j || chord[j] < i)
    { // cout<<"case 1"<<endl;
        // cout<<"k = "<<chord[j]<<endl;
        find(i, j - 1, chord, DP, chord_ans);
    }
    // case 2
    else if (chord[j] < j && chord[j] > i)
    { // cout<<"case 2"<<endl;
        // cout<<"k = "<<chord[j]<<endl;
        if (DP[i][j - 1] <= DP[i][chord[j] - 1] + 1 + DP[chord[j] + 1][j - 1])
        { // cout<<"in"<<endl;

            find(i, chord[j] - 1, chord, DP, chord_ans);
            chord_ans.push_back(j);
            find(chord[j] + 1, j - 1, chord, DP, chord_ans);
        }
        else
        { /*
          cout<<"out"<<endl;
          cout<<"DP[i][j - 1] = "<<DP[i][j - 1]<<endl;
          cout<<"DP[i][chord[j] - 1] = "<<DP[i][chord[j] - 1]<<endl;
          cout<<"DP[chord[j] + 1][j - 1] = "<<DP[chord[j] + 1][j - 1]<<endl;
          cout<<"j = "<<j<<endl;*/
            find(i, j - 1, chord, DP, chord_ans);
        }
    }
    // case 3
    else if (chord[j] == i)
    { // cout<<"case 3"<<endl;
        // cout<<"k = "<<chord[j]<<endl;
        //  Base case 2
        chord_ans.push_back(j);
        find(i + 1, j - 1, chord, DP, chord_ans);
    }
}

int MIS(int i, int j, const vector<int> &chord, vector<vector<int>> &DP)
{
    // cout<<"i = "<<i<<endl;
    // cout<<"j = "<<j<<endl;
    // Base case 1
    if (i >= j)
    {
        DP[i][j] = 0;
        return 0;
    }
    // Check if DP[i][j] has been computed before
    if (DP[i][j] >= 0)
    { // cout<<"DP[i][j] = "<<DP[i][j]<<endl;

        return DP[i][j];
    }
    // case 1
    if (chord[j] > j || chord[j] < i)
    { // cout<<"case 1"<<endl;
        DP[i][j] = MIS(i, j - 1, chord, DP);
    }
    // case 2
    else if (chord[j] < j && chord[j] > i)
    { // cout<<"case 2"<<endl;
        if (MIS(i, j - 1, chord, DP) < MIS(i, chord[j] - 1, chord, DP) + 1 + MIS(chord[j] + 1, j - 1, chord, DP))
        {
            DP[i][j] = MIS(i, chord[j] - 1, chord, DP) + 1 + MIS(chord[j] + 1, j - 1, chord, DP);
        }
        else
        {
            DP[i][j] = MIS(i, j - 1, chord, DP);
        }
    }
    // case 3
    else if (chord[j] == i)
    { // cout<<"case 3"<<endl;
        // Base case 2
        if (j == (i + 1))
        {

            DP[i][j] = 1;
        }
        else
        {

            DP[i][j] = MIS(i + 1, j - 1, chord, DP) + 1;
        }
    }
    return DP[i][j];
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    int N = 0;

    fstream fin(argv[1]);

    if (!fin.is_open())
    {
        cerr << "無法打開輸入文件" << endl;
        return 1;
    }

    fstream fout;
    fout.open(argv[2], ios::out);

    if (!fout.is_open())
    {
        cerr << "無法打開輸出文件" << endl;
        fin.close();
        return 1;
    }

    fin >> N; // N = 2n
    int n = N / 2;
    // cout << "n = " << n << endl;
    int start, end;
    vector<int> start_points;
    vector<int> end_points;
    while (fin >> start >> end)
    {
        start_points.push_back(start);
        end_points.push_back(end);
    }
    /*
    for (int i = 0; i < start_points.size(); i++)
    {
        cout << "Start Points: " << start_points[i] << endl;
    }

    for (int j = 0; j < end_points.size(); j++)
    {
        cout << "End Points: " << end_points[j] << endl;
    }
    */

    vector<int> chord(N);
    for (int i = 0; i < n; i++)
    {
        chord[start_points[i]] = end_points[i];
        chord[end_points[i]] = start_points[i];
    }
    /*
    for (int j = 0; j < N; j++)
    {
        cout << "point 1 = " << j << " point 2 = " << chord[j] << endl;
    }
    */

    vector<vector<int>> DP(2 * n, vector<int>(2 * n, -999));
    vector<int> chord_ans;
    int output_value = 0;
    output_value = MIS(0, 2 * n - 1, chord, DP);
    /*for (int i = 0; i < 2*n; i++)
    {
        for (int j = 0; j < 2*n; j++)
        {
            cout << DP[i][j] << '\t';
        }
        cout << endl; // 换行以显示下一行
    }*/
    /*for(int i  = 0; i < 2*n; i++)
    {
        cout<<chord_ans[i]<<endl;
    }*/
    fout << output_value << endl;
    find(0, 2 * n - 1, chord, DP, chord_ans);
    // cout<<"chord_ans.size()"<<chord_ans.size()<<endl;
    for (int i = 0; i < chord_ans.size(); i++)
    {
        fout << chord[chord_ans[i]] << ' ' << chord_ans[i] << endl;
    }
    fin.close();
    fout.close();

    return 0;
}
