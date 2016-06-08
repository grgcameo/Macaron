
# coding=utf-8

class DuckHunting :
    ducks = 3

    def hunting(self):
        if self.ducks > 0 :
            print ("Catch !!")
            self.ducks -= 1
        else :
            print ("None Duck")

    def checkDucks(self):
        if self.ducks == 0 :
            print ("Good Dog !!")
        else :
            print (self.ducks)

import sys
print (sys.version)
