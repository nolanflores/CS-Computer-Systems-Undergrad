"""
C-08: ProgressAnalyzer
Auth: Alex Cortes
Supports: UR-APT-03, UR-APT-02, UR-APT-01
Collaborators: Session [...], Planner[...], User[...]
"""


from .WorkoutPlan import WorkoutPlan
from .User import User
from datetime import date as date_type, timedelta


class ProgressAnalyzer:
    """
    Primary Purpose: Manages the calculation of statistics and tracking of progress.
    
    READ THESE NOTES:
        This class assumes that it will be given a list of Sessions. 
        Tracing where this list of session comes from:
            [Planner.py] get_logs(self) -> list[Session] --
                [User.py] get_sessions(self) -> list[Session] --
                     -> [ProgressAnalyzer.py] 
                        __init__(self, user, session): 
                            if user:
                                self.sessions = user.get_sessions()
                            else:
                                self.sessions = sessions or []  # list of Session objects
                                
        TLDR; Sessions can be supplied directly or retrived from User object
              Session.py has _date and _duration_minutes attributes added for this class.
              
              If the session logs (list of kept sessions) is EVER read from JSON,
                    it breaks all statistics calculations. 
    """
    # user -> Retrieves the user's completed session (if exists)
    # session -> List of COMPLETED sessions
    def __init__(self, user=None, sessions=None):
        if user:
            self.sessions = user.get_sessions()
        else:
            self.sessions = sessions or []  # list of Session objects

    def calculate_streak(self) -> int:
        """
        Calculates the current consecutive-day workout streak.

        Sorts all sessions by date, then walks forward comparing adjacent days.
        If two consecutive sessions are exactly 1 day apart, the streak continues.
        If a gap is found, the streak resets to 1. 
        NOTE: Does not anchor to today's date, so edits to past sessions are 
              automatically reflected when refreshing (calling) this class.

        Returns:
            int: The current streak count. Returns 0 if there are no sessions.
        """
        
        # Streaks (basic implementation)
        distinct_days = sorted({s.date for s in self.sessions})
        current_streak = 0
        for i in range(1, len(distinct_days)):
            # Count forwards, and if the dates are exactly 1 day apart, streak++
            if (distinct_days[i] - distinct_days[i-1]).days == 1:
                current_streak += 1
            else:
                current_streak = 1
        return current_streak
    
    # TODO: Intended statistics:
    #       Total Workouts -- Int
    #       Streaks -- Int
    #       Average Workouts (that week) -- float
    def calculate_stats(self):
        
        total_sessions = len(self.sessions)
        if not self.sessions: # No sessions
            return {
            "total_workouts": 0,
            "avg_per_week": 0,
            "current_streak": 0
            }     
            
        # Average Per Week 
        # Basic general average -> # of workouts total / number of weeks spanned
        # Getting the weeks spanned requires:
        #   # of days from (current date - earliest date) of ALL sessions / 7 (week length)
        #       DONT DIVIDE BY ZERO AT ALL COSTS
        #       This can happen IF there is only one week's worth of workouts logged
        dates = sorted([s.date for s in self.sessions]) 
        num_weeks = max(((dates[-1] - dates[0]).days / 7), 1) # without max(,1), zero is possible
        avg_per_week = round(total_sessions / num_weeks, 1)
        # Streaks
        current_streak = self.calculate_streak()
        
        return {
            "total_workouts": total_sessions,
            "avg_per_week": avg_per_week,
            "current_streak": current_streak}
        

    def calculate_weekly_stats(self, weeks=4):
        """
        Breaks down workout activity into weekly buckets going back from today.

        Args:
            weeks (int): Number of weekly buckets to generate. 
                         Defaults to 4 (month).

        Returns:
            list: A list of dicts, one per week, each containing:
                - "week" (str): Label for the bucket (e.g. "Week #1").
                - "workout_count" (int): Number of sessions in that window.
                - "total_duration" (int): Total minutes worked out that week.
        """
        today = date_type.today()
        weekly_data = []
        for i in range(weeks):
            # Each iteration is week #
            # Week bucket definition, going backwards from today.
            # i=0 → current week, i=1 → last week, i=2 → two weeks ago, etc.
            week_start = today - timedelta(weeks=i+1)
            week_end   = today - timedelta(weeks=i)
            
            # Duration : Sum total workout minutes for this window
            duration = sum(
                s.duration_minutes for s in self.sessions
                if week_start <= s.date < week_end
            )
            
            # Workouts total that week
            count = sum(
                1 for s in self.sessions
                if week_start <= s.date < week_end
            )
            
            weekly_data.append(
                {
                    "week": i,
                    "workout_count": count,
                    "total_duration": duration,
                }
            )
    
        return weekly_data

    # Insight text
    def improvement_insights(self):
        """
        Generates motivational insight messages based on streak and workout duration.

        Returns:
            list: A list of insight strings to display to the user.
        """
        
        insights = [] 
        if len(self.sessions) < 3:
            insights.append("Log more workouts for some insights :)")
            return insights # Exit for no crash :)

        # TODO: add default insights for streaks and duration.
        streak = self.calculate_streak()
        if streak == 1:
            insights.append("You've started a streak — come back tomorrow to keep it going!")
        elif streak < 4:
            insights.append(f"You're on a {streak}-day streak — great consistency, keep it up!")
        elif streak < 7:
            insights.append(f"{streak} days in a row — you're building a solid habit!")
        else:
            insights.append(f"Incredible! {streak}-day streak — you're on fire!")
            
        # Duration
        durations = [s.duration_minutes for s in self.sessions]
        avg_duration = sum(durations) / len(durations)

        if avg_duration < 20:
            insights.append("Even short sessions count — try pushing to 20 minutes next time!")
        elif avg_duration < 45:
            insights.append(f"You're averaging {round(avg_duration)} minutes per workout — nice work!")
        else:
            insights.append(f"Averaging {round(avg_duration)} minutes per session — outstanding effort!")
        return insights
    
    # Generates all statistics (general + weekly) and motivational improvement insights
    def generate_report(self):
        """
        Generate comprehensive progress report statistics
        """
        return {
            "basic_stats": self.calculate_stats(),
            "weekly_stats": self.calculate_weekly_stats(),
            "improvement_areas": self.improvement_insights(),
        }
    def statistics(user):
        user_stats = ProgressAnalyzer(user)
        statistics = user_stats.generate_report()
        basic_stats, weekly_stats = statistics['basic_stats'], statistics['weekly_stats']
        insights = statistics['improvement_areas']
        # print("--DEBUG--")
        # print(insights)
        print("\n // Workout Statistics // ")
        print(f"Total Workouts: {basic_stats['total_workouts']}")
        print(f"Average Per Week: {basic_stats['avg_per_week']}")
        print(f"Current Streak: {basic_stats['current_streak']}\n")
        for i, week in enumerate(weekly_stats):
            print(f" -- Week {week['week']} STATS -- ")
            # print(f"Week # {week[i]['week']}")
            print(f"Workout Count this Week: {week['workout_count']}")
            print(f"Total time spent working out: {week['total_duration']}")
        for item in insights:
            print(
                    "\n Workout Insights:\n", 
                    f"{item}"
                )    
            print("\n // End of Workout Statistics")
