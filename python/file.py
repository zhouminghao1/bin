load = "python\\test.txt"

#读文件
'''with open(load, 'r') as file:
  content = file.read()
  print(content)

print('-'*40)
with open(load, 'r') as file:
  line = file.readline()
  while line:
    print(line, end='')
    line = file.readline()
print()

print('-'*40)
with open(load, 'r') as file:
  lines = file.readlines()
  for line in lines:
    print(line, end='')'''


#写文件
'''with open(load, 'w') as file:
  file.write("Hello world!")

with open(load, 'r') as file:
  content = file.read()
  print(content)'''

lines = ["First line\n", "Second line\n", "Third line\n"]
with open(load, 'w') as file:
  file.writelines(lines)

with open(load, 'r') as file:
  content = file.read()
  print(content)
