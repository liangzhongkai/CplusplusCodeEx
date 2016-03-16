
//  187MS	29320K	1727 B	C++
#include<iostream>

using namespace std;

const int N = 500001;

struct node{
	node *fail;
	node *next[26];
	int count;
	node(){
		fail = NULL;
		count = 0;
		memset(next, NULL, sizeof(next));
	}
}*q[N];
char keyword[51];
char str[1000001];
int head, tail;

void insert(char *str, node *root){
	node *p = root;
	int i = 0, index;
	while(str[i]){
		index = str[i] - 'a';
		if(p->next[index]==NULL)  p->next[index] = new node();
		p = p->next[index];
		i++;
	}
	p->count++;
}

void ac_auto(node *root){
	int i;
	root->fail = NULL;
	q[head++] = root;
	while(head!=tail){
		node *temp = q[tail++];
		node *p = NULL;
		for(i=0; i<26; i++){
			if(temp->next[i]!=NULL){
				if(temp==root) temp->next[i]->fail = root;
				else{
					p = temp->fail;
					while(p!=NULL){
						if(p->next[i]!=NULL){
							temp->next[i]->fail = p->next[i];   //指向相同字母
							break;
						}
						p = p->fail;
					}
					if(p==NULL) temp->next[i]->fail = root;
				}
				q[head++] = temp->next[i];
			}
		}
	}
}

int query(node *root){
	int i=0, cnt=0, index, len=strlen(str);
	node *p = root;
	while(str[i]){
		index = str[i] - 'a';
		while(p->next[index]==NULL && p!=root) p = p->fail;
		p = p->next[index];
		p = (p==NULL)?root:p;
		node *temp = p;
		while(temp!=root && temp->count!=-1){
			cnt += temp->count;
			temp->count = -1;
			temp = temp->fail;
		}
		i++;
	}
	return cnt;
}

int main()
{
	int n, t;
	scanf("%d", &t);
	while(t--){
		head = tail = 0;
		node *root = new node();
		scanf("%d", &n);
		getchar();
		while(n--){
			gets(keyword);
			insert(keyword, root);
		}
		ac_auto(root);
		scanf("%s", str);
		printf("%d\n", query(root));
	}

	return 0;
}