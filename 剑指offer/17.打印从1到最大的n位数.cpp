//
// Created by W on 2019/2/22 0022.
//
// 面试题17：打印1到最大的n位数
// 题目：输入数字n，按顺序打印出从1最大的n位十进制数。比如输入3，则
// 打印出1、2、3一直到最大的3位数即999。

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    double Power(double base, int exponent) {

    }

private:
};

void PrintNumber(char* number);
bool Increment(char* number);
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index);

// ====================方法一====================
void Print1ToMaxOfNDigits_1(int n)
{
    if (n <= 0)
        return;

    char *number = new char[n + 1];
    memset(number, '0', n);
    number[n] = '\0';

    while (!Increment(number)) {
        PrintNumber(number);
    }

    delete[]number;
}

// 字符串number表示一个数字，在 number上增加1
// 如果做加法溢出，则返回true；否则为false
bool Increment(char* number)
{
    bool isOverflow = false;
    int nTakeOver = 0;
    int nLength = strlen(number);

    for (int i = nLength - 1; i >= 0; i--) {
        int nSum = number[i] - '0' + nTakeOver;
        if (i == nLength - 1)
            nSum++;

        if (nSum >= 10) {
            if (i == 0)
                isOverflow = true;
            else {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = '0' + nSum;
            }
        }
        else {
            number[i] = '0' + nSum;
            break;
        }
    }

    return isOverflow;
}

// ====================方法二====================
void Print1ToMaxOfNDigits_2(int n)
{
    if (n <= 0)
        return;

    char* number = new char[n + 1];
    number[n] = '\0';

    for (int i = 0; i < 10; ++i) {
        number[0] = i + '0';
        Print1ToMaxOfNDigitsRecursively(number, n, 0);
    }

    delete[] number;
}

void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index)
{
    if (index == length - 1) {
        PrintNumber(number);
        return;
    }

    for (int i = 0; i < 10; ++i) {
        number[index + 1] = i + '0';
        Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
    }
}

// ====================公共函数====================
// 字符串number表示一个数字，数字有若干个0开头
// 打印出这个数字，并忽略开头的0
void PrintNumber(char* number)
{
    bool isBeginning0 = true;
    int nLength = strlen(number);

    for (int i = 0; i < nLength; ++i) {
        if (isBeginning0 && number[i] != '0')
            isBeginning0 = false;

        if (!isBeginning0) {
            printf("%c", number[i]);
        }
    }

    printf("\t");
}

// ====================测试代码====================
void Test(int n)
{
    printf("Test for %d begins:\n", n);

    Print1ToMaxOfNDigits_1(n);
    Print1ToMaxOfNDigits_2(n);

    printf("\nTest for %d ends.\n", n);
}

// 大数加法
string plusTwoNum(string num1, string num2){
    int isNegative1 = 0, isNegative2 = 0;

    if(num1.size() < num2.size()){
        //把num1固定为位数较多的那个数
        string temp = num1;
        num1 = num2;
        num2 = temp;
    }

    int length1 = num1.size(), length2 = num2.size(), flag = 0, a, b, sum;
    while(length1 > 0){
        a = num1[length1 - 1] - '0';
        if(length2 > 0)
            b = num2[length2 - 1] - '0';
        else
            b = 0;

        sum = a + b + flag;
        if(sum >= 10){
            num1[length1 - 1] = char('0' + sum % 10);
            flag = 1;
        }
        else{
            num1[length1 - 1] = char('0' + sum);
            flag = 0;
        }
        length1--;
        length2--;
    }

    if (flag == 1)
        num1 = "1" + num1;
    return num1;
}

int main(int argc, char* argv[])
{
/*    Test(1);
    Test(2);
    Test(3);
    Test(0);
    Test(-1);*/

    Solution solver;
    vector<int> arr = {3, 4, 5, 1, 2};
    int result = 0;
    //result = solver.NumberOf1(7);
    cout << result << endl;

    string a = "98", b = "17";
    string c;
    c = plusTwoNum(a, b);
    cout << c << endl;

    // 输出含有前置0的字符串
    string d = "00123";
    int isBegin0 = 1;
    for(int i = 0; i < d.size(); ++i){
        if(isBegin0 && d[i] != '0'){
            isBegin0 = 0;
        }
        if(!isBegin0)
            cout << d[i];
    }

    return 0;
}
