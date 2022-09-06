import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import lognorm
import math
a = 104580.93
b = 409084324.46
c = 400055166835.44
D = [0.1, 3, 7, 2, 1, 3, 1.5, 1.5]
E = [0.5, 13, 35, 8, 3, 20, 5, 5]
ratio = [0, 0.103, 0.250, 0.069, 0.161, 0.011, 0.226, 0.179]
beta = 0.359  # the ratio of single-use plastic


def use_age(kind, year):
    d = D[kind] ** 2
    s = math.log((1 + d / (E[kind] ** 2))) ** 0.5
    mu = math.log(E[kind]) - 0.5 * math.log((1 + D[kind] / (E[kind] ** 2)))
    res = lognorm.cdf(year, s, scale=math.exp(mu)) - lognorm.cdf(year - 1, s,
                                                                 scale=math.exp(mu))
    return res


def AP(t):
    return a * (t**2) - b * t + c


def AW_s(t, x):
    res = 0
    res += AP(t - 1) * x * use_age(0, 1)
    res += AP(t - 2) * x * use_age(0, 2)
    return res


def AW_o(t):
    res = 0
    for i in range(1, t + 1):
        for j in range(1, 8):
            res += AP(t - i) * ratio[j] * use_age(j, i)
    return res


def Hp_test(year, x):
    res = 0
    t = year - 1950
    res = AW_s(t, x) * (1 - (0.7045 * year - 1394) / 100) + AW_o(t) * (1 -
                                                                       (0.7045 * year - 1394) / 100 - (0.7 * year - 1391) / 100)
    return res


"""x stands for the ratio of single-use plastic"""
if __name__ == ’__main__’:
    _Hp = [0]
    for i in range(2016, 2026):
        res = Hp_test(i, beta)
        _Hp.append(res)

    error = 0
    for i in range(1, 10):
        x = 0.3
        min_x = x
        while x > 0:
            x -= 0.002
            flag = False
            error = abs(Hp_test(2015 + i, x) / _Hp[i] - 1)
            if error < 0.1:
                flag = True
            if flag is True:
                if x < min_x:
                    min_x = x
            else:
                break
        print(str(2015 + i) + ": the minimum beta is " + format(min_x, ’.3f’) + ’, AW_s is ’ +
              format(AW_s(i + 2015, min_x), ’.2f’) + ’, AW_o is ’ +
              format(AW_o(i + 2015), ’.2f’) + " and Pull is " +
              format(Hp_test(i + 2015, min_x), ’.2f’) + ". The error is "
              + format(error, ’.4f’))
        print(" the origin beta is " + format(beta, ’.3f’) + ’, AW_s is ’ + format(AW_s(i + 2015, beta), ’.2f’) + ’, AW_o is ’ + format(AW_o(i + 2015), ’.2f’) + ’ and Pull is ’
              + format(Hp_test(i + 2015, beta), ’.2f’))
