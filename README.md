# Smart-Buffet-Meal-Planner-using-Greedy-and-Dynamic-Programming

A C-based optimization system that generates cost-effective and nutritionally balanced buffet meal combinations within a given budget. The project compares a fast Greedy approach with an optimal Dynamic Programming (Knapsack) solution, along with additional features like binary search for meal lookup and weekly buffet planning.

---

This project is a budget-based buffet meal planning system that selects meal combinations to maximize nutritional value while staying within a user-defined budget.

It demonstrates multiple algorithmic techniques:

* Greedy Algorithm (fast, approximate)
* Dynamic Programming (optimal solution using Knapsack)
* Binary Search (efficient meal lookup)

The system also generates a structured weekly buffet plan.

---

### Project Objectives:

* Optimize meal combination selection under budget constraints
* Compare Greedy vs Dynamic Programming approaches
* Demonstrate real-world application of optimization algorithms
* Enable fast searching using Binary Search
* Provide nutritional insights (protein, calories)

---

### Data Model:

Each meal combo contains:

* Name
* Cost
* Protein
* Calories
* Veg/Non-Veg
* Category (breakfast/lunch/dinner)

---

### Nutrition Score Formula:

```math
Nutrition\ Score = (Protein \times 2) + (Calories \times 0.1)
```

This prioritizes protein while also considering calorie intake.

---

### Greedy Approach

### Strategy:

* Select meal combos based on maximum nutrition per unit cost
* Sort → Pick best ratio → Continue until budget is exhausted

### Advantages:

* Very fast (O(n²) due to sorting in this implementation)
* Simple and efficient

### Limitation:

* May miss the globally optimal combination

---

### Dynamic Programming (0/1 Knapsack)

### Strategy:

Evaluate all possible combinations using a DP table

```math
dp[i][w] = max(dp[i-1][w], dp[i-1][w - cost] + value)
```

### Advantages:

* Guarantees optimal solution

### Limitation:

* Higher time complexity: O(n × budget)
* Uses additional memory

---

### Binary Search

### Purpose:

* Quickly search for a meal combo by name

### Strategy:

* Sort meal combos alphabetically
* Apply binary search

### Complexity:

* O(log n)

---

### Greedy vs Dynamic Programming

| Feature    | Greedy          | Dynamic Programming  |
| ---------- | --------------- | -------------------- |
| Speed      | Fast            | Slower               |
| Accuracy   | Approx          | Optimal              |
| Complexity | O(n²)           | O(n × budget)        |
| Use Case   | Quick decisions | Precise optimization |

---

### Features

* Budget-based buffet optimization
* Veg / Non-Veg filtering
* Meal type filtering (Breakfast / Lunch / Dinner)
* Nutritional analysis (Protein & Calories)
* Algorithm comparison output
* Weekly buffet meal planner
* Binary search for meal lookup

---

### Weekly Buffet Plan

The system generates a rotating weekly meal plan:

* Breakfast 
* Lunch 
* Dinner 

Each day includes a balanced combination of meals.

---

### Project Structure

```text
.
├── smart_buffet_meal_planner.c
│
├── Data Model
│   └── MealCombo (struct)
│
├── Algorithms
│   ├── greedy()
│   └── dp()
│
├── Utilities
│   ├── filterItems()
│   ├── displayItems()
│   ├── sortByName()
│   └── binarySearch()
│
├── Features
│   ├── weeklyBuffet()
│
└── main()
```

---

### How to Run

```bash
gcc smart_buffet_meal_planner.c -o planner
./planner
```

---

### Input Required:

* Budget
* Veg preference (1 = Yes, 0 = No)
* Meal type (breakfast / lunch / dinner / all)

---

### Sample Output

* Selected meal combos
* Total cost
* Protein & calorie summary
* Nutrition score
* Greedy vs DP comparison
* Weekly buffet plan
* Search result for a specific meal

---

### Key Concepts Demonstrated

* Greedy choice property
* Optimal substructure
* 0/1 Knapsack problem
* Binary Search
* Trade-off between speed and optimality

---

### Source Code

Main implementation file: 

---

### Conclusion

This project demonstrates how different algorithmic techniques can be combined to solve a real-world problem efficiently:

* Greedy → Fast and practical decisions
* Dynamic Programming → Optimal and accurate results
* Binary Search → Efficient data retrieval

A strong example of applying core computer science concepts to practical optimization problems.
