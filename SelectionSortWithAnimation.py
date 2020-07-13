from turtle import *
from array import *
import random
import time
def rectangle(length, width): 
    seth(0)
    lt(90);fd(length);lt(90);fd(width) 
    lt(90);fd(length);lt(90);fd(width)

def register_bar(length=1, width=1):
    reset() 
    begin_poly();rectangle(length, width);end_poly()
    poly=get_poly()
    register_shape("Bar", poly)
    down()

def make_bar(length, width):
    tracer(False)
    bar=Turtle()
    bar.up()
    bar.shape("Bar")
#color= random.choice(["red", "green", "blue", "yellow", "pink", "purple"])
    color="blue"
    bar.color(color)
    bar.shapesize(length, width)
    return bar

def printBarPositions(bar_list, Arr, arr_size):
    print("A : ", Arr)
    print("Bar_positions : ", end="")
    for k in range(len(bar_list)):
        bar=bar_list[k]
        x,y=bar.pos()
        print("{} ".format(x), end="")
    print() 
def animateSelectionSorting(bar_list, Arr, arr_size):
    tracer(False)
    delay=1

    for i in range(0,arr_size-1):
        min_j=i
        for j in range(i+1, arr_size):
            if (Arr[min_j]>Arr[j]):
                min_j=j
        if (min_j != i):
            temp_bar = bar_list[min_j]
            bar_list[min_j]=bar_list[i]
            bar_list[i]=temp_bar
            bar_list[i].setx(min_x + x_space * i)
            bar_list[min_j].setx(min_x + x_space * min_j)
            bar_list[i].color("red")
            bar_list[min_j].color("red")
            temp=Arr[min_j]
            Arr[min_j]=Arr[i]
            Arr[i]=temp
            update() 
        time.sleep(0.1)
def main():
    global min_x, min_y, max_x, max_y, bar_width, A, array_size, x_space
    screen=Screen()
    screen.setup(1600, 900)
    max_x = screen.window_width()//2-50
    max_y = screen.window_height()//2-50
    min_x =-max_x
    min_y =-max_y
    register_bar()
    array_size = 200
    bar_width=5
    x_space =7
    y_step=4
    A=array('i')
    for i in range(array_size):
        A.append(array_size-i)
    random.shuffle(A)
    bar_list = []
    for i in range(array_size):
        length=A[i]*y_step+1
        bar=make_bar(length, bar_width)
        pos_x = min_x + x_space *i
        pos_y = min_y;bar.setpos(pos_x, pos_y)
        bar_list.append(bar)
    animateSelectionSorting(bar_list, A, array_size)

if __name__ == "__main__":
    main()