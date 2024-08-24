#include <iostream>
#include <queue>

using namespace std;

int main() {

  queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  int size = q.size();
  for (int i = 0; i < size; i++) {
    q.push(q.front());
    q.push(q.front());
    q.pop();
  }

  cout << "q: ";
  for (; !q.empty(); q.pop())
    cout << q.front() << ' ';
  cout << '\n';

  return 0;
}
