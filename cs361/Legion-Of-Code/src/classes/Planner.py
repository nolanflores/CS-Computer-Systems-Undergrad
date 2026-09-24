"""
C-04: Planner
Auth: Nolan Cutler
Supports EP-WOP-01, UR-APT-03, UR-APT-02, UR-APT-01, UR-BRBS
Collaborators: WorkoutPlan[0..*], Session [0..*]
"""

import json
from pathlib import Path

from .Session import Session
from .WorkoutPlan import WorkoutPlan
from models.Workout import Workout


class Planner:
    def __init__(self, user=None):
        self._user = user
        self._plans = [] # workoutplans
        self._log = [] # sessions

        if self._user is not None and self._user._username:
            self.load_saved_plans()
            self.load_saved_log()

    def add_plan(self, plan: WorkoutPlan) -> None:
        self._plans.append(plan)
        if self.save_plans() is None: 
            print("Error saving workout plans")

    def list_plans(self) -> list[WorkoutPlan]:
        return self._plans

    def log_workout(self, session: Session) -> None:
        self._log.append(session)
        if self.save_log() is None:
            print("Error saving workout log")

    def edit_log(self, id: int, new_sess: Session) -> None:
        for index, session in enumerate(self._log):
            if session.id == id:
                self._log[index] = new_sess
                break

    def get_logs(self) -> list[Session]:
        return self._log

    def set_user(self, user) -> None:
        self._user = user
        if self._user is not None and self._user._username:
            self.load_saved_plans()
            self.load_saved_log()

    def get_user(self):
        return self._user

    def save_plans(self) -> str | None:
        # get workout-plan json for this user
        path = self._get_data_path("workout-plan")
        if path is None:
            return None

        data = []
        for plan in self._plans:
            data.append({"workout_plan": plan.to_dict()})

        path.write_text(json.dumps(data, indent=2), encoding="utf-8")
        return str(path)

    def load_saved_plans(self) -> list[WorkoutPlan]:
        # get workout plan json for this user
        path = self._get_data_path("workout-plan")
        if path is None or not path.exists():
            self._plans = []
            return self._plans

        text = path.read_text(encoding="utf-8").strip()
        if not text:
            self._plans = []
            return self._plans

        # load plans from the workout-plan json
        self._plans = []
        for item in json.loads(text):
            plan = WorkoutPlan.from_dict(item.get("workout_plan", {}))
            self._plans.append(plan)

        return self._plans

    def save_log(self) -> str | None:
        path = self._get_data_path("workout-log")
        if path is None:
            return None

        data = []
        for session in self._log:
            w = session.workout
            data.append({
                "id": session.id,
                "day": session.day,
                "notes": session.notes,
                "perceived_intensity": session.perceived_intensity,
                # serialize workout fields so we can reconstruct it on load; None if no workout was linked
                "workout": {"name": w.name, "reps": w.reps, "sets": w.sets, "rest_time": w.rest_time, "video_id": w.video_id} if w else None,
            })

        path.write_text(json.dumps(data, indent=2), encoding="utf-8")
        return str(path)

    def load_saved_log(self) -> list[Session]:
        # log json (/src/prog-data/workout-log-{user id}.json)
        path = self._get_data_path("workout-log")
        if path is None or not path.exists():
            self._log = []
            return self._log

        text = path.read_text(encoding="utf-8").strip()
        if not text:
            self._log = []
            return self._log

        self._log = []
        for item in json.loads(text):
            workout_data = item.get("workout")
            # reconstruct Workout if data was saved, otherwise None means no workout was linked for this session
            workout = Workout(**workout_data) if workout_data else None
            session = Session(
                id=item.get("id", 0),
                day=item.get("day", ""),
                notes=item.get("notes", ""),
                perceived_intensity=item.get("perceived_intensity", 0),
                workout=workout,
            )
            self._log.append(session)

        return self._log

    def get_workout_plan_path(self) -> str | None:
        path = self._get_data_path("workout-plan")
        return str(path) if path else None

    def _get_data_path(self, prefix: str) -> Path | None:
        if self._user is None:
            return None

        username= self._user._username
        if not username:
            return None

        data_dir = Path(__file__).resolve().parent.parent / "prog-data"
        data_dir.mkdir(parents=True, exist_ok=True)
        return data_dir / f"{prefix}-{username}.json"

