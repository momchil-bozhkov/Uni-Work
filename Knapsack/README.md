# Knapsack Problem Solver

This program is a C++ implementation of a solver for the 0-1 knapsack problem using a recursive approach. The knapsack problem, is a well-studied optimization problem in computer science and mathematics, involving selecting a combination of items from a given set to maximize the total value while considering the weight constraints of a knapsack.

In the 0-1 knapsack problem, each item can either be included (1) or excluded (0) from the knapsack,
meaning no fractional items are allowed. The goal is to find the combination of items that maximizes
the total value while not exceeding the knapsack's weight capacity. https://en.wikipedia.org/wiki/Knapsack_problem

The program expects an input file as a command-line parameter. This file should contain the problem
description, including the capacity of the knapsack and the weight-value pairs of each item. The
program reads this input file, solves the knapsack problem recursively, and provides the solution.

Example input files, "knapsack1" and "knapsack2", are provided for testing the program.