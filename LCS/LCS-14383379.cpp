#include <bits/stdc++.h>
using namespace std;

const int maxN = 250500;
const int maxState = maxN << 1;

struct State {
    State *go[26], *suffix;
    int depth, id;
    long long cnt;
};
State pool[maxState], *point, *root, *sink;
int size;

State *newState(int dep) {
    point->id = size++;
    point->depth = dep;
    return point++;
}

void init() {
    point = pool;
    size = 0;
    root = sink = newState(0);
}

void insert(int a) {
    State *p = newState(sink->depth+1);
    State *cur = sink, *sufState;
    while (cur && !cur->go[a]) {
        cur->go[a] = p;
        cur = cur->suffix;
    }
    if (!cur)
        sufState = root;
    else {
        State *q = cur->go[a];
        if (q->depth == cur->depth + 1)
            sufState = q;
        else {
            State *r = newState(cur->depth+1);
            memcpy(r->go, q->go, sizeof(q->go));
            r->suffix = q->suffix;
            q->suffix = r;
            sufState = r;
            while (cur && cur->go[a] == q) {
                cur->go[a] = r;
                cur = cur->suffix;
            }
        }
    }
    p->suffix = sufState;
    sink = p;
}

int work(char buf[]) {
    //printf("%s", buf);
    int len = strlen(buf);
    int tmp = 0, ans = 0;
    State *cur = root;
    for (int i = 0; i < len; i++) {
        if (cur->go[buf[i]-'a']) {
            tmp++;
            cur = cur->go[buf[i]-'a'];
        } else {
            while (cur && !cur->go[buf[i]-'a'])
                cur = cur->suffix;
            if (!cur) {
                cur = root;
                tmp = 0;
            } else {
                tmp = cur->depth + 1;
                cur = cur->go[buf[i]-'a'];
            }
        }
        ans = max(ans, tmp);

    }
    return ans;
}

char ch[maxN];

int main() {
    scanf("%s", ch);
    init();
    int len = strlen(ch);
    for (int i = 0; i < len; i++)
        insert(ch[i]-'a');
    scanf("%s", ch);
    printf("%d\n", work(ch));
    return 0;
}
