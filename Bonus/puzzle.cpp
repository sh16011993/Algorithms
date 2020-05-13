/* 
References:
1) https://github.com/ani94/8-puzzle-solver-cpp/blob/master/8puzzle.cpp
2) https://stackoverflow.com/questions/36108269/does-8-puzzle-solvability-rules-work-for-any-goal-state
*/

#include<bits/stdc++.h>
using namespace std;

typedef struct position{
	int x; 
	int y;
}pos;

// Create an empty graph with initial state
vector<vector<int>> init(3, vector<int>(3));
// Create a filled graph for final state which is fixed
vector<vector<int>> final(3, vector<int>(3));

struct Cmp{
	bool operator()(const pair<vector<vector<int>>, int> &a, const pair<vector<vector<int>>, int> &b) const{
		// Fitness functions values
		int f1, f2;
			
		vector<vector<int>> state1 = a.first;
		vector<vector<int>> state2 = b.first;
		
		//Creating temporary arrays to hold the values from both states
		pos s[9], f[9];
		
		// Fill the array for the final state
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				if(final[i][j] == -1){
					f[0].x = i;
					f[0].y = j;
				}
				else{
					f[final[i][j]].x = i;
					f[final[i][j]].y = j;
				}
			}
		}
		
		//Now, calculate the Manhatten distance of state1 from goal state
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				if(state1[i][j] == -1){
					s[0].x = i;
					s[0].y = j;
				}
				else{
					s[state1[i][j]].x = i;
					s[state1[i][j]].y = j;	
				}
			}
		}
		//Now, find the manhatten distance
		int dis = 0;
		for(int i=0; i<9; i++){
			dis+=(abs(s[i].x-f[i].x) + abs(s[i].y-f[i].y));
		}
		f1 = a.second + dis;
		//Now, calculate the Manhatten distance of state2 from goal state
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				if(state2[i][j] == -1){
					s[0].x = i;
					s[0].y = j;
				}
				else{
					s[state2[i][j]].x = i;
					s[state2[i][j]].y = j;	
				}
			}
		}
		//Now, find the manhatten distance
		dis = 0;
		for(int i=0; i<9; i++){
			dis+=(abs(s[i].x-f[i].x) + abs(s[i].y-f[i].y));
		}
		f2 = b.second + dis;
			
		//Compare and return the smaller value
		return f1>f2;
	}
};

void tracepath(vector<vector<int>> state, map<vector<vector<int>>, vector<vector<int>>> &m){
	vector<vector<int>> parent;
	if(m.find(state) != m.end()){
		parent = m[state];
		//Recursively call till root state is reached
		tracepath(parent, m);
	}
	//Print
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(state[i][j] == -1)
				cout<<"_"<<" ";
			else
				cout<<state[i][j]<<" ";
		}
		cout<<endl;
	}			
	cout<<endl;
}

void astar(vector<vector<int>> &init, vector<vector<int>> &final, int heuristic){
	//Hashmap of visited states to keep their track
	map<vector<vector<int>>, bool> visited;
	
	//Parent's hashmap to keep track of the parent of a state
	map<vector<vector<int>>, vector<vector<int>>> m;
	
	if(heuristic == 0){
		queue<pair<vector<vector<int>>, int>> pq;
		//Insert initial state into pq
		int moves = 0;
		pq.push(make_pair(init, moves));
		while(!pq.empty()){
			pair<vector<vector<int>>, int> data = pq.front();
			vector<vector<int>> state = data.first;
			moves = data.second;
			visited[state] = 1; 
			pq.pop();
			if(state == final){
				// trace the path from init to final
				tracepath(state, m);
				break;
			}
			else{
				// Visit neighbours and put them in the priority queue
				// First, Get "-1" position index from the current state
				pos p;
				for(int i=0; i<3; i++){
					for(int j=0; j<3; j++){
						if(state[i][j] == -1){
							p.x = i; p.y = j;
						}
					}
				}
				
				// Initialize a temporary neighbour state
				vector<vector<int>> neighbour;
				// Check all the 4 directions
				//Top
				if(p.x-1>=0){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x][p.y] with neighbour[p.x][p.y-1]
					swap(neighbour[p.x][p.y], neighbour[p.x-1][p.y]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						//Push pair<state, state's parent> into hashmap
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
				//Bottom
				if((p.x+1)<=2){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x][p.y] with neighbour[p.x][p.y-1]
					swap(neighbour[p.x][p.y], neighbour[p.x+1][p.y]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
				//Left
				if(p.y-1>=0){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x-1][p.y] with neighbour[p.x-1][p.y]
					swap(neighbour[p.x][p.y], neighbour[p.x][p.y-1]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
				//Right
				if(p.y+1<=2){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x][p.y] with neighbour[p.x][p.y-1]
					swap(neighbour[p.x][p.y], neighbour[p.x][p.y+1]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
			}
		}	
	}
	else{
		//Priority Queue to hold states according to the h function
		priority_queue<pair<vector<vector<int>>, int>, vector<pair<vector<vector<int>>, int>>, Cmp> pq;	
		//Insert initial state into pq
		int moves = 0;
		pq.push(make_pair(init, moves));
		while(!pq.empty()){
			pair<vector<vector<int>>, int> data = pq.top();
			vector<vector<int>> state = data.first;
			moves = data.second;
			visited[state] = 1; 
			pq.pop();
			if(state == final){
				// trace the path from init to final
				tracepath(state, m);
				break;
			}
			else{
				// Visit neighbours and put them in the priority queue
				// First, Get "-1" position index from the current state
				pos p;
				for(int i=0; i<3; i++){
					for(int j=0; j<3; j++){
						if(state[i][j] == -1){
							p.x = i; p.y = j;
						}
					}
				}
				
				// Initialize a temporary neighbour state
				vector<vector<int>> neighbour;
				// Check all the 4 directions
				//Top
				if(p.x-1>=0){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x][p.y] with neighbour[p.x][p.y-1]
					swap(neighbour[p.x][p.y], neighbour[p.x-1][p.y]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						//Push pair<state, state's parent> into hashmap
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
				//Bottom
				if(p.x+1<=2){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x][p.y] with neighbour[p.x][p.y-1]
					swap(neighbour[p.x][p.y], neighbour[p.x+1][p.y]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
				//Left
				if(p.y-1>=0){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x-1][p.y] with neighbour[p.x-1][p.y]
					swap(neighbour[p.x][p.y], neighbour[p.x][p.y-1]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
				//Right
				if(p.y+1<=2){ // Valid
					neighbour = state;
					//Now, swap positions neighbour[p.x][p.y] with neighbour[p.x][p.y-1]
					swap(neighbour[p.x][p.y], neighbour[p.x][p.y+1]);
					//Check and Push neighbour to priority queue if not present in visited set
					if(visited.find(neighbour) == visited.end()){
						m[neighbour] = state;
						pq.push(make_pair(neighbour, moves+1));	
					}
				}
			}
		}
	}
}

int main(int argc, char* argv[]){
	int heuristic = argv[1][0]-'0';
	
	//Initialize counter to 1
	int counter = 1;
	// Fill the graph
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(i==0 && j==0){
				final[i][j] = -1;
			}
			else{
				final[i][j] = counter++;	
			}
		}
	}
	//Get the initial state from the commandline arguments and set it in the graph
	counter = 2; // Graph state arguments start from position 2
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(argv[counter][0] == '_'){
				init[i][j] = -1;
			}
			else{
				init[i][j] = argv[counter][0]-'0';
			}	
			counter++;
		}
	}
	
	//Check if given 8-puzzle problem is solvable or not
	counter = 0;
	int initparity, finalparity, isparity = 0, fsparity = 0;
	int fs[8], is[8];
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(init[i][j] != -1)
				is[counter++] = init[i][j];
		}
	}
	counter = 0;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(final[i][j] != -1)
				fs[counter++] = final[i][j];
		}
	}
	for(int i=0; i<7; i++){
		for(int j=i+1; j<8; j++){
			if(is[i]>is[j])
				isparity++;
		}
	}
	for(int i=0; i<7; i++){
		for(int j=i+1; j<8; j++){
			if(fs[i]>fs[j])
				fsparity++;
		}
	}
	if((isparity%2 == 0) && (fsparity%2 == 0)){
		astar(init, final, heuristic);	
	}
	else if((isparity%2 != 0) && (fsparity%2 != 0)){
		astar(init, final, heuristic);	
	}
	else{
		cout<<"This puzzle cannot be solved"<<endl;
	}

	return 0;
}
