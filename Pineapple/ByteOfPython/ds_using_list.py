#This is my shopping list (리스트는 변화될 수 있는 성질을 지녀서 비정적 이라고 한다
shoplist = ['apple', 'mango', 'carrot', 'banana', 1]

print 'I have', len(shoplist), 'items to purchase.'

print 'There items are:'

for item in shoplist:
    print item,   
    # print 다음에 , 는 줄바꿈 대신 공백을 출력하도록 지정 한 것

print '\nI also have to buy rice.'
shoplist.append('rice')

print 'My shopping list is now', shoplist

print 'I will sort my list now'
shoplist.sort()
print 'Sorted shopping list is', shoplist

print 'The first item I will buy is', shoplist[0]

olditem = shoplist[0]
del shoplist[0]

print 'I bought the', olditem
print 'My shopping list is now', shoplist
