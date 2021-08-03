#include<vector>
using namespace std;
int main(){
    vector<int> v;
    for(int i=0;i<10;i++)
        v.push_back(i);
    printf("%lu\n",v.size());
    v.pop_back();
    v.resize(100);
    printf("%d\n",v[88]); // 0,如果添加更多的元素，默认初始值是0
}