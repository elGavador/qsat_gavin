# Queen's Satellite Team (QSAT)
Below is an outline of a structure for the repository. It is tentative and open to discussion by the team. 

## Recent Update

* The spectrometer folder reads data from the AvaSpec-Mini spectrometer.
  The data has not been verified as valid.


* An implementation of CONOPS in C psuedo-code has been created in the src directory.
  Code follows C style guide where functions are NamedWithCapitals and variables are
  all lower case with_under_scores. See NASA C style guide for more details.

  

## Structure of Repository
Please read GitHub's excellent introduction:
https://guides.github.com/introduction/flow/

#### Branches
There is a Release branch that contains stable code that is tested and functional. There is a Development branch for integrating and testing features. There are Feature branches for developing features. When a recently merged Feature is tested and integrated into Development (i.e development is stable), Development will be merged into Release.  Master will contain the most stable known code.

The naming convention for feature branches will be: feature-(sub-system)-(name of feature). For example, if a I2C script was being developed for the Communication sub-system, a branch would be made from development with a branch name: feature-comm-I2Cscript. This format will allow the feature branches to be alphabetized together and easily readable.

| Acronyms for Branch Sub-System Names     |      |
|-----------------------------------------|------|
| Attitude Determination & Control System | adcs |
| Command and Data Handling               | cdh  |
| Communications                          | comm |
| Power                                   | pow  |

Master and Release will have limited privileges, meaning everyone will not be able to push to these branches. This is a common precautionary measure to reduce mistakes and allow team members who are not familiar with git to feel confident that they can push without ruining anything. In this case, a pull request will have to be made in order to merge into these branches.

Issue tracking is important. Issues will be tracked using the GitHub Issue feature which allows a team member to post an issue and the team to discuss the problem. When necessary, there will be branches for bug fixes and other issues as they arise. The naming convention will be iss(number), where (number) is given by the GitHub tracker. For more information read GitHub's excellent documentation:
https://guides.github.com/features/issues/

#### Commit Messages
Terrible commit messages are notorious. A good way to think of a commit message is a small email with a title and a message (if necessary), separated by a newline. Every commit message, regardless of size, should have a title that fits in the statement: if this commit were accepted it would (commit message). For example, a proper commit message would be "Remove X method from Y class" rather than "I removed X method from Y class". Commit messages are often easily understood at the time of committing but indecipherable at any later point. This can be avoided by being pedantic about what changes are being made and only making small changes. It really cannot be emphasized enough that spending an extra few minutes thinking about a descriptive commit message is invaluable. This structure allows the GitHub interface to be useful, rather than cumbersome, and makes roll backs and other changes easier to apply. It also offers a valuable chronology for future members. Please read:
https://chris.beams.io/posts/git-commit/

#### Directories
It may make sense for each sub-system to have its own directory. As directories are added to the repository, a short description will be added here.
