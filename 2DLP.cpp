#include <bits/stdc++.h>
#define MAX numeric_limits<float>::infinity()
#define MIN -1 * numeric_limits<float>::infinity()

using namespace std;

struct line
{
	float a, b, c, slope, height;
};

struct point
{
	float x,y;
	list<line>::iterator L1, L2;
};


bool isequal(float a, float b)
{
	if(abs(a-b) < 1E-4) return true;
	else return false;
}
list<line> L;




point intersection( list<line>::iterator l1, list<line>::iterator l2)
{
	point p;
	float son = l1->a* l2->b -  l2->a* l1->b;
	p.x = (l1->c*l2->b - l2->c*l1->b)/ son;
	p.y = (l2->c* l1->a - l1->c* l2->a)/ son;
	p.L1 = l1; p.L2 = l2;
	return p;
}

bool pointsCmp( point p1, point p2)
{
	return( p1.x <= p2.x);
}


float AlphaBelta_y(list<line>::iterator l, float x)
{
	return (l->c - l->a*x)/l->b;
}

float TDLP()
{
	list<line> bottom, top;
	float xl = MIN, xr = MAX;
	/*Seperate two set into bottom\top and the X boundary*/
	for(auto i = L.begin(); i != L.end(); i++){
		auto lin = *i;
		if( lin.b > 0 )	top.push_back(lin);
		else if(lin.b < 0) bottom.push_back(lin);
		else{
			if(lin.a > 0) xr = min(xr, lin.c/lin.a);
			else xl = max(xl, lin.c/lin.a);
		}
	}

	// cout << "------------------------------------------" << endl;
	// for(auto i = bottom.begin(); i != bottom.end(); i++)
	// 	cout << (i->a) << " " << (i->b) << " " << (i->c) <<endl;
	// for(auto i = top.begin(); i != top.end(); i++)
	// 	cout << (i->a) << " " << (i->b) << " " << (i->c) <<endl;
	
	// cout << "while" << endl;
	while(true){	
		int b_size = bottom.size();
		int t_size = top.size();
		if( xl > xr ) return NAN;
		if(b_size == 0) return MIN;
		else if(b_size == 1){
			auto b_line = bottom.begin();
			if(t_size == 0){
				if (b_line->a == 0)
				{
					return (b_line -> c/ b_line -> b);
				}
				else if(b_line->b == 0)
					return MIN;
				else if(b_line->slope > 0){
					if(xl != MIN)
					{
						return AlphaBelta_y(b_line, xl);
					}
					else
					{
						return MIN;
					}
				}
				else if(b_line->slope < 0)
					if(xr != MAX)
					{
						return AlphaBelta_y(b_line, xr);
					}
					else
					{
						return MAX;
					}

			}
			else if(t_size == 1)
			{
				auto t_line = top.begin();
				auto p = intersection(b_line, t_line);
				
				if(t_line->slope == b_line->slope)
				{
					if(b_line->height >= t_line->height)
						return NAN;
				}
				else
				{
					// cout << " t_line.slope " << t_line->slope << endl;
					// cout << " b_line.slope " << b_line->slope << endl;
					if(b_line->slope < t_line->slope)
					{
						xl = max(p.x, xl);
					}
					if(b_line->slope > t_line->slope)
					{
						xr = min(p.x, xr);
					}
				}
				cout << "p.x : " << p.x << endl;
				cout << " xl : " << xl << " xr : " << xr << endl;
				top.erase(t_line);
				continue;
			}
		}
/*Check Lines Number*/
	// 	cout << "------------------------------------------" << endl;
	// for(auto i = bottom.begin(); i != bottom.end(); i++)
	// 	cout << (i->a) << " " << (i->b) << " " << (i->c) <<endl;
	// cout << "//////////////////" << endl;
	// for(auto i = top.begin(); i != top.end(); i++)
	// 	cout << (i->a) << " " << (i->b) << " " << (i->c) <<endl;
	cout << "bot size : " << bottom.size() << endl;
	cout << "top size : " << top.size() << endl;

		
		vector<point> Points;
		auto botsize = bottom.size();
		auto topsize = top.size();
		/*Get points for pairs line for bottom*/
		// cout << " ------Bottom pairs------- " << endl;
		for(auto i = bottom.begin(); i != bottom.end();){
			auto lin1 = i++, lin2 = i++;
			if( lin2 == bottom.end()) break;
			else if(lin1->slope == lin2->slope){
				bottom.erase(lin1->height < lin2->height? lin1:lin2);
			}
			else{
				auto p = intersection(lin1, lin2);
				if( p.x <= xl )		
					bottom.erase(lin1->slope < lin2->slope? lin1: lin2);
				else if( p.x >= xr ) 
					bottom.erase(lin1->slope > lin2->slope? lin1: lin2);
				else{
					Points.push_back(p);
					cout << " xl : " << xl << " xr : " << xr << endl;
					cout << " p : " << p.x << " " << p.y << endl;
				}
			}
		}
	
		// cout << 123<< endl;
		/*Get points for pairs line for top*/
		// cout << " ------Top pairs------- " << endl;
		for(auto i = top.begin(); i != top.end();){
			auto lin1 = i++, lin2 = i++;
			if( lin2 == top.end()) break;
			else if(lin1->slope == lin2->slope) 
				top.erase(lin1->height > lin2->height? lin1:lin2);
			else{
				auto p = intersection(lin1, lin2);
				if( p.x <= xl )
					top.erase(lin1->slope > lin2->slope? lin1: lin2);
				else if( p.x >= xr ) 
					top.erase(lin1->slope < lin2->slope? lin1: lin2);
				else{
					Points.push_back(p);
					cout << " xl : " << xl << " xr : " << xr << endl;
					cout << " p : " << p.x << " " << p.y << endl;
				}
			}
		}

		/*Find alpha/belta y && reduce points*/
		int pointSize = Points.size();
		if(pointSize){
			int mid = pointSize/2;
			float alpha_y = MIN, belta_y = MAX, s_max, s_min, t_max, t_min;
			nth_element(Points.begin(), Points.begin()+mid, Points.end(), pointsCmp);
			// cout << " nth Point : " << " ( " << Points[mid].x << ", " << Points[mid].y << " ) " << "MID POINT IS HERE!!!!!!!!!" << endl;
			
			/*Alpha_y s_max s_min*/
			for(auto i = bottom.begin(); i != bottom.end(); i++){
				float y = AlphaBelta_y(i, Points[mid].x);

				if( isequal(y, alpha_y )){
					s_max = max( s_max, i-> slope);
					s_min = min( s_min, i-> slope);
				}
				else if( y > alpha_y){
					alpha_y = y;
					s_max = s_min = i->slope;
				}
			}

			/*Belta_y t_max t_min*/
			for(auto i = top.begin(); i != top.end(); i++){
				float y = AlphaBelta_y(i, Points[mid].x);
				// cout << i->a << " " << i->b << " " << i->c << endl; 
				// cout << " Belta y? : " << y << endl;
				if( isequal(y, belta_y )){
					t_max = max( t_max, i-> slope);
					t_min = min( t_min, i-> slope);
				}
				else if( y < belta_y){
					belta_y = y;
					t_max = t_min = i->slope;
				}
			}

			/* Print ay, by and tmax tmin, smax smin */
			cout << " alpha_y : " << alpha_y << " belta_y : " << belta_y << "~~~~~~~~~~~" << endl;
			cout << "s_max : " << s_max << "\ts_min : " << s_min << endl;
			cout << "t_max : " << t_max << "\tt_min : " << t_min << endl;

 			/*6 type cases*/
			bool opt_x_right ;
			if(alpha_y < belta_y){
				if(s_max >= 0 && s_min <= 0 && s_min <= s_max)
				{ // \./
					return Points[mid].y;
				}
				else if( s_min <= s_max && s_max < 0) // \_.
				{
					opt_x_right = true;
				}
				else if( s_max >= s_min	&& s_min > 0){ // ._/
					opt_x_right = false;
				}
			}
			else if(alpha_y > belta_y) 
			{
				if( s_max < t_min)
				{
					opt_x_right = true;
				}
				else if(s_min > t_max)
				{
					opt_x_right = false;	
				}
				else if(s_max >= t_min && s_min <= t_max)
					return NAN;
			}



			if(opt_x_right){
				for(int i = 0; i <= mid; i++){
					auto p = Points[i];
					if(p.L1->b < 0)
						bottom.erase(p.L1->slope < p.L2->slope? p.L1: p.L2);
					else
						top.erase(p.L1->slope > p.L2->slope? p.L1: p.L2);
				}
			}
			else{
				for(int i = mid; i < pointSize; i++){
					auto p = Points[i];
					if(p.L1->b < 0)
						bottom.erase(p.L1->slope > p.L2->slope? p.L1: p.L2);
					else
						top.erase(p.L1->slope < p.L2->slope? p.L1: p.L2);
				}
			}

		}
		// cout << " -------------After prune------------ " << endl;
		// cout << "bot size : " << bottom.size() << endl;
		// cout << "top size : " << top.size() << endl;
		

	} // while

}




int main(int argc, char const *argv[])
{
	int n, a, b, c;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		line tmp;
		cin >> tmp.a >> tmp.b >> tmp.c;
		if(tmp.b == 0) tmp.slope = MAX;
		else tmp.slope = -1*tmp.a/tmp.b;
		tmp.height = tmp.c/tmp.b;
		if(tmp.a == 0 && tmp.b == 0) continue;
		else L.push_back(tmp);
	}

	float ans;
	ans = TDLP();
	if(ans == MIN) cout << "-INF";
	else if(isnan(ans)) cout << "NA";
	else{
		ans =  ans > 0? int(ans+0.5): int(ans-0.5);
	cout  << ans;	
	} 



	return 0;
}