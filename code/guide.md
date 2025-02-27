# A Practical Guide to Coding Autons
This guide answers five main questions:
 * What is an auton?
 * What is our current auton strategy?
 * Where can I find & edit autons?
 * How do I code autons?
 * How do I test autons?
## 1. What is an auton?
An auton is a pre-programmed sequence of movements that the robot performs at the beginning of a match. Autons can have many strategies. Autons are written in C++. With the current architecture (v1), the drivetrain is controlled through two main functions: going forwards/backwards and turning to a specific angle. **All autons are coded from the perspective of the red alliance; a mirroring scheme is implemented for the blue alliance.**
### 1.1. Coordinate System for Autons
The coordinate system for autons is a little complicated. If you think of the red side of the field as a 6x3 grid of tiles (width of 6, height of 3, with the ladder on top), with the autonomous line going horizontally through the middle of the bottom row of tiles (farthest from the ladder), the center of the autonomous line is (0, 0). **Note: Do not worry for coordinates for now, they will only come into play for archie v2.** Negative x-values are in the nonrush (NR) side, and positive x-values are in the rush side (RS). (and vice versa for the blue side) The meaning of these names will be explained later. 

We use cartesian coordinates; that is, 0 is going right (again, from the perspective of the red drive team), 90 is going towards the blue side of the field, etc. Angles go counterclockwise.
## 2. What is our current auton strategy?
As of 9/15/24, this is a quick summary of our auton strategy.
Autons have three main goals: 1) getting the Autonomous Bonus, 2) getting the Autonomous Win Point (AWP) (only in quals), and 3) matching the driver strategy. The Autonomous Bonus is worth 6 points and can be earned by scored higher in autonomous. AWPs can be earning by completing all the following tasks:
 * At least three (3) Scored Rings of the Alliance’s color
 * A minimum of two (2) Stakes on the Alliance’s side of the Autonomous Line with at least (1)
 * Ring of the Alliance’s color Scored
 * Neither Robot contacting / breaking the plane of the Starting Line
 * At least one (1) Robot contacting the Ladder
(It is possible for neither or both of the alliances to get AWP as well)
Here are a few specific match strategies to think about:
 * Null: only move 24 inches for AWP, in case every single other auton is broken
 * PosCorn: the main early season meta strat is seizing both positive corners with full goals, so PosCorn (aka positive corner) strat is just to score as much as possible in auton
 * Disrupt: disrupting rings on the other side of the field (even if accidentally) prevents and/or interferes with the other side's auton, meaning that they may score less points -> giving us auton bonus or preventing them from getting AWP.
 * Rush: On one side of the field, there is a mogo on the autonomous line. This mogo is generally viewed as strategic to get (although there is often only time to do so in elims). However, since often both teams try to get that mogo, it is strategic to try to get it as early as possible (that is why we have a rubber piece on our doinker arm; it allows us to not have to drive forward as much and instead just deploy the doinker to grab the mogo). The side of field with the rush mogo on it is thus called rush side, and the other nonrush.
**Skills**: Skills is a part of V5RC where the team has 1 minute acting as the red alliance on a differently set-up field to score as many points as possible. There are both autonomous and driver skills runs, each of which follow the same rules. This year, 315P has agreed to run the autonomous section for both auton and driver skills, which means it has to be really good.
## 3. Where can I find & edit autons?
All autons are in the `src/autons.cpp` file. 
TODO: namespaces, blocks
## 4. How do I code autons?
TODO: dt functions, auton-specific functions, logging, subsys functions
## 5. How do I test autons?
