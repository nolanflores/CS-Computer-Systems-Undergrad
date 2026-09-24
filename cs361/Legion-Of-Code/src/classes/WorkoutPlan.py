from collections import defaultdict
from dataclasses import asdict

from models.Workout import Workout

"""
C-01: Class for Workout Plan
Auth: Kevin Rubio, Aron Meraz
Supports: EP-BRBS, EP-WOP, UR-WP-01, UR-WP-02, UR-WP-03
Collaborators: Workout[0..7] (since there is 7 days in the week)
"""


class WorkoutPlan:
    def __init__(self):

        # probably will need
        self._workout_plan = defaultdict(
            list
        )  # Init an empty dict for workout plan where Keys = Day of the week and Values = workout (probably will be class)

    @property
    def workout_plan(self) -> dict:
        return self._workout_plan

    # Returns true if the workout plan is empty
    def workout_plan_empty(self) -> bool:
        return not self._workout_plan

    # Will add a workout to the workout plan
    def add_workout(self, day: str, workout: Workout) -> None:
        self._workout_plan[day].append(workout)

    def to_dict(self) -> dict:
        return {day: [asdict(w) for w in workouts] for day, workouts in self._workout_plan.items()}

    @classmethod
    def from_dict(cls, data: dict) -> "WorkoutPlan":
        plan = cls()
        for day, workouts in data.items():
            for w in workouts:
                plan.add_workout(day, Workout(**w))
        return plan

    # Will calculate if a rest day is needed in the user's current workout plan i.e. if they have 5 days in a row of working out
    def calculate_rest_day(self) -> bool:
        week = ["Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"]
        streak = 0
        for day in week:
            if day in self._workout_plan and self._workout_plan[day]:
                streak += 1
                if streak >= 5:
                    return True
            else:
                streak = 0
        return False

    # Will calcuate which muslce groups are being undertrained or over trained in the current user's plan
    def calculate_muscle_group_balance(self) -> dict[str, int] | None:
        if not self._workout_plan:
            return None
        counts: dict[str, int] = {}
        for workouts in self._workout_plan.values():
            for workout in workouts:
                group = workout.muscle_group
                counts[group] = counts.get(group, 0) + 1
        return counts
