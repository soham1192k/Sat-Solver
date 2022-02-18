#include<bits/stdc++.h>
using namespace std;
#define int long long
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
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
    temp.open("output.txt");
    getline(temp,data);
    if(data[0]=='S'){
        cout<<"For the given assignment, the formula evaluates to: ";
        getline(temp,data);
        istringstream hold(data);
        map<int,bool>mp;
        while(hold>>token){
            bool negative=false;
            if(token[0]=='-') {negative=true;token=token.substr(1);}
            int val=stoi(token);
            if(negative==false) mp[val]=true;
            else mp[val]=false;
        }
        for(int i=0;i<(int)res.size();i++){
            bool evals_to_true=false;
            for(int j=0;j<(int)res[i].size();j++){
				if(res[i][j]<0) evals_to_true|=(mp[abs(res[i][j])]^1);
                else evals_to_true|=mp[abs(res[i][j])];
            }
            if(evals_to_true==false) {cout<<"FALSE! Wrong assignment\n";return 0;}
        }
        cout<<"TRUE! Correct Assignment\n";
    }
    else{
        cout<<"Formula is unsatisfiable\n";
    }
    return 0;
}