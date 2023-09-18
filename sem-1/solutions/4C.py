s = input()
try:
    result = eval(s)
    print(result)
except SyntaxError:
    print("WRONG")
except NameError:
    print("WRONG")