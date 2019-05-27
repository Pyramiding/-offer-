//
// Created by W on 2019/2/20 0020.
//
// 面试题9：用两个栈实现队列
// 题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail
// 和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。

#include <iostream>
#include <stack>
#include <queue>

//
// NowCoder提交格式
//
class Solution1 {
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()){
            while(!stack1.empty()){
                int data = stack1.top();
                stack1.pop();
                stack2.push(data);
            }
        }

        if(stack2.empty())
            throw string("queue is empty");
        int head = stack2.top();
        stack2.pop();

        return head;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};


// 相关题目：用两个队列实现一个栈
class Solution2 {
public:
    //数据的插入原则：保持一个队列为空，一个队列不为空，往不为空的队列中插入元素
    void push(int node) {
        if (queue2.empty())
            queue1.push(node);
        else
            queue2.push(node);
    }
    //元素删除，使非空队列中只剩一个元素
    int pop() {
        int ret;
        if (!queue1.empty()) {
            int size1 = queue1.size();
            while (size1 > 1) {
                queue2.push(queue1.front());
                queue1.pop();
                --size1;
            }
            ret = queue1.front();
            queue1.pop();
        } else {
            int size2 = queue2.size();
            while (size2 > 1) {
                queue1.push(queue2.front());
                queue2.pop();
                --size2;
            }
            ret = queue2.front();
            queue2.pop();
        }
        return ret;
    }

private:
    queue<int> queue1;
    queue<int> queue2;
};


template <typename T> class CQueue {
public:
    CQueue(void);
    ~CQueue(void);

    // 在队列末尾添加一个结点
    void appendTail(const T& node);

    // 删除队列的头结点
    T deleteHead();

private:
    stack<T> stack1;
    stack<T> stack2;
};


template <typename T> CQueue<T>::CQueue() = default;

template <typename T> CQueue<T>::~CQueue() = default;


template<typename T> void CQueue<T>::appendTail(const T& element) {
    stack1.push(element);
}

template<typename T> T CQueue<T>::deleteHead() {
    if(stack2.empty()) {
        while(!stack1.empty()) {
            T& data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }

    if(stack2.empty())
        throw string("queue is empty");

    T head = stack2.top();
    stack2.pop();

    return head;
}

// ====================测试代码====================
void Test(char actual, char expected) {
    if(actual == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}


int main(int argc, char* argv[])
{
    CQueue<char> queue;

    queue.appendTail('a');
    queue.appendTail('b');
    queue.appendTail('c');

    char head = queue.deleteHead();
    Test(head, 'a');

    head = queue.deleteHead();
    Test(head, 'b');

    queue.appendTail('d');
    head = queue.deleteHead();
    Test(head, 'c');

    queue.appendTail('e');
    head = queue.deleteHead();
    Test(head, 'd');

    head = queue.deleteHead();
    Test(head, 'e');


    Solution1 queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    cout << queue.pop() << endl;
    cout << queue.pop() << endl;
    queue.push(4);
    cout << queue.pop() << endl;
    cout << endl;

    Solution2 stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
    stack.push(4);
    cout << stack.pop() << endl;

    return 0;
}