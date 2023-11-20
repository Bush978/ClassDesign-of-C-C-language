#include "iostream"
#include "cstring"
#include<stdlib.h>
#include <bits/stdc++.h>
using namespace std;
#define MAXLEN 5000			//串的最大长度
typedef struct {
    char* ch;			//存储串的一维数组
    int length;				//串的当前长度  
    string s;
}HString;


void InputRule(HString* ip, int n)
{//输入n条规则，并将其中的n个ip地址存放到ip数组 
    int number = 0;
    string c;
    while (number < n) {
        string c;
        getline(cin, c);
        for (int i = 0; i < c.length(); i++)
        {
            if (isdigit(c[i]))
                ip[number].s += c[i];
            else if (c[i] == '.')
                ip[number].s += c[i];
        }
        if (ip[number].s[ip[number].s.length() - 1] == '.')
            ip[number].s.erase(ip[number].s.length() - 1, 1);
        number++;
    }

}

void InputLog(HString& log, int m)
{//输入m条日志，并合并存放到log
    int number = 0;
    while (number < m) {
        string c;
        getline(cin, c);
        for (int i = 0; i < c.length(); i++)
        {
            if (isdigit(c[i]))
                log.s += c[i];
            else if (c[i] == '.')
                log.s += c[i];
            else if (c[i] == ' ')
                continue;
        }
        number++;
    }
}

void GetNext(HString pattern, int* next)
{//求模式串pattern的next函数值并存入数组next
    int i = 1, j = 0;
    next[1] = 0;
    while (i < pattern.s.length())
    {
        if (j == 0 || pattern.s[i] == pattern.s[j])
        {
            i++; j++;
            next[i] = j;
        }
        else j = next[j];
    }
}

int IndexKMP(HString target, HString pattern, int* next)
{//KMP匹配算法,target为主串，pattern为子串。
//匹配成功返回主串中所含子串第一次出现的位置，否则返回-1。
//调用GetNext函数获取模式串的next数组
    GetNext(pattern, next);
    int i = 0, j = 1;
    while (i < target.s.length() && j < pattern.s.length()) {
        if (j == 0 || target.s[i] == pattern.s[j]) {
            i++; j++;
        }
        else j = next[j];
    }
    if (j >= pattern.s.length())
        return 1;
    else return -1;
}
//3 3
//protocol:tcp ip:225.93.118.39 msg:"Network intrusion detected."
//protocol:tcp ip:152.213.218.150 msg:"Network intrusion detected."
//protocol:tcp ip:181.164.101.231 msg:"Network intrusion detected."
//Proto Recv-Q Send-Q Local-Address Foreign-Address State
//tcp 0 0 36.51.200.67:95403 40.56.49.213:29716 LAST_ACK
//tcp 0 0 215.142.133.153:49323 106.54.135.230:18487 CLOSED
//1 6
//protocol:tcp ip:44.207.25.205 msg:"Network intrusion detected."
//Proto Recv-Q Send-Q Local-Address Foreign-Address State
//tcp 0 0 63.228.177.122:83999 115.120.78.164:25267 ESTABLISHED
//tcp 0 0 91.62.129.226:75977 77.138.44.135:71910 ESTABLISHED
//tcp 0 0 12.70.45.198:24940 44.207.25.205:7927 CLOSE_WAIT
//tcp 0 0 155.212.113.157:94592 147.138.105.205:64521 LAST_ACK
//tcp 0 0 148.0.118.155:33854 128.61.218.176:83248 LISTEN
int main()
{
    int n, m;
    cin >> n >> m;
    getchar();


    HString ip[5000];//ip数组存放n个ip地址 
    InputRule(ip, n);

    HString log;
    log.ch = (char*)malloc(sizeof(char) * 10000);
    strcpy(log.ch, "");
    log.length = 0;
    InputLog(log, m);

    for (int i = 0; i < n; i++)
    {
        int* next = new int[ip[i].length];
        if (IndexKMP(log, ip[i], next) != -1)
        {
            cout << "Intrusion." << endl;
            return 0;
        }
    }
    cout << "No Intrusion." << endl;
    return 0;

}
