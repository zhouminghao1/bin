students = ['minghao', 'yihan', 'zeli'] #这是list
print(students)
students.append('shixing')
print(students)
students.insert(2,'sicheng')
print(students)
students.pop()
print(students)
students.pop(1)
print(students)
print(students[1])
classmates = ('Michael', 'Bob', 'Tracy') #这是tuple 现在，classmates这个tuple不能变了，它也没有append()，insert()这样的方法。其他获取元素的方法和list是一样的，你可以正常地使用classmates[0]，classmates[-1]，但不能赋值成另外的元素。
#不可变的tuple有什么意义？因为tuple不可变，所以代码更安全。如果可能，能用tuple代替list就尽量用tuple