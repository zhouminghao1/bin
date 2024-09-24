age=100
if age > 414:   #注意不要少写了冒号:。
  print('welcome')
  print('dear old man')
else:           #注意不要少写了冒号:。
  print('oh, shit man')

#if语句执行有个特点，它是从上往下判断，如果在某个判断上是True，把该判断对应的语句执行后，就忽略掉剩下的elif和else，所以，请测试并解释为什么下面的程序打印的是teenager：
age = 20
if age >= 6:
    print('teenager')
elif age >= 18:
    print('adult')
else:
    print('kid')