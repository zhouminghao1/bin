import array as arr

arr1=arr.array('i', [1,2,3,4,5])
print(arr1)

revarray=arr1[::-1]
print(revarray)

new_array=arr.array('i',reversed(arr1))
print(new_array)

print(('-'*40))
sorted(revarray)
print(revarray)