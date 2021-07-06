//#include"pch.h"//VS2017必须包含从头文件
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

vector<int> v(1005);

int main() {
	//freopen("d:\\input.txt","r",stdin);
	int R,N;

	while (1) {
		cin >> R >> N;
		if (R == -1)break;
		_for(i, 0, N)cin >> v[i];
		sort(v.begin(), v.begin() + N);
		int cnt = 0, lo = 0,hi=0;
		while (lo < N) {
			cnt++;
			while (hi < N&&v[hi] <= v[lo] + R)hi++;
			lo = hi - 1;
			while (hi < N&&v[hi] <= v[lo] + R)hi++;
			lo = hi;
		}
		cout << cnt << endl;
	}

	return 0;
}
