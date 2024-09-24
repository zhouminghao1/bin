#include<iostream>
using namespace std;

typedef struct house{
	int a[10];
	int s=0;
}; 

int main(){
    int m,n,i,j;
    cin>>n>>m;
    house hou[1000];
    for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>hou[i].a[j];
		}
    }
    for(i=0;i<n;i++){
    	if(hou[i].s==0){
    		j=0;
    		while(j<i){
				int k=0;
				int flag1=0;
				while(k<m){
					if(hou[j].a[k]<=hou[i].a[k]){
						flag1=1;
						break;
					}
					k++;
				}
				if(flag1==0){
					hou[i].s=j+1;
					break;
				}
				j++;		
			}	
		}
		if(hou[i].s==0){
			j=i+1;
    		while(j<n){
				int k=0;
				int flag1=0;
				while(k<m){
					if(hou[j].a[k]<=hou[i].a[k]){
						flag1=1;
						break;
					}
					k++;
				}
				if(flag1==0){
					hou[i].s=j+1;
					break;
				}
				j++;		
			}	
		}
	}
	for(i=0;i<n;i++){
		cout<<hou[i].s<<endl;
	}
	cin.get();
	cin.get();
    return 0;
}
