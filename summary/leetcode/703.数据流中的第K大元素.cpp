/*
保留一个k个元素的小项堆即可
*/

class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int> > pq;
    int k;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for(int i=0;i<nums.size();i++)pq.push(nums[i]);
        while(pq.size()>k)pq.pop();
    }
    
    int add(int val) {
        if(pq.size()<k){
            pq.push(val);
        }else if(val>pq.top()){
            pq.push(val);
            pq.pop();
        }
        if(pq.size()<k)return 0;
        else return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */