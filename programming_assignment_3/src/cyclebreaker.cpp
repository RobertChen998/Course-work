#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> make_set(int total_vertex)
{

    vector<int> vertices;
    for (int i = 0; i < total_vertex; i++)
    {
        vertices.push_back(i);
    }

    return vertices;
}

vector<int> Union(int u, int v, int total_vertex, vector<int> &disjoint_set)
{

    int head_u = disjoint_set[u];
    int head_v = disjoint_set[v];
    for (int i = 0; i < total_vertex; i++)
    {
        if (disjoint_set[i] == head_u)
        {
            disjoint_set[i] = head_v;
        }
    }

    return disjoint_set;
}

// Max heapify
void MaxHeapify(vector<int> &data, int root, int heapSize, vector<int> &start_points, vector<int> &end_points)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    int largest = 0;
    if (l <= heapSize - 1 && data[l] > data[root])
    {
        largest = l;
    }
    else
    {
        largest = root;
    }
    if (r <= heapSize - 1 && data[r] > data[largest])
    {
        largest = r;
    }
    if (largest != root)
    {
        swap(data[root], data[largest]);
        swap(start_points[root], start_points[largest]);
        swap(end_points[root], end_points[largest]);
        MaxHeapify(data, largest, heapSize, start_points, end_points);
    }
}

// Build max heap
void BuildMaxHeap(vector<int> &data, int heapSize, vector<int> &start_points, vector<int> &end_points)
{
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = (data.size() / 2) - 1; i >= 0; i--)
    {
        MaxHeapify(data, i, heapSize, start_points, end_points);
    }
}

// Heap sort method
vector<int> HeapSort(vector<int> &data, int heapSize, vector<int> &start_points, vector<int> &end_points)
{
    int t_e = heapSize;
    // Build Max-Heap
    BuildMaxHeap(data, heapSize, start_points, end_points);
    vector<int> wgt_str_end(3 * t_e, 0);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
        swap(data[0], data[i]);
        swap(start_points[0], start_points[i]);
        swap(end_points[0], end_points[i]);
        heapSize--;
        MaxHeapify(data, 0, heapSize, start_points, end_points);
    }
    for (int i = 0; i < t_e; i++)
    {
        wgt_str_end[i] = data[i];
    }

    for (int i = 0; i < t_e; i++)
    {
        wgt_str_end[i + t_e] = start_points[i];
    }

    for (int i = 0; i < t_e; i++)
    {
        wgt_str_end[i + 2 * t_e] = end_points[i];
    }

    return wgt_str_end;
}

bool DFS_visit(int u , vector<vector<int>> &adj, int t_v , int t_e , vector<int> &color)
{
    color[u] = 1 ; // 1 -> Gray
    for(int i = 0 ; i < adj[u].size() ; i++)
    {
        
        if(color[adj[u][i]] == 1)
        {
            return true;

        }
        else if(color[adj[u][i]] == 0 &&  DFS_visit(adj[u][i],adj,t_v,t_e,color) == true )
        {
           return true;
        }

    }
    color[u] = 2 ; // 2 -> Black
        
    return false;



}



bool DFS(vector<int> &str, vector<int> &end, int extra_str, int extra_end , int t_v , int t_e)
{
    vector<vector<int> > adj(t_v);
    for (int i = 0 ; i < str.size() ; i++)
    {
        adj[str[i]].push_back(end[i]);
    }
    adj[extra_str].push_back(extra_end);
    
    vector<int> color(t_v,0);
    

    return  DFS_visit(extra_str, adj , t_v,t_e,color);
    
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

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

    char type;

    fin >> type;

    int start, end, weight;
    int t_v, t_e;
    vector<int> start_points;
    vector<int> end_points;
    vector<int> weights;
    fin >> t_v >> t_e;
    while (fin >> start >> end >> weight)
    {
        start_points.push_back(start);
        end_points.push_back(end);
        weights.push_back(weight);
    }
    for (int i = 0; i < t_e; i++)
    {
        weights[i] = (-1) * weights[i];
    }
    /*
    cout<<"Total vertex = "<<t_v<<endl;
    cout<<"Total edges = " <<t_e<<endl;

    for (int i = 0; i < start_points.size(); i++)
    {
        cout << "Start Points: " << start_points[i] << endl;
    }

    for (int j = 0; j < end_points.size(); j++)
    {
        cout << "End Points: " << end_points[j] << endl;
    }

    for (int k = 0; k < weights.size(); k++)
    {
        cout << "Weights: " << weights[k] << endl;
    }
    */
    vector<int> heap_sort_array = HeapSort(weights, t_e, start_points, end_points);

    /*
    for (int i = 0 ; i < 3*t_e ; i++)
    {
        cout<<heap_sort_array[i]<<endl;

    }*/

    vector<int> edge_sorted(t_e, 0);
    vector<int> str_sorted(t_e, 0);
    vector<int> end_sorted(t_e, 0);
    for (int i = 0; i < t_e; i++)
    {
        edge_sorted[i] = heap_sort_array[i];
        str_sorted[i] = heap_sort_array[i + t_e];
        end_sorted[i] = heap_sort_array[i + 2 * t_e];
    }

    // Kruskal's Algorithm
    int total_deserted = 0;

    vector<int> disjoint_set = make_set(t_v);
    vector<int> str_deserted;
    vector<int> end_deserted;
    vector<int> edge_deserted;
    vector<int> str_reserved;
    vector<int> end_reserved;
    for (int i = 0; i < t_e; i++)
    {
        if (disjoint_set[str_sorted[i]] != disjoint_set[end_sorted[i]])
        {
            // cout<<"fsjdofis"<<endl;
            Union(str_sorted[i], end_sorted[i], t_v, disjoint_set);
            str_reserved.push_back(str_sorted[i]);
            end_reserved.push_back(end_sorted[i]);
        }
        else
        {
            total_deserted = total_deserted + edge_sorted[i];
            /*
            cout<<"total_deserted = " << total_deserted<<endl;
            cout<<"edge_sorted = " <<edge_sorted[i]<<endl;
            cout<<"str_sorted = "<<str_sorted[i]<<endl;
            cout<<"end_sorted = " <<end_sorted[i]<<endl;
            */
            str_deserted.push_back(str_sorted[i]);
            end_deserted.push_back(end_sorted[i]);
            edge_deserted.push_back((-1) * edge_sorted[i]);
        }
    }
    if (type == 'u')
    {
        total_deserted = total_deserted * (-1);
        fout << total_deserted << endl;
        for (int i = 0; i < edge_deserted.size(); i++)
        {
            fout << str_deserted[i] << ' ' << end_deserted[i] << ' ' << edge_deserted[i] << ' ' << endl;
        }
    }
    /*
    for(int i = 0 ; i < t_v ; i++)
    {
        cout<<disjoint_set[i]<<endl;
    }*/
    else
    {

        total_deserted = 0;
        for (int i = 0; i <edge_deserted.size(); i++)
        {
            if (edge_deserted[i] > 0 )
            {
                if(DFS(str_reserved,end_reserved, str_deserted[i], end_deserted[i] , t_v , t_e ) == false)
                {
                    
                    str_reserved.push_back(str_deserted[i]);
                    end_reserved.push_back(end_deserted[i]);
                    edge_deserted[i] = -1000;
                }
                
            }
        }
        for (int i = 0; i < edge_deserted.size(); i++)
        {
            if (edge_deserted[i] != -1000)
            {
                total_deserted = total_deserted + edge_deserted[i];
            }
        }
        fout << total_deserted << endl;
        for (int i = 0; i < edge_deserted.size(); i++)
        {
            if (edge_deserted[i] != -1000)
            {
                fout << str_deserted[i] << ' ' << end_deserted[i] << ' ' << edge_deserted[i] << ' ' << endl;
            }
        }
    }

    fin.close();
    fout.close();

    return 0;
}
