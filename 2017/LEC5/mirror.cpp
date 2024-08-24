#include <iostream>
#include <queue>
#include <stack>

using namespace std;

void mirror(queue<string> &q) {
  int size = q.size();
  stack<string> s;
  for (int i = 0; i < size; i++) {
    s.push(q.front());
    q.push(q.front());
    q.pop();
  }
  for (int i = 0; i < size; i++) {
    q.push(s.top());
    s.pop();
  }
}

int main() {

  queue<string> q;
  q.push("a");
  q.push("b");
  q.push("c");

  mirror(q);

  while (!q.empty()) {
    cout << q.front() << " ";
    q.pop();
  }
  cout << endl;

  return 0;
}
