# Career Information Day Scheduling

This project was one part of my submission for the second round of the 26th German National Competition in Compute Science (Bundeswettbewerb Informatik) held in 2007 and 2008. It was my first mixed integer program and I had a lot of fun, spending all my holidays on this exercise.

# Task

The goal is to schedule a career information day at a school:

- 16 talks by parents about their work

- 4 time slots

- students provide a preference list of six talks they would like to attend

- each talk has a minimum and maximum number of participants

The task is to write a simple-to-use software that schedules the talks to the 4 time slots and optimizes the satisfaction of students and parents with the GNU Linear Programming Kit (GLPK).

The full tasks can be found [here](Aufgabenstellung.pdf) (in German).

# My solution

I decided to use C++ with Qt4 as GUI and lifted the requirements of exactly 16 talks and 4 time slots to obtain a tool that would also be useful for other scheduling tasks. Also, the weight of preference of the students is fully flexible, meaning that all wishes could be equally good, or the first preference is much more preferred. The full documentation, which was part of the assignment, can be found [here](Dokumentation_Informationstag.pdf) (in German).

Fortunately, my submission was successful, and I could attend the third and final round (which was an in-person assessment), where I was selected as "award winner".

# Requirements

- Qt 4.3.2

- [GLPK](https://www.gnu.org/software/glpk/) 4.27

# Install (all Platforms)

As Qt4 is not supported anymore on newer operating systems, we recommend using a virtual machine [VirtualBox](https://www.virtualbox.org) running [Ubuntu 14.04.6 Trusty Tahr](https://www.osboxes.org/ubuntu/).

1. Install GLPK

2. Run `make` in the main directory to compile the program.

# Usage

- Run the program with `./Informationstag`

- Set the number of event slots (Termine).

- Set the number of preferences/wishes each student can have (Wünsche)

- Create the talks by choosing a name and a minimum/maximum number of participants in the "Angebot" section. Click "Hinzufügen" to add it to the list.

- Afterward, create participants by choosing a name and the preferences in the "Teilnehmer" section. It is also possible to create one or ten random participants.

- Finally, use weights for the priorities in the "Prioritäten" section. These are the coefficient in the objective.

- There are two optimization algorithms, a "fast" and an "optimal" one. For choosing the optimal algorithm, select the "Optimal" checkbox.

- Press "Plan erstellen" to run the optimization algorithm that creates a schedule.
