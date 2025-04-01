#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const  int inf=500;
int main() {

	return 0;
}
vector<int> dijie(vector<vector<int> > G, int source) {
	int n = G.size();
	vector<int> dis(n, inf);
	vector<bool> flag(n, false);
	int node = -1;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (!flag[j] && node == -1 || dis[j] < dis[node]) {
				node = j;
			}
		}

		for (int j = 0; j < n; j++) {
			dis[j] = min(dis[j], dis[node] + G[node][j]);
		}
		flag[node] = true;
	}
	return dis;
}

const int inf=500;
void djst(vector<vector<int>> G,int source) {
	int n = G.size();
	vector<int> dis(n, inf);
	vector<bool> flag(n, false);
	int node = -1;

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (!flag[j]&&node == -1 || dis[j] < dis[node])
			node = j;		
		}
		for (int j = 0; j < n; j++) {
			dis[j] = min(dis[j], dis[node] + G[node][j]);
		}
		flag[i] = true;
	}
	return dis;
}