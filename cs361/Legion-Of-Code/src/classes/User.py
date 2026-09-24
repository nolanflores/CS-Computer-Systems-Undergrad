"""
C-07: User
Auth: Niki Pandya
Supports: UR-WP-01, UR-WP-02, UR-WP-03, UR-APT-01, UR-WOP-01
Collaborators: Planner[1]
"""

import json
from pathlib import Path

from .Planner import Planner
from .WorkoutPlan import WorkoutPlan
from .Session import Session

class User:
    """
    Represents a user of the workout tracking application.
    A User owns workout plans and workout session history.
    """

    def __init__(self, username: str, email: str):
        self._username: str = username
        self._email: str = email
        self._planner = Planner(self)
        self.load_credentials()

    # ------------------------
    # Workout Plan Management
    # ------------------------

    def add_workout_plan(self, plan: WorkoutPlan) -> None:
        """Adds a workout plan to the user's planner"""
        self._planner.add_plan(plan)

    def get_plans(self) -> list[WorkoutPlan]:
        """Returns all workout plans owned by the user"""
        return self._planner.list_plans()

    # ------------------------
    # Session Management
    # ------------------------

    def add_session(self, session: Session) -> None:
        """Logs a completed workout session"""
        self._planner.log_workout(session)

    def get_sessions(self) -> list[Session]:
        """Returns all logged workout sessions"""
        return self._planner.get_logs()

    # ------------------------
    # Profile Management
    # ------------------------

    def update_profile(self, name: str, email: str) -> None:
        """Updates the user's profile information"""
        self._name = name
        self._email = email
        self.save_credentials()

    def get_user_info(self) -> dict:
        """Returns basic user information"""
        return {"username": self._username, "email": self._email}

    def get_planner(self) -> Planner:
        return self._planner

    def get_credentials_path(self) -> str:
        return str(self._credentials_path())

    def save_credentials(self) -> str:
        path = self._credentials_path()
        payload = {
            "username": self._username,
            "email": self._email,
        }

        path.write_text(json.dumps(payload, indent=2), encoding="utf-8")

        return str(path)

    def load_credentials(self) -> bool:
        path = self._credentials_path()
        if not path.exists():
            return False

        text = path.read_text(encoding="utf-8").strip()

        if not text:
            return False

        data = json.loads(text)
        self._username = data.get("username", self._username)
        self._email = data.get("email", self._email)
        return True

    def _credentials_path(self) -> Path:
        data_dir = Path(__file__).resolve().parent.parent / "prog-data"
        data_dir.mkdir(parents=True, exist_ok=True)
        return data_dir / f"{self._username}.info"


