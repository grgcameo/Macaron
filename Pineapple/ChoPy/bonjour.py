# coding=utf-8

# def
MY_FILE_NAME = "FirstFile.txt"

def writeToFile(strInput):
    my_file = open(MY_FILE_NAME, "wb")
    print (my_file.mode)
    print (my_file.name)
    my_file.write(strInput)
    my_file.close()

def readFromFile():
    my_file = open(MY_FILE_NAME, "rb")
    print (my_file.read())
    my_file.close()


writeToFile("Hello, python!!")
readFromFile()



