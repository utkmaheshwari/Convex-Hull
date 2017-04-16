#include<bits/stdc++.h>

using namespace std;

struct node{
    node* next;
    node* prev;
    int data;
    int data2;
};

class cdll{
    public:
    node* root;
    node* main_root;
    node* last_root;
    node* pointer;
    cdll(){
        pointer = NULL;
        root = NULL;
    }
    void insert(vector<int> x , vector<int> y){
        int val, val2;
        val = x[0], val2 = y[0];
        root = new node;
        main_root = root;
        root->next = NULL;
        root->prev = NULL;
        root->data = val;
        root->data2 = val2;
        
        for(int i=1;i<x.size();i++){
            val = x[i];
            val2 = y[i];
            node *temp1 = new node;
            temp1->next = NULL;
            temp1->prev = root;
            temp1->data = val;
            temp1->data2 = val2;
            root->next = temp1;
            root = root->next;
        }
        root->next = main_root;
        last_root = root;
        main_root->prev = last_root;
        root=root->next;
    }
    void push(int val, int val2){
        node* temp1 = new node;
        temp1->data = val;
        temp1->data2 = val2;
        temp1->next = main_root;
        temp1->prev = last_root;
        last_root->next = temp1;
        last_root = temp1;
    }

    int size(){
        int cnt = 0;
        node* temp = main_root;
        while(temp != last_root){
            cnt++;
            temp = temp->next;
        }
        cnt++;
        return cnt;
    }

    node* y_max(){
        node* temp = main_root;
        node* temp2 = main_root;
        while(temp != last_root){
            if(temp->data2 > temp2->data2) {
            	temp2 = temp;	
			}
            temp = temp->next;
        }
        if(temp->data2 > temp2->data2){
        	temp2 = temp;	
		} 
        return temp2;
    }

    node* y_min(){
        node* temp = last_root;
        node* temp2 = last_root;
        while(temp != main_root){
            if(temp->data2 < temp2->data2){
            	temp2 = temp;
			}
            temp = temp->prev;
        }
        if(temp->data2 < temp2->data2){
        	temp2 = temp;	
		}
        return temp2;
    }
};

struct hull{
    vector<int> x_cord;
    vector<int> y_cord;
};

struct point{
    int x;
    int y;
};

class convex_hull{
	public:
    int n,f;
    vector<int> xh;
    vector<int> yh;
    void getData(){
    	int x,y;
        for(int i=0;i<n;++i){
			cin>>x>>y;
			xh.push_back(x);
			yh.push_back(y);
		}
    }

    void run(){
        hull res;
        res = con_hull(xh,yh,0,xh.size()-1,xh.size());
	}

    hull con_hull(vector<int> x, vector<int> y, int start, int end, int num) {
    	if (start < end ){
            if(num == 1 || num == 2 || num == 3 || x[start] == x[end]){
                hull hh1;
                if(x[start] == x[end]){
                    hh1.x_cord.push_back(x[start]);
                    hh1.y_cord.push_back(y[start]);
                    hh1.x_cord.push_back(x[end]);
                    hh1.y_cord.push_back(y[end]);
                } 
                else{
                    for(int i = start; i <= end; i++){
                        hh1.x_cord.push_back (x[i]);
                        hh1.y_cord.push_back (y[i]);
                    }
                }
                return hh1;
            }
            int mid = (start + end)/2;
            hull h_left;
            hull h_right;
            h_left = con_hull(x, y, start, mid, mid - start + 1);
            h_right = con_hull(x, y, mid + 1, end, end - mid);
            hull m_hull = merge(h_left, h_right);
            return m_hull;
        }
    }
    hull merge(hull left, hull right){
        cdll l, r;
        int counter_l, counter_r;
        node *n1, *n2, *n3, *n4;
        hull final;
        bool b1;
        l.insert(left.x_cord, left.y_cord);
        r.insert(right.x_cord, right.y_cord);
        int flag = 0;
        point temp1, temp2;
        l.pointer = l.y_max();
        r.pointer = r.y_max();
        if(l.y_max()->data2 > r.y_max()->data2){
            counter_l = 0;
            while (counter_l != l.size()) {
                counter_l++;
                counter_r=0;
                r.pointer = r.y_max();
                while (counter_r != r.size()) {
                    counter_r++;
                    temp1.x = l.pointer->data;
                    temp1.y = l.pointer->data2;
                    temp2.x = r.pointer->data;
                    temp2.y = r.pointer->data2;
                    bool b1 = check(temp1 , temp2 , left , right );
                    if(b1){
                        n1 = l.pointer;
                        n2 = r.pointer;
                        flag = 1;
                        break;
                    } 
                    else{
                    	r.pointer = r.pointer->prev;
					} 
                }
                if(flag == 1) {
                	break;
				}
                l.pointer = l.pointer->next;
            }
        } 
        else{
            counter_r = 0;
            while (counter_r != r.size()){
                counter_r++;
                counter_l=0;
                l.pointer = l.y_max();
                while (counter_l != l.size()){
                    counter_l++;
                    temp1.x = l.pointer->data;
                    temp1.y = l.pointer->data2;
                    temp2.x = r.pointer->data;
                    temp2.y = r.pointer->data2;
                    bool b1 = check(temp1, temp2, left, right);
                    if(b1){
                        n1 = l.pointer;
                        n2 = r.pointer;
                        flag = 1;
                        break;
                    } 
                    else{
                    	l.pointer = l.pointer->next;
					}
                }
                if(flag == 1){
                	break;
				} 
                r.pointer = r.pointer->prev;
            }
        }
	    l.pointer = l.y_min() ;
	    r.pointer = r.y_min() ;
	    flag = 0;
        if(l.y_min()->data2<r.y_min()->data2){
	        counter_l = 0;
	        while (counter_l != l.size()){
	            counter_l++;
	            counter_r=0;
	            r.pointer = r.y_max();
	            while (counter_r != r.size()){
	                counter_r++;
	                temp1.x = l.pointer->data;
	                temp1.y = l.pointer->data2;
	                temp2.x = r.pointer->data;
	                temp2.y = r.pointer->data2;
	                bool b1 = check(temp1, temp2, left, right);
	                if(b1){
	                    n3 = l.pointer;
	                    n4 = r.pointer;
	                    flag = 1;
	                    break;
	                } 
	                else{
	                	r.pointer = r.pointer->next;
					} 
	            }
	            if(flag == 1) {
	            	break;
				}
	            l.pointer = l.pointer->prev;
	        }
        } 
        else{
            counter_r = 0;
            while (counter_r != r.size()){
                counter_r++;
              	counter_l=0;
              	l.pointer = l.y_max();
            	while (counter_l != l.size()){
	        		counter_l++;
	                point temp1, temp2;
	                temp1.x = r.pointer->data;
	                temp1.y = r.pointer->data2;
	                temp2.x = l.pointer->data;
	                temp2.y = l.pointer->data2;
	                bool b1 = check(temp1, temp2, left, right);
	                if(b1){
	                    n3 = l.pointer;
	                    n4 = r.pointer;
	                    flag = 1;
	                    break;
	                } 
	                else{
	                	l.pointer = l.pointer->prev;
					}
	            }
                if(flag == 1) {
                	break;
				}
                r.pointer = r.pointer->next;
            }
        }
	    node* tempr1 = n2;
	    while (tempr1 != n4){
	        final.x_cord.push_back(tempr1->data);
	         final.y_cord.push_back(tempr1->data2);
	        tempr1 = tempr1->next;
	    }
	    final.x_cord.push_back(tempr1->data);
	    final.y_cord.push_back(tempr1->data2);
	    node*  tempr2 = n3;
	    while(tempr2 != n1){
	              final.x_cord.push_back(tempr2->data);
	            final.y_cord.push_back(tempr2->data2);
	               tempr2 = tempr2->next;
	    }
	    final.x_cord.push_back(tempr2->data);
	    final.y_cord.push_back(tempr2->data2);
	    return final;
    }
    int equation(int x1, int x2, int y1, int y2, int x, int y){
        return ((y-y1) * (x1-x2)) - ((y1-y2)*(x-x1));
    }

    bool check(point l, point r, hull lef, hull rig){
        bool f;
        int tempo1 = lef.x_cord[0];
        int tempo2 = lef.y_cord[0];
        for (int i = 0; i < lef.x_cord.size(); i++){
            if(tempo1 == l.x && tempo2 == l.y){
	            tempo1 = lef.x_cord[i];
	            tempo2 = lef.y_cord[i];
            }
            else{
            	break;
			} 
        }
        if (equation(l.x, r.x, l.y, r.y, tempo1, tempo2) < 0){
        	f = false;
		}
        else{
        	f = true;
		}
        for (int i = 0; i < lef.x_cord.size(); i++){
            if (equation(l.x, r.x, l.y, r.y, lef.x_cord[i], lef.y_cord[i]) > 0 && f == false)
                return false;
            else if (equation(l.x, r.x, l.y, r.y, lef.x_cord[i], lef.y_cord[i]) < 0 && f == true)
                return false;
        }
        for(int i = 0; i < rig.x_cord.size(); i++ ){
        	if (equation(l.x, r.x, l.y, r.y, rig.x_cord[i], rig.y_cord[i]) > 0 && f == false)
                return false;
            else if (equation(l.x, r.x, l.y, r.y, rig.x_cord[i], rig.y_cord[i]) < 0 && f == true)
            	return false;
        }
        return true;
    }
};

int cmp(const void *vp1, const void *vp2);

int main()
{
	freopen("dataSet.txt","r",stdin);
	freopen("guickHullAns.txt","w+",stdout);
	for(int k=0;k<15;++k){
		vector<point> data;
		convex_hull h1;
		cin>>h1.n;
    	h1.getData();
		for(int i=0;i<h1.n;++i){
			point p;
			p.x=h1.xh[i];
			p.y=h1.yh[i];
			data.push_back(p);
		}
		clock_t startTime=clock();
    	qsort(&data[0],h1.n,sizeof(point),cmp);
    	h1.xh.clear();
    	h1.yh.clear();
    	for(int i=0;i<h1.n;++i){
			h1.xh.push_back(data[i].x);
			h1.yh.push_back(data[i].y);
		}
    	h1.run();
    	double exeTime=double(clock()-startTime)/(double)CLOCKS_PER_SEC;
		cout<<h1.n<<" "<<exeTime<<endl;
	}
    return 0;
}

int cmp(const void *vp1, const void *vp2){
   point *p1 = (point *)vp1;
   point *p2 = (point *)vp2;
   return (p1->x<=p2->x)?1:-1;
}
