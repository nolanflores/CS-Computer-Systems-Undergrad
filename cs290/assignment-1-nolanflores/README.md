# Assignment 1
**→ Preferred deadline: 11:59pm on Monday, 10/14/2024** <br/>
**→ Extension deadline: 11:59pm on Wednesday, 10/16/2024 (no submissions allowed after this)** <br/>
**→ Assignment and Code Blog entry due at the same time** <br/>
**→ Grading demo due: 11:59pm on Monday 10/28/2024**

This assignment is intended to get you up and running with some of the tools we'll be using in this course and also to get you to start using HTML to create web pages.  It should be very straightforward.  It has three parts, described below.

## 1. View a post on Ed Discussion

This first part of this assignment is simple and doesn't involve coding.  Just visit our course forum on Ed Discussion and familiarize yourself with that platform.  You don't even have to post anything, but make sure to view at least one post, so Ed registers you as being active there.

You can find a link to our Ed forum both on the course website and in Canvas within the course navigation bar for our course.  Most of you should already be automatically enrolled in our course on Ed with your @oregonstate.edu email address.  However, if you have trouble connecting to our course forum there, please catch up with me after lecture or drop into my office hours, and I’ll make sure you’re able to log in.

We'll be using Ed as our main communication platform for the course.  Ed is essentially a StackOverflow-style Q&A forum, where you can ask questions and answer your classmates’ questions.  Please use Ed exclusively for questions you have about the course, so all our course Q&A can live in one central, easily accessible place.  I (Hess) and the TAs will be on Ed, just like you and your fellow students, so you can feel confident about getting the answers you need there.

I strongly encourage you to also spend time answering your fellow classmates’ questions on Ed. This will not only enable everyone to get help quickly, but it will also help you improve your understanding of the material, since teaching someone else is the best way to learn something.  **As an extra incentive to answer questions on Ed, extra credit will be awarded to the most active Ed participants at the end of the course** (based on analytics tracked by Ed).

## 2. Use Git and GitHub and start practicing HTML

The other tool we'll be using quite a bit for this course is Git/GitHub.  You're already here looking at this assignment, so we know you've got at least some Git/GitHub skills.  Practice a little more and also start using HTML by following these steps:

1. If you're new to Git and GitHub, take a few minutes to play with Git-it, which is a desktop app that teaches you how to use Git and GitHub:

    https://github.com/jlord/git-it-electron#git-it-desktop-app

    We'll be using Git and GitHub heavily in this course, so it'll pay off to put in the time now to learn how to use them.

2. Clone this assignment repository from GitHub onto your development machine. Within the cloned assignment directory on your development machine, create a new file `index.html` that contains a complete HTML-only page (no CSS or JS required yet, but feel free to use them if you want) that displays these things:
    * Your name and what you prefer to be called (if it's different from your name).
    * Your OSU email address (e.g. `hessro@oregonstate.edu`).
    * Your major and year of study.
    * The answer to this question: what is the most complex or interesting thing you've done with your current web development skills?  If you've never done anything related to web development, that's fine, but make sure to say that here.
    * The answer to this question: what do you hope to learn from this class?
    * The answer to this question: have you signed up for our course Campuswire forum?
    * A description of the most interesting fact about you or the most unique experience you've had.  There's no need to wrack your brain about this: include only what you can think of and write down in two minutes, maximum.
    * A photo with a clear picture of your face (using an `<img>` tag).

    This info should be well-structured, e.g. using headings (`<h1>`, `<h2>`, `<h3>`, etc.), paragraphs (`<p>`), an unordered list (`<ul>` and `<li>`), a combination of those things, or anything else that makes sense.

3. Use Git commands to add and commit your new file to the local assignment repository on your development machine and to push the changes in your local repository back to your remote assignment repository on GitHub.

4. Add to your assignment directory a new file `blog.html` that contains an HTML-only page (again, feel free to add CSS and/or JS if you want, but that's not required) that will contain your code blog for the whole term.  In this file, you should start your code blog with a single entry reflecting on your experience completing this assignment.  Here are some example questions you might answer, but feel free to reflect in any way you wish, beyond these questions:
    * What challenges or troubles did you have completing this assignment.  How did you work through them?
    * What did you learn from this assignment?  What did you already know?
    * What resources (e.g. specific web articles, the class Campuswire forum, the TAs) were most helpful in completing this assignment?  How did you use these resources?

    Again, your blog page should be nicely structured, with a title at the top and a title and date for your first post.  You should also include a link at the top of your blog page that goes back to `index.html`.

5. Use Git commands to add and commit your new file to the local assignment repository on your development machine and to push the changes in your local repository back to your remote assignment repository on GitHub.

6. Commit and push an update to your `index.html` file adding a link near the top of the page to navigate to your code blog in `blog.html`.  Similarly, add a link near the top of `blog.html` to navigate to your home page in `index.html`.

## 3. Publish your newly-created pages

The last thing you'll do for this assignment is publish your newly created pages on the web.  You have two options for how to do this:

  1. Publish your index and blog pages under your personal ENGR web space under a URL like this: http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/.  For help publishing to your web space, see [this page](http://it.engineering.oregonstate.edu/where-do-i-put-my-personal-webpages) (more tips are included below).  Note that because you're taking a course in the College of Engineering (i.e. this course), you should have access to a personal ENGR web space even if you're not an Engineering student.  You can use the following site to create an ENGR account and get access to ENGR resources like a personal web space (use the "create a new account" link):

      https://teach.engr.oregonstate.edu

  2. Publish your pages using GitHub Pages: https://pages.github.com/.  Note that because you won't have administrative permission on the assignment repo created for you by GitHub Classroom, you won't have the ability to directly publish that repo under GitHub Pages.  I (Hess) will announce in class how you can have that repo published.  Alternatively, you can create a repo under your personal GitHub account (in addition to the one created for you by GitHub Classroom!) to use for publishing to GitHub Pages.

However you publish your pages, make sure to visit them on the internet (i.e. using a URL that starts with `https://` or `http://` and NOT one that starts with `file://`), and make sure they look the way you expect them to look.

## Tips on publishing to ENGR web space

Here are a few helpful hints on getting your pages published to your ENGR web spaces:

  * The main way to publish content on the ENGR web space web space is to put files in the `public_html/` directory that lives in your home directory on the ENGR servers.  You can do this in any number of ways:
      * [Using Windows file sharing](https://it.engineering.oregonstate.edu/accessing-engineering-file-space-using-windows-file-sharing).  Once you can access your `public_html/` directory this way, all you need to do is put your HTML files inside.
      * Using one of the methods [described here](https://it.engineering.oregonstate.edu/accessing-engineering-file-space).
      * Using SSH/SFTP, e.g. using [MobaXterm](https://mobaxterm.mobatek.net/documentation.html#2_3_3) or [FileZilla](https://filezilla-project.org/).

  * Make sure to publish *all* of the files needed by your pages, including HTML files, image files, etc.

  * Once you have the files you want to publish put inside `public_html/`, the web URLs of those files match the directory structure underneath `public_html/`.  For example, say the contents of your `public_html/` directory on the ENGR servers look like this:

      ```
      public_html/
        index.html
        blog.html
      ```

    Then the two files inside `public_html/` will be available at the following two URLs:

      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/index.html
      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/blog.html

    If, instead, your files live in a subdirectory within `public_html/` on the ENGR servers (e.g. `public_html/cs290/`) like this:

      ```
      public_html/
        cs290/
          index.html
          blog.html
      ```

    then those files will be available at the following two URLs (note the extra `cs290` component in the URL corresponding to the `cs290/` directory):

      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/index.html
      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/blog.html

  * To be viewable on the web, the files inside your `public_html/` directory need to have the correct Unix permissions.  Specifically, all files need to have *read* permission granted for the world, and all subdirectories within `public_html/` need to have *read* and *execute* permission granted for the world.  You can read more about Unix permissions here:

      https://www.tutorialspoint.com/unix/unix-file-permission.htm

    Once you understand how Unix permissions work, make sure all of your files have permissions that look something like this: `-rw-r--r--` (i.e. `644` permissions), and make sure the subdirectories under `public_html/` have permissions that look something like this: `-rwxr-xr-x` (i.e. `755` permissions).

  * You should *never* use a URL that begins with `file:///...` within any of your HTML files.  Such a URL describes the location of a file *on a specific computer*.  If you need to refer to a local file, use a [relative URL](https://www.w3schools.com/html/html_filepaths.asp).


## Submission

We'll be using GitHub Classroom for this assignment, and you will submit your assignment via GitHub.  Just make sure your completed files are committed and pushed by the assignment's deadline to the main branch of the GitHub repo that was created for you by GitHub Classroom.  A good way to check whether your files are safely submitted is to look at the main branch your assignment repo on the github.com website (i.e. https://github.com/osu-cs290-f24/assignment-1-YourGitHubUsername/). If your changes show up there, you can consider your files submitted.

In addition to submitting your assignment via GitHub, you must submit the URL to your code blog entry (e.g. http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/blog.html) via Canvas by the due date specified above.

## Grading criteria

The assignment is worth 100 total points, broken down as follows:

  * 30 points: Successfully logged in to the CS 290 forum on Ed Discussion and viewed at least one post.
    * There’s no need to post anything, just log in and view at least one post.  This will be verified based on whether you are marked as “active” in Ed’s analytics at the assignment deadline.
    * This part of the grade is all-or-nothing.  You will earn 0/20 points if you don’t log in.

  * 50 points: Created `index.html` and `blog.html` with the requested structure and content and pushed them to GitHub.
    * 10 points: `index.html` contains answers to the questions listed above
    * 10 points: `index.html` contains an image, as described above
    * 10 points: `blog.html` contains your first code blog entry, as described above
    * 10 points: Both `index.html` and `blog.html` are well structured (e.g. into paragraphs and headings, into ordered and/or unordered lists, etc.)
    * 10 points: Both `index.html` and `blog.html` contain a link to the other page

  * 20 points: Published `index.html` and `blog.html` to your ENGR web space or to GitHub Pages.
    * 15 points: Both pages are viewable online using an `http://...` or `https://...` URL (not a `file://...` URL!)
    * 5 points: All files associated with both pages (e.g. HTML, images, etc.) are viewable

In addition to your programming assignment grade, you will receive a pass/fail grade for your code blog entry, included in the code blog portion of your grade.
