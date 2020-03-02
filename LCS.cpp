#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<vector<vector<string>>> subLCS;
vector<vector<size_t>> len;
vector<vector<bool>> trace;
vector<vector<bool>> trace_same;
void build_len(const string &s1, const string &s2){
	len.resize(s1.size()+1);
	for(auto &i : len)	i.resize(s2.size()+1);
	for(int i=1; i<=s1.size(); i++){
		for(int j=1; j<=s2.size(); j++){
			if(s1[i-1] == s2[j-1])	len[i][j] = len[i-1][j-1]+1;
			else	len[i][j] = max(len[i-1][j], len[i][j-1]);
		}
	}
}
void init_trace(const string &s1, const string &s2){
	trace.resize(s1.size()+1);
	for(auto &i : trace)	i.resize(s2.size()+1);
	trace_same.resize(s1.size()+1);
	for(auto &i : trace_same)	i.resize(s2.size()+1);
}
void init_subLCS(const string &s1, const string &s2){
	subLCS.resize(s1.size()+1);
	for(auto &i : subLCS)	i.resize(s2.size()+1);
}
vector<string> LCS(const string &s1, const string &s2, bool flag){
	//base case
	if(len[s1.size()][s2.size()] == 0){
		vector<string> base{""};
		return base;
	}
	if(s1.back() == s2.back()){
		//cout<<s1.size()<<"\t"<<s2.size()<<endl;
		if(flag == false){
			if(trace[s1.size()][s2.size()] == true)
				return subLCS[s1.size()][s2.size()];
			vector<string> temp;
			//
			if(len[s1.size()][s2.size()] == len[s1.size()-1][s2.size()])
				temp = LCS(s1.substr(0, s1.size()-1), s2, false);
			if(len[s1.size()][s2.size()] == len[s1.size()][s2.size()-1]){
				for(auto i : LCS(s1, s2.substr(0, s2.size()-1), false))
					temp.push_back(i);
			}
			for(auto i : LCS(s1.substr(0, s1.size()-1), s2.substr(0, s2.size()-1), false)){
				i.push_back(s1.back());
				temp.push_back(i);
			}
			subLCS[s1.size()][s2.size()] = temp;
			trace[s1.size()][s2.size()] = true;
			return temp;
		}
		else{
			if(trace_same[s1.size()][s2.size()] == true){
				vector<string> empty;
				return empty;
			}
			else{
				vector<string> temp;
				if(len[s1.size()][s2.size()] == len[s1.size()-1][s2.size()])
					temp = LCS(s1.substr(0, s1.size()-1), s2, true);
				if(len[s1.size()][s2.size()] == len[s1.size()][s2.size()-1]){
					for(auto i : LCS(s1, s2.substr(0, s2.size()-1), true))
						temp.push_back(i);
				}
				for(auto i  : LCS(s1.substr(0, s1.size()-1), s2.substr(0, s2.size()-1), false)){
					i.push_back(s1.back());
					temp.push_back(i);
				}
				trace_same[s1.size()][s2.size()] = true;
				//return LCS(s1, s2, false);
				return temp;
			}
		}
	}
	else{
		//cout<<s1.size()<<"\t"<<s2.size()<<endl;
		if(len[s1.size()-1][s2.size()] == len[s1.size()][s2.size()-1]){
			vector<string> temp = LCS(s1.substr(0, s1.size()-1), s2, true);
			for(auto i : LCS(s1, s2.substr(0, s2.size()-1), true))
				temp.push_back(i);
			if(flag == false){
				for(size_t i = 0; i <= s1.size(); i++)
					for(size_t j = 0; j <= s2.size(); j++)
						trace_same[i][j] = 0;
			}
			//
			return temp;
		}
		else if(len[s1.size()-1][s2.size()] > len[s1.size()][s2.size()-1])
			return LCS(s1.substr(0, s1.size()-1), s2, flag);
		else
			return LCS(s1, s2.substr(0, s2.size()-1), flag);
	}
}
int main(){
	string s1, s2;
	cin>>s1>>s2;
	//cout<<"---------------\n";
	build_len(s1, s2);
	init_trace(s1, s2);
	init_subLCS(s1, s2);
	vector<string> ans = LCS(s1, s2, false);
	cout<<len[s1.size()][s2.size()]<<" "<<ans.size()<<"\n";
	sort(ans.begin(), ans.end());
	for(auto i : ans)
		cout<<i<<"\n";
	return 0;
}
