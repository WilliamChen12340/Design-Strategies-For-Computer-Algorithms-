#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
double lb = 0;
typedef struct{
	double value;
	double weight;
	double cp;
}item;
bool cmp(const item& i1, const item& i2){
	return i1.cp > i2.cp;
}
double upper_bound(double capacity, double taken, vector<item> vi){
	double ub = 0;
	auto it = vi.begin();
	while(capacity > 0)
	{
		if(it->weight <= capacity)
		{
			capacity -= it->weight;
			ub += it->value;
			it++;
		}
		else
		{
			ub += it->cp * capacity;
			capacity = 0;
		}
	}
	return taken + ub;
}
void knapsack(double capacity, double taken, vector<item> vi){
	//initial condition
	if(vi.empty() || capacity == 0)
		lb = max(lb, taken);
	//recursive
	double ub_taken = 0;
	vector<item> temp = vi;
	temp.erase(vi.begin());
	if(capacity >= vi.begin()->weight)
		ub_taken = upper_bound(capacity - vi.begin()->weight, taken + vi.begin()->value, temp);
	double ub_not_taken = upper_bound(capacity, taken, temp);
	cout<<ub_taken<<"\n";
	cout<<ub_not_taken<<"\n";
	//double lb_taken, lb_not_taken;
	if(ub_taken > ub_not_taken)
	{
		if(capacity >= vi.begin()->weight)
			knapsack(capacity - vi.begin()->weight, taken + vi.begin()->value, temp);
		if(lb < ub_not_taken)
			knapsack(capacity, taken, temp);
	}
	else
	{
		knapsack(capacity, taken, temp);
		if(lb < ub_taken)
		{
			if(capacity >= vi.begin()->weight)
				knapsack(capacity - vi.begin()->weight, taken + vi.begin()->value, temp);
		}
	}
	return 0;
}
int main()
{
	double W, I;
	cin >> W >> I;
	vector<item> vi;
	vi.resize(I);
	for(int i = 0; i < I; i++){
		cin >> vi.at(i).value >> vi.at(i).weight;
		vi.at(i).cp = vi.at(i).value / vi.at(i).weight;
	}
	sort(vi.begin(), vi.end(), cmp);
	knapsack(W, 0, vi);
	//cout<<upper_bound(W, 0, vi);
	//for(auto i : vi)	cout<<i.cp<<"\n";
	return 0;
}