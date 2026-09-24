"""
C-05: Session
Auth: Nolan Cutler
Supports: EP-WOP-01, UR-APT-03, UR-APT-02, UR-APT-01
Collaborators: Workout[1]
"""
import json
from pathlib import Path
from datetime import date as date_type
from models.Workout import Workout

class Session:
    def __init__(self, id: int, day: str, notes: str, perceived_intensity: int, workout: Workout | None= None, date: date_type | None= None, duration_minutes: int = 0):
        self._id: int = id
        self._day: str = day
        self._notes: str = notes
        self._perceived_intensity: int = perceived_intensity
        # optional because new users logging a session without linking a specific exercise
        self._workout: Workout | None = workout
        self._date: date_type | None = date               # Added for ProgressAnalyzer
        self._duration_minutes: int = duration_minutes  # Added for ProgressAnalyzer

    @property
    def id(self) -> int:
        return self._id

    @property
    def day(self) -> str:
        return self._day

    @property
    def notes(self) -> str:
        return self._notes

    @property
    def perceived_intensity(self) -> int:
        return self._perceived_intensity

    @property
    def workout(self) -> Workout | None:
        return self._workout
    
    @property 
    def date(self) -> date_type | None:                   # Added for ProgressAnalyzer
        return self._date

    @property
    def duration_minutes(self) -> int:             # Added for ProgressAnalyzer
        return self._duration_minutes

    def load_data(self):
        file = Path(f"session_{self._id}.json")
        if file.exists():
            with open(file, "r") as f:
                return json.load(f)
        return {}

    def save_data(self, data):
        with open(f"session_{self._id}.json", "w") as f:
            json.dump(data, f, indent=4)

    def track_id(self, id: int) -> None:
        data = self.load_data()
        data["Session ID"] = id
        self.save_data(data)

    def store_notes(self, notes: str) -> None:
        data = self.load_data()
        data["Notes"] = notes
        self.save_data(data)

    def log_workout_day(self, day: str) -> None:
        data = self.load_data()
        data["Date"] = day
        self.save_data(data)

    def log_workout_date(self, date: date_type) -> None:   # Added for ProgressAnalyzer
        self._date = date
        data = self.load_data()
        data["Date"] = date.isoformat()
        self.save_data(data)

    def log_duration(self, minutes: int) -> None:          # Added for ProgressAnalyzer
        self._duration_minutes = minutes
        data = self.load_data()
        data["Duration"] = minutes
        self.save_data(data)

    def workout_intensity(self, intensity: int) -> None:
        data = self.load_data()
        data["Intensity"] = intensity
        self.save_data(data)

    def log_workout(self, workout: Workout | None) -> None:
        data = self.load_data()
        data["Workout"] = workout
        self.save_data(data)
