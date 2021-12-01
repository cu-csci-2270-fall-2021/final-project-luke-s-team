# CSCI 2275 – Data Structures - Final Project

Please include a thorough description of your program's functionality. Imagine that you are publishing this for users who know nothing about this project. **Also, include the names of the team-members/authors**. 

	This project is a local repository for storing files. Similar to GitHub, however it only runs when the designed program is running.
  
	Starting the program prompts the user to enter one of seven options.
	Options Include:
  
	1 - Initialize the repository. Doing so will allow functionality for all other options.
  
	2 - Add a file to the repository. The user must enter a valid file name for the file to be added. 
	Furthermore, the file must already exist in the directory that the program is run from. 
  
	3 - Remove a file from the repository. Must be a valid file name that exists in the current repository.
  
	4 - Commit all added files, removed files, and changes made to files to the repository. All these most current changes will be saved in as a previous commit. 
	When committing a version, the user will be prompted to enter a valid commit message. The message must be no longer than three words. 
	If no changes have been made since the last commit, then a new commit will not be made.
  
	5 - Return to a previous commit. The user must enter a valid commit number to return to. 
	If the user chooses to move forward, all local changes in the directory will be lost and return to whatever was saved in the commit chosen to return to. 
	If not on the most recent commit, then the user cannot add, remove, or commit any files.
  
	6 - Search for a commit number based on a keyword. If the word entered matches any words in any previous commit messages, 
	then the version associated with that message will be displayed to the user. 
  
	7 - Quit the program. Doing so will delete the entire repository. The files in the current directory will be whatever they are when choosing this option.
