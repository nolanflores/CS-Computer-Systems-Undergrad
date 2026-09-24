"""
C-06: Viewer
Auth: Nolan Cutler, Nolan Flores
Supports EP-WOP-01, UR-IID-01, UR-APT-03, UR-APT-02, UR-APT-01
Collaborators: Planner[1]
"""

from .Planner import Planner
from .SuggestionEngine import SuggestionEngine
from .ProgressAnalyzer import ProgressAnalyzer
from .User import User

import tkinter as tk
from tkinter import messagebox, ttk

from .ExercisePickerFrame import ExercisePickerFrame
from .CreatePlanDialog import CreatePlanDialog
from .EditPlanDialog import EditPlanDialog
from .LogWorkoutDialog import LogWorkoutDialog


class Viewer:
    """
    Manages workout plans/logs through GUI menu
    """

    def __init__(self):
        self._window: tk.Tk = tk.Tk()
        self._window.title("Legion of Code - Workout Planner")
        self._window.geometry("800x500")
        self._window.resizable(True, True)
        self._user: User = None
        self._planner: Planner = None
        self._pageContent: ttk.Frame = None

    def start(self) -> None:
        for w in self._window.winfo_children():
            w.destroy()
        frame = ttk.Frame(self._window, padding=60)
        frame.place(relx=0.5, rely=0.5, anchor="center")

        ttk.Label(frame, text="Legion of Code", font=("Helvetica", 20, "bold")).grid(row=0, columnspan=2, pady=(0, 4))
        ttk.Label(frame, text="Workout Planner", font=("Helvetica", 13)).grid(row=1, columnspan=2, pady=(0, 24))

        ttk.Label(frame, text="Username:").grid(row=2, column=0, pady=6)
        self._username = ttk.Entry(frame, width=24)
        self._username.grid(row=2, column=1, padx=10)
        self._username.focus()

        ttk.Label(frame, text="Email:").grid(row=3, column=0, pady=6)
        self._email = ttk.Entry(frame, width=24)
        self._email.grid(row=3, column=1, padx=10)

        ttk.Button(frame, text="Start", command=self._handle_login).grid(row=4, columnspan=2, pady=20)
        self._window.bind("<Return>", lambda _: self._handle_login())
    
    def main_loop(self):
        self._window.mainloop()

    def _handle_login(self):
        username = self._username.get().strip()
        email = self._email.get().strip()
        if not username or not email:
            messagebox.showerror("Error", "Please enter both username and email.")
            return
        user = User(username=username, email=email)
        user.save_credentials()
        self.set_user(user)
        self.main_menu()

    def main_menu(self):
        self._window.unbind("<Return>")
        for w in self._window.winfo_children():
            w.destroy()

        sidebar = ttk.Frame(self._window, padding=10, relief="groove")
        sidebar.pack(side="left", fill="y")

        self._pageContent = ttk.Frame(self._window, padding=15)
        self._pageContent.pack(side="right", fill="both", expand=True)
        menu_items = [
            ("Create Workout Plan", self.create_plan),
            ("View Workout Plans",  self.view_plans),
            ("Edit Workout Plan",   self.edit_plan),
            ("Add Workout Log",     self.log_workout),
            ("View Workout Logs",   self.view_logs),
            ("Get a Suggestion",    self.view_suggestion),
            ("View Statistics",     self.view_statistics),
            ("Exit",                self._window.quit),
        ]
        for label, cmd in menu_items:
            ttk.Button(sidebar, text=label, command=cmd, width=20).pack(pady=3, fill="x")

        ttk.Label(self._pageContent, text="Select an option from the menu.", font=("Helvetica", 12)).pack(expand=True)

    def create_plan(self) -> None:
        CreatePlanDialog(self._window, self._planner)

    def view_plans(self) -> None:
        for w in self._pageContent.winfo_children():
            w.destroy()

        plans = self._planner.list_plans()
        if not plans:
            ttk.Label(self._pageContent, text="No saved workout plans.").pack(expand=True)
            return

        canvas = tk.Canvas(self._pageContent, borderwidth=0)
        vsb = ttk.Scrollbar(self._pageContent, orient="vertical", command=canvas.yview)
        canvas.configure(yscrollcommand=vsb.set)
        vsb.pack(side="right", fill="y")
        canvas.pack(side="left", fill="both", expand=True)
        inner = ttk.Frame(canvas)
        canvas.create_window((0, 0), window=inner, anchor="nw")
        inner.bind("<Configure>", lambda _: canvas.configure(scrollregion=canvas.bbox("all")))

        for i, plan in enumerate(plans, 1):
            ttk.Label(inner, text=f"Plan {i}", font=("Helvetica", 12, "bold")).pack(anchor="w", pady=(12, 2))
            ttk.Separator(inner, orient="horizontal").pack(fill="x", pady=2)
            for day, workouts in plan.workout_plan.items():
                ttk.Label(inner, text=f"  {day}", font=("Helvetica", 10, "bold")).pack(anchor="w")
                for w in workouts:
                    ttk.Label(inner,text=f"      * {w.name}  |  {w.sets}x{w.reps}  |  rest {w.rest_time}s").pack(anchor="w")

    def log_workout(self) -> None:
        LogWorkoutDialog(self._window, self._planner)

    def view_logs(self) -> None:
        for w in self._pageContent.winfo_children():
            w.destroy()

        logs = self._planner.get_logs()
        if not logs:
            ttk.Label(self._pageContent, text="No workout logs yet.").pack(expand=True)
            return

        cols = ("ID", "Day", "RPE", "Workout", "Notes")
        tree = ttk.Treeview(self._pageContent, columns=cols, show="headings", height=18)
        widths = (40, 70, 50, 160, 220)
        for col, w in zip(cols, widths):
            tree.heading(col, text=col)
            tree.column(col, width=w, anchor="center")

        for s in logs:
            tree.insert("", "end", values=(s.id, s.day, s._perceived_intensity, s.workout, s.notes))

        vsb = ttk.Scrollbar(self._pageContent, orient="vertical", command=tree.yview)
        tree.configure(yscrollcommand=vsb.set)
        vsb.pack(side="right", fill="y")
        tree.pack(fill="both", expand=True)

    def view_suggestion(self) -> None:
        for w in self._pageContent.winfo_children():
            w.destroy()

        plans = self._planner.list_plans()
        engine = SuggestionEngine()

        ttk.Label(self._pageContent, text="Suggestions", font=("Helvetica", 13, "bold")).pack(pady=(20, 10))

        if not plans:
            ttk.Label(self._pageContent, text="No workout plan found.", wraplength=480, justify="center").pack()
            return

        rest_text = engine.suggest_rest_day(plans[0])
        muscle_text = engine.suggest_muscle_group(plans[0])

        ttk.Label(self._pageContent, text="Rest Day", font=("Helvetica", 11, "bold")).pack(anchor="w", padx=20, pady=(10, 2))
        ttk.Label(self._pageContent, text=rest_text, wraplength=480, justify="left").pack(anchor="w", padx=30)

        ttk.Separator(self._pageContent, orient="horizontal").pack(fill="x", padx=20, pady=10)

        ttk.Label(self._pageContent, text="Muscle Groups", font=("Helvetica", 11, "bold")).pack(anchor="w", padx=20, pady=(0, 2))
        ttk.Label(self._pageContent, text=muscle_text, wraplength=480, justify="left").pack(anchor="w", padx=30)

    def view_statistics(self) -> None:
        for w in self._pageContent.winfo_children():
            w.destroy()

        stats = ProgressAnalyzer.statistics(self._user)
        ttk.Label(self._pageContent, text="Statistics", font=("Helvetica", 13, "bold")).pack(pady=(20, 10))
        ttk.Label(self._pageContent, text=str(stats), wraplength=480, justify="left").pack()

    def edit_plan(self) -> None:
        EditPlanDialog(self._window, self._planner)

    def set_user(self, user) -> None:
        if not user:
            raise ValueError("No user cannot initialize Viewer")
        self._user = user
        self._planner = Planner(user) # Critical for the entire app lol