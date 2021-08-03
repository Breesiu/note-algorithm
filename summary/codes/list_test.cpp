#include<list>
using namespace std;
int main(){
    list<int> l;
    for(int i=0;i<10;i++)
        l.push_back(i);
    for(int i=0;i<10;i++)
        l.push_front(i);
    l.pop_front();
    l.pop_back();
    printf("%lu\n",l.size());
    l.erase(l.begin());
    printf("%d\n",*l.begin());
    l.insert(l.begin(),-1);
    printf("%d\n",*l.begin());
}