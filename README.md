# DiamondsMatch

## Enviroment
### Platform Tool
It was developed using visual studio 2019. if you're using it or any newer version to debug then no problem;
Otherwise you would have to change that manually:
Go to: Project->Properties->General->Platform Toolset and change it to your version;
### SDK
it uses Windows SDK 10.0;
### GTest
It uses google test library for unit testing, and you can check the tests by uncommenting the 2 lines in main.cpp;

## Future Work
### Design
Probablly It could have been better designed like added a matcher class for all the match operations instead, but I used the time to focus more on enhancing the matching criteria and the replacing of diamonds;
### UI and GamePlay
UI could have had a way of showing the timer going down, also I could have added more options for enhancing the gameplay, like adding the option for drag and drop as it currently only works if you clicked on two adjacent diamonds;
### Player Feedback
I should have added a way of providing a feedback for the player (for ex. if the swap was not succesfull and got reverted);
