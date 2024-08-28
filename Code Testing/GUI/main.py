from scaraGUI import SimpleGUI
from inverseKinematics import *
import math
import tkinter as tk

if __name__ == "__main__":
    root = tk.Tk()
    app = SimpleGUI(root)
    root.protocol("WM_DELETE_WINDOW", app.on_closing)
    root.mainloop()