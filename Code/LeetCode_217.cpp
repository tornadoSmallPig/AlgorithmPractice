#include<iostream>
using namespace std;
#include<cmath>
#include<vector>
#include<string.h>
struct HashItem
{
    int set;//是否存放了元素
    int data;//数据
};
struct HashMap
{
    int size;
    HashItem *map;
};

bool containsDuplicate(vector<int> nums) 
{
    HashMap* m = (HashMap*)malloc(sizeof(HashMap));//创建哈希表
    m->map = (HashItem*)malloc(sizeof(HashItem) * nums.size() * 1.1);//分配地址空间（该空间要有一定剩余，以防止内存溢出）
    m->size = 0;//size设零
    memset(m->map, 0, sizeof(HashItem) * nums.size());//全设置为0
    int hashpos = 0;//哈希地址
    int hashLen = nums.size();//哈希表长度
    int hashSlice = 0;        //哈希子表大小

    /*根据hash表的长度确定哈希子表的大小*/
    if (hashLen < 100)
    {
        hashSlice = 1;
    }
    else if (hashLen < 1000)
    {
        hashSlice = 100;
    }
    else
    {
        hashSlice = 1000;
    }

    for (int i = 0; i < hashLen; i++)//遍历每个元素
    {
        int j = 0;
        int pos = 0;
        int last = -1;
        hashpos = nums[i] % hashSlice;//哈希函数为 hashpos = 数组下标 % hashSlice（哈希子表长度）
        if (hashpos < 0) hashpos = ~hashpos + 1;//如果为负数，则取反加一（其作用是对操作数的每一个二进制位取反）
        do
        {
            pos = hashpos + (hashSlice * j);
            if (m->map[pos].set)//如果存放了元素
            {
                if (m->map[pos].data == nums[i])
                {
                    return true;
                }    
            }
            else if (last == -1)
            {
                last = j;
                break;
            }
            j++;
        } while (hashpos + (hashSlice * j) <= hashLen);
        if (last != -1)
        {
            m->map[last * hashSlice + hashpos].data = nums[i];
            m->map[last * hashSlice + hashpos].set = 1;
        }
    }
    return false;
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);  // 计算数组长度
    std::vector<int> nums(arr, arr + n);
    cout<<containsDuplicate(nums);
    system("pause");
}