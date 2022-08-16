from fractions import Fraction
num = input()
zi = Fraction(num).numerator
mu = Fraction(num).denominator
whole = int(zi/mu)
zi -= mu * whole
print('%d %d %d' %(whole,zi,mu))
