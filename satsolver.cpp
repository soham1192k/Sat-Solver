#include<bits/stdc++.h>
using namespace std;
#define int long long

//to store the final set of assignments to all variables
vector<int>final_solution;

//function to return the index of the smallest clause 
//clauses: consist of disjunctions in CNF encoding
int shortest_clause(vector<vector<int>>v){
	//initial minimum length and index
	int minn=v[0].size();
	int idx=0;
	//iterate over all clauses
	for(int i=1;i<(int)v.size();i++){
		//update minimum length and index
		if(minn>(int)v[i].size()){
			minn=(int)v[i].size();
			idx=i;
		}
	}
	//return index
	return idx;
}

//Assume var is true. Hence, we can remove all clauses containing var as one of
//its literals. Also, we can remove the negation of var from all clauses 
//in which it is present.
//This function does this work
vector<vector<int>>shorten_formula(vector<vector<int>>v,int var){
	vector<int>to_be_removed;
	//iterating over all clauses
	for(int i=0;i<(int)v.size();i++){
		//iterating on the literals in the ith clause
		for(int j=0;j<(int)v[i].size();j++){
			//if var is present, remove the entire clause
			if(v[i][j]==var) {to_be_removed.push_back(i);break;}
			//if negation of var is present,then remove it from that clause
			else if(v[i][j]==-1*var) {auto itr=v[i].begin();v[i].erase(itr+j);break;}
		}
	}
	//removal of the clause
	for(int i=0;i<(int)to_be_removed.size();i++) v.erase(v.begin()-i+to_be_removed[i]);
	
	//returning the updated set of clauses
	return v;
}

//Given some index, consider all literals in that clause.
//Return the variable which occurs maximum times in the entire formula
int maxoccur(vector<vector<int>>v,int idx){
	//Hashmap to store the frequencies
	map<int,int>mp;
	//Iterating over the clauses
	for(int i=0;i<(int)v.size();i++){
		//Iterating on the ith clause
		for(int j=0;j<(int)v[i].size();j++){	
			//For all literals in the given clause 
			for(int k=0;k<(int)v[idx].size();k++){
				//if that literal or the negation of the literal is present
				//increase frequency
				if(v[i][j]==v[idx][k]){
					mp[k]++;
					break;
				}
				//increase frequency
				else if(v[i][j]==-1*v[idx][k]){
					mp[k]++;
					break;
				}
			}
		}
	}
	//compute the max frequency, and its index
	int maxx=-1,ret_idx=-1;
	for(int i=0;i<(int)v[idx].size();i++){
		if(maxx<mp[i]){
			maxx=mp[i];
			ret_idx=i;
		}
	}
	//return the maximal occuring element
	return v[idx][ret_idx];
}

//recursive function to solve the formula
int solve(vector<vector<int>>v,int n){
	//if empty after shortening, successfully solved.
	if(n==0) return 1;
	//find index of the shortest clause
	int idx=shortest_clause(v);
	if(v[idx].size()==0) return -1;
	//find which variable occurs the max times in the formula
	//among all variables present in the clause at that index
	int var=maxoccur(v,idx);
	//try to set this variable to true
	final_solution.push_back(var);
	//get the shortened encoding
	vector<vector<int>>next=shorten_formula(v,var);
	//if the remaining formula can not be solved
	if(solve(next,(int)next.size())!=1){
		//remove the last element from final_solution
		auto itr=final_solution.end();
		itr--;
		final_solution.erase(itr);
		//try to set this variable to false now
		final_solution.push_back(-1*var);
		//get the shortened encoding
		next=shorten_formula(v,-1*var);
		//if the remaining formula cannot be solved,
		//we have exhausted both true and false for the current variable
		//Thus the formula must be unsatisfiable
		if(solve(next,(int)next.size())!=1){
			itr=final_solution.end();
			itr--;
			final_solution.erase(itr);
			return -1;
		}
		//the remaining formula can be solved with the value of the current
		//literal as false; hence satisfiable
		else return 1;
	}
	//the remaining formula can be solved with the value of the current
	//literal as true; hence satisfiable
	else return 1;
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//redirect output
    freopen("output.txt", "w", stdout);
	ifstream temp;
	temp.open("input.txt");
	string data,token;
	int variables=0,clauses=0;
	//get the first line of data
	getline(temp,data);
	//removing comments from the DIMACS representation
	while(data[0]=='c') getline(temp,data);
	//must conform to DIMACS representation
	if(data[0]!='p') cout<<"ERROR:NOT IN DIMACS REPRESENTATION\n";
	else{
		istringstream hold(data);
		int cnt=0;
		while(hold>>token){
			cnt++;
			//store the number of variables and clauses
			if(cnt==3) variables=stoi(token);
			else if(cnt==4) clauses=stoi(token);
		}
	}
	//to store the clauses
	vector<vector<int>>res(clauses);
	int ptr=0;
	//iterate over all clauses
	while(clauses>0){
		//read the clause
		getline(temp,data);
		istringstream hold(data);
		while(hold>>token){
			//each line ends with a 0
			if(token=="0") break;
			//store the literal inside that clause.
			res[ptr].push_back(stoi(token));
		}
		clauses--;
		ptr++;
	}
	temp.close();

	//solve the set of clauses
	int st=solve(res,(int)res.size());
	if(st!=1){
		cout<<"UNSAT";
	}
	else{
		cout<<"SAT\n";
		vector<int>fin(variables);
		//if a variable is not present in final_solution, it is irrelevant
		//to the formula, and can be assigned both true or false.
		//We assign true to such variables
		for(int i=0;i<variables;i++) fin[i]=i+1;
		for(int i=0;i<final_solution.size();i++){
			//if final solution contains the negation of some variable
			//copy that in fin
			if(final_solution[i]<0) fin[(-1*final_solution[i])-1]=final_solution[i];
		}
		//print the final assignment of all variables
		for(int i=0;i<variables;i++) cout<<fin[i]<<" ";
		//ends with a 0
		cout<<"0";
	}
	return 0;
}