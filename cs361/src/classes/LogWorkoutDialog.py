"""
C-06: LogWorkoutDialog
Auth: Nolan Flores
"""

import tkinter as tk
from tkinter import messagebox, ttk

from .Session import Session
from .ExercisePickerFrame import ExercisePickerFrame

WEEKDAYS = ["Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"]


class LogWorkoutDialog:
    def __init__(self, parent, planner):
        self.window = tk.Toplevel(parent)
        self.window.title("Log Workout")
        self.window.resizable(False, False)
        self._planner = planner

        f = ttk.Frame(self.window, padding=10)
        f.pack(fill="both", expand=True)

        ttk.Label(f, text="Day:").grid(row=0, column=0, sticky="w", pady=4)
        self._day_var = tk.StringVar()
        ttk.Combobox(f, textvariable=self._day_var, values=WEEKDAYS,
                     state="readonly", width=14).grid(row=0, column=1, sticky="w", padx=5)

        ttk.Label(f, text="Notes:").grid(row=1, column=0, sticky="w", pady=4)
        self._notes = ttk.Entry(f, width=28)
        self._notes.grid(row=1, column=1, sticky="w", padx=5)

        ttk.Label(f, text="Intensity (1–10):").grid(row=2, column=0, sticky="w", pady=4)
        self._intensity = tk.IntVar(value=5)
        ttk.Spinbox(f, from_=1, to=10, textvariable=self._intensity,
                    width=5).grid(row=2, column=1, sticky="w", padx=5)

        self._picker = ExercisePickerFrame(self.window)
        self._picker.frame.pack(fill="both", expand=True, padx=10, pady=5)

        btns = ttk.Frame(self.window, padding=(10, 0, 10, 10))
        btns.pack(fill="x")
        ttk.Button(btns, text="Log",    command=self._log).pack(side="left", padx=4)
        ttk.Button(btns, text="Cancel", command=self.window.destroy).pack(side="right", padx=4)

    def _log(self):
        day = self._day_var.get()
        if not day:
            messagebox.showerror("Missing day", "Please choose a day.", parent=self.window)
            return
        session = Session(
            id=len(self._planner.get_logs()) + 1,
            day=day,
            notes=self._notes.get().strip(),
            perceived_intensity=self._intensity.get(),
            workout=self._picker.get_workout(),
            date=None,
            duration_minutes=0,
        )
        self._planner.log_workout(session)
        messagebox.showinfo("Logged", "Workout logged!", parent=self.window)
        self.window.destroy()