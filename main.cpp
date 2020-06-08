#include <stdio.h>

#include <string.h>

#include <iostream>

using namespace std;

typedef struct NODE {

struct NODE *left, *right;

int frequency;

char c;

} *node;

struct NODE character_pool[256] = {{0}};

node alphabet_queue[255], *q = alphabet_queue - 1;

int number_of_nodes = 0, queue_end = 1;

char *codeArray[128] = {0}, buffer[1024];

node makeNewNode(int frequency, char c, node a, node b)

{

node temp = character_pool + number_of_nodes++;

if (frequency) temp->c = c, temp->frequency = frequency;

else {

temp->left = a, temp->right = b;

temp->frequency = a->frequency + b->frequency;

}

return temp;

}

void queueInsert(node n)

{

int j, i = queue_end++;

while ((j = i / 2)) {

if (q[j]->frequency <= n->frequency) break;

q[i] = q[j], i = j;

}

q[i] = n;

}

node queueRemove()

{

int i, l;

node n = q[i = 1];

if (queue_end < 2) return 0;

queue_end--;

while ((l = i * 2) < queue_end) {

if (l + 1 < queue_end && q[l + 1]->frequency < q[l]->frequency) l++;

q[i] = q[l], i = l;

}

q[i] = q[queue_end];

return n;

}

void build_codeArray(node n, char *string, int len)

{

static char *out = buffer;

if (n->c) {

string[len] = 0;

strcpy(out, string);

codeArray[n->c] = out;

out += len + 1;

return;

}

string[len] = '0'; build_codeArray(n->left, string, len + 1);

string[len] = '1'; build_codeArray(n->right, string, len + 1);

}

void initialisation(const char *string)

{

int i, frequency[128] = {0};

char c[16];

while (*string) frequency[(int)*string++]++;

for (i = 0; i < 128; i++)

if (frequency[i]) queueInsert(makeNewNode(frequency[i], i, 0, 0));

while (queue_end > 2)

queueInsert(makeNewNode(0, 0, queueRemove(), queueRemove()));

build_codeArray(q[1], c, 0);

}

void encodeArray(const char *string, char *out)

{

while (*string) {

strcpy(out, codeArray[*string]);

out += strlen(codeArray[*string++]);

}

}

void decodeArray(const char *string, node temp)

{

node n = temp;

while (*string) {

if (*string++ == '0') n = n->left;

else n = n->right;

if (n->c) putchar(n->c), n = temp;

}

putchar('\n');

if (temp != n) cout<<"invalid input by user \n";

}

int main(void)

{

int i;

char *string = "aaaaaabccccccddeeeee"; // you can modify it by taking input from user

char buffer[1024];

initialisation(string);

for (i = 0; i < 128; i++)

if (codeArray[i]) cout<<"'"<<(char)i<<"' "<<":"<<codeArray[i]<<endl;

encodeArray(string, buffer);

cout<<"encoded : "<<buffer;

return 0;

}