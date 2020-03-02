#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
double lb = 0;
typedef struct {
	double value;
	double weight;
	double cp_value;
}item;
bool mycmp(const item& i1, const item& i2){
	return i1.cp_value < i2.cp_value;
}
double upper_bound(int W, vector<item> vi, double taken){
	double ub = taken;
	while(!vi.empty() && W > vi.back().weight){
		item i = vi.back();
		ub += i.value;
		W -= i.weight;
		vi.pop_back();
	}
	if(!vi.empty())
		ub += W * vi.back().cp_value;
	return ub;
}
void knapsack(int W, vector<item> vi, double taken){
	item ith = vi.back();
	vi.pop_back();
	double ub1 = upper_bound(W - ith.weight, vi, taken + ith.value);
	double ub0 = upper_bound(W, vi, taken);
	if(vi.empty())
		lb = (W >= ith.weight)? max(lb, taken + ith.value) : max(lb, taken);
	else{
		if(ub1 >= ub0){
			if(lb >= ub1)	;
			else{
				if(W >= ith.weight)	knapsack(W - ith.weight, vi, taken + ith.value);
				if(ub0 > lb)	knapsack(W, vi, taken);
			}
		}
		else{
			if(lb >= ub0)	;
			else{
				knapsack(W, vi, taken);
				if(ub1 > lb){
					if(W >= ith.weight)	knapsack(W - ith.weight, vi, taken + ith.value);
				}
			}
		}
	}
}
int main(){
	int W, I;
	cin >> W >> I;
	vector<item> vi;
	vi.resize(I);
	for(int i=0; i<I; i++){
		item temp_i;
		cin >> temp_i.value >> temp_i.weight;
		temp_i.cp_value = temp_i.value / temp_i.weight;
		vi.at(i) = temp_i;
	}
	sort(vi.begin(), vi.end(), mycmp);
	knapsack(W, vi, 0);
	cout<<lb<<"\n";
	return 0;
}