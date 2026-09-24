# CS 361: SOFTWARE ENGINEERING I – Winter Term-2026  

----------------------------------------------------------------
## Activity Diagram ID: AD-02 – Edit Workout Plan

Activity Diagram Title: Edit Workout Plan

Related Epic: Workout Plan Management  
Related User Story(ies): UR-WP-02 
Related Test Case(s): TC-02, TC-06, TC-03
Related Test Case Title: Edit Workout Plan  
Related Test Case Objective(s):
Verify that the user can successfully edit an existing workout plan and that changes are saved correctly without creating duplicate plans. 

Activity Diagram Description:
This activity diagram illustrates the workflow for editing an existing workout plan. The user logs into the system, navigates to stored workout plans, and selects a plan to modify. The system loads the plan and allows the user to edit exercise parameters such as sets and repetitions. The system validates the input before saving changes. Valid updates are stored in the database, while invalid inputs trigger validation errors and prevent data updates.

Activity Diagram:
- <img width="653" height="715" alt="image" src="https://github.com/user-attachments/assets/109c05b8-d070-4bab-a205-f031f02b4d49" />
- https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/836dfc5679a053bd29dca2fa8ae3a2faccaa360a/design/activity-diagrams/AD-02_Edit_Workout_Plan.puml

Notes & Assumptions:
- Assumes user is authenticated before editing.
- Validation rules include non-negative numeric values and required fields.

Feedback & Revisions:
- Feedback from: (To be completed)
- Revision Date: (To be completed)
- Changes Made: (To be completed)


----------------------------------------------------------------
## Activity Diagram ID: AD-04 – Prevent Starting Empty Workout Plan

Activity Diagram Title: Prevent Starting Empty Workout Plan

Related Epic: Workout Session Management  
Related User Story(ies):
- As a user, I want the system to prevent me from starting a workout plan that contains no exercises.

Related Test Case(s): TC-04, TC-07
Related Test Case Title: Prevent Starting Empty Workout Plan  
Related Test Case Objective(s): 
Verify that the system prevents users from starting a workout plan that contains no exercises.

Activity Diagram Description:
This activity diagram models the validation process executed when a user attempts to start a workout. After selecting a workout plan, the system checks whether the plan contains exercises. If exercises exist, the system creates a workout session and loads exercises. If no exercises are found, the system blocks the workflow, displays an error message, and redirects the user back to editing.

Activity Diagram:
- <img width="598" height="621" alt="image" src="https://github.com/user-attachments/assets/04ac0415-2c87-4b38-9f59-c56b03a3c101" />
- https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/836dfc5679a053bd29dca2fa8ae3a2faccaa360a/design/activity-diagrams/AD-04_Start_Workout_Validation.puml
  
Notes & Assumptions:
- Assumes workout plans are stored prior to session start.
- System enforces at least one exercise as a precondition.

Feedback & Revisions:
- Feedback from: (To be completed)
- Revision Date: (To be completed)
- Changes Made: (To be completed)

----------------------------------------------------------------
## Activity Diagram ID: AD-05 – Organising Workouts by Day

Activity Diagram Title: Organising Workouts by Day

Related Epic: Workout Scheduling  
Related User Story(ies):
- As a user, I want to assign workout plans to specific days of the week so that I can organise my weekly training schedule.

Related Test Case(s): TC-05, TC-08, TC-09
Related Test Case Title: Organising Workouts by Day  
Related Test Case Objective(s): 
Ensure that users can assign workout plans to specific days and that the dashboard reflects the scheduled workout correctly.

Activity Diagram Description:
This diagram represents how users schedule workout plans by assigning them to specific days of the week. The system loads existing plans, the user selects a plan, and chooses a day. The system validates scheduling constraints before persisting changes. Valid schedules update the dashboard, while invalid configurations trigger scheduling errors.

Activity Diagram:
- <img width="596" height="715" alt="image" src="https://github.com/user-attachments/assets/151ca77e-1dbd-4c5f-b5f0-cdd7cd95125e" />
- https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/836dfc5679a053bd29dca2fa8ae3a2faccaa360a/design/activity-diagrams/AD-05_Assign_Workout_Day.puml

Notes & Assumptions:
- Each day may have configurable constraints.
- System prevents duplicate scheduling conflicts.

Feedback & Revisions:
- Feedback from: (To be completed)
- Revision Date: (To be completed)
- Changes Made: (To be completed)

----------------------------------------------------------------
## Activity Diagram ID: AD-06 – Tracking Reps and Sets

Activity Diagram Title: Tracking Reps and Sets

Related Epic: EP-APT  
Related User Story(ies): UR-WP-03, UR-APT-01
Related Test Case(s): TC-06  
Related Test Case Title: Tracking Reps and Sets 
Related Test Case Objective(s):  
- The user must be able to input the number of reps and sets the do while working out.

Activity Diagram:
- <img width="905" height="823" alt="AD-06_Tracking_Reps_and_Sets" src="https://github.com/user-attachments/assets/0d95b67d-ac53-4769-9b9b-a1a66b78edb6" />
- https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/AD-06_Tracking_Reps_and_Sets.puml

Notes & Assumptions:
- None

Feedback & Revisions:
- Feedback from: (To be completed)
- Revision Date: (To be completed)
- Changes Made: (To be completed)

----------------------------------------------------------------
## Activity Diagram ID: AD-07

Activity Diagram Title: Rest day Suggestion

Related Epic: EP-BRBS, EP-WP 
Related User Story(ies): UR-BRBS-01  
Related Test Case(s): TC-07 
Related Test Case Title: Rest day suggestion  
Related Test Case Objective(s): Ensure that the system will suggest a rest day when users go to add another workout after 6 consecutive days of logging a workout.  

Activity Diagram:
- ![AD-07 Rest Day Suggestion](https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/TC-07_Rest_Day_Suggestion.png?raw=1)
- https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/AD-07_Rest_Day_Suggestion.puml

Notes & Assumptions:

- Note 1 (if applicable): TC-07 does not mention where the workout counter is going to be stored (i.e. local or in DB) 
- Assumption 1 (if applicable): This AD assumes the user already has a set workout plan

Feedback & Revisions:

- Feedback from [Team Member/Reviewer Name]: Aron Meraz  
- Revision Date: 02/22/26
- Changes Made: Fixed an issue with the conditional logic flow to include a Yes section.  

----------------------------------------------------------------
## Activity Diagram ID: AD-08 – 

Activity Diagram Title: Muscle Group Suggestion

Related Epic: EP-BRBS, EP-WOP
Related User Story(ies): UR-BRBS-02 

Related Test Case(s): TC-08 
Related Test Case Title: Muscle Group Suggestion 
Related Test Case Objective(s): “Ensure that the system notifies the user which muscle group has seen the least amount of attention and has received sufficient rest time 

Activity Diagram Description: This diagram shows the suggestions flow triggers when a user is adding a workout. The systems gets the users workout history, calculates how frequently each muscle group has been hit and sorts them from least to most frequent and check whether the muscle group has rested at least 2 days. If it has a suggestion is sent to the user recommending that muscle group be targeted. The flow ends when the user denies and add’s their own workout.  

<img width="1735" height="1048" alt="AD-08_Muscle_Group_suggestion" src="https://github.com/user-attachments/assets/d2db5331-4a93-4fb7-ad99-c2bf0e86df77" />

https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/AD-08_Muscle_Group_suggestion.puml 

----------------------------------------------------------------
## Activity Diagram ID: AD-09 - Workout Statistics

Activity Diagram Description: Activity Diagram 09 documents the flow of how a user would view and interact with their workout statistics. It shows the correlation between user actions and system calculations for progress tracking.

Related Epic: EP-APT (Activity & Progress Tracking) 

Related User Story(ies): UR-APT-02 (Viewing basic statistics from logged workouts) 

Related Test Case(s): TC-09

Related Test Case Title: Statistics from Workout History

Related Test Case Objective(s): Validate the calculations of statistics from the workout data. This includes the average per week, streaks, and total workouts, alongside consistent updates automatically after logging new workouts.

Activity Diagram: 
- ![TC-09 Statistics from Workout History](https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/TC-09%20Statistics%20from%20Workout%20History.png)
- https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/AD-09_Workout_Statistics.puml

Notes & Assumptions: 
- The diagram assumes that with each workout being logged, the system has a cache invalidation system. This means that any update to user data (whether its from the system or the user) will recalculate the basic statistics to show the user 
- The user being able to log workouts assumes that the system processes correctly stores the data for it to be used in the calculating statistics. 

----------------------------------------------------------------
## Activity Diagram ID: AD-10 – View Exercise Videos

Activity Diagram Title: View Exercise Videos

Related Epic: EP-IID
Related User Story(ies):
- UR-IID-01

Related Test Case(s): TC-10, TC-01
Related Test Case Title:
- Exercise Video Plays in Exercise Viewer
- Workout Plan Creation
Related Test Case Objective(s):
Ensure that the user can navigate to the workout planner section and that the video player loads and plays the correct tutorial for the selected exercise.

Activity Diagram Description:
This activity diagram models the flow for viewing exercise tutorial videos during workout plan creation. The user logs in, opens the workout planner, views the exercise list, and selects “View Video” for an exercise. The system loads the corresponding tutorial video. If the video loads successfully, the client-side player plays it. If the video fails to load, the system displays an error and returns the user to the exercise list.

Activity Diagram:
- <img width="800" alt="AD-10 View Exercise Videos" src="https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/AD-10_View_Exercise_Video.png?raw=1" />
- https://github.com/CS361-2026-Winter-Term/Legion-Of-Code/blob/main/design/activity-diagrams/AD-10_View_Exercise_Video.puml

Notes & Assumptions:
- Note 1 (if applicable): If the video fails to load, the “View Video” action displays a load error and does not start playback.

Feedback & Revisions 
- Feedback from [Niki]: Looks good, the diagram has a clear Start and End Node, all actions are meaningful and well-named, transitions are correct with no disconnected elements, decision nodes have valid conditions with at least two outcomes, and the diagram is readable, logically structured, and well-labeled. However, it does not include fork/join nodes or loops, as they are not needed.
