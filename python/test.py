dict_list = [
    {'name': 'Alice', 'age': 25},
    {'name': 'Bob', 'age': 20},
    {'name': 'Charlie', 'age': 30}
]

# 按年龄排序（升序）
sorted_list = sorted(dict_list, key=lambda x: x['age'])