#include <iostream>
#include <string>
#define MAXSTACKSIZE 100

using namespace std;

bool IsStringRight(string &); // прототип функции проверки

struct STACK {          // структура СТЕК
  char A[MAXSTACKSIZE]; // контейнер элементов
  int v;                // индекс вершины стека
};

STACK S;

int main() {
  // Начальное состояние = Вершина стека = 0
  S.v = 0;

  string str;
  getline(cin, str); // ввод строки
  if (IsStringRight(str)) {
    cout << "String is right";
  } else {
    cout << "String is wrong";
  }
  return 0;
}

bool IsStringRight(string &str) {
  // НАПИШИТЕ ЭТУ ФУНКЦИЮ
  // ВОЗВРАЩАЕТ ИСТИНУ В СЛУЧАЕ, ЕСЛИ СТРОКА "ПРАВИЛЬНАЯ"
  // ВОЗВРАЩАЕТ ЛОЖЬ, ЕСЛИ СТРОКА "НЕ ПРАВИЛЬНАЯ"
  char temp;
  int i = 0;
  for (int i = 0; i < str.size(); ++i) {
    temp = str[i];
    if (temp != '}' && temp != '{' && temp != '[' && temp != ']' &&
        temp != '(' && temp != ')')
      continue;
    if (temp == '(' || temp == '{' || temp == '[') {
      S.A[S.v++] = temp;
    } else if (S.v == 0 || (temp == ')' && S.A[S.v - 1] != '(') ||
               (temp == '}' && S.A[S.v - 1] != '{') ||
               (temp == ']' && S.A[S.v - 1] != '[')) {
      return false;
    } else {
      S.v--;
    }
  }
  if (S.v != 0) {
    return false;
  }

  return true;
}
