"""
C-06: CreatePlanDialog
Auth: Nolan Flores
"""

import tkinter as tk
from tkinter import messagebox, ttk

from .WorkoutPlan import WorkoutPlan
from .ExercisePickerFrame import ExercisePickerFrame
from .SuggestionEngine import SuggestionEngine

WEEKDAYS = ["Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"]


class CreatePlanDialog:
    def __init__(self, parent, planner):
        self.window = tk.Toplevel(parent)
        self.window.title("Create Workout Plan")
        self.window.resizable(False, False)
        self._planner = planner
        self._plan = WorkoutPlan()
        self._engine = SuggestionEngine()

        top = ttk.Frame(self.window, padding=10)
        top.pack(fill="x")
        ttk.Label(top, text="Day:").grid(row=0, column=0, sticky="w")
        self._day_var = tk.StringVar()
        ttk.Combobox(top, textvariable=self._day_var, values=WEEKDAYS, state="readonly", width=12).grid(row=0, column=1, padx=5)

        self._picker = ExercisePickerFrame(self.window)
        self._picker.frame.pack(fill="both", expand=True, padx=10)

        summary_frame = ttk.LabelFrame(self.window, text="Added so far", padding=5)
        summary_frame.pack(fill="both", padx=10, pady=5)
        self._summary = tk.Text(summary_frame, height=5, state="disabled", font=("Courier", 9))
        self._summary.pack(fill="both")

        suggestion_frame = ttk.LabelFrame(self.window, text="Suggestions", padding=5)
        suggestion_frame.pack(fill="x", padx=10, pady=5)
        self._suggestion_text = ttk.Label(suggestion_frame, text="Add exercises to see suggestions.", wraplength=380, justify="left")
        self._suggestion_text.pack(anchor="w")

        btns = ttk.Frame(self.window, padding=(10, 0, 10, 10))
        btns.pack(fill="x")
        ttk.Button(btns, text="Add Exercise", command=self._add).pack(side="left", padx=4)
        ttk.Button(btns, text="Save Plan", command=self._save).pack(side="left", padx=4)
        ttk.Button(btns, text="Cancel", command=self.window.destroy).pack(side="right", padx=4)

    def _add(self):
        day = self._day_var.get()
        if not day:
            messagebox.showerror("Missing day", "Please choose a day.", parent=self.window)
            return
        exercise = self._picker.get_workout()
        if not exercise:
            messagebox.showerror("Missing exercise", "Please select an exercise.", parent=self.window)
            return
        self._plan._workout_plan.setdefault(day, []).append(exercise)
        self._summary.config(state="normal")
        self._summary.insert("end", f"{day:6s} → {exercise.name}\n")
        self._summary.config(state="disabled")
        self._refresh_suggestions()

    def _refresh_suggestions(self):
        rest = self._engine.suggest_rest_day(self._plan)
        muscle = self._engine.suggest_muscle_group(self._plan)
        self._suggestion_text.config(text=f"Rest: {rest}\n\nMuscle Groups: {muscle}")

    def _save(self):
        if not self._plan._workout_plan:
            messagebox.showerror("Empty plan", "Add at least one exercise.", parent=self.window)
            return
        self._planner.add_plan(self._plan)
        messagebox.showinfo("Saved", "Workout plan saved!", parent=self.window)
        self.window.destroy()