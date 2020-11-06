#!/usr/bin/python
print("Введите число, с которым будут производится расчёты факториала")

a = int(input())
result = 1

for i in range(2, a + 1):
    result *= i

print(result)
