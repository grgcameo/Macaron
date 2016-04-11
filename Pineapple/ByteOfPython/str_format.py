#coding=utf-8
#for korean
age = 20
name = 'Swaroop'

print '{0} was {1} years old when he wrote this book'.format(name, age)
print 'Why is {0} playing with that python?'.format(name)

print name + ' is' + str(age) + ' years old'


print '{} was {} years old when he wrote this book'.format(name, age)
print 'Why is {} playing with that python?'.format(name)


# 소수점 이하 셋째 자리까지 부동 소숫점 숫자 표기 (0.333)
print '{0:.3f}'.format(1.0/3)
# 밑줄(_)로 11칸을 채우고 가운데 정렬(^)하기 (___hello___)
print '{0:_^11}'.format('hello')
# 사용자 지정 키워드를 이용해 (Swaroop wrote A Byte of Python) 표기
print '{name} wrote {book}'.format(name='Swaroop',
book='A Byte of Python')
