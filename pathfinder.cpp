#include<iostream> 
#include<unordered_map> 
#include<vector>
#include<string>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;

vector<pair<int,int>> adj[100];
vector<int> college_map;
unordered_map<int, string> index_place;
unordered_map<string, int> place_index;
vector<string> places;
int n;


void connect_edge(string a, string b, int distance){
     int x = place_index[a];
     int y = place_index[b];

     adj[x].push_back({y,distance});
     adj[y].push_back({x,distance});
}

void create_map(){
    places.push_back("OAT");
    places.push_back("GYM");
    places.push_back("Health Centre");
    places.push_back("PE Ground");
    places.push_back("DJAC");
    places.push_back("DOAA Canteen");
    places.push_back("CCD");
    places.push_back("Library");
    places.push_back("Computer Centre");
    places.push_back("Hall 9");
    places.push_back("Hall 5");
    places.push_back("Visitor Hostel 1");
    places.push_back("Visitor Hostel 2");
    places.push_back("SBI Branch");
    places.push_back("Police Station");
    places.push_back("Petrol Pump");

    for(int i=0; i< places.size(); i++){
        index_place[i] = places[i];
        place_index[places[i]] = i;
    }

    n = places.size();
    connect_edge("OAT","Hall 9", 4);
    connect_edge("Visitor Hostel 1","DJAC",7);
    connect_edge("Hall 5","DJAC",7);
    connect_edge("Hall 5"," Visitor Hostel 1",5);
    connect_edge("Hall 9","GYM",5);
    connect_edge("Hall 5","Hall 9",4);
    connect_edge("GYM","Health Centre",4);
    connect_edge("OAT","Health Centre",6);
    connect_edge("GYM","PE Ground",3);
    connect_edge("Hall 5","PE Ground",5);
    connect_edge("Hall 5","GYM",4);
    connect_edge("Hall 5","Library",6);
    connect_edge("Library","DOAA Canteen",3);
    connect_edge("Library","Computer Centre",2);
    connect_edge("DJAC","Computer Centre",4);
    connect_edge("Computer Centre","SBI Branch",4);
    connect_edge("SBI Branch","Petrol Pump",3);
    connect_edge("Police Station","Petrol Pump",6);
    connect_edge("SBI Branch","PE Ground",5);
    connect_edge("Health Centre","Visitor Hostel 2",3);
    connect_edge("Visitor Hostel 2","PE Ground",3);
    connect_edge("DOAA Canteen","DJAC",2);
    connect_edge("CCD","Library",1);
    return;
}

void dfs(int source, int parent, vector<bool> &vis){
    vis[source] =1;
    college_map.push_back(source);

    for(auto it : adj[source]){
        int node = it.first;

        if(!vis[node]){
            dfs(node, source , vis);
        }
    }
}

void display_places(){
    for(int i=0;i<places.size(); i++){
        cout << i+1 << ". " << places[i] << endl;
    }
}

void display_map(){
    vector<bool>vis(n);
    dfs(0,-1,vis);
    for(int i=0;i<college_map.size();i++){
        if(i!=college_map.size()-1){
            cout << index_place[college_map[i]]<<"  -->  ";
        }
        else{
            cout << index_place[college_map[i]];
        }
    }
    cout<<endl;
}

int shortest_path(int source, int destination){
    vector<int> dist(n,INT_MAX);
    dist[source] =0;
    priority_queue<pair<int,int>, vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({source,0});

    while(!pq.empty()){
        int node = pq.top().first;
        int len = pq.top().second;
        pq.pop();

        for(auto it : adj[node]){
            int adjNode = it.first;
            int edge = it.second;

            if(len + edge < dist[adjNode]){

                dist[adjNode] = len + edge;
                pq.push({adjNode,dist[adjNode]});
            }
        }
    }

    return dist[destination];

}

void bfs(int source, vector<int> parent[]){
    vector<int> dist(n,1e9);
    queue<int> q;
    parent[source].clear();
    parent[source].push_back(-1);

    dist[source] = 0;
    q.push(source);

    while(!q.empty()){
        int node = q.front();
        q.pop();

        for(auto it : adj[node]){
            int adjNode = it.first;
            int edge = it.second;

            if(dist[adjNode] > dist[node] + edge){
                dist[adjNode] = dist[node] + edge;
                parent[adjNode].clear();
                parent[adjNode].push_back(node);
                q.push(adjNode);
            }
            else if(dist[adjNode] == dist[node] + edge){
                parent[adjNode].push_back(node);
            }
        }
        
    }
}

void find_path(vector<int> parent[], vector<vector<int>> &paths, vector<int> path, int destination){
    if(destination == -1){
        paths.push_back(path);
        return;
    }
    path.push_back(destination);  // Add the destination to the path
    for(auto it : parent[destination]){
        find_path(parent, paths, path, it);
    }
}


void print_path(int source, int destination){
    vector<vector<int>>paths;
    vector<int>path;
    vector<int>parent[n];

    bfs(source, parent);
    find_path(parent, paths, path, destination);

    if (!paths.empty()) {
    reverse(paths[0].begin(), paths[0].end());
    for(int i=0; i<paths[0].size()-1; i++){
        cout << index_place[paths[0][i]] << " --> ";
    }
    
    cout << index_place[paths[0][paths[0].size()-1]] << endl;
}

}



int main(){
    create_map();

    cout << "WELCOME" << endl;
    while(true){
        cout << "CHOOSE SERVICE" << endl;
        cout << "1 -> PLACE CODE "<<endl;
        cout << "2 -> MAP " << endl;
        cout << "3 -> GET SHORTEST DISTANCE AND PATH " << endl;
        cout << "4 -> BACK " << endl;
       

        int input;
        cin >> input;
        
        if(input == 1){
           display_places(); 
        }
        else if(input == 2){
            display_map();
        }
        else if(input == 3){
            display_places();
            cout << "FROM (PLACE CODE)" << endl;
            cout << "TO (PLACE CODE)" << endl;  
            int x ,y;
            cin >> x >> y ;
            x-- ; y--;
            int answer =  shortest_path(x,y);
            cout << "SHOTREST DISTANCE IS " << answer << endl;
            cout << "PATH "<< endl;
            print_path(x,y);
        }
        else{
            break;
        }
        
            
            
        
    }
}
