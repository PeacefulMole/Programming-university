#!/usr/bin/python
def create(num, start, step):
  data = [start + i*step for i in range(num)]
  return data
def sort(data):
  return sorted(data)
print1 = print
def print(data):

  return print1(data)


print("Введите размер массива")
size = int(input())
print("Введите начальное число")
start = int(input())
print("Введите элемент ариф прогрессии")
step = int(input())
data = create(size, start,step)
data = sort(data)
print(data)
