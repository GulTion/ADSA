#include<bits/stdc++.h>
using namespace std;
int Assembly(int n,const vector<vector<int> > &a,const vector<vector<int> > &t,vector<int> entry,vector<int> exit){
	vector<int>dp1(n),dp2(n);
	dp1[0]=entry[0]+a[0][0];
	dp2[0]=entry[1]+a[1][0];
	
	for(int i=1;i<n;i++){
		dp1[i]=min(dp1[i-1] +a[0][i],dp2[i-1]+t[1][i-1]+a[0][i]);
		dp2[i]=min(dp2[i-1] +a[1][i],dp1[i-1]+t[0][i-1]+a[1][i]);
		
	}
	return min(dp1[n-1]+exit[0],dp2[n-1]+exit[1]);
}
int main(){
	int n;
	cout<<"Enter The number of station\n";
	cin>>n;
	vector<vector<int> > a(2,vector<int>(n)),t(2,vector<int>(n-1));
	cout<<"Enter the processing times for each line\n";
	for(int i=0;i<2;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	
	cout<<"Enter the transition times b/w lines\n";
	for(int i=0;i<2;i++){
		for(int j=0;j<n-1;j++){
			cin>>t[i][j];
		}
	}
	
	vector<int> v1(2,0);
	cout<<"Enter the entry\n";
	for(int i=0;i<2;i++)
	{
		cin>>v1[i];
	}
	vector<int> v2(2,0);
	cout<<"Enter the exit\n";
	for(int i=0;i<2;i++)
	{
		cin>>v2[i];
	}
	cout<<"Minimum times requiredis "<<Assembly(n,a,t,v1,v2)<<endl;
	return 0;
}

