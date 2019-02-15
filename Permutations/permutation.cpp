/*Exercise 2 CtCI*/

#include <iostream>
#include <stdio.h>
#include "string.h"
using namespace std;

bool checkPerms(char* masterStr, int masterLen, char* testStr, int testLen);
template<class T> void merge(T* a, int n1, int n2);
template<class T> void sort(T* a, int n);

int main()
{
    int masterLength, testLength;
    printf("Enter master string length..\n");
    scanf("%d", &masterLength);
    char* masterString = new char[masterLength];
    printf("Enter master string...\n");
    scanf("%s", masterString);

    printf("Enter test string length..\n");
    scanf("%d", &testLength);
    char* testString = new char[testLength];
    printf("Enter test string...\n");
    scanf("%s", testString);

    bool result;
    result = checkPerms(masterString, masterLength, testString, testLength);
    cout << "Master string contains permutation of sub string: " << result << endl;

    delete [] masterString;
    delete [] testString;
    return 0;
}

bool checkPerms(char* masterStr, int masterLen, char* testStr, int testLen)
{
    if(masterStr == nullptr || testStr == nullptr){
        cout << "string inputs cannot be NULL\n";
        return false;
    }
    if(masterLen < testLen){
        cout << "master length cannot be less than test length\n";
        return false;
    }
    bool mismatchFound;
    int countMatchedChars;
    char* subStr = new char[testLen];
    sort(testStr, testLen);
    for(int i = 0; i < (masterLen - testLen + 1); i++)
    {
        mismatchFound = false;
        countMatchedChars = 0;
        for(int k = 0; k < testLen; k++)
        {
            subStr[k] = masterStr[i + k];
        }
        sort(subStr, testLen);
        while(!mismatchFound && countMatchedChars != testLen)
        {
            if(subStr[countMatchedChars] == testStr[countMatchedChars]){
                countMatchedChars++;
                continue;
            }
            mismatchFound = true;
        }
        if(countMatchedChars == testLen){
            delete [] subStr;
            return true;
        }
    }
    delete [] subStr;
    return false;
}

template<class T>
void merge(T* a, int n1, int n2)
{
    T* temp = new T[n1 + n2];
    int i = 0, j1 = 0, j2 = 0;
    while(j1 < n1 && j2 < n2)
        temp[i++] = ( a[j1] <= a[n1+j2] ? a[j1++] : a[n1+j2++] );
    while(j1 < n1)
        temp[i++] = a[j1++];
    while(j2 < n2)
        temp[i++] = (a+n1)[j2++];
    for(i = 0; i < n1+n2; i++)
        a[i] = temp[i];
    delete [] temp;
}

template<class T>
void sort(T* a, int n)
{
    if(n > 1)
    {
        int n1 = n/2;
        int n2 = n - n1;
        sort(a, n1);
        sort(a+n1, n2);
        merge(a, n1, n2);
    }
}
