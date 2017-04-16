#include<bits/stdc++.h>
using namespace std;

int main(){
	freopen("dataSet.txt","w+",stdout);
	int a[]={100, 1000, 2000, 5000, 10000};
	srand(time(NULL));
	for(int i=0;i<5;++i){
		for(int j=0;j<3;++j){
			cout<<a[i]<<endl;
			for(int k=0;k<a[i];++k){
				cout<<rand()%a[i]<<" "<<rand()%a[i]<<endl;
			}
			cout<<endl;
		}
	}
	return 0;
}
