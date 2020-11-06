#!/usr/bin/python
import random

while True:
    num = int(random.random() * 101)
    win = False

    print("Введите число")

    for i in range(5):
        num1 = int(input())
        if num1 > num:
            print("Загаданное число меньше")
        elif num1 < num:
            print("Загаданное число больше")
        else:
            print("Вы выиграли!")
            win = True
            break

    if not win:
        print("Вы проиграли. Загаданное число:", num)

    if not 1 == int(input("Хотите начать сначала? (1 - да)\n")):
        break
