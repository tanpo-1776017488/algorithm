#11.2 homework hwang jae hyeon

from tkinter import *

class KmMileConverter:
    def __init__(self,master):
        frame=Frame(master)
        frame.pack()
        self.km_var=DoubleVar()
        Entry(frame,textvariable=self.km_var).grid(row=0,column=0)
        Label(frame,text="Km").grid(row=0,column=1)
        
        self.mile_var=DoubleVar()
        Entry(frame,textvariable=self.mile_var).grid(row=0,column=2)
        Label(frame,text="Mile").grid(row=0,column=3)

        button=Button(frame,text='Km->Mile',command=self.convert_km_mile)
        button.grid(row=1,column=0,columnspan=2)

        button=Button(frame,text='Km<-Mile',command=self.convert_mile_km)
        button.grid(row=1,column=2,columnspan=2)

    def convert_km_mile(self):
        km=self.km_var.get()
        self.mile_var.set(km/1.60934)
    def convert_mile_km(self):
        mile=self.mile_var.get()
        self.km_var.set(mile*1.60934)

        
         
def main():
    global window
    window=Tk()
    window.wm_title("Km <-> Mile converter")
    app=KmMileConverter(window)
    window.mainloop()

if __name__=="__main__":
    main()
