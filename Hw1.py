
import sympy as s

n = s.symbols('n')
f1 = int(input())
f2 = int(input())
f3 = int(input())
f4 = int(input())
f5 = int(input())
f6 = int(input())

F1 = n**f1
F2 = n**f2
F3 = n**f3
F4 = n**f4
F5 = n**f5
F6 = n**f6

eq1 = n**2 * F2 + n**2 * F1
eq2 = n**2 * F1 + n**2 *n * F3 + n**2 *n*F4 + n**2 *n*F5
eq3 = n**2 * F1 + n**2 *n * F3 + n**2 *n*F4 + n**2 *n*F6

print("eq1: ", eq1)
print("eq2: ", eq2)
print("eq3: ", eq3)
 #test123
 #test234
