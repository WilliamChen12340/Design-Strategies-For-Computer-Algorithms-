#include<bits/stdc++.h>
using namespace std;
vector<pair<int, int>> ans_pair;
bool cmp(pair<int, int> p1, pair<int, int> p2){
	return p1.second < p2.second;
}
/*
int _2DCP(vector<pair<int, int>> v){
	//initial condition
	
	//divide into L and R
	vector<pair<int, int>> tmp = v;
	nth_element(tmp.begin(), tmp.begin()+int((N-1)/2), tmp.end());
	int xmedian = (tmp.begin()+int((N-1)/2))->first;
	int cnt = 0;
	for(auto i : v)
	{
		if(i.first == xmedian)
			cnt++;
	}
	vector<pair<int, int>> vL, vR;
	//vL.resize(int((N+1)/2));
	//vR.resize(int(N/2));
	int j = 0;
	cout<<(tmp.begin()+int((N-1)/2))->first<<endl;
	for(auto i : v) 
	{
		if(i < (*(tmp.begin()+int((N-1)/2))))
			vL.push_back(i);
		else if(i > (*(tmp.begin()+int((N-1)/2))))
			vR.push_back(i);
		else
		{
			if(j <= (cnt+1)/2)
			{
				vL.push_back(i);
				j++;
			}
			else
				vR.push_back(i);
		}
	}
	//recursive
	int dL = _2DCP(vL);
	int dR = _2DCP(vR);
	int d = min(dL, dR);
	//combine
	vector<pair<int, int>> sL, sR;
	auto it_L = vL.end()-1;
	while(pow((vL.end()-1)->first - it_L->first),2 <= d)
	{
		sL.push_back(*it_L);
		it_L++;
	}
	auto it_R = vR.begin();
	while(pow((vL.end()-1)->first - it_R->first),2 <= d)
	{
		sR.push_back(*it_R);
		it_R++;
	}

}
*/
int main(){
	int N;
	cin >> N;
	vector<pair<int, int>> v;
	v.resize(N);
	for(int i=0; i < N; i++)
		cin >> v.at(i).first >> v.at(i).second;
	sort(v.begin(), v.end(), cmp);



	vector<pair<int, int>> tmp = v;
	nth_element(tmp.begin(), tmp.begin()+int((N-1)/2), tmp.end());
	int xmedian = (tmp.begin()+int((N-1)/2))->first;
	int cnt = 0;
	for(auto i : v)
	{
		if(i.first == xmedian)
			cnt++;
	}
	vector<pair<int, int>> vL, vR;
	int j = 0;
	for(auto i : v) 
	{
		if(i < (*(tmp.begin()+int((N-1)/2))))
			vL.push_back(i);
		else if(i > (*(tmp.begin()+int((N-1)/2))))
			vR.push_back(i);
		else
		{
			if(j <= (cnt+1)/2)
			{
				vL.push_back(i);
				j++;
			}
			else
				vR.push_back(i);
		}
	}
	//for(auto i : v)
	//	cout<<"("<<i.first<<","<<i.second<<")"<<endl;
	
	for(auto i : vL)
		cout<<"vLis : ("<<i.first<<","<<i.second<<")"<<endl;
	cout<<"----------"<<endl;
	for(auto i : vR)
		cout<<"vRis : ("<<i.first<<","<<i.second<<")"<<endl;
	
	//ans = _2DCP(v);
	return 0;
}