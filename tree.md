# 二叉树

## 遍历

递归版本的遍历十分简单，略过。

以下介绍一种根据`first()`和`next()`接口写迭代版遍历的一种方法，节点的结构和算法入口如下：

```cpp
class TreeNode {
    public:
        int v;
        TreeNode *l;
        TreeNode *r;
        TreeNode *p;
        TreeNode(int x) : v(x), l(NULL), r(NULL), p(NULL) {}
        TreeNode* next() {} // 表示该节点访问之后的下一个访问节点
        TreeNode* first() {} // 表示以该节点为跟节点的子树要访问的第一个节点
};

void travel(TreeNode* c){
    if(c!=NULL){
        printf("%d\n",c->v);
        travel(c->next());
    }
}
```

对于先序中序和后续，分别实现不同的`first()`和`next()`接口即可，参考答案如下：

* 先序：

```cpp
TreeNode* TreeNode::first() {
    return this;
}
TreeNode* TreeNode::next() {
    if(l)return l->first();
    else if(r) r->first();
    else NULL;
}
```

* 中序：

```cpp
TreeNode* TreeNode::first() {
    TreeNode* t = this;
    while(t->l)t=t->l;
    return t;
}
TreeNode* TreeNode::next() {
    if(r)return r->first();
    else{
        TreeNode* t = this;
        while(t->p && t->p->r == t)t=t->p;
        return t->p;
    };
}
```

* 后序：

```cpp
TreeNode* TreeNode::first() {
    TreeNode* t = this;
    while(t->l||t->r)t=(t->l?t->l:t->r);
    return t;
}
TreeNode* TreeNode::next() {
    if(p){
        if(p->l == this){
            if(p->r)return p->r->first();
            else p;
        }else{
            return p;
        }
    }else NULL;
}
```

## BBST

### 红黑树