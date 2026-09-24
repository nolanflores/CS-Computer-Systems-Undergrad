# Assignment 3: smallsh

Refer to the assignment document in Canvas for the assignment requirements.

## Getting Started

To work on this assignment, you'll need to start by cloning this repository to your desired workspace. This repository contains the starter code, and pushing your changes back to this repository is how you'll submit your work.

There are many ways to do this, depending on your desired workflow. Below are step-by-step instructions for a typical terminal-based workflow that involves developing and testing directly on our OS1 server. It's recommended that you stick to this workflow unless you really know what you're doing. Regardless of your chosen workflow, make sure to adhere to the technical requirements in the assignment document. Note that the below instructions assume that you've already configured SSH keys to authenticate with your GitHub account from the ENGR servers (e.g., following the workflow instructions in the Assignment 1 repository's front page / `README.md` file).

1. Open your favorite terminal or SSH client (PowerShell, Mac Terminal, MobaXTerm, Putty, etc).
2. Connect to the OS1 server over SSH.
    - In most shells, you can do this via the `ssh` shell command.
        - If you're on the OSU network (e.g., the OSU Secure wifi network, or eduroam), you can simply execute the following: `ssh <ONID>@os1.engr.oregonstate.edu`. Replace `<ONID>` with your ONID (e.g., my connection string would be `guyera@access.engr.oregonstate.edu`). It will then ask for your ONID password. Type it in and press enter (it will be invisible as you type it). It may then ask for a Duo authentication. Type the number corresponding to the desired duo device and press enter. Complete the Duo authentication.
	- If you're not on the OSU network, you have two options: a) download and configure the OSU VPN, and then execute the aforementioned shell command, or b) first connect to OSU's public-facing ENGR servers (`access.engr.oregonstate.edu`) over SSH, and then, within that SSH connection, further connect to the OS1 server using the aforementioned shell command. In other words, option b) is to execute the following two commands: 1) `ssh <ONID>@access.engr.oregonstate.edu`, followed by 2) `ssh <ONID>@os1.engr.oregonstate.edu` (again, replacing `<ONID>` with your ONID). Option b) tunnels your connection through OSU's public-facing ENGR servers. Note that option b) introduces a second point of failure: if the public-facing ENGR servers are ever down, then you won't be able to tunnel through them, and you may have to fall back to option a) (the VPN should be very stable). But the servers rarely go down anyways, and when they do, they're usually down for just a few minutes.
    - In a dedicated SSH client (MobaXTerm, Putty, etc), the process is the same, but rather than using the `ssh` command, you'll likely need to enter a "host" and "user" (and maybe a "password"). The user is your ONID. The host is the second part of the `ssh` connection string (`os1.engr.oregonstate.edu` for the OS1 server). The password (if there's a field for that) is your ONID password (if it doesn't ask for a password, it'll ask once you initiate the connection). Complete the authentication, including Duo authentication if it asks you to. If you're off-campus and need to tunnel through the public-facing ENGR servers with a dedicated SSH client, use a hybrid approach: configure the SSH client to connect to the public-facing ENGR servers (`access.engr.oregonstate.edu`), and then use the `ssh` shell command from within that SSH session to further connect to the OS1 servers.
3. At the top of this repository's front page (likely the page that you're looking at right now if you're reading this document on GitHub), clik the green `<> Code` button. Click on the SSH tab. Copy the presented SSH URL to your clipboard.
4. In your SSH session on the OS1 server, create and navigate to the directory where you want to store your assignment work for this course (e.g., using `mkdir`, `cd`, etc).
5. Clone this repository via the following shell command: `git clone <PASTE SSH URL HERE>`. To verify that it worked, run `ls`. You should see a new directory called `assignment-3-smallsh-<USER>` (where `<USER>` is your GitHub username). Navigate into that directory via `cd`. It should contain a copy of this repository's contents. You can now proceed to complete `processmovies.c` in a terminal-based text editor, such as `vim`. If `git clone` *didn't* work, then there may be something wrong with your SSH key config. Refer to the Assignment 1 repository's front page / `README.md` file for instructions on how to fix these issues.

## Committing and pushing changes
You should **frequently** stage, commit, and push your changes as you work on the assignment. `git` is a version control system (VCS), meaning that its purpose is to keep track of a history of changes made to a digital project. It even allows you to roll back to a previous commit (commits are sometimes referred to as "snapshots" for this reason). This makes it easy to undo your mistakes (and you will make mistakes; we all do). However, you can only take advantage of this if you make small, frequent commits.

Here are the steps to stage, commit, and push your changes (you should do this every time you want to save a snapshot of the state of your work, which should probably be after every few minutes of work):
1. Run `git status`. It will report a list of modified files (usually in red) and staged files (usually in green).
2. For each modified file whose changes you want to include in your next commit (likely just `processmovies.c`; no need to stage or commit executables), stage it via `git add <file>`. For example, `git add processmovies.c`.
3. Run `git status` again. The file(s) that you just staged should now show up as such (usually in green).
4. When you're done staging files for the next commit, create the commit itself: `git commit -m "<COMMIT MESSAGE>"`. The quotation marks around the commit message are necessary. Replace `<COMMIT MESSAGE>` with a brief message / comment explaining the changes that you made since the last commit (i.e., the changes that you're trying to "save" into the commit).
5. Run `git status`. The files whose changes you just staged and committed should no longer be listed. That means they were committed successfully.
6. Run `git push`. That will "push", or upload, all of your recent commits to this GitHub repository.
7. Refresh this GitHub repository page. The contents of this repository should now be up-to-date, reflecting the changes that you just pushed.

Just below the `<> Code` button on this repository's front page, there should be a link that says "X commits", where X is the number of commits in this repository's commit history. If you click on that button, you can view all of the past commits (snapshots) of your work. If you ever want to roll back to a previous commit (i.e., undo one or more recent commits), you'll need to look into the `git log` and `git revert` commands. Feel free to stop by office hours for help if you run into that situation.

## Submitting your work
The TAs have access to all repositories in our class's GitHub organization, but they have no way of knowing whose is whose. So, once you've pushed your final changes to this repository, complete the following steps to submit your work:

1. Navigate to this repository's main page (you're probably already on it---the page that displays the README.md file that you're reading right now).
2. Copy the URL in your browser's address bar.
3. Navigate to this assignment's Canvas page.
4. Click "Start Assignment"
5. Paste the copied URL into the textbox
6. Click submit

The time of your latest commit will be treated as your final submission time. Pushing new commits after the assignment deadline requires using grace days.

If you ever want to test that your submission went through properly (which you should, especially after pushing your final commit), follow these steps:

1. Navigate to the URL that you submitted into the Canvas submission box for the assignment (which should be this webpage). Copy the repository's SSH URL via the green `<> Code` button.
2. Create an empty temporary directory on the OS1 server via `mkdir`
3. Navigate into that empty directory via `cd`, and use `git clone <Paste SSH URL here>` to clone the repository
4. Navigate into the freshly cloned project directory and compile and test your program. If it works as expected, then you can consider it submitted. If it doesn't work as expected, then delete the temporary directory that you just created, navigate back to your original workspace, make the necessary changes, stage / commit / push them, and test again (you don't need to resubmit the URL in Canvas; the URL won't change). Important: Only make changes to your code from within your original project workspace. If you have two clones of the same repository, and then you try to make independent changes to it from within each clone, you can run into git conflicts, which can be a pain to resolve if you don't know much about `git`.
