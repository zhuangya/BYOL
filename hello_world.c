#include <stdio.h>

int forloop (int);
int whileloop (int);

int main (int argc, char** argv) {
  //forloop(5);
  whileloop(5);
  return 0;
}

int forloop (int times) {
  for (int i = 0; i < times; i++) {
    puts("Hello, world!");
  }
  return 0;
}

int whileloop (int times) {
  while (times-- > 0) {
    puts("Hello, world!");
  }
  return 0;
}
