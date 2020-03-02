#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<vector<vector<string>>> subLCS;
vector<vector<bool>> boolTable;
vector<string> LCS(string a, string b){
	//base case
	if(a.empty() || b.empty()){
		subLCS[a.size()][b.size()].push_back("");
		boolTable[a.size()][b.size()] = true;
		return subLCS[a.size()][b.size()];
	}
	//case1
	if(a.back() == b.back()){	
		if(boolTable[a.size()-1][b.size()-1] == false){
			string sub_a = a.substr(0, a.size()-1), sub_b = b.substr(0, b.size()-1);
			LCS(sub_a, sub_b);
		}
		for(auto i : subLCS[a.size()-1][b.size()-1]){
			i.push_back(a.back());
			subLCS[a.size()][b.size()].push_back(i);
		}
		//cout<<subLCS[a.size()][b.size()].size()<<endl;
		boolTable[a.size()][b.size()] = true;
		return subLCS[a.size()][b.size()];
	}
	//case2
	else{
		if(boolTable[a.size()-1][b.size()] == false){
			string sub_a = a.substr(0, a.size()-1), sub_b = b.substr(0, b.size());
			LCS(sub_a, sub_b);
		}
		if(boolTable[a.size()][b.size()-1] == false){
			string sub_a = a.substr(0, a.size()), sub_b = b.substr(0, b.size()-1);
			LCS(sub_a, sub_b);
		}
		if(subLCS[a.size()-1][b.size()][0].size() >= subLCS[a.size()][b.size()-1][0].size()){
			//cout<<"from leftside"<<endl;
			for(auto i : subLCS[a.size()-1][b.size()])
				subLCS[a.size()][b.size()].push_back(i);
		}
		if(subLCS[a.size()-1][b.size()][0].size() <= subLCS[a.size()][b.size()-1][0].size()){
			//cout<<"from upside"<<endl;
			for(auto i : subLCS[a.size()][b.size()-1])
				subLCS[a.size()][b.size()].push_back(i);
		}
		boolTable[a.size()][b.size()] = true;
		return subLCS[a.size()][b.size()];
	}
}
void initialize(string a, string b){
	//init subLCS
	subLCS.resize(a.size()+1);
	for(auto &i : subLCS)
		i.resize(b.size()+1);
	//inti boolTable
	boolTable.resize(a.size()+1);
	for(auto &i : boolTable)
		i.resize(b.size()+1);
}
int main()
{
	string s1, s2;
	cin>>s1>>s2;
	cout<<"------------"<<endl;
	initialize(s1, s2);
	vector<string> print = LCS(s1, s2);
	if(print[0] == "")
		cout<<0<<"\t"<<0<<endl;
	else{
		cout<<print[0].size()<<"\t"<<print.size()<<endl;
		for(auto i : print)
			cout << i << endl;
	}
	//debug
	
	/*for(auto i : subLCS){
		for(auto j : i)
			cout<<j.size()<<"\t";
		cout<<"\n";
	}*/
	return 0;
}