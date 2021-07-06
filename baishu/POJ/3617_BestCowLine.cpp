//Presentation Error,但是不知道哪里出错了
//#include"pch.h" //VS2017必须包含从头文件
//#include<bits/stdc++.h>//包含全部头文件 POJ不支持
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
using namespace std;

#define MAXN 1002
#define PII pair<int,int>
#define mp make_pair
#define pb push_back
#define M 100
#define inf 0x7fffffff
#define _for(i,lo,hi) for(int i=(lo);i<(hi);i++)
typedef long long LL;


bool fun(string& s, int i, int j) {
	while (i < j) {
		if (s[i] == s[j]) {
			i++; j--;
		}
		else if (s[i] < s[j])
			return true;
		else
			return false;
	}
	return true;
}
int main() {
	//freopen("d:\\input.txt","r",stdin);
	int N;
	char c;
	cin >> N;
	string s,ans;
	_for(i, 0, N) {
		cin >> c;
		s += c;
	}

	int i = 0,j=N-1;
	while (i<=j) {
		if (fun(s, i, j)) {
			ans += s[i]; i++;
		}
		else {
			ans += s[j]; j--;
		}
	}
	_for(i, 0, N)cout << ans[i];
	cout << endl;

	return 0;
}
