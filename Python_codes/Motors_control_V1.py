# from tkinter import Tk

def lef(event = None):
    print("lf")
def rig(event = None):
    print("rig")
def up(event = None):
    print("up")
def dw(event = None):
    print("dw")
    
# root = Tk() #also works on other TK widgets
# sortir = True
# 
# print("loop")
# 
# root.bind("<Right>", lef())
# root.bind("<Left>", rig())
# root.bind("<Up>", up())
# root.bind("<Down>", dw())
# root.mainloop()


import keyboard
keyboard.add_hotkey("<Right>", lef())
keyboard.add_hotkey("<Left>", rig())
keyboard.add_hotkey("<Up>", up())
keyboard.add_hotkey("<Down>", dw())
