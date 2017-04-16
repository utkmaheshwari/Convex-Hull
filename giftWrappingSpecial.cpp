#include <bits/stdc++.h>
#include <sys/time.h>
#include<stdio.h>
#include<time.h>
using namespace std;

struct point
{
    long long x;
	long long y;
};

int main(){
	freopen("specialDataSet.txt","r",stdin);
	freopen("giftWrappingSpecialAns.txt","w+",stdout);
	long long k;
	for(k=0;k<5;++k){
		vector<point> data;
		vector<point> ans;
		long long n,i,leftmost,pos,temp,sign,l,k;
		cin>>n;
		data.clear();
		for(i=0;i<n;++i){
			point p;
			cin>>p.x>>p.y;
			data.push_back(p);
		}
		clock_t startTime=clock();
		leftmost=0;
	    for (i=1;i<n;++i){
	    	if(data[i].x<data[leftmost].x){
	    		leftmost=i;
			}
		}
		ans.clear();
		pos=leftmost;
		ans.push_back(data[pos]);
		
		while(true){
			temp=(pos+1)%n;
			for(i=0;i<n;++i){
				sign=(data[i].y-data[pos].y)*(data[temp].x-data[i].x)-
				     (data[i].x-data[pos].x)*(data[temp].y-data[i].y);
	        	if(sign<0){
	        		temp=i;
				}
	        }
	        pos=temp;
	        if(pos==leftmost){
	        	break;
			}
	        ans.push_back(data[pos]);
	    }
		double exeTime=double(clock()-startTime)/(double)CLOCKS_PER_SEC;
		cout<<"Input Size: "<<n<<endl;
		cout<<"Convex Hull SIze: "<<ans.size()<<endl;
		cout<<"Execution Time: "<<exeTime<<endl<<endl;
	}
    return 0;
}
