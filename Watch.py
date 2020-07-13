import turtle
from turtle import *
from datetime import datetime

def jump(distance):
    penup(); forward(distance); pendown()

def rectangle(width, height):
    fd(width/2); lt(90); fd(height); lt(90);
    fd(width); lt(90); fd(height); lt(90);
    fd(width/2)

def make_hand_shape(name, width, height):
    reset()
    left(90); jump(-height*0.15); right(90)
    begin_poly()
    rectangle(width, height*1.15)
    end_poly()
    clock_hand = get_poly()
    register_shape(name, clock_hand)

def clockface(radius):
    reset()
    pensize(7)
    for i in range(60):
        jump(radius)
        if i % 5 == 0:
            fd(25)
            jump(-radius-25)
        else:
            dot(3)
            jump(-radius)
        rt(6)

def setup():
    global sec_hand, min_hand, hour_hand, writer
    mode("logo")    
    make_hand_shape("sec_hand", 5, 150)
    make_hand_shape("min_hand", 10, 130)
    make_hand_shape("hour_hand", 15, 110)
    clockface(160)
    hour_hand = Turtle()
    hour_hand.shape("hour_hand")
    hour_hand.color("black", "black")
    
    min_hand = Turtle()
    min_hand.shape("min_hand")
    min_hand.color("blue1", "blue1")
    
    sec_hand = Turtle()
    sec_hand.shape("sec_hand")
    sec_hand.color("red", "red")
    for hand in sec_hand, min_hand, hour_hand:
        hand.resizemode("user")
        hand.shapesize(1, 1, 3)
        hand.speed(0)
    ht()
    writer = Turtle()
    #writer.mode("logo")
    writer.ht()
    writer.pu()
    writer.bk(85)

def getWeekDayName(t):
    weekday_name = ["Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday", "Sunday"]
    return weekday_name[t.weekday()]

def getDateString(date):
    month_name = ["Jan.", "Feb.", "Mar.", "Apr.", "May", "June","July", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."]
    yr = date.year
    mn = month_name[date.month - 1]
    dy = date.day
    return "%s %d %d" % (mn, dy, yr)

def tick():
    t = datetime.today()
    sec = t.second + t.microsecond*0.000001
    minute = t.minute + sec/60.0
    hour = t.hour + minute/60.0
    try:
        tracer(False) # Terminator can occur here
        writer.clear()
        writer.home()
        writer.pencolor("darkred")
        writer.forward(65)
        writer.write(getWeekDayName(t),align="center", font=("Courier", 14, "bold"))
        writer.back(150)
        writer.pencolor("brown")
        writer.write(getDateString(t),align="center", font=("Courier", 14, "bold"))
        writer.back(30)
        hhmmss = "(%2d : %2d : %2d)"%(hour, minute, sec)
        writer.pencolor("red")
        writer.write(hhmmss, align="center", font=("Tahoma", 14, "bold"))
        writer.forward(115)
        tracer(True)
        sec_hand.setheading(6*sec + 90) # or here
        min_hand.setheading(6*minute + 90)
        hour_hand.setheading(30*hour + 90)
        tracer(True)
        ontimer(tick, 100)
    except Terminator:
        pass # turtle demo user pressed STOP

def main():
    tracer(False)
    setup()
    tracer(True)
    tick()
    return "Analog clock demo"

if __name__ == "__main__":
    mode("logo")
    turtle.setup(500, 500)
    turtle.title("My Analog Clock with Python")
    msg = main()
    #print(msg)
    mainloop()