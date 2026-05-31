#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100000 + 5; 
unsigned int a[MAXN], b[MAXN];
int cnt[65536];

const int BUFFER_SIZE = 1 << 20;
char in_buf[BUFFER_SIZE];
int in_ptr = 0, in_len = 0;

inline char getChar() {
    if (in_ptr == in_len) {
        in_len = fread(in_buf, 1, BUFFER_SIZE, stdin);
        in_ptr = 0;
        if (in_len == 0) return EOF;
    }
    return in_buf[in_ptr++];
}

inline bool readInt(int &x) {
    char c = getChar();
    while (c <= ' ' && c != EOF) c = getChar();
    if (c == EOF) return false;
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = getChar();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getChar();
    }
    if (neg) x = -x;
    return true;
}

char out_buf[BUFFER_SIZE];
int out_ptr = 0;

inline void writeChar(char c) {
    if (out_ptr == BUFFER_SIZE) {
        fwrite(out_buf, 1, BUFFER_SIZE, stdout);
        out_ptr = 0;
    }
    out_buf[out_ptr++] = c;
}

inline void writeInt(int x) {
    if (x < 0) {
        writeChar('-');
        x = -x;
    }
    if (x == 0) {
        writeChar('0');
        return;
    }
    char s[12];
    int idx = 0;
    while (x > 0) {
        s[idx++] = (x % 10) + '0';
        x /= 10;
    }
    while (idx > 0) {
        writeChar(s[--idx]);
    }
}

inline void flushOut() {
    if (out_ptr > 0) {
        fwrite(out_buf, 1, out_ptr, stdout);
        out_ptr = 0;
    }
}

void radixSort(int n) {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[a[i] & 0xFFFF]++;
    for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--cnt[a[i] & 0xFFFF]] = a[i];

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[(b[i] >> 16) ^ 0x8000]++;
    for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) a[--cnt[(b[i] >> 16) ^ 0x8000]] = b[i];
}

int main() {
    int n;
    if (!readInt(n)) return 0;

    for (int i = 0; i < n; i++) {
        int temp;
        readInt(temp);
        a[i] = (unsigned int)temp;
    }

    radixSort(n);

    writeInt(n);
    writeChar('\n');
    for (int i = 0; i < n; i++) {
        writeInt((int)a[i]);
        writeChar('\n');
    }

    flushOut();
    return 0;
}
