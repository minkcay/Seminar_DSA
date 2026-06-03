#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// -------------------------------------------------------------------------
// A. Integer Sort

const int N = 100000;

int Rand(int l, int r)
{
    static mt19937 gen(time(0));

    uniform_int_distribution<int> dis(l, r);

    return dis(gen);
}

// 1. Random Uniform
void generateInt_Test1(ofstream &fout)
{
    fout << N << "\n";

    for (int i = 0; i < N; i++)
    {
        fout << Rand(-1000000000, 1000000000)
             << "\n";
    }
}

// 2. Sorted
void generateInt_Test2(ofstream &fout)
{
    fout << N << "\n";

    for (int i = 1; i <= N; i++)
    {
        fout << i << "\n";
    }
}

// 3. Reverse Sorted
void generateInt_Test3(ofstream &fout)
{
    fout << N << "\n";

    for (int i = N; i >= 1; i--)
    {
        fout << i << "\n";
    }
}

// 4. Many Duplicates
void generateInt_Test4(ofstream &fout)
{
    fout << N << "\n";

    for (int i = 0; i < N; i++)
    {
        fout << Rand(1, 10)
             << "\n";
    }
}

// 5. Clustered Values
void generateInt_Test5(ofstream &fout)
{
    fout << N << "\n";

    int base = Rand(-100000, 100000);

    for (int i = 0; i < N; i++)
    {
        fout << base + Rand(-50, 50)
             << "\n";
    }
}

// -------------------------------------------------------------------------
// B. Lexicographic String Sort

string randomString(int len)
{
    string s;

    for (int i = 0; i < len; i++)
    {
        s += char('a' + Rand(0, 25));
    }

    return s;
}

// 1. Random Strings
void generateStrLexi_Test1(ofstream &fout)
{
    fout << Nc << "\n";

    for (int i = 0; i < Nc; i++)
    {
        fout << randomString(Rand(10, LEN))
             << "\n";
    }
}

// 2. Common Prefix
void generateStrLexi_Test2(ofstream &fout)
{
    fout << Nc << "\n";

    string prefix(95, 'a');

    for (int i = 0; i < Nc; i++)
    {
        string s = prefix;

        for (int j = 0; j < 5; j++)
        {
            s += char('a' + Rand(0, 25));
        }

        fout << s << "\n";
    }
}

// 3. Identical Strings
void generateStrLexi_Test3(ofstream &fout)
{
    fout << Nc << "\n";

    string s(100, 'm');

    for (int i = 0; i < Nc; i++)
    {
        fout << s << "\n";
    }
}

// 4. Many Duplicates
void generateStrLexi_Test4(ofstream &fout)
{
    fout << Nc << "\n";

    vector<string> base;

    for (int i = 0; i < 10; i++)
    {
        base.push_back(randomString(20));
    }

    for (int i = 0; i < Nc; i++)
    {
        fout << base[Rand(0, 9)]
             << "\n";
    }
}

// 5. Variable Length Strings
void generateStrLexi_Test5(ofstream &fout)
{
    fout << Nc << "\n";

    for (int i = 0; i < Nc; i++)
    {
        fout << randomString(Rand(10, LEN))
             << "\n";
    }
}

// -------------------------------------------------------------------------
// C. Length-aware Lexicographic String Sort

const int Nc = 10000;
const int LEN = 100;

template <typename T>
void my_swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int my_min(int a, int b)
{
    return (a < b) ? a : b;
}

string toLexString(int x)
{
    string s(LEN, 'a');
    for (int i = LEN - 1; i >= 0; --i)
    {
        s[i] = char('a' + (x % 26));
        x /= 26;
    }
    return s;
}

// 1. Last Diff
void generateStrLenLexi_Test1(ofstream &fout)
{
    fout << Nc << "\n";
    for (int i = 0; i < Nc; ++i)
    {
        string s(99, 'z');
        s += (char)('a' + (i % 26));
        fout << s << "\n";
    }
}

// 2. Anti-QuickSort Median-of-Three
vector<int> buildAntiMedian3(int n)
{
    vector<int> p(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;

    for (int len = 2; len <= n; len *= 2)
    {
        for (int l = 0; l < n; l += len)
        {
            int r = my_min(l + len - 1, n - 1);
            int mid = (l + r) >> 1;

            my_swap(p[mid], p[r]);

            if (mid - 1 >= l)
            {
                my_swap(p[l], p[mid - 1]);
            }
        }
    }
    return p;
}

void generateStrLenLexi_Test2(ofstream &fout)
{
    fout << Nc << "\n";
    vector<int> perm = buildAntiMedian3(Nc);
    vector<string> res(Nc);
    for (int i = 0; i < Nc; ++i)
    {
        res[perm[i]] = toLexString(i);
    }
    for (const string &s : res)
    {
        fout << s << "\n";
    }
}

// 3. Giong nhau hoan toan
void generateStrLenLexi_Test3(ofstream &fout)
{
    fout << Nc << "\n";
    string s(LEN, 'm');
    for (int i = 0; i < Nc; ++i)
    {
        fout << s << "\n";
    }
}

// 4. Random
void generateStrLenLexi_Test4(ofstream &fout)
{
    fout << Nc << "\n";
    mt19937 gen(time(0));
    uniform_int_distribution<> dis('a', 'z');
    for (int i = 0; i < Nc; ++i)
    {
        string s = "";
        for (int j = 0; j < LEN; ++j)
        {
            s += (char)dis(gen);
        }
        fout << s << "\n";
    }
}

// 5. Reverse Sorted
void generateStrLenLexi_Test5(ofstream &fout)
{
    fout << Nc << "\n";
    for (int i = Nc - 1; i >= 0; --i)
    {
        fout << toLexString(i) << "\n";
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Loi cu phap!\nSu dung: ./test_gen.<ext> <int/strlexi/strlenlexi> <1/2/3/4/5>\n";
        return 1;
    }

    string dataType = argv[1];

    int choice = argv[2][0] - '0';

    ofstream fout("test.in");
    if (!fout.is_open())
    {
        cout << "Khong the tao file test.in!\n";
        return 1;
    }

    if (dataType == "int")
    {
        switch (choice)
        {
        case 1:
            generateInt_Test1(fout);
            break;
        case 2:
            generateInt_Test2(fout);
            break;
        case 3:
            generateInt_Test3(fout);
            break;
        case 4:
            generateInt_Test4(fout);
            break;
        case 5:
            generateInt_Test5(fout);
            break;
        default:
            cout << "Test case cho 'int' khong hop le (chi nhan 1-5).\n";
            return 1;
        }
    }
    else if (dataType == "strlexi")
    {
        switch (choice)
        {
        case 1:
            generateStrLexi_Test1(fout);
            break;
        case 2:
            generateStrLexi_Test2(fout);
            break;
        case 3:
            generateStrLexi_Test3(fout);
            break;
        case 4:
            generateStrLexi_Test4(fout);
            break;
        case 5:
            generateStrLexi_Test5(fout);
            break;
        default:
            cout << "Test case cho 'strlexi' khong hop le (chi nhan 1-5).\n";
            return 1;
        }
    }
    else if (dataType == "strlenlexi")
    {
        switch (choice)
        {
        case 1:
            generateStrLenLexi_Test1(fout);
            break;
        case 2:
            generateStrLenLexi_Test2(fout);
            break;
        case 3:
            generateStrLenLexi_Test3(fout);
            break;
        case 4:
            generateStrLenLexi_Test4(fout);
            break;
        case 5:
            generateStrLenLexi_Test5(fout);
            break;
        default:
            cout << "Test case cho 'strlenlexi' khong hop le (chi nhan 1-5).\n";
            return 1;
        }
    }
    else
    {
        cout << "Kieu du lieu khong hop le! Vui long nhap int, strlexi hoac strlenlexi.\n";
        return 1;
    }

    fout.close();
    cout << "Da tao file test.in thanh cong cho bai [" << dataType << "] - Test so [" << choice << "]!\n";

    return 0;
}
