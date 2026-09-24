"""
C-06: EditPlanDialog
Auth: Nolan Flores
"""

import tkinter as tk
from tkinter import messagebox, ttk

from .ExercisePickerFrame import ExercisePickerFrame

WEEKDAYS = ["Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"]


class EditPlanDialog:
    def __init__(self, parent, planner):
        self.window = tk.Toplevel(parent)
        self.window.title("Edit Workout Plan")
        self.window.resizable(False, False)
        self._planner = planner
        self._plans = planner.list_plans()

        if not self._plans:
            ttk.Label(self.window, text="No plans to edit.", padding=20).pack()
            ttk.Button(self.window, text="Close", command=self.window.destroy).pack(pady=5)
            return

        f = ttk.Frame(self.window, padding=10)
        f.pack(fill="both", expand=True)

        ttk.Label(f, text="Plan:").grid(row=0, column=0, sticky="w", pady=4)
        plan_labels = [
            f"Plan {i+1}  ({', '.join(p.workout_plan.keys())})"
            for i, p in enumerate(self._plans)
        ]
        self._plan_combo = ttk.Combobox(f, values=plan_labels, state="readonly", width=30)
        self._plan_combo.grid(row=0, column=1, padx=5)
        self._plan_combo.current(0)

        ttk.Label(f, text="Day:").grid(row=1, column=0, sticky="w", pady=4)
        self._day_var = tk.StringVar()
        ttk.Combobox(f, textvariable=self._day_var, values=WEEKDAYS,
                     state="readonly", width=14).grid(row=1, column=1, sticky="w", padx=5)

        ttk.Label(f, text="Action:").grid(row=2, column=0, sticky="w", pady=4)
        self._action = tk.StringVar(value="replace")
        action_frame = ttk.Frame(f)
        action_frame.grid(row=2, column=1, sticky="w", padx=5)
        ttk.Radiobutton(action_frame, text="Replace with exercise",
                        variable=self._action, value="replace").pack(anchor="w")
        ttk.Radiobutton(action_frame, text="Remove day",
                        variable=self._action, value="remove").pack(anchor="w")

        self._picker = ExercisePickerFrame(self.window)
        self._picker.frame.pack(fill="both", expand=True, padx=10, pady=5)

        btns = ttk.Frame(self.window, padding=(10, 0, 10, 10))
        btns.pack(fill="x")
        ttk.Button(btns, text="Apply",  command=self._apply).pack(side="left", padx=4)
        ttk.Button(btns, text="Cancel", command=self.window.destroy).pack(side="right", padx=4)

    def _apply(self):
        plan = self._plans[self._plan_combo.current()]
        day = self._day_var.get()
        if not day:
            messagebox.showerror("Missing day", "Please choose a day.", parent=self.window)
            return

        if self._action.get() == "remove":
            if day in plan._workout_plan:
                del plan._workout_plan[day]
                self._planner.save_plans()
            messagebox.showinfo("Done", f"'{day}' removed.", parent=self.window)
            self.window.destroy()
            return

        exercise = self._picker.get_workout()
        if not exercise:
            messagebox.showerror("Missing exercise", "Please select an exercise.", parent=self.window)
            return
        plan._workout_plan[day] = [exercise]
        self._planner.save_plans()
        messagebox.showinfo("Done", "Plan updated!", parent=self.window)
        self.window.destroy()