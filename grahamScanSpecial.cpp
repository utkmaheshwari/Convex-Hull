#include<bits/stdc++.h>
using namespace std;
 
struct point
{
    long long x;
	long long y;
};

long long n,j,i,m,k;
point p0;
 
long long dist(point p1, point p2);

long long  order(point p, point q, point r);

int cmp(const void *vp1, const void *vp2);

int main(){
	freopen("specialDataSet.txt","r",stdin);
	freopen("grahamScanSpecialAns.txt","w+",stdout);
	for(k=0;k<5;++k){
		vector<point> data;
		vector<point> ans;
		cin>>n;
		for(i=0;i<n;++i){
			point p;
			cin>>p.x>>p.y;
			data.push_back(p);
		}
		clock_t startTime=clock();
	    j = 0;
		for (i=1;i<n;i++){
			if((data[i].y<data[j].y)||((data[i].y==data[j].y)&&(data[i].x<data[j].x))){
				j=i;
			}
		}
		point temp=data[0];
		data[0]=data[j];
		data[j]=temp;
	 
		p0=data[0];
	    qsort(&data[1],n-1,sizeof(point),cmp);
	    m=1;
	    for (i=1;i<n;i++){
			while ((i<n-1)&&(order(p0,data[i],data[i+1])==0)){
	       		i++;
		   	}
			data[m]=data[i];
	       	m++;
	    }
	    ans.push_back(data[0]);
	    ans.push_back(data[1]);
	    ans.push_back(data[2]);
	    for (i = 3;i<m;i++){
	    	while(order(*(ans.end()-2),*(ans.end()-1),data[i])!=2){
	      		ans.pop_back();	
		    }
	        ans.push_back(data[i]);
	    }
		double exeTime=double(clock()-startTime)/(double)CLOCKS_PER_SEC;
		cout<<"Input Size: "<<n<<endl;
		cout<<"Convex Hull SIze: "<<ans.size()<<endl;
		cout<<"Execution Time: "<<exeTime<<endl<<endl;
	}
	return 0;
}

long long dist(point p1, point p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

long long order(point p, point q, point r){
    long long sign=(q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y);
    if (sign==0){
		return 0;
	}
	else if(sign>0){
		return 1;
	}
	else{
		return 2;
	}
}

int cmp(const void *vp1, const void *vp2){
   point *p1 = (point *)vp1;
   point *p2 = (point *)vp2;
   long long o=order(p0,*p1,*p2);
   if (o==0)
     return (dist(p0,*p2)>=dist(p0,*p1))?-1:1;
   return (o==2)?-1:1;
}
