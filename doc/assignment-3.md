---
title: "INF-2700 Mandatory Assignment No. 3"
subtitle: "Natural Join Operations"
date: "Deadline: Friday, 30 October 2026, 23:59"
---

# INF-2700 Mandatory Assignment No. 3

**Deadline:** Friday, 30 October 2026, 23:59  
**Submission:** Canvas  

## Overview

In this assignment, you will extend the `db2700` database management system with a natural join operation.

You may continue with your implementation from Assignment 2 or start with the provided base program without your Assignment 2 changes. The latest version of the base program and any supporting files are available through Canvas.

## Passing the Assignment

There are no specific requirements concerning which tasks you must complete or how much functionality you must implement.

**To pass the assignment, you only need to submit something in Canvas before the deadline.**

You are encouraged to work on as many of the tasks as you find useful. You may submit incomplete code, experiments, notes, a report, or other material showing your work.

You may ask for feedback on your work during the assignment period.

## Task 1: Implementing Natural Join

Implement the natural join operation using the following algorithms:

1. **Nested-loop join**, as described in Section 15.5.1 of the textbook.
2. **Block nested-loop join**, as described in Section 15.5.2 of the textbook.

You may assume that:

- the two tables being joined have exactly one common attribute; and
- the common attribute has the `int` type.

## Task 2: Performance

Run your implementations using relatively large tables. For example, the tables could contain enough data to occupy thousands of times the number of available buffer pages.

Profile the runs and compare the performance of the two join algorithms:

- nested-loop join;
- block nested-loop join.

Use the profiling functionality provided by the base program rather than measuring only elapsed execution time.

Also investigate whether the order of the input tables affects performance. In particular, consider two tables of very different sizes and compare:

```text
large_table NATURAL JOIN small_table
```

with:

```text
small_table NATURAL JOIN large_table
```

Discuss whether changing the left-right order of the tables makes a difference and explain your findings.

## Task 3: Think Outside the Box

This is a written task; no programming is required.

Suppose that both tables in the join are stored in B^+-tree-organised files and that the search key of each B^+-tree is the common attribute of the two tables.

Suggest a join algorithm that makes use of this file organisation.

Compare your suggested algorithm with the block nested-loop join algorithm. Your discussion may consider factors such as:

- the number of page accesses;
- the sizes of the input tables;
- the number of matching records;
- the height and fan-out of the B^+-trees;
- whether the common attributes contain duplicate values;
- the amount of available buffer space;
- the storage overhead of the B^+-tree indexes.

State any assumptions you make.

## Feedback

You may ask for feedback while working on the assignment. Feedback can cover, for example:

- your understanding of natural joins;
- your implementation approach;
- your nested-loop join implementation;
- your block nested-loop join implementation;
- debugging problems;
- test-data generation;
- profiling and performance experiments;
- interpretation of your results;
- your proposed B^+-tree-based join algorithm;
- drafts or incomplete work.

Consult the course information in Canvas for the available feedback channels and response times.

## Submission

Submit your work through **Canvas** before the deadline.

You may submit any material that represents your work, including incomplete work. Possible submission contents include:

- source code;
- test code or scripts;
- experimental results;
- profiling results;
- notes;
- diagrams;
- a written report;
- a short text describing what you attempted.

If you include source code, it is helpful to provide brief instructions explaining how to compile and run the program and experiments.

You are encouraged, but not required, to submit a report named `report-assignment3.pdf`. A report could include:

- a description of your design and implementation;
- instructions for running your program and experiments;
- performance results for your join algorithms;
- your findings about the algorithms' performance;
- the effect of changing the left-right order of the input tables;
- problems encountered and lessons learned;
- your proposed join algorithm for B^+-tree-organised files;
- a comparison with block nested-loop join.

Generated executables and large database table files normally do not need to be submitted, provided they can be regenerated from your source code.

**Remember: the only requirement for passing is to submit something in Canvas before the deadline.**

Enjoy coding, and good luck!
