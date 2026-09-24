"""
C-02: Suggestion Engine
Auth: Kevin Rubio, Aron Meraz
Supports: EP-BRBS, EP-WOP-01, UR-BRBS
Collaborators: WorkoutPlan
"""


class SuggestionEngine:
    # will generate suggestions by analyzing workout plans

    def __init__(self):
        # Empty for now
        pass

    def suggest_rest_day(self, workoutplan) -> str:
        if workoutplan.calculate_rest_day():
            return "You have 5+ consecutive workout days. Consider adding a rest day."
        return "Your workout looks balanced. No rest needed."

    def suggest_muscle_group(self, workoutplan) -> str:
        ALL_GROUPS = {"chest", "back", "legs", "shoulders", "triceps"}
        counts = workoutplan.calculate_muscle_group_balance()
        if counts is None:
            return "No workout plan found to analyze."

        unworked = ALL_GROUPS - counts.keys()
        if unworked:
            return f"You haven't trained these muscle groups yet: {', '.join(sorted(unworked))}. Consider adding them to your plan."

        least_worked = min(counts, key=counts.get)
        return f"All muscle groups are covered. Consider adding more '{least_worked}' work — it's your least trained group ({counts[least_worked]} exercise(s))."
