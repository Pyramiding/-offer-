//
// Created by W on 2019/3/1 0001.
//
// 面试题37：序列化二叉树
// 题目：请实现两个函数，分别用来序列化和反序列化二叉树。

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include "Utilities\BinaryTree.h"

using namespace std;

//
// NowCoder提交格式
//
//不能用，内存超限
class Solution1 {
public:
    string sHelper(BinaryTreeNode *node) {
        if (!node)
            return "$";
        return to_string(node->m_nValue) + "," +
               sHelper(node->m_pLeft) + "," +
               sHelper(node->m_pRight);
    }

    char* Serialize(BinaryTreeNode *root) {
        string str = sHelper(root);
        char *ret = new char[str.length() + 1];
        strcpy(ret, const_cast<char*>(str.c_str()));
        return ret;
    }

    BinaryTreeNode* dHelper(stringstream &ss) {
        string str;
        getline(ss, str, ',');
        if (str == "&")
            return nullptr;
        else
        {
            //auto *node = new BinaryTreeNode(stoi(str));
            auto *node = new BinaryTreeNode(atoi(str.c_str()));
            node->m_pLeft = dHelper(ss);
            node->m_pRight = dHelper(ss);
            return node;
        }
    }

    BinaryTreeNode* Deserialize(char *str) {
        stringstream ss(str);
        return dHelper(ss);
    }


private:

};
//也不能用，stoi不能用
class Solution2 {
public:
    void serializeHelper(BinaryTreeNode *node, string& s)
    {
        if (!node)
        {
            s.push_back('$');
            s.push_back(',');
            return;
        }
        s += to_string(node->m_nValue);
        s.push_back(',');
        serializeHelper(node->m_pLeft, s);
        serializeHelper(node->m_pRight, s);
    }
    char* Serialize(BinaryTreeNode *root)
    {
        if (!root)
            return nullptr;
        string s = "";
        serializeHelper(root, s);

        char *ret = new char[s.length() + 1];
        strcpy(ret, s.c_str());
        return ret;
    }

    BinaryTreeNode* deserializeHelper(string &s)
    {
        if (s.empty())
            return nullptr;
        if (s[0] == '#')
        {
            s = s.substr(2);
            return nullptr;
        }
        auto *ret = new BinaryTreeNode(stoi(s));
        s = s.substr(s.find_first_of(',') + 1);
        ret->m_pLeft = deserializeHelper(s);
        ret->m_pRight = deserializeHelper(s);
        return ret;
    }

    BinaryTreeNode* Deserialize(char *str)
    {
        if (!str)
            return nullptr;
        string s(str);
        return deserializeHelper(s);
    }
};

class Solution {
private:
    BinaryTreeNode* decode(char *&str) {
        if(*str=='#'){
            str++;
            return nullptr;
        }
        int num = 0;
        while(*str != ',')
            num = num*10 + (*(str++)-'0');
        str++;
        BinaryTreeNode *root = new BinaryTreeNode(num);
        root->m_pLeft = decode(str);
        root->m_pRight = decode(str);
        return root;
    }
public:
    char* Serialize(BinaryTreeNode *root) {
        if(!root) return "#";
        string r = to_string(root->m_nValue);
        r.push_back(',');
        char* left = Serialize(root->m_pLeft);
        char* right = Serialize(root->m_pRight);
        char* ret = new char[strlen(left) + strlen(right) + r.size()];
        strcpy(ret, r.c_str());
        strcat(ret, left);
        strcat(ret, right);
        return ret;
    }
    BinaryTreeNode* Deserialize(char *str) {
        return decode(str);
    }
};

void Serialize(const BinaryTreeNode* pRoot, ostream& stream)
{
    if(pRoot == nullptr)
    {
        stream << "$,";
        return;
    }

    stream << pRoot->m_nValue << ',';
    Serialize(pRoot->m_pLeft, stream);
    Serialize(pRoot->m_pRight, stream);
}

bool ReadStream(istream& stream, int* number)
{
    if(stream.eof())
        return false;

    char buffer[32];
    buffer[0] = '\0';

    char ch;
    stream >> ch;
    int i = 0;
    while(!stream.eof() && ch != ',')
    {
        buffer[i++] = ch;
        stream >> ch;
    }

    bool isNumeric = false;
    if(i > 0 && buffer[0] != '$')
    {
        *number = atoi(buffer);
        isNumeric = true;
    }

    return isNumeric;
}

void Deserialize(BinaryTreeNode** pRoot, istream& stream)
{
    int number;
    if(ReadStream(stream, &number))
    {
        *pRoot = new BinaryTreeNode();
        (*pRoot)->m_nValue = number;
        (*pRoot)->m_pLeft = nullptr;
        (*pRoot)->m_pRight = nullptr;

        Deserialize(&((*pRoot)->m_pLeft), stream);
        Deserialize(&((*pRoot)->m_pRight), stream);
    }
}

// ==================== Test Code ====================
bool isSameTree(const BinaryTreeNode* pRoot1, const BinaryTreeNode* pRoot2)
{
    if(pRoot1 == nullptr && pRoot2 == nullptr)
        return true;

    if(pRoot1 == nullptr || pRoot2 == nullptr)
        return false;

    if(pRoot1->m_nValue != pRoot2->m_nValue)
        return false;

    return isSameTree(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
           isSameTree(pRoot1->m_pRight, pRoot2->m_pRight);
}

void Test(const char* testName, const BinaryTreeNode* pRoot)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    PrintTree(pRoot);

    const char* fileName = "test.txt";
    ofstream fileOut;
    fileOut.open(fileName);

    Serialize(pRoot, fileOut);
    fileOut.close();

    // print the serialized file
    ifstream fileIn1;
    char ch;
    fileIn1.open(fileName);
    while(!fileIn1.eof())
    {
        fileIn1 >> ch;
        cout << ch;
    }
    fileIn1.close();
    cout << endl;

    ifstream fileIn2;
    fileIn2.open(fileName);
    BinaryTreeNode* pNewRoot = nullptr;
    Deserialize(&pNewRoot, fileIn2);
    fileIn2.close();

    PrintTree(pNewRoot);

    if(isSameTree(pRoot, pNewRoot))
        printf("The deserialized tree is same as the oritinal tree.\n\n");
    else
        printf("The deserialized tree is NOT same as the oritinal tree.\n\n");

    DestroyTree(pNewRoot);
}

//            8
//        6      10
//       5 7    9  11
void Test1()
{
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

    ConnectTreeNodes(pNode8, pNode6, pNode10);
    ConnectTreeNodes(pNode6, pNode5, pNode7);
    ConnectTreeNodes(pNode10, pNode9, pNode11);

    Test("Test1", pNode8);

    DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test2()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);

    Test("Test2", pNode5);

    DestroyTree(pNode5);
}

//        5
//         4
//          3
//           2
void Test3()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode2);

    Test("Test3", pNode5);

    DestroyTree(pNode5);
}

void Test4()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    Test("Test4", pNode5);

    DestroyTree(pNode5);
}

void Test5()
{
    Test("Test5", nullptr);
}

//        5
//         5
//          5
//         5
//        5
//       5 5
//      5   5
void Test6()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode61 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode62 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode71 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode72 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode1, nullptr, pNode2);
    ConnectTreeNodes(pNode2, nullptr, pNode3);
    ConnectTreeNodes(pNode3, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode5, nullptr);
    ConnectTreeNodes(pNode5, pNode61, pNode62);
    ConnectTreeNodes(pNode61, pNode71, nullptr);
    ConnectTreeNodes(pNode62, nullptr, pNode72);

    Test("Test6", pNode1);

    DestroyTree(pNode1);
}

void manytest()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
}


int main(int argc, char* argv[])
{
    manytest();

/*    vector<int> push = {5, 7, 6, 9, 11, 10, 8};
    Solution solver;
    vector<vector<int> > ret = solver.FindPath(pNode10, 22);
    for(auto elmt1: ret)
    {
        for(auto elmt2: elmt1)
            cout << elmt2 << " ";
        cout << endl;
    }*/

    //cout << boolalpha << ret << endl;

    return 0;
}