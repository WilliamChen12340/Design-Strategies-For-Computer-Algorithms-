#include <bits/stdc++.h>
using namespace std;
bool mycmp(const pair<pair<int,int>,size_t> &point1, const pair<pair<int,int>,size_t> &point2)
{
	return point1.first.second < point2.first.second;
}
long long _2DCP(vector<pair<pair<int,int>,size_t>> point, vector<pair<size_t,size_t>> &ans)
{	size_t N = point.size();
	//initial
	if(point.size() == 1)
		return numeric_limits<long long>::max();
	if(point.size() == 2)
	{
		ans.push_back({min(point.begin()->second, (point.begin()+1)->second), max(point.begin()->second, (point.begin()+1)->second)});
		return pow((point.begin()->first).first - ((point.begin()+1)->first).first,2)\
			   + pow((point.begin()->first).second - ((point.begin()+1)->first).second,2);
	}
	//divide into L and R
	auto tmp = point;
	nth_element(tmp.begin(), tmp.begin()+(N-1)/2, tmp.end());
	auto median = *(tmp.begin()+(N-1)/2);
	decltype(point) Lpoint, Rpoint;
	for(auto i : point)
	{
		if(i <= median)
			Lpoint.push_back(i);
		else
			Rpoint.push_back(i);
	}
	// cout<<"median "<<median.second<<" ("<<median.first.first<<", "<<median.first.second<<")"<<endl;
	// for(auto i : Lpoint)
	// 	cout<<"Lpoint "<<i.second<<" ("<<i.first.first<<", "<<i.first.second<<")"<<endl;
	// cout<<"----------------"<<endl;
	// for(auto i : Rpoint)
	// 	cout<<"Rpoint "<<i.second<<" ("<<i.first.first<<", "<<i.first.second<<")"<<endl;
	// cout<<"################"<<endl;
	//recursive
	vector<pair<size_t,size_t>> Lans, Rans;
	long long d;
	long long dL = _2DCP(Lpoint, Lans);
	long long dR = _2DCP(Rpoint, Rans);
	if(dL < dR)
	{
		d = dL;
		ans = Lans;
	}
	else if(dL > dR)
	{
		d = dR;
		ans = Rans;
	}
	else
	{
		d = dL;
		ans = Lans;
		ans.insert(ans.end(), Rans.begin(), Rans.end());
	}
	//combine
	double D = sqrt((double)d);
	decltype(point) sL, sR;
	for(auto i : Lpoint)
	{
		if(i.first.first >= median.first.first - D)
			sL.push_back(i);
	}
	for(auto i : Rpoint)
	{
		if(i.first.first <= median.first.first + D)
			sR.push_back(i);	
	}
	auto Lowest_itR = sR.begin();
	for(auto i : sL)
	{
		while(Lowest_itR != sR.end() && (Lowest_itR->first).second < i.first.second - D)
			Lowest_itR++;
		if(Lowest_itR == sR.end())	break;
		auto itR = Lowest_itR;
		while(itR != sR.end() && (itR->first).second <= i.first.second + D && (itR->first).second >= i.first.second - D)
		{
			if(pow((itR->first).first - i.first.first,2) + pow((itR->first).second - i.first.second,2) == d)
			{
				ans.push_back({min(itR->second, i.second), max(itR->second, i.second)});
			}
			else if(pow((itR->first).first - i.first.first,2) + pow((itR->first).second - i.first.second,2) < d)
			{
				ans.clear();
				d = pow((itR->first).first - i.first.first,2) + pow((itR->first).second - i.first.second,2);
				ans.push_back({min(itR->second, i.second), max(itR->second, i.second)});
			}
			itR++;
		}
	}
	return d;
}
int main(int argc, char const *argv[])
{
	int N;
	vector<pair<pair<int,int>,size_t>> point;
	cin >> N;
	point.resize(N);
	for(int i = 0; i < N; i++)
	{
		cin >> point.at(i).first.first >> point.at(i).first.second;
		point.at(i).second = i+1; 
	}
	vector<pair<size_t,size_t>> ans;
	sort(point.begin(), point.end(), mycmp);
	long long d = _2DCP(point, ans);
	//cout<<"------------------"<<endl;
	cout << d <<" "<< ans.size()<<"\n";
	sort(ans.begin(), ans.end());
	for(auto i : ans)
		cout << i.first <<" "<<i.second<<"\n";
	return 0;
}