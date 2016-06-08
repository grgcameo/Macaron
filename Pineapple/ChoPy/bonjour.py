# coding=utf-8

import threading
import random

class Messenger(threading.Thread):
    def run(self):
        for _ in range(10):
            print (threading.currentThread().getName())


a = Messenger(name = "a 입니다.")
b = Messenger(name = "b 입니다.")



a.start()
b.start()



class ChatOn(threading.Thread):
    def run(self):
        print (random.randrange(1, 5))


c = ChatOn()

c.start()
