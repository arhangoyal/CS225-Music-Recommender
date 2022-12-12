# Development Logs

## Development Log (Date: 10/28/22 -- 11/04/22)

### Weekly Goals
1. We wanted to meet twice and have a final project idea ready. We **completed** the task.
2. We wanted to choose the dataset to use for our project. We **completed** the task.
3. We wanted to create a rough list of things to do with our dataset. We **completed** the task.
4. We wanted to complete our team contract. We **completed** the task.
5. Submit all deliverables on PrairieLearn. We **completed** the task.
6. Documented a starter list of algorithms we can use for our project. We **completed** the task.

### Specific Tasks Completed (and by who)
1. Brainstormed project idea and detailed what we wanted to do with our dataset (Sara, Arhan, Amitabh, Alex): We will essentially treat subreddit hyperlink data as a social network. Given the Stanford subreddit data graph, we perform a BFS traversal of the graph in order to find the shortest distance of hyperlinks between each subreddit. We then take the 5 closest subreddits based on hyperlink distance and print them out. The shorter the hyperlink distance, the more related two subreddits are. We also want to figure out if popularity correlates with number of links leading to the subreddit.
2. Found dataset to use (Alex): [Link to Reddit Hyperlinks Dataset](http://snap.stanford.edu/data/soc-RedditHyperlinks.html)
3. Created GitHub repository and shared it with team of 4 and our mentor (Arhan): [Link to repository](https://github.com/arhangoyal/CS225-Music-Recommender) has been created. The only thing left is sharing it with Sara, who will share her GitHub username later tonight since she is on the road.
4. Complete team contract (Amitabh): submitted on PrairieLearn.
5. Submit all deliverables on PrairieLearn (Arhan).
6. Documented a starter list of algorithms we can use for our project (Sara): PageRank, Djikstra's, &c. We have an initial list ready but will select the final one next week.
7. Submit an initial project proposal. All aspects could be subject to change depending on whether or not an optimization was discovered. (Alex, Amitabh, Arhan)

### Problems Encountered 
1. We did not encounter any problems except hearing each other since we met online for our meeting today (Friday). The noise at Grainger IDEA Lab was tough to hear over.

### Plans for next week
1. Decide algorithm to use: PageRank or Djikstra's algorithm
2. Start building out step 1 of project (basic grouping of subreddits), OR
3. Create shortest path algorithm (perhaps Djikstra's Algorithm?)

### Optional: Questions for mentor
1. Are there any optimizations you could think of?
2. What exactly does Eulerian walk/Cycle detection mean?


----


## Development Log (Date: 11/04/22 - 11/11/22)

### Weekly Goals
- We decided to plan which algorithm to use between Dijkstra's and PageRank. We were able to meet the goal.
- We decided to start structuring over our development and haven't been able to do so. We plan to meet on Saturday (12 Nov, 22) and meet the goal.
- We decided to start creating a file parser & preprocessor and haven't been able to do so. We plan to meet on Saturday (12 Nov, 22) and meet the goal.

### Specific Tasks Completed (and by who)
- Arhan and Sara have collectively decided how to revise our initial proposal for a successful regrade.
- Alex and Amitabh have collectively started conceptualizing the file parsers and algorithms to be developed soon.

### Problems Encountered 
- Majority members had crucial exams, for which we had to postpone our meet (11 Nov, 2022).

### Plans for next week
- Get the file parser and preprocessor running
- Get done with the BFS algorithm

### Optional: Questions for mentor
- We have a few question and will be reaching out directly via e-mail.


----


# Development Log (Date: 11/11/2022 -- 11/18/2022)

## Weekly Goals
1) Finalize project proposal and look at notes (IN PROGRESS)

2) Create a makefile / start working on project files (DONE)

3) Clean dataset / start work on a data cleaning program (IN PROGRESS)


## Specific Tasks Completed (and by who)

1) Create a makefile / start working on project files (Alex)


## Problems Encountered 
1) Still need to finish a new project proposal, as we don't have a proper uncovered algorithm

2) Considering changing the project topic overall to flight data instead due to topic complications


## Plans for next week
1) Finalize plans for project proposal
2) Figure out what uncovered algorithm will be chosen
3) Decide what dataset and goal we will go for
4) Begin creating an adjacency list / directed graph for overall usage regardless of topic/data

## Optional: Questions for mentor
N/A


----


# Development Log (Date: 11/18/2022 -- 11/25/2022)

## Weekly Goals:
1. Complete Mid-Project Check-in; talk to professor given our confusion in the project proposal
2. Study new dataset properly
2. Finish the data parsing and data cleaning

## Specific Tasks Completed (and by who)
1. Meet professor as suggested by our mentor: Arhan, Sara
2. Meet mentor (Savya) for check-in and demo data clean up and parsing: Arhan, Amitabh, Alex, Sara
3. Studied dataset to add one more data clean-up (remove >0 stop records to not duplicate paths in graph. Example: Chicago->Delhi 1 stop is just a repeat of Chicago->Amsterdam->Delhi): Arhan
4. Finalize data parsing and clean up: Alex, Arhan
5. Start working on individual algorithms (DFS, Dijikstra's, PageRank): work assigned and started

## Problems Encountered 
1. Project timeline due to project proposal mix-up. However, it has been cleared up now and we are back on schedule!

## Plans for next week
1. Complete algorithms by Wednesday, then write up a "Findings" document and make the project video
2. Get Git repository ready for final submission

## Optional: Questions for mentor
N/A
