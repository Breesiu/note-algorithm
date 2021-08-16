class LRUCache {
public:
    //本题关键在于选择合适的数据结构实现题目要求的复杂度，然后根据题意模拟即可
    //list<pair<int, int>> (key, value)存在list中。unordered_map<int, list<pair<int, int>>::iterator> 存储key和key所在的list的位置。
    list<pair<int, int>> lis;
    unordered_map<int, list<pair<int, int>>::iterator> umap;
    int n;//容量
    LRUCache(int capacity) {
        n=capacity;
    }
    
    int get(int key) {
        auto it=umap.find(key);
        if(it!=umap.end()){
            int val=it->second->second;
            lis.erase(it->second);
            lis.push_front({key,val});
            umap[key]=lis.begin();
            return val;
        }else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        auto it=umap.find(key);
        if(it!=umap.end()){
            lis.erase(it->second);
            lis.push_front({key,value});
            umap[key]=lis.begin();
        }else{
            //添加元素时要考虑容量n
            lis.push_front({key,value});
            umap[key]=lis.begin();
            //如果超容量则删除列表最后一个元素
            if(lis.size()>n){
                umap.erase(lis.back().first);
                lis.pop_back();
            }
            
            
        }
        //cout<<"put:"<<umap[key]->first<<endl;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */