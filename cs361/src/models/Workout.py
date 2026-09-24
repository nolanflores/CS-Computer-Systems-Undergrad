"""
C-03: Workout
Auth: Nolan Cutler
Supports: EP-BRBS, UR-W0P-01
Collaborators: None
"""

from dataclasses import dataclass


@dataclass
class Workout:
    """
    Stores information specific to an exercise
    """

    name: str
    reps: int
    sets: int
    rest_time: int
    video_id: str
    muscle_group: str = "unknown"
